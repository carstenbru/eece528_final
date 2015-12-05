
 
// SNES Controller MODULE
// Written by Fabio Andres Hernandez Rueda
// ECE 31289 UPB
// Year 2014
// https://sites.google.com/site/ece31289upb

module snes_controller(
			   clk_166MHz, // FSM clk
			   sclk, //  SNES Clk
			   latch, // SNES Latch
			   datain, // SNES data
			   start, // FSM start
			   finish, // FSM finish
			   boton_B, 
			   boton_Y,
			   boton_SELECT,
			   boton_START,
			   boton_UP,
			   boton_DOWN,
			   boton_LEFT,
			   boton_RIGHT,
			   boton_A,
			   boton_X,
			   boton_L,
			   boton_R);

 //reloj de la maquina de estados
input datain; // datos que envia el control
input start;  // señal de start
output sclk;  // reloj que se envia al control
output latch; // señal de latch
input  clk_166MHz;
output finish; // salida que indica que se han tomado los datos
output  boton_B;
output  boton_Y;
output  boton_SELECT;
output  boton_START;
output  boton_UP;
output  boton_DOWN;
output  boton_LEFT;
output  boton_RIGHT;
output  boton_A; 
output  boton_X;
output  boton_L; 
output  boton_R;



localparam idle   = 7'b 0001_1_1_0; 
localparam second = 7'b 0010_0_1_0;
localparam third  = 7'b 0100_0_0_0;
localparam fourth = 7'b 1000_1_1_1;

reg [6:0] state = idle;  /// inicia registro estado idle
reg [4:0] counter = 5'd0;  /// conteo de 0 a 15
reg [11:0] Data_IN;
reg [2:0] ADDR;
reg [15:0]data;

reg [15:0]botones;


wire finish; // salida que indica que se han tomado los datos

			 
assign sclk = state[1]; // sclk es el bit uno del estado
assign finish = state[0]; // stado fourth=1
assign latch = state[2]; //stado third=1



always @ (posedge clk_166MHz) //el reloj principal controla el cambio de estados
begin
   
	        case (state)
			
			idle: 
			begin
			      if (!start)
				  begin
				  state[6:0]<=idle;
				  end
				  else
				  begin
				  state[6:0]<=second; // cuando la señal de start da inicio, se pasa al estado second
				  end
			end
			
			second:
			begin
			      if (counter<=5'd15) // del estado second si no se ha llegado al final pasa al tercer estado
				  begin
				  state[6:0]<=third;
				  end
				  else
				  begin
				  state[6:0]<=fourth; // si se llego al final se pasa al estado final
				  end
			end
			
			third:
			begin
			     state[6:0]<=second;		 // se devuelve al estado dos	
			end
			
			fourth:
			begin 
			     state[6:0]<=idle;  // al llegar al estado final, se resetea la fsm
			end
			
			default:
			begin
			     state[6:0]<=idle;
			end
			
			endcase
			
	  end
	      
	  
	  




always @ (posedge sclk, posedge finish)
begin
      
	       if (finish)
		   begin 
		   counter[4:0] <= 5'd0; // si se llega a finish se reinicia el contador
		   end
		   else
		   begin
		   counter[4:0] <= counter[4:0]+1'b1; // si no se suma uno
		   end
	  end


				
always @ (posedge sclk)
begin
     
	  if(counter<=15)
	  begin 
	  data[15:0] <= {data[14:0],datain}; //hasta el ciclo doce se toman datos
	  end
end

always @(posedge finish)
begin
	botones<=data;
end

assign  boton_B=botones[15];
assign  boton_Y=botones[14];
assign  boton_SELECT=botones[13];
assign  boton_START=botones[12];
assign  boton_UP=botones[11];
assign  boton_DOWN=botones[10];
assign  boton_LEFT=botones[9];
assign  boton_RIGHT=botones[8];
assign  boton_A=botones[7]; 
assign  boton_X=botones[6];
assign  boton_L=botones[5]; 
assign  boton_R=botones[4];

endmodule
