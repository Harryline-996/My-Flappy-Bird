#include "library.h"
#include "draw.h"
#include "definitions.h"
#include "event.h"

//���ļ�����Դ�ļ�

void Main()
{
	SetWindowSize(WindowWidth, WindowHeight);             //��ʼ��ͼ�ν��� 
	SetWindowTitle("Flappy Bird");
	InitGraphics();                

	registerCharEvent(CharEventProcess);                  //ע��ص����� 
    registerKeyboardEvent(KeyboardEventProcess);
    registerMouseEvent(MouseEventProcess);
    registerTimerEvent(TimerEventProcess);
    
    startTimer(SHOW_GAME_EASY,timer_interval_easy);       //�򿪶�ʱ�� 
    startTimer(SHOW_GAME_MEDIUM ,timer_interval_medium);
    startTimer(SHOW_GAME_HARD ,timer_interval_hard);
    startTimer(SHOW_MENU ,timer_interval_menu);
    
    Pipe_1.cx=5.0;                                        //����һ��ˮ�� 
    srand(time(0));
    double d=(double) (rand()%10);
	Pipe_1.cy=d/10+rand()%2+2.4;
	if(Pipe_3.cy>=4.4) Pipe_3.cy-=0.5;
    Pipe_2.cx=7.4;
    Pipe_2.cy=2;
    Pipe_3.cx=9.8;
    Pipe_3.cy=4;


} 




