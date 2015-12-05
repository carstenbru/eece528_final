// (C) 2001-2013 Altera Corporation. All rights reserved.
// Your use of Altera Corporation's design tools, logic functions and other 
// software and tools, and its AMPP partner logic functions, and any output 
// files any of the foregoing (including device programming or simulation 
// files), and any associated documentation or information are expressly subject 
// to the terms and conditions of the Altera Program License Subscription 
// Agreement, Altera MegaCore Function License Agreement, or other applicable 
// license agreement, including, without limitation, that your use is for the 
// sole purpose of programming logic devices manufactured by Altera and sold by 
// Altera or its authorized distributors.  Please refer to the applicable 
// agreement for further details.


// $Id: //acds/rel/13.1/ip/merlin/altera_merlin_multiplexer/altera_merlin_multiplexer.sv.terp#1 $
// $Revision: #1 $
// $Date: 2013/08/11 $
// $Author: swbranch $

// ------------------------------------------
// Merlin Multiplexer
// ------------------------------------------

`timescale 1 ns / 1 ns


// ------------------------------------------
// Generation parameters:
//   output_name:         system_mm_interconnect_0_cmd_xbar_mux_003
//   NUM_INPUTS:          1
//   ARBITRATION_SHARES:  1
//   ARBITRATION_SCHEME   "round-robin"
//   PIPELINE_ARB:        1
//   PKT_TRANS_LOCK:      72 (arbitration locking enabled)
//   ST_DATA_W:           117
//   ST_CHANNEL_W:        28
// ------------------------------------------

module system_mm_interconnect_0_cmd_xbar_mux_003
(
    // ----------------------
    // Sinks
    // ----------------------
    input                       sink0_valid,
    input [117-1   : 0]  sink0_data,
    input [28-1: 0]  sink0_channel,
    input                       sink0_startofpacket,
    input                       sink0_endofpacket,
    output                      sink0_ready,


    // ----------------------
    // Source
    // ----------------------
    output                      src_valid,
    output [117-1    : 0] src_data,
    output [28-1 : 0] src_channel,
    output                      src_startofpacket,
    output                      src_endofpacket,
    input                       src_ready,

    // ----------------------
    // Clock & Reset
    // ----------------------
    input clk,
    input reset
);
    localparam PAYLOAD_W        = 117 + 28 + 2;
    localparam NUM_INPUTS       = 1;
    localparam SHARE_COUNTER_W  = 1;
    localparam PIPELINE_ARB     = 1;
    localparam ST_DATA_W        = 117;
    localparam ST_CHANNEL_W     = 28;
    localparam PKT_TRANS_LOCK   = 72;

	assign	src_valid			=  sink0_valid;
	assign	src_data			=  sink0_data;
	assign	src_channel			=  sink0_channel;
	assign	src_startofpacket	=  sink0_startofpacket;
	assign	src_endofpacket		=  sink0_endofpacket;
	assign	sink0_ready			=  src_ready;
endmodule


