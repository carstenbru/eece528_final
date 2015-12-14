module intersect_sphere(clk,
								start,
								finish,
								radius_sqr,
								centerx,
								centery,
								centerz,
								rayorig_x,
								rayorig_y,
								rayorig_z,
								raydir_x,
								raydir_y,
								raydir_z,
								t0,
								t1,
								result);
input clk,start;
output reg finish=1'b0;
input [31:0]radius_sqr;
input [31:0]centerx;
input [31:0]centery;
input [31:0]centerz;
input [31:0]rayorig_x;
input [31:0]rayorig_y;
input [31:0]rayorig_z;
input [31:0]raydir_x;
input [31:0]raydir_y;
input [31:0]raydir_z;
output [31:0]t0;
output [31:0]t1;
output reg result;


reg  [31:0]	tca;
reg  [47:0]	d2;
wire  [15:0]thc;
reg [1:0]counter=2'd1;
	
	
wire [31:0]l[2:0];
wire [63:0]r_dot;
wire [31:0]b_dot[2:0];
assign b_dot[0][31:0]=(counter[1:0]==2'd0)?raydir_x[31:0]:l[0][31:0];
assign b_dot[1][31:0]=(counter[1:0]==2'd0)?raydir_y[31:0]:l[1][31:0];
assign b_dot[2][31:0]=(counter[1:0]==2'd0)?raydir_z[31:0]:l[2][31:0];

wire [31:0]sqrt_result;

wire  [63:0]tca_square;
wire [47:0]radius_shift=radius_sqr[31:0]<<16;



multi_hw	multi_hw_inst (
	.dataa ( tca[31:0] ),
	.datab ( tca[31:0] ),
	.result ( tca_square[63:0] )
	);

	
sub_v sub_v1
(
	.type(1),
	.ax(centerx[31:0]) ,	// input [31:0] ax_sig
	.ay(centery[31:0]) ,	// input [31:0] ay_sig
	.az(centerz[31:0]) ,	// input [31:0] az_sig
	.bx(rayorig_x[31:0]) ,	// input [31:0] bx_sig
	.by(rayorig_y[31:0]) ,	// input [31:0] by_sig
	.bz(rayorig_z[31:0]) ,	// input [31:0] bz_sig
	.cx(l[0][31:0]) ,	// output [31:0] cx_sig
	.cy(l[1][31:0]) ,	// output [31:0] cy_sig
	.cz(l[2][31:0]) 	// output [31:0] cz_sig
);



dot_v dot(l[0][31:0],l[1][31:0],l[2][31:0],b_dot[0][31:0],b_dot[1][31:0],b_dot[2][31:0],r_dot[63:0]);

always@(posedge clk)
begin	
	tca[31:0]<=(counter[1:0]==2'd0)?r_dot[47:16]:tca[31:0];
	d2[47:0]<=(counter[1:0]==2'd1)?(r_dot[63:16] - tca_square[63:16]) :d2[31:0];
end

always@(posedge clk)
begin
	if(start)
	begin
		counter[31:0]<=2'd0;
	end
	else
	begin
		counter[1:0]<=counter[1:0];
		if(counter[1:0]<2'd1)
		begin
			counter[1:0]<=counter[1:0]+1'b1;
		end
	end
end


always@(posedge clk)
begin
	if(start)
	begin
		finish<=1'b0;
		result<=1'b0;
	end
	else
	begin
		finish<=finish;
		result<=result;
		if(counter[31:0]==2'd0)
		begin
			finish<=tca[31];
			result<=1'b0;
		end
		else if(counter[31:0]==2'd1)
		begin
			finish<=1'b1;
			result<=~(d2[47:0]>(radius_shift[47:0]));
		end
	end
end

sqrt	sqrt_inst (
	.radical ( radius_shift[47:0] - d2[47:0]),
	.q ( sqrt_result[31:0] ),
	.remainder (  )
	);
assign thc[15:0]=sqrt_result[31:16];

assign t0[31:0]=tca[31:0]-thc[15:0];
assign t1[31:0]=tca[31:0]+thc[15:0];
	

endmodule
