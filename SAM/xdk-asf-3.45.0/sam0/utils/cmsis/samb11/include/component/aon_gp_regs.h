/**
 * \file
 *
 * \brief Component description for AON_GP_REGS
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#ifndef _SAMB11_AON_GP_REGS_COMPONENT_
#define _SAMB11_AON_GP_REGS_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR AON_GP_REGS */
/* ========================================================================== */
/** \addtogroup SAMB11_AON_GP_REGS Always On General Purpose Registers 
 *  @{
 */

#ifndef COMPONENT_TYPEDEF_STYLE
  #define COMPONENT_TYPEDEF_STYLE 'N'  /**< Defines default style of typedefs for the component header files ('R' = RFO, 'N' = NTO*/
#endif

#define AON_GP_REGS_AGR1234
#define REV_AON_GP_REGS                  0x100

/* -------- AON_GP_REGS_AON_PINMUX_SEL : (AON_GP_REGS Offset: 0x00) (R/W 16) Controls the pinmux selection for the AO GPIOs -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t AO_GPIO_0_SEL:2;           /**< bit:   0..1  Pinmux select for AO_GPIO_0              */
    uint16_t :2;                        /**< bit:   2..3  Reserved */
    uint16_t AO_GPIO_1_SEL:2;           /**< bit:   4..5  Pinmux select for AO_GPIO_1              */
    uint16_t :2;                        /**< bit:   6..7  Reserved */
    uint16_t AO_GPIO_2_SEL:2;           /**< bit:   8..9  Pinmux select for AO_GPIO_2              */
    uint16_t :6;                        /**< bit: 10..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} AON_GP_REGS_AON_PINMUX_SEL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_GP_REGS_AON_PINMUX_SEL_OFFSET   0x00                                          /**<  (AON_GP_REGS_AON_PINMUX_SEL) Controls the pinmux selection for the AO GPIOs  Offset */
#define AON_GP_REGS_AON_PINMUX_SEL_RESETVALUE 0x01u                                         /**<  (AON_GP_REGS_AON_PINMUX_SEL) Controls the pinmux selection for the AO GPIOs  Reset Value */

#define AON_GP_REGS_AON_PINMUX_SEL_AO_GPIO_0_SEL_Pos 0                                              /**< (AON_GP_REGS_AON_PINMUX_SEL) Pinmux select for AO_GPIO_0 Position */
#define AON_GP_REGS_AON_PINMUX_SEL_AO_GPIO_0_SEL_Msk (0x3u << AON_GP_REGS_AON_PINMUX_SEL_AO_GPIO_0_SEL_Pos)  /**< (AON_GP_REGS_AON_PINMUX_SEL) Pinmux select for AO_GPIO_0 Mask */
#define AON_GP_REGS_AON_PINMUX_SEL_AO_GPIO_0_SEL(value) (AON_GP_REGS_AON_PINMUX_SEL_AO_GPIO_0_SEL_Msk & ((value) << AON_GP_REGS_AON_PINMUX_SEL_AO_GPIO_0_SEL_Pos))
#define AON_GP_REGS_AON_PINMUX_SEL_AO_GPIO_1_SEL_Pos 4                                              /**< (AON_GP_REGS_AON_PINMUX_SEL) Pinmux select for AO_GPIO_1 Position */
#define AON_GP_REGS_AON_PINMUX_SEL_AO_GPIO_1_SEL_Msk (0x3u << AON_GP_REGS_AON_PINMUX_SEL_AO_GPIO_1_SEL_Pos)  /**< (AON_GP_REGS_AON_PINMUX_SEL) Pinmux select for AO_GPIO_1 Mask */
#define AON_GP_REGS_AON_PINMUX_SEL_AO_GPIO_1_SEL(value) (AON_GP_REGS_AON_PINMUX_SEL_AO_GPIO_1_SEL_Msk & ((value) << AON_GP_REGS_AON_PINMUX_SEL_AO_GPIO_1_SEL_Pos))
#define AON_GP_REGS_AON_PINMUX_SEL_AO_GPIO_2_SEL_Pos 8                                              /**< (AON_GP_REGS_AON_PINMUX_SEL) Pinmux select for AO_GPIO_2 Position */
#define AON_GP_REGS_AON_PINMUX_SEL_AO_GPIO_2_SEL_Msk (0x3u << AON_GP_REGS_AON_PINMUX_SEL_AO_GPIO_2_SEL_Pos)  /**< (AON_GP_REGS_AON_PINMUX_SEL) Pinmux select for AO_GPIO_2 Mask */
#define AON_GP_REGS_AON_PINMUX_SEL_AO_GPIO_2_SEL(value) (AON_GP_REGS_AON_PINMUX_SEL_AO_GPIO_2_SEL_Msk & ((value) << AON_GP_REGS_AON_PINMUX_SEL_AO_GPIO_2_SEL_Pos))
#define AON_GP_REGS_AON_PINMUX_SEL_MASK     0x333u                                         /**< \deprecated (AON_GP_REGS_AON_PINMUX_SEL) Register MASK  (Use AON_GP_REGS_AON_PINMUX_SEL_Msk instead)  */
#define AON_GP_REGS_AON_PINMUX_SEL_Msk      0x333u                                         /**< (AON_GP_REGS_AON_PINMUX_SEL) Register Mask  */

/* -------- AON_GP_REGS_AON_PMU_CTRL : (AON_GP_REGS Offset: 0x04) (R/W 32) Always On Misc Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t PMU_REGS_4TO1_SEL:1;       /**< bit:      0  If 1 then uses the frequency hopping table otherwise registers in PD0 */
    uint32_t PMU_RTC_CLK_EN:1;          /**< bit:      1  Enables the PMU RTC clock                */
    uint32_t :2;                        /**< bit:   2..3  Reserved */
    uint32_t PMU_RETN_VAL_SEL:2;        /**< bit:   4..5  Retention Voltage Selection              */
    uint32_t :1;                        /**< bit:      6  Reserved */
    uint32_t EFUSE_LDO_EN:1;            /**< bit:      7  Enables the EFUSE LDO                    */
    uint32_t PMU_MUX_EN:1;              /**< bit:      8  PMU MUX EN                               */
    uint32_t PMU_MUX_A:3;               /**< bit:  9..11  PMU MUX A                                */
    uint32_t PMU_MUX_SEL:4;             /**< bit: 12..15  PMU MUX SEL                              */
    uint32_t PMU_SENS_ADC_EN:1;         /**< bit:     16  PMU Sensor ADC Enable                    */
    uint32_t PMU_SENS_ADC_RST:1;        /**< bit:     17  PMU Sensor ADC Reset                     */
    uint32_t PMU_BGR_EN:1;              /**< bit:     18  PMU BGR EN                               */
    uint32_t PMU_2MHZ_CLK_EN:1;         /**< bit:     19  Enables the 2MHz OSC clock coming to the digital from the PMU */
    uint32_t PMU_26MHZ_CLK_FORCE_OFF:1;  /**< bit:     20  If set, this will force off the OSC 26 MHz clock, otherwise this will follow the power for PD1 */
    uint32_t :11;                       /**< bit: 21..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} AON_GP_REGS_AON_PMU_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_GP_REGS_AON_PMU_CTRL_OFFSET     0x04                                          /**<  (AON_GP_REGS_AON_PMU_CTRL) Always On Misc Control  Offset */
#define AON_GP_REGS_AON_PMU_CTRL_RESETVALUE 0xA0022u                                      /**<  (AON_GP_REGS_AON_PMU_CTRL) Always On Misc Control  Reset Value */

#define AON_GP_REGS_AON_PMU_CTRL_PMU_REGS_4TO1_SEL_Pos 0                                              /**< (AON_GP_REGS_AON_PMU_CTRL) If 1 then uses the frequency hopping table otherwise registers in PD0 Position */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_REGS_4TO1_SEL_Msk (0x1u << AON_GP_REGS_AON_PMU_CTRL_PMU_REGS_4TO1_SEL_Pos)  /**< (AON_GP_REGS_AON_PMU_CTRL) If 1 then uses the frequency hopping table otherwise registers in PD0 Mask */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_REGS_4TO1_SEL AON_GP_REGS_AON_PMU_CTRL_PMU_REGS_4TO1_SEL_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_PMU_CTRL_PMU_REGS_4TO1_SEL_Msk instead */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_RTC_CLK_EN_Pos 1                                              /**< (AON_GP_REGS_AON_PMU_CTRL) Enables the PMU RTC clock Position */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_RTC_CLK_EN_Msk (0x1u << AON_GP_REGS_AON_PMU_CTRL_PMU_RTC_CLK_EN_Pos)  /**< (AON_GP_REGS_AON_PMU_CTRL) Enables the PMU RTC clock Mask */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_RTC_CLK_EN AON_GP_REGS_AON_PMU_CTRL_PMU_RTC_CLK_EN_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_PMU_CTRL_PMU_RTC_CLK_EN_Msk instead */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_RETN_VAL_SEL_Pos 4                                              /**< (AON_GP_REGS_AON_PMU_CTRL) Retention Voltage Selection Position */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_RETN_VAL_SEL_Msk (0x3u << AON_GP_REGS_AON_PMU_CTRL_PMU_RETN_VAL_SEL_Pos)  /**< (AON_GP_REGS_AON_PMU_CTRL) Retention Voltage Selection Mask */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_RETN_VAL_SEL(value) (AON_GP_REGS_AON_PMU_CTRL_PMU_RETN_VAL_SEL_Msk & ((value) << AON_GP_REGS_AON_PMU_CTRL_PMU_RETN_VAL_SEL_Pos))
#define AON_GP_REGS_AON_PMU_CTRL_EFUSE_LDO_EN_Pos 7                                              /**< (AON_GP_REGS_AON_PMU_CTRL) Enables the EFUSE LDO Position */
#define AON_GP_REGS_AON_PMU_CTRL_EFUSE_LDO_EN_Msk (0x1u << AON_GP_REGS_AON_PMU_CTRL_EFUSE_LDO_EN_Pos)  /**< (AON_GP_REGS_AON_PMU_CTRL) Enables the EFUSE LDO Mask */
#define AON_GP_REGS_AON_PMU_CTRL_EFUSE_LDO_EN AON_GP_REGS_AON_PMU_CTRL_EFUSE_LDO_EN_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_PMU_CTRL_EFUSE_LDO_EN_Msk instead */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_MUX_EN_Pos 8                                              /**< (AON_GP_REGS_AON_PMU_CTRL) PMU MUX EN Position */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_MUX_EN_Msk (0x1u << AON_GP_REGS_AON_PMU_CTRL_PMU_MUX_EN_Pos)  /**< (AON_GP_REGS_AON_PMU_CTRL) PMU MUX EN Mask */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_MUX_EN AON_GP_REGS_AON_PMU_CTRL_PMU_MUX_EN_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_PMU_CTRL_PMU_MUX_EN_Msk instead */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_MUX_A_Pos 9                                              /**< (AON_GP_REGS_AON_PMU_CTRL) PMU MUX A Position */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_MUX_A_Msk (0x7u << AON_GP_REGS_AON_PMU_CTRL_PMU_MUX_A_Pos)  /**< (AON_GP_REGS_AON_PMU_CTRL) PMU MUX A Mask */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_MUX_A(value) (AON_GP_REGS_AON_PMU_CTRL_PMU_MUX_A_Msk & ((value) << AON_GP_REGS_AON_PMU_CTRL_PMU_MUX_A_Pos))
#define AON_GP_REGS_AON_PMU_CTRL_PMU_MUX_SEL_Pos 12                                             /**< (AON_GP_REGS_AON_PMU_CTRL) PMU MUX SEL Position */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_MUX_SEL_Msk (0xFu << AON_GP_REGS_AON_PMU_CTRL_PMU_MUX_SEL_Pos)  /**< (AON_GP_REGS_AON_PMU_CTRL) PMU MUX SEL Mask */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_MUX_SEL(value) (AON_GP_REGS_AON_PMU_CTRL_PMU_MUX_SEL_Msk & ((value) << AON_GP_REGS_AON_PMU_CTRL_PMU_MUX_SEL_Pos))
#define AON_GP_REGS_AON_PMU_CTRL_PMU_SENS_ADC_EN_Pos 16                                             /**< (AON_GP_REGS_AON_PMU_CTRL) PMU Sensor ADC Enable Position */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_SENS_ADC_EN_Msk (0x1u << AON_GP_REGS_AON_PMU_CTRL_PMU_SENS_ADC_EN_Pos)  /**< (AON_GP_REGS_AON_PMU_CTRL) PMU Sensor ADC Enable Mask */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_SENS_ADC_EN AON_GP_REGS_AON_PMU_CTRL_PMU_SENS_ADC_EN_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_PMU_CTRL_PMU_SENS_ADC_EN_Msk instead */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_SENS_ADC_RST_Pos 17                                             /**< (AON_GP_REGS_AON_PMU_CTRL) PMU Sensor ADC Reset Position */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_SENS_ADC_RST_Msk (0x1u << AON_GP_REGS_AON_PMU_CTRL_PMU_SENS_ADC_RST_Pos)  /**< (AON_GP_REGS_AON_PMU_CTRL) PMU Sensor ADC Reset Mask */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_SENS_ADC_RST AON_GP_REGS_AON_PMU_CTRL_PMU_SENS_ADC_RST_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_PMU_CTRL_PMU_SENS_ADC_RST_Msk instead */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_BGR_EN_Pos 18                                             /**< (AON_GP_REGS_AON_PMU_CTRL) PMU BGR EN Position */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_BGR_EN_Msk (0x1u << AON_GP_REGS_AON_PMU_CTRL_PMU_BGR_EN_Pos)  /**< (AON_GP_REGS_AON_PMU_CTRL) PMU BGR EN Mask */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_BGR_EN AON_GP_REGS_AON_PMU_CTRL_PMU_BGR_EN_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_PMU_CTRL_PMU_BGR_EN_Msk instead */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_2MHZ_CLK_EN_Pos 19                                             /**< (AON_GP_REGS_AON_PMU_CTRL) Enables the 2MHz OSC clock coming to the digital from the PMU Position */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_2MHZ_CLK_EN_Msk (0x1u << AON_GP_REGS_AON_PMU_CTRL_PMU_2MHZ_CLK_EN_Pos)  /**< (AON_GP_REGS_AON_PMU_CTRL) Enables the 2MHz OSC clock coming to the digital from the PMU Mask */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_2MHZ_CLK_EN AON_GP_REGS_AON_PMU_CTRL_PMU_2MHZ_CLK_EN_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_PMU_CTRL_PMU_2MHZ_CLK_EN_Msk instead */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_26MHZ_CLK_FORCE_OFF_Pos 20                                             /**< (AON_GP_REGS_AON_PMU_CTRL) If set, this will force off the OSC 26 MHz clock, otherwise this will follow the power for PD1 Position */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_26MHZ_CLK_FORCE_OFF_Msk (0x1u << AON_GP_REGS_AON_PMU_CTRL_PMU_26MHZ_CLK_FORCE_OFF_Pos)  /**< (AON_GP_REGS_AON_PMU_CTRL) If set, this will force off the OSC 26 MHz clock, otherwise this will follow the power for PD1 Mask */
#define AON_GP_REGS_AON_PMU_CTRL_PMU_26MHZ_CLK_FORCE_OFF AON_GP_REGS_AON_PMU_CTRL_PMU_26MHZ_CLK_FORCE_OFF_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_PMU_CTRL_PMU_26MHZ_CLK_FORCE_OFF_Msk instead */
#define AON_GP_REGS_AON_PMU_CTRL_MASK       0x1FFFB3u                                      /**< \deprecated (AON_GP_REGS_AON_PMU_CTRL) Register MASK  (Use AON_GP_REGS_AON_PMU_CTRL_Msk instead)  */
#define AON_GP_REGS_AON_PMU_CTRL_Msk        0x1FFFB3u                                      /**< (AON_GP_REGS_AON_PMU_CTRL) Register Mask  */

/* -------- AON_GP_REGS_AON_BLE_LP_CTRL : (AON_GP_REGS Offset: 0x08) (R/W 8) Always On BLE LP Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  WAKEUP_LP_LATCH:1;         /**< bit:      0  If set, this will latch the wakeup signal in the BLE LP block */
    uint8_t  DEEP_SLEEP_STAT_SYNC_EN:1;  /**< bit:      1  If set, this will use the sync flops for deep sleep stat */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} AON_GP_REGS_AON_BLE_LP_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_GP_REGS_AON_BLE_LP_CTRL_OFFSET  0x08                                          /**<  (AON_GP_REGS_AON_BLE_LP_CTRL) Always On BLE LP Control  Offset */
#define AON_GP_REGS_AON_BLE_LP_CTRL_RESETVALUE 0x00u                                         /**<  (AON_GP_REGS_AON_BLE_LP_CTRL) Always On BLE LP Control  Reset Value */

#define AON_GP_REGS_AON_BLE_LP_CTRL_WAKEUP_LP_LATCH_Pos 0                                              /**< (AON_GP_REGS_AON_BLE_LP_CTRL) If set, this will latch the wakeup signal in the BLE LP block Position */
#define AON_GP_REGS_AON_BLE_LP_CTRL_WAKEUP_LP_LATCH_Msk (0x1u << AON_GP_REGS_AON_BLE_LP_CTRL_WAKEUP_LP_LATCH_Pos)  /**< (AON_GP_REGS_AON_BLE_LP_CTRL) If set, this will latch the wakeup signal in the BLE LP block Mask */
#define AON_GP_REGS_AON_BLE_LP_CTRL_WAKEUP_LP_LATCH AON_GP_REGS_AON_BLE_LP_CTRL_WAKEUP_LP_LATCH_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_BLE_LP_CTRL_WAKEUP_LP_LATCH_Msk instead */
#define AON_GP_REGS_AON_BLE_LP_CTRL_DEEP_SLEEP_STAT_SYNC_EN_Pos 1                                              /**< (AON_GP_REGS_AON_BLE_LP_CTRL) If set, this will use the sync flops for deep sleep stat Position */
#define AON_GP_REGS_AON_BLE_LP_CTRL_DEEP_SLEEP_STAT_SYNC_EN_Msk (0x1u << AON_GP_REGS_AON_BLE_LP_CTRL_DEEP_SLEEP_STAT_SYNC_EN_Pos)  /**< (AON_GP_REGS_AON_BLE_LP_CTRL) If set, this will use the sync flops for deep sleep stat Mask */
#define AON_GP_REGS_AON_BLE_LP_CTRL_DEEP_SLEEP_STAT_SYNC_EN AON_GP_REGS_AON_BLE_LP_CTRL_DEEP_SLEEP_STAT_SYNC_EN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_BLE_LP_CTRL_DEEP_SLEEP_STAT_SYNC_EN_Msk instead */
#define AON_GP_REGS_AON_BLE_LP_CTRL_MASK    0x03u                                          /**< \deprecated (AON_GP_REGS_AON_BLE_LP_CTRL) Register MASK  (Use AON_GP_REGS_AON_BLE_LP_CTRL_Msk instead)  */
#define AON_GP_REGS_AON_BLE_LP_CTRL_Msk     0x03u                                          /**< (AON_GP_REGS_AON_BLE_LP_CTRL) Register Mask  */

/* -------- AON_GP_REGS_AON_MISC_CTRL : (AON_GP_REGS Offset: 0x0c) (R/W 32) Always On Misc Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :1;                        /**< bit:      0  Reserved */
    uint32_t USE_RTC_32KHZ_CLK_SLEEP_TIMER:1;  /**< bit:      1  If set, this will use the RTC version of the 32khz clock for the sleep timer */
    uint32_t USE_EXT_32KHZ_CLK_SLEEP_TIMER:1;  /**< bit:      2  If set, this will use an external RTC for the 32khz clock for the sleep timer */
    uint32_t LPMCU_BOOT_RESET_MUXSEL:1;  /**< bit:      3  If 1, then it uses the CPU register bit, otherwise LP_BOOT_PIN is connected */
    uint32_t LPMCU_USE_BOOT_REGS:1;     /**< bit:      4  If 1, then the ARM will use the boot regs instead of the boot rom for the first 4 boot addresses (0x0 - 0xF) */
    uint32_t LPMCU_CPU_RESET_OVERRIDE_EN:1;  /**< bit:      5  If 1, then it will use the PD0 register value for LPMCU CPU RESET (higher priority than lpmcu_boot_reset_muxsel) */
    uint32_t LPMCU_CPU_RESET_OVERRIDE_VAL:1;  /**< bit:      6  If lpmcu_cpu_reset_override_en is set then this value will be used for the LPMCU CPU RESET */
    uint32_t :7;                        /**< bit:  7..13  Reserved */
    uint32_t USE_2M_AON_PWR_SEQ_CLK:1;  /**< bit:     14  If set, this will use either the osc 2M or rtc 32kHz clock for the AON power sequencer.  The field use_rtc_aon_pwr_seq_clk determines which. */
    uint32_t USE_OSC2M_AS_TB_CLK:1;     /**< bit:     15  If set, this will use the osc 2M clock as the PD0 testbus clock */
    uint32_t AON_SLEEP_TIMER_CLK_EN:1;  /**< bit:     16  If set, this will enable the 32khz clock to the AON Sleep Timer */
    uint32_t AON_EXT_32KHZ_OUT_EN:1;    /**< bit:     17  If set, this will enable the 32khz clock to the AON pads as an output of the chip */
    uint32_t USE_RTC_AON_PWR_SEQ_CLK:1;  /**< bit:     18  If set, this will use the RTC clock as the AON power sequencer clock once use_2m_aon_pwr_seq_clk is also set.  This must be set first. */
    uint32_t INVERT_WAKEUP_GPIO_0:1;    /**< bit:     19  If set, this will invert the wakeup gpio_0 */
    uint32_t FORCE_OFF_XO:1;            /**< bit:     20  If set, this will force off the XO, otherwise XO is always on if BLE core is powered on. */
    uint32_t FORCE_XO_TO_BYPASS_MODE:1;  /**< bit:     21  If set, this will force the XO into bypass mode. */
    uint32_t :10;                       /**< bit: 22..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} AON_GP_REGS_AON_MISC_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_GP_REGS_AON_MISC_CTRL_OFFSET    0x0C                                          /**<  (AON_GP_REGS_AON_MISC_CTRL) Always On Misc Control  Offset */
#define AON_GP_REGS_AON_MISC_CTRL_RESETVALUE 0x10000u                                      /**<  (AON_GP_REGS_AON_MISC_CTRL) Always On Misc Control  Reset Value */

#define AON_GP_REGS_AON_MISC_CTRL_USE_RTC_32KHZ_CLK_SLEEP_TIMER_Pos 1                                              /**< (AON_GP_REGS_AON_MISC_CTRL) If set, this will use the RTC version of the 32khz clock for the sleep timer Position */
#define AON_GP_REGS_AON_MISC_CTRL_USE_RTC_32KHZ_CLK_SLEEP_TIMER_Msk (0x1u << AON_GP_REGS_AON_MISC_CTRL_USE_RTC_32KHZ_CLK_SLEEP_TIMER_Pos)  /**< (AON_GP_REGS_AON_MISC_CTRL) If set, this will use the RTC version of the 32khz clock for the sleep timer Mask */
#define AON_GP_REGS_AON_MISC_CTRL_USE_RTC_32KHZ_CLK_SLEEP_TIMER AON_GP_REGS_AON_MISC_CTRL_USE_RTC_32KHZ_CLK_SLEEP_TIMER_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_MISC_CTRL_USE_RTC_32KHZ_CLK_SLEEP_TIMER_Msk instead */
#define AON_GP_REGS_AON_MISC_CTRL_USE_EXT_32KHZ_CLK_SLEEP_TIMER_Pos 2                                              /**< (AON_GP_REGS_AON_MISC_CTRL) If set, this will use an external RTC for the 32khz clock for the sleep timer Position */
#define AON_GP_REGS_AON_MISC_CTRL_USE_EXT_32KHZ_CLK_SLEEP_TIMER_Msk (0x1u << AON_GP_REGS_AON_MISC_CTRL_USE_EXT_32KHZ_CLK_SLEEP_TIMER_Pos)  /**< (AON_GP_REGS_AON_MISC_CTRL) If set, this will use an external RTC for the 32khz clock for the sleep timer Mask */
#define AON_GP_REGS_AON_MISC_CTRL_USE_EXT_32KHZ_CLK_SLEEP_TIMER AON_GP_REGS_AON_MISC_CTRL_USE_EXT_32KHZ_CLK_SLEEP_TIMER_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_MISC_CTRL_USE_EXT_32KHZ_CLK_SLEEP_TIMER_Msk instead */
#define AON_GP_REGS_AON_MISC_CTRL_LPMCU_BOOT_RESET_MUXSEL_Pos 3                                              /**< (AON_GP_REGS_AON_MISC_CTRL) If 1, then it uses the CPU register bit, otherwise LP_BOOT_PIN is connected Position */
#define AON_GP_REGS_AON_MISC_CTRL_LPMCU_BOOT_RESET_MUXSEL_Msk (0x1u << AON_GP_REGS_AON_MISC_CTRL_LPMCU_BOOT_RESET_MUXSEL_Pos)  /**< (AON_GP_REGS_AON_MISC_CTRL) If 1, then it uses the CPU register bit, otherwise LP_BOOT_PIN is connected Mask */
#define AON_GP_REGS_AON_MISC_CTRL_LPMCU_BOOT_RESET_MUXSEL AON_GP_REGS_AON_MISC_CTRL_LPMCU_BOOT_RESET_MUXSEL_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_MISC_CTRL_LPMCU_BOOT_RESET_MUXSEL_Msk instead */
#define AON_GP_REGS_AON_MISC_CTRL_LPMCU_USE_BOOT_REGS_Pos 4                                              /**< (AON_GP_REGS_AON_MISC_CTRL) If 1, then the ARM will use the boot regs instead of the boot rom for the first 4 boot addresses (0x0 - 0xF) Position */
#define AON_GP_REGS_AON_MISC_CTRL_LPMCU_USE_BOOT_REGS_Msk (0x1u << AON_GP_REGS_AON_MISC_CTRL_LPMCU_USE_BOOT_REGS_Pos)  /**< (AON_GP_REGS_AON_MISC_CTRL) If 1, then the ARM will use the boot regs instead of the boot rom for the first 4 boot addresses (0x0 - 0xF) Mask */
#define AON_GP_REGS_AON_MISC_CTRL_LPMCU_USE_BOOT_REGS AON_GP_REGS_AON_MISC_CTRL_LPMCU_USE_BOOT_REGS_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_MISC_CTRL_LPMCU_USE_BOOT_REGS_Msk instead */
#define AON_GP_REGS_AON_MISC_CTRL_LPMCU_CPU_RESET_OVERRIDE_EN_Pos 5                                              /**< (AON_GP_REGS_AON_MISC_CTRL) If 1, then it will use the PD0 register value for LPMCU CPU RESET (higher priority than lpmcu_boot_reset_muxsel) Position */
#define AON_GP_REGS_AON_MISC_CTRL_LPMCU_CPU_RESET_OVERRIDE_EN_Msk (0x1u << AON_GP_REGS_AON_MISC_CTRL_LPMCU_CPU_RESET_OVERRIDE_EN_Pos)  /**< (AON_GP_REGS_AON_MISC_CTRL) If 1, then it will use the PD0 register value for LPMCU CPU RESET (higher priority than lpmcu_boot_reset_muxsel) Mask */
#define AON_GP_REGS_AON_MISC_CTRL_LPMCU_CPU_RESET_OVERRIDE_EN AON_GP_REGS_AON_MISC_CTRL_LPMCU_CPU_RESET_OVERRIDE_EN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_MISC_CTRL_LPMCU_CPU_RESET_OVERRIDE_EN_Msk instead */
#define AON_GP_REGS_AON_MISC_CTRL_LPMCU_CPU_RESET_OVERRIDE_VAL_Pos 6                                              /**< (AON_GP_REGS_AON_MISC_CTRL) If lpmcu_cpu_reset_override_en is set then this value will be used for the LPMCU CPU RESET Position */
#define AON_GP_REGS_AON_MISC_CTRL_LPMCU_CPU_RESET_OVERRIDE_VAL_Msk (0x1u << AON_GP_REGS_AON_MISC_CTRL_LPMCU_CPU_RESET_OVERRIDE_VAL_Pos)  /**< (AON_GP_REGS_AON_MISC_CTRL) If lpmcu_cpu_reset_override_en is set then this value will be used for the LPMCU CPU RESET Mask */
#define AON_GP_REGS_AON_MISC_CTRL_LPMCU_CPU_RESET_OVERRIDE_VAL AON_GP_REGS_AON_MISC_CTRL_LPMCU_CPU_RESET_OVERRIDE_VAL_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_MISC_CTRL_LPMCU_CPU_RESET_OVERRIDE_VAL_Msk instead */
#define AON_GP_REGS_AON_MISC_CTRL_USE_2M_AON_PWR_SEQ_CLK_Pos 14                                             /**< (AON_GP_REGS_AON_MISC_CTRL) If set, this will use either the osc 2M or rtc 32kHz clock for the AON power sequencer.  The field use_rtc_aon_pwr_seq_clk determines which. Position */
#define AON_GP_REGS_AON_MISC_CTRL_USE_2M_AON_PWR_SEQ_CLK_Msk (0x1u << AON_GP_REGS_AON_MISC_CTRL_USE_2M_AON_PWR_SEQ_CLK_Pos)  /**< (AON_GP_REGS_AON_MISC_CTRL) If set, this will use either the osc 2M or rtc 32kHz clock for the AON power sequencer.  The field use_rtc_aon_pwr_seq_clk determines which. Mask */
#define AON_GP_REGS_AON_MISC_CTRL_USE_2M_AON_PWR_SEQ_CLK AON_GP_REGS_AON_MISC_CTRL_USE_2M_AON_PWR_SEQ_CLK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_MISC_CTRL_USE_2M_AON_PWR_SEQ_CLK_Msk instead */
#define AON_GP_REGS_AON_MISC_CTRL_USE_OSC2M_AS_TB_CLK_Pos 15                                             /**< (AON_GP_REGS_AON_MISC_CTRL) If set, this will use the osc 2M clock as the PD0 testbus clock Position */
#define AON_GP_REGS_AON_MISC_CTRL_USE_OSC2M_AS_TB_CLK_Msk (0x1u << AON_GP_REGS_AON_MISC_CTRL_USE_OSC2M_AS_TB_CLK_Pos)  /**< (AON_GP_REGS_AON_MISC_CTRL) If set, this will use the osc 2M clock as the PD0 testbus clock Mask */
#define AON_GP_REGS_AON_MISC_CTRL_USE_OSC2M_AS_TB_CLK AON_GP_REGS_AON_MISC_CTRL_USE_OSC2M_AS_TB_CLK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_MISC_CTRL_USE_OSC2M_AS_TB_CLK_Msk instead */
#define AON_GP_REGS_AON_MISC_CTRL_AON_SLEEP_TIMER_CLK_EN_Pos 16                                             /**< (AON_GP_REGS_AON_MISC_CTRL) If set, this will enable the 32khz clock to the AON Sleep Timer Position */
#define AON_GP_REGS_AON_MISC_CTRL_AON_SLEEP_TIMER_CLK_EN_Msk (0x1u << AON_GP_REGS_AON_MISC_CTRL_AON_SLEEP_TIMER_CLK_EN_Pos)  /**< (AON_GP_REGS_AON_MISC_CTRL) If set, this will enable the 32khz clock to the AON Sleep Timer Mask */
#define AON_GP_REGS_AON_MISC_CTRL_AON_SLEEP_TIMER_CLK_EN AON_GP_REGS_AON_MISC_CTRL_AON_SLEEP_TIMER_CLK_EN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_MISC_CTRL_AON_SLEEP_TIMER_CLK_EN_Msk instead */
#define AON_GP_REGS_AON_MISC_CTRL_AON_EXT_32KHZ_OUT_EN_Pos 17                                             /**< (AON_GP_REGS_AON_MISC_CTRL) If set, this will enable the 32khz clock to the AON pads as an output of the chip Position */
#define AON_GP_REGS_AON_MISC_CTRL_AON_EXT_32KHZ_OUT_EN_Msk (0x1u << AON_GP_REGS_AON_MISC_CTRL_AON_EXT_32KHZ_OUT_EN_Pos)  /**< (AON_GP_REGS_AON_MISC_CTRL) If set, this will enable the 32khz clock to the AON pads as an output of the chip Mask */
#define AON_GP_REGS_AON_MISC_CTRL_AON_EXT_32KHZ_OUT_EN AON_GP_REGS_AON_MISC_CTRL_AON_EXT_32KHZ_OUT_EN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_MISC_CTRL_AON_EXT_32KHZ_OUT_EN_Msk instead */
#define AON_GP_REGS_AON_MISC_CTRL_USE_RTC_AON_PWR_SEQ_CLK_Pos 18                                             /**< (AON_GP_REGS_AON_MISC_CTRL) If set, this will use the RTC clock as the AON power sequencer clock once use_2m_aon_pwr_seq_clk is also set.  This must be set first. Position */
#define AON_GP_REGS_AON_MISC_CTRL_USE_RTC_AON_PWR_SEQ_CLK_Msk (0x1u << AON_GP_REGS_AON_MISC_CTRL_USE_RTC_AON_PWR_SEQ_CLK_Pos)  /**< (AON_GP_REGS_AON_MISC_CTRL) If set, this will use the RTC clock as the AON power sequencer clock once use_2m_aon_pwr_seq_clk is also set.  This must be set first. Mask */
#define AON_GP_REGS_AON_MISC_CTRL_USE_RTC_AON_PWR_SEQ_CLK AON_GP_REGS_AON_MISC_CTRL_USE_RTC_AON_PWR_SEQ_CLK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_MISC_CTRL_USE_RTC_AON_PWR_SEQ_CLK_Msk instead */
#define AON_GP_REGS_AON_MISC_CTRL_INVERT_WAKEUP_GPIO_0_Pos 19                                             /**< (AON_GP_REGS_AON_MISC_CTRL) If set, this will invert the wakeup gpio_0 Position */
#define AON_GP_REGS_AON_MISC_CTRL_INVERT_WAKEUP_GPIO_0_Msk (0x1u << AON_GP_REGS_AON_MISC_CTRL_INVERT_WAKEUP_GPIO_0_Pos)  /**< (AON_GP_REGS_AON_MISC_CTRL) If set, this will invert the wakeup gpio_0 Mask */
#define AON_GP_REGS_AON_MISC_CTRL_INVERT_WAKEUP_GPIO_0 AON_GP_REGS_AON_MISC_CTRL_INVERT_WAKEUP_GPIO_0_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_MISC_CTRL_INVERT_WAKEUP_GPIO_0_Msk instead */
#define AON_GP_REGS_AON_MISC_CTRL_FORCE_OFF_XO_Pos 20                                             /**< (AON_GP_REGS_AON_MISC_CTRL) If set, this will force off the XO, otherwise XO is always on if BLE core is powered on. Position */
#define AON_GP_REGS_AON_MISC_CTRL_FORCE_OFF_XO_Msk (0x1u << AON_GP_REGS_AON_MISC_CTRL_FORCE_OFF_XO_Pos)  /**< (AON_GP_REGS_AON_MISC_CTRL) If set, this will force off the XO, otherwise XO is always on if BLE core is powered on. Mask */
#define AON_GP_REGS_AON_MISC_CTRL_FORCE_OFF_XO AON_GP_REGS_AON_MISC_CTRL_FORCE_OFF_XO_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_MISC_CTRL_FORCE_OFF_XO_Msk instead */
#define AON_GP_REGS_AON_MISC_CTRL_FORCE_XO_TO_BYPASS_MODE_Pos 21                                             /**< (AON_GP_REGS_AON_MISC_CTRL) If set, this will force the XO into bypass mode. Position */
#define AON_GP_REGS_AON_MISC_CTRL_FORCE_XO_TO_BYPASS_MODE_Msk (0x1u << AON_GP_REGS_AON_MISC_CTRL_FORCE_XO_TO_BYPASS_MODE_Pos)  /**< (AON_GP_REGS_AON_MISC_CTRL) If set, this will force the XO into bypass mode. Mask */
#define AON_GP_REGS_AON_MISC_CTRL_FORCE_XO_TO_BYPASS_MODE AON_GP_REGS_AON_MISC_CTRL_FORCE_XO_TO_BYPASS_MODE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_MISC_CTRL_FORCE_XO_TO_BYPASS_MODE_Msk instead */
#define AON_GP_REGS_AON_MISC_CTRL_MASK      0x3FC07Eu                                      /**< \deprecated (AON_GP_REGS_AON_MISC_CTRL) Register MASK  (Use AON_GP_REGS_AON_MISC_CTRL_Msk instead)  */
#define AON_GP_REGS_AON_MISC_CTRL_Msk       0x3FC07Eu                                      /**< (AON_GP_REGS_AON_MISC_CTRL) Register Mask  */

/* -------- AON_GP_REGS_AON_GLOBAL_RESET : (AON_GP_REGS Offset: 0x10) (R/W 8) Active Low Always On Reset Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  GLOBAL_RSTN:1;             /**< bit:      0  Global Reset                             */
    uint8_t  SLEEP_TIMER_RSTN:1;        /**< bit:      1  Sleep Timer Reset                        */
    uint8_t  :1;                        /**< bit:      2  Reserved */
    uint8_t  BLE_LP_RSTN:1;             /**< bit:      3  BLE Low Power Reset                      */
    uint8_t  PD4_RSTN:1;                /**< bit:      4  Allow the SW to force PD4 into reset     */
    uint8_t  :3;                        /**< bit:   5..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} AON_GP_REGS_AON_GLOBAL_RESET_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_GP_REGS_AON_GLOBAL_RESET_OFFSET 0x10                                          /**<  (AON_GP_REGS_AON_GLOBAL_RESET) Active Low Always On Reset Control  Offset */
#define AON_GP_REGS_AON_GLOBAL_RESET_RESETVALUE 0x1Bu                                         /**<  (AON_GP_REGS_AON_GLOBAL_RESET) Active Low Always On Reset Control  Reset Value */

#define AON_GP_REGS_AON_GLOBAL_RESET_GLOBAL_RSTN_Pos 0                                              /**< (AON_GP_REGS_AON_GLOBAL_RESET) Global Reset Position */
#define AON_GP_REGS_AON_GLOBAL_RESET_GLOBAL_RSTN_Msk (0x1u << AON_GP_REGS_AON_GLOBAL_RESET_GLOBAL_RSTN_Pos)  /**< (AON_GP_REGS_AON_GLOBAL_RESET) Global Reset Mask */
#define AON_GP_REGS_AON_GLOBAL_RESET_GLOBAL_RSTN AON_GP_REGS_AON_GLOBAL_RESET_GLOBAL_RSTN_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_GLOBAL_RESET_GLOBAL_RSTN_Msk instead */
#define AON_GP_REGS_AON_GLOBAL_RESET_SLEEP_TIMER_RSTN_Pos 1                                              /**< (AON_GP_REGS_AON_GLOBAL_RESET) Sleep Timer Reset Position */
#define AON_GP_REGS_AON_GLOBAL_RESET_SLEEP_TIMER_RSTN_Msk (0x1u << AON_GP_REGS_AON_GLOBAL_RESET_SLEEP_TIMER_RSTN_Pos)  /**< (AON_GP_REGS_AON_GLOBAL_RESET) Sleep Timer Reset Mask */
#define AON_GP_REGS_AON_GLOBAL_RESET_SLEEP_TIMER_RSTN AON_GP_REGS_AON_GLOBAL_RESET_SLEEP_TIMER_RSTN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_GLOBAL_RESET_SLEEP_TIMER_RSTN_Msk instead */
#define AON_GP_REGS_AON_GLOBAL_RESET_BLE_LP_RSTN_Pos 3                                              /**< (AON_GP_REGS_AON_GLOBAL_RESET) BLE Low Power Reset Position */
#define AON_GP_REGS_AON_GLOBAL_RESET_BLE_LP_RSTN_Msk (0x1u << AON_GP_REGS_AON_GLOBAL_RESET_BLE_LP_RSTN_Pos)  /**< (AON_GP_REGS_AON_GLOBAL_RESET) BLE Low Power Reset Mask */
#define AON_GP_REGS_AON_GLOBAL_RESET_BLE_LP_RSTN AON_GP_REGS_AON_GLOBAL_RESET_BLE_LP_RSTN_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_GLOBAL_RESET_BLE_LP_RSTN_Msk instead */
#define AON_GP_REGS_AON_GLOBAL_RESET_PD4_RSTN_Pos 4                                              /**< (AON_GP_REGS_AON_GLOBAL_RESET) Allow the SW to force PD4 into reset Position */
#define AON_GP_REGS_AON_GLOBAL_RESET_PD4_RSTN_Msk (0x1u << AON_GP_REGS_AON_GLOBAL_RESET_PD4_RSTN_Pos)  /**< (AON_GP_REGS_AON_GLOBAL_RESET) Allow the SW to force PD4 into reset Mask */
#define AON_GP_REGS_AON_GLOBAL_RESET_PD4_RSTN AON_GP_REGS_AON_GLOBAL_RESET_PD4_RSTN_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_GLOBAL_RESET_PD4_RSTN_Msk instead */
#define AON_GP_REGS_AON_GLOBAL_RESET_MASK   0x1Bu                                          /**< \deprecated (AON_GP_REGS_AON_GLOBAL_RESET) Register MASK  (Use AON_GP_REGS_AON_GLOBAL_RESET_Msk instead)  */
#define AON_GP_REGS_AON_GLOBAL_RESET_Msk    0x1Bu                                          /**< (AON_GP_REGS_AON_GLOBAL_RESET) Register Mask  */

/* -------- AON_GP_REGS_AON_PULL_ENABLE : (AON_GP_REGS Offset: 0x14) (R/W 8) Active Low Always On Pull Enable Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  AO_GPIO_0:1;               /**< bit:      0  Pull Enable for AO_GPIO_0                */
    uint8_t  AO_GPIO_1:1;               /**< bit:      1  Pull Enable for AO_GPIO_1                */
    uint8_t  AO_GPIO_2:1;               /**< bit:      2  Pull Enable for AO_GPIO_2                */
    uint8_t  :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint8_t  AO_GPIO_:3;                /**< bit:   0..2  Pull Enable for AO_GPIO_2                */
    uint8_t  :5;                        /**< bit:   3..7 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint8_t  reg;                         /**< Type used for register access */
} AON_GP_REGS_AON_PULL_ENABLE_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_GP_REGS_AON_PULL_ENABLE_OFFSET  0x14                                          /**<  (AON_GP_REGS_AON_PULL_ENABLE) Active Low Always On Pull Enable Control  Offset */
#define AON_GP_REGS_AON_PULL_ENABLE_RESETVALUE 0x00u                                         /**<  (AON_GP_REGS_AON_PULL_ENABLE) Active Low Always On Pull Enable Control  Reset Value */

#define AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO_0_Pos 0                                              /**< (AON_GP_REGS_AON_PULL_ENABLE) Pull Enable for AO_GPIO_0 Position */
#define AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO_0_Msk (0x1u << AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO_0_Pos)  /**< (AON_GP_REGS_AON_PULL_ENABLE) Pull Enable for AO_GPIO_0 Mask */
#define AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO_0 AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO_0_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO_0_Msk instead */
#define AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO_1_Pos 1                                              /**< (AON_GP_REGS_AON_PULL_ENABLE) Pull Enable for AO_GPIO_1 Position */
#define AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO_1_Msk (0x1u << AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO_1_Pos)  /**< (AON_GP_REGS_AON_PULL_ENABLE) Pull Enable for AO_GPIO_1 Mask */
#define AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO_1 AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO_1_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO_1_Msk instead */
#define AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO_2_Pos 2                                              /**< (AON_GP_REGS_AON_PULL_ENABLE) Pull Enable for AO_GPIO_2 Position */
#define AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO_2_Msk (0x1u << AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO_2_Pos)  /**< (AON_GP_REGS_AON_PULL_ENABLE) Pull Enable for AO_GPIO_2 Mask */
#define AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO_2 AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO_2_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO_2_Msk instead */
#define AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO__Pos 0                                              /**< (AON_GP_REGS_AON_PULL_ENABLE Position) Pull Enable for AO_GPIO_2 */
#define AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO__Msk (0x7u << AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO__Pos)  /**< (AON_GP_REGS_AON_PULL_ENABLE Mask) AO_GPIO_ */
#define AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO_(value) (AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO__Msk & ((value) << AON_GP_REGS_AON_PULL_ENABLE_AO_GPIO__Pos))  
#define AON_GP_REGS_AON_PULL_ENABLE_MASK    0x07u                                          /**< \deprecated (AON_GP_REGS_AON_PULL_ENABLE) Register MASK  (Use AON_GP_REGS_AON_PULL_ENABLE_Msk instead)  */
#define AON_GP_REGS_AON_PULL_ENABLE_Msk     0x07u                                          /**< (AON_GP_REGS_AON_PULL_ENABLE) Register Mask  */

/* -------- AON_GP_REGS_AON_RESET_CTRL : (AON_GP_REGS Offset: 0x1c) (R/W 32) Reset Count Control for PD1, PD4, PD6 and PD7 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :4;                        /**< bit:   0..3  Reserved */
    uint32_t PD1_COUNT:4;               /**< bit:   4..7  Number of clock cycles to delay the PD1 reset. (also for PD7) Upper 4 MSBs only (bits 3:0 will be forced to 0) */
    uint32_t :4;                        /**< bit:  8..11  Reserved */
    uint32_t PD4_COUNT:4;               /**< bit: 12..15  Number of clock cycles to delay the PD4 reset. Upper 4 MSBs only (bits 3:0 will be forced to 0) */
    uint32_t PD6_COUNT:4;               /**< bit: 16..19  Number of clock cycles to delay the PD6 reset */
    uint32_t :12;                       /**< bit: 20..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} AON_GP_REGS_AON_RESET_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_GP_REGS_AON_RESET_CTRL_OFFSET   0x1C                                          /**<  (AON_GP_REGS_AON_RESET_CTRL) Reset Count Control for PD1, PD4, PD6 and PD7  Offset */
#define AON_GP_REGS_AON_RESET_CTRL_RESETVALUE 0x3A0A0u                                      /**<  (AON_GP_REGS_AON_RESET_CTRL) Reset Count Control for PD1, PD4, PD6 and PD7  Reset Value */

#define AON_GP_REGS_AON_RESET_CTRL_PD1_COUNT_Pos 4                                              /**< (AON_GP_REGS_AON_RESET_CTRL) Number of clock cycles to delay the PD1 reset. (also for PD7) Upper 4 MSBs only (bits 3:0 will be forced to 0) Position */
#define AON_GP_REGS_AON_RESET_CTRL_PD1_COUNT_Msk (0xFu << AON_GP_REGS_AON_RESET_CTRL_PD1_COUNT_Pos)  /**< (AON_GP_REGS_AON_RESET_CTRL) Number of clock cycles to delay the PD1 reset. (also for PD7) Upper 4 MSBs only (bits 3:0 will be forced to 0) Mask */
#define AON_GP_REGS_AON_RESET_CTRL_PD1_COUNT(value) (AON_GP_REGS_AON_RESET_CTRL_PD1_COUNT_Msk & ((value) << AON_GP_REGS_AON_RESET_CTRL_PD1_COUNT_Pos))
#define AON_GP_REGS_AON_RESET_CTRL_PD4_COUNT_Pos 12                                             /**< (AON_GP_REGS_AON_RESET_CTRL) Number of clock cycles to delay the PD4 reset. Upper 4 MSBs only (bits 3:0 will be forced to 0) Position */
#define AON_GP_REGS_AON_RESET_CTRL_PD4_COUNT_Msk (0xFu << AON_GP_REGS_AON_RESET_CTRL_PD4_COUNT_Pos)  /**< (AON_GP_REGS_AON_RESET_CTRL) Number of clock cycles to delay the PD4 reset. Upper 4 MSBs only (bits 3:0 will be forced to 0) Mask */
#define AON_GP_REGS_AON_RESET_CTRL_PD4_COUNT(value) (AON_GP_REGS_AON_RESET_CTRL_PD4_COUNT_Msk & ((value) << AON_GP_REGS_AON_RESET_CTRL_PD4_COUNT_Pos))
#define AON_GP_REGS_AON_RESET_CTRL_PD6_COUNT_Pos 16                                             /**< (AON_GP_REGS_AON_RESET_CTRL) Number of clock cycles to delay the PD6 reset Position */
#define AON_GP_REGS_AON_RESET_CTRL_PD6_COUNT_Msk (0xFu << AON_GP_REGS_AON_RESET_CTRL_PD6_COUNT_Pos)  /**< (AON_GP_REGS_AON_RESET_CTRL) Number of clock cycles to delay the PD6 reset Mask */
#define AON_GP_REGS_AON_RESET_CTRL_PD6_COUNT(value) (AON_GP_REGS_AON_RESET_CTRL_PD6_COUNT_Msk & ((value) << AON_GP_REGS_AON_RESET_CTRL_PD6_COUNT_Pos))
#define AON_GP_REGS_AON_RESET_CTRL_MASK     0xFF0F0u                                       /**< \deprecated (AON_GP_REGS_AON_RESET_CTRL) Register MASK  (Use AON_GP_REGS_AON_RESET_CTRL_Msk instead)  */
#define AON_GP_REGS_AON_RESET_CTRL_Msk      0xFF0F0u                                       /**< (AON_GP_REGS_AON_RESET_CTRL) Register Mask  */

/* -------- AON_GP_REGS_AON_BTRIM_ACTIVE : (AON_GP_REGS Offset: 0x20) (R/W 8) BTRIM settings for active mode (i.e. not in retention) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  AON_BTRIM_ACTIVE:4;        /**< bit:   0..3                                           */
    uint8_t  :4;                        /**< bit:   4..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} AON_GP_REGS_AON_BTRIM_ACTIVE_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_GP_REGS_AON_BTRIM_ACTIVE_OFFSET 0x20                                          /**<  (AON_GP_REGS_AON_BTRIM_ACTIVE) BTRIM settings for active mode (i.e. not in retention)  Offset */
#define AON_GP_REGS_AON_BTRIM_ACTIVE_RESETVALUE 0x08u                                         /**<  (AON_GP_REGS_AON_BTRIM_ACTIVE) BTRIM settings for active mode (i.e. not in retention)  Reset Value */

#define AON_GP_REGS_AON_BTRIM_ACTIVE_AON_BTRIM_ACTIVE_Pos 0                                              /**< (AON_GP_REGS_AON_BTRIM_ACTIVE)  Position */
#define AON_GP_REGS_AON_BTRIM_ACTIVE_AON_BTRIM_ACTIVE_Msk (0xFu << AON_GP_REGS_AON_BTRIM_ACTIVE_AON_BTRIM_ACTIVE_Pos)  /**< (AON_GP_REGS_AON_BTRIM_ACTIVE)  Mask */
#define AON_GP_REGS_AON_BTRIM_ACTIVE_AON_BTRIM_ACTIVE(value) (AON_GP_REGS_AON_BTRIM_ACTIVE_AON_BTRIM_ACTIVE_Msk & ((value) << AON_GP_REGS_AON_BTRIM_ACTIVE_AON_BTRIM_ACTIVE_Pos))
#define AON_GP_REGS_AON_BTRIM_ACTIVE_MASK   0x0Fu                                          /**< \deprecated (AON_GP_REGS_AON_BTRIM_ACTIVE) Register MASK  (Use AON_GP_REGS_AON_BTRIM_ACTIVE_Msk instead)  */
#define AON_GP_REGS_AON_BTRIM_ACTIVE_Msk    0x0Fu                                          /**< (AON_GP_REGS_AON_BTRIM_ACTIVE) Register Mask  */

/* -------- AON_GP_REGS_AON_BTRIM_RETENTION : (AON_GP_REGS Offset: 0x24) (R/W 8) BTRIM settings for retention mode -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  AON_BTRIM_RETENTION:4;     /**< bit:   0..3                                           */
    uint8_t  :4;                        /**< bit:   4..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} AON_GP_REGS_AON_BTRIM_RETENTION_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_GP_REGS_AON_BTRIM_RETENTION_OFFSET 0x24                                          /**<  (AON_GP_REGS_AON_BTRIM_RETENTION) BTRIM settings for retention mode  Offset */
#define AON_GP_REGS_AON_BTRIM_RETENTION_RESETVALUE 0x08u                                         /**<  (AON_GP_REGS_AON_BTRIM_RETENTION) BTRIM settings for retention mode  Reset Value */

#define AON_GP_REGS_AON_BTRIM_RETENTION_AON_BTRIM_RETENTION_Pos 0                                              /**< (AON_GP_REGS_AON_BTRIM_RETENTION)  Position */
#define AON_GP_REGS_AON_BTRIM_RETENTION_AON_BTRIM_RETENTION_Msk (0xFu << AON_GP_REGS_AON_BTRIM_RETENTION_AON_BTRIM_RETENTION_Pos)  /**< (AON_GP_REGS_AON_BTRIM_RETENTION)  Mask */
#define AON_GP_REGS_AON_BTRIM_RETENTION_AON_BTRIM_RETENTION(value) (AON_GP_REGS_AON_BTRIM_RETENTION_AON_BTRIM_RETENTION_Msk & ((value) << AON_GP_REGS_AON_BTRIM_RETENTION_AON_BTRIM_RETENTION_Pos))
#define AON_GP_REGS_AON_BTRIM_RETENTION_MASK 0x0Fu                                          /**< \deprecated (AON_GP_REGS_AON_BTRIM_RETENTION) Register MASK  (Use AON_GP_REGS_AON_BTRIM_RETENTION_Msk instead)  */
#define AON_GP_REGS_AON_BTRIM_RETENTION_Msk 0x0Fu                                          /**< (AON_GP_REGS_AON_BTRIM_RETENTION) Register Mask  */

/* -------- AON_GP_REGS_AON_LPMCU_SCRATCH_PAD : (AON_GP_REGS Offset: 0x40) (R/W 8) Usage for the LPMCU for any sort of status it needs to store for itself before it goes to sleep -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  AON_LPMCU_SCRATCH_PAD:8;   /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} AON_GP_REGS_AON_LPMCU_SCRATCH_PAD_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_GP_REGS_AON_LPMCU_SCRATCH_PAD_OFFSET 0x40                                          /**<  (AON_GP_REGS_AON_LPMCU_SCRATCH_PAD) Usage for the LPMCU for any sort of status it needs to store for itself before it goes to sleep  Offset */
#define AON_GP_REGS_AON_LPMCU_SCRATCH_PAD_RESETVALUE 0x00u                                         /**<  (AON_GP_REGS_AON_LPMCU_SCRATCH_PAD) Usage for the LPMCU for any sort of status it needs to store for itself before it goes to sleep  Reset Value */

#define AON_GP_REGS_AON_LPMCU_SCRATCH_PAD_AON_LPMCU_SCRATCH_PAD_Pos 0                                              /**< (AON_GP_REGS_AON_LPMCU_SCRATCH_PAD)  Position */
#define AON_GP_REGS_AON_LPMCU_SCRATCH_PAD_AON_LPMCU_SCRATCH_PAD_Msk (0xFFu << AON_GP_REGS_AON_LPMCU_SCRATCH_PAD_AON_LPMCU_SCRATCH_PAD_Pos)  /**< (AON_GP_REGS_AON_LPMCU_SCRATCH_PAD)  Mask */
#define AON_GP_REGS_AON_LPMCU_SCRATCH_PAD_AON_LPMCU_SCRATCH_PAD(value) (AON_GP_REGS_AON_LPMCU_SCRATCH_PAD_AON_LPMCU_SCRATCH_PAD_Msk & ((value) << AON_GP_REGS_AON_LPMCU_SCRATCH_PAD_AON_LPMCU_SCRATCH_PAD_Pos))
#define AON_GP_REGS_AON_LPMCU_SCRATCH_PAD_MASK 0xFFu                                          /**< \deprecated (AON_GP_REGS_AON_LPMCU_SCRATCH_PAD) Register MASK  (Use AON_GP_REGS_AON_LPMCU_SCRATCH_PAD_Msk instead)  */
#define AON_GP_REGS_AON_LPMCU_SCRATCH_PAD_Msk 0xFFu                                          /**< (AON_GP_REGS_AON_LPMCU_SCRATCH_PAD) Register Mask  */

/* -------- AON_GP_REGS_AON_LPMCU_COLD_BOOT : (AON_GP_REGS Offset: 0x44) (R/W 8) To be used by ARM to determine if it is a cold boot or not -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  AON_LPMCU_COLD_BOOT:8;     /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} AON_GP_REGS_AON_LPMCU_COLD_BOOT_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_GP_REGS_AON_LPMCU_COLD_BOOT_OFFSET 0x44                                          /**<  (AON_GP_REGS_AON_LPMCU_COLD_BOOT) To be used by ARM to determine if it is a cold boot or not  Offset */
#define AON_GP_REGS_AON_LPMCU_COLD_BOOT_RESETVALUE 0x78u                                         /**<  (AON_GP_REGS_AON_LPMCU_COLD_BOOT) To be used by ARM to determine if it is a cold boot or not  Reset Value */

#define AON_GP_REGS_AON_LPMCU_COLD_BOOT_AON_LPMCU_COLD_BOOT_Pos 0                                              /**< (AON_GP_REGS_AON_LPMCU_COLD_BOOT)  Position */
#define AON_GP_REGS_AON_LPMCU_COLD_BOOT_AON_LPMCU_COLD_BOOT_Msk (0xFFu << AON_GP_REGS_AON_LPMCU_COLD_BOOT_AON_LPMCU_COLD_BOOT_Pos)  /**< (AON_GP_REGS_AON_LPMCU_COLD_BOOT)  Mask */
#define AON_GP_REGS_AON_LPMCU_COLD_BOOT_AON_LPMCU_COLD_BOOT(value) (AON_GP_REGS_AON_LPMCU_COLD_BOOT_AON_LPMCU_COLD_BOOT_Msk & ((value) << AON_GP_REGS_AON_LPMCU_COLD_BOOT_AON_LPMCU_COLD_BOOT_Pos))
#define AON_GP_REGS_AON_LPMCU_COLD_BOOT_MASK 0xFFu                                          /**< \deprecated (AON_GP_REGS_AON_LPMCU_COLD_BOOT) Register MASK  (Use AON_GP_REGS_AON_LPMCU_COLD_BOOT_Msk instead)  */
#define AON_GP_REGS_AON_LPMCU_COLD_BOOT_Msk 0xFFu                                          /**< (AON_GP_REGS_AON_LPMCU_COLD_BOOT) Register Mask  */

/* -------- AON_GP_REGS_AON_BO_OUT_STATUS : (AON_GP_REGS Offset: 0x80) (R/ 8) Brown Out Detected (must be cleared manually) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  AON_BO_OUT_STATUS:1;       /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} AON_GP_REGS_AON_BO_OUT_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_GP_REGS_AON_BO_OUT_STATUS_OFFSET 0x80                                          /**<  (AON_GP_REGS_AON_BO_OUT_STATUS) Brown Out Detected (must be cleared manually)  Offset */
#define AON_GP_REGS_AON_BO_OUT_STATUS_RESETVALUE 0x00u                                         /**<  (AON_GP_REGS_AON_BO_OUT_STATUS) Brown Out Detected (must be cleared manually)  Reset Value */

#define AON_GP_REGS_AON_BO_OUT_STATUS_AON_BO_OUT_STATUS_Pos 0                                              /**< (AON_GP_REGS_AON_BO_OUT_STATUS)  Position */
#define AON_GP_REGS_AON_BO_OUT_STATUS_AON_BO_OUT_STATUS_Msk (0x1u << AON_GP_REGS_AON_BO_OUT_STATUS_AON_BO_OUT_STATUS_Pos)  /**< (AON_GP_REGS_AON_BO_OUT_STATUS)  Mask */
#define AON_GP_REGS_AON_BO_OUT_STATUS_AON_BO_OUT_STATUS AON_GP_REGS_AON_BO_OUT_STATUS_AON_BO_OUT_STATUS_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_AON_BO_OUT_STATUS_AON_BO_OUT_STATUS_Msk instead */
#define AON_GP_REGS_AON_BO_OUT_STATUS_MASK  0x01u                                          /**< \deprecated (AON_GP_REGS_AON_BO_OUT_STATUS) Register MASK  (Use AON_GP_REGS_AON_BO_OUT_STATUS_Msk instead)  */
#define AON_GP_REGS_AON_BO_OUT_STATUS_Msk   0x01u                                          /**< (AON_GP_REGS_AON_BO_OUT_STATUS) Register Mask  */

/* -------- AON_GP_REGS_CLEAR_BROWN_OUT_REG : (AON_GP_REGS Offset: 0x84) (R/W 8) Set to 1 to clear (hold until 0 read at aon_bo_out_status and then this must be cleared to detect another brown out condition) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CLEAR_BROWN_OUT_REG:1;     /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} AON_GP_REGS_CLEAR_BROWN_OUT_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_GP_REGS_CLEAR_BROWN_OUT_REG_OFFSET 0x84                                          /**<  (AON_GP_REGS_CLEAR_BROWN_OUT_REG) Set to 1 to clear (hold until 0 read at aon_bo_out_status and then this must be cleared to detect another brown out condition)  Offset */
#define AON_GP_REGS_CLEAR_BROWN_OUT_REG_RESETVALUE 0x00u                                         /**<  (AON_GP_REGS_CLEAR_BROWN_OUT_REG) Set to 1 to clear (hold until 0 read at aon_bo_out_status and then this must be cleared to detect another brown out condition)  Reset Value */

#define AON_GP_REGS_CLEAR_BROWN_OUT_REG_CLEAR_BROWN_OUT_REG_Pos 0                                              /**< (AON_GP_REGS_CLEAR_BROWN_OUT_REG)  Position */
#define AON_GP_REGS_CLEAR_BROWN_OUT_REG_CLEAR_BROWN_OUT_REG_Msk (0x1u << AON_GP_REGS_CLEAR_BROWN_OUT_REG_CLEAR_BROWN_OUT_REG_Pos)  /**< (AON_GP_REGS_CLEAR_BROWN_OUT_REG)  Mask */
#define AON_GP_REGS_CLEAR_BROWN_OUT_REG_CLEAR_BROWN_OUT_REG AON_GP_REGS_CLEAR_BROWN_OUT_REG_CLEAR_BROWN_OUT_REG_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_CLEAR_BROWN_OUT_REG_CLEAR_BROWN_OUT_REG_Msk instead */
#define AON_GP_REGS_CLEAR_BROWN_OUT_REG_MASK 0x01u                                          /**< \deprecated (AON_GP_REGS_CLEAR_BROWN_OUT_REG) Register MASK  (Use AON_GP_REGS_CLEAR_BROWN_OUT_REG_Msk instead)  */
#define AON_GP_REGS_CLEAR_BROWN_OUT_REG_Msk 0x01u                                          /**< (AON_GP_REGS_CLEAR_BROWN_OUT_REG) Register Mask  */

/* -------- AON_GP_REGS_RF_PMU_REGS_0 : (AON_GP_REGS Offset: 0x400) (R/W 32) RF PMU Registers -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CLK_EDGE_SEL:1;            /**< bit:      0  Select clock edge for Vreg comparator in buck converter */
    uint32_t VOUT_CTRL_BUCK:4;          /**< bit:   1..4  Select the output voltage of the buck converter */
    uint32_t CLK_2_4:1;                 /**< bit:      5  Comparator clock divider in buck converter */
    uint32_t VREG_FILT_CTRL:2;          /**< bit:   6..7  Not Used                                 */
    uint32_t CLK_DIV:3;                 /**< bit:  8..10  Programmable divider that sets the on duration of positive charging pulse */
    uint32_t RESET_FSM:1;               /**< bit:     11  Force reset of FSM in buck converter     */
    uint32_t EN_TRISTATE:1;             /**< bit:     12  Allow tristate_ctrl to control minimum time between pulses of the buck converter */
    uint32_t TRISTATE_CTRL:3;           /**< bit: 13..15  Controls the minimum time between pulses in the buck converter */
    uint32_t OFFSETP_CTRL:4;            /**< bit: 16..19  Controls a fixed comparator offset in the buck converter for positive pulses */
    uint32_t OFFSETN_CTRL:4;            /**< bit: 20..23  Controls a fixed comparator offset in the buck converter for negative pulses */
    uint32_t P_SW_CTRL:7;               /**< bit: 24..30  Power switch units for the buck converter */
    uint32_t CLK_SEL:1;                 /**< bit:     31  Source clock for the buck converter      */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} AON_GP_REGS_RF_PMU_REGS_0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_GP_REGS_RF_PMU_REGS_0_OFFSET    0x400                                         /**<  (AON_GP_REGS_RF_PMU_REGS_0) RF PMU Registers  Offset */
#define AON_GP_REGS_RF_PMU_REGS_0_RESETVALUE 0xF600409u                                    /**<  (AON_GP_REGS_RF_PMU_REGS_0) RF PMU Registers  Reset Value */

#define AON_GP_REGS_RF_PMU_REGS_0_CLK_EDGE_SEL_Pos 0                                              /**< (AON_GP_REGS_RF_PMU_REGS_0) Select clock edge for Vreg comparator in buck converter Position */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_EDGE_SEL_Msk (0x1u << AON_GP_REGS_RF_PMU_REGS_0_CLK_EDGE_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Select clock edge for Vreg comparator in buck converter Mask */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_EDGE_SEL AON_GP_REGS_RF_PMU_REGS_0_CLK_EDGE_SEL_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_RF_PMU_REGS_0_CLK_EDGE_SEL_Msk instead */
#define   AON_GP_REGS_RF_PMU_REGS_0_CLK_EDGE_SEL_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Comparator samples on rising edge of clock  */
#define   AON_GP_REGS_RF_PMU_REGS_0_CLK_EDGE_SEL_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Comparator samples on falling edge of clock  */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_EDGE_SEL_0 (AON_GP_REGS_RF_PMU_REGS_0_CLK_EDGE_SEL_0_Val << AON_GP_REGS_RF_PMU_REGS_0_CLK_EDGE_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Comparator samples on rising edge of clock Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_EDGE_SEL_1 (AON_GP_REGS_RF_PMU_REGS_0_CLK_EDGE_SEL_1_Val << AON_GP_REGS_RF_PMU_REGS_0_CLK_EDGE_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Comparator samples on falling edge of clock Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Pos 1                                              /**< (AON_GP_REGS_RF_PMU_REGS_0) Select the output voltage of the buck converter Position */
#define AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Msk (0xFu << AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Select the output voltage of the buck converter Mask */
#define AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK(value) (AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Msk & ((value) << AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Pos))
#define   AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.12V  */
#define   AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.15V  */
#define   AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_2_Val 0x2u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.17V  */
#define   AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_3_Val 0x3u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.20V  */
#define   AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_4_Val 0x4u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.22V  */
#define   AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_5_Val 0x5u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.25V  */
#define   AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_6_Val 0x6u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.27V  */
#define   AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_7_Val 0x7u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.30V  */
#define   AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_8_Val 0x8u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.32V  */
#define   AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_9_Val 0x9u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.35V  */
#define   AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_10_Val 0xAu                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.37V  */
#define   AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_11_Val 0xBu                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.40V  */
#define   AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_12_Val 0xCu                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.42V  */
#define   AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_13_Val 0xDu                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.45V  */
#define   AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_14_Val 0xEu                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.47V  */
#define   AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_15_Val 0xFu                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.50V  */
#define AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_0 (AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_0_Val << AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.12V Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_1 (AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_1_Val << AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.15V Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_2 (AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_2_Val << AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.17V Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_3 (AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_3_Val << AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.20V Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_4 (AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_4_Val << AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.22V Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_5 (AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_5_Val << AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.25V Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_6 (AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_6_Val << AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.27V Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_7 (AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_7_Val << AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.30V Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_8 (AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_8_Val << AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.32V Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_9 (AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_9_Val << AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.35V Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_10 (AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_10_Val << AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.37V Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_11 (AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_11_Val << AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.40V Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_12 (AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_12_Val << AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.42V Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_13 (AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_13_Val << AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.45V Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_14 (AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_14_Val << AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.47V Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_15 (AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_15_Val << AON_GP_REGS_RF_PMU_REGS_0_VOUT_CTRL_BUCK_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.50V Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_2_4_Pos 5                                              /**< (AON_GP_REGS_RF_PMU_REGS_0) Comparator clock divider in buck converter Position */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_2_4_Msk (0x1u << AON_GP_REGS_RF_PMU_REGS_0_CLK_2_4_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Comparator clock divider in buck converter Mask */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_2_4   AON_GP_REGS_RF_PMU_REGS_0_CLK_2_4_Msk          /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_RF_PMU_REGS_0_CLK_2_4_Msk instead */
#define   AON_GP_REGS_RF_PMU_REGS_0_CLK_2_4_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 2  */
#define   AON_GP_REGS_RF_PMU_REGS_0_CLK_2_4_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 4  */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_2_4_0 (AON_GP_REGS_RF_PMU_REGS_0_CLK_2_4_0_Val << AON_GP_REGS_RF_PMU_REGS_0_CLK_2_4_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 2 Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_2_4_1 (AON_GP_REGS_RF_PMU_REGS_0_CLK_2_4_1_Val << AON_GP_REGS_RF_PMU_REGS_0_CLK_2_4_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 4 Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_VREG_FILT_CTRL_Pos 6                                              /**< (AON_GP_REGS_RF_PMU_REGS_0) Not Used Position */
#define AON_GP_REGS_RF_PMU_REGS_0_VREG_FILT_CTRL_Msk (0x3u << AON_GP_REGS_RF_PMU_REGS_0_VREG_FILT_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Not Used Mask */
#define AON_GP_REGS_RF_PMU_REGS_0_VREG_FILT_CTRL(value) (AON_GP_REGS_RF_PMU_REGS_0_VREG_FILT_CTRL_Msk & ((value) << AON_GP_REGS_RF_PMU_REGS_0_VREG_FILT_CTRL_Pos))
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_Pos 8                                              /**< (AON_GP_REGS_RF_PMU_REGS_0) Programmable divider that sets the on duration of positive charging pulse Position */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_Msk (0x7u << AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Programmable divider that sets the on duration of positive charging pulse Mask */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV(value) (AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_Msk & ((value) << AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_Pos))
#define   AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 4  */
#define   AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 6  */
#define   AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_2_Val 0x2u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 8  */
#define   AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_3_Val 0x3u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 10  */
#define   AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_4_Val 0x4u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 12  */
#define   AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_5_Val 0x5u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 14  */
#define   AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_6_Val 0x6u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 16  */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_0 (AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_0_Val << AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 4 Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_1 (AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_1_Val << AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 6 Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_2 (AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_2_Val << AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 8 Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_3 (AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_3_Val << AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 10 Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_4 (AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_4_Val << AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 12 Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_5 (AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_5_Val << AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 14 Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_6 (AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_6_Val << AON_GP_REGS_RF_PMU_REGS_0_CLK_DIV_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 16 Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_RESET_FSM_Pos 11                                             /**< (AON_GP_REGS_RF_PMU_REGS_0) Force reset of FSM in buck converter Position */
#define AON_GP_REGS_RF_PMU_REGS_0_RESET_FSM_Msk (0x1u << AON_GP_REGS_RF_PMU_REGS_0_RESET_FSM_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Force reset of FSM in buck converter Mask */
#define AON_GP_REGS_RF_PMU_REGS_0_RESET_FSM AON_GP_REGS_RF_PMU_REGS_0_RESET_FSM_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_RF_PMU_REGS_0_RESET_FSM_Msk instead */
#define   AON_GP_REGS_RF_PMU_REGS_0_RESET_FSM_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) FSM is not reset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_RESET_FSM_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) FSM is reset  */
#define AON_GP_REGS_RF_PMU_REGS_0_RESET_FSM_0 (AON_GP_REGS_RF_PMU_REGS_0_RESET_FSM_0_Val << AON_GP_REGS_RF_PMU_REGS_0_RESET_FSM_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) FSM is not reset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_RESET_FSM_1 (AON_GP_REGS_RF_PMU_REGS_0_RESET_FSM_1_Val << AON_GP_REGS_RF_PMU_REGS_0_RESET_FSM_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) FSM is reset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_EN_TRISTATE_Pos 12                                             /**< (AON_GP_REGS_RF_PMU_REGS_0) Allow tristate_ctrl to control minimum time between pulses of the buck converter Position */
#define AON_GP_REGS_RF_PMU_REGS_0_EN_TRISTATE_Msk (0x1u << AON_GP_REGS_RF_PMU_REGS_0_EN_TRISTATE_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Allow tristate_ctrl to control minimum time between pulses of the buck converter Mask */
#define AON_GP_REGS_RF_PMU_REGS_0_EN_TRISTATE AON_GP_REGS_RF_PMU_REGS_0_EN_TRISTATE_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_RF_PMU_REGS_0_EN_TRISTATE_Msk instead */
#define   AON_GP_REGS_RF_PMU_REGS_0_EN_TRISTATE_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Tristate logic disable  */
#define   AON_GP_REGS_RF_PMU_REGS_0_EN_TRISTATE_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Tristate logic enabled  */
#define AON_GP_REGS_RF_PMU_REGS_0_EN_TRISTATE_0 (AON_GP_REGS_RF_PMU_REGS_0_EN_TRISTATE_0_Val << AON_GP_REGS_RF_PMU_REGS_0_EN_TRISTATE_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Tristate logic disable Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_EN_TRISTATE_1 (AON_GP_REGS_RF_PMU_REGS_0_EN_TRISTATE_1_Val << AON_GP_REGS_RF_PMU_REGS_0_EN_TRISTATE_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Tristate logic enabled Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_Pos 13                                             /**< (AON_GP_REGS_RF_PMU_REGS_0) Controls the minimum time between pulses in the buck converter Position */
#define AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_Msk (0x7u << AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Controls the minimum time between pulses in the buck converter Mask */
#define AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL(value) (AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_Msk & ((value) << AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_Pos))
#define   AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 4  */
#define   AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 6  */
#define   AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_2_Val 0x2u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 8  */
#define   AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_3_Val 0x3u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 10  */
#define   AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_4_Val 0x4u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 12  */
#define   AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_5_Val 0x5u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 14  */
#define   AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_6_Val 0x6u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 16  */
#define AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_0 (AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_0_Val << AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 4 Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_1 (AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_1_Val << AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 6 Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_2 (AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_2_Val << AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 8 Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_3 (AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_3_Val << AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 10 Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_4 (AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_4_Val << AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 12 Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_5 (AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_5_Val << AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 14 Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_6 (AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_6_Val << AON_GP_REGS_RF_PMU_REGS_0_TRISTATE_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Divide by 16 Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Pos 16                                             /**< (AON_GP_REGS_RF_PMU_REGS_0) Controls a fixed comparator offset in the buck converter for positive pulses Position */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Msk (0xFu << AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Controls a fixed comparator offset in the buck converter for positive pulses Mask */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL(value) (AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Msk & ((value) << AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Pos))
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 0.0mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 0.4mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_2_Val 0x2u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 0.8mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_3_Val 0x3u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.2mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_4_Val 0x4u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.6mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_5_Val 0x5u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 2.0mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_6_Val 0x6u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 2.4mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_7_Val 0x7u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 2.8mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_8_Val 0x8u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 3.2mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_9_Val 0x9u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 3.6mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_10_Val 0xAu                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 4.0mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_11_Val 0xBu                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 4.4mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_12_Val 0xCu                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 4.8mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_13_Val 0xDu                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 5.2mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_14_Val 0xEu                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 5.6mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_15_Val 0xFu                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 6.0mV offset  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_0 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_0_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 0.0mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_1 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_1_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 0.4mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_2 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_2_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 0.8mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_3 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_3_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.2mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_4 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_4_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.6mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_5 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_5_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 2.0mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_6 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_6_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 2.4mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_7 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_7_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 2.8mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_8 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_8_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 3.2mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_9 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_9_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 3.6mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_10 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_10_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 4.0mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_11 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_11_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 4.4mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_12 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_12_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 4.8mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_13 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_13_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 5.2mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_14 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_14_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 5.6mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_15 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_15_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 6.0mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Pos 20                                             /**< (AON_GP_REGS_RF_PMU_REGS_0) Controls a fixed comparator offset in the buck converter for negative pulses Position */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Msk (0xFu << AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Controls a fixed comparator offset in the buck converter for negative pulses Mask */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL(value) (AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Msk & ((value) << AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Pos))
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 0.0mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 0.4mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_2_Val 0x2u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 0.8mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_3_Val 0x3u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.2mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_4_Val 0x4u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.6mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_5_Val 0x5u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 2.0mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_6_Val 0x6u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 2.4mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_7_Val 0x7u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 2.8mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_8_Val 0x8u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 3.2mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_9_Val 0x9u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 3.6mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_10_Val 0xAu                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 4.0mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_11_Val 0xBu                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 4.4mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_12_Val 0xCu                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 4.8mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_13_Val 0xDu                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 5.2mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_14_Val 0xEu                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 5.6mV offset  */
#define   AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_15_Val 0xFu                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 6.0mV offset  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_0 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_0_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 0.0mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_1 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_1_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 0.4mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_2 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_2_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 0.8mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_3 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_3_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.2mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_4 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_4_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1.6mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_5 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_5_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 2.0mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_6 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_6_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 2.4mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_7 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_7_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 2.8mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_8 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_8_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 3.2mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_9 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_9_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 3.6mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_10 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_10_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 4.0mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_11 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_11_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 4.4mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_12 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_12_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 4.8mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_13 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_13_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 5.2mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_14 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_14_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 5.6mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_15 (AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_15_Val << AON_GP_REGS_RF_PMU_REGS_0_OFFSETN_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 6.0mV offset Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_Pos 24                                             /**< (AON_GP_REGS_RF_PMU_REGS_0) Power switch units for the buck converter Position */
#define AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_Msk (0x7Fu << AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Power switch units for the buck converter Mask */
#define AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL(value) (AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_Msk & ((value) << AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_Pos))
#define   AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 0 power switches enabled  */
#define   AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 1 power switch enabled  */
#define   AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_3_Val 0x3u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 2 power switches enabled  */
#define   AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_7_Val 0x7u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 3 power switches enabled  */
#define   AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_15_Val 0xFu                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) 4 power switches enabled  */
#define   AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_31_Val 0x1Fu                                          /**< (AON_GP_REGS_RF_PMU_REGS_0) 5 power switches enabled  */
#define   AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_63_Val 0x3Fu                                          /**< (AON_GP_REGS_RF_PMU_REGS_0) 6 power switches enabled  */
#define AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_0 (AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_0_Val << AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 0 power switches enabled Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_1 (AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_1_Val << AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 1 power switch enabled Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_3 (AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_3_Val << AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 2 power switches enabled Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_7 (AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_7_Val << AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 3 power switches enabled Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_15 (AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_15_Val << AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 4 power switches enabled Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_31 (AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_31_Val << AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 5 power switches enabled Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_63 (AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_63_Val << AON_GP_REGS_RF_PMU_REGS_0_P_SW_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) 6 power switches enabled Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_SEL_Pos 31                                             /**< (AON_GP_REGS_RF_PMU_REGS_0) Source clock for the buck converter Position */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_SEL_Msk (0x1u << AON_GP_REGS_RF_PMU_REGS_0_CLK_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Source clock for the buck converter Mask */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_SEL   AON_GP_REGS_RF_PMU_REGS_0_CLK_SEL_Msk          /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_RF_PMU_REGS_0_CLK_SEL_Msk instead */
#define   AON_GP_REGS_RF_PMU_REGS_0_CLK_SEL_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) Internal 26MHz clock  */
#define   AON_GP_REGS_RF_PMU_REGS_0_CLK_SEL_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_0) External 52MHz clock  */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_SEL_0 (AON_GP_REGS_RF_PMU_REGS_0_CLK_SEL_0_Val << AON_GP_REGS_RF_PMU_REGS_0_CLK_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) Internal 26MHz clock Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_CLK_SEL_1 (AON_GP_REGS_RF_PMU_REGS_0_CLK_SEL_1_Val << AON_GP_REGS_RF_PMU_REGS_0_CLK_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_0) External 52MHz clock Position  */
#define AON_GP_REGS_RF_PMU_REGS_0_MASK      0xFFFFFFFFu                                    /**< \deprecated (AON_GP_REGS_RF_PMU_REGS_0) Register MASK  (Use AON_GP_REGS_RF_PMU_REGS_0_Msk instead)  */
#define AON_GP_REGS_RF_PMU_REGS_0_Msk       0xFFFFFFFFu                                    /**< (AON_GP_REGS_RF_PMU_REGS_0) Register Mask  */

/* -------- AON_GP_REGS_RF_PMU_REGS_1 : (AON_GP_REGS Offset: 0x404) (R/W 32) RF PMU Registers -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SADC_BIAS_RES_CTRL:4;      /**< bit:   0..3  Internal reference voltage level for sensor ADC */
    uint32_t SADC_REF_SEL:3;            /**< bit:   4..6  Reference Voltage Source for the Sensor ADC */
    uint32_t BOD_EN:1;                  /**< bit:      7  Brown Out Detector Enable Control        */
    uint32_t LPD_CLK_INJECT_EN:1;       /**< bit:      8  Low Power Domain Clock Injection Enable Control */
    uint32_t EFUSE_LDO_BYP:1;           /**< bit:      9  Bypass controlf for EFUSE LDO            */
    uint32_t EFUSE_LDO_VOUT_CTRL:3;     /**< bit: 10..12  Output voltage of EFUSE LDO              */
    uint32_t EFUSE_LDO_IBIAS_CTRL:2;    /**< bit: 13..14  Set the current bias for the EFUSE LDO   */
    uint32_t PIERCE_RES_CTRL:1;         /**< bit:     15  RTC crystal circuit feedback resistance value */
    uint32_t PIERCE_GM_CTRL:4;          /**< bit: 16..19  Transconductance of RTC oscillator       */
    uint32_t PIERCE_CAP_CTRL:4;         /**< bit: 20..23  On chip single ended capacitors for RTC oscillator */
    uint32_t SADC_CHN_CTRL:1;           /**< bit:     24  enable input channel time multiplexing to the sensor ADC */
    uint32_t SADC_CHN_SEL:3;            /**< bit: 25..27  Input channel selection for the sensor ADC */
    uint32_t CODE_IN:2;                 /**< bit: 28..29  Optional mode to improve sub-ranging technique of the sensor ADC */
    uint32_t SADC_LP_CTRL:2;            /**< bit: 30..31  Comparator biasing current for different sampling rates of the sensor ADC */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} AON_GP_REGS_RF_PMU_REGS_1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_GP_REGS_RF_PMU_REGS_1_OFFSET    0x404                                         /**<  (AON_GP_REGS_RF_PMU_REGS_1) RF PMU Registers  Offset */
#define AON_GP_REGS_RF_PMU_REGS_1_RESETVALUE 0x31888C82u                                   /**<  (AON_GP_REGS_RF_PMU_REGS_1) RF PMU Registers  Reset Value */

#define AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Pos 0                                              /**< (AON_GP_REGS_RF_PMU_REGS_1) Internal reference voltage level for sensor ADC Position */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Msk (0xFu << AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Internal reference voltage level for sensor ADC Mask */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL(value) (AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Msk & ((value) << AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Pos))
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 0.5V  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 0.6V  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_2_Val 0x2u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 0.7V  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_3_Val 0x3u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 0.8V  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_4_Val 0x4u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 0.9V  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_5_Val 0x5u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 1.0V  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_6_Val 0x6u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 1.1V (only for VBATT gt 2.0V)  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_7_Val 0x7u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 1.2V (only for VBATT gt 2.0V)  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_8_Val 0x8u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 1.3V (only for VBATT gt 2.0V)  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_9_Val 0x9u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 1.4V (only for VBATT gt 2.0V)  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_10_Val 0xAu                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 1.5V (only for VBATT gt 2.0V)  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_11_Val 0xBu                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 1.6V (only for VBATT gt 2.0V)  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_12_Val 0xCu                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 1.7V (only for VBATT gt 2.0V)  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_13_Val 0xDu                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 1.8V (only for VBATT gt 2.0V)  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_14_Val 0xEu                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 1.9V (only for VBATT gt 2.0V)  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_15_Val 0xFu                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 2.0V (only for VBATT gt 2.0V)  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_0 (AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_0_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 0.5V Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_1 (AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_1_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 0.6V Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_2 (AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_2_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 0.7V Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_3 (AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_3_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 0.8V Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_4 (AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_4_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 0.9V Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_5 (AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_5_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 1.0V Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_6 (AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_6_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 1.1V (only for VBATT gt 2.0V) Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_7 (AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_7_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 1.2V (only for VBATT gt 2.0V) Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_8 (AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_8_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 1.3V (only for VBATT gt 2.0V) Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_9 (AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_9_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 1.4V (only for VBATT gt 2.0V) Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_10 (AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_10_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 1.5V (only for VBATT gt 2.0V) Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_11 (AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_11_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 1.6V (only for VBATT gt 2.0V) Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_12 (AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_12_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 1.7V (only for VBATT gt 2.0V) Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_13 (AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_13_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 1.8V (only for VBATT gt 2.0V) Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_14 (AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_14_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 1.9V (only for VBATT gt 2.0V) Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_15 (AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_15_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_BIAS_RES_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 2.0V (only for VBATT gt 2.0V) Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_Pos 4                                              /**< (AON_GP_REGS_RF_PMU_REGS_1) Reference Voltage Source for the Sensor ADC Position */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_Msk (0x7u << AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Reference Voltage Source for the Sensor ADC Mask */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL(value) (AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_Msk & ((value) << AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_Pos))
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) Buffered reference voltage  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) IR voltage  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_2_Val 0x2u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) VBATT divided by 2  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_3_Val 0x3u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) GPIO_MS1  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_4_Val 0x4u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) GPIO_MS2  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_5_Val 0x5u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) GPIO_MS3  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_6_Val 0x6u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) GPIO_MS4  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_7_Val 0x7u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) VBATT supply voltage  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_0 (AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_0_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Buffered reference voltage Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_1 (AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_1_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) IR voltage Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_2 (AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_2_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) VBATT divided by 2 Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_3 (AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_3_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) GPIO_MS1 Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_4 (AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_4_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) GPIO_MS2 Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_5 (AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_5_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) GPIO_MS3 Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_6 (AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_6_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) GPIO_MS4 Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_7 (AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_7_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_REF_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) VBATT supply voltage Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_BOD_EN_Pos 7                                              /**< (AON_GP_REGS_RF_PMU_REGS_1) Brown Out Detector Enable Control Position */
#define AON_GP_REGS_RF_PMU_REGS_1_BOD_EN_Msk (0x1u << AON_GP_REGS_RF_PMU_REGS_1_BOD_EN_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Brown Out Detector Enable Control Mask */
#define AON_GP_REGS_RF_PMU_REGS_1_BOD_EN    AON_GP_REGS_RF_PMU_REGS_1_BOD_EN_Msk           /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_RF_PMU_REGS_1_BOD_EN_Msk instead */
#define   AON_GP_REGS_RF_PMU_REGS_1_BOD_EN_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) Disable  */
#define   AON_GP_REGS_RF_PMU_REGS_1_BOD_EN_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) Enable  */
#define AON_GP_REGS_RF_PMU_REGS_1_BOD_EN_0  (AON_GP_REGS_RF_PMU_REGS_1_BOD_EN_0_Val << AON_GP_REGS_RF_PMU_REGS_1_BOD_EN_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Disable Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_BOD_EN_1  (AON_GP_REGS_RF_PMU_REGS_1_BOD_EN_1_Val << AON_GP_REGS_RF_PMU_REGS_1_BOD_EN_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Enable Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_LPD_CLK_INJECT_EN_Pos 8                                              /**< (AON_GP_REGS_RF_PMU_REGS_1) Low Power Domain Clock Injection Enable Control Position */
#define AON_GP_REGS_RF_PMU_REGS_1_LPD_CLK_INJECT_EN_Msk (0x1u << AON_GP_REGS_RF_PMU_REGS_1_LPD_CLK_INJECT_EN_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Low Power Domain Clock Injection Enable Control Mask */
#define AON_GP_REGS_RF_PMU_REGS_1_LPD_CLK_INJECT_EN AON_GP_REGS_RF_PMU_REGS_1_LPD_CLK_INJECT_EN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_RF_PMU_REGS_1_LPD_CLK_INJECT_EN_Msk instead */
#define   AON_GP_REGS_RF_PMU_REGS_1_LPD_CLK_INJECT_EN_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) Disable (Free running)  */
#define   AON_GP_REGS_RF_PMU_REGS_1_LPD_CLK_INJECT_EN_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) Enable (Lock to XO clock)  */
#define AON_GP_REGS_RF_PMU_REGS_1_LPD_CLK_INJECT_EN_0 (AON_GP_REGS_RF_PMU_REGS_1_LPD_CLK_INJECT_EN_0_Val << AON_GP_REGS_RF_PMU_REGS_1_LPD_CLK_INJECT_EN_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Disable (Free running) Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_LPD_CLK_INJECT_EN_1 (AON_GP_REGS_RF_PMU_REGS_1_LPD_CLK_INJECT_EN_1_Val << AON_GP_REGS_RF_PMU_REGS_1_LPD_CLK_INJECT_EN_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Enable (Lock to XO clock) Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_BYP_Pos 9                                              /**< (AON_GP_REGS_RF_PMU_REGS_1) Bypass controlf for EFUSE LDO Position */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_BYP_Msk (0x1u << AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_BYP_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Bypass controlf for EFUSE LDO Mask */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_BYP AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_BYP_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_BYP_Msk instead */
#define   AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_BYP_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) EFUSE LDO regulates from VBATT voltage to 2.5V  */
#define   AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_BYP_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1)  EFUSE LDO is bypass to VBATT voltage  */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_BYP_0 (AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_BYP_0_Val << AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_BYP_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) EFUSE LDO regulates from VBATT voltage to 2.5V Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_BYP_1 (AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_BYP_1_Val << AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_BYP_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1)  EFUSE LDO is bypass to VBATT voltage Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_Pos 10                                             /**< (AON_GP_REGS_RF_PMU_REGS_1) Output voltage of EFUSE LDO Position */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_Msk (0x7u << AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Output voltage of EFUSE LDO Mask */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL(value) (AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_Msk & ((value) << AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_Pos))
#define   AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 2.3V  */
#define   AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 2.4V  */
#define   AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_2_Val 0x2u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 2.4V  */
#define   AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_3_Val 0x3u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 2.5V  */
#define   AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_4_Val 0x4u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 2.6V  */
#define   AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_5_Val 0x5u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 2.7V  */
#define   AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_6_Val 0x6u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 2.7V  */
#define   AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_7_Val 0x7u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 2.8V  */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_0 (AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_0_Val << AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 2.3V Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_1 (AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_1_Val << AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 2.4V Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_2 (AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_2_Val << AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 2.4V Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_3 (AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_3_Val << AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 2.5V Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_4 (AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_4_Val << AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 2.6V Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_5 (AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_5_Val << AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 2.7V Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_6 (AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_6_Val << AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 2.7V Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_7 (AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_7_Val << AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_VOUT_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 2.8V Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_Pos 13                                             /**< (AON_GP_REGS_RF_PMU_REGS_1) Set the current bias for the EFUSE LDO Position */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_Msk (0x3u << AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Set the current bias for the EFUSE LDO Mask */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL(value) (AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_Msk & ((value) << AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_Pos))
#define   AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 80uA bias current  */
#define   AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 100uA bias current  */
#define   AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_2_Val 0x2u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 120uA bias current  */
#define   AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_3_Val 0x3u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 140uA bias current  */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_0 (AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_0_Val << AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 80uA bias current Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_1 (AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_1_Val << AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 100uA bias current Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_2 (AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_2_Val << AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 120uA bias current Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_3 (AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_3_Val << AON_GP_REGS_RF_PMU_REGS_1_EFUSE_LDO_IBIAS_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 140uA bias current Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_RES_CTRL_Pos 15                                             /**< (AON_GP_REGS_RF_PMU_REGS_1) RTC crystal circuit feedback resistance value Position */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_RES_CTRL_Msk (0x1u << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_RES_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) RTC crystal circuit feedback resistance value Mask */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_RES_CTRL AON_GP_REGS_RF_PMU_REGS_1_PIERCE_RES_CTRL_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_RF_PMU_REGS_1_PIERCE_RES_CTRL_Msk instead */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_RES_CTRL_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 20Mohm resistor  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_RES_CTRL_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 30Mohm resistor  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_RES_CTRL_0 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_RES_CTRL_0_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_RES_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 20Mohm resistor Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_RES_CTRL_1 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_RES_CTRL_1_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_RES_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 30Mohm resistor Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Pos 16                                             /**< (AON_GP_REGS_RF_PMU_REGS_1) Transconductance of RTC oscillator Position */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Msk (0xFu << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Transconductance of RTC oscillator Mask */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL(value) (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Msk & ((value) << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Pos))
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 75nS  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 85nS  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_2_Val 0x2u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 96nS  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_3_Val 0x3u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 106nS  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_4_Val 0x4u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 116nS  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_5_Val 0x5u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 127nS  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_6_Val 0x6u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 137nS  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_7_Val 0x7u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 147nS  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_8_Val 0x8u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 158nS  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_9_Val 0x9u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 168nS  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_10_Val 0xAu                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 178nS  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_11_Val 0xBu                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 189nS  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_12_Val 0xCu                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 199nS  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_13_Val 0xDu                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 209nS  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_14_Val 0xEu                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 220nS  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_15_Val 0xFu                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 230nS  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_0 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_0_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 75nS Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_1 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_1_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 85nS Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_2 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_2_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 96nS Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_3 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_3_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 106nS Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_4 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_4_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 116nS Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_5 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_5_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 127nS Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_6 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_6_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 137nS Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_7 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_7_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 147nS Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_8 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_8_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 158nS Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_9 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_9_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 168nS Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_10 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_10_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 178nS Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_11 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_11_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 189nS Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_12 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_12_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 199nS Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_13 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_13_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 209nS Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_14 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_14_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 220nS Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_15 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_15_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_GM_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 230nS Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Pos 20                                             /**< (AON_GP_REGS_RF_PMU_REGS_1) On chip single ended capacitors for RTC oscillator Position */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Msk (0xFu << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) On chip single ended capacitors for RTC oscillator Mask */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL(value) (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Msk & ((value) << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Pos))
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 0pF  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 1pF  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_2_Val 0x2u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 2pF  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_3_Val 0x3u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 3pF  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_4_Val 0x4u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 4pF  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_5_Val 0x5u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 5pF  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_6_Val 0x6u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 6pF  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_7_Val 0x7u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 7pF  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_8_Val 0x8u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 8pF  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_9_Val 0x9u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 9pF  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_10_Val 0xAu                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 10pF  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_11_Val 0xBu                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 11pF  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_12_Val 0xCu                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 12pF  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_13_Val 0xDu                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 13pF  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_14_Val 0xEu                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 14pF  */
#define   AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_15_Val 0xFu                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) 15pF  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_0 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_0_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 0pF Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_1 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_1_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 1pF Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_2 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_2_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 2pF Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_3 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_3_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 3pF Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_4 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_4_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 4pF Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_5 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_5_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 5pF Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_6 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_6_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 6pF Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_7 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_7_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 7pF Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_8 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_8_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 8pF Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_9 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_9_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 9pF Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_10 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_10_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 10pF Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_11 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_11_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 11pF Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_12 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_12_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 12pF Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_13 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_13_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 13pF Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_14 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_14_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 14pF Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_15 (AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_15_Val << AON_GP_REGS_RF_PMU_REGS_1_PIERCE_CAP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) 15pF Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_CTRL_Pos 24                                             /**< (AON_GP_REGS_RF_PMU_REGS_1) enable input channel time multiplexing to the sensor ADC Position */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_CTRL_Msk (0x1u << AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) enable input channel time multiplexing to the sensor ADC Mask */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_CTRL AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_CTRL_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_CTRL_Msk instead */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_CTRL_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) Conversion is done on the four input channels in a time multiplexed manner  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_CTRL_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) Conversion is done for one specific input channel  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_CTRL_0 (AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_CTRL_0_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Conversion is done on the four input channels in a time multiplexed manner Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_CTRL_1 (AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_CTRL_1_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Conversion is done for one specific input channel Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_Pos 25                                             /**< (AON_GP_REGS_RF_PMU_REGS_1) Input channel selection for the sensor ADC Position */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_Msk (0x7u << AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Input channel selection for the sensor ADC Mask */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL(value) (AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_Msk & ((value) << AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_Pos))
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) GPIO_MS1  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) GPIO_MS2  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_2_Val 0x2u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) GPIO_MS3  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_3_Val 0x3u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) GPIO_MS4  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_4_Val 0x4u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) On Chip Temperature  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_5_Val 0x5u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) VBATT divided by 4 voltage level  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_6_Val 0x6u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) LP_LDO_OUT_1P2 low power domain voltage  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_7_Val 0x7u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) Sensor ADC reference voltage level  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_0 (AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_0_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) GPIO_MS1 Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_1 (AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_1_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) GPIO_MS2 Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_2 (AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_2_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) GPIO_MS3 Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_3 (AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_3_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) GPIO_MS4 Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_4 (AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_4_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) On Chip Temperature Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_5 (AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_5_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) VBATT divided by 4 voltage level Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_6 (AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_6_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) LP_LDO_OUT_1P2 low power domain voltage Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_7 (AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_7_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_SEL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Sensor ADC reference voltage level Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_Pos 28                                             /**< (AON_GP_REGS_RF_PMU_REGS_1) Optional mode to improve sub-ranging technique of the sensor ADC Position */
#define AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_Msk (0x3u << AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Optional mode to improve sub-ranging technique of the sensor ADC Mask */
#define AON_GP_REGS_RF_PMU_REGS_1_CODE_IN(value) (AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_Msk & ((value) << AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_Pos))
#define   AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) input dynamic range from 0V to VBATT voltage level  */
#define   AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) input dynamic range from 0.08*VBATT to 0.92*VBATT  */
#define   AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_2_Val 0x2u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) input dynamic range from 0.17*VBATT to 0.83*VBATT  */
#define   AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_3_Val 0x3u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) input dynamic range from 0.25*VBATT to 0.75*VBATT  */
#define AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_0 (AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_0_Val << AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) input dynamic range from 0V to VBATT voltage level Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_1 (AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_1_Val << AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) input dynamic range from 0.08*VBATT to 0.92*VBATT Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_2 (AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_2_Val << AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) input dynamic range from 0.17*VBATT to 0.83*VBATT Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_3 (AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_3_Val << AON_GP_REGS_RF_PMU_REGS_1_CODE_IN_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) input dynamic range from 0.25*VBATT to 0.75*VBATT Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_Pos 30                                             /**< (AON_GP_REGS_RF_PMU_REGS_1) Comparator biasing current for different sampling rates of the sensor ADC Position */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_Msk (0x3u << AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Comparator biasing current for different sampling rates of the sensor ADC Mask */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL(value) (AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_Msk & ((value) << AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_Pos))
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) Comparator bias current is 4uA  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) Comparator bias current is 8uA  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_2_Val 0x2u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) Comparator bias current is 20uA  */
#define   AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_3_Val 0x3u                                           /**< (AON_GP_REGS_RF_PMU_REGS_1) Comparator bias current is 24uA  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_0 (AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_0_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Comparator bias current is 4uA Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_1 (AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_1_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Comparator bias current is 8uA Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_2 (AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_2_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Comparator bias current is 20uA Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_3 (AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_3_Val << AON_GP_REGS_RF_PMU_REGS_1_SADC_LP_CTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_1) Comparator bias current is 24uA Position  */
#define AON_GP_REGS_RF_PMU_REGS_1_MASK      0xFFFFFFFFu                                    /**< \deprecated (AON_GP_REGS_RF_PMU_REGS_1) Register MASK  (Use AON_GP_REGS_RF_PMU_REGS_1_Msk instead)  */
#define AON_GP_REGS_RF_PMU_REGS_1_Msk       0xFFFFFFFFu                                    /**< (AON_GP_REGS_RF_PMU_REGS_1) Register Mask  */

/* -------- AON_GP_REGS_RF_PMU_REGS_2 : (AON_GP_REGS Offset: 0x408) (R/W 16) RF PMU Registers -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t DIG_CORE_LDO_BYP:1;        /**< bit:      0  Bypass mode of digital core LDO which regulates from the buck converter output to the local power domains of each digital power island */
    uint16_t DIG_CORE_LDO_VCTRL:2;      /**< bit:   1..2  Voltage level of the digital core LDO when LDO is not in bypass mode */
    uint16_t REF_HP_MODE:3;             /**< bit:   3..5  Controls the sensor ADCs internal reference buffer output resistance */
    uint16_t OFFSET_CAL_EN:1;           /**< bit:      6  Enable sensor ADC offset calibration     */
    uint16_t RESERVED_7:1;              /**< bit:      7  not using                                */
    uint16_t CLK_CTRL_26MHZ:5;          /**< bit:  8..12  Control the 26MHz RC oscillator frequency */
    uint16_t RESERVED_15_13:3;          /**< bit: 13..15  not using                                */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} AON_GP_REGS_RF_PMU_REGS_2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_GP_REGS_RF_PMU_REGS_2_OFFSET    0x408                                         /**<  (AON_GP_REGS_RF_PMU_REGS_2) RF PMU Registers  Offset */
#define AON_GP_REGS_RF_PMU_REGS_2_RESETVALUE 0x05u                                         /**<  (AON_GP_REGS_RF_PMU_REGS_2) RF PMU Registers  Reset Value */

#define AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_BYP_Pos 0                                              /**< (AON_GP_REGS_RF_PMU_REGS_2) Bypass mode of digital core LDO which regulates from the buck converter output to the local power domains of each digital power island Position */
#define AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_BYP_Msk (0x1u << AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_BYP_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) Bypass mode of digital core LDO which regulates from the buck converter output to the local power domains of each digital power island Mask */
#define AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_BYP AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_BYP_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_BYP_Msk instead */
#define   AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_BYP_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) Not in bypass mode  */
#define   AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_BYP_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) Bypass mode so output will be shorted to the buck converter output  */
#define AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_BYP_0 (AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_BYP_0_Val << AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_BYP_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) Not in bypass mode Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_BYP_1 (AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_BYP_1_Val << AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_BYP_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) Bypass mode so output will be shorted to the buck converter output Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_Pos 1                                              /**< (AON_GP_REGS_RF_PMU_REGS_2) Voltage level of the digital core LDO when LDO is not in bypass mode Position */
#define AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_Msk (0x3u << AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) Voltage level of the digital core LDO when LDO is not in bypass mode Mask */
#define AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL(value) (AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_Msk & ((value) << AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_Pos))
#define   AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) 0.91V  */
#define   AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) 0.96V  */
#define   AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_2_Val 0x2u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) 1.02V  */
#define   AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_3_Val 0x3u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) 1.09V  */
#define AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_0 (AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_0_Val << AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 0.91V Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_1 (AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_1_Val << AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 0.96V Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_2 (AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_2_Val << AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 1.02V Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_3 (AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_3_Val << AON_GP_REGS_RF_PMU_REGS_2_DIG_CORE_LDO_VCTRL_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 1.09V Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_Pos 3                                              /**< (AON_GP_REGS_RF_PMU_REGS_2) Controls the sensor ADCs internal reference buffer output resistance Position */
#define AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_Msk (0x7u << AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) Controls the sensor ADCs internal reference buffer output resistance Mask */
#define AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE(value) (AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_Msk & ((value) << AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_Pos))
#define   AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) setting for applications that require less than 10KSPS  */
#define   AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) setting for throughputs between 10KSPS and 100KSPS  */
#define   AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_2_Val 0x2u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) setting for 100KSPS  */
#define   AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_3_Val 0x3u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) setting for 325KSPS  */
#define   AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_4_Val 0x4u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) setting for 550KSPS  */
#define   AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_5_Val 0x5u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) setting for 775KSPS  */
#define   AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_6_Val 0x6u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) setting for 1MSPS  */
#define AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_0 (AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_0_Val << AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) setting for applications that require less than 10KSPS Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_1 (AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_1_Val << AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) setting for throughputs between 10KSPS and 100KSPS Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_2 (AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_2_Val << AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) setting for 100KSPS Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_3 (AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_3_Val << AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) setting for 325KSPS Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_4 (AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_4_Val << AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) setting for 550KSPS Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_5 (AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_5_Val << AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) setting for 775KSPS Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_6 (AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_6_Val << AON_GP_REGS_RF_PMU_REGS_2_REF_HP_MODE_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) setting for 1MSPS Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_OFFSET_CAL_EN_Pos 6                                              /**< (AON_GP_REGS_RF_PMU_REGS_2) Enable sensor ADC offset calibration Position */
#define AON_GP_REGS_RF_PMU_REGS_2_OFFSET_CAL_EN_Msk (0x1u << AON_GP_REGS_RF_PMU_REGS_2_OFFSET_CAL_EN_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) Enable sensor ADC offset calibration Mask */
#define AON_GP_REGS_RF_PMU_REGS_2_OFFSET_CAL_EN AON_GP_REGS_RF_PMU_REGS_2_OFFSET_CAL_EN_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_RF_PMU_REGS_2_OFFSET_CAL_EN_Msk instead */
#define   AON_GP_REGS_RF_PMU_REGS_2_OFFSET_CAL_EN_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) Disable  */
#define   AON_GP_REGS_RF_PMU_REGS_2_OFFSET_CAL_EN_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) Enable  */
#define AON_GP_REGS_RF_PMU_REGS_2_OFFSET_CAL_EN_0 (AON_GP_REGS_RF_PMU_REGS_2_OFFSET_CAL_EN_0_Val << AON_GP_REGS_RF_PMU_REGS_2_OFFSET_CAL_EN_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) Disable Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_OFFSET_CAL_EN_1 (AON_GP_REGS_RF_PMU_REGS_2_OFFSET_CAL_EN_1_Val << AON_GP_REGS_RF_PMU_REGS_2_OFFSET_CAL_EN_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) Enable Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_RESERVED_7_Pos 7                                              /**< (AON_GP_REGS_RF_PMU_REGS_2) not using Position */
#define AON_GP_REGS_RF_PMU_REGS_2_RESERVED_7_Msk (0x1u << AON_GP_REGS_RF_PMU_REGS_2_RESERVED_7_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) not using Mask */
#define AON_GP_REGS_RF_PMU_REGS_2_RESERVED_7 AON_GP_REGS_RF_PMU_REGS_2_RESERVED_7_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_RF_PMU_REGS_2_RESERVED_7_Msk instead */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos 8                                              /**< (AON_GP_REGS_RF_PMU_REGS_2) Control the 26MHz RC oscillator frequency Position */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Msk (0x1Fu << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) Control the 26MHz RC oscillator frequency Mask */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ(value) (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Msk & ((value) << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos))
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_0_Val 0x0u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) 12MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_1_Val 0x1u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) 13MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_2_Val 0x2u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) 14MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_3_Val 0x3u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) 15MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_4_Val 0x4u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) 16MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_5_Val 0x5u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) 17MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_6_Val 0x6u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) 18MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_7_Val 0x7u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) 19MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_8_Val 0x8u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) 20MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_9_Val 0x9u                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) 21MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_10_Val 0xAu                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) 22MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_11_Val 0xBu                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) 23MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_12_Val 0xCu                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) 24MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_13_Val 0xDu                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) 25MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_14_Val 0xEu                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) 26MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_15_Val 0xFu                                           /**< (AON_GP_REGS_RF_PMU_REGS_2) 27MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_16_Val 0x10u                                          /**< (AON_GP_REGS_RF_PMU_REGS_2) 28MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_17_Val 0x11u                                          /**< (AON_GP_REGS_RF_PMU_REGS_2) 29MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_18_Val 0x12u                                          /**< (AON_GP_REGS_RF_PMU_REGS_2) 30MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_19_Val 0x13u                                          /**< (AON_GP_REGS_RF_PMU_REGS_2) 31MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_20_Val 0x14u                                          /**< (AON_GP_REGS_RF_PMU_REGS_2) 32MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_21_Val 0x15u                                          /**< (AON_GP_REGS_RF_PMU_REGS_2) 33MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_22_Val 0x16u                                          /**< (AON_GP_REGS_RF_PMU_REGS_2) 34MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_23_Val 0x17u                                          /**< (AON_GP_REGS_RF_PMU_REGS_2) 35MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_24_Val 0x18u                                          /**< (AON_GP_REGS_RF_PMU_REGS_2) 36MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_25_Val 0x19u                                          /**< (AON_GP_REGS_RF_PMU_REGS_2) 37MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_26_Val 0x1Au                                          /**< (AON_GP_REGS_RF_PMU_REGS_2) 38MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_27_Val 0x1Bu                                          /**< (AON_GP_REGS_RF_PMU_REGS_2) 39MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_28_Val 0x1Cu                                          /**< (AON_GP_REGS_RF_PMU_REGS_2) 40MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_29_Val 0x1Du                                          /**< (AON_GP_REGS_RF_PMU_REGS_2) 41MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_30_Val 0x1Eu                                          /**< (AON_GP_REGS_RF_PMU_REGS_2) 42MHz  */
#define   AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_31_Val 0x1Fu                                          /**< (AON_GP_REGS_RF_PMU_REGS_2) 43MHz  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_0 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_0_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 12MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_1 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_1_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 13MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_2 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_2_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 14MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_3 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_3_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 15MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_4 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_4_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 16MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_5 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_5_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 17MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_6 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_6_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 18MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_7 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_7_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 19MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_8 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_8_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 20MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_9 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_9_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 21MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_10 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_10_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 22MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_11 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_11_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 23MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_12 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_12_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 24MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_13 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_13_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 25MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_14 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_14_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 26MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_15 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_15_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 27MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_16 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_16_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 28MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_17 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_17_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 29MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_18 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_18_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 30MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_19 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_19_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 31MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_20 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_20_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 32MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_21 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_21_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 33MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_22 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_22_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 34MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_23 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_23_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 35MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_24 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_24_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 36MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_25 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_25_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 37MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_26 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_26_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 38MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_27 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_27_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 39MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_28 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_28_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 40MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_29 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_29_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 41MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_30 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_30_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 42MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_31 (AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_31_Val << AON_GP_REGS_RF_PMU_REGS_2_CLK_CTRL_26MHZ_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) 43MHz Position  */
#define AON_GP_REGS_RF_PMU_REGS_2_RESERVED_15_13_Pos 13                                             /**< (AON_GP_REGS_RF_PMU_REGS_2) not using Position */
#define AON_GP_REGS_RF_PMU_REGS_2_RESERVED_15_13_Msk (0x7u << AON_GP_REGS_RF_PMU_REGS_2_RESERVED_15_13_Pos)  /**< (AON_GP_REGS_RF_PMU_REGS_2) not using Mask */
#define AON_GP_REGS_RF_PMU_REGS_2_RESERVED_15_13(value) (AON_GP_REGS_RF_PMU_REGS_2_RESERVED_15_13_Msk & ((value) << AON_GP_REGS_RF_PMU_REGS_2_RESERVED_15_13_Pos))
#define AON_GP_REGS_RF_PMU_REGS_2_MASK      0xFFFFu                                        /**< \deprecated (AON_GP_REGS_RF_PMU_REGS_2) Register MASK  (Use AON_GP_REGS_RF_PMU_REGS_2_Msk instead)  */
#define AON_GP_REGS_RF_PMU_REGS_2_Msk       0xFFFFu                                        /**< (AON_GP_REGS_RF_PMU_REGS_2) Register Mask  */

/* -------- AON_GP_REGS_MS_GPIO_MODE : (AON_GP_REGS Offset: 0x410) (R/W 8) Analog Mode Select of Mixed Signal GPIOs -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  ANALOG_ENABLE_44:1;        /**< bit:      0  Active High Analog Mode Enable for Mixed Signal LP_GPIO_44 */
    uint8_t  ANALOG_ENABLE_45:1;        /**< bit:      1  Active High Analog Mode Enable for Mixed Signal LP_GPIO_45 */
    uint8_t  ANALOG_ENABLE_46:1;        /**< bit:      2  Active High Analog Mode Enable for Mixed Signal LP_GPIO_46 */
    uint8_t  ANALOG_ENABLE_47:1;        /**< bit:      3  Active High Analog Mode Enable for Mixed Signal LP_GPIO_47 */
    uint8_t  :4;                        /**< bit:   4..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint8_t  ANALOG_ENABLE_:4;          /**< bit:   0..3  Active High Analog Mode Enable for Mixed Signal LP_GPIO_47 */
    uint8_t  :4;                        /**< bit:   4..7 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint8_t  reg;                         /**< Type used for register access */
} AON_GP_REGS_MS_GPIO_MODE_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_GP_REGS_MS_GPIO_MODE_OFFSET     0x410                                         /**<  (AON_GP_REGS_MS_GPIO_MODE) Analog Mode Select of Mixed Signal GPIOs  Offset */
#define AON_GP_REGS_MS_GPIO_MODE_RESETVALUE 0x0Fu                                         /**<  (AON_GP_REGS_MS_GPIO_MODE) Analog Mode Select of Mixed Signal GPIOs  Reset Value */

#define AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_44_Pos 0                                              /**< (AON_GP_REGS_MS_GPIO_MODE) Active High Analog Mode Enable for Mixed Signal LP_GPIO_44 Position */
#define AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_44_Msk (0x1u << AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_44_Pos)  /**< (AON_GP_REGS_MS_GPIO_MODE) Active High Analog Mode Enable for Mixed Signal LP_GPIO_44 Mask */
#define AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_44 AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_44_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_44_Msk instead */
#define AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_45_Pos 1                                              /**< (AON_GP_REGS_MS_GPIO_MODE) Active High Analog Mode Enable for Mixed Signal LP_GPIO_45 Position */
#define AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_45_Msk (0x1u << AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_45_Pos)  /**< (AON_GP_REGS_MS_GPIO_MODE) Active High Analog Mode Enable for Mixed Signal LP_GPIO_45 Mask */
#define AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_45 AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_45_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_45_Msk instead */
#define AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_46_Pos 2                                              /**< (AON_GP_REGS_MS_GPIO_MODE) Active High Analog Mode Enable for Mixed Signal LP_GPIO_46 Position */
#define AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_46_Msk (0x1u << AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_46_Pos)  /**< (AON_GP_REGS_MS_GPIO_MODE) Active High Analog Mode Enable for Mixed Signal LP_GPIO_46 Mask */
#define AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_46 AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_46_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_46_Msk instead */
#define AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_47_Pos 3                                              /**< (AON_GP_REGS_MS_GPIO_MODE) Active High Analog Mode Enable for Mixed Signal LP_GPIO_47 Position */
#define AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_47_Msk (0x1u << AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_47_Pos)  /**< (AON_GP_REGS_MS_GPIO_MODE) Active High Analog Mode Enable for Mixed Signal LP_GPIO_47 Mask */
#define AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_47 AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_47_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_47_Msk instead */
#define AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE__Pos 0                                              /**< (AON_GP_REGS_MS_GPIO_MODE Position) Active High Analog Mode Enable for Mixed Signal LP_GPIO_47 */
#define AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE__Msk (0xFu << AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE__Pos)  /**< (AON_GP_REGS_MS_GPIO_MODE Mask) ANALOG_ENABLE_ */
#define AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_(value) (AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE__Msk & ((value) << AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE__Pos))  
#define AON_GP_REGS_MS_GPIO_MODE_MASK       0x0Fu                                          /**< \deprecated (AON_GP_REGS_MS_GPIO_MODE) Register MASK  (Use AON_GP_REGS_MS_GPIO_MODE_Msk instead)  */
#define AON_GP_REGS_MS_GPIO_MODE_Msk        0x0Fu                                          /**< (AON_GP_REGS_MS_GPIO_MODE) Register Mask  */

/* -------- AON_GP_REGS_IO_PADS_CONTROL : (AON_GP_REGS Offset: 0x414) (R/W 8) Controls behaviour of IO Pads in Sleep Mode -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  LATCH_ENABLE:1;            /**< bit:      0  Active High Latch Enable of IO Pads configuration parameters. When Low, Pads retain their configured state during sleep mode. */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} AON_GP_REGS_IO_PADS_CONTROL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_GP_REGS_IO_PADS_CONTROL_OFFSET  0x414                                         /**<  (AON_GP_REGS_IO_PADS_CONTROL) Controls behaviour of IO Pads in Sleep Mode  Offset */
#define AON_GP_REGS_IO_PADS_CONTROL_RESETVALUE 0x01u                                         /**<  (AON_GP_REGS_IO_PADS_CONTROL) Controls behaviour of IO Pads in Sleep Mode  Reset Value */

#define AON_GP_REGS_IO_PADS_CONTROL_LATCH_ENABLE_Pos 0                                              /**< (AON_GP_REGS_IO_PADS_CONTROL) Active High Latch Enable of IO Pads configuration parameters. When Low, Pads retain their configured state during sleep mode. Position */
#define AON_GP_REGS_IO_PADS_CONTROL_LATCH_ENABLE_Msk (0x1u << AON_GP_REGS_IO_PADS_CONTROL_LATCH_ENABLE_Pos)  /**< (AON_GP_REGS_IO_PADS_CONTROL) Active High Latch Enable of IO Pads configuration parameters. When Low, Pads retain their configured state during sleep mode. Mask */
#define AON_GP_REGS_IO_PADS_CONTROL_LATCH_ENABLE AON_GP_REGS_IO_PADS_CONTROL_LATCH_ENABLE_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_GP_REGS_IO_PADS_CONTROL_LATCH_ENABLE_Msk instead */
#define AON_GP_REGS_IO_PADS_CONTROL_MASK    0x01u                                          /**< \deprecated (AON_GP_REGS_IO_PADS_CONTROL) Register MASK  (Use AON_GP_REGS_IO_PADS_CONTROL_Msk instead)  */
#define AON_GP_REGS_IO_PADS_CONTROL_Msk     0x01u                                          /**< (AON_GP_REGS_IO_PADS_CONTROL) Register Mask  */

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#if COMPONENT_TYPEDEF_STYLE == 'R'
/** \brief AON_GP_REGS hardware registers */
typedef struct {  /* Always On General Purpose Registers */
  RwReg16 AON_PINMUX_SEL; /**< (AON_GP_REGS Offset: 0x00) Controls the pinmux selection for the AO GPIOs */
  __I  uint8_t  Reserved1[2];
  RwReg   AON_PMU_CTRL;   /**< (AON_GP_REGS Offset: 0x04) Always On Misc Control */
  RwReg8  AON_BLE_LP_CTRL; /**< (AON_GP_REGS Offset: 0x08) Always On BLE LP Control */
  __I  uint8_t  Reserved2[3];
  RwReg   AON_MISC_CTRL;  /**< (AON_GP_REGS Offset: 0x0C) Always On Misc Control */
  RwReg8  AON_GLOBAL_RESET; /**< (AON_GP_REGS Offset: 0x10) Active Low Always On Reset Control */
  __I  uint8_t  Reserved3[3];
  RwReg8  AON_PULL_ENABLE; /**< (AON_GP_REGS Offset: 0x14) Active Low Always On Pull Enable Control */
  __I  uint8_t  Reserved4[7];
  RwReg   AON_RESET_CTRL; /**< (AON_GP_REGS Offset: 0x1C) Reset Count Control for PD1, PD4, PD6 and PD7 */
  RwReg8  AON_BTRIM_ACTIVE; /**< (AON_GP_REGS Offset: 0x20) BTRIM settings for active mode (i.e. not in retention) */
  __I  uint8_t  Reserved5[3];
  RwReg8  AON_BTRIM_RETENTION; /**< (AON_GP_REGS Offset: 0x24) BTRIM settings for retention mode */
  __I  uint8_t  Reserved6[27];
  RwReg8  AON_LPMCU_SCRATCH_PAD; /**< (AON_GP_REGS Offset: 0x40) Usage for the LPMCU for any sort of status it needs to store for itself before it goes to sleep */
  __I  uint8_t  Reserved7[3];
  RwReg8  AON_LPMCU_COLD_BOOT; /**< (AON_GP_REGS Offset: 0x44) To be used by ARM to determine if it is a cold boot or not */
  __I  uint8_t  Reserved8[59];
  RoReg8  AON_BO_OUT_STATUS; /**< (AON_GP_REGS Offset: 0x80) Brown Out Detected (must be cleared manually) */
  __I  uint8_t  Reserved9[3];
  RwReg8  CLEAR_BROWN_OUT_REG; /**< (AON_GP_REGS Offset: 0x84) Set to 1 to clear (hold until 0 read at aon_bo_out_status and then this must be cleared to detect another brown out condition) */
  __I  uint8_t  Reserved10[891];
  RwReg   RF_PMU_REGS_0;  /**< (AON_GP_REGS Offset: 0x400) RF PMU Registers */
  RwReg   RF_PMU_REGS_1;  /**< (AON_GP_REGS Offset: 0x404) RF PMU Registers */
  RwReg16 RF_PMU_REGS_2;  /**< (AON_GP_REGS Offset: 0x408) RF PMU Registers */
  __I  uint8_t  Reserved11[6];
  RwReg8  MS_GPIO_MODE;   /**< (AON_GP_REGS Offset: 0x410) Analog Mode Select of Mixed Signal GPIOs */
  __I  uint8_t  Reserved12[3];
  RwReg8  IO_PADS_CONTROL; /**< (AON_GP_REGS Offset: 0x414) Controls behaviour of IO Pads in Sleep Mode */
} AonGpRegs;

#elif COMPONENT_TYPEDEF_STYLE == 'N'
/** \brief AON_GP_REGS hardware registers */
typedef struct {  /* Always On General Purpose Registers */
  __IO AON_GP_REGS_AON_PINMUX_SEL_Type AON_PINMUX_SEL; /**< Offset: 0x00 (R/W  16) Controls the pinmux selection for the AO GPIOs */
       RoReg8                         Reserved1[0x2];
  __IO AON_GP_REGS_AON_PMU_CTRL_Type  AON_PMU_CTRL;   /**< Offset: 0x04 (R/W  32) Always On Misc Control */
  __IO AON_GP_REGS_AON_BLE_LP_CTRL_Type AON_BLE_LP_CTRL; /**< Offset: 0x08 (R/W   8) Always On BLE LP Control */
       RoReg8                         Reserved2[0x3];
  __IO AON_GP_REGS_AON_MISC_CTRL_Type AON_MISC_CTRL;  /**< Offset: 0x0C (R/W  32) Always On Misc Control */
  __IO AON_GP_REGS_AON_GLOBAL_RESET_Type AON_GLOBAL_RESET; /**< Offset: 0x10 (R/W   8) Active Low Always On Reset Control */
       RoReg8                         Reserved3[0x3];
  __IO AON_GP_REGS_AON_PULL_ENABLE_Type AON_PULL_ENABLE; /**< Offset: 0x14 (R/W   8) Active Low Always On Pull Enable Control */
       RoReg8                         Reserved4[0x7];
  __IO AON_GP_REGS_AON_RESET_CTRL_Type AON_RESET_CTRL; /**< Offset: 0x1C (R/W  32) Reset Count Control for PD1, PD4, PD6 and PD7 */
  __IO AON_GP_REGS_AON_BTRIM_ACTIVE_Type AON_BTRIM_ACTIVE; /**< Offset: 0x20 (R/W   8) BTRIM settings for active mode (i.e. not in retention) */
       RoReg8                         Reserved5[0x3];
  __IO AON_GP_REGS_AON_BTRIM_RETENTION_Type AON_BTRIM_RETENTION; /**< Offset: 0x24 (R/W   8) BTRIM settings for retention mode */
       RoReg8                         Reserved6[0x1B];
  __IO AON_GP_REGS_AON_LPMCU_SCRATCH_PAD_Type AON_LPMCU_SCRATCH_PAD; /**< Offset: 0x40 (R/W   8) Usage for the LPMCU for any sort of status it needs to store for itself before it goes to sleep */
       RoReg8                         Reserved7[0x3];
  __IO AON_GP_REGS_AON_LPMCU_COLD_BOOT_Type AON_LPMCU_COLD_BOOT; /**< Offset: 0x44 (R/W   8) To be used by ARM to determine if it is a cold boot or not */
       RoReg8                         Reserved8[0x3B];
  __I  AON_GP_REGS_AON_BO_OUT_STATUS_Type AON_BO_OUT_STATUS; /**< Offset: 0x80 (R/    8) Brown Out Detected (must be cleared manually) */
       RoReg8                         Reserved9[0x3];
  __IO AON_GP_REGS_CLEAR_BROWN_OUT_REG_Type CLEAR_BROWN_OUT_REG; /**< Offset: 0x84 (R/W   8) Set to 1 to clear (hold until 0 read at aon_bo_out_status and then this must be cleared to detect another brown out condition) */
       RoReg8                         Reserved10[0x37B];
  __IO AON_GP_REGS_RF_PMU_REGS_0_Type RF_PMU_REGS_0;  /**< Offset: 0x400 (R/W  32) RF PMU Registers */
  __IO AON_GP_REGS_RF_PMU_REGS_1_Type RF_PMU_REGS_1;  /**< Offset: 0x404 (R/W  32) RF PMU Registers */
  __IO AON_GP_REGS_RF_PMU_REGS_2_Type RF_PMU_REGS_2;  /**< Offset: 0x408 (R/W  16) RF PMU Registers */
       RoReg8                         Reserved11[0x6];
  __IO AON_GP_REGS_MS_GPIO_MODE_Type  MS_GPIO_MODE;   /**< Offset: 0x410 (R/W   8) Analog Mode Select of Mixed Signal GPIOs */
       RoReg8                         Reserved12[0x3];
  __IO AON_GP_REGS_IO_PADS_CONTROL_Type IO_PADS_CONTROL; /**< Offset: 0x414 (R/W   8) Controls behaviour of IO Pads in Sleep Mode */
} AonGpRegs;

#else /* COMPONENT_TYPEDEF_STYLE */
#error Unknown component typedef style
#endif /* COMPONENT_TYPEDEF_STYLE */

#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/** @}*/


#endif /* _SAMB11_AON_GP_REGS_COMPONENT_ */
