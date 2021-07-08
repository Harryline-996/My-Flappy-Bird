/*��ͷ�ļ�����һЩȫ���õ��ĺꡢ�������ṹ��*/

#define WindowWidth 5.0      //���ڿ�
#define WindowHeight 7.0     //���ڸ�
#define BlankHeight 1.8      //����ˮ��֮��յ��Ĵ�С
#define GroundHeight 1.6     //����߶�
#define BlankHeight 1.8      //����ˮ��֮��յ��Ĵ�С 
#define GroundHeight 1.6     //����߶�
#define Pipe_Speed 0.12 

//��ʱ��IDѡ��:
#define SHOW_GAME_EASY 1     
#define SHOW_GAME_MEDIUM 2
#define SHOW_GAME_HARD 3
#define SHOW_MENU 4

//���״̬: 
#define  WINGUP        1   
#define  WINGMID       2
#define  WINGDOWN      3

//�Ѷ�:
#define  Easy          1   
#define  Medium        2
#define  Hard          3

static int enable_move_pipe=1;      //�����ƶ� 

//�������ʱ�� (�����ڵ�����Ϸ�Ѷȣ�:
static int timer_interval_easy=35;  
static int timer_interval_medium=32;
static int timer_interval_hard=25; 
    
static int timer_interval_menu=50;  //��ʼ����ˢ�¼��ʱ�䣨��ֹ������˸�� 
static int    show_more_buttons1 = 0; 
static int    show_more_buttons2 = 0; 
static int    show_more_buttons3 = 0; 

typedef struct{  //����ˮ�ܽṹ 
	double cx;
	double cy;
} Pipe;
Pipe Pipe_1, Pipe_2, Pipe_3; 

typedef struct {  //������ҽṹ 
	char name[100];
	int score;
}Player;

struct Toptenplayer {  //�������а��������Ϣ������ 
	char name[100];
	int score;
	struct Toptenplayer *next;
};

