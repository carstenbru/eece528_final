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




#include <stdlib.h>
#include <unistd.h>

#include "./Ray_tracing/Raytracer_int.hpp"
#include "./Ray_tracing/Sphere.hpp"

#include <io.h>

extern "C"{
	#include "terasic_includes.h"
	#include "vip_fr.h"
	#include "./graphic_lib/simple_graphics.h"
	#include "./graphic_lib/gimp_bmp.h"
	#include "./graphic_lib/draw_gimps.h"
};

#define FRAME_WIDTH  800
#define FRAME_HEIGHT 600


#define FR_FRAME_0  (SDRAM_BASE)
#define FR_FRAME_1  (SDRAM_BASE+FRAME_WIDTH*FRAME_HEIGHT*4)


int main(void)
{

	int x,y;
	//frame = create_surface(width, height);

	VIP_FRAME_READER *pReader;

	////////Se inicializa el HW del sistema//////////////
	// frame reader

	pReader =  VIPFR_Init(ALT_VIP_VFR_0_BASE, (void *)FR_FRAME_0, (void *)FR_FRAME_0, FRAME_WIDTH, FRAME_HEIGHT);

   // se activa el frame de video
	VIPFR_ActiveDrawFrame(pReader);
	// clean screen
	vid_clean_screen(pReader, RED_24);
	// se activa el frame de video
	VIPFR_ActiveDrawFrame(pReader);
		// clean screen
	vid_clean_screen(pReader, RED_24);


    Raytracer_int raytracer(200, 200);
    raytracer.setreal_frame_width(FRAME_WIDTH);

    raytracer.generateSimpleScene();
    printf("Starting....\n");
    unsigned int count=0;
    while (1)
   {

    	IOWR(START_TIMER_BASE,0,1);
    	raytracer.render(pReader->DisplayFrame? (unsigned int*) pReader->Frame0_Base: (unsigned int*) pReader->Frame1_Base);
    	IOWR(START_TIMER_BASE,0,0);
    	printf("%d\n",IORD(TIMER_MEASUREMENT_BASE,0));
    	// se activa el frame de video
		VIPFR_ActiveDrawFrame(pReader);
    	count++;
  }


	return 0;
}


