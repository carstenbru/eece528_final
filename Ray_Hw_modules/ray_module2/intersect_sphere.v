module intersect_sphere(clk,
								start,
								calc_t0,
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
								//t1,
								//result
								);
input clk,start;
input calc_t0;
output reg finish;
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
output reg [31:0]t0;
//output reg [31:0]t1;
//output reg result;

parameter MAX_CYCLE_COUNT = 5;

reg  [31:0]	tca;
wire  [47:0]d2;
reg  [47:0]thc_sqr;
wire  [31:0]thc;
reg [2:0] state;
	
wire start_sync;
wire [31:0]l[2:0];
wire [63:0]r_dot;
wire [31:0]b_dot[2:0];
assign b_dot[0][31:0]=(state==3'd0)?raydir_x[31:0]:l[0][31:0];
assign b_dot[1][31:0]=(state==3'd0)?raydir_y[31:0]:l[1][31:0];
assign b_dot[2][31:0]=(state==3'd0)?raydir_z[31:0]:l[2][31:0];

wire [23:0]sqrt_result;

wire  [63:0]tca_square;
wire i_test;

/*
async_trap_and_reset async_trap_and_reset_inst
(
	.async_sig(start) ,	// input  async_sig_sig
	.outclk(clk) ,	// input  outclk_sig
	.out_sync_sig(start_sync) ,	// output  out_sync_sig_sig
	.auto_reset(1'b1) ,	// input  auto_reset_sig
	.reset(1'b1) 	// input  reset_sig
);*/
assign start_sync = start;

assign i_test = (d2[47:0] > {radius_sqr[31:0],16'b0});


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


assign d2[47:0] = r_dot[63:16] - tca_square[63:16];

always@(posedge clk)
begin	
  if (state == 3'd0) begin
    tca[31:0] <= r_dot[47:16];
  end
end


always@(posedge clk)
begin
	if(start_sync)
	begin
		finish <= 1'b0;
		t0 <= 1'b0;
		state <= 2'd0;
	end
	else
	begin
	  if (finish == 1'b0) begin
		if(state==3'd0)
		begin
		   state <= 3'd1;
			finish <= r_dot[63];
			t0 <= 32'd0;		
	   end else if(state==3'd1) begin //TODO input to say if t0 is required or not
		   if (calc_t0 == 1'b1) begin		
			  finish <= i_test;
			  t0 <= 32'd0;
			end else begin
			  finish <= 1'b1;
			  t0 <= ~i_test;
			end
			state <= 3'd2;
			thc_sqr[47:0] <= {radius_sqr[31:0],16'b0} - d2[47:0];
		end else if(state == MAX_CYCLE_COUNT) begin
		  finish <= 1'b1;
		  t0[31:0] <= tca[31:0]-thc[31:0];
        //t1[31:0] <= tca[31:0]+thc[31:0];
		end else begin
		  state <= state + 1;
		end
	 end	
	end
end

sqrt	sqrt_inst (
   .clk(clk),
	.radical ( thc_sqr[47:0] ),
	.q ( sqrt_result[23:0] )
	//.remainder (  )
	);
defparam sqrt_inst.ALTSQRT_component.pipeline = MAX_CYCLE_COUNT - 2;
	
assign thc[31:0]={sqrt_result[23:0], 8'b0};
	

endmodule
