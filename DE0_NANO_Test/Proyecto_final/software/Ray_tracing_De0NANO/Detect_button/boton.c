/*
 * snes_listext.c
 *
 *  Created on: 19/04/2014
 *      Author:
 */
#include <stdio.h>
#include "boton.h"
#include  <system.h>
#include "io.h" // I/O access

int rom_index=0;

char y_snes_now=1;
char y_snes_previous=1;

char x_snes_now=1;
char x_snes_previous=1;
char l_snes_now=1;
char l_snes_previous=1;
char r_snes_now=1;
char r_snes_previous=1;
char left_snes_now=1;
char left_snes_previous=1;
char right_snes_now=1;
char right_snes_previous=1;
char up_snes_now=1;
char up_snes_previous=1;
char down_snes_now=1;
char down_snes_previous=1;

/***************************************************************************/
/*SUB-FUNCIONES                                                                 */
/***************************************************************************/


char Y_snes()
{
	char result;
	result=-1;

	y_snes_now=IORD(BOTON_Y_BASE,0);
	if(y_snes_now!=y_snes_previous){

		if(y_snes_now==1 && y_snes_previous==0){
			result=1;//event up
		}
		else if(y_snes_now==0 && y_snes_previous==1){
			result=2;//event down
		}
		y_snes_previous=y_snes_now;
	}

	return result;
}





char X_snes_event_up()
{
char result_x;
result_x=-1;

x_snes_now=IORD(BOTON_X_BASE,0);
if(x_snes_now!=x_snes_previous)
{
  if(x_snes_now==1 && x_snes_previous==0)
  {
     result_x=1;//event up
  }
  else if(x_snes_now==0 && x_snes_previous==1)
  {
     result_x=2;//event down
  }
  x_snes_previous=x_snes_now;
}
return result_x;
}



char L_snes_event_up()
{
char return1;
return1=-1;

l_snes_now=IORD(BOTON_L_BASE,0);
if(l_snes_now!=l_snes_previous)
{
  if(l_snes_now==1 && l_snes_previous==0)
  {
     return1=1;//event up
  }
  else if(l_snes_now==0 && l_snes_previous==1)
  {
     return1=2;//event down
  }
  l_snes_previous=l_snes_now;
}
return return1;
}


char R_snes_event_up()
{
char return1;
return1=-1;

r_snes_now=IORD(BOTON_R_BASE,0);
if(r_snes_now!=r_snes_previous)
{
  if(r_snes_now==1 && r_snes_previous==0)
  {
     return1=1;//event up
  }
  else if(r_snes_now==0 && r_snes_previous==1)
  {
     return1=2;//event down
  }
  r_snes_previous=r_snes_now;
}
return return1;
}


char UP_snes_event_up()
{
char return1;
return1=-1;

up_snes_now=IORD(BOTON_UP_BASE,0);
if(up_snes_now!=up_snes_previous)
{
  if(up_snes_now==1 && up_snes_previous==0)
  {
     return1=1;//event up
  }
  else if(up_snes_now==0 && up_snes_previous==1)
  {
     return1=2;//event down
  }
  up_snes_previous=up_snes_now;
}
return return1;
}

char DOWN_snes_event_up()
{
char return1;
return1=-1;

down_snes_now=IORD(BOTON_DOWN_BASE,0);
if(down_snes_now!=down_snes_previous)
{
  if(down_snes_now==1 && down_snes_previous==0)
  {
     return1=1;//event up
  }
  else if(down_snes_now==0 && down_snes_previous==1)
  {
     return1=2;//event down
  }
  down_snes_previous=down_snes_now;
}
return return1;
}


char LEFT_snes_event_up()
{
char return1;
return1=-1;

left_snes_now=IORD(BOTON_LEFT_BASE,0);
if(left_snes_now!=left_snes_previous)
{
  if(left_snes_now==1 && left_snes_previous==0)
  {
     return1=1;//event up
  }
  else if(left_snes_now==0 && left_snes_previous==1)
  {
     return1=2;//event down
  }
  left_snes_previous=left_snes_now;
}
return return1;
}

char RIGHT_snes_event_up()
{
char return1;
return1=-1;

right_snes_now=IORD(BOTON_RIGHT_BASE,0);
if(right_snes_now!=right_snes_previous)
{
  if(right_snes_now==1 && right_snes_previous==0)
  {
     return1=1;//event up
  }
  else if(right_snes_now==0 && right_snes_previous==1)
  {
     return1=2;//event down
  }
  right_snes_previous=right_snes_now;
}
return return1;
}












