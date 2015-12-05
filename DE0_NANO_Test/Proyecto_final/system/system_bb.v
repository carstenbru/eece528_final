
module system (
	alt_vip_itc_0_clocked_video_vid_clk,
	alt_vip_itc_0_clocked_video_vid_data,
	alt_vip_itc_0_clocked_video_underflow,
	alt_vip_itc_0_clocked_video_vid_datavalid,
	alt_vip_itc_0_clocked_video_vid_v_sync,
	alt_vip_itc_0_clocked_video_vid_h_sync,
	alt_vip_itc_0_clocked_video_vid_f,
	alt_vip_itc_0_clocked_video_vid_h,
	alt_vip_itc_0_clocked_video_vid_v,
	analog1_x_export,
	analog1_y_export,
	analog2_x_export,
	analog2_y_export,
	boton_a_export,
	boton_b_export,
	boton_down_export,
	boton_l_export,
	boton_left_export,
	boton_r_export,
	boton_right_export,
	boton_up_export,
	boton_x_export,
	boton_y_export,
	clk_clk,
	epcs_dclk,
	epcs_sce,
	epcs_sdo,
	epcs_data0,
	pio_led_green_export,
	pio_sw_export,
	reset_reset_n,
	sdram_addr,
	sdram_ba,
	sdram_cas_n,
	sdram_cke,
	sdram_cs_n,
	sdram_dq,
	sdram_dqm,
	sdram_ras_n,
	sdram_we_n,
	touch_panel_busy_export,
	touch_panel_penirq_n_export,
	touch_panel_spi_MISO,
	touch_panel_spi_MOSI,
	touch_panel_spi_SCLK,
	touch_panel_spi_SS_n);	

	input		alt_vip_itc_0_clocked_video_vid_clk;
	output	[23:0]	alt_vip_itc_0_clocked_video_vid_data;
	output		alt_vip_itc_0_clocked_video_underflow;
	output		alt_vip_itc_0_clocked_video_vid_datavalid;
	output		alt_vip_itc_0_clocked_video_vid_v_sync;
	output		alt_vip_itc_0_clocked_video_vid_h_sync;
	output		alt_vip_itc_0_clocked_video_vid_f;
	output		alt_vip_itc_0_clocked_video_vid_h;
	output		alt_vip_itc_0_clocked_video_vid_v;
	input	[7:0]	analog1_x_export;
	input	[7:0]	analog1_y_export;
	input	[7:0]	analog2_x_export;
	input	[7:0]	analog2_y_export;
	input		boton_a_export;
	input		boton_b_export;
	input		boton_down_export;
	input		boton_l_export;
	input		boton_left_export;
	input		boton_r_export;
	input		boton_right_export;
	input		boton_up_export;
	input		boton_x_export;
	input		boton_y_export;
	input		clk_clk;
	output		epcs_dclk;
	output		epcs_sce;
	output		epcs_sdo;
	input		epcs_data0;
	output	[7:0]	pio_led_green_export;
	input	[3:0]	pio_sw_export;
	input		reset_reset_n;
	output	[12:0]	sdram_addr;
	output	[1:0]	sdram_ba;
	output		sdram_cas_n;
	output		sdram_cke;
	output		sdram_cs_n;
	inout	[15:0]	sdram_dq;
	output	[1:0]	sdram_dqm;
	output		sdram_ras_n;
	output		sdram_we_n;
	input		touch_panel_busy_export;
	input		touch_panel_penirq_n_export;
	input		touch_panel_spi_MISO;
	output		touch_panel_spi_MOSI;
	output		touch_panel_spi_SCLK;
	output		touch_panel_spi_SS_n;
endmodule
