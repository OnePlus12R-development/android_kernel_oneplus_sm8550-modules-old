/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2021, The Linux Foundation. All rights reserved.
 */

#ifndef WSA884X_REG_SHIFTS_H
#define WSA884X_REG_SHIFTS_H
#include <linux/regmap.h>
#include <linux/device.h>
#include "wsa884x-registers.h"

/*
 * Use in conjunction with wsa884x-reg-masks.c for field values.
 * field_value = (register_value & field_mask) >> field_shift
 */

#define FIELD_SHIFT(register_name, field_name) \
	WSA884X_##register_name##_##field_name##_SHIFT

/* WSA884X_VSENSE1 Fields: */
#define WSA884X_VSENSE1_GAIN_VSENSE_FE_SHIFT                              0x05
#define WSA884X_VSENSE1_VSENSE_AMP_IQ_CTL_1_SHIFT                         0x04
#define WSA884X_VSENSE1_IDLE_MODE_CTL_SHIFT                               0x02
#define WSA884X_VSENSE1_VOCM_AMP_CTL_SHIFT                                0x00
/* WSA884X_ADC_2 Fields: */
#define WSA884X_ADC_2_ATEST_SEL_CAL_REF_SHIFT                             0x07
#define WSA884X_ADC_2_ISNS_LOAD_STORED_SHIFT                              0x06
#define WSA884X_ADC_2_EN_DET_SHIFT                                        0x05
#define WSA884X_ADC_2_EN_ATEST_REF_SHIFT                                  0x04
#define WSA884X_ADC_2_EN_ATEST_INT_SHIFT                                  0x01
#define WSA884X_ADC_2_D_ADC_REG_EN_SHIFT                                  0x00
/* WSA884X_ADC_7 Fields: */
#define WSA884X_ADC_7_CLAMPON_SHIFT                                       0x07
#define WSA884X_ADC_7_CAL_LOOP_TRIM_SHIFT                                 0x04
#define WSA884X_ADC_7_REG_TRIM_EN_SHIFT                                   0x03
#define WSA884X_ADC_7_EN_AZ_REG_SHIFT                                     0x02
#define WSA884X_ADC_7_EN_SAR_REG_SHIFT                                    0x01
#define WSA884X_ADC_7_EN_SW_CURRENT_REG_SHIFT                             0x00
/* WSA884X_BOP_DEGLITCH_CTL Fields: */
#define WSA884X_BOP_DEGLITCH_CTL_BOP_DEGLITCH_SETTING_SHIFT               0x01
#define WSA884X_BOP_DEGLITCH_CTL_BOP_DEGLITCH_EN_SHIFT                    0x00
/* WSA884X_CDC_SPK_DSM_A2_0 Fields: */
#define WSA884X_CDC_SPK_DSM_A2_0_COEF_A2_SHIFT                            0x00
/* WSA884X_CDC_SPK_DSM_A2_1 Fields: */
#define WSA884X_CDC_SPK_DSM_A2_1_COEF_A2_SHIFT                            0x00
/* WSA884X_CDC_SPK_DSM_A3_0 Fields: */
#define WSA884X_CDC_SPK_DSM_A3_0_COEF_A3_SHIFT                            0x00
/* WSA884X_CDC_SPK_DSM_A3_1 Fields: */
#define WSA884X_CDC_SPK_DSM_A3_1_COEF_A3_SHIFT                            0x00
/* WSA884X_CDC_SPK_DSM_A4_0 Fields: */
#define WSA884X_CDC_SPK_DSM_A4_0_COEF_A4_SHIFT                            0x00
/* WSA884X_CDC_SPK_DSM_A5_0 Fields: */
#define WSA884X_CDC_SPK_DSM_A5_0_COEF_A5_SHIFT                            0x00
/* WSA884X_CDC_SPK_DSM_A6_0 Fields: */
#define WSA884X_CDC_SPK_DSM_A6_0_COEF_A6_SHIFT                            0x00
/* WSA884X_CDC_SPK_DSM_A7_0 Fields: */
#define WSA884X_CDC_SPK_DSM_A7_0_COEF_A7_SHIFT                            0x00
/* WSA884X_CDC_SPK_DSM_C_0 Fields: */
#define WSA884X_CDC_SPK_DSM_C_0_COEF_C3_SHIFT                             0x04
#define WSA884X_CDC_SPK_DSM_C_0_COEF_C2_SHIFT                             0x00
/* WSA884X_CDC_SPK_DSM_C_2 Fields: */
#define WSA884X_CDC_SPK_DSM_C_2_COEF_C7_SHIFT                             0x04
#define WSA884X_CDC_SPK_DSM_C_2_COEF_C6_SHIFT                             0x00
/* WSA884X_CDC_SPK_DSM_C_3 Fields: */
#define WSA884X_CDC_SPK_DSM_C_3_COEF_C7_SHIFT                             0x00
/* WSA884X_CDC_SPK_DSM_R1 Fields: */
#define WSA884X_CDC_SPK_DSM_R1_SAT_LIMIT_R1_SHIFT                         0x00
/* WSA884X_CDC_SPK_DSM_R2 Fields: */
#define WSA884X_CDC_SPK_DSM_R2_SAT_LIMIT_R2_SHIFT                         0x00
/* WSA884X_CDC_SPK_DSM_R3 Fields: */
#define WSA884X_CDC_SPK_DSM_R3_SAT_LIMIT_R3_SHIFT                         0x00
/* WSA884X_CDC_SPK_DSM_R4 Fields: */
#define WSA884X_CDC_SPK_DSM_R4_SAT_LIMIT_R4_SHIFT                         0x00
/* WSA884X_CDC_SPK_DSM_R5 Fields: */
#define WSA884X_CDC_SPK_DSM_R5_SAT_LIMIT_R5_SHIFT                         0x00
/* WSA884X_CDC_SPK_DSM_R6 Fields: */
#define WSA884X_CDC_SPK_DSM_R6_SAT_LIMIT_R6_SHIFT                         0x00
/* WSA884X_CDC_SPK_DSM_R7 Fields: */
#define WSA884X_CDC_SPK_DSM_R7_SAT_LIMIT_R7_SHIFT                         0x00
/* WSA884X_DRE_CTL_0 Fields: */
#define WSA884X_DRE_CTL_0_PROG_DELAY_SHIFT                                0x04
#define WSA884X_DRE_CTL_0_OFFSET_SHIFT                                    0x00
/* WSA884X_GAIN_RAMPING_MIN Fields: */
#define WSA884X_GAIN_RAMPING_MIN_MIN_GAIN_SHIFT                           0x00
/* WSA884X_CLSH_SOFT_MAX Fields: */
#define WSA884X_CLSH_SOFT_MAX_SOFT_MAX_SHIFT                              0x00
/* WSA884X_CLSH_VTH1 Fields: */
#define WSA884X_CLSH_VTH1_CLSH_VTH1_SHIFT                                 0x00
/* WSA884X_CLSH_VTH10 Fields: */
#define WSA884X_CLSH_VTH10_CLSH_VTH10_SHIFT                               0x00
/* WSA884X_CLSH_VTH11 Fields: */
#define WSA884X_CLSH_VTH11_CLSH_VTH11_SHIFT                               0x00
/* WSA884X_CLSH_VTH12 Fields: */
#define WSA884X_CLSH_VTH12_CLSH_VTH12_SHIFT                               0x00
/* WSA884X_CLSH_VTH13 Fields: */
#define WSA884X_CLSH_VTH13_CLSH_VTH13_SHIFT                               0x00
/* WSA884X_CLSH_VTH14 Fields: */
#define WSA884X_CLSH_VTH14_CLSH_VTH14_SHIFT                               0x00
/* WSA884X_CLSH_VTH15 Fields: */
#define WSA884X_CLSH_VTH15_CLSH_VTH15_SHIFT                               0x00
/* WSA884X_ANA_WO_CTL_0 Fields: */
#define WSA884X_ANA_WO_CTL_0_VPHX_SYS_EN_SHIFT                            0x06
#define WSA884X_ANA_WO_CTL_0_PA_AUX_GAIN_SHIFT                            0x02
#define WSA884X_ANA_WO_CTL_0_PA_MIN_GAIN_BYP_SHIFT                        0x01
#define WSA884X_ANA_WO_CTL_0_DAC_CM_CLAMP_EN_SHIFT                        0x00
/* WSA884X_ANA_WO_CTL_1 Fields: */
#define WSA884X_ANA_WO_CTL_1_BOOST_SHARE_EN_SHIFT                         0x03
#define WSA884X_ANA_WO_CTL_1_EXT_VDDSPK_EN_SHIFT                          0x00
/* WSA884X_DRE_CTL_1 Fields: */
#define WSA884X_DRE_CTL_1_CSR_GAIN_SHIFT                                  0x01
#define WSA884X_DRE_CTL_1_CSR_GAIN_EN_SHIFT                               0x00
/* WSA884X_VBAT_THRM_FLT_CTL Fields: */
#define WSA884X_VBAT_THRM_FLT_CTL_THRM_COEF_SEL_SHIFT                     0x05
#define WSA884X_VBAT_THRM_FLT_CTL_THRM_FLT_EN_SHIFT                       0x04
#define WSA884X_VBAT_THRM_FLT_CTL_VBAT_COEF_SEL_SHIFT                     0x01
#define WSA884X_VBAT_THRM_FLT_CTL_VBAT_FLT_EN_SHIFT                       0x00
/* WSA884X_PDM_WD_CTL Fields: */
#define WSA884X_PDM_WD_CTL_HOLD_OFF_SHIFT                                 0x02
#define WSA884X_PDM_WD_CTL_TIME_OUT_SEL_SHIFT                             0x01
#define WSA884X_PDM_WD_CTL_PDM_WD_EN_SHIFT                                0x00
/* WSA884X_PA_FSM_BYP_CTL Fields: */
#define WSA884X_PA_FSM_BYP_CTL_PA_FSM_BYP_SHIFT                           0x00
/* WSA884X_TADC_VALUE_CTL Fields: */
#define WSA884X_TADC_VALUE_CTL_VBAT_VALUE_RD_EN_SHIFT                     0x01
#define WSA884X_TADC_VALUE_CTL_TEMP_VALUE_RD_EN_SHIFT                     0x00
/* WSA884X_PA_FSM_BYP0 Fields: */
#define WSA884X_PA_FSM_BYP0_TSADC_EN_SHIFT                                0x07
#define WSA884X_PA_FSM_BYP0_SPKR_PROT_EN_SHIFT                            0x06
#define WSA884X_PA_FSM_BYP0_D_UNMUTE_SHIFT                                0x05
#define WSA884X_PA_FSM_BYP0_PA_EN_SHIFT                                   0x04
#define WSA884X_PA_FSM_BYP0_BOOST_EN_SHIFT                                0x03
#define WSA884X_PA_FSM_BYP0_BG_EN_SHIFT                                   0x02
#define WSA884X_PA_FSM_BYP0_CLK_WD_EN_SHIFT                               0x01
#define WSA884X_PA_FSM_BYP0_DC_CAL_EN_SHIFT                               0x00
/* WSA884X_PA_FSM_BYP1 Fields: */
#define WSA884X_PA_FSM_BYP1_NG_MODE_SHIFT                                 0x06
#define WSA884X_PA_FSM_BYP1_PWRSAV_CTL_SHIFT                              0x05
#define WSA884X_PA_FSM_BYP1_RAMP_DOWN_SHIFT                               0x04
#define WSA884X_PA_FSM_BYP1_RAMP_UP_SHIFT                                 0x03
#define WSA884X_PA_FSM_BYP1_BLEEDER_EN_SHIFT                              0x02
#define WSA884X_PA_FSM_BYP1_PA_MAIN_EN_SHIFT                              0x01
#define WSA884X_PA_FSM_BYP1_PA_AUX_EN_SHIFT                               0x00
/* WSA884X_PA_FSM_EN Fields: */
#define WSA884X_PA_FSM_EN_GLOBAL_PA_EN_SHIFT                              0x00
#endif /* WSA884X_REG_SHIFTS_H */
