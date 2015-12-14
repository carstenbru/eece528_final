// megafunction wizard: %ALTSQRT%VBB%
// GENERATION: STANDARD
// VERSION: WM1.0
// MODULE: ALTSQRT 

// ============================================================
// File Name: sqrt.v
// Megafunction Name(s):
// 			ALTSQRT
//
// Simulation Library Files(s):
// 			altera_mf
// ============================================================
// ************************************************************
// THIS IS A WIZARD-GENERATED FILE. DO NOT EDIT THIS FILE!
//
// 15.0.0 Build 145 04/22/2015 Patches 0.01we SJ Web Edition
// ************************************************************

//Copyright (C) 1991-2015 Altera Corporation. All rights reserved.
//Your use of Altera Corporation's design tools, logic functions 
//and other software and tools, and its AMPP partner logic 
//functions, and any output files from any of the foregoing 
//(including device programming or simulation files), and any 
//associated documentation or information are expressly subject 
//to the terms and conditions of the Altera Program License 
//Subscription Agreement, the Altera Quartus II License Agreement,
//the Altera MegaCore Function License Agreement, or other 
//applicable license agreement, including, without limitation, 
//that your use is for the sole purpose of programming logic 
//devices manufactured by Altera and sold by Altera or its 
//authorized distributors.  Please refer to the applicable 
//agreement for further details.

module sqrt (
	radical,
	q,
	remainder);

	input	[63:0]  radical;
	output	[31:0]  q;
	output	[32:0]  remainder;

endmodule

// ============================================================
// CNX file retrieval info
// ============================================================
// Retrieval info: PRIVATE: INTENDED_DEVICE_FAMILY STRING "MAX 10"
// Retrieval info: PRIVATE: SYNTH_WRAPPER_GEN_POSTFIX STRING "0"
// Retrieval info: LIBRARY: altera_mf altera_mf.altera_mf_components.all
// Retrieval info: CONSTANT: PIPELINE NUMERIC "0"
// Retrieval info: CONSTANT: Q_PORT_WIDTH NUMERIC "32"
// Retrieval info: CONSTANT: R_PORT_WIDTH NUMERIC "33"
// Retrieval info: CONSTANT: WIDTH NUMERIC "64"
// Retrieval info: USED_PORT: q 0 0 32 0 OUTPUT NODEFVAL "q[31..0]"
// Retrieval info: USED_PORT: radical 0 0 64 0 INPUT NODEFVAL "radical[63..0]"
// Retrieval info: USED_PORT: remainder 0 0 33 0 OUTPUT NODEFVAL "remainder[32..0]"
// Retrieval info: CONNECT: @radical 0 0 64 0 radical 0 0 64 0
// Retrieval info: CONNECT: q 0 0 32 0 @q 0 0 32 0
// Retrieval info: CONNECT: remainder 0 0 33 0 @remainder 0 0 33 0
// Retrieval info: GEN_FILE: TYPE_NORMAL sqrt.v TRUE
// Retrieval info: GEN_FILE: TYPE_NORMAL sqrt.inc FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL sqrt.cmp FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL sqrt.bsf FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL sqrt_inst.v TRUE
// Retrieval info: GEN_FILE: TYPE_NORMAL sqrt_bb.v TRUE
// Retrieval info: LIB_FILE: altera_mf
