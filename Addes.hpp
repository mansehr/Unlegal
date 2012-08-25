			//////////////////////////////////////////////////////////
			//														//
			//			Fil: "Unlegal.cpp"							//
			//														//
			//			Författad av: Andreas Sehr 2001,09,15		//
			//														//
			//			Senast ändrad:	2002,01,07					//
			//														//
			//			Annvänds till mina egna objekt hpp filer	//
			//														//
			//////////////////////////////////////////////////////////

#include "math.h"
#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>

BITMAP *bmp;

//Färger
enum  COLOUR {
	BLACK = 0,
	DARKBLUE = 4,
	LIGHTGREY = 8,
	GREY = 247,
	DARKGREY = 248,
	RED = 249,
	YELLOW = 251,
	BLUE = 252,
	WHITE = 255
};
const int text_color = 170;
const int bokstavsBredd = 8;

enum Status { Null = 0, NotPressable, Hoover, Active, Pressed };

ofstream fout("res.txt");

const double RAD = M_PI/180;
char  te[80];
void cirkel()
{
	int temp = 0;
	clear(screen);

	temp++;
	sprintf(te,"Hejsan!! Antal tryck: %d",  temp);
	textout(screen, font, te, 10, 10, text_color);

	double x,y;
	int radie = 10;
	int left = 100,top = 100,bottom = 140, right = 200;
/*	line(screen, left + radie, top, right - radie, top, WHITE);
	line(screen, left + radie, bottom, right - radie, bottom, WHITE);
	line(screen, left, top + radie, left, bottom - radie, WHITE);
	line(screen, right, top + radie, right, bottom - radie, WHITE);
*/
//Bakgrund
	rectfill(screen, left, top, right, bottom, GREY);
//Yttre boxen
	line(screen, left + radie, bottom, right - radie, bottom, BLACK);
	line(screen, right - radie, bottom, right - radie, top, BLACK);
	line(screen, left + radie, bottom-1, left + radie, top, WHITE);
	line(screen, left + radie, top, right - radie-1, top, WHITE);
//Inre boxen
	line(screen, left + radie+1, bottom-1, left + radie+1, top+1, LIGHTGREY);
	line(screen, left + radie+1, top+1, right - radie-1, top+1, LIGHTGREY);
	line(screen, right - radie-1, bottom-1, right - radie-1, top+1, DARKGREY);
	line(screen, left + radie+1, bottom-1, right - radie-1, bottom-1, DARKGREY);

	for (double i = 0; i < 360; i+=1)
	{
		x = sin(i*RAD) * radie;
		y = cos(i*RAD) * radie;

		if (i > -1 && i < 90)
		{
			x += right - radie;
			y += bottom - radie;
		}
		else if (i > 89 && i < 180)	{
			x += right - radie;
			y += top + radie;
		}
		else if (i > 179 && i < 270)	{
			x += left + radie;
			y += top + radie;
		}
		else if (i > 269)	{
			x += left + radie;
			y += bottom - radie;
		}
		putpixel(screen, int (x) , int (y), WHITE);
	}

	while ((!key[KEY_ESC]) && (!key[KEY_SPACE]));
}

		//Inkludera dem i rätt ordning....
#include "String.hpp"
#include "Point.hpp"
#include "Objekt.hpp"
#include "TextField.hpp"
#include "List.hpp"
#include "Button.hpp"
#include "Radio.hpp"
#include "MenuButton.hpp"
#include "Menu.hpp"

#include "RitaObjekt.hpp"
RitaObjekt rita;

#include "ActionEvent.hpp"
ActionEvent actionEvent;
void ActionHandler(ActionEvent &ev);

#include "ActionListener.hpp"
ActionListen actionListener;


