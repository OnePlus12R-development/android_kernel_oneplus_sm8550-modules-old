// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2017-2021, The Linux Foundation. All rights reserved.
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/debugfs.h>
#include <linux/videodev2.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <media/cam_sync.h>
#include <media/cam_defs.h>
#include <media/cam_icp.h>
#include "cam_node.h"
#include "cam_context.h"
#include "cam_context_utils.h"
#include "cam_icp_context.h"
#include "cam_req_mgr_util.h"
#include "cam_mem_mgr.h"
#include "cam_trace.h"
#include "cam_debug_util.h"
#include "cam_packet_util.h"
#include "cam_req_mgr_dev.h"
#include "cam_icp_hw_mgr_intf.h"

static const char icp_dev_name[] = "cam-icp";

static int cam_icp_context_dump_active_request(void *data, void *args)
{
	struct cam_context         *ctx = (struct cam_context *)data;
	struct cam_ctx_request     *req = NULL;
	struct cam_ctx_request     *req_temp = NULL;
	struct cam_hw_dump_pf_args *pf_args = (struct cam_hw_dump_pf_args *)args;
	int rc = 0;

	if (!ctx || !pf_args) {
		CAM_ERR(CAM_ICP, "Invalid ctx %pK or pf args %pK",
			ctx, pf_args);
		return -EINVAL;
	}

	CAM_INFO(CAM_ICP, "iommu fault for icp ctx %d state %d",
		ctx->ctx_id, ctx->state);

	list_for_each_entry_safe(req, req_temp,
			&ctx->active_req_list, list) {
		CAM_INFO(CAM_ICP, "Active req_id: %llu ctx_id: %u",
			req->request_id, ctx->ctx_id);

		rc = cam_context_dump_pf_info_to_hw(ctx, pf_args, &req->pf_data);
		if (rc)
			CAM_ERR(CAM_ICP, "Failed to dump pf info ctx_id: %u state: %d",
				ctx->ctx_id, ctx->state);
	}

	/*
	 * Faulted ctx found. Since IPE/BPS instances are shared among contexts,
	 * faulted ctx is found if and only if the context contains
	 * faulted buffer
	 */
	if (pf_args->pf_context_info.ctx_found) {
		/* Send PF notification to UMD if PF found on current CTX */
		rc = cam_context_send_pf_evt(ctx, pf_args);
		if (rc)
			CAM_ERR(CAM_ICP,
				"Failed to notify PF event to userspace rc: %d", rc);
	}

	return rc;
}

static int cam_icp_context_mini_dump(void *priv, void *args)
{
	int rc;
	struct cam_context *ctx;

	if (!priv || !args) {
		CAM_ERR(CAM_ICP, "Invalid priv %pK args %pK", priv, args);
		return -EINVAL;
	}

	ctx = (struct cam_context *)priv;
	rc = cam_context_mini_dump(ctx, args);
	if (rc)
		CAM_ERR(CAM_ICP, "ctx [id: %u name: %s] Mini Dump failed rc %d", ctx->dev_name,
			ctx->ctx_id, rc);

	return rc;
}

static int __cam_icp_acquire_dev_in_available(struct cam_context *ctx,
	struct cam_acquire_dev_cmd *cmd)
{
	int rc;

	rc = cam_context_acquire_dev_to_hw(ctx, cmd);
	if (!rc) {
		ctx->state = CAM_CTX_ACQUIRED;
		trace_cam_context_state("ICP", ctx);
	}

	return rc;
}

static int __cam_icp_release_dev_in_acquired(struct cam_context *ctx,
	struct cam_release_dev_cmd *cmd)
{
	int rc;

	rc = cam_context_release_dev_to_hw(ctx, cmd);
	if (rc)
		CAM_ERR(CAM_ICP, "Unable to release device");

	cam_common_release_err_params(ctx->dev_hdl);

	ctx->state = CAM_CTX_AVAILABLE;
	trace_cam_context_state("ICP", ctx);
	return rc;
}

static int __cam_icp_start_dev_in_acquired(struct cam_context *ctx,
	struct cam_start_stop_dev_cmd *cmd)
{
	int rc;

	rc = cam_context_start_dev_to_hw(ctx, cmd);
	if (!rc) {
		ctx->state = CAM_CTX_READY;
		trace_cam_context_state("ICP", ctx);
	}

	return rc;
}

static int __cam_icp_dump_dev_in_ready(
	struct cam_context      *ctx,
	struct cam_dump_req_cmd *cmd)
{
	int rc;

	rc = cam_context_dump_dev_to_hw(ctx, cmd);
	if (rc)
		CAM_ERR(CAM_ICP, "Failed to dump device");

	return rc;
}

static int __cam_icp_flush_dev_in_ready(struct cam_context *ctx,
	struct cam_flush_dev_cmd *cmd)
{
	int rc;

	rc = cam_context_flush_dev_to_hw(ctx, cmd);
	if (rc)
		CAM_ERR(CAM_ICP, "Failed to flush device");

	return rc;
}

static int __cam_icp_config_dev_in_ready(struct cam_context *ctx,
	struct cam_config_dev_cmd *cmd)
{
	int rc;
	size_t len;
	uintptr_t packet_addr;
	struct cam_packet *packet;
	size_t remain_len = 0;

	rc = cam_mem_get_cpu_buf((int32_t) cmd->packet_handle,
		&packet_addr, &len);
	if (rc) {
		CAM_ERR(CAM_ICP, "[%s][%d] Can not get packet address",
			ctx->dev_name, ctx->ctx_id);
		rc = -EINVAL;
		return rc;
	}

	remain_len = len;
	if ((len < sizeof(struct cam_packet)) ||
		(cmd->offset >= (len - sizeof(struct cam_packet)))) {
		CAM_ERR(CAM_CTXT,
			"Invalid offset, len: %zu cmd offset: %llu sizeof packet: %zu",
			len, cmd->offset, sizeof(struct cam_packet));
		return -EINVAL;
	}

	remain_len -= (size_t)cmd->offset;
	packet = (struct cam_packet *) ((uint8_t *)packet_addr +
		(uint32_t)cmd->offset);

	rc = cam_packet_util_validate_packet(packet, remain_len);
	if (rc) {
		CAM_ERR(CAM_CTXT, "Invalid packet params, remain length: %zu",
			remain_len);
		return rc;
	}

	if (((packet->header.op_code & 0xff) ==
		CAM_ICP_OPCODE_IPE_SETTINGS) ||
		((packet->header.op_code & 0xff) ==
		CAM_ICP_OPCODE_BPS_SETTINGS))
		rc = cam_context_config_dev_to_hw(ctx, cmd);
	else
		rc = cam_context_prepare_dev_to_hw(ctx, cmd);

	if (rc)
		CAM_ERR(CAM_ICP, "Failed to prepare device");

	return rc;
}

static int __cam_icp_stop_dev_in_ready(struct cam_context *ctx,
	struct cam_start_stop_dev_cmd *cmd)
{
	int rc;

	rc = cam_context_stop_dev_to_hw(ctx);
	if (rc)
		CAM_ERR(CAM_ICP, "Failed to stop device");

	ctx->state = CAM_CTX_ACQUIRED;
	trace_cam_context_state("ICP", ctx);
	return rc;
}

static int __cam_icp_release_dev_in_ready(struct cam_context *ctx,
	struct cam_release_dev_cmd *cmd)
{
	int rc;

	rc = __cam_icp_stop_dev_in_ready(ctx, NULL);
	if (rc)
		CAM_ERR(CAM_ICP, "Failed to stop device");

	rc = __cam_icp_release_dev_in_acquired(ctx, cmd);
	if (rc)
		CAM_ERR(CAM_ICP, "Failed to release device");

	return rc;
}

static uint32_t get_error_code(uint32_t err_type)
{
	switch (err_type) {
	case CAM_ICP_HW_ERROR_NO_MEM:
		return CAM_REQ_MGR_ICP_NO_MEMORY;
	case CAM_ICP_HW_ERROR_SYSTEM_FAILURE:
		return CAM_REQ_MGR_ICP_SYSTEM_FAILURE;
	default:
		return 0;
	}
}

static int __cam_icp_notify_v4l2_err_evt(struct cam_context *ctx,
	uint32_t err_type, uint32_t err_code, uint64_t request_id)
{
	struct cam_req_mgr_message req_msg = {0};
	int rc;

	req_msg.session_hdl = ctx->session_hdl;
	req_msg.u.err_msg.device_hdl = ctx->dev_hdl;
	req_msg.u.err_msg.error_type = err_type;
	req_msg.u.err_msg.link_hdl = ctx->link_hdl;
	req_msg.u.err_msg.request_id = request_id;
	req_msg.u.err_msg.resource_size = 0x0;
	req_msg.u.err_msg.error_code = err_code;

	rc = cam_req_mgr_notify_message(&req_msg, V4L_EVENT_CAM_REQ_MGR_ERROR,
		V4L_EVENT_CAM_REQ_MGR_EVENT);
	if (rc)
		CAM_ERR(CAM_ICP,
			"Error in notifying the error time for req id:%lld ctx %u",
			request_id,
			ctx->ctx_id);

	CAM_INFO(CAM_ICP,
		"CTX: [%s][%d] notifying error to userspace err type: %d, err code: %u, req id: %llu",
		ctx->dev_name, ctx->ctx_id, err_type, err_code, request_id);

	return rc;
}

static int cam_icp_ctx_handle_fatal_error(void *ctx, void *err_evt_data)
{
	struct cam_icp_hw_error_evt_data *err_evt;
	uint32_t err_code = 0;
	int rc;

	err_evt = (struct cam_icp_hw_error_evt_data *)err_evt_data;
	err_code = get_error_code(err_evt->err_type);

	rc = __cam_icp_notify_v4l2_err_evt(ctx, CAM_REQ_MGR_ERROR_TYPE_RECOVERY,
		err_code, err_evt->req_id);

	return rc;
}

static int cam_icp_ctx_handle_buf_done_in_ready(void *ctx, void *done_evt_data)
{
	struct cam_icp_hw_buf_done_evt_data *buf_done;

	buf_done = (struct cam_icp_hw_buf_done_evt_data *)done_evt_data;
	return cam_context_buf_done_from_hw(ctx, buf_done->buf_done_data, buf_done->evt_id);
}

static int __cam_icp_ctx_handle_hw_event(void *ctx,
	uint32_t evt_id, void *evt_data)
{
	int rc;

	if (!ctx || !evt_data) {
		CAM_ERR(CAM_ICP, "Invalid ctx and event data");
		return -EINVAL;
	}

	switch (evt_id) {
	case CAM_ICP_EVT_ID_BUF_DONE:
		rc = cam_icp_ctx_handle_buf_done_in_ready(ctx, evt_data);
		break;
	case CAM_ICP_EVT_ID_ERROR:
		rc = cam_icp_ctx_handle_fatal_error(ctx, evt_data);
		break;
	default:
		CAM_ERR(CAM_ICP, "Invalid event id: %d", evt_id);
		rc = -EINVAL;
	}

	return rc;
}

static int cam_icp_context_inject_error(void *context, void *err_param)
{
	int rc = 0;
	uint32_t err_code;
	uint32_t err_type;
	uint64_t req_id;
	struct cam_context *ctx = (struct cam_context *)context;

	if (!err_param) {
		CAM_ERR(CAM_ICP, "err_params is not valid");
		return -EINVAL;
	}

	err_code = ((struct cam_err_inject_param *)err_param)->err_code;
	err_type = ((struct cam_err_inject_param *)err_param)->err_type;
	req_id = ((struct cam_err_inject_param *)err_param)->req_id;

	switch (err_type) {
	case CAM_SYNC_STATE_SIGNALED_ERROR:
		switch (err_code) {
		case CAM_SYNC_ICP_EVENT_FRAME_PROCESS_FAILURE:
		case CAM_SYNC_ICP_EVENT_CONFIG_ERR:
			break;
		default:
			CAM_ERR(CAM_ICP, "ICP Error code %d not supported!", err_code);
			return -EINVAL;
		}
		break;
	default:
		CAM_ERR(CAM_ICP, "ICP Error type: %d not supported!", err_code);
		return -EINVAL;
	}

	CAM_INFO(CAM_ICP,
		"Err inject params: err_code: %u err_type: %u, to dev_hdl: %lld",
		err_code, err_type, ctx->dev_hdl);

	rc = cam_context_err_to_hw(ctx, err_param);

	return rc;
}

static struct cam_ctx_ops
	cam_icp_ctx_state_machine[CAM_CTX_STATE_MAX] = {
	/* Uninit */
	{
		.ioctl_ops = {},
		.crm_ops = {},
		.irq_ops = NULL,
	},
	/* Available */
	{
		.ioctl_ops = {
			.acquire_dev = __cam_icp_acquire_dev_in_available,
		},
		.crm_ops = {},
		.irq_ops = NULL,
		.mini_dump_ops = cam_icp_context_mini_dump,
	},
	/* Acquired */
	{
		.ioctl_ops = {
			.release_dev = __cam_icp_release_dev_in_acquired,
			.start_dev = __cam_icp_start_dev_in_acquired,
			.config_dev = __cam_icp_config_dev_in_ready,
			.flush_dev = __cam_icp_flush_dev_in_ready,
			.dump_dev = __cam_icp_dump_dev_in_ready,
		},
		.crm_ops = {},
		.irq_ops = __cam_icp_ctx_handle_hw_event,
		.pagefault_ops = cam_icp_context_dump_active_request,
		.mini_dump_ops = cam_icp_context_mini_dump,
		.err_inject_ops = cam_icp_context_inject_error,
	},
	/* Ready */
	{
		.ioctl_ops = {
			.stop_dev = __cam_icp_stop_dev_in_ready,
			.release_dev = __cam_icp_release_dev_in_ready,
			.config_dev = __cam_icp_config_dev_in_ready,
			.flush_dev = __cam_icp_flush_dev_in_ready,
			.dump_dev = __cam_icp_dump_dev_in_ready,
		},
		.crm_ops = {},
		.irq_ops = __cam_icp_ctx_handle_hw_event,
		.pagefault_ops = cam_icp_context_dump_active_request,
		.mini_dump_ops = cam_icp_context_mini_dump,
		.err_inject_ops = cam_icp_context_inject_error,
	},
	/* Flushed */
	{
		.ioctl_ops = {},
	},
	/* Activated */
	{
		.ioctl_ops = {},
		.crm_ops = {},
		.irq_ops = NULL,
		.pagefault_ops = cam_icp_context_dump_active_request,
		.mini_dump_ops = cam_icp_context_mini_dump,
		.err_inject_ops = cam_icp_context_inject_error,
	},
};

int cam_icp_context_init(struct cam_icp_context *ctx,
	struct cam_hw_mgr_intf *hw_intf, uint32_t ctx_id, int img_iommu_hdl)
{
	int rc;

	if ((!ctx) || (!ctx->base) || (!hw_intf)) {
		CAM_ERR(CAM_ICP, "Invalid params: %pK %pK", ctx, hw_intf);
		rc = -EINVAL;
		goto err;
	}

	rc = cam_context_init(ctx->base, icp_dev_name, CAM_ICP, ctx_id,
		NULL, hw_intf, ctx->req_base, CAM_CTX_ICP_REQ_MAX, img_iommu_hdl);
	if (rc) {
		CAM_ERR(CAM_ICP, "Camera Context Base init failed");
		goto err;
	}

	ctx->base->state_machine = cam_icp_ctx_state_machine;
	ctx->base->ctx_priv = ctx;
	ctx->base->max_hw_update_entries = CAM_CTX_CFG_MAX;
	ctx->base->max_in_map_entries = CAM_CTX_CFG_MAX;
	ctx->base->max_out_map_entries = CAM_CTX_CFG_MAX;
	ctx->ctxt_to_hw_map = NULL;

err:
	return rc;
}

int cam_icp_context_deinit(struct cam_icp_context *ctx)
{
	if ((!ctx) || (!ctx->base)) {
		CAM_ERR(CAM_ICP, "Invalid params: %pK", ctx);
		return -EINVAL;
	}

	cam_context_deinit(ctx->base);
	memset(ctx, 0, sizeof(*ctx));

	return 0;
}
