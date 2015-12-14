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
#include "system.h"
#include "./Ray_tracing/Raytracer_int.hpp"
#include "./Ray_tracing/Sphere.hpp"


extern "C"{

	#include "frame.h"

};

#define FRAME_OFFSET 0x989680

VFR_PARAMETERS frame[] = {

    {
        0,
        1280, 800,// resolution
        0,
        /* words' divider is master_port_width (in bits) / 32, in deca_vip.qsys, port width is 256, therefore divider is 8 */
        256/32,//
        0,
        ALT_VIP_VFR_1_BASE,// base of the frame
        MEM_IF_DDR3_EMIF_BASE+FRAME_OFFSET,
        MEM_IF_DDR3_EMIF_BASE+SCREEN_WIDTH*SCREEN_HEIGHT*4+FRAME_OFFSET,
    }

};

int main(void)
{

	ConfigVFR(frame[0].vfr_register,
			 frame[0].width, frame[0].height,
			 frame[0].base0,
			  frame[0].base1,
			  frame[0].words_divider,
			  frame[0].cpr_halve
			  );


	cleanscreen((unsigned int*)frame[0].base0);

    Raytracer_int raytracer(640, 480);
    raytracer.setreal_frame_width(SCREEN_WIDTH);

    raytracer.generateSimpleScene();
    unsigned char count=0;
    while (1)
   {
    	printf("%d\n",count);
    	raytracer.render((unsigned int*)frame[0].base0);
    	// se activa el frame de video
		//VIPFR_ActiveDrawFrame(pReader);
    	count++;
  }


	return 0;
}


