module Mandelbrot
    #(
        parameter W= 32, // width (# bits) of Qm. 
        parameter M= 4 // # of bits in m
    )
    (
        input wire clk, reset ,
        input wire start,
        input wire [W-1:0] cx, cy,
        input wire [15:0] max_it,
        output reg [15:0] iter,
        output reg idler
		  
    );

    // constant declaration
     localparam F = W - M; // # of bits in fraction

    // symbolic state declaration

    localparam [3:0] idle=4'b0001;
      localparam [3:0] load_data=4'b0010;
		localparam [3:0]  operation1= 4'b0011;
		localparam [3:0]  finish= 4'b0100;
		 localparam [3:0] resetea=   4'b0101;
		 localparam [3:0] finaliza=   4'b0110;
		 
		 localparam [3:0]  operation2= 4'b0111;
		 localparam [3:0]  operation3= 4'b1000;
		 localparam [3:0]  operation4= 4'b1001;
		 localparam [3:0]  operation5= 4'b1010;

		 
		  
		  
		  

    // signal declaration
    reg [3:0] state_reg, state_next;
    reg [15:0] it_reg , it_next;
    reg signed [2*W-1:0] xx_raw, yy_raw, xy_raw;
    reg signed [W-1:0] xx, yy, xy2;
    reg signed [W-1:0] x_reg, x_next, y_reg, y_next;
    reg signed [W-1:0] cx_reg, cx_next, cy_reg, cy_next;
	 wire	reset1;
    wire escape;
    reg frac_ready_i, frac_done;
	 reg reset_reg;
	 reg [31:0] suma;

     // body
    // FSMD state-data registers
    always@(posedge clk)
    begin
        if (reset)
            begin
                    state_reg <= idle;
                    it_reg <= 0;
                    x_reg <= 0;
                    y_reg <= 0;
                    cx_reg <= 0;
                    cy_reg <=0;
              end
        else
				begin
					case (state_reg[3:0])
					
					idle:											
							begin
							
							idler<=1'b1;
							
							if(start==1'b0)
								begin
									state_reg<=idle;
								end
							else
								begin								
									state_reg<=load_data;
								end
								
							end
							
					load_data:
							begin
							
							idler<=1'b0;
							
							x_reg<=cx; //x = cx;
							y_reg<=cy; //y = cy;				
							
							cx_reg<=cx; // nunca se modifican
							cy_reg<=cy; // nunca se modifican
							
							state_reg<=operation1; 
													
							end
					operation1: 
							begin
								state_reg<=operation2;  //while
								idler<=1'b0;
								xx_raw <= x_reg * x_reg; //   xx_raw= (fixed856)(x) * (fixed856)(x);	
							end
						
					operation2:
							begin
								state_reg<=operation3;  //while
								idler<=1'b0;
								xx<= xx_raw[2*W-1:28] ; //  xx = (fixed428)(xx_raw >> 28);
								yy_raw <= y_reg * y_reg; //   yy_raw = (fixed856)(y) * (fixed856)(y);
							end
					operation3:
							begin
								state_reg<=operation4;  //while
								idler<=1'b0;
								yy <=  yy_raw >> 28; //    yy = (fixed428)(yy_raw >> 28);
								xy_raw <= x_reg * y_reg; //  xy_raw=(fixed856)(x) * (fixed856)(y);
							end
					operation4:
							begin
							
								state_reg<=operation5;  //while
								idler<=1'b0;
								
								xy2 <= xy_raw >> 27 ; // xy2 = (fixed428)(xy_raw>>27); // 2* is same as «1															
							  x_reg<= xx-yy+ cx_reg;    //   x = xx - yy + cx; 
							  
							  suma<= xx+yy;
							  
							  end
		
					operation5:
							begin
							  y_next<=  xy2+cy_reg;  //     y =  xy2 + cy;
							  it_reg<=  it_reg +1;  //     itr++;
							  
							  if((suma<32'h40000000) && ( it_reg <  max_it )) //while (((xx+yy)<0x40000000) && ( itr < max_itr ) ) ;
								begin
								state_reg<=operation1;  //while
																		
								end
								else
								state_reg<=finish;
							
								
							end
			
					finish:
						 begin
						  idler<=0;
						  it_reg <= 0;
                    x_reg <= 0;
                    y_reg <= 0;
                    cx_reg <= 0;
                    cy_reg <=0;
						  iter<=it_reg; //return(itr);
						  state_reg<=idle;
						  end
						  
					default:
						begin
							state_reg<=idle;
						end
			endcase
			
			end
		end
		
		

			
endmodule
								
							
					
						
					
						
//					
//					
//					
//								
//							
//								
//								
//							
//								
//					
//							 
//					
//		  
//            begin
//                    state_reg<= state_next;
//                    it_reg <= it_next;
//                    x_reg <= x_next;
//                    y_reg <= y_next;
//                    cx_reg<= cx_next;
//                    cy_reg<=cy_next;
//            end
//        end
//
//     // fixed-point  multiplications
//
//        assign xx_raw = x_reg * x_reg; // in Q2m.2f
//        assign xx= xx_raw [(2*W-1)-M:F]; // back to Qm.f
//        assign yy_raw = y_reg * y_reg; // in Q2m.2f
//        assign yy =  yy_raw [(2*W-1)-M:F]; // back to Qm.f
//        assign xy_raw = x_reg * y_reg; // xy in Q2m.2f
//        assign xy2=xy_raw[(2*W-1)-M-1:F-1] ; // 2xy in Qm. f
//
//        // escape condition
//
//        assign escape = (xx+yy > 32'h40000000);
//
//        //FSMD next-state logic
//
//       always @*
//        begin
//                state_next = state_reg;
//                it_next = it_reg;
//                x_next = x_reg;
//                y_next = y_reg;
//    cx_next = cx_reg;
//    cy_next = cy_reg;
//    frac_ready_i = 1'b0;
//    frac_done = 1'b0;
//    case (state_reg)
//        idle:
//            begin
//                    frac_ready_i = 1'b1;
//                    if (frac_start)
//                        begin
//                               x_next = cx;
//                                            y_next = cy;
//                                            cx_next =cx;
//                                            cy_next = cy;
//                                             it_next =0;
//                                            state_next = op;
//                                        end
//                                end
//                        
//                       op:
//
//                            begin
//                                   x_next= xx-yy+cx_reg;            
//                                   y_next=  xy2+cy_reg;
//                                   it_next=  it_reg +1;
//        
//                                    if (escape | (it_next==max_it))
//                                        begin    
//                                             state_next=idle;
//                                             frac_done= 1'b1;
//                                        end
//                               end
//                      endcase
//
//                    end
//
//
//               // output assignment
//                    assign iter=  it_reg;
//                    assign frac_done_tick = frac_done ;
//                    assign frac_ready =  frac_ready_i ;
//
//endmodule