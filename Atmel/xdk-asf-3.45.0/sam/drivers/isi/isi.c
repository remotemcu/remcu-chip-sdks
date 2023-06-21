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

#include "isi.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \brief Workaround for ISI CFG2 register read.
 * \note The ISI_CFG2[31:27] can be written correctly, because the input writing
 * data are assigned directly to the internal control bits as specified,
 * the mismatch only happens in reading operation.
 * [31:28] are shift right 1 bit, so [31:27] can be read from [30:27].
 */
static inline uint32_t _isi_get_CFG2_workaround(void)
{
	uint32_t wrongfield;
	wrongfield = ISI->ISI_CFG2 >> (ISI_CFG2_YCC_SWAP_Pos - 1);
	return (ISI->ISI_CFG2 & 0x07FFFFFF) | (wrongfield << ISI_CFG2_YCC_SWAP_Pos);
}

/**
 * \brief Initialize the ISI module.
 *
 * \param p_isi  Pointer to a ISI instance.
 * \param isi_cfg   Configuration for the ISI
 */
void isi_init(Isi *p_isi, struct isi_config_t *isi_cfg)
{
	uint32_t reg = 0;

	if(isi_cfg->hpol) {
		reg |= ISI_CFG1_HSYNC_POL;
	}
	if(isi_cfg->vpol) {
		reg |= ISI_CFG1_VSYNC_POL;
	}
	if(isi_cfg->pck_plo) {
		reg |= ISI_CFG1_PIXCLK_POL;
	}
	if(isi_cfg->emb_sync) {
		reg |= ISI_CFG1_EMB_SYNC;
	}
	if(isi_cfg->crc_sync) {
		reg |= ISI_CFG1_CRC_SYNC;
	}
	reg |= ISI_CFG1_THMASK(isi_cfg->thmask) | ISI_CFG1_SLD(isi_cfg->sld)
		| ISI_CFG1_SFD(isi_cfg->sfd);
	p_isi->ISI_CFG1 = reg;

	reg = _isi_get_CFG2_workaround();
	switch(isi_cfg->image_fmt) {
		case ISI_INPUT_YUV:
			reg &= ~ISI_CFG2_COL_SPACE;
			break;
		case ISI_INPUT_RGB565:
			reg |= ISI_CFG2_COL_SPACE;
			reg |= ISI_CFG2_RGB_MODE;
			break;
		case ISI_INPUT_RGB888:
			reg |= ISI_CFG2_COL_SPACE;
			reg &= ~ISI_CFG2_RGB_MODE;
			break;
		case ISI_INPUT_GS_12BIT:
			reg |= ISI_CFG2_GRAYSCALE;
			break;
		case ISI_INPUT_GS_8BIT:
			reg &= ~ISI_CFG2_GRAYSCALE;
			reg &= ~ISI_CFG2_RGB_SWAP;
			reg &= ~ISI_CFG2_COL_SPACE;
			reg &= ~ISI_CFG2_YCC_SWAP_Msk;
			break;
		default:
			break;
	}
	reg |= ISI_CFG2_IM_VSIZE(isi_cfg->image_vsize - 1)
		| ISI_CFG2_IM_HSIZE(isi_cfg->image_hsize - 1);
	p_isi->ISI_CFG2 = reg;
}

/**
 * \brief Configue RGB swap mode and RGB pattern when RGB_MODE is set to 1.
 *
 * \param p_isi  Pointer to a ISI instance.
 * \param patten  RGB pattern
 * \param swap  0: D7-R7, 1: D0-R7
 */
void isi_rgb_configue(Isi *p_isi, uint8_t patten, uint8_t swap)
{
	p_isi->ISI_CFG2 = _isi_get_CFG2_workaround() | ISI_CFG2_RGB_CFG(patten);

	if(swap) {
		p_isi->ISI_CFG2 = _isi_get_CFG2_workaround() | (ISI_CFG2_RGB_SWAP);
	} else {
		p_isi->ISI_CFG2 = _isi_get_CFG2_workaround() & (~ISI_CFG2_RGB_SWAP);
	}
}

/**
 * \brief Defines YCrCb swap format.
 *
 * \param p_isi  Pointer to a ISI instance.
 * \param swap YUV Swap format
 */
void isi_yuv_configue(Isi *p_isi, uint8_t swap)
{
	p_isi->ISI_CFG2 = _isi_get_CFG2_workaround() & (~ISI_CFG2_YCC_SWAP_Msk);
	p_isi->ISI_CFG2 = _isi_get_CFG2_workaround() | ISI_CFG2_YCC_SWAP(swap);
}

/**
 * \brief Input image is assumed to be grayscale-coded.
 *
 * \param p_isi  Pointer to a ISI instance.
 * \param mode  0: 2 pixels per word, 1: 1 pixel per word.
 */
void isi_gs_configue(Isi *p_isi, uint8_t mode)
{
	if(mode) {
		p_isi->ISI_CFG2 = _isi_get_CFG2_workaround() | (ISI_CFG2_GS_MODE);
	} else {
		p_isi->ISI_CFG2 = _isi_get_CFG2_workaround() & (~ISI_CFG2_GS_MODE);
	}
}

/**
 * \brief Set image and preview size, then calculate scaler factor automatically.
 *
 * \param p_isi  Pointer to a ISI instance.
 * \param image_hsize  Horizontal image input size  (range 1~2048).
 * \param image_vsize  Vertical image input size  (range 1~2048).
 * \param preview_hsize  Horizontal Preview size  (640 max only in RGB mode).
 * \param preview_vsize  Vertical Preview size  (480 max only in RGB mode).
 */
void isi_size_configure(Isi *p_isi, uint32_t image_hsize, uint32_t image_vsize,
						uint32_t preview_hsize, uint32_t preview_vsize)
{
	p_isi->ISI_CFG2 = _isi_get_CFG2_workaround() & (~ISI_CFG2_IM_VSIZE_Msk);
	p_isi->ISI_CFG2 = _isi_get_CFG2_workaround() & (~ISI_CFG2_IM_HSIZE_Msk);
	p_isi->ISI_CFG2 = _isi_get_CFG2_workaround() | ISI_CFG2_IM_VSIZE(image_vsize - 1) | ISI_CFG2_IM_HSIZE(image_hsize - 1);

	p_isi->ISI_PSIZE &= (~ISI_PSIZE_PREV_VSIZE_Msk);
	p_isi->ISI_PSIZE &= (~ISI_PSIZE_PREV_HSIZE_Msk);
	p_isi->ISI_PSIZE |= ISI_PSIZE_PREV_VSIZE(preview_hsize - 1) | ISI_PSIZE_PREV_HSIZE(preview_vsize - 1);

	uint32_t hRatio;
	hRatio = 1600 * image_hsize / preview_hsize;
	p_isi->ISI_PDECF = (hRatio / 100);
}

/**
 * \brief Configure DMA for preview path.
 *
 * \param p_isi  Pointer to a ISI instance.
 * \param frate frame rate capture
 * \param base_buf_desc  Preview descriptor address.
 * \param dma_ctrl  DMA preview control.
 * \param frame_buf_start_addr  DMA preview base address.
 */
void isi_set_dma_preview_path(Isi *p_isi, uint8_t frate,
		uint32_t base_buf_desc, uint32_t dma_ctrl, uint32_t frame_buf_start_addr)
{
	if(frate > 7) {
		frate = 7;
	}
	p_isi->ISI_CFG1 |= ISI_CFG1_FRATE(frate);

	p_isi->ISI_DMA_P_DSCR = base_buf_desc;
	p_isi->ISI_DMA_P_CTRL = dma_ctrl;
	p_isi->ISI_DMA_P_ADDR = frame_buf_start_addr;

}

/**
 * \brief Configure DMA for codec path.
 *
 * \param p_isi  Pointer to a ISI instance.
 * \param full_mode  Full mode is allowed.
 * \param discr  Disable codec request.
 * \param base_buf_desc  Codec descriptor address.
 * \param dma_ctrl  DMA codec Control.
 * \param frame_buf_start_addr  DMA codec base address.
 */
void isi_set_dma_codec_path(Isi *p_isi, uint8_t full_mode, uint8_t discr,
		uint32_t base_buf_desc, uint32_t dma_ctrl, uint32_t frame_buf_start_addr)
{
	if(full_mode) {
		p_isi->ISI_CFG1 |= ISI_CFG1_FULL;
	} else {
		p_isi->ISI_CFG1 &= ~ISI_CFG1_FULL;
	}
	if(discr) {
		p_isi->ISI_CFG1 |= ISI_CFG1_DISCR;
	} else {
		p_isi->ISI_CFG1 &= ~ISI_CFG1_DISCR;
	}

	p_isi->ISI_DMA_C_DSCR = base_buf_desc;
	p_isi->ISI_DMA_C_CTRL = dma_ctrl;
	p_isi->ISI_DMA_C_ADDR = frame_buf_start_addr;
}

/**
 * \brief ISI set matrix for YUV to RGB color space for preview path.
 *
 * \param p_isi  Pointer to a ISI instance.
 * \param yuv2rgb structure of YUV to RBG parameters.
 */
void isi_set_matrix_yuv2rgb(Isi *p_isi, isi_Y2R* yuv2rgb)
{
	p_isi->ISI_Y2R_SET0 = ISI_Y2R_SET0_C0(yuv2rgb->C0)
					 | ISI_Y2R_SET0_C1(yuv2rgb->C1)
					 | ISI_Y2R_SET0_C2(yuv2rgb->C2)
					 | ISI_Y2R_SET0_C3(yuv2rgb->C3);

	p_isi->ISI_Y2R_SET1 = ISI_Y2R_SET1_C4(yuv2rgb->C4)
					 | ((yuv2rgb->Yoff == 1)? ISI_Y2R_SET1_Yoff: 0)
					 | ((yuv2rgb->Croff == 1)? ISI_Y2R_SET1_Croff: 0)
					 | ((yuv2rgb->Cboff == 1)? ISI_Y2R_SET1_Cboff: 0);
}

/**
 * \brief ISI set matrix for RGB to YUV color space for codec path.
 *
 * \param p_isi  Pointer to a ISI instance.
 * \param rgb2yuv structure of RGB to YUV parameters.
 */
void isi_set_matrix_rgb2yuv(Isi *p_isi, isi_R2Y* rgb2yuv)
{
	p_isi->ISI_R2Y_SET0 = ISI_R2Y_SET0_C0(rgb2yuv->C0)
					  | ISI_R2Y_SET0_C1(rgb2yuv->C1)
					  | ISI_R2Y_SET0_C2(rgb2yuv->C2)
					  | ((rgb2yuv->Roff == 1)? ISI_R2Y_SET0_Roff: 0);

	p_isi->ISI_R2Y_SET1 = ISI_R2Y_SET1_C3(rgb2yuv->C3)
					  | ISI_R2Y_SET1_C4(rgb2yuv->C4)
					  | ISI_R2Y_SET1_C5(rgb2yuv->C5)
					  | ((rgb2yuv->Goff == 1)? ISI_R2Y_SET1_Goff: 0);

	p_isi->ISI_R2Y_SET2 = ISI_R2Y_SET2_C6(rgb2yuv->C6)
					  | ISI_R2Y_SET2_C7(rgb2yuv->C7)
					  | ISI_R2Y_SET2_C8(rgb2yuv->C8)
					  | ((rgb2yuv->Boff == 1)? ISI_R2Y_SET2_Boff: 0);
}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
