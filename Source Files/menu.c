#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "imgui.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

static double winwidth, winheight; 
static int    show_more_buttons1 = 0; 
static int    show_more_buttons2 = 0; 
static int    show_more_buttons3 = 0; 

void DisplayClear(void); 

void startTimer(int id,int timeinterval);

void display(void); 

void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); 
	display(); 
}

void Main() 
{
	SetWindowTitle("Flappy Bird");

    InitGraphics();

    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();

	registerMouseEvent(MouseEventProcess);      
}

void drawButtons()
{
	double fH = GetFontHeight();
	double h = fH*2; 
	double x = winwidth/2.5;  
	double y = winheight/2-2*h; 
	double w = winwidth/5; 

/*select level button*/
	if (button(GenUIID(0), x, y - 0.5, w, h, show_more_buttons1 ? "Select Level" : "Start"))
		show_more_buttons1 = ! show_more_buttons1;
	
/*levels to select*/
	if( show_more_buttons1 ) {
		int k;
		k = 1;
		char name[128]; 
		sprintf(name, "Easy", k);
		button(GenUIID(k), x + 0.2, y - k*h*2+0.25 - 0.4, w - 0.4, h*3/4, name);
		
		k = 2;
		sprintf(name, "Medium", k);
		button(GenUIID(k), x + 0.2, y - k*h*2+0.5 - 0.3, w - 0.4, h*3/4, name);
		
		k = 3;
		sprintf(name, "Hard", k);
		button(GenUIID(k), x + 0.2, y - k*h*2+0.75 - 0.2, w - 0.4, h*3/4, name);
	}
	
/*button to exist*/
	if( button(GenUIID(0), x + 4, y + 3, w/3, w/3, "Exit") )
		exit(-1);
	
/*button for settings*/	
	if (button(GenUIID(0), x - 3, y + 2, w/3, w/3, show_more_buttons2 ? "Setting" : "Setting"))
		show_more_buttons2 = ! show_more_buttons2;
		
/*button for bgm, click to on or off, no extra buttons*/
	if( show_more_buttons2 ) {
		if (button(GenUIID(0), x - 2.25, y + 2 + 0.15,w - 0.4, h*3/4, show_more_buttons3 ? "Sound On" : "Sound Off"))
		show_more_buttons3 = ! show_more_buttons3;
		
	}
	
/*button to show ranking, now written up to clearing the screen*/
	if( button(GenUIID(0), x - 3, y+3, w/3, w/3, "Ranking") )
		DisplayClear();
		//Show Ranking list
}

void display()
{
	DisplayClear();

	drawButtons();
}
