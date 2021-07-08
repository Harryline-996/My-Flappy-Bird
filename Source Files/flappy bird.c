#include "library.h"
#include "draw.h"
#include "definitions.h"
#include "event.h"

//此文件是主源文件

void Main()
{
	SetWindowSize(WindowWidth, WindowHeight);             //初始化图形界面 
	SetWindowTitle("Flappy Bird");
	InitGraphics();                

	registerCharEvent(CharEventProcess);                  //注册回调函数 
    registerKeyboardEvent(KeyboardEventProcess);
    registerMouseEvent(MouseEventProcess);
    registerTimerEvent(TimerEventProcess);
    
    startTimer(SHOW_GAME_EASY,timer_interval_easy);       //打开定时器 
    startTimer(SHOW_GAME_MEDIUM ,timer_interval_medium);
    startTimer(SHOW_GAME_HARD ,timer_interval_hard);
    startTimer(SHOW_MENU ,timer_interval_menu);
    
    Pipe_1.cx=5.0;                                        //画第一根水管 
    srand(time(0));
    double d=(double) (rand()%10);
	Pipe_1.cy=d/10+rand()%2+2.4;
	if(Pipe_3.cy>=4.4) Pipe_3.cy-=0.5;
    Pipe_2.cx=7.4;
    Pipe_2.cy=2;
    Pipe_3.cx=9.8;
    Pipe_3.cy=4;


} 




