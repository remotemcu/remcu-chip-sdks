/**
 * \file
 *
 * \brief Configurations for the WILC3000 Serial Bridge Application
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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


 #include "bt_uart.h"
 #include "uart_stream.h"
 #include "driver/include/ble_firmware_3000.h"

 // Address to load firmware
 #define IRAM_START 0x80000000

 // Larger blocks (e.g. 8192) cause hang
 #define FIRMWARE_CHUNK_SIZE 4096

 static int     download_count;
 static uint8_t event_buffer[15];
 static uint8_t command_buffer[12];
 static const uint8_t * fw_data;
 static uint32_t        fw_size;
 static uint32_t        fw_offset;

 // HCI commands used for firmware upload
 static const uint8_t hci_reset_command[] = { 0x01, 0x03, 0x0c, 0x00 };
 static const uint8_t hci_read_local_version_information_command[] = { 0x01, 0x01, 0x10, 0x00 };
 static const uint8_t hci_vendor_specific_reset_command[] = { 0x01, 0x55, 0xfc, 0x00 };

 void little_endian_store_32(uint8_t *buffer, uint16_t pos, uint32_t value){
	 buffer[pos++] = (uint8_t)(value);
	 buffer[pos++] = (uint8_t)(value >> 8);
	 buffer[pos++] = (uint8_t)(value >> 16);
	 buffer[pos++] = (uint8_t)(value >> 24);
 }

 uint8_t bt_uart_firmware_download(void)
 {
	 uint8_t s8Ret = 0;
	 uint16_t bytes_to_write = 0;

	fw_size = sizeof(firmware_ble);
	fw_data = &firmware_ble;
	
	do 
	{
		bytes_to_write = min((fw_size - fw_offset), FIRMWARE_CHUNK_SIZE);
		// setup write command
		command_buffer[0] = 1;
		command_buffer[1] = 0x52;
		command_buffer[2] = 0xfc;
		command_buffer[3] = 8; // NOTE: this is in violation of the Bluetooth Specification, but documented in the Atmel-NNNNN-ATWIL_Linux_Porting_Guide
		little_endian_store_32(command_buffer, 4, IRAM_START + fw_offset);
		little_endian_store_32(command_buffer, 8, bytes_to_write);
		bt_usart_stream_write_buffer(&command_buffer[0], 12);		
		bt_usart_stream_write_buffer(&fw_data[fw_offset], bytes_to_write);	
		
		fw_offset += bytes_to_write;   
		if (fw_offset >= fw_size){
			return;
		}
	} while (1);

	 return s8Ret;
 }

 void bt_serial_bridge()
 {
	bt_usart_stream_write_buffer(&hci_reset_command[0],sizeof(hci_reset_command));	
	bt_usart_stream_write_buffer(&hci_read_local_version_information_command[0], sizeof(hci_read_local_version_information_command));	
	bt_uart_firmware_download();
	bt_usart_stream_write_buffer(&hci_vendor_specific_reset_command[0], sizeof(hci_vendor_specific_reset_command));
 }
