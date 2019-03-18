/**
 * \file
 *
 * \brief Common Sensor Service Proximity Sensor Gesture Recognition Example
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

/**
 * \mainpage
 *
 * \section intro Introduction
 *
 * This application demonstrates the use of a multi-channel proximity sensor
 * to identify the movement direction of a physical gesture.  Typically,
 * this will be a hand or other object moving from side to side within
 * the detection range of a sensor installed on an Atmel Sensors Xplained
 * board.  The application sets up an event handler with a proximity
 * threshold, then places the microcontroller in a low-power sleep state.
 * When the proximity threshold is detected, the system wakes up, and
 * the channels of the proximity are repeatedly measured.  Based on the
 * sequence of the individual channels exceeding their thresholds, the
 * direction of motion of the gesture object is indicated.
 * The system then re-enters the sleep mode, and the wake/sleep cycle
 * repeats indefinitely.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com/design-centers/8-bit">Atmel AVR</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <stdio.h>
#include <asf.h>
#include <led.h>

/* Configuration Constants */

#define USE_PRINTF          (true) /* If true, output results via serial
	                            * terminal */
#define PROX_SAMPLE_RATE    (100)  /* Proximity sensor sample rate (Hz) */

#define SET_PROX_THRESHOLD  (true) /* If true, manually set proximity
	                            * threshold */
#define PROX_THRESHOLD      (100)  /* Manual prox sensor threshold for "near" */

#define SET_PROX_CURRENT    (true) /* If true, manually set proximity current */
#define PROX_CURRENT_mA     (150)  /* Current for proximity sensor LEDs (mA) */

#if UC3
/* UC3 Sleep Mode to use, one of: */
/*   SLEEPMGR_ACTIVE, SLEEPMGR_IDLE, SLEEPMGR_FROZEN, SLEEPMGR_STDBY, */
/*   SLEEPMGR_STOP, SLEEPMGR_DEEPSTOP, SLEEPMGR_STATIC, */
/*   SLEEPMGR_SHUTDOWN (UC3L only) */
#  define SLEEP_MODE     (SLEEPMGR_FROZEN)   /* sleep mode to use */
#elif XMEGA
/* XMega Sleep Mode to use, one of: */
/*   SLEEPMGR_ACTIVE, SLEEPMGR_IDLE, SLEEPMGR_ESTDBY, SLEEPMGR_PSAVE, */
/*   SLEEPMGR_STDBY, SLEEPMGR_PDOWN */
#  define SLEEP_MODE     (SLEEPMGR_IDLE)     /* sleep mode to use */
#endif

/* LED definitions */
#if (BOARD == UC3_L0_XPLAINED) || \
	(BOARD == XMEGA_B1_XPLAINED)
#  define UP_LED     LED0
#  define DOWN_LED   LED1
#  define LEFT_LED   LED2
#  define RIGHT_LED  LED3
#elif (BOARD == UC3_A3_XPLAINED) || \
	(BOARD == XMEGA_A3BU_XPLAINED)
#  define UP_LED     LED0
#  define DOWN_LED   LED1
#  define LEFT_LED   LED3
#  define RIGHT_LED  LED2
#elif (BOARD == XMEGA_A1_XPLAINED)
#  define UP_LED     LED0
#  define DOWN_LED   LED3
#  define LEFT_LED   LED2
#  define RIGHT_LED  LED6
#endif

#define ERR_BLINK_COUNT  (2)    /* Number of times to blink LEDs on error */

/** Strings to display based on gesture direction */
static const char *const direction_labels[5] = {
	"Unknown",
	"Up     ",
	"Down   ",
	"Left   ",
	"Right  "
};

/** Direction code values */
typedef enum {
	UNK   = 0,              /* Unknown - unable to determine direction */
	UP    = 1,              /* Up */
	DOWN  = 2,              /* Down */
	LEFT  = 3,              /* Left */
	RIGHT = 4               /* Right */
} direction_t;

/** Direction lookup table of start_channels (rows) x end_channels (columns) */
direction_t dir_tbl[8][8] =
	//  none    1      2      1+2     3     1+3    2+3    1+2+3
	// --------------------------------------------------------
	{{  UNK,   UNK,   UNK,    UNK,   UNK,   UNK,   UNK,   UNK   },	 // none
	 {  UNK,   UNK,   RIGHT,  UNK,   DOWN,  UNK,   DOWN,  DOWN  },   // 1
	 {  UNK,   LEFT,  UNK,    UNK,   LEFT,  LEFT,  UNK,   LEFT  },   // 2
	 {  UNK,   UNK,   UNK,    UNK,   DOWN,  UNK,   DOWN,  UNK   },   // 1+2
	 {  UNK,   UP,    RIGHT,  UP,    UNK,   UNK,   RIGHT, UP    },   // 3
	 {  UNK,   UP,    RIGHT,  RIGHT, DOWN,  UNK,   RIGHT, RIGHT },   // 1+3
	 {  UNK,   UP,    RIGHT,  UP,    LEFT,  LEFT,  UNK,   UNK   },   // 2+3
	 {  UNK,   UP,    RIGHT,  UNK,   DOWN,  LEFT,  UNK,   UNK   }};  // 1+2+3

/* Proximity channel bit codes - indicate which channels are above threshold */
/*   Used cumulatively to form index values for direction table lookup. */
#define CHAN_NONE  0x00
#define CHAN_1     0x01
#define CHAN_2     0x02
#define CHAN_3     0x04

/** Strings to indicate which channels detected proximity */
static const char *const channel_labels[8] = {
	"none ",                /* CHAN_NONE */
	"1    ",                /* CHAN_1 */
	"2    ",                /* CHAN_2 */
	"1+2  ",                /* CHAN_1 | CHAN_2 */
	"3    ",                /* CHAN_3 */
	"1+3  ",                /* CHAN_1 | CHAN_3 */
	"2+3  ",                /* CHAN_2 | CHAN_3 */
	"1+2+3"                 /* CHAN_1 | CHAN_2 | CHAN_3 */
};

/* Sensor descriptor and data storage */
sensor_t prox_dev;                /* Proximity sensor descriptor */
sensor_data_t prox_data  = { .scaled = true }; /* Scaled sensor data */
bool prox_event_occurred = false; /* Flag to indicate event */


/** \brief Proximity value test
 *
 * This routine examines the data fields in the sensor_data_t structure
 * and returns a single value summarizing which channels have a reported
 * proximity value (i.e. the value is not PROXIMITY_NONE).
 *
 * \param	data	Address of sensor_data_t struct containing prox data
 *
 * \return  int8_t	Encoded with bits set per channel over threshold
 */
static int8_t test_channels(sensor_data_t *data)
{
	int8_t channels = CHAN_NONE;

	if (data->proximity.value[0] != PROXIMITY_NONE) {
		channels |= CHAN_1;
	}

	if (data->proximity.value[1] != PROXIMITY_NONE) {
		channels |= CHAN_2;
	}

	if (data->proximity.value[2] != PROXIMITY_NONE) {
		channels |= CHAN_3;
	}

	return channels;
}

/** \brief Proximity event handler
 *
 * This routine will be called when a near-proximity event occurs.  It
 * simply copies the proximity data to the sensor_data_t structure
 * specified during the sensor_add_event function call.
 *
 * This routine executes as part of the interrupt service routine for
 * the sensor interrupt.
 */
static void prox_event_handler(volatile sensor_event_data_t *event_data,
		volatile void *arg)
{
	prox_data = event_data->data;

	prox_event_occurred = true;
}

/** \brief Proximity Sensor gesture recognition demo application entry
 *
 * This application uses a 3-channel proximity sensor to recognize simple
 * gestures.  When a proximity event occurs, the routine will wake up from
 * a low-power sleep mode and begin repeatedly sampling the proximity
 * sensor, until the proximity of the object is no longer detected.  Then
 * the beginning and ending sensor readings are compared, and the overall
 * direction of the object's movement is determined based on a lookup table.
 *
 * Once the direction is determined, it is indicate by turning on one of the
 * LEDs on the controller board and (optionally) by serial output to a
 * terminal device.  If the direction cannot be determined, all indicator
 * LEDs will be blinked rapidly.
 *
 * The application then resets by returning to a low-power sleep mode until
 * the next proximity event is detected.
 */
int main(void)
{
	uint8_t start_channels;    /* First channels detecting proximity */
	uint8_t current_channels;  /* Current channels detecting proximity */
	uint8_t end_channels;      /* Final channels detecting proximity */
	direction_t direction;     /* Calculated gesture direction */
	int i;

	/* Initialize the board (Xplained UC3 or XMEGA & Xplained Sensor boards)
	 * I/O pin mappings and any other configurable resources selected in
	 * the build configuration.
	 */
	sensor_platform_init();

	/* Turn on LEDs while initialization completes */
	LED_On(UP_LED);
	LED_On(DOWN_LED);
	LED_On(LEFT_LED);
	LED_On(RIGHT_LED);

	/* Initialize the MCU sleep manager API and specify a sleep mode. */
	sleepmgr_init();
	sleepmgr_lock_mode(SLEEP_MODE);

	/* Attach and initialize proximity sensor */
	sensor_attach(&prox_dev, SENSOR_TYPE_PROXIMITY, 0, 0);

	if (prox_dev.err) {
		puts("\r\nProximity sensor initialization error.");

		while (true) {
			/* Error occurred, loop forever */
		}
	}

#if (USE_PRINTF == true)
	uint32_t id;      /* Device ID */
	uint8_t version;  /* Device version */

	sensor_device_id(&prox_dev, &id, &version);
	printf("\r\nProximity sensor: %s    ID = 0x%02x ver. 0x%02x\r\n",
			prox_dev.drv->caps.name, (unsigned)id,
			(unsigned)version);
#endif

	/* Set sample rate */
	sensor_set_sample_rate(&prox_dev, PROX_SAMPLE_RATE);

	/* Select all proximity sensor channels */
	sensor_set_channel(&prox_dev, SENSOR_CHANNEL_ALL);
	
#if (SET_PROX_THRESHOLD == true)
	/* Manually  set proximity threshold values for each channel */
	/*  Otherwise, sensor will use values previously stored in nvram. */
	sensor_set_threshold(&prox_dev, SENSOR_THRESHOLD_NEAR_PROXIMITY,
			PROX_THRESHOLD);
#endif

#if (SET_PROX_CURRENT == true)
	/* Manually set LED current value for each channel */
	/*  Otherwise, sensor will use default values */
	sensor_set_current(&prox_dev, PROX_CURRENT_mA);
#endif

	/* Set up close proximity event to wakeup system */
	sensor_add_event(&prox_dev, SENSOR_EVENT_NEAR_PROXIMITY,
			prox_event_handler, 0, false);

	while (true) {
		/* Enable proximity event */
		sensor_enable_event(&prox_dev, SENSOR_EVENT_NEAR_PROXIMITY);

		/* Delay before putting device to sleep */
		delay_ms(10);

		/* Put device in low power sleep mode; wait for an interrupt to
		 * wake. */
		LED_Off(UP_LED);
		LED_Off(DOWN_LED);
		LED_Off(LEFT_LED);
		LED_Off(RIGHT_LED);

		/* Enter specified sleep mode */
		sleepmgr_enter_sleep();

		/* Only do sensor processing if proximity event woke device up */
		if (prox_event_occurred) {
			prox_event_occurred = false;

			/* Disable new proximity events during gesture sampling */
			sensor_disable_event(&prox_dev,
					SENSOR_EVENT_NEAR_PROXIMITY);

			/* Get starting value saved by event handler routine */
			start_channels = test_channels(&prox_data);
			end_channels = start_channels;

			/* Loop until no longer detecting proximity */
			do {
				/* Get new readings from sensor */
				sensor_get_proximity(&prox_dev, &prox_data);

				current_channels = test_channels(&prox_data);

				/* Update end value if proximity is still
				 * detected */
				if (current_channels != CHAN_NONE) {
					end_channels = current_channels;
				}
			} while (current_channels != CHAN_NONE);

			/* Get direction from lookup table based on start/end
			 * channel sets */
			direction = dir_tbl [start_channels] [end_channels];

#if USE_PRINTF
			/* Display direction */
			printf("Start: %s  End: %s  Direction: %s \r\n",
					channel_labels[start_channels],
					channel_labels[end_channels],
					direction_labels[direction]);
#endif

			/* Use LEDs to display direction */
			switch (direction) {
			case UP:
				LED_On(UP_LED);
				break;

			case DOWN:
				LED_On(DOWN_LED);
				break;

			case LEFT:
				LED_On(LEFT_LED);
				break;

			case RIGHT:
				LED_On(RIGHT_LED);
				break;

			default: 
				/* Unknown - blink all LEDs to indicate */
				for (i = 0; i < (ERR_BLINK_COUNT * 2); i++) {
					LED_Toggle(UP_LED);
					LED_Toggle(DOWN_LED);
					LED_Toggle(LEFT_LED);
					LED_Toggle(RIGHT_LED);

					delay_ms(50);
				}
				break;
			}
		}
		
		delay_ms(500);
	}
	
	return 0;
}
