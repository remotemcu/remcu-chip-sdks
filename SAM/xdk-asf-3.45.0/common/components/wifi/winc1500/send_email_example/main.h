/**
 * \file
 *
 * \brief MAIN configuration.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/** Wi-Fi Settings */
#define MAIN_WLAN_SSID                  "DEMO_AP" /**< Destination SSID */
#define MAIN_WLAN_AUTH                  M2M_WIFI_SEC_WPA_PSK /**< Security manner */
#define MAIN_WLAN_PSK                   "12345678" /**< Password for Destination SSID */

/** Using IP address. */
#define IPV4_BYTE(val, index)           ((val >> (index * 8)) & 0xFF)

/** All SMTP defines */
#define MAIN_SMTP_BUF_LEN               1024
#define MAIN_GMAIL_HOST_NAME            "smtp.gmail.com"
#define MAIN_GMAIL_HOST_PORT            465
#define MAIN_SENDER_RFC                 "<sender@gmail.com>" /* Set Sender Email Address */
#define MAIN_RECIPIENT_RFC              "<recipient@gmail.com>"  /* Set Recipient Email Address */
#define MAIN_EMAIL_SUBJECT              "Hello from WINC1500!"
#define MAIN_TO_ADDRESS                 "recipient@gmail.com" /* Set To Email Address */
#define MAIN_FROM_ADDRESS               "sender@gmail.com" /* Set From Email Address */
#define MAIN_FROM_PASSWORD              "12345678"              /* Set Sender Email Password */
#define MAIN_EMAIL_MSG                  "This mail is sent from Send Email Example."
#define MAIN_WAITING_TIME               30000
#define MAIN_RETRY_COUNT                3

typedef enum {
	SocketInit = 0,
	SocketConnect,
	SocketWaiting,
	SocketComplete,
	SocketError
} eSocketStatus;

typedef enum {
	SMTP_INACTIVE = 0,
	SMTP_INIT,
	SMTP_HELO,
	SMTP_AUTH,
	SMTP_AUTH_USERNAME,
	SMTP_AUTH_PASSWORD,
	SMTP_FROM,
	SMTP_RCPT,
	SMTP_DATA,
	SMTP_MESSAGE_SUBJECT,
	SMTP_MESSAGE_TO,
	SMTP_MESSAGE_FROM,
	SMTP_MESSAGE_CRLF,
	SMTP_MESSAGE_BODY,
	SMTP_MESSAGE_DATAEND,
	SMTP_QUIT,
	SMTP_ERROR
} eSMTPStatus;

/* Initialize error handling flags for smtp state machine */
typedef enum {
	MAIN_EMAIL_ERROR_FAILED = -1,
	MAIN_EMAIL_ERROR_NONE = 0,
	MAIN_EMAIL_ERROR_INIT,
	MAIN_EMAIL_ERROR_HELO,
	MAIN_EMAIL_ERROR_AUTH,
	MAIN_EMAIL_ERROR_AUTH_USERNAME,
	MAIN_EMAIL_ERROR_AUTH_PASSWORD,
	MAIN_EMAIL_ERROR_FROM,
	MAIN_EMAIL_ERROR_RCPT,
	MAIN_EMAIL_ERROR_DATA,
	MAIN_EMAIL_ERROR_MESSAGE,
	MAIN_EMAIL_ERROR_QUIT
} eMainEmailError;

/** Return Codes */
const char cSmtpCodeReady[] = {'2', '2', '0', '\0'};
const char cSmtpCodeOkReply[] = {'2', '5', '0', '\0'};
const char cSmtpCodeIntermedReply[] = {'3', '5', '4', '\0'};
const char cSmtpCodeAuthReply[] = {'3', '3', '4', '\0'};
const char cSmtpCodeAuthSuccess[] = {'2', '3', '5', '\0'};

/** Send Codes */
const char cSmtpHelo[] = {'H', 'E', 'L', 'O', '\0'};
const char cSmtpMailFrom[] = {'M', 'A', 'I', 'L', ' ', 'F', 'R', 'O', 'M', ':', ' ', '\0'};
const char cSmtpRcpt[] = {'R', 'C', 'P', 'T', ' ', 'T', 'O', ':', ' ', '\0'};
const char cSmtpData[] = "DATA";
const char cSmtpCrlf[] = "\r\n";
const char cSmtpSubject[] = "Subject: ";
const char cSmtpTo[] = "To: ";
const char cSmtpFrom[] = "From: ";
const char cSmtpDataEnd[] = {'\r', '\n', '.', '\r', '\n', '\0'};
const char cSmtpQuit[] = {'Q', 'U', 'I', 'T', '\r', '\n', '\0'};

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H_INCLUDED */
