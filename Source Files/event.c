#include "library.h"
#include "draw.h"
#include "definitions.h"
#include "event.h"

extern bool IsGameOn,IsGameOver,IsIntroducrtionOn,IsRankingOn,InputOver; //判断游戏状态的各个布尔变量 
extern int level; //难度 
double bx=1.0,by=3.5; //小鸟坐标 
double v=0.0,a=0.022; //小鸟速度与加速度 
int score=0;  //得分 
char str[10]; //用于显示分数的字符数组 
bool outside=FALSE; //判断小鸟是否出上边界的布尔变量 

//显示开始界面： 
void displaymenu(){
DisplayClear();
if(!IsIntroducrtionOn&&(!IsRankingOn))
DrawMenu();
if(!IsIntroducrtionOn&&IsRankingOn)
DrawRanking();
if(IsIntroducrtionOn&&(!IsRankingOn))
DrawIntroduction();
}

//显示游戏界面： 
void displaygame(){
	DisplayClear();
	DrawBackground();
	DrawBird(RandomInteger(1,4),bx,by);
	v+=a;
	by-=v;	
	if(by<=1.9)
	IsGameOver=TRUE;
	if(by>=7.3)
	outside=TRUE;
	else
	outside=FALSE;
	Pipe_1.cx-=Pipe_Speed;
    DrawPipe(Pipe_1.cx,Pipe_1.cy);
    Pipe_2.cx-=Pipe_Speed;
    DrawPipe(Pipe_2.cx,Pipe_2.cy);
	Pipe_3.cx-=Pipe_Speed;
    DrawPipe(Pipe_3.cx,Pipe_3.cy);
    if(Pipe_1.cx<=-0.6){
    	Pipe_1.cx=Pipe_2.cx;
	    Pipe_1.cy=Pipe_2.cy;
	    Pipe_2.cx=Pipe_3.cx;
	    Pipe_2.cy=Pipe_3.cy;
	    Pipe_3.cx=6.6;
	    double d=(double) (rand()%10);
	    Pipe_3.cy=d/10+rand()%3+2.4;
	    if(Pipe_3.cy>=4.4) Pipe_3.cy-=0.5;
	}
	
	   itoa(score,str,10);              //分数数字转换为字符便于用TextString显示 
	   DrawScore();                     //实时显示分数

	if(Pipe_1.cx<0.2&&Pipe_1.cx>0.08){  //记录分数 
	    score++;
		}
		
//下面判断是否碰撞： 
	if(Pipe_1.cx>0.9&&Pipe_1.cx<=1.1){
	if(by-0.1>Pipe_1.cy+BlankHeight||by-0.1<Pipe_1.cy||(Pipe_1.cx-0.9)*(Pipe_1.cx-0.9)+(Pipe_1.cy-by+0.1)*(Pipe_1.cy-by+0.1)<0.175*0.175||(Pipe_1.cx-0.9)*(Pipe_1.cx-0.9)+(Pipe_1.cy+BlankHeight-by+0.1)*(Pipe_1.cy+BlankHeight-by+0.1)<0.175*0.175) 
	IsGameOver=TRUE;}
	else if(Pipe_1.cx<=0.9&&Pipe_1.cx>=0.3){
	if(by<Pipe_1.cy+0.25||by>Pipe_1.cy+BlankHeight-0.05) IsGameOver=TRUE;}
	else if(Pipe_1.cx<0.3&&Pipe_1.cx>=0.1){
	if(by-0.1>Pipe_1.cy+BlankHeight||by-0.1<Pipe_1.cy||(Pipe_1.cx-0.1)*(Pipe_1.cx-0.1)+(Pipe_1.cy-by+0.1)*(Pipe_1.cy-by+0.1)<0.35*0.35||(Pipe_1.cx-0.1)*(Pipe_1.cx-0.1)+(Pipe_1.cy+BlankHeight-by+0.1)*(Pipe_1.cy+BlankHeight-by+0.1)<0.35*0.35) 
	IsGameOver=TRUE;}
 
	
}

//游戏结束界面显示： 
void displaygameend(){
	DisplayClear();
	if(IsRankingOn){
	DrawRanking();
	}
    else
    DrawGameEnd();
    if(!InputOver&&!IsRankingOn){
    	SetPenColor("Blue");
    	MovePen(WindowWidth/3 - 0.43, WindowHeight/3*2 - 1.0);
	    DrawTextString("请英雄留下姓名!（输入'#'结束）");                 //提示输入姓名 
	}
    if(InputOver&&!IsRankingOn){
    	SetPenColor("Blue");
    	MovePen(WindowWidth/3 - 0.17, WindowHeight/3*2 - 1.38);
	    DrawTextString("您的大名已经输入成功！");                  //提示姓名输入完毕 
	}
    
}


//用户的字符事件响应函数： 
void CharEventProcess(char ch)  
{
	uiGetChar(ch); //GUI字符输入 

} 

//用户的键盘事件响应函数：
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event);
	
	//按下空格键或向上方向键给小鸟一个向上的速度
	if((key==VK_SPACE||key==VK_UP)&&event==KEY_DOWN)
	v=-0.17;

}

//用户的鼠标事件响应函数：
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event);
	
	//按下鼠标左键给小鸟一个向上的速度 
	if(button==LEFT_BUTTON&&event==BUTTON_DOWN&&IsGameOn&&!outside)
	v=-0.17;
	
//用户的定时器响应函数：
}
void TimerEventProcess(int timerID)
{
		if(timerID==SHOW_MENU&&!IsGameOn)
	displaymenu();
	
	//对应三种难度 
	if (level==Easy&&timerID==SHOW_GAME_EASY&&IsGameOn&&!IsGameOver){
			displaygame();
	}
	if (level==Medium&&timerID==SHOW_GAME_MEDIUM&&IsGameOn&&!IsGameOver){
			displaygame();
	}
	if (level==Hard&&timerID==SHOW_GAME_HARD&&IsGameOn&&!IsGameOver){
			displaygame();
	}
	
	//界面刷新计时器 
	if (timerID==SHOW_MENU&&IsGameOn&&IsGameOver){
			displaygameend();
			
	}


}



