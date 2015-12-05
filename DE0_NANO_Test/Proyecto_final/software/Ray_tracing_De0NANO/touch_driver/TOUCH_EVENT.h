/*
 * TOUCH_EVENT.h
 *
 *  Created on: 1/04/2014
 *      Author: Holguer A. Becerra
 *      Adrizcorp@gmail.com
 */

#ifndef TOUCH_EVENT_H_
#define TOUCH_EVENT_H_


#include "alt_touchscreen.h"


//************buttonevent_is_up_up********************************
// las acciones solo se realizaran, cuando exista un evento UP
// si el evento up existe procedemos a ejecutar una accion de acuerdo
// a la ultima posicion donde se hizo down
//************buttonevent_is_up_up********************************
int event_is_up(alt_touchscreen* touchscreen, int* posx, int* posy);


#endif /*TOUCH_EVENT_H_*/
