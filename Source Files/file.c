#include "library.h"
#include "draw.h"
#include "definitions.h"

void readfile();                  //读取文件内容，并将其加入链表中等待排序 
void sortlinkedlist();            //对链表内容进行排序
void putfile();                   //将链表内容存储到文件中 
void initfile();                  //清空文件内容 

extern Player players[1000];
extern int playercode;
struct Toptenplayer *head, *end;

void readfile() {

	FILE *fp;                      //定义文件指针 
	char s[20][30];                //定义读取文件信息后作为容器的数组 
	int i, j;                      //定义循环变量 


	head = (struct Toptenplayer *)malloc(sizeof(struct Toptenplayer));
	head->next = NULL;
	end = head;                    //创建一个空链表
	



    if((fp = fopen("ranking.txt", "r"))==NULL)     //打开文本文件 
	{
	 printf("File open error!\n");
	 exit(0);
    }
    
	for (i = 0; i < 20; i++)                       //连续读取10个玩家的信息保存到数组中 
	{
		fgets(s[i], 30, fp);
		if (!strcmp(s[i], "*"))                    //读到'*'时结束读取 
			break;
	}

	for (j = 0; j < i; j += 2)                     //将读取到的玩家信息加入到之前创建的链表中 
	{
		struct Toptenplayer *temp;
		temp = (struct Toptenplayer *)malloc(sizeof(struct Toptenplayer));
		strcpy((temp->name), s[j]);
		temp->score = atoi(s[j + 1]);              //字符转换成整数 
		end->next = temp;
		end = temp;

	}

	head = head->next;
	end->next = NULL;

	if(fclose(fp)){                                //结束存取，关闭文件 
		printf("Can not close the file!\n");
		exit(0); 
	}


	                                               //文本文件中没有储存玩家信息的情况 
	if (i == 0) {                                 
		head = (struct Toptenplayer *)malloc(sizeof(struct Toptenplayer));
		head->next = NULL;
		strcpy((head->name), players[playercode].name);
		strcat((head->name), "\n");
		head->score = players[playercode].score;
	}
	                                               //文本文件中已有玩家信息的情况 
	else {
	sortlinkedlist();                                    //对读入链表中的信息进行排序 
	}
	putfile();                                     //将链表中排序好的信息重新写入文本文件中保存 
} 

void sortlinkedlist() {

	struct Toptenplayer *cur, *curnext;            //当前节点指针与下一个节点的指针 
	int i;
	cur = head;
	for (i = 0; i < 10; i++) {
		curnext = cur->next;
		if (curnext == NULL) {                      //只有一个玩家记录的情况
			
			if ((cur->score) >= players[playercode].score) {
				struct Toptenplayer *temp;
				temp = (struct Toptenplayer *)malloc(sizeof(struct Toptenplayer));
				temp->next = NULL;
				strcpy((temp->name), players[playercode].name);
				strcat((temp->name), "\n");
				temp->score = players[playercode].score;
				cur->next = temp;
			}
			else {
				                                    //转移头结点 
				struct Toptenplayer *temp;
				temp = (struct Toptenplayer *)malloc(sizeof(struct Toptenplayer));
				temp->next = cur;
				head = temp;
				strcpy((temp->name), players[playercode].name);
				strcat((temp->name), "\n");
				temp->score = players[playercode].score;
			}


			break;
		}

		                                           //有多个玩家记录的情况 
		if (i == 0 && (cur->score) < players[playercode].score) {
			struct Toptenplayer *temp;
			temp = (struct Toptenplayer *)malloc(sizeof(struct Toptenplayer));
			temp->next = cur;
			head = temp;
			strcpy((temp->name), players[playercode].name);
			strcat((temp->name), "\n");
			temp->score = players[playercode].score;
			break;
		}

		if ((cur->score) >= players[playercode].score && (curnext->score) <= players[playercode].score) {
			struct Toptenplayer *temp;
			temp = (struct Toptenplayer *)malloc(sizeof(struct Toptenplayer));
			temp->next = NULL;
			strcpy((temp->name), players[playercode].name);
			strcat((temp->name), "\n");
			temp->score = players[playercode].score;
			temp->next = curnext;
			cur->next = temp;
			break;
		}
		else {
			cur = cur->next;
		}
	}
}

void putfile() {
	FILE *fl;
	struct Toptenplayer *Top;
	char num[10];
	int i, j;
	
	if((fl = fopen("ranking.txt", "w"))==NULL)     //用'w'方式打开,首先清空文件便于重新将新的链表数据写入  
	{
	 printf("File open error!\n");
	 exit(0);
    }
    
	Top = head;

	while ((Top->next != NULL)) {
		fputs(Top->name, fl);
		itoa(Top->score, num, 10);
		fputs(num, fl);
		fputs("\n", fl);
		Top = Top->next;
	}
	fputs(Top->name, fl);
	itoa(Top->score, num, 10);
	fputs(num, fl);

	fputs("\n", fl);
	fputs("*", fl);

    if(fclose(fl)){                                
		printf("Can not close the file!\n");
		exit(0); 
	}

}

void initfile(){
	FILE *f2;
	if((f2 = fopen("ranking.txt", "w"))==NULL)     //用写'w'方式打开并清空文件，达到重置排行榜的目的 
	{
	 printf("File open error!\n");
	 exit(0);
    }
    
	fputs("*", f2);
	
	if(fclose(f2)){                                
		printf("Can not close the file!\n");
		exit(0); 
	}

}
 


