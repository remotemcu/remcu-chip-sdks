/* This source file is part of the ATMEL QTouch Library Release 5.1 */

/**
 * \file
 *
 * \brief  This file contains the SAM4L QTouch Library pin, register and sensors
 * configuration options for Capacitive Touch acquisition using the CATB module.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef TOUCH_CONFIG_SAM4L_H
#define TOUCH_CONFIG_SAM4L_H

#ifdef __cplusplus
extern "C"
{
#endif

/*----------------------------------------------------------------------------
                            compiler information
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                include files
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                    macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                   acquisition method manifest constants
----------------------------------------------------------------------------*/
/*! \name Acquisition method manifest constants.
 * \brief The following constants can be used to select the desired Touch
 * acquisition methods to be used with the SAM4L QTouch Library.  Choose QTouch,
 * and Autonomous QTouch methods by setting the corresponding macro to 1.
 */
//! When 1, QTouch Group A method acquisition is used.
//! When 0, QTouch Group A method acquisition is not used.
#define DEF_TOUCH_QTOUCH		        (1)

//! When 1, Autonomous QTouch method acquisition is used.
//! When 0, Autonomous QTouch method acquisition is not used.
#define DEF_TOUCH_AUTONOMOUS_QTOUCH     (1)

/**
 * Enable/Disable QDebug for touch debug information communication with
 * QTouch Studio PC Software.
 *  When 1, QDebug debug data communication to QTouch Studio is enabled.
 *  When 0, QDebug debug data communication to QTouch Studio is disabled.
 */
#define DEF_TOUCH_QDEBUG_ENABLE_QT      (0)
#define DEF_TOUCH_QDEBUG_ENABLE_AT      (0)
#define DEF_TOUCH_QDEBUG_ENABLE         (DEF_TOUCH_QDEBUG_ENABLE_AT  || \
                                         DEF_TOUCH_QDEBUG_ENABLE_QT)
#if DEF_TOUCH_QDEBUG_ENABLE == 1
#define _DEBUG_INTERFACE_
#endif
/*----------------------------------------------------------------------------
                QTouch Pin Configuration Options.
----------------------------------------------------------------------------*/
/* QTouch method is selected. */
#if DEF_TOUCH_QTOUCH == 1

/*! \name QTouch Pin Configuration Options.
 */
//! @{

/**
 * QTouch Sensor pins's selected.
 * Specify the Sensor pins's to be used for QTouch, seperated by a comma.
 * Refer qt_sensor_pin_options_t enum in touch_api_sam4l.h file.
 *
 * NOTE: DO NOT INCLUDE BRACKETS (), SINCE THIS MACRO IS BEING PLACED
 * INSIDE AN ARRAY.
 */
#define QT_SENSOR_PINS_SELECTED        SP_PB04, SP_PA04, SP_PA05, SP_PB02

/**
 * QTouch Number of Sensor pins's.
 * Specify the Total number of Sensor pins's selected using the
 * QT_SENSOR_PINS_SELECTED macro.
 */
#define QT_NUM_SENSOR_PINS_SELECTED    (4u)

/**
 * QTouch Discharge pin selected.
 * Specify the Discharge pins to be used for QTouch.
 * Refer qt_discharge_pin_options_t enum in touch_api_sam4l.h file.
 */
#define QT_DISCHARGE_PIN_SELECTED      (DIS_PB03)

//! @}

/*----------------------------------------------------------------------------
                     QTouch Sensor Configuration options.
----------------------------------------------------------------------------*/
/*! \name QTouch Sensor Configuration options.
 */
//! @{

/**
 * QTouch number of Sensors.
 * Specify the number of QTouch touch sensors to be used by the Touch Library.
 * A sensor is either a key, rotor or slider.
 * Example configuration: If the configuration has 6 keys (a key is formed
 * using one Sensor Pin), one rotor (a QTouch rotor is formed using 3 Sensor
 * Pins) and one slider (a QTouch slider is formed using 3 Sensor Pins), then
 * the number of sensors is 6 key + 1 rotor + 1 slider = 8 sensors.
 * Range: 1u to QT_NUM_SENSOR_PINS_SELECTED.
 */
#define QT_NUM_SENSORS                 (2u)

/**
 * QTouch number of Rotors and Sliders.
 * Specify the total number of QTouch Rotors and Sliders to be used by
 * the Touch Library.  The number of Rotors and Sliders mentioned here is part of
 * the Total number of sensors specified in the QT_NUM_SENSORS macro.  When
 * no rotors or slider are required, specify a value of 0u.
 */
#define QT_NUM_ROTORS_SLIDERS          (1u)

//! @}

/*----------------------------------------------------------------------------
           QTouch Clock and Register Configuration Options.
----------------------------------------------------------------------------*/
/*! \name QTouch Clock and Register Configuration Options.
 */
//! @{

/**
 * CATB Clock Acquisition Clock Source Select
 * 0: The RC oscillator is selected as acquisition clock and is used as timing
 * source for the measurements.
 * 1: The GCLK is selected as acquisition clock and is used as the timing
 * source for measurements.
 */
#define QT_CLOCK_SEL			(0u)

/**
 * CATB Discharge time.
 * Select the Number of CATB Acquisition clock cycles to provide time to
 * Discharge.
 */
#define QT_DISCHARGET			(1000u)

/**
 * CATB Charge time.
 * Select the Number of CATB Acquisition clock cycles to provide time to
 * Charge.The measured capacitance is charged for 2^(CHARGET) clcok cycles of 
 * the acquisition clock(selected with CKSEL) before each discharge measurement. 
 */
#define QT_CHARGET			(0u)

/**
 * CATB Repeat measurements.
 * Select the Number of times acquisition should be repeated.
 * Range: 0u to 8u.
 */
#define QT_REPEAT			(3u)



//! @}

/*----------------------------------------------------------------------------
                  QTouch DMA Channel Options.
----------------------------------------------------------------------------*/
/*! \name QTouch DMA Channel Options.
 */
//! @{

/**
 * QTouch DMA Channel 0.
 * Specify the DMA Channel option 0 to be used by the CATB module to transfer
 * Sensor configuration data from memory to CATB registers..
 * Range: 0u to 11u.
 */
#define QT_DMA_CHANNEL_0               (0u)

/**
 * QTouch DMA Channel 0.
 * Specify the DMA Channel option 0 to be used by the CAT module to transfer
 * Sensor configuration data from CATB registers to memory.
 * Range: 0u to 11u.
 */
#define QT_DMA_CHANNEL_1               (1u)

//! @}

/*----------------------------------------------------------------------------
               QTouch Global acquisition parameters.
----------------------------------------------------------------------------*/
/*! \name QTouch Global acquisition parameters.
 * Refer the Touch Library User guide for more information on these parameters.
 */
//! @{

/**
 * QTouch Sensor detect integration (DI) limit.
 * Range: 0u to 255u.
 */
#define QT_DI                          (4u)

/**
 * QTouch Sensor negative drift rate.
 * Units: 200ms
 * Default value: 20u = 4 seconds.
 * Range: 1u to 127u.
 */
#define QT_NEG_DRIFT_RATE              (20u)

/**
 * QTouch Sensor positive drift rate.
 * Units: 200ms
 * Default value: 5u = 1 second.
 * Range: 1u to 127u.
 */
#define QT_POS_DRIFT_RATE              (5u)

/**
 * QTouch Sensor maximum on duration.
 * Units: 200ms (Example: a value 5u indicated Max ON duration of 1 second.)
 * Default value: 0 (No maximum ON time limit).
 * Range: 0u to 255u.
 */
#define QT_MAX_ON_DURATION             (0u)

/**
 * QTouch Sensor drift hold time.
 * Units: 200ms
 * Default value: 20 (hold off drifting for 4 seconds after leaving detect).
 * Range: 1u to 255u.
 */
#define QT_DRIFT_HOLD_TIME             (20u)

/**
 * QTouch Positive Recalibration delay.
 * Default value: 10.
 * Range: 1u to 255u.
 */
#define QT_POS_RECAL_DELAY             (10u)

/**
 * QTouch Sensor recalibration threshold.
 * Default: RECAL_50 (recalibration threshold = 50% of detection threshold).
 * Range: refer recal_threshold_t enum in touch_api_sam4l.h.
 */
#define QT_RECAL_THRESHOLD             (RECAL_50)

//! @}

/*----------------------------------------------------------------------------
                    QTouch Callback functions.
----------------------------------------------------------------------------*/
/*! \name  QTouch Callback functions.
 */
//! @{

/**
 * QTouch Filter callback function.
 * A filter callback (when not NULL) is called by the Touch Library each time
 * a new set of Signal values are available.
 * An Example filter callback function prototype.
 * void qt_filter_callback( touch_filter_data_t *p_filter_data );
 */
#define QT_FILTER_CALLBACK             (NULL)

//! @}
#endif				/* end of #if DEF_TOUCH_QTOUCH. */

/*----------------------------------------------------------------------------
                    Autonomous QTouch notes.
----------------------------------------------------------------------------*/
/* Autonomous QTouch method is selected. */
#if DEF_TOUCH_AUTONOMOUS_QTOUCH == 1


/*----------------------------------------------------------------------------
                Autonomous QTouch Pin Configuration Options.
----------------------------------------------------------------------------*/
/**
 * Autonomous QTouch Sensor Pin selected.
 * Specify the Sense pair to be used for Autonomous QTouch.
 * Refer qt_sensor_pin_options_t enum in touch_api_sam4l.h file.
 */
#define AT_SP_SELECTED                 (SP_PB04)

/**
 * Autonomous QTouch Discharge pin selected.
 * Specify the Discharge pins to be used for QTouch.
 * Refer qt_discharge_pin_options_t enum in touch_api_sam4l.h file.
 */
#define AT_DISCHARGE_PIN_SELECTED      (DIS_PB03)
/*----------------------------------------------------------------------------
              Autonomous QTouch Clock and Register Configuration Options.
----------------------------------------------------------------------------*/
/*! \name Autonomous QTouch Clock and Register Configuration Options.
 */
//! @{

/**
 * CATB Clock Acquisition Clock Source Select
 * 0: The RC oscillator is selected as acquisition clock and is used as timing
 * source for the measurements.
 * 1: The GCLK is selected as acquisition clock and is used as the timing
 * source for measurements.
 */
#define AT_CLOCK_SEL			(0u)

/**
 * CATB Discharge time.
 * Select the Number of CATB Acquisition clock cycles to provide time to
 * Discharge.
 */
#define AT_DISCHARGET			(2000000u)

/**
 * CATB Charge time.
 * Select the Number of CATB Acquisition clock cycles to provide time to
 * Charge.
 */
#define AT_CHARGET			(0u)

/**
 * CATB Repeat measurements.
 * Select the Number of times acquisition should be repeated.
 * Range: 0u to 8u.
 */
#define AT_REPEAT			(0u)

/**
 * Enable/Disable Spread Spectrum based acquisition.
 */
#define AT_SPREAD			(0u)

#define AT_THRESHOLD			(15u)
/**
 * QTouch Sensor detect integration (DI) limit.
 * Range: 0u to 255u.
 */
#define AT_DI			        (3u)


//! @}

#endif				/* end of #if DEF_TOUCH_AUTONOMOUS_QTOUCH. */

#ifdef __cplusplus
}
#endif

#endif				/* TOUCH_CONFIG_SAM4L_H */
/* EOF */
