/**
 * \file
 *
 * \brief OHCI registers and data structures definition header file.
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

#ifndef _OHCI_COMPONENT_
#define _OHCI_COMPONENT_

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief OHCI hardware registers */
typedef struct {
	__I uint32_t HcRevision;   /**< \brief (Udp Offset: 0x000) Frame Number Register */
	__IO uint32_t HcControl;  /**< \brief (Udp Offset: 0x004) Global State Register */
	__IO uint32_t HcCommandStatus;     /**< \brief (Udp Offset: 0x008) Function Address Register */
	__IO uint32_t HcInterruptStatus;   /**< \brief (Udp Offset: 0x00C) Interrupt Status Register */
	__IO uint32_t HcInterruptEnable;       /**< \brief (Udp Offset: 0x010) Interrupt Enable Register */
	__IO uint32_t HcInterruptDisable;       /**< \brief (Udp Offset: 0x014) Interrupt Disable Register */
	__IO uint32_t HcHCCA;       /**< \brief (Udp Offset: 0x018) Interrupt Mask Register */
	__IO uint32_t HcPeriodCurrentED;       /**< \brief (Udp Offset: 0x01C) Interrupt Status Register */
	__IO uint32_t HcControlHeadED;       /**< \brief (Udp Offset: 0x020) Interrupt Clear Register */
	__IO uint32_t HcControlCurrentED;
	__IO uint32_t HcBulkHeadED;    /**< \brief (Udp Offset: 0x028) Reset Endpoint Register */
	__IO uint32_t HcBulkCurrentED;
	__I uint32_t HcDoneHead;    /**< \brief (Udp Offset: 0x030) Endpoint Control and Status Register */
	__IO uint32_t HcFmInterval;
	__I uint32_t HcFmRemaining;    /**< \brief (Udp Offset: 0x050) Endpoint FIFO Data Register */
	__I uint32_t HcFmNumber;
	__IO uint32_t HcPeriodicStart;      /**< \brief (Udp Offset: 0x074) Transceiver Control Register */
	__IO uint32_t HcLSThreshold;
	__IO uint32_t HcRhDescriptorA;  /**< \brief (Udp Offset: 0x0F8) USB FS Device Features Register */
	__IO uint32_t HcRhDescriptorB;   /**< \brief (Udp Offset: 0x0FC) Version Register */
	__IO uint32_t HcRhStatus;  /**< \brief (Udp Offset: 0x0F8) USB FS Device Features Register */
	__IO uint32_t HcRhPortStatus;   /**< \brief (Udp Offset: 0x0FC) Version Register */
} Ohci;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/** \brief  HcControl register fields */
#define HC_CONTROL_PLE                  (0x1u << 2)
#define HC_CONTROL_IE                   (0x1u << 3)
#define HC_CONTROL_CLE                  (0x1u << 4)
#define HC_CONTROL_BLE                  (0x1u << 5)
#define HC_CONTROL_HCFS                 (0x3u << 6)
#define HC_CONTROL_HCFS_USBRESET        (0x0u << 6)
#define HC_CONTROL_HCFS_USBRESUME       (0x1u << 6)
#define HC_CONTROL_HCFS_USBOPERATIONAL  (0x2u << 6)
#define HC_CONTROL_HCFS_USBSUSPEND      (0x3u << 6)
#define HC_CONTROL_IR	                (0x1u << 8)	/* interrupt routing */
#define HC_CONTROL_RWC	                (0x1u << 9)	/* remote wakeup connected */
#define HC_CONTROL_RWE	                (0x1u << 10)	/* remote wakeup enable */

/** \brief  HcCommandStatus register fields */
#define HC_COMMANDSTATUS_HCR            (0x1u << 0)
#define HC_COMMANDSTATUS_CLF            (0x1u << 1)
#define HC_COMMANDSTATUS_BLF            (0x1u << 2)

/*
 * \brief  HcInterruptEnable/Disable/Status registers fields
 *
 * masks used with interrupt registers:
 * HcInterruptStatus (intrstatus)
 * HcInterruptEnable (intrenable)
 * HcInterruptDisable (intrdisable)
 */
#define HC_INTERRUPT_SO                 (0x1u << 0)  /* scheduling overrun */
#define HC_INTERRUPT_WDH                (0x1u << 1)  /* writeback of done_head */
#define HC_INTERRUPT_SF                 (0x1u << 2)  /* start frame */
#define HC_INTERRUPT_RD                 (0x1u << 3)  /* resume detect */
#define HC_INTERRUPT_UE                 (0x1u << 4)  /* unrecoverable error */
#define HC_INTERRUPT_FNO                (0x1u << 5)  /* frame number overflow */
#define HC_INTERRUPT_RHSC               (0x1u << 6)  /* root hub status change */
#define HC_INTERRUPT_OC                 (0x1u << 30) /* ownership change */ 
#define HC_INTERRUPT_MIE                (0x1u << 31) /* master interrupt enable */

/** \brief  HcFmInterval register fields */
#define HC_FMINTERVAL_FI                0x00003FFF

/** \brief  HcRhDescriptorA register fields */
#define HC_RHDESCRIPTORA_NDP            0x000000FF

//! \brief  HcRhPortStatus register fields
#define HC_RHPORTSTATUS_CCS             (0x1u << 0)
#define HC_RHPORTSTATUS_PRS             (0x1u << 4)
#define HC_RHPORTSTATUS_LSDA            (0x1u << 9)


/* OHCI ROOT HUB REGISTER MASKS */

/* roothub.portstatus [i] bits */
#define RH_PS_CCS            0x00000001		/* current connect status */
#define RH_PS_PES            0x00000002		/* port enable status*/
#define RH_PS_PSS            0x00000004		/* port suspend status */
#define RH_PS_POCI           0x00000008		/* port over current indicator */
#define RH_PS_PRS            0x00000010		/* port reset status */
#define RH_PS_PPS            0x00000100		/* port power status */
#define RH_PS_LSDA           0x00000200		/* low speed device attached */
#define RH_PS_CSC            0x00010000		/* connect status change */
#define RH_PS_PESC           0x00020000		/* port enable status change */
#define RH_PS_PSSC           0x00040000		/* port suspend status change */
#define RH_PS_OCIC           0x00080000		/* over current indicator change */
#define RH_PS_PRSC           0x00100000		/* port reset status change */

/* roothub.status bits */
#define RH_HS_LPS	     0x00000001		/* local power status */
#define RH_HS_OCI	     0x00000002		/* over current indicator */
#define RH_HS_DRWE	     0x00008000		/* device remote wakeup enable */
#define RH_HS_LPSC	     0x00010000		/* local power status change */
#define RH_HS_OCIC	     0x00020000		/* over current indicator change */
#define RH_HS_CRWE	     0x80000000		/* clear remote wakeup enable */

/* roothub.b masks */
#define RH_B_DR		0x0000ffff		/* device removable flags */
#define RH_B_PPCM	0xffff0000		/* port power control mask */

/* roothub.a masks */
#define	RH_A_NDP	(0xff << 0)		/* number of downstream ports */
#define	RH_A_PSM	(0x1u << 8)		/* power switching mode */
#define	RH_A_NPS	(0x1u << 9)		/* no power switching */
#define	RH_A_DT		(0x1u << 10)		/* device type (mbz) */
#define	RH_A_OCPM	(0x1u << 11)		/* over current protection mode */
#define	RH_A_NOCP	(0x1u << 12)		/* no over current protection */
#define	RH_A_POTPGT	(0xff << 24)		/* power on to power good time */

/*
 * OHCI Endpoint Descriptor (ED) ... holds TD queue
 * See OHCI spec, section 4.2
 */
typedef union {
	struct {
		uint32_t  bFunctionAddress:7;    //!< Device address on the bus
		uint32_t  bEndpointNumber:4;     //!< Endpoint number
		uint32_t  bDirection:2;          //!< Endpoint direction
		uint32_t  bSpeed:1;              //!< Full- or low-speed
		uint32_t  bSkip:1;               //!< Process TDs on this endpoint ?
		uint32_t  bFormat:1;             //!< TD format
		uint32_t  bMaximumPacketSize:11; //!< Maximum packet size
		uint32_t  bReserved:5;
	} ed_info_s;
	uint32_t ul_ed_info;
} ed_info_t;

struct ohci_ed {
	ed_info_t       ed_info;
    void           *p_td_tail;                //!< Pointer to the tail TD
    void           *p_td_head;                //!< Pointer to the head TD
    struct ohci_ed  *p_next_ed;               //!< Pointer to next ED
};

/** \brief  Transfer descriptor directions */
#define TD_DIRECTION_SETUP              0
#define TD_DIRECTION_OUT                1
#define TD_DIRECTION_IN                 2

/** \brief  Transfer descriptor data toggle values */
#define TD_TOGGLE_AUTO                  0
#define TD_TOGGLE_DATA0                 2
#define TD_TOGGLE_DATA1                 3

/**
 * \brief  Condition code field values
 * Completion Codes, General TD or isochronous data packet processing
 * completed with.
 */
/* no detected errors */
#define TD_CONDITIONCODE_NOERROR            0x0 // 0000
/* Last data packet from endpoint contained a CRC error. */
#define TD_CONDITIONCODE_CRC                0x1 // 0001
/* Last data packet from endpoint contained a bit stuffing violation. */
#define TD_CONDITIONCODE_BITSTUFFING        0x2 // 0010
/**
 * Last packet from endpoint had data toggle PID that didnot match
 * the expected value.
 */
#define TD_CONDITIONCODE_DATATOGGLEMISMATCH 0x3 // 0011
/* TD was moved to the Done Queue because the endpoint returned a STALL PID. */
#define TD_CONDITIONCODE_STALL              0x4 // 0100
/* Device did not respond to token (IN) or did not provide a handshake (OUT). */
#define TD_CONDITIONCODE_NOTRESPONDING      0x5 // 0101
/* Check bits on PID from endpoint failed on data PID (IN) or handshake (OUT). */
#define TD_CONDITIONCODE_PIDCHECKFAILURE    0x6 // 0110
// Receive PID was not valid when encountered or PID value is not defined. */
#define TD_CONDITIONCODE_UNEXPECTEDPID      0x7 // 0111
/**
 * The amount of data returned by the endpoint exceeded either the size of 
 * the maximum data packet allowed from the endpoint (found in 
 * MaximumPacketSize field of ED) or the remaining buffer size.
 */
#define TD_CONDITIONCODE_DATAOVERRUN        0x8 // 1000
/**
 * The endpoint returned less than MaximumPacketSize and that amount was not
 * sufficient to fill the specified buffer.
 */
#define TD_CONDITIONCODE_DATAUNDERRUN       0x9 // 1001
// Reserved                                 0xA // 1010
// Reserved                                 0xB // 1011
/**
 * During an IN, HC received data from endpoint faster than it could be written
 * to system memory.
 */
#define TD_CONDITIONCODE_BUFFEROVERRUN      0xC // 1100
/**
 * During an OUT, HC could not retrieve data from system memory fast enough
 * to keep up with data USB data rate.
 */
#define TD_CONDITIONCODE_BUFFERUNDERRUN     0xD // 1101
/**
 * This code is set by software before the TD is placed on a list to be
 * processed by the HC.
 */
#define TD_CONDITIONCODE_NOTACCESSED        0xE // 111x

/*
 * OHCI Transfer Descriptor (TD) ... one per transfer segment
 * See OHCI spec, sections 4.3.1 (general = control/bulk/interrupt)
 * and 4.3.2 (iso)
 */
struct ohci_td_general {
	struct {
	  uint32_t  bReserved1:18;
	  uint32_t  bBufferRounding:1;      //!< Last data packet size policy
	  uint32_t  bDirectionPID:2;        //!< Packet PID
	  uint32_t  bDelayInterrupt:3;      //!< Interrupt delay count
	  uint32_t  bDataToggle:2;          //!< Data toggle value
	  uint32_t  bErrorCount:2;          //!< Transmission error count
	  uint32_t  bConditionCode:4;       //!< Status of last transaction
	} td_info;
	void           *pCurrentBufferPointer; //!< Pointer to the data buffer
	struct ohci_td_general *p_next_td;               //!< Pointer to next TD
	void           *pBufferEnd;            //!< Address of data buffer last byte
};

struct ohci_td_iso {
	struct {
	  uint32_t  bStartingFrame:16;      //!< Start frame number
	  uint32_t  bReserved1:5;
	  uint32_t  bDelayInterrupt:3;      //!< Interrupt delay count
	  uint32_t  FrameCount:3;          //!< Number of data packets (frames)
	  uint32_t  bReserved2:1;
	  uint32_t  bConditionCode:4;       //!< Status of last transaction
	} td_info;
	void           *pBufferPage0;       //!< Pointer to the data buffer
	struct ohci_td_iso *p_next_td;               //!< Pointer to next TD
	void           *pBufferEnd;            //!< Address of data buffer last byte
	uint16_t    offset_psw[8];            //!< Offset, packet status word
};

/*
 * The HCCA (Host Controller Communications Area) is a 256 byte
 * structure defined section 4.4.1 of the OHCI spec. The HC is
 * told the base address of it.  It must be 256-byte aligned.
 */
struct ohci_hcca {
    uint32_t InterruptTable[32];
    uint16_t FrameNumber;
    uint16_t Pad1;
    void         *pDoneHead;
    uint32_t Reserved[29];
	uint32_t what;		/* spec only identifies 252 bytes :) */
};

#define	FI			0x2edf		/* 12000 bits per frame (-1) */
#define	FSMP(fi)	(0x7fff & ((6 * ((fi) - 210)) / 7))
#define	FIT			(0x1u << 31)
#define LSTHRESH	0x628		/* lowspeed bit threshold */

#endif /* _OHCI_COMPONENT_ */
