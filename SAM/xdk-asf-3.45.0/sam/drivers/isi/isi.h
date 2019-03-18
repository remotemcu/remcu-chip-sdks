/**
 * \file
 *
 * \brief SAM Image Sensor Interface (ISI) driver.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef ISI_H
#define ISI_H

/**
 * \defgroup asfdoc_sam_drivers_isi_group SAMV71/V70/E70/S70 Image Sensor Interface Driver
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based SAM Image Sensor Interface (ISI) connects a CMOS-type
 * image sensor to the processor and provides image capture in various formats.
 *
 * Devices from the following series can use this module:
 * - Atmel | SMART SAMV71
 * - Atmel | SMART SAMV70
 * - Atmel | SMART SAMS70
 * - Atmel | SMART SAME70
 *
 * @{
 */

#include  <compiler.h>
#include  <status_codes.h>

/** @cond */
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/** @endcond */

/** Enum for the possible image format for the ISI module. */
enum isi_input_image_format {
	/** ISI input YCrCb */
	ISI_INPUT_YUV =  0,
	/** ISI input RGB 8:8:8 */
	ISI_INPUT_RGB565 =  1,
	/** ISI input RGB 5:6:5 */
	ISI_INPUT_RGB888 =  2,
	/** ISI input 12-bit grayscale */
	ISI_INPUT_GS_12BIT =  3,
	/** ISI input 8-bit grayscale */
	ISI_INPUT_GS_8BIT =  4,
};

/** ISI Matrix Color Space Conversion YCrCb to RGB */
typedef struct
{
	/** Color Space Conversion Matrix Coefficient C0 */
	uint8_t C0;
	/** Color Space Conversion Matrix Coefficient C1 */
	uint8_t C1;
	/** Color Space Conversion Matrix Coefficient C2 */
	uint8_t C2;
	/** Color Space Conversion Matrix Coefficient C3 */
	uint8_t C3;
   /** Color Space Conversion Red Chrominance Default Offset */
	uint8_t Croff;
	/** Color Space Conversion Blue Chrominance Default Offset */
	uint8_t Cboff;
	/** Color Space Conversion Luminance Default Offset */
	uint8_t Yoff;
	 /** Color Space Conversion Matrix Coefficient C4 */
	uint16_t C4;
} isi_Y2R;

/** ISI Matrix Color Space Conversion RGB to YCrCb */
typedef struct
{
	/** Color Space Conversion Matrix Coefficient C0 */
	uint8_t C0;
	/** Color Space Conversion Matrix Coefficient C1 */
	uint8_t C1;
	/** Color Space Conversion Matrix Coefficient C2 */
	uint8_t C2;
	/** Color Space Conversion Red Component Offset */
	uint8_t Roff;
	/** Color Space Conversion Matrix Coefficient C3*/
	uint8_t C3;
	/** Color Space Conversion Matrix Coefficient C4 */
	uint8_t C4;
	/** Color Space Conversion Matrix Coefficient C5 */
	uint8_t C5;
	/** Color Space Conversion Green Component Offset */
	uint8_t Goff;
	/** Color Space Conversion Matrix Coefficient C6*/
	uint8_t C6;
	/** Color Space Conversion Matrix Coefficient C7 */
	uint8_t C7;
	/** Color Space Conversion Matrix Coefficient C8 */
	uint8_t C8;
	/** Color Space Conversion Blue Component Offset */
	uint8_t Boff;
} isi_R2Y;

/** ISI configuration structure. */
struct isi_config_t {
	/** Horizontal Synchronization Polarity */
	uint8_t hpol;
	/** Vertical Synchronization Polarity */
	uint8_t vpol;
	/** Pixel Clock Polarity */
	uint8_t pck_plo;
	/** Embedded Synchronization */
	uint8_t emb_sync;
	/** Embedded Synchronization Correction */
	uint8_t crc_sync;
	/** Threshold Mask */
	uint8_t thmask;
	/** Start of Line Delay */
	uint8_t sld;
	/** Start of Frame Delay */
	uint8_t sfd;

	/** Input image format */
	enum isi_input_image_format image_fmt;
	/** Input image horizontal size */
	uint32_t image_hsize;
	/** Input image vertical size */
	uint32_t image_vsize;
};

/** Frame buffer descriptors */
struct isi_frame_buffer_descriptors
{
	/** Address of the Current FrameBuffer */
	uint32_t current;
	/** Address of the Control */
	uint32_t control;
	/** Address of the Next FrameBuffer */
	uint32_t next;
};

/**
 * \brief Enable ISI
 *
 * \param p_isi  Pointer to a ISI instance.
 */
static inline void isi_enable(Isi *p_isi)
{
	p_isi->ISI_CR |= ISI_CR_ISI_EN;
	while((p_isi->ISI_SR & ISI_CR_ISI_EN) != ISI_CR_ISI_EN);
}

/**
 * \brief Disable ISI
 *
 * \param p_isi  Pointer to a ISI instance.
 */
static inline void isi_disable(Isi *p_isi)
{
	p_isi->ISI_CR |= ISI_CR_ISI_DIS;
	/* Software must poll DIS_DONE field in the ISI_STATUS register to verify that the command
	has successfully completed.*/
	while((p_isi->ISI_SR & ISI_SR_DIS_DONE) != ISI_SR_DIS_DONE);
}

/**
 * \brief Reset ISI
 *
 * \param p_isi  Pointer to a ISI instance.
 */
static inline void isi_reset(Isi *p_isi)
{
	/* Resets the image sensor interface.
	   Finish capturing the current frame and then shut down the module. */
	p_isi->ISI_CR = ISI_CR_ISI_SRST | ISI_CR_ISI_DIS;
	/* wait Software reset has completed successfully. */
	while((p_isi->ISI_SR & ISI_SR_SRST) != ISI_SR_SRST);
}

/**
 * \brief Enable the codec datapath and capture a full resolution frame.
 *
 * \param p_isi  Pointer to a ISI instance.
 */
static inline void isi_capture(Isi *p_isi)
{
	/* A new request cannot be taken into account while CDC_PND bit is active */
	while((p_isi->ISI_SR & ISI_SR_CDC_PND) == ISI_SR_CDC_PND);
	p_isi->ISI_CR = ISI_CR_ISI_CDC;
}

void isi_init(Isi *p_isi, struct isi_config_t *isi_cfg);

void isi_rgb_configue(Isi *p_isi, uint8_t patten, uint8_t swap);

void isi_yuv_configue(Isi *p_isi, uint8_t swap);

void isi_gs_configue(Isi *p_isi, uint8_t mode);

void isi_size_configure(Isi *p_isi, uint32_t image_hsize, uint32_t image_vsize, 
						uint32_t preview_hsize, uint32_t preview_vsize);

/**
 * \brief Enable ISI interrupt
 *
 * \param p_isi  Pointer to a ISI instance.
 * \param  flag of interrupt to enable
 */
static inline void isi_enable_interrupt(Isi *p_isi, uint32_t flag)
{
	p_isi->ISI_IER = flag;
}

/**
 * \brief Disable ISI interrupt
 *
 * \param p_isi  Pointer to a ISI instance.
 * \param  flag of interrupt to disable
 */
static inline void isi_disable_interrupt(Isi *p_isi, uint32_t flag)
{
	p_isi->ISI_IDR = flag;
}

/**
 * \brief Return ISI status register
 *
 * \param p_isi  Pointer to a ISI instance.
 * \return Status of ISI register
 */
static inline uint32_t isi_get_status(Isi *p_isi)
{
	return(p_isi->ISI_SR);
}

/**
 * \brief Enable ISI Dma channel
 *
 * \param p_isi  Pointer to a ISI instance.
 * \param  channel to be enabled
 */
static inline void isi_dma_channel_enable(Isi *p_isi, uint32_t channel)
{
	p_isi->ISI_DMA_CHER |= channel;
}

/**
 * \brief Disable ISI Dma channel
 *
 * \param p_isi  Pointer to a ISI instance.
 * \param  channel to be disabled
 */
static inline void isi_dma_channel_disable(Isi *p_isi, uint32_t channel)
{
	p_isi->ISI_DMA_CHDR |= channel;
}

void isi_set_dma_preview_path(Isi *p_isi, uint8_t frate,
		uint32_t base_buf_desc, uint32_t dma_ctrl, uint32_t frame_buf_start_addr);

void isi_set_dma_codec_path(Isi *p_isi, uint8_t full_mode, uint8_t discr, 
		uint32_t base_buf_desc, uint32_t dma_ctrl, uint32_t frame_buf_start_addr);

/**
 * \brief Enable or disable write protection of ADC registers.
 *
 * \param p_isi  Pointer to a ISI instance.
 * \param is_enable 1 to enable, 0 to disable.
 */
static inline void isi_set_writeprotect(Isi *p_isi,
		const bool is_enable)
{
	if (is_enable) {
		p_isi->ISI_WPMR = ISI_WPMR_WPEN | ISI_WPMR_WPKEY_PASSWD;
	} else {
		p_isi->ISI_WPMR = ISI_WPMR_WPKEY_PASSWD;
	}
}

/**
 * \brief Indicate write protect status.
 *
 * \param p_isi  Pointer to a ISI instance.
 *
 * \return 0 if no write protect violation occurred, or 16-bit write protect
 * violation source.
 */
static inline uint32_t isi_get_writeprotect_status(Isi *p_isi)
{
	uint32_t reg_value;

	reg_value = p_isi->ISI_WPSR;
	if (reg_value & ISI_WPSR_WPVS) {
		return (reg_value & ISI_WPSR_WPVSRC_Msk) >> ISI_WPSR_WPVSRC_Pos;
	} else {
		return 0;
	}
}

void isi_set_matrix_yuv2rgb(Isi *p_isi, isi_Y2R* yuv2rgb);
void isi_set_matrix_rgb2yuv(Isi *p_isi, isi_R2Y* rgb2yuv);

/** @cond */
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/** @endcond */

#endif //#ifndef ISI_H
