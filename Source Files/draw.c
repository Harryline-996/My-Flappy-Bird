#include "library.h"
#include "draw.h"
#include "definitions.h"
#include "event.h"

//����һϵ���ж���Ϸ״̬�Ĳ��������� 
bool IsGameOn=FALSE;
bool IsGameOver=FALSE;
bool IsIntroducrtionOn=FALSE;
bool IsRankingOn=FALSE;
bool InputOver=FALSE;

int level;                          //�Ѷ� 
extern double by,v,a;               //С���йز��� 
extern int score;                   //�÷� 
extern char str[10];                //������ʾ�������ַ����� 
Player players[1000];        //��ҽṹ���� 
int playercode=0;                   //��Ҵ��� 

//�������� 
void DrawBackground(){              
	MovePen(0,0);
	StartFilledRegion(0.38);
	SetPenColor("Yellow"); 
	DrawLine(WindowWidth,0);
	DrawLine(0,GroundHeight-0.3);
	DrawLine(-WindowWidth,0);
	DrawLine(0,0.3-GroundHeight);
	EndFilledRegion();
	MovePen(0,GroundHeight-0.3);
	StartFilledRegion(0.4);
	SetPenColor("Black"); 
	DrawLine(WindowWidth,0);
	DrawLine(0,0.3);
	DrawLine(-WindowWidth,0);
	DrawLine(0,-0.3);
	EndFilledRegion();
}

//��������壺 
void DrawBird(int state, double bx, double by){  
	MovePen(bx,by);
	StartFilledRegion(0.88);
	SetPenColor("Blue");
	DrawEllipticalArc(0.2,0.15,55,240); //������ 
	EndFilledRegion();
	MovePen(bx,by);
	SetPenColor("Black");
	DrawEllipticalArc(0.2,0.15,55,240);
	MovePen(bx+0.05,by-0.07);
	StartFilledRegion(0);
	DrawEllipticalArc(0.091,0.079,0,360);
	EndFilledRegion();
	SetPenSize(3);                      //���۾�
	MovePen(bx-0.03,by-0.08);
	DrawLine(0,0.015);
	SetPenSize(1);                      //���
	StartFilledRegion(0.88);
	SetPenColor("Red");
    MovePen(bx-0.08,by-0.15);
	DrawLine(0.16,0.005);
	DrawLine(0.01,-0.02);
	DrawLine(-0.01,-0.02);
	DrawLine(-0.15,-0.005);
	DrawLine(0.13,-0.02);
	DrawLine(0,-0.03);
	DrawLine(-0.14,0.005);
	DrawLine(-0.025,0.025);
    DrawLine(0,0.037);
    DrawLine(0.025,0.025);
    EndFilledRegion();
    SetPenColor("Black");
    MovePen(bx-0.08,by-0.15);
	DrawLine(0.16,0.005);
	DrawLine(0.01,-0.02);
	DrawLine(-0.01,-0.02);
	DrawLine(-0.15,-0.005);
	DrawLine(0.13,-0.02);
	DrawLine(0,-0.03);
	DrawLine(-0.14,0.005);
	DrawLine(-0.025,0.025);
    DrawLine(0,0.037);
    DrawLine(0.025,0.025);
    MovePen(bx-0.2,by-0.13);
    StartFilledRegion(0);              //����������״̬
    if(state==WINGMID)
    DrawEllipticalArc(0.085,0.047,0,360);
    else if(state==WINGUP){
    DrawLine(0,0.04);
    DrawLine(-0.06,0.06);
    DrawLine(-0.06,0);
    DrawLine(-0.04,-0.02);
    DrawLine(0,-0.08);
    DrawLine(0.04,-0.04);
    DrawLine(0.06,0);
    DrawLine(0.06,0.02);
	}
	else if(state==WINGDOWN){
	DrawLine(-0.14,0);
	DrawLine(-0.03,-0.03);
	DrawLine(0,-0.06);
	DrawLine(0.03,-0.03);
	DrawLine(0.07,0);
	DrawLine(0.10,0.10);
	DrawLine(-0.03,0.02);
	}
    EndFilledRegion();
    
}

//��ˮ��:
void DrawPipe(double PipeLocation, double PipeHeight){   
	MovePen(PipeLocation,PipeHeight-0.2);
	StartFilledRegion(0.7);                      //�¹���ɫ
	SetPenColor("Green");
	DrawLine(0,0.2+GroundHeight-PipeHeight);
	DrawLine(0.6,0);
	DrawLine(0,PipeHeight-GroundHeight-0.2);
	DrawLine(-0.7,0);
	DrawLine(0,0.2);
	DrawLine(0.8,0);
	DrawLine(0,-0.2);
	DrawLine(-0.1,0);
	EndFilledRegion();
	SetPenColor("Black");                        //�¹���� 
    MovePen(PipeLocation,PipeHeight-0.2);
	DrawLine(0,0.2+GroundHeight-PipeHeight);
	DrawLine(0.6,0);
	DrawLine(0,PipeHeight-GroundHeight-0.2);
	DrawLine(-0.7,0);
	DrawLine(0,0.2);
	DrawLine(0.8,0);
	DrawLine(0,-0.2);
	DrawLine(-0.1,0);
	
	MovePen(PipeLocation,PipeHeight+BlankHeight+0.2);           //�Ϲ���ɫ 
	StartFilledRegion(0.7);
	SetPenColor("Green");
	DrawLine(0,6.8-PipeHeight-BlankHeight);
	DrawLine(0.6,0);
	DrawLine(0,PipeHeight+BlankHeight-6.8);
	DrawLine(-0.7,0);
	DrawLine(0,-0.2);
	DrawLine(0.8,0);
	DrawLine(0,0.2);
	DrawLine(-0.1,0);
	EndFilledRegion();
	MovePen(PipeLocation,PipeHeight+BlankHeight+0.2);           //�Ϲ���� 
	SetPenColor("Black");
	DrawLine(0,6.8-PipeHeight-BlankHeight);
	DrawLine(0.6,0);
	DrawLine(0,PipeHeight+BlankHeight-6.8);
	DrawLine(-0.7,0);
	DrawLine(0,-0.2);
	DrawLine(0.8,0);
	DrawLine(0,0.2);
	DrawLine(-0.1,0);
}

//�����а�:
void DrawRanking(){    

    PrintRanking();
    SetPointSize(10); 
 	double fH = GetFontHeight();
	double h = fH*2; 
	double w = WindowWidth/5;    
setButtonColors("Soft Yellow", "Brown", "Soft Yellow", "Soft Orange", 1); //�����а��пؼ� 
	if (button(GenUIID(0), 0.37, 1, w*2 - 0.4, h*3/4, "������һ���˵�")){
		IsRankingOn=FALSE;
		}
	if (button(GenUIID(0), 3.0, 1, w*2 - 0.4, h*3/4, "�������а�")){
	    initfile(); 
		}
}

//���ļ��ж�ȡ���а���Ϣ����ʾ:
void PrintRanking()  
{
	FILE *fp;
	char s[20][30];
	int i,j;
	
	SetPointSize(35);                 //�����а�Ľ��� 
	SetPenColor("Red");
	MovePen(WindowWidth/2.0-0.5, 6.6);
	DrawTextString("Top 10");
	SetPointSize(24);
	SetPenColor("Blue");
	MovePen(0.5, 6);
	DrawTextString("Player");
	MovePen(3.7, 6);
	DrawTextString("Score");
	
	fp=fopen("ranking.txt","r");      //���ļ��ж�ȡ��������ͷ��� 

	for(i=0;i<20;i++)
	{
		fgets(s[i],30,fp);
		if(!strcmp(s[i],"*"))
			break;
	}

	for(j=0;j<i;j+=2)                //��ʾ��������ͷ��� 
	{ 
	SetPointSize(20);
	SetPenColor("Black");
	MovePen(0.6, 5.5-j/5.0);
	DrawTextString(s[j]);
	MovePen(4, 5.5-j/5.0);
	DrawTextString(s[j+1]);
	}

	fclose(fp);
}

//չʾ��Ϸ˵�����棺 
void DrawIntroduction(){          
	double fH = GetFontHeight();
	double h = fH*2; 
	double x = 0.0;  
	double y = WindowHeight-2*h; 
	double w = WindowWidth/5; 
	double m =  TextStringWidth("(һ)��Ϸ˵��   "); 

	SetPenColor("Red");
	drawLabel(0.1 ,  y , "����˵��");
	SetPenColor("Black");
	drawLabel(0.1 ,  y - h , "1.��ʼ�˵��������Ѷȹ���ѡ��");
	drawLabel(0.1 ,  y - 2 * h , "2.������ٿ�ʼ�Զ�Ĭ��Ϊ�Ѷ�Ϊ��");
	drawLabel(0.1 ,  y - 3 * h , "3.������������¼��̿ո�������ϼ�ʹС������");
	drawLabel(0.1 ,  y - 4 * h , "4.��������������������������С����Զ�����");
	drawLabel(0.1 ,  y - 5 * h , "5.���׻�����ˮ�ܵĻ���GameOver�ˣ�");
	drawLabel(0.1 ,  y - 6 * h , "6.��Ϸ����֮�������ı���������������'#'��β"); 
	drawLabel(0.1 ,  y - 7 * h , "7.������а�ť���Բ鿴�������"); 

	SetPenColor("Red");
	drawLabel(0.1 ,  y - 9 * h   , " ******************************************* ");
	drawLabel(0.1 ,  y - 10 * h   , " ����Ϸ�� ���� ��� �վ�� ������� ");
	drawLabel(0.1 ,  y - 11 * h  , " ******************************************* ");
	
	setButtonColors("Soft Yellow", "Brown", "Soft Yellow", "Soft Orange", 1);         //���������水ť 
	if (button(GenUIID(0), 0.37, 1, w*2 - 0.4, h*3/4, "������һ���˵�")){
		IsIntroducrtionOn=FALSE;
		}
	
}

//ʵʱ��ʾ������ 
void DrawScore(){  

	MovePen(WindowWidth/2-0.1,6);
	SetPointSize(40);
	DrawTextString(str);
	
}

//����ʼ���棺 
void DrawMenu() 
{
	static char * menuListStart[] = {"Start", "Quick Start  | Ctrl-Q", "Exit   | Ctrl-E"};
	static char * menuListDifficulty[] = {"Difficulty",	"Easy | Ctrl-O", "Medium | Ctrl-M", "Hard | Ctrl-H"};
	static char * menuListHelp[] = {"Help", "Instruction  | Ctrl-I"};
	static char * selectedLabel = NULL;
	
	double fH = GetFontHeight();
	double h = fH*2; 
	double x = WindowWidth/2.8;  
	double y = WindowHeight/2-2*h; 
	double w = WindowWidth/5; 
	double wlist = TextStringWidth(menuListDifficulty[3])*1.2;
	double xindent = WindowHeight/20;
	int selection;
	
	setMenuColors("Soft Yellow", "Brown", "Soft Yellow", "Soft Orange", 1);
	
//Start�� 
	selection = menuList(GenUIID(0), x - 1.75, y + 3.85, w, wlist, h, menuListStart, sizeof(menuListStart)/sizeof(menuListStart[0]));
	if( selection>0 ) selectedLabel = menuListStart[selection];
	if( selection==1 ){
		DisplayClear();
		IsGameOn=TRUE;
		level=Easy;
	}else if(selection == 2){
		exit(-1);
	}
	
//Difficulty�� 
	selection = menuList(GenUIID(0),x - 1.74 + w,  y + 3.85, w, wlist,h, menuListDifficulty,sizeof(menuListDifficulty)/sizeof(menuListDifficulty[0]));
	if( selection>0 ) selectedLabel = menuListDifficulty[selection];
	if( selection==1 ){
		DisplayClear();
		IsGameOn=TRUE;
		level=Easy;
	}else if(selection==2){
		DisplayClear();
		IsGameOn=TRUE;
		level=Medium; 
	}else if(selection==3){
		DisplayClear();
		IsGameOn=TRUE;
		level=Hard;
	}	
		
//Help�� 
	selection = menuList(GenUIID(0),x - 0.725 + w,  y + 3.85, w, wlist,h, menuListHelp,sizeof(menuListHelp)/sizeof(menuListHelp[0]));
	if( selection>0 ) selectedLabel = menuListHelp[selection];
	if( selection==1 ){
		IsIntroducrtionOn=TRUE;
	}else if(selection==2){
		exit(-1);
	}
	

	x = WindowWidth / 2.5;  
	y = WindowHeight / 2-2*h; 

//Show "FLAPPY BIRD":
	MovePen(x - 1.175, y + 1.982);
	SetPointSize(44);	
	SetPenColor("Orange");
	DrawTextString("FLAPPY BIRD");
	MovePen(x - 1.185, y + 2.03);
	SetPointSize(42);	
	SetPenColor("Soft Yellow");
	DrawTextString("FLAPPY BIRD");
	
//draw Bird:
	DrawBird(2, x + 0.7, y + 1);
	
	SetPointSize(10);
	setButtonColors("Soft Yellow", "Brown", "Soft Yellow", "Soft Orange", 1);
	
//draw Background:
	DrawBackground();

//select level button:
	if (button(GenUIID(0), x - 0.565, y - 0.6, w*2, h*3/2, show_more_buttons1 ? "Select Level" : "Start"))
		show_more_buttons1 = ! show_more_buttons1;
	
//levels to select:
	if( show_more_buttons1 ) {
		int k;
		k = 1;
		char name[128]; 
		sprintf(name, "Easy", k);
		if (button(GenUIID(k), x - 0.37, y - k*h*2+0.25 - 0.5, w*2 - 0.4, h*3/4, name)){
			DisplayClear();
			IsGameOn=TRUE;
			level=Easy;
		}
		
		k = 2;
		sprintf(name, "Medium", k);
		if	(button(GenUIID(k),  x - 0.37, y - k*h*2+0.5-0.4, w*2 - 0.4, h*3/4, name)){
			DisplayClear();
			IsGameOn=TRUE;
			level=Medium;
		}
		
		k = 3;
		sprintf(name, "Hard", k);
		if	(button(GenUIID(k),  x - 0.37, y - k*h*2+0.75 - 0.3, w*2 - 0.4, h*3/4, name)){
			DisplayClear();
			IsGameOn=TRUE;
			level=Hard;
		}
	}
	
//Exit:
	if( button(GenUIID(0), x + 2.1, y + 0.5, w/3*2, w/3*2, "Exit") ){
		exit(-1);
	}
	
		
	
	
/*
button for settings	
	if (button(GenUIID(0), x/3 - 0.5, y + 2, w/3*2, w/3*2, show_more_buttons2 ? "Setting" : "Setting"))
		show_more_buttons2 = ! show_more_buttons2;
		
//button for bgm, click to on or off, no extra buttons
	if( show_more_buttons2 ) {
		if (button(GenUIID(0), x - 1, y + 2.2,w, h*3/4, show_more_buttons3 ? "Sound On" : "Sound Off"))
		show_more_buttons3 = ! show_more_buttons3;
		
	}
*/

//button to show ranking:
	if( button(GenUIID(0), x/3 - 0.5, y+0.5, w/3*2, w/3*2, "Ranking")) {
		DisplayClear();
		IsRankingOn=TRUE;	
                   }
                   
//Show most recently selected menu ״̬��Ϣ�� 
	SetPenColor("Blue");
	drawLabel(1.1, 6, "Most recently selected menu is:");
	SetPenColor("Red");
	drawLabel(1.1, 5.7, selectedLabel);

} 

//���������棺 
void DrawGameEnd()
{
	double fH = GetFontHeight();
	double h = fH*2; 
	double x = WindowWidth/2.8;  
	double y = WindowHeight/2-2*h; 
	double w = WindowWidth/5;
	int i,j;
	
//draw Background�� 
	DrawBackground();

//show game over�� 
	MovePen(WindowWidth/3 - 0.4, WindowHeight/3*2 + 0.5);
	SetPointSize(35);	
	SetPenColor("RED");
	DrawTextString("GAME OVER");
	
	
//print score�� 
	MovePen(WindowWidth/3 - 0.48, WindowHeight/3*2 - 0.5);
	SetPointSize(28);
	DrawTextString("YOUR SCORE:"); 
	DrawTextString(str);


//Input name�� 
	setTextBoxColors("Dark Gray", "Light Gray", "Dark Gray", "Light Gray", 0);
	static char memo[30]="\0";
	
	SetPointSize(15);
	SetPenColor("BLUE");
	//MovePen(winwidth/16*6.5 - 3, winheight/3*2 - 1.25);
	if(textbox(GenUIID(0),WindowWidth/3 - 0.25, WindowHeight/3*2 - 1.5, w +1.25, h, memo, sizeof(memo)))
	{
	for(i=0;i<=30;i++){
		if(memo[i]=='#'){
			memo[i]='\0';
			strcpy(players[playercode].name,memo);
	        players[playercode].score=score;
	        readfile();
	        InputOver=TRUE;
	        for(j=0;j<=i;j++){
	        	memo[j]='\0';
			}
	        break;
		}
	}
	
	}
	
	SetPointSize(10);
	SetPenColor("BLACK"); //See if we wanna change a color
	
//Restart:
	if (button(GenUIID(0), x - 0.245, y - 0.5, w+1, h + 0.05, "Restart")){
		IsGameOn=FALSE;  //����������ʼ�� 
		IsGameOver=FALSE;
		IsIntroducrtionOn=FALSE;
	    IsRankingOn=FALSE;
        InputOver=FALSE;
        
		show_more_buttons1 = ! show_more_buttons1;
		score=0;         //����������ʼ�� 
		by=3.5;
		v=0.0,a=0.022;
		Pipe_1.cx=5.0;
        srand(time(0));
        double d=(double) (rand()%10);
	    Pipe_1.cy=d/10+rand()%2+2.4;
	    if(Pipe_3.cy>=4.4) Pipe_3.cy-=0.5;
        Pipe_2.cx=7.4;
        Pipe_2.cy=2;
        Pipe_3.cx=9.8;
        Pipe_3.cy=4;


	}

//Exit:
	if( button(GenUIID(0), x + 0.85, y - 1, w/2 + 0.4, h , "Exit") )
		exit(-1);
	
//Ranking:
	if( button(GenUIID(0), x - 0.245, y - 1, w/2 + 0.4, h, "Ranking") ){
	DisplayClear();
	IsRankingOn=TRUE;
    }

 }


