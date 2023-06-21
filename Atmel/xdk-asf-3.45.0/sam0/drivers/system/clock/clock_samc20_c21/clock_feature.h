/**
 * \file
 *
 * \brief SAM C2x Clock Driver
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
#ifndef SYSTEM_CLOCK_FEATURE_H_INCLUDED
#define SYSTEM_CLOCK_FEATURE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup asfdoc_sam0_system_clock_group SAM System Clock Management (SYSTEM CLOCK) Driver
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based microcontrollers provides an interface for the configuration
 * and management of the device's clocking related functions. This includes
 * the various clock sources, bus clocks, and generic clocks within the device,
 * with functions to manage the enabling, disabling, source selection, and
 * prescaling of clocks to various internal peripherals.
 *
 * The following peripherals are used by this module:
 *
 * - GCLK (Generic Clock Management)
 * - PM (Power Management)
 * - OSCCTRL (Oscillators Controller)
 * - OSC32KCTRL (32K Oscillators Controller)
 * - MCLK (Main Clock)
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM C20/C21
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam0_system_clock_prerequisites
 *  - \ref asfdoc_sam0_system_clock_module_overview
 *  - \ref asfdoc_sam0_system_clock_special_considerations
 *  - \ref asfdoc_sam0_system_clock_extra_info
 *  - \ref asfdoc_sam0_system_clock_examples
 *  - \ref asfdoc_sam0_system_clock_api_overview
 *
 *
 * \section asfdoc_sam0_system_clock_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_sam0_system_clock_module_overview Module Overview
 * The SAM devices contain a sophisticated clocking system, which is designed
 * to give the maximum flexibility to the user application. This system allows
 * a system designer to tune the performance and power consumption of the device
 * in a dynamic manner, to achieve the best trade-off between the two for a
 * particular application.
 *
 * This driver provides a set of functions for the configuration and management
 * of the various clock related functionality within the device.
 *
 *
 * \subsection asfdoc_sam0_system_clock_module_overview_clock_sources Clock Sources
 * The SAM devices have a number of master clock source modules, each of
 * which being capable of producing a stabilized output frequency, which can then
 * be fed into the various peripherals and modules within the device.
 *
 * Possible clock source modules include internal R/C oscillators as well as external
 * crystal oscillators and/or clock inputs.
 *
 * \subsection asfdoc_sam0_system_clock_module_overview_cpu_clock CPU / Bus Clocks
 * The CPU and AHB/APBx buses are clocked by the same physical clock source
 * (referred in this module as the Main Clock), however the APBx buses may
 * have additional prescaler division ratios set to give each peripheral bus a
 * different clock speed.
 *
 * The general main clock tree for the CPU and associated buses is shown in
 * the figure below.
 *
 * \anchor asfdoc_sam0_system_clock_module_clock_tree
 * \dot
 * digraph overview {
 *   rankdir=LR;
 *   clk_src [label="Clock Sources", shape=none, height=0];
 *   node [label="CPU Bus" shape=ellipse] cpu_bus;
 *   node [label="AHB Bus" shape=ellipse] ahb_bus;
 *   node [label="APBA Bus" shape=ellipse] apb_a_bus;
 *   node [label="APBB Bus" shape=ellipse] apb_b_bus;
 *   node [label="APBC Bus" shape=ellipse] apb_c_bus;
 *   node [label="Main Bus\nPrescaler" shape=square] main_prescaler;
 *   node [label="APBA Bus\nPrescaler" shape=square] apb_a_prescaler;
 *   node [label="APBB Bus\nPrescaler" shape=square] apb_b_prescaler;
 *   node [label="APBC Bus\nPrescaler" shape=square] apb_c_prescaler;
 *   node [label="", shape=polygon, sides=4, distortion=0.6, orientation=90, style=filled, fillcolor=black, height=0.9, width=0.2] main_clock_mux;
 *
 *   clk_src         -> main_clock_mux;
 *   main_clock_mux  -> main_prescaler;
 *   main_prescaler  -> cpu_bus;
 *   main_prescaler  -> ahb_bus;
 *   main_prescaler  -> apb_a_prescaler;
 *   main_prescaler  -> apb_b_prescaler;
 *   main_prescaler  -> apb_c_prescaler;
 *   apb_a_prescaler -> apb_a_bus;
 *   apb_b_prescaler -> apb_b_bus;
 *   apb_c_prescaler -> apb_c_bus;
 * }
 * \enddot
 *
 * \subsection asfdoc_sam0_system_clock_module_overview_clock_masking Clock Masking
 * To save power, the input clock to one or more peripherals on the AHB and APBx
 * buses can be masked away - when masked, no clock is passed into the module.
 * Disabling of clocks of unused modules will prevent all access to the masked
 * module, and will reduce the overall device power consumption.
 *
 * \subsection asfdoc_sam0_system_clock_module_overview_gclk Generic Clocks
 * Within the SAM devices there are a number of Generic Clocks; these are used to
 * provide clocks to the various peripheral clock domains in the device in a
 * standardized manner. One or more master source clocks can be selected as the
 * input clock to a Generic Clock Generator, which can prescale down the input
 * frequency to a slower rate for use in a peripheral.
 *
 * Additionally, a number of individually selectable Generic Clock Channels are
 * provided, which multiplex and gate the various generator outputs for one or
 * more peripherals within the device. This setup allows for a single common
 * generator to feed one or more channels, which can then be enabled or disabled
 * individually as required.
 *
 * \anchor asfdoc_sam0_system_clock_module_chain_overview
 * \dot
 * digraph overview {
 *   rankdir=LR;
 *   node [label="Clock\nSource a" shape=square] system_clock_source;
 *   node [label="Generator 1" shape=square] clock_gen;
 *   node [label="Channel x" shape=square] clock_chan0;
 *   node [label="Channel y" shape=square] clock_chan1;
 *   node [label="Peripheral x" shape=ellipse style=filled fillcolor=lightgray] peripheral0;
 *   node [label="Peripheral y" shape=ellipse style=filled fillcolor=lightgray] peripheral1;
 *
 *   system_clock_source -> clock_gen;
 *   clock_gen   -> clock_chan0;
 *   clock_chan0 -> peripheral0;
 *   clock_gen   -> clock_chan1;
 *   clock_chan1 -> peripheral1;
 * }
 * \enddot
 *
 * \subsubsection asfdoc_sam0_system_clock_module_chain_example Clock Chain Example
 * An example setup of a complete clock chain within the device is shown in
 * the figure below.
 *
 * \anchor asfdoc_sam0_system_clock_module_chain_example_fig
 * \dot
 * digraph overview {
 *   rankdir=LR;
 *   node [label="External\nOscillator" shape=square] system_clock_source0;
 *   node [label="Generator 0" shape=square] clock_gen0;
 *   node [label="Channel x" shape=square] clock_chan0;
 *   node [label="Core CPU" shape=ellipse  style=filled fillcolor=lightgray] peripheral0;
 *
 *   system_clock_source0 -> clock_gen0;
 *   clock_gen0    -> clock_chan0;
 *   clock_chan0   -> peripheral0;
 *   node [label="48MHz R/C\nOscillator (OSC48M)" shape=square fillcolor=white] system_clock_source1;
 *   node [label="Generator 1" shape=square] clock_gen1;
 *   node [label="Channel y" shape=square] clock_chan1;
 *   node [label="Channel z" shape=square] clock_chan2;
 *   node [label="SERCOM\nModule" shape=ellipse  style=filled fillcolor=lightgray] peripheral1;
 *   node [label="Timer\nModule" shape=ellipse  style=filled fillcolor=lightgray] peripheral2;
 *
 *   system_clock_source1 -> clock_gen1;
 *   clock_gen1    -> clock_chan1;
 *   clock_gen1    -> clock_chan2;
 *   clock_chan1   -> peripheral1;
 *   clock_chan2   -> peripheral2;
 * }
 * \enddot
 *
 * \subsubsection asfdoc_sam0_system_clock_module_overview_gclk_generators Generic Clock Generators
 * Each Generic Clock generator within the device can source its input clock
 * from one of the provided Source Clocks, and prescale the output for one or
 * more Generic Clock Channels in a one-to-many relationship. The generators
 * thus allow for several clocks to be generated of different frequencies,
 * power usages, and accuracies, which can be turned on and off individually to
 * disable the clocks to multiple peripherals as a group.
 *
 * \subsubsection asfdoc_sam0_system_clock_module_overview_gclk_channels Generic Clock Channels
 * To connect a Generic Clock Generator to a peripheral within the
 * device, a Generic Clock Channel is used. Each peripheral or
 * peripheral group has an associated Generic Clock Channel, which serves as the
 * clock input for the peripheral(s). To supply a clock to the peripheral
 * module(s), the associated channel must be connected to a running Generic
 * Clock Generator and the channel enabled.
 *
 * \section asfdoc_sam0_system_clock_special_considerations Special Considerations
 *
 * There are no special considerations for this module.
 *
 *
 * \section asfdoc_sam0_system_clock_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_sam0_system_clock_extra. This includes:
 *  - \ref asfdoc_sam0_system_clock_extra_acronyms
 *  - \ref asfdoc_sam0_system_clock_extra_dependencies
 *  - \ref asfdoc_sam0_system_clock_extra_errata
 *  - \ref asfdoc_sam0_system_clock_extra_history
 *
 *
 * \section asfdoc_sam0_system_clock_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_sam0_system_clock_exqsg.
 *
 *
 * \section asfdoc_sam0_system_clock_api_overview API Overview
 * @{
 */

#include <compiler.h>
#include <gclk.h>



/**
 * \brief Available startup times for the XOSC32K.
 *
 * Available external 32KHz oscillator startup times, as a number of external
 * clock cycles.
 */
enum system_xosc32k_startup {
	/** Wait 2048 clock cycles until the clock source is considered stable */
	SYSTEM_XOSC32K_STARTUP_2048,
	/** Wait 4096 clock cycles until the clock source is considered stable */
	SYSTEM_XOSC32K_STARTUP_4096,
	/** Wait 16384 clock cycles until the clock source is considered stable */
	SYSTEM_XOSC32K_STARTUP_16384,
	/** Wait 32768 clock cycles until the clock source is considered stable */
	SYSTEM_XOSC32K_STARTUP_32768,
	/** Wait 65536 clock cycles until the clock source is considered stable */
	SYSTEM_XOSC32K_STARTUP_65536,
	/** Wait 131072 clock cycles until the clock source is considered stable */
	SYSTEM_XOSC32K_STARTUP_131072,
	/** Wait 262144 clock cycles until the clock source is considered stable */
	SYSTEM_XOSC32K_STARTUP_262144,
};

/**
 * \brief Available startup times for the XOSC.
 *
 * Available external oscillator startup times, as a number of external clock
 * cycles.
 */
enum system_xosc_startup {
	/** Wait one clock cycles until the clock source is considered stable */
	SYSTEM_XOSC_STARTUP_1,
	/** Wait two clock cycles until the clock source is considered stable */
	SYSTEM_XOSC_STARTUP_2,
	/** Wait four clock cycles until the clock source is considered stable */
	SYSTEM_XOSC_STARTUP_4,
	/** Wait eight clock cycles until the clock source is considered stable */
	SYSTEM_XOSC_STARTUP_8,
	/** Wait 16 clock cycles until the clock source is considered stable */
	SYSTEM_XOSC_STARTUP_16,
	/** Wait 32 clock cycles until the clock source is considered stable */
	SYSTEM_XOSC_STARTUP_32,
	/** Wait 64 clock cycles until the clock source is considered stable */
	SYSTEM_XOSC_STARTUP_64,
	/** Wait 128 clock cycles until the clock source is considered stable */
	SYSTEM_XOSC_STARTUP_128,
	/** Wait 256 clock cycles until the clock source is considered stable */
	SYSTEM_XOSC_STARTUP_256,
	/** Wait 512 clock cycles until the clock source is considered stable */
	SYSTEM_XOSC_STARTUP_512,
	/** Wait 1024 clock cycles until the clock source is considered stable */
	SYSTEM_XOSC_STARTUP_1024,
	/** Wait 2048 clock cycles until the clock source is considered stable */
	SYSTEM_XOSC_STARTUP_2048,
	/** Wait 4096 clock cycles until the clock source is considered stable */
	SYSTEM_XOSC_STARTUP_4096,
	/** Wait 8192 clock cycles until the clock source is considered stable */
	SYSTEM_XOSC_STARTUP_8192,
	/** Wait 16384 clock cycles until the clock source is considered stable */
	SYSTEM_XOSC_STARTUP_16384,
	/** Wait 32768 clock cycles until the clock source is considered stable */
	SYSTEM_XOSC_STARTUP_32768,
};

/**
 * \brief Available startup times for the OSC32K.
 *
 * Available internal 32KHz oscillator startup times, as a number of internal
 * OSC32K clock cycles.
 */
enum system_osc32k_startup {
	/** Wait three clock cycles until the clock source is considered stable */
	SYSTEM_OSC32K_STARTUP_3,
	/** Wait four clock cycles until the clock source is considered stable */
	SYSTEM_OSC32K_STARTUP_4,
	/** Wait six clock cycles until the clock source is considered stable */
	SYSTEM_OSC32K_STARTUP_6,
	/** Wait ten clock cycles until the clock source is considered stable */
	SYSTEM_OSC32K_STARTUP_10,
	/** Wait 18 clock cycles until the clock source is considered stable */
	SYSTEM_OSC32K_STARTUP_18,
	/** Wait 34 clock cycles until the clock source is considered stable */
	SYSTEM_OSC32K_STARTUP_34,
	/** Wait 66 clock cycles until the clock source is considered stable */
	SYSTEM_OSC32K_STARTUP_66,
	/** Wait 130 clock cycles until the clock source is considered stable */
	SYSTEM_OSC32K_STARTUP_130,
};

/**
 * \brief Division prescalers for the internal 48MHz system clock.
 *
 * Available prescalers for the internal 48MHz (nominal) system clock.
 */
enum system_osc48m_div {
	/** Divide the 48MHz RC oscillator output by one */
	SYSTEM_OSC48M_DIV_1,
	/** Divide the 48MHz RC oscillator output by two */
	SYSTEM_OSC48M_DIV_2,
	/** Divide the 48MHz RC oscillator output by three */
	SYSTEM_OSC48M_DIV_3,
	/** Divide the 48MHz RC oscillator output by four */
	SYSTEM_OSC48M_DIV_4,
	/** Divide the 48MHz RC oscillator output by five */
	SYSTEM_OSC48M_DIV_5,
	/** Divide the 48MHz RC oscillator output by six */
	SYSTEM_OSC48M_DIV_6,
	/** Divide the 48MHz RC oscillator output by seven */
	SYSTEM_OSC48M_DIV_7,
	/** Divide the 48MHz RC oscillator output by eight */
	SYSTEM_OSC48M_DIV_8,
	/** Divide the 48MHz RC oscillator output by nine */
	SYSTEM_OSC48M_DIV_9,
	/** Divide the 48MHz RC oscillator output by ten */
	SYSTEM_OSC48M_DIV_10,
	/** Divide the 48MHz RC oscillator output by eleven */
	SYSTEM_OSC48M_DIV_11,
	/** Divide the 48MHz RC oscillator output by twelve */
	SYSTEM_OSC48M_DIV_12,
	/** Divide the 48MHz RC oscillator output by thirteen */
	SYSTEM_OSC48M_DIV_13,
	/** Divide the 48MHz RC oscillator output by fourteen */
	SYSTEM_OSC48M_DIV_14,
	/** Divide the 48MHz RC oscillator output by fifteen */
	SYSTEM_OSC48M_DIV_15,
	/** Divide the 48MHz RC oscillator output by sixteen */
	SYSTEM_OSC48M_DIV_16,
};

/**
 * \brief Available startup times for the OSC48M.
 *
 * Available internal 48MHz oscillator startup times, as a number of internal
 * clock cycles.
 */
enum system_osc48m_startup {
	/** Wait 8 clock cycles until the clock source is considered stable */
	SYSTEM_OSC48M_STARTUP_8,
	/** Wait 16 clock cycles until the clock source is considered stable */
	SYSTEM_OSC48M_STARTUP_16,
	/** Wait 32 clock cycles until the clock source is considered stable */
	SYSTEM_OSC48M_STARTUP_32,
	/** Wait 64 clock cycles until the clock source is considered stable */
	SYSTEM_OSC48M_STARTUP_64,
	/** Wait 128 clock cycles until the clock source is considered stable */
	SYSTEM_OSC48M_STARTUP_128,
	/** Wait 256 clock cycles until the clock source is considered stable */
	SYSTEM_OSC48M_STARTUP_256,
	/** Wait 512 clock cycles until the clock source is considered stable */
	SYSTEM_OSC48M_STARTUP_512,
	/** Wait 1024 clock cycles until the clock source is considered stable */
	SYSTEM_OSC48M_STARTUP_1024,
};

/**
 * \brief XOSC failure detector prescaler from OSC48M .
 *
 * Available clock failure detector prescaler.
 */
enum system_clock_xosc_failure_detector_prescaler {
	/** Divide OSC48M frequency by 1 for clock failure detector clock */
	SYSTEM_CLOCK_XOSC_FAILURE_DETECTOR_PRESCALER_1,
	/** Divide OSC48M frequency by 2 for clock failure detector clock */
	SYSTEM_CLOCK_XOSC_FAILURE_DETECTOR_PRESCALER_2,
	/** Divide OSC48M frequency by 4 for clock failure detector clock */
	SYSTEM_CLOCK_XOSC_FAILURE_DETECTOR_PRESCALER_4,
	/** Divide OSC48M frequency by 8 for clock failure detector clock */
	SYSTEM_CLOCK_XOSC_FAILURE_DETECTOR_PRESCALER_8,
	/** Divide OSC48M frequency by 16 for clock failure detector clock */
	SYSTEM_CLOCK_XOSC_FAILURE_DETECTOR_PRESCALER_16,
	/** Divide OSC48M frequency by 32 for clock failure detector clock */
	SYSTEM_CLOCK_XOSC_FAILURE_DETECTOR_PRESCALER_32,
	/** Divide OSC48M frequency by 64 for clock failure detector clock */
	SYSTEM_CLOCK_XOSC_FAILURE_DETECTOR_PRESCALER_64,
	/** Divide OSC48M frequency by 128 for clock failure detector clock */
	SYSTEM_CLOCK_XOSC_FAILURE_DETECTOR_PRESCALER_128,
};

/**
 * \brief XOSC32K failure detector prescaler from OSCULP32K.
 *
 * Available clock failure detector prescaler.
 */
enum system_clock_xosc32k_failure_detector_prescaler {
	/** Divide OSCULP32K frequency by 1 for clock failure detector clock */
	SYSTEM_CLOCK_XOSC32K_FAILURE_DETECTOR_PRESCALER_1,
	/** Divide OSCULP32K frequency by 2 for clock failure detector clock */
	SYSTEM_CLOCK_XOSC32K_FAILURE_DETECTOR_PRESCALER_2,
};

/**
 * \brief Main CPU division.
 *
 * Available division ratios for the CPU clocks.
 */
enum system_main_clock_div {
	/** Divide Main clock by one */
	SYSTEM_MAIN_CLOCK_DIV_1,
	/** Divide Main clock by two */
	SYSTEM_MAIN_CLOCK_DIV_2,
	/** Divide Main clock by four */
	SYSTEM_MAIN_CLOCK_DIV_4,
	/** Divide Main clock by eight */
	SYSTEM_MAIN_CLOCK_DIV_8,
	/** Divide Main clock by 16 */
	SYSTEM_MAIN_CLOCK_DIV_16,
	/** Divide Main clock by 32 */
	SYSTEM_MAIN_CLOCK_DIV_32,
	/** Divide Main clock by 64 */
	SYSTEM_MAIN_CLOCK_DIV_64,
	/** Divide Main clock by 128 */
	SYSTEM_MAIN_CLOCK_DIV_128,
};

/**
 * \brief External clock source types.
 *
 * Available external clock source types.
 */
enum system_clock_external {
	/** The external clock source is a crystal oscillator */
	SYSTEM_CLOCK_EXTERNAL_CRYSTAL,
	/** The connected clock source is an external logic level clock signal */
	SYSTEM_CLOCK_EXTERNAL_CLOCK,
};

/**
 * \brief Available clock sources in the system.
 *
 * Clock sources available to the GCLK generators
 */
enum system_clock_source {
	/** Internal 48MHz RC oscillator */
	SYSTEM_CLOCK_SOURCE_OSC48M    = GCLK_SOURCE_OSC48M,
	/** Internal 32KHz RC oscillator */
	SYSTEM_CLOCK_SOURCE_OSC32K   = GCLK_SOURCE_OSC32K,
	/** External oscillator */
	SYSTEM_CLOCK_SOURCE_XOSC     = GCLK_SOURCE_XOSC ,
	/** External 32KHz oscillator */
	SYSTEM_CLOCK_SOURCE_XOSC32K  = GCLK_SOURCE_XOSC32K,
	/** Internal Ultra Low Power 32KHz oscillator */
	SYSTEM_CLOCK_SOURCE_ULP32K   = GCLK_SOURCE_OSCULP32K,
	/** Generator input pad */
	SYSTEM_CLOCK_SOURCE_GCLKIN     = GCLK_SOURCE_GCLKIN,
	/** Generic clock generator one output */
	SYSTEM_CLOCK_SOURCE_GCLKGEN1   = GCLK_SOURCE_GCLKGEN1,
	/** Digital Phase Locked Loop (DPLL) */
	SYSTEM_CLOCK_SOURCE_DPLL     = GCLK_SOURCE_FDPLL,
};

/**
 * \brief List of APB peripheral buses.
 *
 * Available bus clock domains on the APB bus.
 */
enum system_clock_apb_bus {
	/** Peripheral bus A on the APB bus */
	SYSTEM_CLOCK_APB_APBA,
	/** Peripheral bus B on the APB bus */
	SYSTEM_CLOCK_APB_APBB,
	/** Peripheral bus C on the APB bus */
	SYSTEM_CLOCK_APB_APBC,
};

/**
 * \brief Configuration structure for XOSC.
 *
 * External oscillator clock configuration structure.
 */
struct system_clock_source_xosc_config {
	/** External clock type */
	enum system_clock_external external_clock;
	/** Crystal oscillator startup time */
	enum system_xosc_startup startup_time;
	/** Enable automatic amplitude gain control */
	bool auto_gain_control;
	/** External clock/crystal frequency */
	uint32_t frequency;
	/** Keep the XOSC enabled in standby sleep mode */
	bool run_in_standby;
	/** Run On Demand. If this is set the XOSC won't run
	 * until requested by a peripheral */
	bool on_demand;
	/** Clock failure detector prescaler from OSC48M for clock the CFD prescaler */
	enum system_clock_xosc_failure_detector_prescaler clock_failure_detector_prescaler;
	/** Enable clock failure detector event output */
	bool enable_clock_failure_detector_event_outut;
	/** Enable clock failure detector */
	bool enable_clock_failure_detector;
	/** Enable clock switch back */
	bool enable_clock_switch_back;
};

/**
 * \brief Configuration structure for XOSC32K.
 *
 * External 32KHz oscillator clock configuration structure.
 */
struct system_clock_source_xosc32k_config {
	/** External clock type */
	enum system_clock_external external_clock;
	/** Crystal oscillator startup time */
	enum system_xosc32k_startup startup_time;
	/** Enable 1KHz output */
	bool enable_1khz_output;
	/** Enable 32KHz output */
	bool enable_32khz_output;
	/** External clock/crystal frequency */
	uint32_t frequency;
	/** Keep the XOSC32K enabled in standby sleep mode */
	bool run_in_standby;
	/** Run On Demand. If this is set the XOSC32K won't run
	 * until requested by a peripheral */
	bool on_demand;
	/** Lock configuration after it has been written.
	 *  A device reset will release the lock */
	bool write_once;
	/** Clock failure detector prescaler from OSCULP32K */
	enum system_clock_xosc32k_failure_detector_prescaler clock_failure_detector_prescaler;
	/** Enable clock failure detector event output */
	bool enable_clock_failure_detector_event_outut;
	/** Enable clock failure detector */
	bool enable_clock_failure_detector;
	/** Enable clock switch back */
	bool enable_clock_switch_back;
};

/**
 * \brief Configuration structure for OSC48M.
 *
 * Internal 48MHz (nominal) oscillator configuration structure.
 */
struct system_clock_source_osc48m_config {
	/** Internal 48MHz RC oscillator divider */
	enum system_osc48m_div div;
	/** Keep the OSC48M enabled in standby sleep mode */
	bool run_in_standby;
	/** Run On Demand. If this is set the OSC48M won't run
	 * until requested by a peripheral */
	bool on_demand;
	/** Crystal oscillator startup time */
	enum system_osc48m_startup startup_time;
};

/**
 * \brief Configuration structure for OSCULP32K.
 *
 * Internal 32KHz Ultra Low Power oscillator configuration structure.
 */
struct system_clock_source_osculp32k_config {
	/** Lock configuration after it has been written,
	 *  a device reset will release the lock */
	bool write_once;
};

/**
 * \brief Configuration structure for OSCULP32K.
 *
 * Internal 32KHz  oscillator configuration structure.
 */
struct system_clock_source_osc32k_config {
	/** Startup time */
	enum system_osc32k_startup startup_time;
	/** Enable 1KHz output */
	bool enable_1khz_output;
	/** Enable 32KHz output */
	bool enable_32khz_output;
	/** Keep the OSC32K enabled in standby sleep mode */
	bool run_in_standby;
	/** Run On Demand. If this is set the OSC32K won't run
	 * until requested by a peripheral */
	bool on_demand;
	/** Lock configuration after it has been written,
	 *  a device reset will release the lock */
	bool write_once;
};

/**
 * \name External Oscillator Management
 * @{
 */

/**
 * \brief Retrieve the default configuration for XOSC.
 *
 * Fills a configuration structure with the default configuration for an
 * external oscillator module:
 *   - External Crystal
 *   - Startup time of 16384 external clock cycles
 *   - Automatic crystal gain control mode disabled
 *   - Frequency of 12MHz
 *   - Don't run in STANDBY sleep mode
 *   - Run when it's enabled (not on demand)
 *   - Clock failure detector prescaler is 1
 *   - Clock failure detector event outut is disabled
 *   - Clock failure detector is disabled
 *   - Clock switch back is disabled
 *
 * \param[out] config  Configuration structure to fill with default values
 */
static inline void system_clock_source_xosc_get_config_defaults(
		struct system_clock_source_xosc_config *const config)
{
	Assert(config);

	config->external_clock    = SYSTEM_CLOCK_EXTERNAL_CRYSTAL;
	config->startup_time      = SYSTEM_XOSC_STARTUP_16384;
	config->auto_gain_control = false;
	config->frequency         = 12000000UL;
	config->run_in_standby    = false;
	config->on_demand         = false;
	config->clock_failure_detector_prescaler = SYSTEM_CLOCK_XOSC_FAILURE_DETECTOR_PRESCALER_1;
	config->enable_clock_failure_detector_event_outut = false;
	config->enable_clock_failure_detector = false;
	config->enable_clock_switch_back = false;
}

void system_clock_source_xosc_set_config(
		struct system_clock_source_xosc_config *const config);

/**
 * \brief Checks if XOSC clock failure detected
 *
 * Checks if XOSC clock detected.
 *
 *
 * \returns XOSC clock failure detected state.
 *
 * \retval true   XOSC clock failure detected
 * \retval false  XOSC clock failure is not detected
 */
static inline bool system_clock_xosc_clock_failure_detected(void)
{
	return ((OSCCTRL->STATUS.reg & OSCCTRL_STATUS_XOSCFAIL) == OSCCTRL_STATUS_XOSCFAIL);
}

/**
 * \brief Checks if XOSC is switched and provides the safe clock
 *
 * Checks if XOSC is switched and provides the safe clock.
 *
 *
 * \returns XOSC clock switch state.
 *
 * \retval true   XOSC clock is switched and provides the safe clock
 * \retval false  XOSC clock is not switched and provides the external clock
 *  or crystal oscillator clock
 */

static inline bool system_clock_xosc_is_switched(void)
{
	return ((OSCCTRL->STATUS.reg & OSCCTRL_STATUS_XOSCCKSW) == OSCCTRL_STATUS_XOSCCKSW);
}

/**
 * @}
 */


/**
 * \name External 32KHz Oscillator Management
 * @{
 */

/**
 * \brief Retrieve the default configuration for XOSC32K.
 *
 * Fills a configuration structure with the default configuration for an
 * external 32KHz oscillator module:
 *   - External Crystal
 *   - Startup time of 16384 external clock cycles
 *   - Automatic crystal gain control mode disabled
 *   - Frequency of 32.768KHz
 *   - 1KHz clock output disabled
 *   - 32KHz clock output enabled
 *   - Don't run in STANDBY sleep mode
 *   - Run only when requested by peripheral (on demand)
 *   - Don't lock registers after configuration has been written
 *   - Clock failure detector prescaler is 1
 *   - Clock failure detector event outut is disabled
 *   - Clock failure detector is disabled
 *   - Clock switch back is disabled
 *
 * \param[out] config  Configuration structure to fill with default values
 */
static inline void system_clock_source_xosc32k_get_config_defaults(
		struct system_clock_source_xosc32k_config *const config)
{
	Assert(config);

	config->external_clock      = SYSTEM_CLOCK_EXTERNAL_CRYSTAL;
	config->startup_time        = SYSTEM_XOSC32K_STARTUP_16384;
	config->frequency           = 32768UL;
	config->enable_1khz_output  = false;
	config->enable_32khz_output = true;
	config->run_in_standby      = false;
	config->on_demand           = true;
	config->write_once          = false;
	config->clock_failure_detector_prescaler = SYSTEM_CLOCK_XOSC32K_FAILURE_DETECTOR_PRESCALER_1;
	config->enable_clock_failure_detector_event_outut = false;
	config->enable_clock_failure_detector = false;
	config->enable_clock_switch_back = false;
}

void system_clock_source_xosc32k_set_config(
		struct system_clock_source_xosc32k_config *const config);

/**
 * \brief Checks if XOSC32K clock failure detected
 *
 * Checks if XOSC32K clock detected.
 *
 *
 * \returns XOSC32K clock failure detected state.
 *
 * \retval true   XOSC32K clock failure detected
 * \retval false  XOSC32K clock failure is not detected
 */
static inline bool system_clock_xosc32k_clock_failure_detected(void)
{
	return ((OSC32KCTRL->STATUS.reg & OSC32KCTRL_STATUS_CLKFAIL) == OSC32KCTRL_STATUS_CLKFAIL);
}

/**
 * \brief Checks if XOSC32K is switched and provides the safe clock
 *
 * Checks if XOSC32K is switched and provides the safe clock.
 *
 *
 * \returns XOSC32K clock switch state.
 *
 * \retval true   XOSC32K clock is switched and provides the safe clock
 * \retval false  XOSC32K clock is not switched and provides the external clock
 *  or crystal oscillator clock
 */
static inline bool system_clock_xosc32k_is_switched(void)
{
	return ((OSC32KCTRL->STATUS.reg & OSC32KCTRL_STATUS_CLKSW) == OSC32KCTRL_STATUS_CLKSW);
}

/**
 * @}
 */


/**
 * \name Internal 32KHz Oscillator Management
 * @{
 */

/**
 * \brief Retrieve the default configuration for OSC32K.
 *
 * Fills a configuration structure with the default configuration for an
 * internal 32KHz oscillator module:
 *   - 1KHz clock output enabled
 *   - 32KHz clock output enabled
 *   - Don't run in STANDBY sleep mode
 *   - Run only when requested by peripheral (on demand)
 *   - Set startup time to 130 cycles
 *   - Don't lock registers after configuration has been written
 *
 * \param[out] config  Configuration structure to fill with default values
 */
static inline void system_clock_source_osc32k_get_config_defaults(
		struct system_clock_source_osc32k_config *const config)
{
	Assert(config);

	config->enable_1khz_output  = true;
	config->enable_32khz_output = true;
	config->run_in_standby      = false;
	config->on_demand           = true;
	config->startup_time        = SYSTEM_OSC32K_STARTUP_130;
	config->write_once          = false;
}

void system_clock_source_osc32k_set_config(
		struct system_clock_source_osc32k_config *const config);

/**
 * @}
 */

/**
 * \name Internal Ultra Low Power 32KHz Oscillator management
 * @{
 */

/**
 * \brief Retrieve the default configuration for OSCULP32K.
 *
 * Fills a configuration structure with the default configuration for an
 * internal Ultra Low Power 32KHz oscillator module:
 *   - 1KHz clock output enabled
 *   - 32KHz clock output enabled
 *
 * \param[out] config  Configuration structure to fill with default values
 */
static inline void system_clock_source_osculp32k_get_config_defaults(
		struct system_clock_source_osculp32k_config *const config)
{
	Assert(config);

	config->write_once          = false;
}

void system_clock_source_osculp32k_set_config(
		struct system_clock_source_osculp32k_config *const config);

/**
 * @}
 */


/**
 * \name Internal 48MHz Oscillator Management
 * @{
 */

/**
 * \brief Retrieve the default configuration for OSC48M.
 *
 * Fills a configuration structure with the default configuration for an
 * internal 48MHz (nominal) oscillator module:
 *   - Clock divider by 12 and output frequency 4MHz
 *   - Don't run in STANDBY sleep mode
 *   - Run only when requested by peripheral (on demand)
 *   - Startup time of eight clock cycles
 *
 * \param[out] config  Configuration structure to fill with default values
 */
static inline void system_clock_source_osc48m_get_config_defaults(
		struct system_clock_source_osc48m_config *const config)
{
	Assert(config);

	config->div = SYSTEM_OSC48M_DIV_12;
	config->run_in_standby  = false;
	config->on_demand       = true;
	config->startup_time = SYSTEM_OSC48M_STARTUP_8;
}

void system_clock_source_osc48m_set_config(
		struct system_clock_source_osc48m_config *const config);

/**
 * @}
 */

/**
 * \name Clock Source Management
 * @{
 */
enum status_code system_clock_source_write_calibration(
		const enum system_clock_source system_clock_source,
		const uint16_t calibration_value,
		const uint8_t freq_range);

enum status_code system_clock_source_enable(
		const enum system_clock_source system_clock_source);

enum status_code system_clock_source_disable(
		const enum system_clock_source clk_source);

bool system_clock_source_is_ready(
		const enum system_clock_source clk_source);

uint32_t system_clock_source_get_hz(
		const enum system_clock_source clk_source);

/**
 * @}
 */

/**
 * \name Main Clock Management
 * @{
 */

/**
 * \brief Set main CPU clock divider.
 *
 * Sets the clock divider used on the main clock to provide the CPU clock.
 *
 * \param[in] divider  CPU clock divider to set
 */
static inline void system_cpu_clock_set_divider(
		const enum system_main_clock_div divider)
{
	MCLK->CPUDIV.reg = MCLK_CPUDIV_CPUDIV(1 << divider);
}

/**
 * \brief Retrieves the current frequency of the CPU core.
 *
 * Retrieves the operating frequency of the CPU core, obtained from the main
 * generic clock and the set CPU bus divider.
 *
 * \return Current CPU frequency in Hz.
 */
static inline uint32_t system_cpu_clock_get_hz(void)
{
	return (system_gclk_gen_get_hz(GCLK_GENERATOR_0) / MCLK->CPUDIV.reg);

}

/**
 * @}
 */

/**
 * \name Bus Clock Masking
 * @{
 */

/**
 * \brief Set bits in the clock mask for the AHB bus.
 *
 * This function will set bits in the clock mask for the AHB bus.
 * Any bits set to 1 will enable that clock, zero bits in the mask
 * will be ignored
 *
 * \param[in] ahb_mask  AHB clock mask to enable
 */
static inline void system_ahb_clock_set_mask(
		const uint32_t ahb_mask)
{
	MCLK->AHBMASK.reg |= ahb_mask;
}

/**
 * \brief Clear bits in the clock mask for the AHB bus.
 *
 * This function will clear bits in the clock mask for the AHB bus.
 * Any bits set to 1 will disable that clock, zero bits in the mask
 * will be ignored.
 *
 * \param[in] ahb_mask  AHB clock mask to disable
 */
static inline void system_ahb_clock_clear_mask(
		const uint32_t ahb_mask)
{
	MCLK->AHBMASK.reg &= ~ahb_mask;
}

/**
 * \brief Set bits in the clock mask for an APBx bus.
 *
 * This function will set bits in the clock mask for an APBx bus.
 * Any bits set to 1 will enable the corresponding module clock, zero bits in
 * the mask will be ignored.
 *
 * \param[in] mask  APBx clock mask, a \c SYSTEM_CLOCK_APB_APBx constant from
 *                  the device header files
 * \param[in] bus   Bus to set clock mask bits for, a mask of \c PM_APBxMASK_*
 *                  constants from the device header files
 *
 * \returns Status indicating the result of the clock mask change operation.
 *
 * \retval STATUS_ERR_INVALID_ARG  Invalid bus given
 * \retval STATUS_OK               The clock mask was set successfully
 */
static inline enum status_code system_apb_clock_set_mask(
		const enum system_clock_apb_bus bus,
		const uint32_t mask)
{
	switch (bus) {
		case SYSTEM_CLOCK_APB_APBA:
			MCLK->APBAMASK.reg |= mask;
			break;

		case SYSTEM_CLOCK_APB_APBB:
			MCLK->APBBMASK.reg |= mask;
			break;

		case SYSTEM_CLOCK_APB_APBC:
			MCLK->APBCMASK.reg |= mask;
			break;
		default:
			Assert(false);
			return STATUS_ERR_INVALID_ARG;

	}

	return STATUS_OK;
}

/**
 * \brief Clear bits in the clock mask for an APBx bus.
 *
 * This function will clear bits in the clock mask for an APBx bus.
 * Any bits set to 1 will disable the corresponding module clock, zero bits in
 * the mask will be ignored.
 *
 * \param[in] mask  APBx clock mask, a \c SYSTEM_CLOCK_APB_APBx constant from
 *                  the device header files
 * \param[in] bus   Bus to clear clock mask bits
 *
 * \returns Status indicating the result of the clock mask change operation.
 *
 * \retval STATUS_ERR_INVALID_ARG  Invalid bus ID was given
 * \retval STATUS_OK               The clock mask was changed successfully
 */
static inline enum status_code system_apb_clock_clear_mask(
		const enum system_clock_apb_bus bus,
		const uint32_t mask)
{
	switch (bus) {
		case SYSTEM_CLOCK_APB_APBA:
			MCLK->APBAMASK.reg &= ~mask;
			break;

		case SYSTEM_CLOCK_APB_APBB:
			MCLK->APBBMASK.reg &= ~mask;
			break;

		case SYSTEM_CLOCK_APB_APBC:
			MCLK->APBCMASK.reg &= ~mask;
			break;
		default:
			Assert(false);
			return STATUS_ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

/**
 * @}
 */

/**
 * \brief Reference clock source of the DPLL module.
 */
enum system_clock_source_dpll_reference_clock {
	/** Select XOSC32K as clock reference */
	SYSTEM_CLOCK_SOURCE_DPLL_REFERENCE_CLOCK_XOSC32K,
	/** Select XOSC as clock reference */
	SYSTEM_CLOCK_SOURCE_DPLL_REFERENCE_CLOCK_XOSC,
	/** Select GCLK as clock reference */
	SYSTEM_CLOCK_SOURCE_DPLL_REFERENCE_CLOCK_GCLK,
};

/**
 * \brief Lock time-out value of the DPLL module.
 */
enum system_clock_source_dpll_lock_time {
	/** Set no time-out as default */
	SYSTEM_CLOCK_SOURCE_DPLL_LOCK_TIME_DEFAULT,
	/** Set time-out if no lock within 8ms */
	SYSTEM_CLOCK_SOURCE_DPLL_LOCK_TIME_8MS = 0x04,
	/** Set time-out if no lock within 9ms */
	SYSTEM_CLOCK_SOURCE_DPLL_LOCK_TIME_9MS,
	/** Set time-out if no lock within 10ms */
	SYSTEM_CLOCK_SOURCE_DPLL_LOCK_TIME_10MS,
	/** Set time-out if no lock within 11ms */
	SYSTEM_CLOCK_SOURCE_DPLL_LOCK_TIME_11MS,
};

/**
 * \brief Filter type of the DPLL module.
 */
enum system_clock_source_dpll_filter {
	/** Default filter mode */
	SYSTEM_CLOCK_SOURCE_DPLL_FILTER_DEFAULT,
	/** Low bandwidth filter */
	SYSTEM_CLOCK_SOURCE_DPLL_FILTER_LOW_BANDWIDTH_FILTER,
	/** High bandwidth filter */
	SYSTEM_CLOCK_SOURCE_DPLL_FILTER_HIGH_BANDWIDTH_FILTER,
	/** High damping filter */
	SYSTEM_CLOCK_SOURCE_DPLL_FILTER_HIGH_DAMPING_FILTER,
};

/**
 * \brief DPLL Output Clock Prescaler.
 */
enum system_clock_source_dpll_prescaler {
	/** DPLL output is divided by 1 */
	SYSTEM_CLOCK_SOURCE_DPLL_DIV_1,
	/** DPLL output is divided by 2 */
	SYSTEM_CLOCK_SOURCE_DPLL_DIV_2,
	/** DPLL output is divided by 4 */
	SYSTEM_CLOCK_SOURCE_DPLL_DIV_4,
};

/**
 * \brief Configuration structure for DPLL.
 *
 * DPLL oscillator configuration structure.
 */
struct system_clock_source_dpll_config {
	/** Run On Demand. If this is set the DPLL won't run
	 * until requested by a peripheral */
	bool on_demand;
	/** Keep the DPLL enabled in standby sleep mode */
	bool run_in_standby;
	/** Bypass lock signal */
	bool lock_bypass;
	/** Wake up fast. If this is set DPLL output clock is enabled after
	 * the startup time */
	bool wake_up_fast;
	/** Enable low power mode  */
	bool low_power_enable;

	/** Output frequency of the clock */
	uint32_t output_frequency;
	/** Reference frequency of the clock */
	uint32_t reference_frequency;
	/** Devider of reference clock */
	uint16_t reference_divider;

	/** Filter type of the DPLL module */
	enum system_clock_source_dpll_filter          filter;
	/** Lock time-out value of the DPLL module */
	enum system_clock_source_dpll_lock_time       lock_time;
	/** Reference clock source of the DPLL module */
	enum system_clock_source_dpll_reference_clock reference_clock;
	/** DPLL prescaler*/
	enum system_clock_source_dpll_prescaler  prescaler;
};

/**
 * \name Internal DPLL Management
 * @{
 */

/**
 * \brief Retrieve the default configuration for DPLL.
 *
 * Fills a configuration structure with the default configuration for a
 * DPLL oscillator module:
 *   - Run only when requested by peripheral (on demand)
 *   - Don't run in STANDBY sleep mode
 *   - Lock bypass disabled
 *   - Fast wake up disabled
 *   - Low power mode disabled
 *   - Output frequency is 48MHz
 *   - Reference clock frequency is 32768Hz
 *   - Not divide reference clock
 *   - Select REF0 as reference clock
 *   - Set lock time to default mode
 *   - Use default filter
 *
 * \param[out] config  Configuration structure to fill with default values
 */
static inline void system_clock_source_dpll_get_config_defaults(
		struct system_clock_source_dpll_config *const config)
{
	config->on_demand           = true;
	config->run_in_standby      = false;
	config->lock_bypass         = false;
	config->wake_up_fast        = false;
	config->low_power_enable    = false;

	config->output_frequency    = 48000000;
	config->reference_frequency = 32768;
	config->reference_divider   = 1;
	config->reference_clock     = SYSTEM_CLOCK_SOURCE_DPLL_REFERENCE_CLOCK_GCLK;
	config->prescaler           = SYSTEM_CLOCK_SOURCE_DPLL_DIV_1;

	config->lock_time           = SYSTEM_CLOCK_SOURCE_DPLL_LOCK_TIME_DEFAULT;
	config->filter              = SYSTEM_CLOCK_SOURCE_DPLL_FILTER_DEFAULT;
};

void system_clock_source_dpll_set_config(
		struct system_clock_source_dpll_config *const config);

/* @} */

/**
 * \name System Clock Initialization
 * @{
 */

void system_clock_init(void);

/**
 * @}
 */

/**
 * \name System Flash Wait States
 * @{
 */

/**
 * \brief Set flash controller wait states.
 *
 * Will set the number of wait states that are used by the onboard
 * flash memory. The number of wait states depend on both device
 * supply voltage and CPU speed. The required number of wait states
 * can be found in the electrical characteristics of the device.
 *
 * \param[in] wait_states Number of wait states to use for internal flash
 */
static inline void system_flash_set_waitstates(uint8_t wait_states)
{
	Assert(NVMCTRL_CTRLB_RWS((uint32_t)wait_states) ==
			((uint32_t)wait_states << NVMCTRL_CTRLB_RWS_Pos));

	NVMCTRL->CTRLB.bit.RWS = wait_states;
}
/**
 * @}
 */

/**
 * @}
 */

/**
 * \page asfdoc_sam0_system_clock_extra Extra Information for SYSTEM CLOCK Driver
 *
 * \section asfdoc_sam0_system_clock_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *	<tr>
 *		<th>Acronym</th>
 *		<th>Description</th>
 *	</tr>
 *	<tr>
 *		<td>DFLL</td>
 *		<td>Digital Frequency Locked Loop</td>
 *	</tr>
 *	<tr>
 *		<td>MUX</td>
 *		<td>Multiplexer</td>
 *	</tr>
 *	<tr>
 *		<td>MCLK</td>
 *		<td>Main Clock</td>
 *	</tr>
 *	<tr>
 *		<td>OSC32K</td>
 *		<td>Internal 32KHz Oscillator</td>
 *	</tr>
 *	<tr>
 *		<td>OSC48M</td>
 *		<td>Internal 48MHz Oscillator</td>
 *	</tr>
 *	<tr>
 *		<td>PLL</td>
 *		<td>Phase Locked Loop</td>
 *	</tr>
 *	<tr>
 *		<td>OSC</td>
 *		<td>Oscillator</td>
 *	</tr>
 *	<tr>
 *		<td>XOSC</td>
 *		<td>External Oscillator</td>
 *	</tr>
 *	<tr>
 *		<td>XOSC32K</td>
 *		<td>External 32KHz Oscillator</td>
 *	</tr>
 *	<tr>
 *		<td>AHB</td>
 *		<td>Advanced High-performance Bus</td>
 *	</tr>
 *	<tr>
 *		<td>APB</td>
 *		<td>Advanced Peripheral Bus</td>
 *	</tr>
 *	<tr>
 *		<td>DPLL</td>
 *		<td>Digital Phase Locked Loop</td>
 *	</tr>
 * </table>
 *
 *
 * \section asfdoc_sam0_system_clock_extra_dependencies Dependencies
 * This driver has the following dependencies:
 *
 *  - None
 *
 *
 * \section asfdoc_sam0_system_clock_extra_errata Errata
 *
 * There are no errata related to this driver.
 *
 * \section asfdoc_sam0_system_clock_extra_history Module History
 * An overview of the module history is presented in the table below, with
 * details on the enhancements and fixes made to the module since its first
 * release. The current version of this corresponds to the newest version in
 * the table.
 *
 * <table>
 *	<tr>
 *		<th>Changelog</th>
 *	</tr>
 *	<tr>
 *		<td>Initial Release</td>
 *	</tr>
 * </table>
 */

/**
 * \page asfdoc_sam0_system_clock_exqsg Examples for System Clock Driver
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_sam0_system_clock_group. QSGs are simple
 * examples with step-by-step instructions to configure and use this driver in
 * a selection of use cases. Note that a QSG can be compiled as a standalone
 * application or be added to the user application.
 *
 *  - \subpage asfdoc_sam0_system_clock_basic_use_case
 *  - \subpage asfdoc_sam0_system_gclk_basic_use_case
 *
 * \page asfdoc_sam0_system_clock_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</td>
 *		<th>Date</td>
 *		<th>Comments</td>
 *	</tr>
 *	<tr>
 *		<td>42647A</td>
 *		<td>01/2016</td>
 *		<td>Initial document release</td>
 *	</tr>
 * </table>
 */

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_CLOCK_FEATURE_H_INCLUDED */
