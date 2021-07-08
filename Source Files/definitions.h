/*此头文件定义一些全局用到的宏、变量、结构等*/

#define WindowWidth 5.0      //窗口宽
#define WindowHeight 7.0     //窗口高
#define BlankHeight 1.8      //上下水管之间空档的大小
#define GroundHeight 1.6     //地面高度
#define BlankHeight 1.8      //上下水管之间空档的大小 
#define GroundHeight 1.6     //地面高度
#define Pipe_Speed 0.12 

//定时器ID选择:
#define SHOW_GAME_EASY 1     
#define SHOW_GAME_MEDIUM 2
#define SHOW_GAME_HARD 3
#define SHOW_MENU 4

//翅膀状态: 
#define  WINGUP        1   
#define  WINGMID       2
#define  WINGDOWN      3

//难度:
#define  Easy          1   
#define  Medium        2
#define  Hard          3

static int enable_move_pipe=1;      //允许移动 

//动画间隔时间 (可用于调整游戏难度）:
static int timer_interval_easy=35;  
static int timer_interval_medium=32;
static int timer_interval_hard=25; 
    
static int timer_interval_menu=50;  //开始界面刷新间隔时间（防止界面闪烁） 
static int    show_more_buttons1 = 0; 
static int    show_more_buttons2 = 0; 
static int    show_more_buttons3 = 0; 

typedef struct{  //定义水管结构 
	double cx;
	double cy;
} Pipe;
Pipe Pipe_1, Pipe_2, Pipe_3; 

typedef struct {  //定义玩家结构 
	char name[100];
	int score;
}Player;

struct Toptenplayer {  //构造排行榜上玩家信息的链表 
	char name[100];
	int score;
	struct Toptenplayer *next;
};

