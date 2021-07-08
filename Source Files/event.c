#include "library.h"
#include "draw.h"
#include "definitions.h"
#include "event.h"

extern bool IsGameOn,IsGameOver,IsIntroducrtionOn,IsRankingOn,InputOver; //�ж���Ϸ״̬�ĸ����������� 
extern int level; //�Ѷ� 
double bx=1.0,by=3.5; //С������ 
double v=0.0,a=0.022; //С���ٶ�����ٶ� 
int score=0;  //�÷� 
char str[10]; //������ʾ�������ַ����� 
bool outside=FALSE; //�ж�С���Ƿ���ϱ߽�Ĳ������� 

//��ʾ��ʼ���棺 
void displaymenu(){
DisplayClear();
if(!IsIntroducrtionOn&&(!IsRankingOn))
DrawMenu();
if(!IsIntroducrtionOn&&IsRankingOn)
DrawRanking();
if(IsIntroducrtionOn&&(!IsRankingOn))
DrawIntroduction();
}

//��ʾ��Ϸ���棺 
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
	
	   itoa(score,str,10);              //��������ת��Ϊ�ַ�������TextString��ʾ 
	   DrawScore();                     //ʵʱ��ʾ����

	if(Pipe_1.cx<0.2&&Pipe_1.cx>0.08){  //��¼���� 
	    score++;
		}
		
//�����ж��Ƿ���ײ�� 
	if(Pipe_1.cx>0.9&&Pipe_1.cx<=1.1){
	if(by-0.1>Pipe_1.cy+BlankHeight||by-0.1<Pipe_1.cy||(Pipe_1.cx-0.9)*(Pipe_1.cx-0.9)+(Pipe_1.cy-by+0.1)*(Pipe_1.cy-by+0.1)<0.175*0.175||(Pipe_1.cx-0.9)*(Pipe_1.cx-0.9)+(Pipe_1.cy+BlankHeight-by+0.1)*(Pipe_1.cy+BlankHeight-by+0.1)<0.175*0.175) 
	IsGameOver=TRUE;}
	else if(Pipe_1.cx<=0.9&&Pipe_1.cx>=0.3){
	if(by<Pipe_1.cy+0.25||by>Pipe_1.cy+BlankHeight-0.05) IsGameOver=TRUE;}
	else if(Pipe_1.cx<0.3&&Pipe_1.cx>=0.1){
	if(by-0.1>Pipe_1.cy+BlankHeight||by-0.1<Pipe_1.cy||(Pipe_1.cx-0.1)*(Pipe_1.cx-0.1)+(Pipe_1.cy-by+0.1)*(Pipe_1.cy-by+0.1)<0.35*0.35||(Pipe_1.cx-0.1)*(Pipe_1.cx-0.1)+(Pipe_1.cy+BlankHeight-by+0.1)*(Pipe_1.cy+BlankHeight-by+0.1)<0.35*0.35) 
	IsGameOver=TRUE;}
 
	
}

//��Ϸ����������ʾ�� 
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
	    DrawTextString("��Ӣ����������!������'#'������");                 //��ʾ�������� 
	}
    if(InputOver&&!IsRankingOn){
    	SetPenColor("Blue");
    	MovePen(WindowWidth/3 - 0.17, WindowHeight/3*2 - 1.38);
	    DrawTextString("���Ĵ����Ѿ�����ɹ���");                  //��ʾ����������� 
	}
    
}


//�û����ַ��¼���Ӧ������ 
void CharEventProcess(char ch)  
{
	uiGetChar(ch); //GUI�ַ����� 

} 

//�û��ļ����¼���Ӧ������
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event);
	
	//���¿ո�������Ϸ������С��һ�����ϵ��ٶ�
	if((key==VK_SPACE||key==VK_UP)&&event==KEY_DOWN)
	v=-0.17;

}

//�û�������¼���Ӧ������
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event);
	
	//������������С��һ�����ϵ��ٶ� 
	if(button==LEFT_BUTTON&&event==BUTTON_DOWN&&IsGameOn&&!outside)
	v=-0.17;
	
//�û��Ķ�ʱ����Ӧ������
}
void TimerEventProcess(int timerID)
{
		if(timerID==SHOW_MENU&&!IsGameOn)
	displaymenu();
	
	//��Ӧ�����Ѷ� 
	if (level==Easy&&timerID==SHOW_GAME_EASY&&IsGameOn&&!IsGameOver){
			displaygame();
	}
	if (level==Medium&&timerID==SHOW_GAME_MEDIUM&&IsGameOn&&!IsGameOver){
			displaygame();
	}
	if (level==Hard&&timerID==SHOW_GAME_HARD&&IsGameOn&&!IsGameOver){
			displaygame();
	}
	
	//����ˢ�¼�ʱ�� 
	if (timerID==SHOW_MENU&&IsGameOn&&IsGameOver){
			displaygameend();
			
	}


}



