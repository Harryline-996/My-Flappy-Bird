/*此头文件声明事件处理中需要用到的函数*/

//回调函数声明： 
void KeyboardEventProcess(int key, int event);
void MouseEventProcess(int x, int y, int button, int event);
void TimerEventProcess(int timerID);
void CharEventProcess(char c);

void DisplayClear(void);    //清屏函数
void startTimer(int id, int timeinterval);   //计时器启动函数

