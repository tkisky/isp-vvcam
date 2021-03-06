/****************************************************************************
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 VeriSilicon Holdings Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 *****************************************************************************
 *
 * The GPL License (GPL)
 *
 * Copyright (c) 2020 VeriSilicon Holdings Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program;
 *
 *****************************************************************************
 *
 * Note: This software is released under dual MIT and GPL licenses. A
 * recipient may use this file under the terms of either the MIT license or
 * GPL License. If you wish to use only one license not the other, you can
 * indicate your decision by deleting one of the above license notices in your
 * version of this file.
 *
 *****************************************************************************/
#ifndef _ISP_DEV_H_
#define _ISP_DEV_H_

#include "isp_version.h"
#include "vvdefs.h"

#define REG_ADDR(x)  ((uint32_t)(uintptr_t)&all_regs->x)

struct isp_reg_t {
	u32 offset;
	u32 val;
};

struct ic_window {
	u16 x;
	u16 y;
	u16 width;
	u16 height;
};

struct isp_context {
	u32 mode;
	u32 sample_edge;
	bool hSyncLowPolarity, vSyncLowPolarity;
	u32 bayer_pattern;
	u32 sub_sampling;
	u32 seq_ccir;
	u32 field_selection;
	u32 input_selection;
	u32 latency_fifo;
	struct ic_window acqWindow;  /**< acquisition window */
	struct ic_window ofWindow;   /**< output formatter window */
	struct ic_window isWindow;   /**< image stabilization output window */
	u32 bypass_mode;
	u8 demosaic_threshold;
};

struct isp_mi_data_path_context {
	bool enable;
	u32 out_mode;	   /**< output format */
	u32 in_mode;		/**< input format */
	u32 data_layout;	/**< layout of data */
	u32 data_alignMode;	/**< align mode of data */
	u32 in_width;
	u32 in_height;
	u32 out_width;
	u32 out_height;
	bool hscale;
	bool vscale;
	int pixelformat;
};

struct isp_mi_context {
	struct isp_mi_data_path_context path[3];
	u32 burst_len;
};

struct isp_bls_context {
	bool enabled;
	u32 mode;
	u16 a, b, c, d;
};

struct isp_tpg_userdefine_mode {
	u16 total, fp, sync, bp, act;
};

struct isp_tpg_context {
	bool enabled;
	u32 image_type;
	u32 bayer_pattern;
	u32 color_depth;
	u32 resolution;
	u16 pixleGap;
	u16 lineGap;
	u16 gapStandard;
	u32 randomSeed;
	struct isp_tpg_userdefine_mode user_mode_h, user_mode_v;
};

struct isp_mux_context {
	u32 mp_mux;				/**< main path muxer (vi_mp_mux) */
	u32 sp_mux;				/**< self path muxer (vi_dma_spmux) */
	u32 chan_mode;			/**< 1-mp, 2-sp, 4-sp2 */
	u32 ie_mux;				/**< image effects muxer (vi_dma_iemux) */
	u32 dma_read_switch;	   /**< dma read switch (vi_dma_switch) */
	u32 if_select;			 /**< interface selector (if_select) */
};

struct isp_awb_context {
	bool enable;
	u8 mode;
	u16 gain_r, gain_gr, gain_gb, gain_b;
	struct ic_window window;
	u16 refcb_max_b;
	u16 refcr_max_r;
	u16 max_y;
	u16 max_c_sum;
	u16 min_y_max_g;
	u16 min_c;
};

struct isp_awb_mean {
	u32 r, g, b;
	u32 no_white_count;
};

struct isp_cnr_context {
	bool enable;
	u32 line_width;
	u32 threshold_1;
	u32 threshold_2;
};

struct isp_cc_context {
	u32 lCoeff[9];
	bool update_curve;
	bool conv_range_y_full, conv_range_c_full;
};

struct isp_xtalk_context {
	u32 lCoeff[9];
	u32 r, g, b;
};

struct isp_gamma_out_context {
	bool enableWB, enableGamma;
	u32 mode;
	u32 curve[17];
};

#define CAEMRIC_GRAD_TBL_SIZE 8
#define CAMERIC_DATA_TBL_SIZE 289
#define CAMERIC_MAX_LSC_SECTORS 16

struct isp_lsc_context {
	u16 r[CAMERIC_DATA_TBL_SIZE];		 /**< correction values of R color part */
	u16 gr[CAMERIC_DATA_TBL_SIZE];		/**< correction values of G (red lines) color part */
	u16 gb[CAMERIC_DATA_TBL_SIZE];		/**< correction values of G (blue lines) color part  */
	u16 b[CAMERIC_DATA_TBL_SIZE];		 /**< correction values of B color part  */
	u16 x_grad[CAEMRIC_GRAD_TBL_SIZE];	/**< multiplication factors of x direction  */
	u16 y_grad[CAEMRIC_GRAD_TBL_SIZE];	/**< multiplication factors of y direction  */
	u16 x_size[CAEMRIC_GRAD_TBL_SIZE];	/**< sector sizes of x direction			*/
	u16 y_size[CAEMRIC_GRAD_TBL_SIZE];	/**< sector sizes of y direction			*/
};

struct isp_buffer_context {
	u32 type;
	u32 path;
	u32 addr_y, addr_cb, addr_cr;
	u32 size_y, size_cb, size_cr;
};


struct isp_dma_context {
	u32 type;
	u32 base;
	u32 width;
	u32 height;
	u32 burst_y;
	u32 burst_c;
};

struct isp_dpf_context {
	bool enable;
	u32 filter_type;
	u32 gain_usage;
	u32 strength_r;
	u32 strength_g;
	u32 strength_b;
	u8 weight_g[6];
	u8 weight_rb[6];
	u16 denoise_talbe[17];
	u32 x_scale;
	u32 nf_gain_r;
	u32 nf_gain_gr;
	u32 nf_gain_gb;
	u32 nf_gain_b;
	bool filter_r_off;
	bool filter_gr_off;
	bool filter_gb_off;
	bool filter_b_off;
};

struct isp_is_context {
	bool enable;
	bool update;
	struct ic_window window;
	u32 recenter;
	u32 max_dx, max_dy;
	u32 displace_x, displace_y;
};

struct isp_exp_context {
	bool enable;
	u32 mode;
	struct ic_window window;
};

struct isp_hist_context {
	bool enable;
	u32 mode;
	u32 step_size;
	struct ic_window window;
	u8 weight[25];
};

struct isp_dpcc_params {
	u32 line_thresh;
	u32 line_mad_fac;
	u32 pg_fac;
	u32 rnd_thresh;
	u32 rg_fac;
};

struct isp_dpcc_context {
	bool enable;
	u32 mode;
	u32 outmode;
	u32 set_use;
	u32 methods_set[3];
	struct isp_dpcc_params params[3];
	u32 ro_limits;
	u32 rnd_offs;
};

struct isp_flt_context {
	bool enable;
	u32 denoise;
	u32 sharpen;
};

struct isp_cac_context {
	bool enable;
	u32 hmode, vmode;
	u32 ab, ar, bb, br, cb, cr;
	u32 xns, xnf, yns, ynf;
	u32 hstart, vstart;
};

/* degamma */
struct isp_deg_context {
	bool enable;
	u8 segment[16];
	u16 r[17];
	u16 g[17];
	u16 b[17];
};

struct isp_ie_context {
	bool enable;
	u32 mode;
	u32 color_sel;
	u32 color_thresh;
	u32 sharpen_factor;
	u32 sharpen_thresh;
	int32_t m[9];
	u32 tint_cr;
	u32 tint_cb;
	bool full_range;
};

struct isp_afm_result {
	u32 sum_a, sum_b, sum_c;
	u32 lum_a, lum_b, lum_c;
};

struct isp_afm_context {
	bool enable;
	u32 thresh;
	struct ic_window window[3];
};

struct isp_vsm_result {
	u32 x, y;
};

struct isp_vsm_context {
	bool enable;
	struct ic_window window;
	u32 h_seg, v_seg;
};

#ifndef WDR3_BIN
#define WDR3_BIN 14
#endif
struct isp_wdr3_context {
	bool enable;
	bool update_bin;
	u32 strength;
	u32 max_gain;
	u32 global_strength;
	u32 histogram[WDR3_BIN];
	u32 shift[WDR3_BIN];
	u32 invert_linear[WDR3_BIN];
	u32 invert_curve[WDR3_BIN];
	u32 gamma_pre[WDR3_BIN];
	u32 gamma_up[WDR3_BIN];
	u32 gamma_down[WDR3_BIN];
	u32 entropy[WDR3_BIN];
	u32 distance_weight[WDR3_BIN];
	u32 difference_weight[WDR3_BIN];
};

struct isp_hdr_context {
	bool enable;
	/* hdr bls */
	u16 width;
	u16 height;
	u8 l_bit_dep, s_bit_dep, vs_bit_dep, ls_bit_dep;
	u8 weight0, weight1, weight2;
	u16 start_linear, norm_factor_mul_linear;
	u16 start_nonlinear, norm_factor_mul_nonlinear;
	u16 dummy_hblank, out_hblank;
	u16 out_vblank;
	u16 long_exp, short_exp, very_short_exp;
	u32 bls[4];
	u32 reg;
	/* hdr awb */
	u32 r, gr, gb, b;
	/* hdr exp */
	u32 compress_lut[15];
	/* long short, very short */
	u32 ls0, ls1, vs0, vs1;
	u32 ext_bit;
	u32 valid_thresh;
	u32 offset_val;
	u32 sat_thresh;
	u32 combine_weight;
};

struct isp_simp_context {
	bool enable;
	u32 x, y;
	u32 r, g, b;
	u32 transparency_mode;
	u32 ref_image;
};

/* COMPAND */
struct isp_comp_context {
	bool enable;
	bool bls;
	bool compress;
	bool expand;
	bool update_tbl;
	/* BLS */
	int a, b, c, d;
	u32 compress_tbl[64];
	u32 expand_tbl[64];
};

struct isp_cproc_context {
	bool enable;
	u32 contrast;
	u32 brightness;
	u32 saturation;
	u32 hue;
	bool y_out_full;
	bool c_out_full;
	bool y_in_full;
};

struct elawb_ellipse_info {
	u32 x, y;		/* ellipse center */
	u32 a1, a2, a3, a4;	/* ellipse axis */
	u32 r_max_sqr;
};

struct isp_elawb_context {
	bool enable;
	u32 id;			/* ellipse id,  1-8,  0 means update all. */
	struct elawb_ellipse_info info[8];
	struct ic_window window;
	u32 r, gr, gb, b;	/* gain */
};

struct isp_gcmono_data {
	u8 basePara[1024];
	u32 px[64];
	u32 dataX[63];
	u32 dataY[64];
};

struct isp_gcmono_context {
	u32 enable;
	u32 mode;
};

struct isp_irq_data {
	uint32_t addr;
	uint32_t val;
	uint32_t nop[14];
};

struct isp_ic_dev {
	void __iomem *base;
	void __iomem *reset;
	struct isp_context ctx;
	struct isp_bls_context bls;
	struct isp_tpg_context tpg;
	struct isp_mux_context mux;
	struct isp_awb_context awb;
	struct isp_lsc_context lsc;
	struct isp_gamma_out_context gamma_out;
	struct isp_xtalk_context xtalk;
	struct isp_cc_context cc;
	struct isp_cnr_context cnr;
	struct isp_is_context is;
	struct isp_is_context rawis;
	struct isp_mi_context mi;
	struct isp_dpf_context dpf;
	struct isp_exp_context exp;
	struct isp_hist_context hist;
	struct isp_dpcc_context dpcc;
	struct isp_flt_context flt;
	struct isp_cac_context cac;
	struct isp_deg_context deg;
	struct isp_ie_context ie;
	struct isp_vsm_context vsm;
	struct isp_afm_context afm;
	struct isp_wdr3_context wdr3;
	struct isp_hdr_context hdr;
	struct isp_comp_context comp;
	struct isp_simp_context simp;
	struct isp_cproc_context cproc;
	struct isp_elawb_context elawb;
	struct isp_gcmono_context gcmono;
};

void isp_write_reg(struct isp_ic_dev *dev, u32 offset, u32 val);
u32 isp_read_reg(struct isp_ic_dev *dev, u32 offset);

#endif /* _ISP_DEV_H_ */
