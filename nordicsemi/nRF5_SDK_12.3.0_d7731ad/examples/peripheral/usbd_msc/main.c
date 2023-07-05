/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <inttypes.h>
#include <stdlib.h>

#include "nrf.h"
#include "nrf_block_dev.h"
#include "nrf_block_dev_ram.h"
#include "nrf_block_dev_empty.h"
#include "nrf_block_dev_qspi.h"
#include "nrf_block_dev_sdc.h"
#include "nrf_drv_usbd.h"
#include "nrf_drv_clock.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_drv_power.h"

#include "ff.h"
#include "diskio_blkdev.h"

#include "app_usbd.h"
#include "app_usbd_core.h"
#include "app_usbd_string_desc.h"
#include "app_usbd_msc.h"

#include "boards.h"

#define NRF_LOG_MODULE_NAME "APP"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

/**@file
 * @defgroup usbd_msc_example main.c
 * @{
 * @ingroup usbd_msc_example
 * @brief USBD MSC example
 *
 */

#define LED_USB_RESUME   (BSP_BOARD_LED_0)
#define LED_USB_START    (BSP_BOARD_LED_1)

#define BTN_RANDOM_FILE (BSP_BOARD_BUTTON_0)
#define BTN_LIST_DIR    (BSP_BOARD_BUTTON_1)
#define BTN_MKFS        (BSP_BOARD_BUTTON_2)

/**
 * @brief Enable power USB detection
 *
 * Configure if example supports USB port connection
 */
#ifndef USBD_POWER_DETECTION
#define USBD_POWER_DETECTION true
#endif

/**
 * @brief SD card enable/disable
 * */
#define USE_SD_CARD       0

/**
 * @brief FatFS for QPSI enable/disable
 * */
#define USE_FATFS_QSPI    1

/**
 * @brief Mass storage class user event handler
 * */
static void msc_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                app_usbd_msc_user_event_t     event);


/**
 * @brief Ram block device size
 * */
#define RAM_BLOCK_DEVICE_SIZE (256 * 512)

/**
 * @brief  RAM block device work buffer
 * */
static uint8_t m_block_dev_ram_buff[RAM_BLOCK_DEVICE_SIZE];

/**
 * @brief  RAM block device definition
 * */
NRF_BLOCK_DEV_RAM_DEFINE(
      m_block_dev_ram,
      NRF_BLOCK_DEV_RAM_CONFIG(512, m_block_dev_ram_buff, sizeof(m_block_dev_ram_buff)),
      NFR_BLOCK_DEV_INFO_CONFIG("Nordic", "RAM", "1.00")
);


/**
 * @brief Empty block device definition
 * */
NRF_BLOCK_DEV_EMPTY_DEFINE(
        m_block_dev_empty,
        NRF_BLOCK_DEV_EMPTY_CONFIG(512, 1024 * 1024),
        NFR_BLOCK_DEV_INFO_CONFIG("Nordic", "EMPTY", "1.00")
);


/**
 * @brief  QSPI block device definition
 * */
NRF_BLOCK_DEV_QSPI_DEFINE(
        m_block_dev_qspi,
        NRF_BLOCK_DEV_QSPI_CONFIG(
                512,
                NRF_BLOCK_DEV_QSPI_FLAG_CACHE_WRITEBACK,
                NRF_DRV_QSPI_DEFAULT_CONFIG
         ),
         NFR_BLOCK_DEV_INFO_CONFIG("Nordic", "QSPI", "1.00")
);

#if USE_SD_CARD

#define SDC_SCK_PIN     (27)        ///< SDC serial clock (SCK) pin.
#define SDC_MOSI_PIN    (26)        ///< SDC serial data in (DI) pin.
#define SDC_MISO_PIN    (2)         ///< SDC serial data out (DO) pin.
#define SDC_CS_PIN      (32 + 15)   ///< SDC chip select (CS) pin.

/**
 * @brief  SDC block device definition
 * */
NRF_BLOCK_DEV_SDC_DEFINE(
        m_block_dev_sdc,
        NRF_BLOCK_DEV_SDC_CONFIG(
                SDC_SECTOR_SIZE,
                APP_SDCARD_CONFIG(SDC_MOSI_PIN, SDC_MISO_PIN, SDC_SCK_PIN, SDC_CS_PIN)
         ),
         NFR_BLOCK_DEV_INFO_CONFIG("Nordic", "SDC", "1.00")
);


/**
 * @brief Block devices list passed to @ref APP_USBD_MSC_GLOBAL_DEF
 * */
#define BLOCKDEV_LIST() (                                       \
        NRF_BLOCKDEV_BASE_ADDR(m_block_dev_ram, block_dev),     \
        NRF_BLOCKDEV_BASE_ADDR(m_block_dev_empty, block_dev),   \
        NRF_BLOCKDEV_BASE_ADDR(m_block_dev_qspi, block_dev),    \
        NRF_BLOCKDEV_BASE_ADDR(m_block_dev_sdc, block_dev)      \
)

#else
#define BLOCKDEV_LIST() (                                       \
        NRF_BLOCKDEV_BASE_ADDR(m_block_dev_ram, block_dev),     \
        NRF_BLOCKDEV_BASE_ADDR(m_block_dev_empty, block_dev),   \
        NRF_BLOCKDEV_BASE_ADDR(m_block_dev_qspi, block_dev)     \
)
#endif

/**
 * @brief Endpoint list passed to @ref APP_USBD_MSC_GLOBAL_DEF
 * */
#define ENDPOINT_LIST() APP_USBD_MSC_ENDPOINT_LIST(1, 1)

/**
 * @brief Mass storage class work buffer size
 * */
#define MSC_WORKBUFFER_SIZE (1024)

/*lint -save -e26 -e64 -e123 -e505 -e651*/
/**
 * @brief Mass storage class instance
 * */
APP_USBD_MSC_GLOBAL_DEF(m_app_msc,
                        0,
                        msc_user_ev_handler,
                        ENDPOINT_LIST(),
                        BLOCKDEV_LIST(),
                        MSC_WORKBUFFER_SIZE);

/*lint -restore*/


static void msc_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                app_usbd_msc_user_event_t     event)
{
    app_usbd_msc_t const * p_msc = app_usbd_msc_class_get(p_inst);
    UNUSED_VARIABLE(p_msc);
    switch (event)
    {
        case APP_USBD_MSC_USER_EVT_SUSPEND:
            bsp_board_led_off(LED_USB_RESUME);
            break;
        case APP_USBD_MSC_USER_EVT_RESUME:
            bsp_board_led_on(LED_USB_RESUME);
            break;
        case APP_USBD_MSC_USER_EVT_START:
            bsp_board_led_invert(LED_USB_START);
            break;
        case APP_USBD_MSC_USER_EVT_STOP:
            bsp_board_leds_off();
            break;
        default:
            break;
    }
}

/**
 * @brief  USB connection status
 * */
static bool m_usb_connected = false;

#if USE_FATFS_QSPI

static FATFS m_filesystem;

static bool fatfs_init(void)
{
    FRESULT ff_result;
    DSTATUS disk_state = STA_NOINIT;

    memset(&m_filesystem, 0, sizeof(FATFS));

    // Initialize FATFS disk I/O interface by providing the block device.
    static diskio_blkdev_t drives[] =
    {
            DISKIO_BLOCKDEV_CONFIG(NRF_BLOCKDEV_BASE_ADDR(m_block_dev_qspi, block_dev), NULL)
    };

    diskio_blockdev_register(drives, ARRAY_SIZE(drives));

    NRF_LOG_INFO("Initializing disk 0 (QSPI)...\r\n");
    disk_state = disk_initialize(0);
    if (disk_state)
    {
        NRF_LOG_ERROR("Disk initialization failed.\r\n");
        return false;
    }

    NRF_LOG_INFO("Mounting volume...\r\n");
    ff_result = f_mount(&m_filesystem, "", 1);
    if (ff_result != FR_OK)
    {
        NRF_LOG_ERROR("Mount failed: %u\r\n", ff_result);
        return false;
    }

    return true;
}

static void fatfs_mkfs(void)
{
    FRESULT ff_result;

    if (m_usb_connected)
    {
        NRF_LOG_ERROR("Unable to operate on filesystem while USB is connected\r\n");
        return;
    }

    NRF_LOG_INFO("\r\nCreating filesystem...\r\n");
    static uint8_t buf[512];
    ff_result = f_mkfs("", FM_FAT, 1024, buf, sizeof(buf));
    if (ff_result != FR_OK)
    {
        NRF_LOG_ERROR("Mkfs failed.\r\n");
        return;
    }

    NRF_LOG_INFO("Mounting volume...\r\n");
    ff_result = f_mount(&m_filesystem, "", 1);
    if (ff_result != FR_OK)
    {
        NRF_LOG_ERROR("Mount failed.\r\n");
        return;
    }

    NRF_LOG_INFO("Done\r\n");
}

static void fatfs_ls(void)
{
    DIR dir;
    FRESULT ff_result;
    FILINFO fno;

    if (m_usb_connected)
    {
        NRF_LOG_ERROR("Unable to operate on filesystem while USB is connected\r\n");
        return;
    }

    NRF_LOG_INFO("\r\nListing directory: /\r\n");
    ff_result = f_opendir(&dir, "/");
    if (ff_result != FR_OK)
    {
        NRF_LOG_ERROR("Directory listing failed: %u\r\n", ff_result);
        return;
    }

    uint32_t entries_count = 0;
    do
    {
        ff_result = f_readdir(&dir, &fno);
        if (ff_result != FR_OK)
        {
            NRF_LOG_ERROR("Directory read failed: %u\r\n", ff_result);
            return;
        }

        if (fno.fname[0])
        {
            if (fno.fattrib & AM_DIR)
            {
                NRF_LOG_RAW_INFO("   <DIR>   %s\r\n",(uint32_t)fno.fname);
            }
            else
            {
                NRF_LOG_RAW_INFO("%9lu  %s\r\n", fno.fsize, (uint32_t)fno.fname);
            }
        }

        ++entries_count;
        NRF_LOG_FLUSH();
    } while (fno.fname[0]);


    NRF_LOG_INFO("Entries count: %u\r\n", entries_count);
}

static void fatfs_file_create(void)
{
    FRESULT ff_result;
    FIL file;
    char filename[16];

    if (m_usb_connected)
    {
        NRF_LOG_ERROR("Unable to operate on filesystem while USB is connected\r\n");
        return;
    }

    (void)snprintf(filename, sizeof(filename), "%08x.txt", rand());

    NRF_LOG_INFO("Creating random file: %s ...", (uint32_t)filename);
    NRF_LOG_FLUSH();

    ff_result = f_open(&file, filename, FA_CREATE_ALWAYS | FA_WRITE);
    if (ff_result != FR_OK)
    {
        NRF_LOG_ERROR("\r\nUnable to open or create file: %u\r\n", ff_result);
        NRF_LOG_FLUSH();
        return;
    }

    ff_result = f_close(&file);
    if (ff_result != FR_OK)
    {
        NRF_LOG_ERROR("\r\nUnable to close file: %u\r\n", ff_result);
        NRF_LOG_FLUSH();
        return;
    }
    NRF_LOG_RAW_INFO("done\r\n");
}

static void fatfs_uninit(void)
{
    NRF_LOG_INFO("Un-initializing disk 0 (QSPI)...\r\n");
    UNUSED_RETURN_VALUE(disk_uninitialize(0));
}
#else //USE_FATFS_QSPI
#define fatfs_init()        false
#define fatfs_mkfs()        do { } while (0)
#define fatfs_ls()          do { } while (0)
#define fatfs_file_create() do { } while (0)
#define fatfs_uninit()      do { } while (0)
#endif


static void power_usb_event_handler(nrf_drv_power_usb_evt_t event)
{
    switch(event)
    {
        case NRF_DRV_POWER_USB_EVT_DETECTED:
            NRF_LOG_INFO("USB power detected\r\n");

            if (!nrf_drv_usbd_is_enabled())
            {
                app_usbd_enable();
            }
            break;
        case NRF_DRV_POWER_USB_EVT_REMOVED:
            NRF_LOG_INFO("USB power removed\r\n");
            m_usb_connected = false;
            break;
        case NRF_DRV_POWER_USB_EVT_READY:
            NRF_LOG_INFO("USB ready\r\n");
            m_usb_connected = true;
            break;
        default:
            ASSERT(false);
    }
}


static void usb_start(void)
{
    if (USBD_POWER_DETECTION)
    {
        static const nrf_drv_power_usbevt_config_t config =
        {
            .handler = power_usb_event_handler
        };

        nrf_drv_power_usbevt_init(&config);
    }
    else
    {
        NRF_LOG_INFO("No USB power detection enabled\r\nStarting USB now\r\n");

        app_usbd_enable();
        app_usbd_start();
        m_usb_connected = true;
    }
}

static bool usb_connection_handle(bool last_usb_conn_status)
{
    if (last_usb_conn_status != m_usb_connected)
    {
        last_usb_conn_status = m_usb_connected;
        if (m_usb_connected)
        {
            fatfs_uninit();
            app_usbd_start();
        }
        else
        {
            app_usbd_disable();
            UNUSED_RETURN_VALUE(fatfs_init());
        }
    }

    return last_usb_conn_status;
}

int main(void)
{
    ret_code_t ret;

    ret = nrf_drv_clock_init();
    APP_ERROR_CHECK(ret);
    ret = nrf_drv_power_init(NULL);
    APP_ERROR_CHECK(ret);

    ret = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(ret);
    NRF_LOG_INFO("Hello USB!\r\n");

    /* Fill whole RAM block device buffer */
    for (size_t i = 0; i < sizeof(m_block_dev_ram_buff); ++i)
    {
        m_block_dev_ram_buff[i] = i;
    }

    /* Configure LEDs and buttons */
    bsp_board_leds_init();
    bsp_board_buttons_init();
    
    if (fatfs_init())
    {
        fatfs_ls();
        fatfs_file_create();
    }
    fatfs_uninit();

    ret = app_usbd_init();
    APP_ERROR_CHECK(ret);

    app_usbd_class_inst_t const * class_inst_msc = app_usbd_msc_class_inst_get(&m_app_msc);
    ret = app_usbd_class_append(class_inst_msc);
    APP_ERROR_CHECK(ret);

    bool last_usb_conn_status = false;
    usb_start();

    while (true)
    {
        last_usb_conn_status = usb_connection_handle(last_usb_conn_status);

        /*For simplicity don't use BSP button events.*/
        if (bsp_board_button_state_get(BTN_RANDOM_FILE))
        {
            fatfs_file_create();
            while (bsp_board_button_state_get(BTN_RANDOM_FILE))
            {
                //Wait for release
            }
        }

        if (bsp_board_button_state_get(BTN_LIST_DIR))
        {
            fatfs_ls();
            while (bsp_board_button_state_get(BTN_LIST_DIR))
            {
                //Wait for release
            }
        }

        if (bsp_board_button_state_get(BTN_MKFS))
        {
            fatfs_mkfs();
            while (bsp_board_button_state_get(BTN_MKFS))
            {
                //Wait for release
            }
        }

        UNUSED_RETURN_VALUE(NRF_LOG_PROCESS());
    }
}

/** @} */
