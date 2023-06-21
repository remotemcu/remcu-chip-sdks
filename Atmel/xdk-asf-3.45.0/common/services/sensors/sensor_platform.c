/**
 * \file
 *
 * \brief Sensor Platform API
 *
 * This module implements Atmel Sensor API platform interfaces for XMEGA and
 * UC3 microcontrollers.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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
#include    <conf_sensors.h>
#include    "sensor_dev.h"

#include    <delay.h>

/**
 * \brief Verify Board Support for the ASF Common Sensor Service
 *
 * The common sensor service requires board-specific configuration constants
 * describing sensor devices, bus interfaces, I/O pin interfaces etc. for a
 * particular hardware implementation.  When a board is configured to provide
 * the board hardware-specific details to the sensor service, the
 * \ref COMMON_SENSOR_PLATFORM configuration constant will be defined in
 * the board-specific header file.
 */
#ifndef COMMON_SENSOR_PLATFORM
#   warning "The target board is not configured for the ASF sensor service."
#endif

/** \internal Sensor Platform Timing Definitions */
/** @{ */
#define SENSOR_START_DELAY_MSEC (50)    /** Settling delay time (in milliseconds) */
/** @} */

/** \internal Sensor Bus Interface Implementations */
/** @{ */

#if defined(CONF_SENSOR_BUS_TWI)
#   define BUSIO_TYPE       (BUS_TYPE_TWI)
#   define BUSIO_SPEED      (CONFIG_TWI_BAUDRATE)
#   define BUSIO_OFFSET     (CONFIG_TWI_OFFSET)
#   define BUSIO_IF         (CONFIG_TWI_MASTER_IF)
#elif defined(CONF_SENSOR_BUS_SPI)
#   define BUSIO_TYPE       (BUS_TYPE_SPI)
#   define BUSIO_SPEED      (CONFIG_SPI_BAUDRATE)
#   define BUSIO_OFFSET     (CONFIG_SPI_OFFSET)
#   define BUSIO_IF         (CONFIG_SPI_MASTER_IF)
#else
#   define BUSIO_TYPE       (BUS_TYPE_UNKNOWN)
#   define BUSIO_SPEED      (0)
#   define BUSIO_OFFSET     (0)
#   define BUSIO_IF         (*((int *)0))
#   warning "Unknown common sensor service bus configuration."
#endif

/** @} */

/** \internal Sensor Hardware Descriptor Macro */
/** @{ */

#define SENSOR_HAL_DESC(sensor_type, name) { \
		.bus.type      = BUSIO_TYPE, \
		.bus.id        = &BUSIO_IF, \
		.bus.addr      = name ## _bus_addr + BUSIO_OFFSET, \
		.bus.no_wait   = false,	\
		.mcu_sigint    = name ## _sigint, \
		.mcu_sigout    = name ## _sigout, \
		.orientation   = name ## _orientation, \
		.dev_type      = sensor_type, \
		.sensor_init   = name ## _init \
}

/** @} */

/** \brief This function returns the current timestamp counter value.
 *
 * The timestamp facility is implemented in terms of the XMEGA or UC3
 * timer and clock function APIs.
 *
 * \return The current counter value (microseconds).
 */
uint32_t sensor_timestamp(void)
{
	uint32_t tsc = 0;

#if UC3
	/** \todo
	 *
	 * Implement this interface in terms of XMEGA and UC3 timer/counter (TC)
	 * facilities exposed through ASF drivers.  A free running counter with
	 * microsecond resolution is desirable.  Ideally, the counter value
	 * should be updated without using interrupts and attached to a clock
	 *that
	 * will be available while the MCU is in lower power modes.
	 */
	tsc = cpu_cy_2_us(Get_system_register(AVR32_COUNT),
			sysclk_get_cpu_hz());
#endif

	return tsc;
}

/** \brief Install a sensor device interrupt handler
 *
 * This routine will enable interrupts on the pin specified by the \c intr_pin
 * parameter and call a user-defined callback \c handler when an interrupt is
 * detected.  The \c arg parameter is used to pass the address of user-defined
 * input and output storage for the callback handler.  Calling the routine with
 * the \c handler parameter set to 0 (the NULL pointer) will cause interrupts to
 * be disabled for the specified GPIO pin.
 *
 * \param   intr_pin    Board-specific interrupt / GPIO pin interface to the
 *MCU.
 * \param   handler     The address of a user-defined interrupt handler.
 * \param   arg         An optional address passed to the interrupt handler.
 *
 * \return  bool        \c true if the call succeeds, else \c false.
 */
bool sensor_irq_connect(uint32_t intr_pin, void (*handler)(volatile void *),
		void *arg)
{
	bool status = false;

#if defined (SENSORS_XPLAINED_BOARD)
	status = sensor_board_irq_connect(intr_pin, handler, arg);
#endif

	return status;
}

/** \brief Fetch the sensor hardware descriptor list
 *
 * This routine returns the system address of a table of sensor hardware
 * descriptors along with the number of descriptors in the \c dev_count
 * parameter.  This utility is currently used to abstract the details of the
 * device list implementation from the rest of the API.  However, it will not
 * be retained in future versions of the API.  As a result applications and
 * library code should not use this routine.  If list iteration is required
 * in API clients, use the sensor_device_enum() function.
 *
 * \param   dev_count   The list descriptor count is returned here.
 *
 * \return  The address of the sensor hardware descriptor list.
 */
sensor_hal_t *sensor_list(size_t *dev_count)
{
	/** \internal Sensor Device List
	 *
	 * When a new driver is added to the API a HAL descriptor indicating
	 * the sensor type, xxx_init() function prefix, bus address (where
	 * applicable), and I/O Pin assignment (where applicable) should be
	 * conditionally allocated in this table.
	 */
	static sensor_hal_t sensor_dev_list[] = {
#ifdef  INCLUDE_AK8975          /* AKM 3-axis electronic compass */
		SENSOR_HAL_DESC(SENSOR_TYPE_COMPASS, ak8975),
#endif

#ifdef  INCLUDE_BMA020          /* Bosch 3-axis accelerometer */
		SENSOR_HAL_DESC(SENSOR_TYPE_ACCELEROMETER, bma020),
#endif

#ifdef  INCLUDE_BMA150          /* Bosch 3-axis accelerometer */
		SENSOR_HAL_DESC(SENSOR_TYPE_ACCELEROMETER, bma150),
#endif

#ifdef  INCLUDE_BMA180          /* Bosch 3-axis accelerometer */
		SENSOR_HAL_DESC(SENSOR_TYPE_ACCELEROMETER, bma180),
#endif

#ifdef  INCLUDE_BMA220          /* Bosch 3-axis accelerometer */
		SENSOR_HAL_DESC(SENSOR_TYPE_ACCELEROMETER, bma220),
#endif

#ifdef  INCLUDE_BMA222          /* Bosch 3-axis accelerometer */
		SENSOR_HAL_DESC(SENSOR_TYPE_ACCELEROMETER, bma222),
#endif

#ifdef  INCLUDE_BMA250          /* Bosch 3-axis accelerometer */
		SENSOR_HAL_DESC(SENSOR_TYPE_ACCELEROMETER, bma250),
#endif

#ifdef  INCLUDE_BMP085          /* Bosch barometric pressure sensor */
		SENSOR_HAL_DESC(SENSOR_TYPE_BAROMETER, bmp085),
#endif

#ifdef  INCLUDE_BMP180          /* Bosch barometric pressure sensor */
		SENSOR_HAL_DESC(SENSOR_TYPE_BAROMETER, bmp180),
#endif

#ifdef  INCLUDE_HMC5883L        /* Honeywell 3-axis magnetometer */
		SENSOR_HAL_DESC(SENSOR_TYPE_COMPASS, hmc5883l),
#endif

#ifdef  INCLUDE_IMU3000         /* InvenSense 3-axis gyroscope/IMU */
		SENSOR_HAL_DESC(SENSOR_TYPE_GYROSCOPE, imu3000),
#endif

#ifdef  INCLUDE_ITG3200         /* InvenSense 3-axis gyroscope */
		SENSOR_HAL_DESC(SENSOR_TYPE_GYROSCOPE, itg3200),
#endif

#if (defined(INCLUDE_KXTF9) || defined(INCLUDE_KXTI9))
		/* Kionix 3-axis accelerometer */
		SENSOR_HAL_DESC(SENSOR_TYPE_ACCELEROMETER, kxtf9),
#endif

#ifdef  INCLUDE_SFH5712         /* Osram SFH5712 light sensor */
		SENSOR_HAL_DESC(SENSOR_TYPE_LIGHT, sfh5712),
#endif

#ifdef  INCLUDE_SFH7770         /* Osram SFH7770 light/prox sensor */
		SENSOR_HAL_DESC((SENSOR_TYPE_LIGHT | SENSOR_TYPE_PROXIMITY),
				sfh7770),
#endif
	};

	*dev_count = ARRAYSIZE(sensor_dev_list);

	return sensor_dev_list;
}

/** \brief Find a sensor hardware descriptor
 *
 * This routine returns the address of a sensor hardware descriptor, based on
 * the sensor type specified in the \c type parameter.  The first hardware
 * entry with the correct type will be used.
 *
 * This utility is currently used to abstract the details of the device list
 * implementation from the rest of the API.  However, it will not be retained in
 * future versions of the API.  As a result applications and library code should
 * not use this routine.  If list iteration is required in API clients, use the
 * sensor_device_enum() function.
 *
 * \param   type   The type of sensor to find in hardware descriptor list
 *
 * \return  The address of the sensor hardware descriptor, or NULL if not found
 */
sensor_hal_t *sensor_find(sensor_type_t type)
{
	size_t dev_count;
	sensor_hal_t *const dev_list = sensor_list(&dev_count);

	/* Find the specified sensor type in the device list. */

	for (int index = 0; index < dev_count; ++index) {
		/* Test device against input type(s) bitmask. */

		if ((dev_list[index].dev_type & type) == type) {
			return &dev_list [index];
		}
	}

	return 0;
}

/** \brief Initialize the Sensor Platform Hardware
 *
 * This function initializes the Atmel \c Xplained platform hardware and
 * must be called once from the client application before any of the Sensors
 * Xplained API routines can be used.
 *
 * After the platform board initialization (i.e. board_init()) configures
 * GPIO pins, interrupts, etc., this routine initializes the AVR and AVR32
 * hardware abstraction layer (HAL) for the Xplained Sensor API.
 *
 * \return  bool    true if the call succeeds, else false is returned.
 */
bool sensor_platform_init(void)
{
	bool initialized = false;

	/* Initialize the system clock and all clocks derived from it. */

	sysclk_init();

	/* Initialize the board (UC3/XMEGA Xplained & Sensor Xplained boards)
	 * I/O pin mappings and any other configurable resources selected in
	 * the build configuration.
	 */

	board_init();

	/* Initialize the sensor bus I/O interface. */

	if (BUSIO_TYPE != BUS_TYPE_UNKNOWN) {
		initialized = sensor_bus_init(&BUSIO_IF, BUSIO_SPEED);
	}

	/* Initialize C Standard I/O (stdio) Redirection. */

#if defined(CONF_STDIO_REDIRECT)
#  if defined(CONF_STDIO_USB)

	/* Start and attach USB CDC device interface for devices with
	 * integrated USB interfaces.
	 */

	stdio_usb_init();
#  elif defined(CONF_STDIO_SERIAL)

	/* Assume the USART is mapped to an appropriate phy in the board
	 * initialization code (e.g. board_init) and initialize terminal
	 * and clib I/O facilities here.
	 */

	usart_serial_options_t const USART_SERIAL_OPTIONS = {
		.baudrate     = CONFIG_USART_BAUDRATE,
		.charlength   = CONFIG_USART_CHAR_LENGTH,
		.paritytype   = CONFIG_USART_PARITY,
		.stopbits     = CONFIG_USART_STOP_BIT
	};

	stdio_serial_init(&CONFIG_USART_IF, &USART_SERIAL_OPTIONS);
#  endif
#endif  /* defined(CONF_STDIO_REDIRECT) */

	/* Sensor devices typically require time to settle after power
	 * is applied.  Wait here for a standard time.  (Individual sensor
	 * drivers may need to wait an additional period during initialization
	 * if the device is particularly slow to settle.)
	 */
	delay_ms(SENSOR_START_DELAY_MSEC);

	return initialized;
}
