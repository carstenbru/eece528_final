module sub_v(type,ax,ay,az,bx,by,bz,cx,cy,cz);
input type;
input [31:0]ax,ay,az,bx,by,bz;
output [31:0]cx,cy,cz;


	assign cx[31:0]=(type?{ax[15:0],16'd0}:ax[31:0])-bx[31:0];
	assign cy[31:0]=(type?{ay[15:0],16'd0}:ay[31:0])-by[31:0];
	assign cz[31:0]=(type?{az[15:0],16'd0}:az[31:0])-bz[31:0];
	
endmodule

module dot_v(ax,ay,az,bx,by,bz,cdot);
input [31:0]ax,ay,az,bx,by,bz;
output [63:0]cdot;


mult_add mult_add_inst
(
	.dataa_0(ax[31:0]) ,	// input [31:0] dataa_0_sig
	.dataa_1(ay[31:0]) ,	// input [31:0] dataa_1_sig
	.dataa_2(az[31:0]) ,	// input [31:0] dataa_2_sig
	.datab_0(bx[31:0]) ,	// input [31:0] datab_0_sig
	.datab_1(by[31:0]) ,	// input [31:0] datab_1_sig
	.datab_2(bz[31:0]) ,	// input [31:0] datab_2_sig
	.result(cdot[63:0]) 	// output [65:0] result_sig
);


endmodule
