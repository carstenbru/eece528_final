/*
 * TOUCH_EVENT.c
 *
 *  Created on: 1/04/2014
 *      Author: Holguer A. Becerra
 *      Adrizcorp@gmail.com
 */



#include "TOUCH_EVENT.h"

/*Funcion event_is_up
 * esta funcion devuelve un valor entere de acuerdo al evento que
 * se presente en la membrana touch, teniendo como base el evento down 
 * del driver
 * 
 * Implementación:
 * int event,pos_x,pos_y;
 * event = event_is_up(&touchscreen,&pos_x,&pos_y);
 * 
 * si event = 0, el evento es DOWN.
 * si event = 1, el evento es UP.
 * si event = 3, el evento es IDLE.
 * si event = -1, estado no desado. 
 * */
//#define MOUSE  

#ifdef MOUSE

#include "system.h"
#include "altera_avalon_pio_regs.h"

#define GET_X_MOUSE  ((IORD_ALTERA_AVALON_PIO_DATA(MOUSE_DXY_BASE)>>10) & 0x3ff)
#define GET_Y_MOUSE  ((IORD_ALTERA_AVALON_PIO_DATA(MOUSE_DXY_BASE)) & 0x3ff)
#define GET_PEN_DOWN_MOUSE  ((IORD_ALTERA_AVALON_PIO_DATA(MOUSE_DXY_BASE)>>20) & 0x1)
#endif
 
int STATE_touch=0;
int x_touch,y_touch=0;
int x2,y2_touch=0; 
 
int event_is_up(alt_touchscreen* touchscreen, int* posx, int* posy)
{

int pen_is_down;
    
#ifdef MOUSE
    pen_is_down=GET_PEN_DOWN_MOUSE;
    y_touch=GET_Y_MOUSE;
    x_touch=GET_X_MOUSE;
    //printf("X: %d, Y: %d, PD: %d",x_touch,y_touch,pen_is_down);
#else
    alt_touchscreen_get_pen (touchscreen, &pen_is_down, &x_touch, &y_touch );
//    printf("X: %d, Y: %d, PD: %d\n",x_touch,y_touch,pen_is_down);
//    printf("adcX: %d, adcY: %d, PD: %d\n",touchscreen->pen_adc_data.x,touchscreen->pen_adc_data.y,pen_is_down);
#endif


if(pen_is_down){
     STATE_touch=1;
     x2=x_touch;
     y2_touch=y_touch;
     *posx=x2;
     *posy=y2_touch;
     //printf("x_touch=%d, y_touch= %d \n",x_touch,y_touch);
     return 0;// STATE_touch DOWN
    }
else{
    if(STATE_touch==1){
    STATE_touch=0;
    *posx=x2;
    *posy=y2_touch;
    //printf("Event UP %d  %d \n",x2,y2_touch);
    return 1;// Now event is up// STATE_touch UP
    }
    *posx=x_touch;
    *posy=y_touch;
    return 3; // STATE_touch IDLE
}

return -1;// No deseable
                         
}

