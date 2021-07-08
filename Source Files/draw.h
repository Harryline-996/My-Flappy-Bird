/*此头文件声明一些绘制界面过程中用到的函数*/

void DrawBird(int state, double bx, double by);//画小鸟的函数，其中state为小鸟的状态,bx,by为小鸟的横纵坐标 

void DrawPipe(double PipeLocation, double PipeHeight);//画水管的函数，其中PipeHeight为下水管的上表面y坐标,属于(1.8, 6.8-BlankHeight） 
                                                      //PipeLocation为水管体左边缘x坐标,属于（0，5）
void DrawMenu(void);//画开始界面的函数 

void DrawGameEnd(void);//画结束界面的函数 

void DrawBackground(void);//画背景的函数

void DrawIntroduction(void); //显示使用说明的函数

void DrawScore(void); //实时显示分数的函数 

void DrawRanking(void);//显示排行榜


