/* This source file is part of the ATMEL QTouch Library Release 5.1 */

/**
 * \file
 *
 * \brief QTouch example for SAM4L.
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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

/*----------------------------------------------------------------------------
                            compiler information
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                include files
----------------------------------------------------------------------------*/
//#include "asf.h"

/**
 * Includes for Touch Library.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include "touch_api_sam4l.h"

#if DEF_TOUCH_QDEBUG_ENABLE == 1
  /**
   * Includes for Touch Debug interface.
   */
#include "QDebug_sam4l.h"
#endif

/*----------------------------------------------------------------------------
                            manifest constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                    macros
----------------------------------------------------------------------------*/
//! This macro indicates how often a new touch measurement must be done.
#define TOUCH_MEASUREMENT_PERIOD_MS     (32u)

/*----------------------------------------------------------------------------
                            type definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                            Structure Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                global variables
----------------------------------------------------------------------------*/
//! QTouch Library Timing info.
touch_qt_time_t touch_qt_time;

//! QTouch measured data pointer.
touch_measure_data_t *p_qt_measure_data = NULL;

/**
 * Flag set by touch_at_status_change_interrupt_callback() function when a fresh Touch
 * status is available.
 */
volatile int8_t autonomous_qtouch_in_touch = 0;

/*----------------------------------------------------------------------------
                                extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                callback functions
----------------------------------------------------------------------------*/
/*! \brief Autonomous QTouch Group status change callback function example prototype.
 */
static void touch_at_status_change_interrupt_callback (touch_at_status *
						       p_at_status);
/*----------------------------------------------------------------------------
                                static variables
----------------------------------------------------------------------------*/
/**
 * QTouch Library Data block provided as input to Touch library.
 */
static uint8_t qt_data_blk[PRIV_QT_DATA_BLK_SIZE];

/**
 * QTouch Library Sensor Pins Info.
 */
static uint8_t sensor_pins[QT_NUM_SENSOR_PINS_SELECTED] = 
{
  QT_SENSOR_PINS_SELECTED
};

/**
 * QTouch Library Configuration structure provided as input to Touch Library.
 *
 * Note: Use the touch_config_sam4l.h configuration header file to fill in
 * the elements of this structure.  DO NOT modify any of the input values
 * directly in this structure.
 */
static touch_qt_config_t qt_config = {
  QT_NUM_CHANNELS,		/* QTouch Library number of channels. */
  QT_NUM_SENSORS,		/* QTouch Library number of sensors. */
  QT_NUM_ROTORS_SLIDERS,	/* QTouch Library number of rotors and sliders. */
  /* QTOUCH Library PIN CONFIGURATION INFO. */
  {
    sensor_pins,		/* QTouch Library Sensor Pins selected. */
    QT_NUM_SENSOR_PINS_SELECTED,
    QT_DISCHARGE_PIN_SELECTED
  },
  /* QTOUCH Library REGISTER CONFIGURATION INFO. */
  /* Refer CAT User Interface section in
     datasheet. */
  /* TOUCH LIBRARY WILL SHIFT THE VALUE
     SPECIFIED BELOW TO THE REQUIRED
     REGISTER OFFSET */
  {
   QT_CLOCK_SEL,		/* uint16_t div; TGxCFG0 Register. */
   QT_CHARGET,			/* uint8_t  selen; TGxCFG0 Register. */
   QT_REPEAT,			/* uint8_t  dishift; TGxCFG1 Register. */
   0,               //QT_SPREAD	                /* uint8_t  sync; TGxCFG1 Register. */
   QT_DISCHARGET,		/* uint8_t  chlen; TGxCFG0 Register. */
  },
  /* QTOUCH Library GLOBAL SENSOR CONFIGURATION INFO. */
  {
   QT_DI,			/* uint8_t  di; Sensor detect integration (DI) limit. */
   /* Interchanging Negative and Positive Drift rate, since Signal increases on Touch. */
   QT_POS_DRIFT_RATE,		/* uint8_t  neg_drift_rate; Sensor negative drift rate. */
   QT_NEG_DRIFT_RATE,		/* uint8_t  pos_drift_rate; Sensor positive drift rate. */
   QT_MAX_ON_DURATION,		/* uint8_t  max_on_duration; Sensor maximum on duration. */
   QT_DRIFT_HOLD_TIME,		/* uint8_t  drift_hold_time; Sensor drift hold time. */
   QT_POS_RECAL_DELAY,		/* uint8_t  pos_recal_delay; Sensor positive recalibration delay. */
   QT_RECAL_THRESHOLD,		/* recal_threshold_t recal_threshold; Sensor recalibration threshold. */
   },
  qt_data_blk,			/* QTouch Library data block index. */
  PRIV_QT_DATA_BLK_SIZE,	/* QTouch Library data block size. */
  QT_FILTER_CALLBACK		/* QTouch Library filter callback function pointer. */
};

/**
 * Autonomous QTouch Configuration structure provided as input to Touch Library.
 *
 * Note: Use the touch_config_sam4l.h configuration header file to fill in
 * the elements of this structure.  DO NOT modify any of the input values
 * directly in this structure. */
static touch_at_config_t at_config = {
  {
   AT_SP_SELECTED, 	        /* Autonomous Touch Sense pair selected. */
   AT_DISCHARGE_PIN_SELECTED
  },
  {
   AT_REPEAT,
   AT_SPREAD,
   AT_THRESHOLD,
   AT_DI,
   AT_CHARGET,
   AT_CLOCK_SEL,
   0,              //AT_ESAMPLES
   0x004u,         //AT_TIDLE
   0x800u,          //AT_TLEVEL
   AT_DISCHARGET
  },
  touch_at_status_change_interrupt_callback
};

/**
 * Touch Library input configuration structure.
 */
touch_config_t touch_config = {
  &qt_config, 			/* Pointer to QTouch Library configuration structure. */
  &at_config,			/* Pointer to Autonomous Touch configuration structure. */    
};

/*----------------------------------------------------------------------------
                                prototypes
----------------------------------------------------------------------------*/
/*! \brief configure keys, rotors and sliders.
 */
static touch_ret_t touch_sensors_config (void);

/*! \brief QTouch Library measure complete callback function example prototype.
 */
static void touch_qt_measure_complete_callback ( void );

/*----------------------------------------------------------------------------
  static functions
----------------------------------------------------------------------------*/

/*! \brief Example application entry function.
 */
touch_ret_t
touch_sensors_init (void)
{

  touch_ret_t touch_ret = TOUCH_SUCCESS;

  touch_qt_time.measurement_period_ms = TOUCH_MEASUREMENT_PERIOD_MS;

  /* Initialize touch library and sam4l cat module for QTouch Library operation. */
  touch_ret = touch_qt_sensors_init (&touch_config);
  if (touch_ret != TOUCH_SUCCESS)
    {
      while (1u);		/* Check API Error return code. */
    }

#if DEF_TOUCH_QDEBUG_ENABLE == 1
  /* Initialize the debug interface. */
  QDebug_Init ();
#endif

  /* configure the touch library sensors. */
  touch_ret = touch_sensors_config ();
  if (touch_ret != TOUCH_SUCCESS)
    {
      while (1u);		/* Check API Error return code. */
    }

  /* Initialize touch sensing. */
  touch_ret = touch_qt_sensors_calibrate ();
  if (touch_ret != TOUCH_SUCCESS)
    {
      while (1u);		/* Check API Error return code. */
    }

  
  // Set up CATB interrupt handler
  NVIC_ClearPendingIRQ(CATB_IRQn);
  NVIC_SetPriority(CATB_IRQn,0);
  NVIC_EnableIRQ(CATB_IRQn);
              
  return (touch_ret);

}

touch_ret_t
touch_sensors_measure (void)
{
  touch_ret_t touch_ret = TOUCH_SUCCESS;
  touch_qt_dma_t qt_dma_ch;

  /* Provide the dma channels to be used by the CATB module.  For each
     acquisition cycle, any different two different dma channel can be provided.
     The touch library can handle different dma channels for each call of the
     touch_qt_sensors_start_acquisition API. */
  qt_dma_ch.dma_ch1 = QT_DMA_CHANNEL_0;
  qt_dma_ch.dma_ch2 = QT_DMA_CHANNEL_1;

  /* Process touch library events. The touch_event_dispatcher API needs to
     be called as frequently as possible in order to have a good touch response. */
  touch_event_dispatcher ();

  if (touch_qt_time.time_to_measure_touch == 1u)
  {
    /* Clear flag: it's time to measure touch */
    touch_qt_time.time_to_measure_touch = 0u;

    /* Start a touch sensors measurement process. */
    touch_ret = touch_qt_sensors_start_acquisition (touch_qt_time.current_time_ms,
                                                    qt_dma_ch,
                                                    NORMAL_ACQ_MODE,
                                                    touch_qt_measure_complete_callback);
    if ((touch_ret != TOUCH_SUCCESS) &&
            (touch_ret != TOUCH_ACQ_INCOMPLETE))
    {
      while (1);
      /* Reaching this point can be due to -
             1. The api has retured an error due to a invalid input parameter.
             2. The api has been called during a invalid Touch Library state. */
    }
  }


  if (touch_qt_time.measurement_done_touch == 1u)
  {
    /* Clear flag: QTouch Library measurement complete. */
    touch_qt_time.measurement_done_touch = 0u;
    
    /* Use Touch Status. */
    //uint8_t touch_status_sensor0 = GET_SENSOR_STATE(SENSOR_NUMBER);
    
    /* Use Rotor/Slider Position. */
    //uint8_t rotor_slider_position = GET_ROTOR_SLIDER_POSITION(ROTOR_SLIDER_NUMBER);
    
#if DEF_TOUCH_QDEBUG_ENABLE == 1
    /* QT600 two-way QDebug communication application Example. */
    /* Process any commands received from QTouch Studio. */
    QDebug_ProcessCommands ();

    /* Send out the Touch debug information data each time when Touch
           measurement process is completed .

           The Touch Signal and Touch Delta values are always sent.
           Touch Status change, Rotor-Slider Position change and Sensor Reference
           values can be optionally sent using the masks below.
           */
    QDebug_SendData ( TOUCH_CHANNEL_REF_CHANGE |
                      TOUCH_ROTOR_SLIDER_POS_CHANGE |
                      TOUCH_STATUS_CHANGE );
#endif
  }


  return (touch_ret);
}

/*! \brief Example configuration for touch keys, rotors and sliders.
 *
 * \retval TOUCH_SUCCESS   Configuration setting successful.
 * \retval TOUCH_INVALID_xx   Invalid input configuration setting.
 */
touch_ret_t
touch_sensors_config (void)
{
  touch_ret_t touch_ret = TOUCH_SUCCESS;
  sensor_id_t sensor_id;

  /* configure touch key. */
  touch_ret =
    touch_qt_sensor_config (SENSOR_TYPE_KEY, (channel_t) 0u,
			    (channel_t) 0u, NO_AKS_GROUP, 15u, HYST_6_25,
			    RES_1_BIT, &sensor_id);
  if (touch_ret != TOUCH_SUCCESS)
    {
      while (1);		/* Check API Error return code. */
    }  


  touch_ret =
    touch_qt_sensor_config (SENSOR_TYPE_SLIDER,
			    (channel_t) 1u, (channel_t) 3u, NO_AKS_GROUP, 12u,
			    (hysteresis_t) HYST_6_25, RES_8_BIT, &sensor_id);
  if (touch_ret != TOUCH_SUCCESS)
    {
      while (1);		/* Check API Error return code. */
    }
  
  return (touch_ret);
}

void
touch_sensors_deinit (void)
{
  touch_qt_deinit();
}

/*! \brief This API is used to enable Autonomous QTouch Sensor that can
 * be used to Wakeup the CPU from Deep-Sleep modes.
 * \return touch_ret_t: QTouch Library Error status.
 */
touch_ret_t 
touch_autonomous_sensor_enable (void)
{
  touch_ret_t touch_ret = TOUCH_SUCCESS;
  
  touch_ret =  
  touch_at_sensor_enable( &touch_config );
  
  if (touch_ret != TOUCH_SUCCESS)
    {
      while (1);		/* Check API Error return code. */
    }
  
  return (touch_ret);  
}

/*! \brief This API is used to disable Autonomous QTouch Sensor.
 * \return touch_ret_t: QTouch Library Error status.
 */
void touch_autonomous_sensor_disable (void)
{
    touch_at_sensor_disable();
}
  
/*! \brief QTouch Library measure complete callback function.
 *
 * This function is called by the library when the touch measurement
 * process for QTouch Library sensors is completed.
 *
 * \note A touch_qt_measure_complete_callback() call signifies that fresh
 * values of touch status, rotor/slider position, measured signals,
 * references and Sensor data is available.
 * The QTouch Library measured data can be accessed using the p_measure_data
 * pointer.
 */
void
touch_qt_measure_complete_callback ( void )
{

  if(!(p_qt_measure_data->acq_status & TOUCH_BURST_AGAIN))
  {
      /* Set the QMatrix measurement done flag. */
      touch_qt_time.measurement_done_touch = 1u;
  }

}

/*! \brief Autonomous QTouch status change interrupt callback function.
 * This callback function is called by the Touch library in the
 * CAT Autonomous QTouch status change Interrupt context, each time
 * there is a status change in the Autonomous Touch sensor.
 *
 * \param  p_at_status: Autonomous QTouch status.
 *         p_at_status->status_change: Autonomous QTouch status change.
 * \note   1. CAUTION - This callback function is called in the CAT Autonomous
 * QTouch Status change INTERRUPT SERVICE ROUTINE by the Touch Library.
 * 2. The Autonomous QTouch Status change callback is called both for
 * an IN_TOUCH status change and an OUT_OF_TOUCH status change.
 */
void
touch_at_status_change_interrupt_callback (touch_at_status * p_at_status)
{
  if (p_at_status->status_change == IN_TOUCH)
    {
      autonomous_qtouch_in_touch = 1u;
    }
  else /* p_at_status->status_change == OUT_OF_TOUCH */
    {
      autonomous_qtouch_in_touch = 0u;

    }
}

/*! \brief QTouch Library time update function.
 * Note: This function is called in an ISR.
 */
void 
touch_sensors_update_time (void)
{
  /* update the current time */
  touch_qt_time.current_time_ms += touch_qt_time.measurement_period_ms;

  /* set flag: it's time to measure touch */
  touch_qt_time.time_to_measure_touch = 1u;
}

