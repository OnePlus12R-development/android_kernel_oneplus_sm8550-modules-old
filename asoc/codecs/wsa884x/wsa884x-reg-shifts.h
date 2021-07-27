/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2021, The Linux Foundation. All rights reserved.
 */

#ifndef WSA884X_REG_SHIFTS_H
#define WSA884X_REG_SHIFTS_H
#include <linux/regmap.h>
#include <linux/device.h>
#include "wsa884x-registers.h"

#define FIELD_SHIFT(register_name, field_name) \
	WSA884X_##register_name##_##field_name##_SHIFT

#define WSA884X_VBAT_SNS_BOP_FREQ_SHIFT 0x05
#define WSA884X_ISENSE2_ISENSE_GAIN_CTL_SHIFT 0x05
#define WSA884X_ADC_2_ISNS_LOAD_STORED_SHIFT 0x06
#define WSA884X_ADC_6_INTRLV_RST_OVRD_SHIFT 0x01
#define WSA884X_ADC_7_EN_AZ_REG_SHIFT 0x02
#define WSA884X_ADC_7_EN_SAR_REG_SHIFT 0x01
#define WSA884X_CURRENT_LIMIT_CURRENT_LIMIT_OVRD_EN_SHIFT 0x07
#define WSA884X_CURRENT_LIMIT_CURRENT_LIMIT_SHIFT 0x02
#define WSA884X_BOOST_MISC_SPKR_RDY_CTL_SHIFT 0x05
#define WSA884X_CKWD_CTL_0_CKWD_FDIV_SEL_SHIFT 0x05
#define WSA884X_CKWD_CTL_1_CKWD_VCOMP_VREF_SEL_SHIFT 0x00
#define WSA884X_CHIP_ID0_BYTE_0_SHIFT 0x00
#define WSA884X_PA_FSM_EN_GLOBAL_PA_EN_SHIFT 0x00
#define WSA884X_PA_FSM_BYP_CTL_PA_FSM_BYP_SHIFT 0x00
#define WSA884X_PA_FSM_BYP0_TSADC_EN_SHIFT 0x07
#define WSA884X_PA_FSM_BYP0_SPKR_PROT_EN_SHIFT 0x06
#define WSA884X_PA_FSM_BYP0_D_UNMUTE_SHIFT 0x05
#define WSA884X_PA_FSM_BYP0_BG_EN_SHIFT 0x02
#define WSA884X_PA_FSM_BYP0_CLK_WD_EN_SHIFT 0x01
#define WSA884X_PA_FSM_BYP0_DC_CAL_EN_SHIFT 0x00
#define WSA884X_TADC_VALUE_CTL_TEMP_VALUE_RD_EN_SHIFT 0x00
#define WSA884X_TEMP_CONFIG0_CTL_THRD_SAF2WAR_SHIFT 0x00
#define WSA884X_TEMP_CONFIG1_CTL_THRD_WAR2SAF_SHIFT 0x00
#define WSA884X_VBAT_THRM_FLT_CTL_VBAT_COEF_SEL_SHIFT 0x01
#define WSA884X_VBAT_THRM_FLT_CTL_VBAT_FLT_EN_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_A2_0_COEF_A2_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_A2_1_COEF_A2_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_A3_0_COEF_A3_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_A3_1_COEF_A3_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_A4_0_COEF_A4_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_A4_1_COEF_A4_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_A5_0_COEF_A5_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_A5_1_COEF_A5_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_A6_0_COEF_A6_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_A7_0_COEF_A7_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_C_0_COEF_C3_SHIFT 0x04
#define WSA884X_CDC_SPK_DSM_C_0_COEF_C2_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_C_1_COEF_C5_SHIFT 0x04
#define WSA884X_CDC_SPK_DSM_C_1_COEF_C4_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_C_2_COEF_C7_SHIFT 0x04
#define WSA884X_CDC_SPK_DSM_C_2_COEF_C6_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_C_3_COEF_C7_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_R1_SAT_LIMIT_R1_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_R2_SAT_LIMIT_R2_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_R3_SAT_LIMIT_R3_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_R4_SAT_LIMIT_R4_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_R5_SAT_LIMIT_R5_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_R6_SAT_LIMIT_R6_SHIFT 0x00
#define WSA884X_CDC_SPK_DSM_R7_SAT_LIMIT_R7_SHIFT 0x00
#define WSA884X_PDM_WD_CTL_PDM_WD_EN_SHIFT 0x00
#define WSA884X_DRE_CTL_0_PROG_DELAY_SHIFT 0x04
#define WSA884X_DRE_CTL_0_OFFSET_SHIFT 0x00
#define WSA884X_DRE_CTL_1_CSR_GAIN_SHIFT 0x01
#define WSA884X_DRE_CTL_1_CSR_GAIN_EN_SHIFT 0x00
#define WSA884X_TAGC_CTL_THERMAL_THRESH_SHIFT 0x01
#define WSA884X_TAGC_CTL_THERMAL_AGC_EN_SHIFT 0x00
#define WSA884X_TAGC_TIME_REL_TIME_SHIFT 0x04
#define WSA884X_VAGC_CTL_VBAT_AGC_EN_SHIFT 0x00
#define WSA884X_VAGC_TIME_REL_TIME_SHIFT 0x02
#define WSA884X_VAGC_TIME_HLD_TIME_SHIFT 0x00
#define WSA884X_VAGC_ATTN_LVL_2_VBAT_ATTN_LVL_SHIFT 0x00
#define WSA884X_VAGC_ATTN_LVL_3_VBAT_ATTN_LVL_SHIFT 0x00
#define WSA884X_OTP_REG_0_WSA884X_ID_SHIFT 0x00
#define WSA884X_OTP_REG_1_LOW_TEMP_MSB_SHIFT 0x00
#define WSA884X_OTP_REG_2_LOW_TEMP_LSB_SHIFT 0x06
#define WSA884X_OTP_REG_3_HIGH_TEMP_MSB_SHIFT 0x00
#define WSA884X_OTP_REG_4_HIGH_TEMP_LSB_SHIFT 0x06
#define WSA884X_DRE_IDLE_DET_CTL_PA_OFF_FORCE_EN_SHIFT 0x06
#define WSA884X_DRE_IDLE_DET_CTL_PDM_WD_FORCE_EN_SHIFT 0x05
#define WSA884X_DRE_IDLE_DET_CTL_DRE_IDLE_FORCE_EN_SHIFT 0x04
#define WSA884X_DRE_IDLE_DET_CTL_DRE_FORCE_VALUE_SHIFT 0x00

#endif /* WSA884X_REG_SHIFTS_H */
