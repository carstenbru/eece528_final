module sub_v(ax,ay,bz,bx,by,bz,cx,cy,cz);
input [31:0]ax,ay,bz,bx,by,bz;
output [31:0]cx,cy,cz;


	assign cx[31:0]={ax[15:0],16'd0}-bx[31:0];
	assign cy[31:0]={ay[15:0],16'd0}-[31:0];
	assign cz[31:0]={az[15:0],16'd0}-rayorig_z[31:0];
	
endmodule

