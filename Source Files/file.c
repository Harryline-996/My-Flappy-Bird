#include "library.h"
#include "draw.h"
#include "definitions.h"

void readfile();                  //��ȡ�ļ����ݣ���������������еȴ����� 
void sortlinkedlist();            //���������ݽ�������
void putfile();                   //���������ݴ洢���ļ��� 
void initfile();                  //����ļ����� 

extern Player players[1000];
extern int playercode;
struct Toptenplayer *head, *end;

void readfile() {

	FILE *fp;                      //�����ļ�ָ�� 
	char s[20][30];                //�����ȡ�ļ���Ϣ����Ϊ���������� 
	int i, j;                      //����ѭ������ 


	head = (struct Toptenplayer *)malloc(sizeof(struct Toptenplayer));
	head->next = NULL;
	end = head;                    //����һ��������
	



    if((fp = fopen("ranking.txt", "r"))==NULL)     //���ı��ļ� 
	{
	 printf("File open error!\n");
	 exit(0);
    }
    
	for (i = 0; i < 20; i++)                       //������ȡ10����ҵ���Ϣ���浽������ 
	{
		fgets(s[i], 30, fp);
		if (!strcmp(s[i], "*"))                    //����'*'ʱ������ȡ 
			break;
	}

	for (j = 0; j < i; j += 2)                     //����ȡ���������Ϣ���뵽֮ǰ������������ 
	{
		struct Toptenplayer *temp;
		temp = (struct Toptenplayer *)malloc(sizeof(struct Toptenplayer));
		strcpy((temp->name), s[j]);
		temp->score = atoi(s[j + 1]);              //�ַ�ת�������� 
		end->next = temp;
		end = temp;

	}

	head = head->next;
	end->next = NULL;

	if(fclose(fp)){                                //������ȡ���ر��ļ� 
		printf("Can not close the file!\n");
		exit(0); 
	}


	                                               //�ı��ļ���û�д��������Ϣ����� 
	if (i == 0) {                                 
		head = (struct Toptenplayer *)malloc(sizeof(struct Toptenplayer));
		head->next = NULL;
		strcpy((head->name), players[playercode].name);
		strcat((head->name), "\n");
		head->score = players[playercode].score;
	}
	                                               //�ı��ļ������������Ϣ����� 
	else {
	sortlinkedlist();                                    //�Զ��������е���Ϣ�������� 
	}
	putfile();                                     //������������õ���Ϣ����д���ı��ļ��б��� 
} 

void sortlinkedlist() {

	struct Toptenplayer *cur, *curnext;            //��ǰ�ڵ�ָ������һ���ڵ��ָ�� 
	int i;
	cur = head;
	for (i = 0; i < 10; i++) {
		curnext = cur->next;
		if (curnext == NULL) {                      //ֻ��һ����Ҽ�¼�����
			
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
				                                    //ת��ͷ��� 
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

		                                           //�ж����Ҽ�¼����� 
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
	
	if((fl = fopen("ranking.txt", "w"))==NULL)     //��'w'��ʽ��,��������ļ��������½��µ���������д��  
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
	if((f2 = fopen("ranking.txt", "w"))==NULL)     //��д'w'��ʽ�򿪲�����ļ����ﵽ�������а��Ŀ�� 
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
 


