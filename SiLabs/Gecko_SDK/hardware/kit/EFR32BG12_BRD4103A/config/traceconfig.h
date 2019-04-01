/***************************************************************************//**
 * @file
 * @brief Provide SWO/ETM TRACE configuration parameters.
 * @version 5.1.0
 *******************************************************************************
 * @section License
 * <b>Copyright 2017 Silicon Laboratories, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef TRACECONFIG_H
#define TRACECONFIG_H

#define BSP_TRACE_SWO_LOCATION GPIO_ROUTELOC0_SWVLOC_LOC0

/* Enable output on pin - GPIO Port F, Pin 2. */
#define TRACE_ENABLE_PINS()                        \
  GPIO->P[5].MODEL &= ~(_GPIO_P_MODEL_MODE2_MASK); \
  GPIO->P[5].MODEL |= GPIO_P_MODEL_MODE2_PUSHPULL

#define BSP_ETM_TRACE              /* This board supports ETM trace. */
#define BSP_TRACE_ETM_CLKLOC     0 /* ETM_TCLK = PF8  */
#define BSP_TRACE_ETM_TD0LOC     0 /* ETM_TD0  = PF9  */
#define BSP_TRACE_ETM_TD1LOC     0 /* ETM_TD1  = PF10 */
#define BSP_TRACE_ETM_TD2LOC     0 /* ETM_TD2  = PF11 */
#define BSP_TRACE_ETM_TD3LOC     0 /* ETM_TD3  = PF12 */

#endif
