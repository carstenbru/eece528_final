module normalize (
        clk,
        start,
		  finish,
        v0x,
        v0y,
        v0z,
        resx,
		  resy,
		  resz,test0,test1
);

parameter SQRT_PIPELINE_STEPS = 2;
parameter DIVIDER_PIPELINE_STEPS = 3;

input clk;
input start;
output reg finish;
input [31:0] v0x;
input [31:0] v0y;
input [31:0] v0z;
output reg [31:0] resx;
output reg [31:0] resy;
output reg [31:0] resz;
output wire [31:0] test0,test1;
assign test0[31:0] = invNor[31:0];
assign test1[31:0] = length[23:0];

wire [63:0] length2;
wire [23:0] length; //Q16.8 format
wire [39:0] invNor;

wire [63:0] resx_w;
wire [63:0] resy_w;
wire [63:0] resz_w;

reg [2:0] state;


length (
	.dataa_0(v0x[31:0]),
	.dataa_1(v0y[31:0]),
	.dataa_2(v0z[31:0]),
	.datab_0(v0x[31:0]),
	.datab_1(v0y[31:0]),
	.datab_2(v0z[31:0]),
	.result(length2[63:0]));
	
sqrt	sqrt_length (
   .clk(clk),
	.radical ( length2[63:16] ),
	.q ( length[23:0] )
	//.remainder (  )
	);
defparam sqrt_length.ALTSQRT_component.pipeline = SQRT_PIPELINE_STEPS;

normalize_divider n_divider(
	.clock(clk),
	.denom(length[23:0]),
	.numer(25'd16777216),
	.quotient(invNor[39:0]),
	//.remain()
	);
defparam n_divider.LPM_DIVIDE_component.lpm_pipeline = DIVIDER_PIPELINE_STEPS;

	
multi_hw	(
	.dataa ( v0x[31:0] ),
	.datab ( invNor[31:0] ),
	.result ( resx_w[63:0] )
	);
multi_hw	(
	.dataa ( v0y[31:0] ),
	.datab ( invNor[31:0] ),
	.result ( resy_w[63:0] )
	);
multi_hw	(
	.dataa ( v0z[31:0] ),
	.datab ( invNor[31:0] ),
	.result ( resz_w[63:0] )
	);
	
always @(posedge clk) begin
  if (start) begin
    finish <= 1'b0;
	 state <= 3'd0;
  end else begin
    if (finish == 1'b0) begin
      state <= state+1;
	   if (state == SQRT_PIPELINE_STEPS + DIVIDER_PIPELINE_STEPS - 1) begin
	     finish <= 1'b1;
		  resx[31:0] <= resx_w[47:16];
		  resy[31:0] <= resy_w[47:16];
		  resz[31:0] <= resz_w[47:16];
	   end
	 end
  end
end


endmodule