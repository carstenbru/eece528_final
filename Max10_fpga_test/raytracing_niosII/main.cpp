/********************************************************************************************************
*
* File                : LCD22(main)
* Hardware Environment:
* Build Environment   : Quartus II Version 10.1 / Nios II 10.1
* Version             :
* By                  : Su Wei Feng
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/



#include <io.h>
#include <stdlib.h>
#include <unistd.h>

#include "Raytracer.hpp"
#include "Sphere.hpp"


extern "C"{
#include "alt_types.h"
	#include <system.h>
	#include "altera_avalon_pio_regs.h"
	#include "LCD32.h"
	#include "touch.h"
};



void init_system_();


int main(void)
{

	int x,y;
	const int width = 320;
	const int height = 240;
	unsigned int frame[width][height];
	//frame = create_surface(width, height);

    init_system_();

    Raytracer raytracer(width, height);

    raytracer.generateSimpleScene();
    LCD_Clear(White);
    while (1)
   {
    	printf("Rendering\n");
    	raytracer.render((unsigned int*) frame);

    	//   DrawCross( 17,200);
    	//   vid_draw_line(1, 1, rand()%320, rand()%240 ,1, RGB565CONVERT(rand()%255,rand()%255,rand()%255) );
    	//   vid_draw_box (0, 0, 100, 100, RED_16,DO_FILL);

    	//   vid_draw_circle(150, 100, 50, BLUE_16, DO_FILL);
    	//   vid_print_string_alpha(0, 100, YELLOW_16, CLEAR_BACKGROUND, &tahomabold_20, "Fabio Gay");

  }


	return 0;
}

void init_system_(){
    IOWR_ALTERA_AVALON_PIO_DATA(BL_P_BASE, 1);
    IOWR_ALTERA_AVALON_PIO_DATA(BL_N_BASE, 0);

    TP_Init();
	LCD_Initializtion();

    LCD_Clear(Blue);
    LCD_Clear(Yellow);
    LCD_Clear(White);
    LCD_Clear(Black);
    LCD_Clear(Magenta);
    LCD_Clear(Red);
    LCD_Clear(Green);
    LCD_Clear(Cyan);

    auto_calibration();

    LCD_Clear(Black);
}
