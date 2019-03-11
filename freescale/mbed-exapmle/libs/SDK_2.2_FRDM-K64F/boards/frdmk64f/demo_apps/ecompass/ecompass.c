/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "fsl_debug_console.h"
#include "fsl_fxos.h"
#include "board.h"
#include "math.h"

#include "fsl_common.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* I2C source clock */
#define ACCEL_I2C_CLK_SRC I2C0_CLK_SRC
#define ACCEL_I2C_CLK_FREQ CLOCK_GetFreq(I2C0_CLK_SRC)
#define I2C_BAUDRATE 100000U
#define ACCEL_I2C_ADDR 1DU

#define I2C_RELEASE_SDA_PORT PORTE
#define I2C_RELEASE_SCL_PORT PORTE
#define I2C_RELEASE_SDA_GPIO GPIOE
#define I2C_RELEASE_SDA_PIN 25U
#define I2C_RELEASE_SCL_GPIO GPIOE
#define I2C_RELEASE_SCL_PIN 24U
#define I2C_RELEASE_BUS_COUNT 100U
#define MAX_ACCEL_AVG_COUNT 25U
#define HWTIMER_PERIOD      10000U
/* multiplicative conversion constants */
#define DegToRad 0.017453292
#define RadToDeg 57.295779
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_I2C_ReleaseBus(void);

/*!
 * @brief Read all data from sensor function
 *
 * @param Ax The pointer store x axis acceleration value
 * @param Ay The pointer store y axis acceleration value
 * @param Az The pointer store z axis acceleration value
 * @param Mx The pointer store x axis magnetic value
 * @param My The pointer store y axis magnetic value
 * @param Mz The pointer store z axis magnetic value
 * @note Must calculate g_dataScale before use this function.
 */
static void Sensor_ReadData(int16_t *Ax, int16_t *Ay, int16_t *Az, int16_t *Mx, int16_t *My, int16_t *Mz);

/*!
 * @brief Magnetometer calibration
 *
 */
static void Magnetometer_Calibrate(void);

/*!
 * @brief Hardware timer initialize
 *
 */
static void HW_Timer_init(void);

/*!
 * @brief Delay function
 *
 * @param ticks Cycle clock delay
 */
static void Delay(uint32_t ticks);
/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(FSL_FEATURE_SOC_LPI2C_COUNT) && (FSL_FEATURE_SOC_LPI2C_COUNT)
extern void FXOS_master_callback(LPI2C_Type *base, lpi2c_master_handle_t *handle, status_t status, void *userData);
lpi2c_master_handle_t g_MasterHandle;
#else
i2c_master_handle_t g_MasterHandle;
#endif

volatile uint16_t SampleEventFlag;
fxos_handle_t g_fxosHandle;
uint8_t g_sensor_address[] = {0x1CU, 0x1EU, 0x1DU, 0x1FU};
uint8_t g_sensorRange = 0;
uint8_t g_dataScale = 0;

int16_t g_Ax_Raw = 0;
int16_t g_Ay_Raw = 0;
int16_t g_Az_Raw = 0;

double g_Ax = 0;
double g_Ay = 0;
double g_Az = 0;

int16_t g_Ax_buff[MAX_ACCEL_AVG_COUNT] = {0};
int16_t g_Ay_buff[MAX_ACCEL_AVG_COUNT] = {0};
int16_t g_Az_buff[MAX_ACCEL_AVG_COUNT] = {0};

int16_t g_Mx_Raw = 0;
int16_t g_My_Raw = 0;
int16_t g_Mz_Raw = 0;

int16_t g_Mx_Offset = 0;
int16_t g_My_Offset = 0;
int16_t g_Mz_Offset = 0;

double g_Mx = 0;
double g_My = 0;
double g_Mz = 0;

double g_Mx_LP = 0;
double g_My_LP = 0;
double g_Mz_LP = 0;

double g_Yaw = 0;
double g_Yaw_LP = 0;
double g_Pitch = 0;
double g_Roll = 0;

bool g_FirstRun = true;

/*******************************************************************************
 * Code
 ******************************************************************************/

static void i2c_release_bus_delay(void)
{
    uint32_t i = 0;
    for (i = 0; i < I2C_RELEASE_BUS_COUNT; i++)
    {
        __NOP();
    }
}

void BOARD_I2C_ReleaseBus(void)
{
    uint8_t i = 0;
    gpio_pin_config_t pin_config;
    port_pin_config_t i2c_pin_config = {0};

    /* Config pin mux as gpio */
    i2c_pin_config.pullSelect = kPORT_PullUp;
    i2c_pin_config.mux = kPORT_MuxAsGpio;

    pin_config.pinDirection = kGPIO_DigitalOutput;
    pin_config.outputLogic = 1U;
    CLOCK_EnableClock(kCLOCK_PortE);
    PORT_SetPinConfig(I2C_RELEASE_SCL_PORT, I2C_RELEASE_SCL_PIN, &i2c_pin_config);
    PORT_SetPinConfig(I2C_RELEASE_SDA_PORT, I2C_RELEASE_SDA_PIN, &i2c_pin_config);

    GPIO_PinInit(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, &pin_config);
    GPIO_PinInit(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, &pin_config);

    /* Drive SDA low first to simulate a start */
    GPIO_WritePinOutput(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 0U);
    i2c_release_bus_delay();

    /* Send 9 pulses on SCL and keep SDA high */
    for (i = 0; i < 9; i++)
    {
        GPIO_WritePinOutput(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 0U);
        i2c_release_bus_delay();

        GPIO_WritePinOutput(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 1U);
        i2c_release_bus_delay();

        GPIO_WritePinOutput(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 1U);
        i2c_release_bus_delay();
        i2c_release_bus_delay();
    }

    /* Send stop */
    GPIO_WritePinOutput(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_WritePinOutput(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_WritePinOutput(I2C_RELEASE_SCL_GPIO, I2C_RELEASE_SCL_PIN, 1U);
    i2c_release_bus_delay();

    GPIO_WritePinOutput(I2C_RELEASE_SDA_GPIO, I2C_RELEASE_SDA_PIN, 1U);
    i2c_release_bus_delay();
}
static void HW_Timer_init(void)
{
    /* Configure the SysTick timer */
    SysTick_Config(SystemCoreClock / HWTIMER_PERIOD);
}

void SysTick_Handler(void)
{
    SampleEventFlag = 1;
}

static void Delay(uint32_t ticks)
{
    while (ticks--)
    {
        __asm("nop");
    }
}

static void Sensor_ReadData(int16_t *Ax, int16_t *Ay, int16_t *Az, int16_t *Mx, int16_t *My, int16_t *Mz)
{
    fxos_data_t fxos_data;

    if (FXOS_ReadSensorData(&g_fxosHandle, &fxos_data) != kStatus_Success)
    {
        PRINTF("Failed to read acceleration data!\r\n");
    }
    /* Get the accel data from the sensor data structure in 14 bit left format data*/
    *Ax = (int16_t)((uint16_t)((uint16_t)fxos_data.accelXMSB << 8) | (uint16_t)fxos_data.accelXLSB)/4U;
    *Ay = (int16_t)((uint16_t)((uint16_t)fxos_data.accelYMSB << 8) | (uint16_t)fxos_data.accelYLSB)/4U;
    *Az = (int16_t)((uint16_t)((uint16_t)fxos_data.accelZMSB << 8) | (uint16_t)fxos_data.accelZLSB)/4U;
    *Ax *= g_dataScale;
    *Ay *= g_dataScale;
    *Az *= g_dataScale;
    *Mx = (int16_t)((uint16_t)((uint16_t)fxos_data.magXMSB << 8) | (uint16_t)fxos_data.magXLSB);
    *My = (int16_t)((uint16_t)((uint16_t)fxos_data.magYMSB << 8) | (uint16_t)fxos_data.magYLSB);
    *Mz = (int16_t)((uint16_t)((uint16_t)fxos_data.magZMSB << 8) | (uint16_t)fxos_data.magZLSB);
}

static void Magnetometer_Calibrate(void)
{
    int16_t Mx_max = 0;
    int16_t My_max = 0;
    int16_t Mz_max = 0;
    int16_t Mx_min = 0;
    int16_t My_min = 0;
    int16_t Mz_min = 0;

    uint32_t times = 0;
    PRINTF("\r\nCalibrating magnetometer...");
    while (times < 5000)
    {
        Sensor_ReadData(&g_Ax_Raw, &g_Ay_Raw, &g_Az_Raw, &g_Mx_Raw, &g_My_Raw, &g_Mz_Raw);
        if (times == 0)
        {
            Mx_max = Mx_min = g_Mx_Raw;
            My_max = My_min = g_My_Raw;
            Mz_max = Mz_min = g_Mz_Raw;
        }
        if (g_Mx_Raw > Mx_max)
        {
            Mx_max = g_Mx_Raw;
        }
        if (g_My_Raw > My_max)
        {
            My_max = g_My_Raw;
        }
        if (g_Mz_Raw > Mz_max)
        {
            Mz_max = g_Mz_Raw;
        }
        if (g_Mx_Raw < Mx_min)
        {
            Mx_min = g_Mx_Raw;
        }
        if (g_My_Raw < My_min)
        {
            My_min = g_My_Raw;
        }
        if (g_Mz_Raw < Mz_min)
        {
            Mz_min = g_Mz_Raw;
        }
        if (times == 4999)
        {
            if ((Mx_max > (Mx_min + 500)) && (My_max > (My_min + 500)) && (Mz_max > (Mz_min + 500)))
            {
                g_Mx_Offset = (Mx_max + Mx_min) / 2;
                g_My_Offset = (My_max + My_min) / 2;
                g_Mz_Offset = (Mz_max + Mz_min) / 2;
                PRINTF("\r\nCalibrate magnetometer successfully!");
                PRINTF("\r\nMagnetometer offset Mx: %d - My: %d - Mz: %d \r\n", g_Mx_Offset, g_My_Offset, g_Mz_Offset);
            }
            else
            {
                PRINTF("Calibrating magnetometer failed! Press any key to recalibrate...\r\n");
                GETCHAR();
                PRINTF("\r\nCalibrating magnetometer...");
                times = 0;
            }
        }
        times++;
        Delay(3000);
    }
}

int main(void)
{
#if defined(FSL_FEATURE_SOC_LPI2C_COUNT) && (FSL_FEATURE_SOC_LPI2C_COUNT)
    lpi2c_master_config_t i2cConfig;
#else
    i2c_master_config_t i2cConfig;
#endif
    uint32_t i2cSourceClock;
    uint16_t i = 0;
    uint16_t loopCounter = 0;
    uint8_t regResult = 0;
    double sinAngle = 0;
    double cosAngle = 0;
    double Bx = 0;
    double By = 0;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_I2C_ReleaseBus();
    BOARD_I2C_ConfigurePins();
    BOARD_InitDebugConsole();

    HW_Timer_init();

#if defined(FSL_FEATURE_SOC_LPI2C_COUNT) && (FSL_FEATURE_SOC_LPI2C_COUNT)
    i2cSourceClock = LPI2C_CLOCK_FREQUENCY;
    /*
     * i2cConfig.debugEnable = false;
     * i2cConfig.ignoreAck = false;
     * i2cConfig.pinConfig = kLPI2C_2PinOpenDrain;
     * i2cConfig.baudRate_Bps = 100000U;
     * i2cConfig.busIdleTimeout_ns = 0;
     * i2cConfig.pinLowTimeout_ns = 0;
     * i2cConfig.sdaGlitchFilterWidth_ns = 0;
     * i2cConfig.sclGlitchFilterWidth_ns = 0;
     */
    LPI2C_MasterGetDefaultConfig(&i2cConfig);
    LPI2C_MasterInit(BOARD_ACCEL_I2C_BASEADDR, &i2cConfig, i2cSourceClock);
    LPI2C_MasterTransferCreateHandle(BOARD_ACCEL_I2C_BASEADDR, &g_MasterHandle, FXOS_master_callback, NULL);
#else
    i2cSourceClock = ACCEL_I2C_CLK_FREQ;
    /*
     * i2cConfig.baudRate_Bps = 100000U;
     * i2cConfig.enableStopHold = false;
     * i2cConfig.glitchFilterWidth = 0U;
     * i2cConfig.enableMaster = true;
     */
    I2C_MasterGetDefaultConfig(&i2cConfig);
    I2C_MasterInit(BOARD_ACCEL_I2C_BASEADDR, &i2cConfig, i2cSourceClock);
    I2C_MasterTransferCreateHandle(BOARD_ACCEL_I2C_BASEADDR, &g_MasterHandle, NULL, NULL);
#endif
    g_fxosHandle.base = BOARD_ACCEL_I2C_BASEADDR;
    g_fxosHandle.i2cHandle = &g_MasterHandle;

    /* Find sensor on board */
    for (i = 0; i < 4; i++)
    {
        g_fxosHandle.xfer.slaveAddress = g_sensor_address[i];
        if (FXOS_ReadReg(&g_fxosHandle, WHO_AM_I_REG, &regResult, 1) == kStatus_Success)
        {
            if(regResult == kFXOS_WHO_AM_I_Device_ID)
            {
                break;
            }
        }
        else /* Not found any sensor on board */
        {
            if (i == 3)
            {
                PRINTF("\r\nFailed to initialize the sensor device!");
                while (1)
                {
                }
            }
        }
    }

    /* Init sensor */
    if (FXOS_Init(&g_fxosHandle) != kStatus_Success)
    {
        return -1;
    }
    /* Get sensor range */
    if (FXOS_ReadReg(&g_fxosHandle, XYZ_DATA_CFG_REG, &g_sensorRange, 1) != kStatus_Success)
    {
        return -1;
    }
    if(g_sensorRange == 0x00)
    {
        g_dataScale = 2U;
    }
    else if(g_sensorRange == 0x01)
    {
        g_dataScale = 4U;
    }
    else if(g_sensorRange == 0x10)
    {
        g_dataScale = 8U;
    }
    else
    {
    }

    PRINTF("\r\nTo calibrate Magnetometer, roll the board on all orientations to get max and min values\r\n");
    PRINTF("\r\nPress any key to start calibrating...\r\n");
    GETCHAR();
    Magnetometer_Calibrate();

    /* Infinite loops */
    for (;;)
    {
        if (SampleEventFlag == 1) /* Fix loop */
        {
            SampleEventFlag = 0;
            g_Ax_Raw = 0;
            g_Ay_Raw = 0;
            g_Az_Raw = 0;
            g_Ax = 0;
            g_Ay = 0;
            g_Az = 0;
            g_Mx_Raw = 0;
            g_My_Raw = 0;
            g_Mz_Raw = 0;
            g_Mx = 0;
            g_My = 0;
            g_Mz = 0;

            /* Read sensor data */
            Sensor_ReadData(&g_Ax_Raw, &g_Ay_Raw, &g_Az_Raw, &g_Mx_Raw, &g_My_Raw, &g_Mz_Raw);

            /* Average accel value */
            for (i = 1; i < MAX_ACCEL_AVG_COUNT; i++)
            {
                g_Ax_buff[i] = g_Ax_buff[i - 1];
                g_Ay_buff[i] = g_Ay_buff[i - 1];
                g_Az_buff[i] = g_Az_buff[i - 1];
            }

            g_Ax_buff[0] = g_Ax_Raw;
            g_Ay_buff[0] = g_Ay_Raw;
            g_Az_buff[0] = g_Az_Raw;

            for (i = 0; i < MAX_ACCEL_AVG_COUNT; i++)
            {
                g_Ax += (double)g_Ax_buff[i];
                g_Ay += (double)g_Ay_buff[i];
                g_Az += (double)g_Az_buff[i];
            }

            g_Ax /= MAX_ACCEL_AVG_COUNT;
            g_Ay /= MAX_ACCEL_AVG_COUNT;
            g_Az /= MAX_ACCEL_AVG_COUNT;

            if(g_FirstRun)
            {
                g_Mx_LP = g_Mx_Raw;
                g_My_LP = g_My_Raw;
                g_Mz_LP = g_Mz_Raw;
            }

            g_Mx_LP += ((double)g_Mx_Raw - g_Mx_LP) * 0.01;
            g_My_LP += ((double)g_My_Raw - g_My_LP) * 0.01;
            g_Mz_LP += ((double)g_Mz_Raw - g_Mz_LP) * 0.01;

            /* Calculate magnetometer values */
            g_Mx = g_Mx_LP - g_Mx_Offset;
            g_My = g_My_LP - g_My_Offset;
            g_Mz = g_Mz_LP - g_Mz_Offset;

            /* Calculate roll angle g_Roll (-180deg, 180deg) and sin, cos */
            g_Roll = atan2(g_Ay, g_Az) * RadToDeg;
            sinAngle = sin(g_Roll * DegToRad);
            cosAngle = cos(g_Roll * DegToRad);

            /* De-rotate by roll angle g_Roll */
            By = g_My * cosAngle - g_Mz * sinAngle;
            g_Mz = g_Mz * cosAngle + g_My * sinAngle;
            g_Az = g_Ay * sinAngle + g_Az * cosAngle;

            /* Calculate pitch angle g_Pitch (-90deg, 90deg) and sin, cos*/
            g_Pitch = atan2(-g_Ax , g_Az) * RadToDeg;
            sinAngle = sin(g_Pitch * DegToRad);
            cosAngle = cos(g_Pitch * DegToRad);

            /* De-rotate by pitch angle g_Pitch */
            Bx = g_Mx * cosAngle + g_Mz * sinAngle;

            /* Calculate yaw = ecompass angle psi (-180deg, 180deg) */
            g_Yaw = atan2(-By, Bx) * RadToDeg;
            if(g_FirstRun)
            {
                g_Yaw_LP = g_Yaw;
                g_FirstRun = false;
            }

            g_Yaw_LP += (g_Yaw - g_Yaw_LP) * 0.01;

            if (++loopCounter > 10)
            {
                PRINTF("\r\nCompass Angle: %3.1lf", g_Yaw_LP);
                loopCounter = 0;
            }
        }
    } /* End infinite loops */
}
