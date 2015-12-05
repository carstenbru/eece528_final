	component system is
		port (
			alt_vip_itc_0_clocked_video_vid_clk       : in    std_logic                     := 'X';             -- vid_clk
			alt_vip_itc_0_clocked_video_vid_data      : out   std_logic_vector(23 downto 0);                    -- vid_data
			alt_vip_itc_0_clocked_video_underflow     : out   std_logic;                                        -- underflow
			alt_vip_itc_0_clocked_video_vid_datavalid : out   std_logic;                                        -- vid_datavalid
			alt_vip_itc_0_clocked_video_vid_v_sync    : out   std_logic;                                        -- vid_v_sync
			alt_vip_itc_0_clocked_video_vid_h_sync    : out   std_logic;                                        -- vid_h_sync
			alt_vip_itc_0_clocked_video_vid_f         : out   std_logic;                                        -- vid_f
			alt_vip_itc_0_clocked_video_vid_h         : out   std_logic;                                        -- vid_h
			alt_vip_itc_0_clocked_video_vid_v         : out   std_logic;                                        -- vid_v
			analog1_x_export                          : in    std_logic_vector(7 downto 0)  := (others => 'X'); -- export
			analog1_y_export                          : in    std_logic_vector(7 downto 0)  := (others => 'X'); -- export
			analog2_x_export                          : in    std_logic_vector(7 downto 0)  := (others => 'X'); -- export
			analog2_y_export                          : in    std_logic_vector(7 downto 0)  := (others => 'X'); -- export
			boton_a_export                            : in    std_logic                     := 'X';             -- export
			boton_b_export                            : in    std_logic                     := 'X';             -- export
			boton_down_export                         : in    std_logic                     := 'X';             -- export
			boton_l_export                            : in    std_logic                     := 'X';             -- export
			boton_left_export                         : in    std_logic                     := 'X';             -- export
			boton_r_export                            : in    std_logic                     := 'X';             -- export
			boton_right_export                        : in    std_logic                     := 'X';             -- export
			boton_up_export                           : in    std_logic                     := 'X';             -- export
			boton_x_export                            : in    std_logic                     := 'X';             -- export
			boton_y_export                            : in    std_logic                     := 'X';             -- export
			clk_clk                                   : in    std_logic                     := 'X';             -- clk
			epcs_dclk                                 : out   std_logic;                                        -- dclk
			epcs_sce                                  : out   std_logic;                                        -- sce
			epcs_sdo                                  : out   std_logic;                                        -- sdo
			epcs_data0                                : in    std_logic                     := 'X';             -- data0
			pio_led_green_export                      : out   std_logic_vector(7 downto 0);                     -- export
			pio_sw_export                             : in    std_logic_vector(3 downto 0)  := (others => 'X'); -- export
			reset_reset_n                             : in    std_logic                     := 'X';             -- reset_n
			sdram_addr                                : out   std_logic_vector(12 downto 0);                    -- addr
			sdram_ba                                  : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_cas_n                               : out   std_logic;                                        -- cas_n
			sdram_cke                                 : out   std_logic;                                        -- cke
			sdram_cs_n                                : out   std_logic;                                        -- cs_n
			sdram_dq                                  : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			sdram_dqm                                 : out   std_logic_vector(1 downto 0);                     -- dqm
			sdram_ras_n                               : out   std_logic;                                        -- ras_n
			sdram_we_n                                : out   std_logic;                                        -- we_n
			touch_panel_busy_export                   : in    std_logic                     := 'X';             -- export
			touch_panel_penirq_n_export               : in    std_logic                     := 'X';             -- export
			touch_panel_spi_MISO                      : in    std_logic                     := 'X';             -- MISO
			touch_panel_spi_MOSI                      : out   std_logic;                                        -- MOSI
			touch_panel_spi_SCLK                      : out   std_logic;                                        -- SCLK
			touch_panel_spi_SS_n                      : out   std_logic                                         -- SS_n
		);
	end component system;

	u0 : component system
		port map (
			alt_vip_itc_0_clocked_video_vid_clk       => CONNECTED_TO_alt_vip_itc_0_clocked_video_vid_clk,       -- alt_vip_itc_0_clocked_video.vid_clk
			alt_vip_itc_0_clocked_video_vid_data      => CONNECTED_TO_alt_vip_itc_0_clocked_video_vid_data,      --                            .vid_data
			alt_vip_itc_0_clocked_video_underflow     => CONNECTED_TO_alt_vip_itc_0_clocked_video_underflow,     --                            .underflow
			alt_vip_itc_0_clocked_video_vid_datavalid => CONNECTED_TO_alt_vip_itc_0_clocked_video_vid_datavalid, --                            .vid_datavalid
			alt_vip_itc_0_clocked_video_vid_v_sync    => CONNECTED_TO_alt_vip_itc_0_clocked_video_vid_v_sync,    --                            .vid_v_sync
			alt_vip_itc_0_clocked_video_vid_h_sync    => CONNECTED_TO_alt_vip_itc_0_clocked_video_vid_h_sync,    --                            .vid_h_sync
			alt_vip_itc_0_clocked_video_vid_f         => CONNECTED_TO_alt_vip_itc_0_clocked_video_vid_f,         --                            .vid_f
			alt_vip_itc_0_clocked_video_vid_h         => CONNECTED_TO_alt_vip_itc_0_clocked_video_vid_h,         --                            .vid_h
			alt_vip_itc_0_clocked_video_vid_v         => CONNECTED_TO_alt_vip_itc_0_clocked_video_vid_v,         --                            .vid_v
			analog1_x_export                          => CONNECTED_TO_analog1_x_export,                          --                   analog1_x.export
			analog1_y_export                          => CONNECTED_TO_analog1_y_export,                          --                   analog1_y.export
			analog2_x_export                          => CONNECTED_TO_analog2_x_export,                          --                   analog2_x.export
			analog2_y_export                          => CONNECTED_TO_analog2_y_export,                          --                   analog2_y.export
			boton_a_export                            => CONNECTED_TO_boton_a_export,                            --                     boton_a.export
			boton_b_export                            => CONNECTED_TO_boton_b_export,                            --                     boton_b.export
			boton_down_export                         => CONNECTED_TO_boton_down_export,                         --                  boton_down.export
			boton_l_export                            => CONNECTED_TO_boton_l_export,                            --                     boton_l.export
			boton_left_export                         => CONNECTED_TO_boton_left_export,                         --                  boton_left.export
			boton_r_export                            => CONNECTED_TO_boton_r_export,                            --                     boton_r.export
			boton_right_export                        => CONNECTED_TO_boton_right_export,                        --                 boton_right.export
			boton_up_export                           => CONNECTED_TO_boton_up_export,                           --                    boton_up.export
			boton_x_export                            => CONNECTED_TO_boton_x_export,                            --                     boton_x.export
			boton_y_export                            => CONNECTED_TO_boton_y_export,                            --                     boton_y.export
			clk_clk                                   => CONNECTED_TO_clk_clk,                                   --                         clk.clk
			epcs_dclk                                 => CONNECTED_TO_epcs_dclk,                                 --                        epcs.dclk
			epcs_sce                                  => CONNECTED_TO_epcs_sce,                                  --                            .sce
			epcs_sdo                                  => CONNECTED_TO_epcs_sdo,                                  --                            .sdo
			epcs_data0                                => CONNECTED_TO_epcs_data0,                                --                            .data0
			pio_led_green_export                      => CONNECTED_TO_pio_led_green_export,                      --               pio_led_green.export
			pio_sw_export                             => CONNECTED_TO_pio_sw_export,                             --                      pio_sw.export
			reset_reset_n                             => CONNECTED_TO_reset_reset_n,                             --                       reset.reset_n
			sdram_addr                                => CONNECTED_TO_sdram_addr,                                --                       sdram.addr
			sdram_ba                                  => CONNECTED_TO_sdram_ba,                                  --                            .ba
			sdram_cas_n                               => CONNECTED_TO_sdram_cas_n,                               --                            .cas_n
			sdram_cke                                 => CONNECTED_TO_sdram_cke,                                 --                            .cke
			sdram_cs_n                                => CONNECTED_TO_sdram_cs_n,                                --                            .cs_n
			sdram_dq                                  => CONNECTED_TO_sdram_dq,                                  --                            .dq
			sdram_dqm                                 => CONNECTED_TO_sdram_dqm,                                 --                            .dqm
			sdram_ras_n                               => CONNECTED_TO_sdram_ras_n,                               --                            .ras_n
			sdram_we_n                                => CONNECTED_TO_sdram_we_n,                                --                            .we_n
			touch_panel_busy_export                   => CONNECTED_TO_touch_panel_busy_export,                   --            touch_panel_busy.export
			touch_panel_penirq_n_export               => CONNECTED_TO_touch_panel_penirq_n_export,               --        touch_panel_penirq_n.export
			touch_panel_spi_MISO                      => CONNECTED_TO_touch_panel_spi_MISO,                      --             touch_panel_spi.MISO
			touch_panel_spi_MOSI                      => CONNECTED_TO_touch_panel_spi_MOSI,                      --                            .MOSI
			touch_panel_spi_SCLK                      => CONNECTED_TO_touch_panel_spi_SCLK,                      --                            .SCLK
			touch_panel_spi_SS_n                      => CONNECTED_TO_touch_panel_spi_SS_n                       --                            .SS_n
		);

