/*3�����Թ���Ϸ
����ʼ����ʱ��ʾһ���Թ���ͼ���Թ�������һֻ�����Թ������·���һ�����֡���Ϸ��������ʹ�ü����ϵķ�������������ڹ涨��ʱ�����ߵ����ִ���
Ҫ��1) ��������ɱ��ϣ����ü��̲����������������ƶ���
2) �Թ���ǽ�㹻��ʵ�������ܴ�ǽ������
3) ��ȷ��������������ڹ涨ʱ�����ߵ����ִ�����ʾ�ɹ���������ʾʧ�ܣ�
4) ��ӱ༭�Թ����ܣ����޸ĵ�ǰ�Թ����޸����ݣ�ǽ��·��·��ǽ��
5) �ҳ��߳��Թ�������·�����Լ����·�����������л�����ʵ���Թ���ͼ�ļ��Ĵ��̺Ͷ����ȹ��ܡ�
*/
#include"graphics.h"
#include"windows.h"
#include"conio.h"
#include"stdlib.h"
#include"stdio.h"
#define  UP 0x48//��
#define  DOWN 0x50//��
#define  LEFT 0x4b//��
#define  RIGHT 0x4d//��
#define  ESC   0x1b//ESC
#define  STACK_INT_SIZE  100
#define  STACKINCREMENT   10
#define  TURE   1
#define  FALSE  0
#define  OK     1
#define  OVERFLOW  -1
struct xydata{//�����Թ����ݵĽṹ��
int mx;
int my;
struct xydata *next;
};

typedef struct{//���浱ǰ����
int x;
int y;
}PosType;

typedef struct{//ջ��Ԫ������
	int ord;
	PosType seat;
	int di;
}SElemType;

typedef struct{//ջ�Ľṹ

	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

SqStack S;//ջS

struct xydata  *head1,*head2,*head3,*head4,*personal1,*personal2;//�ĸ�Ĭ�Ϲؿ��������Զ���ؿ�
IMAGE img;
int visit[20][15];
void pageshow_();//���ڽ�����ʾ�ĺ���
void Choice();//ѡ�񴳹صĺ���
void ChangeMaze();//ѡ���޸��Թ��ĺ���
void Choicepage();//ѡ�񴳹صĺ����� ����
void Quitgame();//�˳���Ϸ��غ���
void Quitgame_();//�˳���Ϸ��غ���
int  colorflag;//��ɫ��־
int  timeflag;//ʱ���־
void MazePath();	
void MazePathShow();
void MissonOnemap();
void pageshow();
void hide(void)
{
	HWND hwnd;
	hwnd=FindWindow("ConsoleWindowClass",NULL);
	if(hwnd)
	{
		ShowOwnedPopups(hwnd,SW_HIDE);
		ShowWindow(hwnd,SW_HIDE);
	}
}
void SaveFile()//�����ݴ����ļ��ĺ���
{
	FILE *fp1;
			fp1 = (fopen("link_list1","wb"));//�Զ����Ʊ����ļ�
			if(fp1 == NULL)
			{
				cleardevice();
				pageshow();
			}
			while(head1)
			{
				if(fwrite(head1,sizeof(struct xydata)+1,1,fp1) != 1)
				{
					printf("file write wrong!\n");
				}
				head1 = head1 -> next;
			}
			fclose(fp1);
	return ;
}
void SaveFiletwo()
{
	FILE *fp2;
			fp2 = (fopen("link_list2","wb"));//�Զ����Ʊ����ļ�
			if(fp2 == NULL)
			{
				cleardevice();
				pageshow();
			}
			while(head2)
			{
				if(fwrite(head2,sizeof(struct xydata)+1,1,fp2) != 1)
				{
					printf("file write wrong!\n");
				}
				head2 = head2 -> next;
			}
			fclose(fp2);
	return ;
}
void SaveFilethree()
{
FILE *fp3;
			fp3 = (fopen("link_list3","wb"));//�Զ����Ʊ����ļ�
			if(fp3 == NULL)
			{
				cleardevice();
				pageshow();
			}
			while(head3)
			{
				if(fwrite(head3,sizeof(struct xydata)+1,1,fp3) != 1)
				{
					printf("file write wrong!\n");
				}
				head3 = head3 -> next;
			}
			fclose(fp3);
	
	return ;
}
void SaveFilefour()
{
FILE *fp4;
			fp4 = (fopen("link_list4","wb"));//�Զ����Ʊ����ļ�
			if(fp4==NULL)
			{
				cleardevice();
				pageshow();
			}
			while(head4)
			{
				if(fwrite(head4,sizeof(struct xydata)+1,1,fp4)!= 1)
				{
					printf("file write wrong!\n");
				}
				head4 = head4 -> next;
			}
			fclose(fp4);
		

	
	return ;
}
void SaveFilePersonalOne()
{
FILE *fp5;

	
	
		
			fp5 = (fopen("link_list5","wb"));//�Զ����Ʊ����ļ�
			if(fp5 == NULL)
			{
				cleardevice();
				pageshow();
			}
			while(personal1)
			{
				if(fwrite(personal1,sizeof(struct xydata)+1,1,fp5) != 1)
				{
					printf("file write wrong!\n");
				}
				personal1 = personal1 -> next;
			}
			fclose(fp5);
	return ;
}
void SaveFilePersonalTwo()
{
FILE *fp6;
			fp6 = (fopen("link_list6","wb"));//�Զ����Ʊ����ļ�
			if(fp6 == NULL)
			{
				cleardevice();
				pageshow();
			}
			while(personal2)
			{
				if(fwrite(personal2,sizeof(struct xydata)+1,1,fp6) != 1)
				{
					printf("file write wrong!\n");
				}
				personal2 = personal2 -> next;
			}
			fclose(fp6);
	return ;
}
void SaveData()//���Թ����ݴ�����������
{
	
	float mx,my;
	struct xydata *p1,*p2;
	for(mx = 38;mx <= 722;mx += 36)
		for(my = 38;my <= 542;my += 36)
		{
			if(getpixel(mx,my) == RGB(254,255,255))
			{
				p1 = (struct xydata*)malloc(sizeof(struct xydata));
				p1 -> mx = mx;
				p1 -> my = my;
				p2 = head1;
				head1 = p1;
				p1 -> next = p2;
			}
		}
		SaveFile();
		return ;
}
void SaveDatatwo()
{
	float mx,my;
	struct xydata *p1,*p2;
	for(mx = 38;mx <= 722;mx += 36)
		for(my = 38;my <= 542;my += 36)
		{
			if(getpixel(mx,my) == RGB(254,255,255))
			{
			p1=(struct xydata*)malloc(sizeof(struct xydata));
				p1 -> mx = mx;
				p1 -> my = my;
				p2 = head2;
				head2 = p1;
				p1 -> next = p2;
			}
		}
		SaveFiletwo();
		return ;
}
void SaveDatathree()
{
	float mx,my;
	struct xydata *p1,*p2;     
	for(mx = 38;mx <= 722;mx += 36)
		for(my = 38;my <= 542;my += 36)
		{
			if(getpixel(mx,my) == RGB(254,255,255))
			{
				p1=(struct xydata*)malloc(sizeof(struct xydata));
				p1 -> mx = mx;
				p1 -> my = my;
				p2 = head3;
				head3 = p1;
				p1 -> next = p2;
			}
		}
		SaveFilethree();
		return ;
}
void SaveDatafour()
{
	float mx,my;
	struct xydata *p1,*p2;
	for(mx = 38;mx <= 722;mx += 36)
		for(my = 38;my <= 542;my += 36)
		{
			if(getpixel(mx,my) == RGB(254,255,255))
			{
				p1 = (struct xydata*)malloc(sizeof(struct xydata));
				p1 -> mx = mx;
				p1 -> my = my;
				p2 = head4;
				head4 = p1;
				p1 -> next = p2;
			}
		}
		SaveFilefour();
		return ;
}
void SaveDataPersonalOne()
{
	float mx,my;
	struct xydata *p1,*p2;
	for(mx = 38;mx <= 722;mx += 36)
		for(my = 38;my <= 542;my += 36)
		{
			if(getpixel(mx,my)==RGB(254,255,255))
			{
				p1 = (struct xydata*)malloc(sizeof(struct xydata));
				p1 -> mx = mx;
				p1 -> my = my;
				p2 = personal1;
				personal1 = p1;
				p1 -> next = p2;
			}
		}
		SaveFilePersonalOne();
		return ;
}
void SaveDataPersonalTwo()
{
float mx,my;
	struct xydata *p1,*p2;
	for(mx = 38;mx <= 722;mx += 36)
		for(my = 38;my <= 542;my += 36)
		{
			if(getpixel(mx,my) == RGB(254,255,255))
			{
				p1 = (struct xydata*)malloc(sizeof(struct xydata));
				p1 -> mx = mx;
				p1 -> my = my;
				p2 = personal2;
				personal2 = p1;
				p1 -> next = p2;
			}
		}
		SaveFilePersonalTwo();
		return ;
}
void Changeone()//�޸ĵ�һ��
{	
	FILE *fp;
	int n=0;
	float mx,my;
	float x,j=220,y,i,ch;
	COLORREF color = WHITE;
	MOUSEMSG m;
	struct xydata *p1,*p2;
	setlinecolor(WHITE);
	outtextxy(800,100,_T("���������ƶ�"));
	//setwritemode(R2_XORPEN);
	for(x = 20;x <= 740;x += 36)
		line(x,20,x,560);
	for(y = 20;y <= 560;y += 36)
		line(20,y,740,y);
	setfillcolor(RGB(254,255,255));
	fillcircle(800,200,50);
	setfillcolor(RED);
	fillcircle(800,300,50);
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("��       ��"));
	rectangle(750,450,850,480);
	outtextxy(760,458,_T("��       ��"));
		fp = (fopen("link_list1","rb"));
		if(fp == NULL)
		{
			goto LOOP;
		}
		while(1)
		{
			p1 = (struct xydata*)malloc(sizeof(struct xydata));
			fread(p1,sizeof(struct xydata)+1,1,fp);
			p2 = head1;
			head1 = p1;
			p1 -> next = p2;
			if(feof(fp))
				break;
		}
		head1 = head1 -> next;
		fclose(fp);
		setfillcolor(RGB(254,255,255));
	while(head1)
	
	{
		floodfill(head1 -> mx,head1 -> my,color);
		head1 = head1 -> next;
	}
	LOOP:while(1)
	{
		m = GetMouseMsg();
		switch(m.uMsg)
		{
			case WM_LBUTTONDOWN:
				
				if(m.y > 150&&m.y < 250&&m.x > 750&&m.x < 850)
				{//�ð���ɫͿɫ
					setfillcolor(RGB(254,255,255));
					colorflag = 1;
				}
				else
				if(m.y > 250 && m.y < 350 && m.x > 750 && m.x < 850)
				{//�ú���ɫͿɫ
				setfillcolor(RED);
				colorflag = 2;
				}
				else 
					if(m.x > 750&&m.x < 850&&m.y > 450&&m.y < 480)//����
						SaveData();
				else
					if(m.x > 750&&m.x < 850&&m.y > 400&&m.y < 430)//750,450,850,480����
						{
							cleardevice();
							Choicepage();
							ChangeMaze();	
						}
				else 
					if(getpixel(m.x,m.y) == RGB(254,255,255) || getpixel(m.x,m.y) == RED)//Ϳɫ
				{
					setfillcolor(BLACK);
					floodfill(m.x,m.y,color);
				}
				else
				{
					if(colorflag == 1)//�ð�ɫ��Ϳ
					{
						setfillcolor(RGB(254,255,255));
						floodfill(m.x,m.y,color);
					}
				else
					if(colorflag == 2)//�ú�ɫ��Ϳ
						{
							setfillcolor(RED);
							floodfill(m.x,m.y,color);
						}
				}
				break;
		case WM_RBUTTONDBLCLK:
			return;
		}
	}	
}
void Changetwo()
{
FILE *fp2;

	int n = 0;
	float mx,my;
	float x,j = 220,y,i,ch;
	COLORREF color = WHITE;
	MOUSEMSG m;
	struct xydata *p1,*p2;
	setlinecolor(WHITE);
	outtextxy(800,100,_T("���������ƶ�"));
	//setwritemode(R2_XORPEN);
	for(x = 20;x <= 740;x += 36)
		line(x,20,x,560);
	for(y = 20;y <= 560;y += 36)
		line(20,y,740,y);
	setfillcolor(RGB(254,255,255));
	fillcircle(800,200,50);
	setfillcolor(RED);
	fillcircle(800,300,50);
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("��       ��"));
	rectangle(750,450,850,480);
	outtextxy(760,458,_T("��       ��"));
		fp2 = (fopen("link_list2","rb"));
		if(fp2 == NULL)
		{
			goto LOOP;
		}
		while(1)
		{
			p1 = (struct xydata*)malloc(sizeof(struct xydata));
			fread(p1,sizeof(struct xydata)+1,1,fp2);
			p2 = head2;
			head2 = p1;
			p1->next = p2;
			if(feof(fp2))
				break;
		}
		head2 = head2 -> next;
		fclose(fp2);
		setfillcolor(RGB(254,255,255));
	while(head2)
	
	{
		floodfill(head2->mx,head2->my,color);
		head2 = head2 -> next;
	}
	LOOP:while(1)
	{
		m = GetMouseMsg();
		switch(m.uMsg)
		{
		case WM_LBUTTONDOWN:
				
			if(m.y > 150 && m.y < 250 && m.x > 750 && m.x < 850)
			{//�ð���ɫͿɫ
				setfillcolor(RGB(254,255,255));
				colorflag = 1;
			}
			else
				if(m.y>250 && m.y<350 && m.x > 750 && m.x < 850)
				{//�ú���ɫͿɫ
					setfillcolor(RED);
					colorflag = 2;
				}
				else 
					if(m.x > 750 && m.x < 850 && m.y > 450 && m.y < 480)//����
						SaveDatatwo();
				else
					if( m.x > 750 && m.x < 850 && m.y > 400 && m.y < 430)//750,450,850,480����
					{
						cleardevice();
						Choicepage();
						ChangeMaze();	
					}
				else 
					if(getpixel(m.x,m.y) == RGB(254,255,255) || getpixel(m.x,m.y) == RED)//Ϳɫ
					{
						setfillcolor(BLACK);
						floodfill(m.x,m.y,color);
					}
				else
					if(colorflag == 1)
					{
						setfillcolor(RGB(254,255,255));
						floodfill(m.x,m.y,color);
					}
				else
					if(colorflag == 2)
					{
						setfillcolor(RED);
						floodfill(m.x,m.y,color);
					}
				break;
		case WM_RBUTTONDBLCLK:
			return;
		} 
	}
}
void Changethree()
{
	FILE *fp3;
	int n = 0;
	float mx,my;
	float x,j = 220,y,i,ch;
	COLORREF color = WHITE;
	MOUSEMSG m;
	struct xydata *p1,*p2;
	setlinecolor(WHITE);
	outtextxy(800,100,_T("���������ƶ�"));
	//setwritemode(R2_XORPEN);
	for(x = 20;x <= 740;x += 36)
		line(x,20,x,560);
	for(y = 20;y <= 560;y += 36)
		line(20,y,740,y);
		setfillcolor(RGB(254,255,255));
		fillcircle(800,200,50);
		setfillcolor(RED);
		fillcircle(800,300,50);
		rectangle(750,400,850,430);
		outtextxy(760,408,_T("��       ��"));
		rectangle(750,450,850,480);
		outtextxy(760,458,_T("��       ��"));
		fp3 = (fopen("link_list3","rb"));
		if(fp3 == NULL)
		{
			goto LOOP;
		}
		while(1)
		{
			p1 = (struct xydata*)malloc(sizeof(struct xydata));
			fread(p1,sizeof(struct xydata)+1,1,fp3);
			p2 = head3;
			head3 = p1;
			p1 -> next = p2;
			if(feof(fp3))
				break;
		}
		head3 = head3 -> next;
		fclose(fp3);
		setfillcolor(RGB(254,255,255));
	while(head3)
	
	{
		floodfill(head3 -> mx,head3 -> my,color);
		head3  = head3 -> next;
	}
	LOOP:while(1)
	{
		m=GetMouseMsg();
		switch(m.uMsg)
		{
		case WM_LBUTTONDOWN:	
			if(m.y > 150 && m.y<250&&m.x > 750 && m.x < 850)
			{//�ð���ɫͿɫ
				setfillcolor(RGB(254,255,255));
				colorflag=1;
			}
			else
				if(m.y > 250 && m.y  < 350 && m.x > 750 && m.x < 850)
				{//�ú���ɫͿɫ
					setfillcolor(RED);
					colorflag=2;
				}
			else 
				if(m.x > 750 && m.x < 850 && m.y > 450 && m.y < 480)//����
					SaveDatathree();
			else
				if(m.x > 750 && m.x < 850 && m.y > 400 && m.y < 430)//750,450,850,480����
				{
					cleardevice();
					Choicepage();
					ChangeMaze();
				}
			else 
				if(getpixel(m.x,m.y) == RGB(254,255,255) || getpixel(m.x,m.y) == RED)//Ϳɫ
				{
					setfillcolor(BLACK);
					floodfill(m.x,m.y,color);
				}
			else
				if(colorflag == 1)
				{
					setfillcolor(RGB(254,255,255));
					floodfill(m.x,m.y,color);
				}
			else
				if(colorflag == 2)
				{
					setfillcolor(RED);
					floodfill(m.x,m.y,color);
				}
				break;
		case WM_RBUTTONDBLCLK:
			return;
			
		}
	}
}
void Changefour()
{
	FILE *fp4;
	int n = 0;
	float mx,my;
	float x,j = 220,y,i,ch;
	COLORREF color = WHITE;
	MOUSEMSG m;
	struct xydata *p1,*p2;
	setlinecolor(WHITE);
	outtextxy(800,100,_T("���������ƶ�"));
	//setwritemode(R2_XORPEN);
	for(x=20;x<=740;x+=36)
		line(x,20,x,560);
	for(y=20;y<=560;y+=36)
		line(20,y,740,y);
	setfillcolor(RGB(254,255,255));
	fillcircle(800,200,50);
	setfillcolor(RED);
	fillcircle(800,300,50);
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("��       ��"));
	rectangle(750,450,850,480);
	outtextxy(760,458,_T("��       ��"));
		fp4 = (fopen("link_list4","rb"));
		if(fp4 == NULL)
		{
			goto LOOP;
		}
		while(1)
		{
			p1 = (struct xydata*)malloc(sizeof(struct xydata));
			fread(p1,sizeof(struct xydata)+1,1,fp4);
			p2 = head4;
			head4 = p1;
			p1 -> next = p2;
			if(feof(fp4))
				break;
		}
		head4 = head4 -> next;
		fclose(fp4);
		setfillcolor(RGB(254,255,255));
	while(head4)
	
	{
		floodfill(head4 -> mx,head4 -> my,color);
		head4 = head4 -> next;
	}
	LOOP:while(1)
	{
		m = GetMouseMsg();
		switch(m.uMsg)
		{
			case WM_LBUTTONDOWN:
				if(m.y > 150 && m.y < 250 && m.x > 750 && m.x < 850)
				{//�ð���ɫͿɫ
					setfillcolor(RGB(254,255,255));
					colorflag = 1;
				}
				else
					if(m.y > 250 && m.y < 350 && m.x > 750 && m.x < 850)
					{//�ú���ɫͿɫ
					setfillcolor(RED);
					colorflag = 2;
					}
				else 
					if(m.x > 750 && m.x < 850 && m.y > 450 && m.y < 480)//����
						SaveDatafour();
				else
					if(m.x > 750 && m.x < 850 && m.y > 400 && m.y < 430)//750,450,850,480����
					{
						cleardevice();
						Choicepage();
						ChangeMaze();		
					}
				else 
					if(getpixel(m.x,m.y) == RGB(254,255,255) || getpixel(m.x,m.y) == RED)//Ϳɫ
					{
						setfillcolor(BLACK);
						floodfill(m.x,m.y,color);
					}
				else
				{
					if(colorflag == 1)
					{
						setfillcolor(RGB(254,255,255));
						floodfill(m.x,m.y,color);
					}
					else
						if(colorflag == 2)
						{
							setfillcolor(RED);
							floodfill(m.x,m.y,color);
						}
				}

				break;
		case WM_RBUTTONDBLCLK:
			return;
		}
	}
}
void ChangePensonalOne()
{
FILE *fp5;
	int n = 0;
	float mx,my;
float x,j=220,y,i,ch;
	COLORREF color = WHITE;
	MOUSEMSG m;
	struct xydata *p1,*p2;
	setlinecolor(WHITE);
	outtextxy(800,100,_T("���������ƶ�"));
	//setwritemode(R2_XORPEN);
	for(x=20;x<=740;x+=36)
		line(x,20,x,560);
	for(y=20;y<=560;y+=36)
		line(20,y,740,y);
	setfillcolor(RGB(254,255,255));
	fillcircle(800,200,50);
	setfillcolor(RED);
	fillcircle(800,300,50);
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("��       ��"));
	rectangle(750,450,850,480);
	outtextxy(760,458,_T("��       ��"));
		fp5 = (fopen("link_list5","rb"));
		if(fp5 == NULL)
		{
			goto LOOP;
		}
		while(1)
		{
			p1 = (struct xydata*)malloc(sizeof(struct xydata));
			fread(p1,sizeof(struct xydata)+1,1,fp5);
			p2 = personal1;
			personal1 = p1;
			p1 -> next = p2;
			if(feof(fp5))
				break;
		}
		personal1 = personal1 -> next;
		fclose(fp5);
	setfillcolor(RGB(254,255,255));
	while(personal1)
	
	{
		floodfill(personal1 -> mx,personal1 -> my,color);
		personal1 = personal1 -> next;
	}
LOOP:while(1)
{
	m = GetMouseMsg();
	switch(m.uMsg)
	{
	case WM_LBUTTONDOWN:
			
		if(m.y > 150 && m.y < 250 && m.x > 750 && m.x < 850)
		{//�ð���ɫͿɫ
			setfillcolor(RGB(254,255,255));
			colorflag = 1;
		}
		else
			if(m.y > 250 && m.y < 350 && m.x > 750 && m.x < 850)
			{//�ú���ɫͿɫ
			setfillcolor(RED);
			colorflag = 2;
			}
			else 
				if(m.x > 750 && m.x < 850 && m.y > 450 && m.y < 480)//����
					SaveDataPersonalOne();
				else
					if(m.x > 750 && m.x < 850 && m.y > 400 && m.y < 430)//750,450,850,480����
					{
						cleardevice();
						Choicepage();
						ChangeMaze();
					}
			else if(getpixel(m.x,m.y) == RGB(254,255,255) || getpixel(m.x,m.y) == RED)//Ϳɫ
			{
				setfillcolor(BLACK);//�����ǰ��ɫ�Ǻ�ɫ������ѡ��ɫ��Ϳ������Ǻ�ɫ���ú�ɫ��Ϳ
				floodfill(m.x,m.y,color);
			}
			else
			{
				if(colorflag==1)//���colorflag==1���ð�ɫ��Ϳ
				{
					setfillcolor(RGB(254,255,255));
					floodfill(m.x,m.y,color);
				}
				else
					if(colorflag==2)//���colorflag==2���ú�ɫ��Ϳ
					{
						setfillcolor(RED);
						floodfill(m.x,m.y,color);
					}
			}
			break;
	case WM_RBUTTONDBLCLK:
		return;
		}
	}
}
void ChangePensonalTwo()
{
FILE *fp6;
	int n = 0;
	float mx,my;
float x,j = 220,y,i,ch;
	COLORREF color = WHITE;
	MOUSEMSG m;
	struct xydata *p1,*p2;
	setlinecolor(WHITE);
	outtextxy(800,100,_T("���������ƶ�"));
	//setwritemode(R2_XORPEN);
	for(x = 20;x <= 740;x += 36)
		line(x,20,x,560);
	for(y = 20;y <= 560;y += 36)
		line(20,y,740,y);
		setfillcolor(RGB(254,255,255));
		fillcircle(800,200,50);
		setfillcolor(RED);
		fillcircle(800,300,50);
		rectangle(750,400,850,430);
		outtextxy(760,408,_T("��       ��"));
		rectangle(750,450,850,480);
		outtextxy(760,458,_T("��       ��"));
		fp6=(fopen("link_list6","rb"));
		if(fp6 == NULL)
		{
			goto LOOP;
		}
		while(1)
		{
			p1 = (struct xydata*)malloc(sizeof(struct xydata));
			fread(p1,sizeof(struct xydata)+1,1,fp6);
			p2 = personal2;
			personal2 = p1;
			p1 -> next = p2;
			if(feof(fp6))
				break;
		}
		personal2 = personal2 -> next;
		fclose(fp6);
	setfillcolor(RGB(254,255,255));
	while(personal2)
	
	{
		floodfill(personal2 ->  mx,personal2 -> my,color);
		personal2 = personal2 -> next;
	}
LOOP:while(1)
{
	m = GetMouseMsg();
	switch(m.uMsg)
	{
	case WM_LBUTTONDOWN:
			
		if(m.y > 150 && m.y < 250 && m.x > 750 && m.x < 850)
		{//�ð���ɫͿɫ
			setfillcolor(RGB(254,255,255));
			colorflag = 1;
		}
		else
			if(m.y > 250 && m.y < 350 && m.x > 750 && m.x < 850)
			{//�ú���ɫͿɫ
			setfillcolor(RED);
			colorflag = 2;
			}
			else 
				if(m.x > 750 && m.x < 850 && m.y > 450 && m.y < 480)//����
					SaveDataPersonalTwo();
				else
					if(m.x>750&&m.x<850&&m.y>400&&m.y<430)//750,450,850,480����
					{
						cleardevice();
						Choicepage();
						ChangeMaze();
					}
			else if(getpixel(m.x,m.y) == RGB(254,255,255) || getpixel(m.x,m.y) == RED)//Ϳɫ
			{
				setfillcolor(BLACK);
				floodfill(m.x,m.y,color);
			}
			else
			{
				if(colorflag == 1)
				{
					setfillcolor(RGB(254,255,255));
					floodfill(m.x,m.y,color);
				}
				else
					if(colorflag == 2)
					{
						setfillcolor(RED);
						floodfill(m.x,m.y,color);
					}
			}

			break;
	case WM_RBUTTONDBLCLK:
		return;
		}
	}
}
void Choicepage()//ѡ�񴳹عؿ��Ľ��溯��
{
	float mx,my;
	float x,j = 220,y,i;
	COLORREF color = WHITE;
	setlinecolor(WHITE);
	line(0,580,200,380);
	for(x = 36;x <= 1080;x += 36)
		line(x,580,x+200,380);
	for(y = 380;y <= 580;y += 20)
		line(j-=20,y,1080,y);
	line(200,380,1080,380);
	y = -20;
	for(x = 0;x <= 200;x += 20)
		line(x,0,x,580-(y+=20));
	line(200,0,200,380);
	for(y = 0;y < 570;y += 25)
		line(0,y,200,y-200);
	for(x = 200;x <= 1080;x += 36)
		line(x,0,x,380);
	for(y = 0;y <= 370;y += 25)
		line(200,y,1080,y);
	setfillcolor(RGB(254,255,255));
	for(mx = 330,my = 590;my > 480;my -= 40,mx += 40)
	{
		floodfill(mx,my,color);
	}
	for(;mx > 100;mx -= 72)
	{
		floodfill(mx,my,color);
	}
	for(mx += 25,my -= 15;my  > 175;my -= 50)
	{
		floodfill(mx,my,color);
	}
	for(;mx <= 200;mx += 40,my -= 40)
	{
		floodfill(mx,my,color);
	}
	for(my += 25,mx += 10;mx < 880;mx += 72)
	{
		floodfill(mx,my,color);
	}
	for(;my < 380;my += 50)
	{
		floodfill(mx,my,color);
	}
	for(mx -= 20;my <= 460;my += 40,mx -= 40)
	{
		floodfill(mx,my,color);
	}
	for(mx -= 20,my -= 20;mx > 550;mx -= 72)
	{
		floodfill(mx,my,color);
	}
	for(mx += 72;my < 580;my += 40,mx -= 40)
	{
		floodfill(mx,my,color);
	}
	setfillcolor(BLACK);
	for(i = 542.5,j = 225;i >= 320,j >= 100;i -= 1.88,j --)
	{
		fillrectangle(i,j,542.5-i+542.5,225-j+225);
		Sleep(1);
	}
}
void ChangeMaze()//ѡ���޸Ĺؿ�
{
	MOUSEMSG m;
		setfillcolor(BLACK);
		fillrectangle(390,130,495,160);
		outtextxy(410,138,_T("��  ��  1"));
		fillrectangle(390,180,495,210);
		outtextxy(410,188,_T("��  ��  2"));
		fillrectangle(390,230,495,260);
		outtextxy(410,238,_T("��  ��  3"));
		fillrectangle(390,280,495,310);
		outtextxy(410,288,_T("��  ��  4"));
		fillrectangle(590,150,695,180);
		outtextxy(603,158,_T("�Զ���ؿ�1"));
		fillrectangle(590,200,695,230);
		outtextxy(603,208,_T("�Զ���ؿ�2"));
		fillrectangle(590,250,695,280);
		outtextxy(623,258,_T("��  ��"));
		while(1)
		{
			m = GetMouseMsg();
			switch(m.uMsg)
			{
			case  WM_LBUTTONDOWN:
								if(m.x > 390 && m.x < 495 && m.y > 130 && m.y < 160)//�ؿ�1
								{
									cleardevice();
									Changeone();
								}
								else
									if(m.x > 390 && m.x < 495 && m.y > 180 && m.y < 210)//�ؿ�2
								{
									cleardevice();
									Changetwo();
								}
								else
									if(m.x > 390 && m.x < 495 && m.y > 230 && m.y < 260)//�޸Ĺؿ�3
								{
									cleardevice();
									Changethree();
								}
								else
									if(m.x > 390 && m.x < 495 && m.y > 280 && m.y < 310)//�޸Ĺؿ�4
								{
									cleardevice();
									Changefour();
								}
								else
									if(m.x > 590 && m.x < 695 && m.y > 150 && m.y < 180)//�޸ĸ��˹ؿ�1
								{
									cleardevice();
									ChangePensonalOne();
								}
								else
									if(m.x > 590 && m.x < 695 && m.y > 200 && m.y < 230)//�޸ĸ��˹ؿ�2
								{
									cleardevice();
									ChangePensonalTwo();
								}
								else
									if(m.x > 590 && m.x < 695 && m.y > 250 && m.y < 280)//����
								{
									cleardevice();
									pageshow_();
								}
								break;
			}
		}
}
void Mission()//��һ��
{
	int x,y,ch;
	char time[10],t=0;
	struct xydata *p1,*p2;
	COLORREF color=WHITE;
	MOUSEMSG	m;
	FILE *fp;
	timeflag=0;
	setlinecolor(WHITE);
	outtextxy(750,100,_T("���������ƶ�  ʱ�����ƣ�20s"));
	outtextxy(750,290,_T("---->����"));
	outtextxy(750,180,_T("��ʼʱ��"));
	outtextxy(850,180,_T("����ʱ��"));
	outtextxy(950,180,_T("��ʱ"));
//	setwritemode(R2_XORPEN);
	for(x=20;x<=740;x+=36)
		line(x,20,x,560);
	for(y=20;y<=560;y+=36)
		line(20,y,740,y);
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("��       ��"));
	rectangle(750,450,850,480);
	outtextxy(760,458,_T("�� �� �� ��"));
		fp = (fopen("link_list1","rb"));
		if(fp == NULL)
		{
			exit(0);
		}
		while(1)
		{
			p1 = (struct xydata*)malloc(sizeof(struct xydata));
			fread(p1,sizeof(struct xydata)+1,1,fp);
			p2 = head1;
			head1 = p1;
			p1 -> next = p2;
			if(feof(fp))
				break;
		}
		head1 = head1 -> next;
		fclose(fp);
	setfillcolor(RGB(254,255,255));
	while(head1)
	
	{
		floodfill(head1 -> mx,head1 -> my,color);
		head1 = head1 -> next;
	}
	setfillcolor(BLACK);
	x = 38;y = 362;//��ʼ��
	fillcircle(x,y,18);
	ch=getch();
	SYSTEMTIME BT,ET;
while(1)
	{
		if(_kbhit())
		{
			
	
			if(ch = 0xe0)
			{
				ch = getch();
				switch(ch)
				{
					
				case UP:
					if(getpixel(x,y-36) == RGB(254,255,255))
					{
						setfillcolor(RGB(254,255,255));fillcircle(x,y,18);y -= 36;setfillcolor(BLACK);fillcircle(x,y,18);}
					else;
						break;
				case DOWN:
					if(getpixel(x,y+36) == RGB(254,255,255))
					{setfillcolor(RGB(254,255,255));fillcircle(x,y,18);y += 36;setfillcolor(BLACK);fillcircle(x,y,18);}
					else
					{;}break;
				case LEFT:
					if(getpixel(x-36,y) == RGB(254,255,255))
					{setfillcolor(RGB(254,255,255));fillcircle(x,y,18);x -= 36;setfillcolor(BLACK);fillcircle(x,y,18);}
					else
					{;	}break;
				case RIGHT:
					if(getpixel(x+36,y) == RGB(254,255,255))
					{setfillcolor(RGB(254,255,255));fillcircle(x,y,18);x += 36;setfillcolor(BLACK);fillcircle(x,y,18);}
					else
					{;}break;
				case ESC:
					goto down;break;


				}
			
			}
		}
		if(x == 74 && y == 362)
		{
			if(timeflag == 0)
			{
				timeflag = 1;
				GetLocalTime(&BT);
				itoa(BT.wHour, time, 10);
				outtextxy(750,210,time);
				itoa(BT.wMinute, time, 10);
				outtextxy(770,210,time);
				itoa(BT.wSecond, time, 10);
				outtextxy(790,210,time);
				outtextxy(767,210,_T(":"));
				outtextxy(787,210,_T(":"));
			}
		}
		if(x == 722 && y == 290)//�յ�
		{
			GetLocalTime(&ET);
			itoa(ET.wHour, time, 10);
			outtextxy(850,210,time);
			itoa(ET.wMinute, time, 10);
			outtextxy(870,210,time);
			itoa(ET.wSecond, time, 10);
			outtextxy(890,210,time);
			outtextxy(867,210,_T(":"));
			outtextxy(887,210,_T(":"));
			itoa((60*(ET.wMinute-BT.wMinute)+ET.wSecond-BT.wSecond), time, 10);
			outtextxy(950,210,time);
			outtextxy(975,210,_T("s"));
			if((60*(ET.wMinute-BT.wMinute)+(ET.wSecond-BT.wSecond)) <= 20)
			{
					outtextxy(835,260,_T("���سɹ�"));
			}
			else
					outtextxy(835,260,_T("����ʧ��"));
			break;
		}
	}
down:while(1)
	 {
		 m = GetMouseMsg();
		 switch(m.uMsg)
		 {
			 case  WM_LBUTTONDOWN://750,400,850,430);
				 if(m.x > 750 && m.x < 850 && m.y > 400 && m.y < 430)
				 {
					cleardevice();
					//putimage(0, 0, &img2);
					Choicepage();
					Choice();
				 }
				 else
					 if(m.x > 750 && m.x < 850 && m.y > 450 && m.y < 480)//750,450,850,480
					 {
						cleardevice();
						Mission();
					 }
		 }
	 }
getch();
	return ;
}
void Missiontwo()
{
	int x,y,ch;
	struct xydata *p1,*p2;
	char time[10],t = 0;
	COLORREF color = WHITE;
	MOUSEMSG	m;
		FILE *fp2;
		timeflag = 0;
	setlinecolor(WHITE);
	outtextxy(750,100,_T("���������ƶ�  ʱ�����ƣ�15s"));
	outtextxy(750,180,_T("��ʼʱ��"));
	outtextxy(850,180,_T("����ʱ��"));
	outtextxy(950,180,_T("��ʱ"));
//	setwritemode(R2_XORPEN);
	for(x=20;x<=740;x+=36)
		line(x,20,x,560);
	for(y=20;y<=560;y+=36)
		line(20,y,740,y);
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("��       ��"));
	rectangle(750,450,850,480);
	outtextxy(760,458,_T("�� �� �� ��"));
		fp2 = (fopen("link_list2","rb"));
		if(fp2 == NULL)
		{
				exit(0);
		}
		while(1)
		{
			p1 = (struct xydata*)malloc(sizeof(struct xydata));
			fread(p1,sizeof(struct xydata)+1,1,fp2);
			p2 = head2;
			head2 = p1;
			p1 -> next = p2;
			if(feof(fp2))
				break;
		}
		head2 = head2 -> next;
		fclose(fp2);
	setfillcolor(RGB(254,255,255));
	while(head2)
	
	{
		floodfill(head2 -> mx,head2 -> my,color);
		head2 = head2 -> next;
	}
	setfillcolor(BLACK);
	x = 146;y = 38;//��������722  542
	outtextxy(752,542,_T("---->����"));
	fillcircle(x,y,18);
	ch = getch();
	SYSTEMTIME BT,ET;
while(1)
	{
		if(_kbhit())
		if(ch = 0xe0)
		{
			ch = getch();
			switch(ch)
			{
				
			case UP:
				if(getpixel(x,y-36) == RGB(254,255,255))
				{
					setfillcolor(RGB(254,255,255));fillcircle(x,y,18);y -= 36;setfillcolor(BLACK);fillcircle(x,y,18);}
				else;
					break;
			case DOWN:
				if(getpixel(x,y+36) == RGB(254,255,255))
				{setfillcolor(RGB(254,255,255));fillcircle(x,y,18);y += 36;setfillcolor(BLACK);fillcircle(x,y,18);}
				else
				{;}break;
			case LEFT:
				if(getpixel(x-36,y) == RGB(254,255,255))
				{setfillcolor(RGB(254,255,255));fillcircle(x,y,18);x -= 36;setfillcolor(BLACK);fillcircle(x,y,18);}
				else
				{;	}break;
			case RIGHT:
				if(getpixel(x+36,y) == RGB(254,255,255))
				{setfillcolor(RGB(254,255,255));fillcircle(x,y,18);x += 36;setfillcolor(BLACK);fillcircle(x,y,18);}
				else
				{;}break;
			case ESC:
				goto downtwo;break;


			}
		}
		if(x == 146&&y == 74)
		{
			if(timeflag == 0)
			{
				timeflag=1;
				GetLocalTime(&BT);
				itoa(BT.wHour, time, 10);
				outtextxy(750,210,time);
				itoa(BT.wMinute, time, 10);
				outtextxy(770,210,time);
				itoa(BT.wSecond, time, 10);
				outtextxy(790,210,time);
				outtextxy(767,210,_T(":"));
				outtextxy(787,210,_T(":"));
			}
		}
		if(x == 722&&y == 542)
		{
			GetLocalTime(&ET);
			itoa(ET.wHour, time, 10);
			outtextxy(850,210,time);
			itoa(ET.wMinute, time, 10);
			outtextxy(870,210,time);
			itoa(ET.wSecond, time, 10);
			outtextxy(890,210,time);
			outtextxy(867,210,_T(":"));
			outtextxy(887,210,_T(":"));
			itoa((60*(ET.wMinute-BT.wMinute)+ET.wSecond-BT.wSecond), time, 10);
			outtextxy(950,210,time);
			outtextxy(970,210,_T("s"));
			if((60*(ET.wMinute-BT.wMinute)+(ET.wSecond-BT.wSecond))<=15)
			{
					outtextxy(835,260,_T("���سɹ�"));
			}
			else
					outtextxy(835,260,_T("����ʧ��"));
			break;
		}
		
	}
downtwo:while(1)
	 {
		 m = GetMouseMsg();
		 switch(m.uMsg)
		 {
			 case  WM_LBUTTONDOWN://750,400,850,430);
				 if(m.x > 750 && m.x < 850 && m.y > 400 && m.y < 430)
				 {
					cleardevice();
					//putimage(0, 0, &img2);
					Choicepage();
					Choice();
				 }
				 else
					 if(m.x > 750 && m.x < 850 && m.y > 450 && m.y < 480)//750,450,850,480
					 {
						cleardevice();
						Missiontwo();
					 }
		 }
	 }
	return ;
}
void Missionthree()
{
	int x,y,ch;
	struct xydata *p1,*p2;
		
	COLORREF color=WHITE;
	MOUSEMSG	m;
	char time[10],t=0;
	timeflag=0;
		FILE *fp3;
	setlinecolor(WHITE);
	outtextxy(750,100,_T("���������ƶ�  ʱ�����ƣ�15s"));
	
	outtextxy(750,180,_T("��ʼʱ��"));
		outtextxy(850,180,_T("����ʱ��"));
		outtextxy(950,180,_T("��ʱ"));
//	setwritemode(R2_XORPEN);
	for(x=20;x<=740;x+=36)
		line(x,20,x,560);
	for(y=20;y<=560;y+=36)
		line(20,y,740,y);
		
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("��       ��"));
	rectangle(750,450,850,480);
	outtextxy(760,458,_T("�� �� �� ��"));
		fp3=(fopen("link_list3","rb"));
		if(fp3==NULL)
		{
				exit(0);
		}
		while(1)
		{
			p1=(struct xydata*)malloc(sizeof(struct xydata));
			fread(p1,sizeof(struct xydata)+1,1,fp3);
			p2=head3;
			head3=p1;
			p1->next=p2;
			if(feof(fp3))
				break;
		}
		head3=head3->next;
		fclose(fp3);
	setfillcolor(RGB(254,255,255));
	while(head3)
	
	{
		floodfill(head3->mx,head3->my,color);
		head3=head3->next;
	}
setfillcolor(BLACK);
		x=38;y=74;//��������  722 352
		outtextxy(752,362,_T("---->����"));
	fillcircle(x,y,18);
	ch=getch();
	SYSTEMTIME BT,ET;
while(1)
	{
		if(_kbhit())
		if(ch=0xe0)
		{
			ch=getch();
			switch(ch)
			{
				
			case UP:
				if(getpixel(x,y-36)==RGB(254,255,255))
				{
					setfillcolor(RGB(254,255,255));fillcircle(x,y,18);y-=36;setfillcolor(BLACK);fillcircle(x,y,18);}
				else;
					break;
			case DOWN:
				if(getpixel(x,y+36)==RGB(254,255,255))
				{setfillcolor(RGB(254,255,255));fillcircle(x,y,18);y+=36;setfillcolor(BLACK);fillcircle(x,y,18);}
				else
				{;}break;
			case LEFT:
				if(getpixel(x-36,y)==RGB(254,255,255))
				{setfillcolor(RGB(254,255,255));fillcircle(x,y,18);x-=36;setfillcolor(BLACK);fillcircle(x,y,18);}
				else
				{;	}break;
			case RIGHT:
				if(getpixel(x+36,y)==RGB(254,255,255))
				{setfillcolor(RGB(254,255,255));fillcircle(x,y,18);x+=36;setfillcolor(BLACK);fillcircle(x,y,18);}
				else
				{;}break;
			case ESC:
				goto downtwo;break;


			}
		}
			if(x==74&&y==74)
		{
			if(timeflag==0)
			{
				timeflag=1;
				GetLocalTime(&BT);
				itoa(BT.wHour, time, 10);
				outtextxy(750,210,time);
				itoa(BT.wMinute, time, 10);
				outtextxy(770,210,time);
				itoa(BT.wSecond, time, 10);
				outtextxy(790,210,time);
				outtextxy(767,210,_T(":"));
				outtextxy(787,210,_T(":"));
			}
		}
		if(x==722&&y==362)
		{
			GetLocalTime(&ET);
		
			itoa(ET.wHour, time, 10);
			outtextxy(850,210,time);
			itoa(ET.wMinute, time, 10);
			outtextxy(870,210,time);
			itoa(ET.wSecond, time, 10);
			outtextxy(890,210,time);
			outtextxy(867,210,_T(":"));
			outtextxy(887,210,_T(":"));
			itoa((60*(ET.wMinute-BT.wMinute)+ET.wSecond-BT.wSecond), time, 10);
			outtextxy(950,210,time);
			outtextxy(970,210,_T("s"));
			if((60*(ET.wMinute-BT.wMinute)+(ET.wSecond-BT.wSecond))<=15)
			{
					outtextxy(835,260,_T("���سɹ�"));
			}
			else
					outtextxy(835,260,_T("����ʧ��"));
			break;
		}
		
	}
downtwo:while(1)
	 {
		 m=GetMouseMsg();
		 switch(m.uMsg)
		 {
			 case  WM_LBUTTONDOWN://750,400,850,430);
				 if(m.x>750&&m.x<850&&m.y>400&&m.y<430)
				 {
					 cleardevice();
						//putimage(0, 0, &img2);
					Choicepage();
						Choice();
				 }
				 else
					 if(m.x>750&&m.x<850&&m.y>450&&m.y<480)//750,450,850,480
					 {
						cleardevice();
						Missionthree();
					 }
		 }
	 }
	return ;
}
void Missionfour()
{
	int x,y,ch;
	struct xydata *p1,*p2;
	COLORREF color=WHITE;
	MOUSEMSG	m;
	char time[10],t=0;
	timeflag=0;
	SYSTEMTIME BT,ET;
		FILE *fp4;
	setlinecolor(WHITE);
	outtextxy(750,100,_T("���������ƶ�  ʱ�����ƣ�15s"));
	
	outtextxy(750,180,_T("��ʼʱ��"));
		outtextxy(850,180,_T("����ʱ��"));
		outtextxy(950,180,_T("��ʱ"));
//	setwritemode(R2_XORPEN);
	for(x=20;x<=740;x+=36)
		line(x,20,x,560);
	for(y=20;y<=560;y+=36)
		line(20,y,740,y);
		
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("��       ��"));
	rectangle(750,450,850,480);
	outtextxy(760,458,_T("�� �� �� ��"));
		fp4=(fopen("link_list4","rb"));
		if(fp4==NULL)
		{
				exit(0);
		}
		while(1)
		{
			p1=(struct xydata*)malloc(sizeof(struct xydata));
			fread(p1,sizeof(struct xydata)+1,1,fp4);
			p2=head4;
			head4=p1;
			p1->next=p2;
			if(feof(fp4))
				break;
		}
		head4=head4->next;
		fclose(fp4);
	setfillcolor(RGB(254,255,255));
	while(head4)
	
	{
		floodfill(head4->mx,head4->my,color);
		head4=head4->next;
	}
setfillcolor(BLACK);
		x=38;y=38;//��������722  74
	outtextxy(752,74,_T("---->����"));
	fillcircle(x,y,18);
	ch=getch();
while(1)
	{
		if(_kbhit())
		if(ch=0xe0)
		{
			ch=getch();
			switch(ch)
			{
				
			case UP:
				if(getpixel(x,y-36)==RGB(254,255,255))
				{
					setfillcolor(RGB(254,255,255));fillcircle(x,y,18);y-=36;setfillcolor(BLACK);fillcircle(x,y,18);}
				else;
					break;
			case DOWN:
				if(getpixel(x,y+36)==RGB(254,255,255))
				{setfillcolor(RGB(254,255,255));fillcircle(x,y,18);y+=36;setfillcolor(BLACK);fillcircle(x,y,18);}
				else
				{;}break;
			case LEFT:
				if(getpixel(x-36,y)==RGB(254,255,255))
				{setfillcolor(RGB(254,255,255));fillcircle(x,y,18);x-=36;setfillcolor(BLACK);fillcircle(x,y,18);}
				else
				{;	}break;
			case RIGHT:
				if(getpixel(x+36,y)==RGB(254,255,255))
				{setfillcolor(RGB(254,255,255));fillcircle(x,y,18);x+=36;setfillcolor(BLACK);fillcircle(x,y,18);}
				else
				{;}break;
			case ESC:
				goto downtwo;break;


			}
		}
		if((x==38&&y==74)||(x==74&&y==38))
		{
			if(timeflag==0)
			{
				timeflag=1;
				GetLocalTime(&BT);
				itoa(BT.wHour, time, 10);
				outtextxy(750,210,time);
				itoa(BT.wMinute, time, 10);
				outtextxy(770,210,time);
				itoa(BT.wSecond, time, 10);
				outtextxy(790,210,time);
				outtextxy(767,210,_T(":"));
				outtextxy(787,210,_T(":"));
			}
		}
		if(x==722&&y==74)//������������ֹͣ��ʱ �������ʱ�� 
		{
			GetLocalTime(&ET);
		
			itoa(ET.wHour, time, 10);
			outtextxy(850,210,time);
			itoa(ET.wMinute, time, 10);
			outtextxy(870,210,time);
			itoa(ET.wSecond, time, 10);
			outtextxy(890,210,time);
			outtextxy(867,210,_T(":"));
			outtextxy(887,210,_T(":"));
			itoa((60*(ET.wMinute-BT.wMinute)+ET.wSecond-BT.wSecond), time, 10);
			outtextxy(950,210,time);
			outtextxy(970,210,_T("s"));
			if((60*(ET.wMinute-BT.wMinute)+(ET.wSecond-BT.wSecond))<=15)
			{
					outtextxy(835,260,_T("���سɹ�"));
			}
			else
					outtextxy(835,260,_T("����ʧ��"));
			break;
		}
		
	}
downtwo:while(1)
	 {
		 m=GetMouseMsg();
		 switch(m.uMsg)
		 {
			 case  WM_LBUTTONDOWN://750,400,850,430);
				 if(m.x>750&&m.x<850&&m.y>400&&m.y<430)
				 {
					 cleardevice();//����
						//putimage(0, 0, &img2);
					Choicepage();//ѡ�񴳹عؿ�����
						Choice();//ѡ�񴳹عؿ�
				 }
				 else
					 if(m.x>750&&m.x<850&&m.y>450&&m.y<480)//750,450,850,480
					 {
						cleardevice();
						Missionfour();
					 }
		 }
	 }
	return ;
}
void MissionPersonalOne()//�Զ���ؿ�1
{
		int x,y,ch;
	struct xydata *p1,*p2;
	COLORREF color=WHITE;//�趨��ɫΪ���ɫ
	MOUSEMSG	m;
	char time[10],t=0;
	timeflag=0;
	SYSTEMTIME BT,ET;
		FILE *fp5;
	setlinecolor(WHITE);
	outtextxy(800,100,_T("���������ƶ�"));
	
	outtextxy(750,290,_T("---->����"));
	outtextxy(750,180,_T("��ʼʱ��"));
		outtextxy(850,180,_T("����ʱ��"));
		outtextxy(950,180,_T("��ʱ"));
//	setwritemode(R2_XORPEN);
	for(x=20;x<=740;x+=36)
		line(x,20,x,560);
	for(y=20;y<=560;y+=36)
		line(20,y,740,y);
		
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("��       ��"));
	rectangle(750,450,850,480);
	outtextxy(760,458,_T("�� �� �� ��"));
		fp5=(fopen("link_list5","rb"));//��ȡ���ݽ������������Թ�����
		if(fp5==NULL)
		{
				exit(0);
		}
		while(1)
		{
			p1=(struct xydata*)malloc(sizeof(struct xydata));
			fread(p1,sizeof(struct xydata)+1,1,fp5);
			p2=personal1;
			personal1=p1;
			p1->next=p2;
			if(feof(fp5))
				break;
		}
		personal1=personal1->next;
		fclose(fp5);
	setfillcolor(RGB(254,255,255));
	while(personal1)
	
	{
		floodfill(personal1->mx,personal1->my,color);
		personal1=personal1->next;
	}
setfillcolor(BLACK);
		x=38;y=146;
	fillcircle(x,y,18);
	ch=getch();
while(1)
	{
		if(_kbhit())
		if(ch=0xe0)
		{
			ch=getch();
			switch(ch)
			{
				
			case UP:
				if(getpixel(x,y-36)==RGB(254,255,255))
				{
					setfillcolor(RGB(254,255,255));fillcircle(x,y,18);y-=36;setfillcolor(BLACK);fillcircle(x,y,18);}
				else;
					break;
			case DOWN:
				if(getpixel(x,y+36)==RGB(254,255,255))
				{setfillcolor(RGB(254,255,255));fillcircle(x,y,18);y+=36;setfillcolor(BLACK);fillcircle(x,y,18);}
				else
				{;}break;
			case LEFT:
				if(getpixel(x-36,y)==RGB(254,255,255))
				{setfillcolor(RGB(254,255,255));fillcircle(x,y,18);x-=36;setfillcolor(BLACK);fillcircle(x,y,18);}
				else
				{;	}break;
			case RIGHT:
				if(getpixel(x+36,y)==RGB(254,255,255))
				{setfillcolor(RGB(254,255,255));fillcircle(x,y,18);x+=36;setfillcolor(BLACK);fillcircle(x,y,18);}
				else
				{;}break;
			case ESC:
				goto downtwo;break;


			}
		}
		if((x==74&&y==146)||(x==38&&y==110)||(x==38&&y==182))//38   146
		{
			if(timeflag==0)
			{
				timeflag=1;
				GetLocalTime(&BT);
				itoa(BT.wHour, time, 10);
				outtextxy(750,210,time);
				itoa(BT.wMinute, time, 10);
				outtextxy(770,210,time);
				itoa(BT.wSecond, time, 10);
				outtextxy(790,210,time);
				outtextxy(767,210,_T(":"));
				outtextxy(787,210,_T(":"));
			}
		}
		if(x==722&&y==290)
		{
			GetLocalTime(&ET);
		
			itoa(ET.wHour, time, 10);
			outtextxy(850,210,time);
			itoa(ET.wMinute, time, 10);
			outtextxy(870,210,time);
			itoa(ET.wSecond, time, 10);
			outtextxy(890,210,time);
			outtextxy(867,210,_T(":"));
			outtextxy(887,210,_T(":"));
			itoa((60*(ET.wMinute-BT.wMinute)+ET.wSecond-BT.wSecond), time, 10);
			outtextxy(950,210,time);
			outtextxy(970,210,_T("s"));
			if((60*(ET.wMinute-BT.wMinute)+(ET.wSecond-BT.wSecond))<=20)
			{
					outtextxy(835,260,_T("���سɹ�"));
			}
			else
					outtextxy(835,260,_T("����ʧ��"));
			break;
		}
		
	}
downtwo:while(1)
	 {
		 m=GetMouseMsg();
		 switch(m.uMsg)
		 {
			 case  WM_LBUTTONDOWN://750,400,850,430);
				 if(m.x>750&&m.x<850&&m.y>400&&m.y<430)
				 {
					 cleardevice();
						//putimage(0, 0, &img2);
					Choicepage();
						Choice();
				 }
				 else
					 if(m.x>750&&m.x<850&&m.y>450&&m.y<480)//750,450,850,480
					 {
						cleardevice();
						MissionPersonalOne();
					 }
		 }
	 }
	return ;
}
void MissionPersonalTwo()
{
int x,y,ch;
	struct xydata *p1,*p2;
	COLORREF color=WHITE;
	MOUSEMSG	m;
		char time[10],t=0;
	timeflag=0;
	SYSTEMTIME BT,ET;
		FILE *fp6;
	setlinecolor(WHITE);
	outtextxy(800,100,_T("���������ƶ�"));
	
	outtextxy(750,180,_T("��ʼʱ��"));
		outtextxy(850,180,_T("����ʱ��"));
		outtextxy(950,180,_T("��ʱ"));
//	setwritemode(R2_XORPEN);
	for(x=20;x<=740;x+=36)
		line(x,20,x,560);
	for(y=20;y<=560;y+=36)
		line(20,y,740,y);
		
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("��       ��"));
	rectangle(750,450,850,480);
	outtextxy(760,458,_T("�� �� �� ��"));
		fp6=(fopen("link_list6","rb"));//��ȡ�ļ���������������ת�����Թ��ĵ�·
		if(fp6==NULL)
		{
				exit(0);
		}
		while(1)
		{
			p1=(struct xydata*)malloc(sizeof(struct xydata));
			fread(p1,sizeof(struct xydata)+1,1,fp6);
			p2=personal2;
			personal2=p1;
			p1->next=p2;
			if(feof(fp6))
				break;
		}
		personal2=personal2->next;
		fclose(fp6);
	setfillcolor(RGB(254,255,255));
	while(personal2)
	
	{
		floodfill(personal2->mx,personal2->my,color);
		personal2=personal2->next;
	}
		setfillcolor(BLACK);
		x=290;y=542;
		outtextxy(752,362,_T("---->����"));
	fillcircle(x,y,18);
	ch=getch();
while(1)
	{
		if(_kbhit())
		if(ch=0xe0)
		{
			ch=getch();
			switch(ch)
			{
				
			case UP:
				if(getpixel(x,y-36)==RGB(254,255,255))
				{
					setfillcolor(RGB(254,255,255));fillcircle(x,y,18);y-=36;setfillcolor(BLACK);fillcircle(x,y,18);}
				else;
					break;
			case DOWN:
				if(getpixel(x,y+36)==RGB(254,255,255))
				{setfillcolor(RGB(254,255,255));fillcircle(x,y,18);y+=36;setfillcolor(BLACK);fillcircle(x,y,18);}
				else
				{;}break;
			case LEFT:
				if(getpixel(x-36,y)==RGB(254,255,255))
				{setfillcolor(RGB(254,255,255));fillcircle(x,y,18);x-=36;setfillcolor(BLACK);fillcircle(x,y,18);}
				else
				{;	}break;
			case RIGHT:
				if(getpixel(x+36,y)==RGB(254,255,255))
				{setfillcolor(RGB(254,255,255));fillcircle(x,y,18);x+=36;setfillcolor(BLACK);fillcircle(x,y,18);}
				else
				{;}break;
			case ESC:
				goto downtwo;break;


			}
		}
			if((x==254&&y==542)||(x==326&&y==542)||(x==290&&y==506))//290  542 
		{
			if(timeflag==0)//ȷ����һ���ƶ���ʱ��ʼ��ʱ
			{
				timeflag=1;
				GetLocalTime(&BT);
				itoa(BT.wHour, time, 10);
				outtextxy(750,210,time);
				itoa(BT.wMinute, time, 10);
				outtextxy(770,210,time);
				itoa(BT.wSecond, time, 10);
				outtextxy(790,210,time);
				outtextxy(767,210,_T(":"));
				outtextxy(787,210,_T(":"));
			}
		}
		if(x==722&&y==362)
		{
			GetLocalTime(&ET);
		
			itoa(ET.wHour, time, 10);//��ʱ��ת�����ַ����������
			outtextxy(850,210,time);
			itoa(ET.wMinute, time, 10);
			outtextxy(870,210,time);
			itoa(ET.wSecond, time, 10);
			outtextxy(890,210,time);
			outtextxy(867,210,_T(":"));
			outtextxy(887,210,_T(":"));
			itoa((60*(ET.wMinute-BT.wMinute)+ET.wSecond-BT.wSecond), time, 10);
			outtextxy(950,210,time);
			outtextxy(970,210,_T("s"));
			if((60*(ET.wMinute-BT.wMinute)+(ET.wSecond-BT.wSecond))<=15)
			{
					outtextxy(835,260,_T("���سɹ�"));
			}
			else
					outtextxy(835,260,_T("����ʧ��"));
			break;
		}
		
		
	}
downtwo:while(1)
	 {
		 m=GetMouseMsg();
		 switch(m.uMsg)
		 {
			 case  WM_LBUTTONDOWN://750,400,850,430);
				 if(m.x>750&&m.x<850&&m.y>400&&m.y<430)
				 {
					 cleardevice();
						//putimage(0, 0, &img2);
					Choicepage();//ѡ�񴳹عؿ��Ľ�����ʾ����
						Choice();
				 }
				else
					 if(m.x>750&&m.x<850&&m.y>450&&m.y<480)//750,450,850,480
					 {
						cleardevice();
						MissionPersonalTwo();
					 }
		 }
	 }
	return ;
}
void Choice()//ѡ�񴳹عؿ�
{
	int i,j;
	MOUSEMSG m;
		setfillcolor(BLACK);
		fillrectangle(390,130,495,160);
		outtextxy(410,138,_T("��  ��  1"));
		fillrectangle(390,180,495,210);
		outtextxy(410,188,_T("��  ��  2"));
		fillrectangle(390,230,495,260);
		outtextxy(410,238,_T("��  ��  3"));
		fillrectangle(390,280,495,310);
		outtextxy(410,288,_T("��  ��  4"));
		fillrectangle(590,150,695,180);
		outtextxy(603,158,_T("�Զ���ؿ�1"));
		fillrectangle(590,200,695,230);
		outtextxy(603,208,_T("�Զ���ؿ�2"));
		fillrectangle(590,250,695,280);
		outtextxy(623,258,_T("��  ��"));
		
	while(1)	{
			m=GetMouseMsg();
			switch(m.uMsg)
			{
			case  WM_LBUTTONDOWN:
								if(m.x>390&&m.x<495&&m.y>130&&m.y<160)//�ؿ�1
								{
									cleardevice();
									Mission();
								}
								else
									if(m.x>390&&m.x<495&&m.y>180&&m.y<210)//�ؿ�2
									{
											cleardevice();
											Missiontwo();
									}
								else
									if(m.x>390&&m.x<495&&m.y>230&&m.y<260)//�ؿ�3
									{
											cleardevice();
											Missionthree();
									}
								else
									if(m.x>390&&m.x<495&&m.y>280&&m.y<310)//�ؿ�4
									{
											cleardevice();
											Missionfour();//�ؿ�4  ��ͬ
									}
								else
									if(m.x>590&&m.x<695&&m.y>150&&m.y<180)//���˹ؿ�1
									{
											cleardevice();
											MissionPersonalOne();//���˹ؿ�1
									}
								else
									if(m.x>590&&m.x<695&&m.y>200&&m.y<230)//���˹ؿ�2
									{
											cleardevice();
											MissionPersonalTwo();//���˹ؿ�2
									}
								else
									if(m.x>590&&m.x<695&&m.y>250&&m.y<280)//����
									{
											 cleardevice();
											pageshow_();
									}
								break;
			}
		}
}
void GameIntr()//��Ϸ���ܺ���
{
	MOUSEMSG m;
	outtextxy(340,130,_T("����ģʽ�������Ĺأ���ʱ����������ɼ���ͨ�ء�"));
	outtextxy(340,150,_T("�޸��Թ��������޸��ĸ��ؿ�����ǽ��·����·��ǽ,"));
	outtextxy(420,170,_T("����Ҳ���ɫ���򼴿��޸ġ�"));
	outtextxy(340,190,_T("���·�����������ͨ��·�������·����"));
	outtextxy(340,210,_T("�˳���Ϸ����������˳���Ϸ��"));
	outtextxy(340,270,_T("�����Ŷӣ����£������ģ����"));
	fillrectangle(640,300,745,330);
	outtextxy(655,310,_T("��          ��"));
	while(1)
	{
			m=GetMouseMsg();
			switch(m.uMsg)
			{
				case  WM_LBUTTONDOWN:
							if(m.x>640&&m.x<745&&m.y>300&&m.y<330)//����
							{
								 cleardevice();//�������
								 pageshow_();//��������ʾ
							}
								break;
			}
	}
}
void pageshow_()
{
	MOUSEMSG m;
	float mx,my;
	float x,j=220,y,i;
	COLORREF color=WHITE;
	setlinecolor(WHITE);
	line(0,580,200,380);
	for(x=36;x<=1080;x+=36)
		line(x,580,x+200,380);
	for(y=380;y<=580;y+=20)
		line(j-=20,y,1080,y);
	line(200,380,1080,380);
	y=-20;
	for(x=0;x<=200;x+=20)
		line(x,0,x,580-(y+=20));
	line(200,0,200,380);
	for(y=0;y<570;y+=25)
		line(0,y,200,y-200);
	for(x=200;x<=1080;x+=36)
		line(x,0,x,380);
	for(y=0;y<=370;y+=25)
		line(200,y,1080,y);
	setfillcolor(RGB(254,255,255));
	for(mx=330,my=590;my>480;my-=40,mx+=40)
	{floodfill(mx,my,color);}
	for(;mx>100;mx-=72)
	{floodfill(mx,my,color);}
	for(mx+=25,my-=15;my>175;my-=50)
	{floodfill(mx,my,color);}
	for(;mx<=200;mx+=40,my-=40)
	{floodfill(mx,my,color);}
	for(my+=25,mx+=10;mx<880;mx+=72)
	{floodfill(mx,my,color);}
	for(;my<380;my+=50)
	{floodfill(mx,my,color);}
	for(mx-=20;my<=460;my+=40,mx-=40)
	{floodfill(mx,my,color);}
	for(mx-=20,my-=20;mx>550;mx-=72)
	{floodfill(mx,my,color);}
	for(mx+=72;my<580;my+=40,mx-=40)
	{floodfill(mx,my,color);}
	for(i=542.5,j=225;i>=320,j>=100;i-=1.88,j--)
	{
		fillrectangle(i,j,542.5-i+542.5,225-j+225);
		Sleep(1);
	}
	setfillcolor(BLACK);
	fillrectangle(490,100,595,130);
	outtextxy(510,108,_T("����ģʽ"));
	fillrectangle(490,150,595,180);
	outtextxy(510,158,_T("�޸��Թ�"));
	fillrectangle(490,200,595,230);
	outtextxy(510,208,_T("ͨ��·��"));
	fillrectangle(490,250,595,280);
	outtextxy(510,258,_T("��Ϸ����"));
	fillrectangle(490,300,595,330);
	outtextxy(510,308,_T("�˳���Ϸ"));

	while(1)
	{
		m=GetMouseMsg();
		switch(m.uMsg)
		{
		case WM_LBUTTONDOWN:
			if(m.x>490&&m.x<595&&m.y>100&&m.y<130)//����ģʽ
			{
				for(i=542.5,j=225;i>=320,j>=100;i-=1.88,j--)
				{
					fillrectangle(i,j,542.5-i+542.5,225-j+225);
					Sleep(1);
				}
				Choice();	
			}
			else
				if(m.x>490&&m.x<595&&m.y>150&&m.y<180)//�޸��Թ�
				{
					for(i=542.5,j=225;i>=320,j>=100;i-=1.88,j--)
						{
							fillrectangle(i,j,542.5-i+542.5,225-j+225);
							Sleep(1);
						}
					ChangeMaze();
				}
				else
					if(m.x>490&&m.x<595&&m.y>250&&m.y<280)//��Ϸ����
					{
						for(i=542.5,j=225;i>=320,j>=100;i-=1.88,j--)
							{
								fillrectangle(i,j,542.5-i+542.5,225-j+225);
								Sleep(1);
							}
							GameIntr();
						}
					else
						if(m.x>490&&m.x<595&&m.y>300&&m.y<330)//�˳���Ϸ490,300,595,330
						{
							for(i=320,j=100;i<=542.5,j<=225;i+=1.88,j++)
							{
								setfillcolor(BLACK);
								fillrectangle(i,j,542.5-i+542.5,225-j+225);
								Sleep(2);
							}
							cleardevice();
							Quitgame_();
							Quitgame();
						}
						else
					if(m.x>490&&m.x<595&&m.y>200&&m.y<230)//���·��490,200,595,230
					{
						for(i=542.5,j=225;i>=320,j>=100;i-=1.88,j--)
						{
							fillrectangle(i,j,542.5-i+542.5,225-j+225);
							Sleep(1);
						}
						MazePathShow();		
					}
				break;
		}
	}
	return ;
}
void pageshow()
{
	MOUSEMSG m;
	float mx,my;
	COLORREF color=WHITE;
	float x,j=220,y,i;
	setlinecolor(WHITE);
	line(0,580,200,380);
	for(x=36;x<=1080;x+=36)
		line(x,580,x+200,380);
	for(y=380;y<=580;y+=20)
		line(j-=20,y,1080,y);
	line(200,380,1080,380);
	y=-20;
	for(x=0;x<=200;x+=20)
		line(x,0,x,580-(y+=20));
	line(200,0,200,380);
	for(y=0;y<570;y+=25)
		line(0,y,200,y-200);
	for(x=200;x<=1080;x+=36)
		line(x,0,x,380);
	for(y=0;y<=370;y+=25)
		line(200,y,1080,y);
		setfillcolor(RGB(254,255,255));
		for(mx=330,my=590;my>480;my-=40,mx+=40)
		{
			floodfill(mx,my,color);
			Sleep(50);
		}
	for(;mx>100;mx-=72)
	{
		floodfill(mx,my,color);
		Sleep(50);
	}
	for(mx+=25,my-=15;my>175;my-=50)
	{
		floodfill(mx,my,color);
		Sleep(50);
	}
	for(;mx<=200;mx+=40,my-=40)
	{
		floodfill(mx,my,color);
		Sleep(50);
	}
	for(my+=25,mx+=10;mx<880;mx+=72)
	{
		floodfill(mx,my,color);
		Sleep(50);
	}
	for(;my<380;my+=50)
	{
		floodfill(mx,my,color);
		Sleep(50);
	}
	for(mx-=20;my<=460;my+=40,mx-=40)
	{
		floodfill(mx,my,color);
		Sleep(50);
	}
	for(mx-=20,my-=20;mx>550;mx-=72)
	{
		floodfill(mx,my,color);
		Sleep(50);
	}
	for(mx+=72;my<580;my+=40,mx-=40)
	{
		floodfill(mx,my,color);
		Sleep(50);
	}
	
	getimage(&img, 0, 0, 1080, 580);
	for(i=542.5,j=225;i>=320,j>=100;i-=1.88,j--)
	{
		fillrectangle(i,j,542.5-i+542.5,225-j+225);
		Sleep(1);
	}
	setfillcolor(BLACK);
	fillrectangle(490,100,595,130);
	outtextxy(510,108,_T("����ģʽ"));
	fillrectangle(490,150,595,180);
	outtextxy(510,158,_T("�޸��Թ�"));
	fillrectangle(490,200,595,230);
	outtextxy(510,208,_T("ͨ��·��"));
	fillrectangle(490,250,595,280);
	outtextxy(510,258,_T("��Ϸ����"));
	fillrectangle(490,300,595,330);
	outtextxy(510,308,_T("�˳���Ϸ"));
while(1)
	{
		m=GetMouseMsg();
		switch(m.uMsg)
		{
		case WM_LBUTTONDOWN:
			if(m.x>490&&m.x<595&&m.y>100&&m.y<130)//����ģʽ
			{
			for(i=542.5,j=225;i>=320,j>=100;i-=1.88,j--)
				{
					fillrectangle(i,j,542.5-i+542.5,225-j+225);
					Sleep(1);
				}
				Choice();//ѡ�񴳹غ���
				
				
			}
			else
				if(m.x>490&&m.x<595&&m.y>150&&m.y<180)//�޸��Թ�
				{
					for(i=542.5,j=225;i>=320,j>=100;i-=1.88,j--)
						{
							fillrectangle(i,j,542.5-i+542.5,225-j+225);
							Sleep(1);
						}
						ChangeMaze();//ѡ���޸��Թ�����
					}
				else
					if(m.x>490&&m.x<595&&m.y>250&&m.y<280)//��Ϸ����
					{
						for(i=542.5,j=225;i>=320,j>=100;i-=1.88,j--)
						{
							fillrectangle(i,j,542.5-i+542.5,225-j+225);
							Sleep(1);
						}
						GameIntr();//��Ϸ����
					}
					else
				if(m.x>490&&m.x<595&&m.y>300&&m.y<330)//�˳���Ϸ490,300,595,330
				{
					
					for(i=320,j=100;i<=542.5,j<=225;i+=1.88,j++)
					
						{setfillcolor(BLACK);//���ú�ɫΪ���ɫ
							
							fillrectangle(i,j,542.5-i+542.5,225-j+225);
							Sleep(2);
						}
						cleardevice();
						Quitgame_();//�˳���Ϸ���溯��
						Quitgame();//�˳���Ϸ���溯��
					}
				else
					if(m.x>490&&m.x<595&&m.y>200&&m.y<230)//���·��490,200,595,230
					{
						for(i=542.5,j=225;i>=320,j>=100;i-=1.88,j--)
						{
							fillrectangle(i,j,542.5-i+542.5,225-j+225);
							Sleep(1);
						}
						MazePathShow();		
					}
						break;
		}
	}
	return ;
}
void Quitgame()
{
		float mx,my;
	COLORREF color=WHITE;
	float x,j=220,y,i;
	setlinecolor(WHITE);
	line(0,580,200,380);
	for(x=36;x<=1080;x+=36)
		line(x,580,x+200,380);
	for(y=380;y<=580;y+=20)
		line(j-=20,y,1080,y);
	line(200,380,1080,380);
	y=-20;
	for(x=0;x<=200;x+=20)
		line(x,0,x,580-(y+=20));

	line(200,0,200,380);
	for(y=0;y<570;y+=25)
		line(0,y,200,y-200);
	for(x=200;x<=1080;x+=36)
		line(x,0,x,380);
	for(y=0;y<=370;y+=25)
	
		line(200,y,1080,y);
		setfillcolor(BLACK);
		for(mx=330,my=590;my>480;my-=40,mx+=40)
		{
			floodfill(mx,my,color);
			Sleep(50);
	}
	for(;mx>100;mx-=72)
	{
		floodfill(mx,my,color);
		Sleep(50);
	}
	for(mx+=25,my-=15;my>175;my-=50)
	{
		floodfill(mx,my,color);
		Sleep(50);
	}
	for(;mx<=200;mx+=40,my-=40)
	{
		floodfill(mx,my,color);
		Sleep(50);
	}
	for(my+=25,mx+=10;mx<880;mx+=72)
	{
		floodfill(mx,my,color);
		Sleep(50);
	}
	for(;my<380;my+=50)
	{
		floodfill(mx,my,color);
		Sleep(50);
	}
	for(mx-=20;my<=460;my+=40,mx-=40)
	{
		floodfill(mx,my,color);
		Sleep(50);
	}
	for(mx-=20,my-=20;mx>550;mx-=72)
	{
		floodfill(mx,my,color);
		Sleep(50);
	}
	for(mx+=72;my<580;my+=40,mx-=40)
	{
		floodfill(mx,my,color);
		Sleep(50);
	}
	setlinecolor(BLACK);
	for(mx=0;mx<=1080;mx++)
	{
		line(mx,0,mx,580);
		Sleep(1);
	}
	
	closegraph();
	hide();
}
void Quitgame_()
{
	
	MOUSEMSG m;
	float mx,my;
	float x,j=220,y,i;
	COLORREF color=WHITE;//�԰�ɫΪ���ɫ
	setlinecolor(WHITE);
	line(0,580,200,380);
	for(x=36;x<=1080;x+=36)
		line(x,580,x+200,380);
	for(y=380;y<=580;y+=20)
		line(j-=20,y,1080,y);
	line(200,380,1080,380);
	y=-20;
	for(x=0;x<=200;x+=20)
		line(x,0,x,580-(y+=20));

	line(200,0,200,380);
	for(y=0;y<570;y+=25)
		line(0,y,200,y-200);
	for(x=200;x<=1080;x+=36)
		line(x,0,x,380);
	for(y=0;y<=370;y+=25)
	
		line(200,y,1080,y);
			setfillcolor(RGB(254,255,255));
		
		for(mx=330,my=590;my>480;my-=40,mx+=40)
		{
			floodfill(mx,my,color);	
		}
	for(;mx>100;mx-=72)
	{
		floodfill(mx,my,color);	
	}
	for(mx+=25,my-=15;my>175;my-=50)
	{
		floodfill(mx,my,color);
	}
	for(;mx<=200;mx+=40,my-=40)
	{
		floodfill(mx,my,color);	
	}
	for(my+=25,mx+=10;mx<880;mx+=72)
	{
		floodfill(mx,my,color);
	}
	for(;my<380;my+=50)
	{
		floodfill(mx,my,color);
	}
	for(mx-=20;my<=460;my+=40,mx-=40)
	{
		floodfill(mx,my,color);	
	}
	for(mx-=20,my-=20;mx>550;mx-=72)
	{
		floodfill(mx,my,color);		
	}
	for(mx+=72;my<580;my+=40,mx-=40)
	{
		floodfill(mx,my,color);	
	}
}
/*typedef struct{//���浱ǰ����
int x;
int y;
}PosType;

typedef struct{//ջ�Ľṹ

	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;


typedef struct{//ջ��Ԫ������
	int ord;
	PosType seat;
	int di;
}SElemType;
*/
void InitStack(SqStack &S)
{
	S.base=(SElemType *)malloc(STACK_INT_SIZE*sizeof(SElemType));
	if(!S.base)
		exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INT_SIZE;
	return ;
}

int Passone(PosType curpos)
{
	//FILE *fp;
	struct xydata *ptr,*p1,*p2;
//fp = (fopen("link_list1","rb"));
		//if(fp == NULL)
		//{
		/*	exit(0);
		}
		while(1)
		{
			p1 = (struct xydata*)malloc(sizeof(struct xydata));
			fread(p1,sizeof(struct xydata)+1,1,fp);
			p2 = head1;
			head1 = p1;
			p1 -> next = p2;
			if(feof(fp))
				break;
		}
		head1 = head1 -> next;
		fclose(fp);*/
		ptr=head1;
		while(ptr)
		{
			if(ptr->mx==curpos.x&&ptr->my==curpos.y&&visit[(curpos.x-38)/36][(curpos.y-38)/36]==0)
				return 1;
			ptr=ptr->next;
		}
return 0;
}

void FootPrint(PosType curpos)
{
	visit[(curpos.x-38)/36][(curpos.y-38)/36]=1;
	return ;
}

void Push(SqStack &S,SElemType e)
{
	if(S.top-S.base >= S.stacksize)
	{
		S.base = (SElemType *)realloc(S.base,(S.stacksize+STACKINCREMENT) * sizeof(SElemType));
		if(!S.base)
			exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=e;
	return ;
}

PosType NextPos(PosType curpos,int di)
{
	switch(di)
	{
	case 1:curpos.x-=36;break;//����
	case 2:curpos.x+=36;break;//����
	case 3:curpos.y-=36;break;//����
	case 4:curpos.y+=36;break;//����
	}
	return curpos;
}

 void  Pop(SqStack &S,SElemType &e)
 {
	 //if(S.top == S.base)
		// r;//!!!!!
		e=*--S.top;//ɾ��ջ�������ص�ǰջ��Ԫ��
		return ;
 }
 void MissionOnemap()
 {
	 int x,y,ch;
	char time[10],t=0;
	struct xydata *p1,*p2,*ptr;
	COLORREF color=WHITE;
	MOUSEMSG	m;
	FILE *fp;
	timeflag=0;
	setlinecolor(WHITE);
//	setwritemode(R2_XORPEN);
	for(x=20;x<=740;x+=36)
		line(x,20,x,560);
	for(y=20;y<=560;y+=36)
		line(20,y,740,y);
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("��       ��"));
	outtextxy(750,290,_T("---->����"));
			fp = (fopen("link_list1","rb"));
		if(fp == NULL)
		{
			exit(0);
		}
		while(1)
		{
			p1 = (struct xydata*)malloc(sizeof(struct xydata));
			fread(p1,sizeof(struct xydata)+1,1,fp);
			p2 = head1;
			head1 = p1;
			p1 -> next = p2;
			if(feof(fp))
				break;
		}
		head1 = head1 -> next;
		fclose(fp);
		ptr=head1;
	setfillcolor(RGB(254,255,255));
	while(ptr)
	
	{
		floodfill(ptr -> mx,ptr -> my,color);
		ptr = ptr -> next;
	}
 }

 int StackEmpty(SqStack &S)
{
	if(S.base==S.top)
		return 1;
		else
		return 0;
}
void MakePrint(PosType curpos)
{
	visit[(curpos.x-38)/36][(curpos.y-38)/36]=1;
	return ;
}

void MissionPTwomap()
{
int x,y,ch;
	struct xydata *p1,*p2,*ptr;
		
	COLORREF color=WHITE;
	MOUSEMSG	m;
	char time[10],t=0;
	timeflag=0;
		FILE *fp3;
	setlinecolor(WHITE);
//	setwritemode(R2_XORPEN);
	for(x=20;x<=740;x+=36)
		line(x,20,x,560);
	for(y=20;y<=560;y+=36)
		line(20,y,740,y);
		
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("��       ��"));
	outtextxy(752,362,_T("---->����"));

		fp3=(fopen("link_list6","rb"));
		if(fp3==NULL)
		{
				exit(0);
		}
		while(1)
		{
			p1=(struct xydata*)malloc(sizeof(struct xydata));
			fread(p1,sizeof(struct xydata)+1,1,fp3);
			p2=personal2;
			personal2=p1;
			p1->next=p2;
			if(feof(fp3))
				break;
		}
		personal2=personal2->next;
		fclose(fp3);
		ptr=personal2;
	setfillcolor(RGB(254,255,255));
	while(ptr)
	
	{
		floodfill(ptr->mx,ptr->my,color);
		ptr=ptr->next;
	}
}
void MissionPOnemap()
{
int x,y,ch;
	struct xydata *p1,*p2,*ptr;
		
	COLORREF color=WHITE;
	MOUSEMSG	m;
	char time[10],t=0;
	timeflag=0;
		FILE *fp3;
	setlinecolor(WHITE);
//	setwritemode(R2_XORPEN);
	for(x=20;x<=740;x+=36)
		line(x,20,x,560);
	for(y=20;y<=560;y+=36)
		line(20,y,740,y);
		
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("��       ��"));
	outtextxy(750,290,_T("---->����"));
		fp3=(fopen("link_list5","rb"));
		if(fp3==NULL)
		{
				exit(0);
		}
		while(1)
		{
			p1=(struct xydata*)malloc(sizeof(struct xydata));
			fread(p1,sizeof(struct xydata)+1,1,fp3);
			p2=personal1;
			personal1=p1;
			p1->next=p2;
			if(feof(fp3))
				break;
		}
		personal1=personal1->next;
		fclose(fp3);
		ptr=personal1;
	setfillcolor(RGB(254,255,255));
	while(ptr)
	
	{
		floodfill(ptr->mx,ptr->my,color);
		ptr=ptr->next;
	}
}
void MissionFourmap()
{
int x,y,ch;
	struct xydata *p1,*p2,*ptr;
		
	COLORREF color=WHITE;
	MOUSEMSG	m;
	char time[10],t=0;
	timeflag=0;
		FILE *fp3;
	setlinecolor(WHITE);
//	setwritemode(R2_XORPEN);
	for(x=20;x<=740;x+=36)
		line(x,20,x,560);
	for(y=20;y<=560;y+=36)
		line(20,y,740,y);
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("��       ��"));
	outtextxy(752,74,_T("---->����"));
		fp3=(fopen("link_list4","rb"));
		if(fp3==NULL)
		{
				exit(0);
		}
		while(1)
		{
			p1=(struct xydata*)malloc(sizeof(struct xydata));
			fread(p1,sizeof(struct xydata)+1,1,fp3);
			p2=head4;
			head4=p1;
			p1->next=p2;
			if(feof(fp3))
				break;
		}
		head4=head4->next;
		fclose(fp3);
		ptr=head4;
	setfillcolor(RGB(254,255,255));
	while(ptr)
	
	{
		floodfill(ptr->mx,ptr->my,color);
		ptr=ptr->next;
	}
}
void MissionThreemap()
{
		int x,y,ch;
	struct xydata *p1,*p2,*ptr;
		
	COLORREF color=WHITE;
	MOUSEMSG	m;
	char time[10],t=0;
	timeflag=0;
		FILE *fp3;
	setlinecolor(WHITE);
//	setwritemode(R2_XORPEN);
	for(x=20;x<=740;x+=36)
		line(x,20,x,560);
	for(y=20;y<=560;y+=36)
		line(20,y,740,y);
		
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("��       ��"));
		outtextxy(752,362,_T("---->����"));
		fp3=(fopen("link_list3","rb"));
		if(fp3==NULL)
		{
				exit(0);
		}
		while(1)
		{
			p1=(struct xydata*)malloc(sizeof(struct xydata));
			fread(p1,sizeof(struct xydata)+1,1,fp3);
			p2=head3;
			head3=p1;
			p1->next=p2;
			if(feof(fp3))
				break;
		}
		head3=head3->next;
		fclose(fp3);
		ptr=head3;
	setfillcolor(RGB(254,255,255));
	while(ptr)
	
	{
		floodfill(ptr->mx,ptr->my,color);
		ptr=ptr->next;
	}
}
void MissionTwomap()
{
	int x,y,ch;
	struct xydata *p1,*p2,*ptr;
	char time[10],t = 0;
	COLORREF color = WHITE;
	MOUSEMSG	m;
		FILE *fp2;
		timeflag = 0;
	setlinecolor(WHITE);
//	setwritemode(R2_XORPEN);
	for(x=20;x<=740;x+=36)
		line(x,20,x,560);
	for(y=20;y<=560;y+=36)
		line(20,y,740,y);
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("��       ��"));
	outtextxy(752,542,_T("---->����"));
		fp2 = (fopen("link_list2","rb"));
		if(fp2 == NULL)
		{
				exit(0);
		}
		while(1)
		{
			p1 = (struct xydata*)malloc(sizeof(struct xydata));
			fread(p1,sizeof(struct xydata)+1,1,fp2);
			p2 = head2;
			head2 = p1;
			p1 -> next = p2;
			if(feof(fp2))
				break;
		}
		head2 = head2 -> next;
		fclose(fp2);
		ptr=head2;
	setfillcolor(RGB(254,255,255));
	while(ptr)
	
	{
		floodfill(ptr -> mx,ptr -> my,color);
		ptr = ptr -> next;
	}
	return;
}

int PassPTwo(PosType curpos)
{
struct xydata *ptr,*p1,*p2;

		ptr=personal2;
		while(ptr)
		{
			if(ptr->mx==curpos.x&&ptr->my==curpos.y&&visit[(curpos.x-38)/36][(curpos.y-38)/36]==0)
				return 1;
			ptr=ptr->next;
		}
return 0;
}
int PassPOne(PosType curpos)
{
struct xydata *ptr,*p1,*p2;

		ptr=personal1;
		while(ptr)
		{
			if(ptr->mx==curpos.x&&ptr->my==curpos.y&&visit[(curpos.x-38)/36][(curpos.y-38)/36]==0)
				return 1;
			ptr=ptr->next;
		}
return 0;
}
int PassFour(PosType curpos)
{

	struct xydata *ptr,*p1,*p2;

		ptr=head4;
		while(ptr)
		{
			if(ptr->mx==curpos.x&&ptr->my==curpos.y&&visit[(curpos.x-38)/36][(curpos.y-38)/36]==0)
				return 1;
			ptr=ptr->next;
		}
return 0;
}
int PassThree(PosType curpos)
{

	struct xydata *ptr,*p1,*p2;
		ptr=head3;
		while(ptr)
		{
			if(ptr->mx==curpos.x&&ptr->my==curpos.y&&visit[(curpos.x-38)/36][(curpos.y-38)/36]==0)
				return 1;
			ptr=ptr->next;
		}
return 0;
}
int PassTwo(PosType curpos)
{
	struct xydata *ptr,*p1,*p2;
		ptr=head2;
		while(ptr)
		{
			if(ptr->mx==curpos.x&&ptr->my==curpos.y&&visit[(curpos.x-38)/36][(curpos.y-38)/36]==0)
				return 1;
			ptr=ptr->next;
		}
return 0;
}

void MazePTwoPath()
{
SqStack S;
	InitStack(S);
	MissionPTwomap();
	int curstep;
	PosType start,curpos,end;
	SElemType e;
	
	memset(visit, 0, sizeof(visit));//��Ԫ��ȫ��Ϊ0
	//x==722&&y==362)x=290;y=542;
	curpos.x=290;
	curpos.y=542;
	curstep=1;
	end.x=722;
	end.y=362;
	do
	{
		if(PassPTwo(curpos))//�����ǰλ�ÿ���ͨ�� ����δ���߹�
		{
			FootPrint(curpos);//�����㼣
			e.ord=curstep;
			e.seat=curpos;
			
			e.di=1;
			Push(S,e);//����·��
			if((curpos.x==end.x)&&(curpos.y==end.y))
				break;
			curpos=NextPos(curpos,1);//��ǰλ�õ�����
				curstep++;
		
		}
		else
		{
			if(!StackEmpty(S))
			{
				Pop(S,e);//��ջ
				while(e.di==4&&(!StackEmpty(S)))
				{
					MakePrint(e.seat);
					Pop(S,e);
				}
				if(e.di<4)
				{
					e.di++;
					Push(S,e);
					curpos = NextPos(e.seat,e.di);
				}
			}
		}
	}while(!StackEmpty(S));

while(S.top!=S.base)
{
setfillcolor(BLACK);
fillcircle(290,542,10);
fillcircle(S.top->seat.x,S.top->seat.y,5);
--S.top;
}
	MOUSEMSG	m;
while(1)
	 {
		 m = GetMouseMsg();
		 switch(m.uMsg)
		 {
			 case  WM_LBUTTONDOWN://750,400,850,430);
				 if(m.x > 750 && m.x < 850 && m.y > 400 && m.y < 430)
				 {
					cleardevice();
					//putimage(0, 0, &img2);
					Choicepage();
					MazePathShow();
				 }
				 
		 }
	 }
	return ;
}
void MazePOnePath()
{
	SqStack S;
	InitStack(S);
	MissionPOnemap();
	int curstep;
	PosType start,curpos,end;
	SElemType e;
	
	memset(visit, 0, sizeof(visit));//��Ԫ��ȫ��Ϊ0
	//x==722&&y==290)x=38;y=146;
	curpos.x=38;
	curpos.y=146;
	curstep=1;
	end.x=722;
	end.y=290;
	do
	{
		if(PassPOne(curpos))//�����ǰλ�ÿ���ͨ�� ����δ���߹�
		{
			FootPrint(curpos);//�����㼣
			e.ord=curstep;
			e.seat=curpos;
			
			e.di=1;
			Push(S,e);//����·��
			if((curpos.x==end.x)&&(curpos.y==end.y))
				break;
			curpos=NextPos(curpos,1);//��ǰλ�õ�����
				curstep++;
		
		}
		else
		{
			if(!StackEmpty(S))
			{
				Pop(S,e);//��ջ
				while(e.di==4&&(!StackEmpty(S)))
				{
					MakePrint(e.seat);
					Pop(S,e);
				}
				if(e.di<4)
				{
					e.di++;
					Push(S,e);
					curpos = NextPos(e.seat,e.di);
				}
			}
		}
	}while(!StackEmpty(S));

while(S.top!=S.base)
{
setfillcolor(BLACK);
fillcircle(38,146,10);
fillcircle(S.top->seat.x,S.top->seat.y,5);
--S.top;
}
	MOUSEMSG	m;
while(1)
	 {
		 m = GetMouseMsg();
		 switch(m.uMsg)
		 {
			 case  WM_LBUTTONDOWN://750,400,850,430);
				 if(m.x > 750 && m.x < 850 && m.y > 400 && m.y < 430)
				 {
					cleardevice();
					//putimage(0, 0, &img2);
					Choicepage();
					MazePathShow();
				 }
				 
		 }
	 }
	return ;
}
void MazefourPath()
{
	SqStack S;
	InitStack(S);
	MissionFourmap();
	int curstep;
	PosType start,curpos,end;
	SElemType e;
	
	memset(visit, 0, sizeof(visit));//��Ԫ��ȫ��Ϊ0
	//x=38;y=38;//��������722  74
	curpos.x=38;
	curpos.y=38;
	curstep=1;
	end.x=722;
	end.y=74;
	do
	{
		if(PassFour(curpos))//�����ǰλ�ÿ���ͨ�� ����δ���߹�
		{
			FootPrint(curpos);//�����㼣
			e.ord=curstep;
			e.seat=curpos;
			
			e.di=1;
			Push(S,e);//����·��
			if((curpos.x==end.x)&&(curpos.y==end.y))
				break;
			curpos=NextPos(curpos,1);//��ǰλ�õ�����
				curstep++;
		
		}
		else
		{
			if(!StackEmpty(S))
			{
				Pop(S,e);//��ջ
				while(e.di==4&&(!StackEmpty(S)))
				{
					MakePrint(e.seat);
					Pop(S,e);
				}
				if(e.di<4)
				{
					e.di++;
					Push(S,e);
					curpos = NextPos(e.seat,e.di);
				}
			}
		}
	}while(!StackEmpty(S));

while(S.top!=S.base)
{
setfillcolor(BLACK);
fillcircle(38,38,10);
fillcircle(S.top->seat.x,S.top->seat.y,5);
--S.top;
}
	MOUSEMSG	m;
while(1)
	 {
		 m = GetMouseMsg();
		 switch(m.uMsg)
		 {
			 case  WM_LBUTTONDOWN://750,400,850,430);
				 if(m.x > 750 && m.x < 850 && m.y > 400 && m.y < 430)
				 {
					cleardevice();
					//putimage(0, 0, &img2);
					Choicepage();
					MazePathShow();
				 }
				 
		 }
	 }
	return ;
}
void MazeThreePath()
{
	SqStack S;
	InitStack(S);
	MissionThreemap();
	int curstep;
	PosType start,curpos,end;
	SElemType e;
	
	memset(visit, 0, sizeof(visit));//��Ԫ��ȫ��Ϊ0
	start.x=38;//x=38;y=74;//��������  722 362
	start.y=74;
	curpos.x=38;
	curpos.y=74;
	curstep=1;
	end.x=722;
	end.y=362;
	do
	{
		if(PassThree(curpos))//�����ǰλ�ÿ���ͨ�� ����δ���߹�
		{
			FootPrint(curpos);//�����㼣
			e.ord=curstep;
			e.seat=curpos;
			
			e.di=1;
			Push(S,e);//����·��
			if((curpos.x==end.x)&&(curpos.y==end.y))
				break;
			curpos=NextPos(curpos,1);//��ǰλ�õ�����
				curstep++;
		
		}
		else
		{
			if(!StackEmpty(S))
			{
				Pop(S,e);//��ջ
				while(e.di==4&&(!StackEmpty(S)))
				{
					MakePrint(e.seat);
					Pop(S,e);
				}
				if(e.di<4)
				{
					e.di++;
					Push(S,e);
					curpos = NextPos(e.seat,e.di);
				}
			}
		}
	}while(!StackEmpty(S));

while(S.top!=S.base)
{
setfillcolor(BLACK);
fillcircle(38,74,10);
fillcircle(S.top->seat.x,S.top->seat.y,5);
--S.top;
}
	MOUSEMSG	m;
while(1)
	 {
		 m = GetMouseMsg();
		 switch(m.uMsg)
		 {
			 case  WM_LBUTTONDOWN://750,400,850,430);
				 if(m.x > 750 && m.x < 850 && m.y > 400 && m.y < 430)
				 {
					cleardevice();
					//putimage(0, 0, &img2);
					Choicepage();
					MazePathShow();
				 }
				 
		 }
	 }
	return ;
}
void MazeTwoPath()
{
	SqStack S;
	InitStack(S);
	MissionTwomap();
	int curstep;
	PosType start,curpos,end;
	SElemType e;
	
	memset(visit, 0, sizeof(visit));//��Ԫ��ȫ��Ϊ0
	start.x=146;//x = 146;y = 38;//��������722  542
	start.y=38;
	curpos.x=146;
	curpos.y=38;
	curstep=1;
	end.x=722;
	end.y=542;
	do
	{
		if(PassTwo(curpos))//�����ǰλ�ÿ���ͨ�� ����δ���߹�
		{
			FootPrint(curpos);//�����㼣
			e.ord=curstep;
			e.seat=curpos;
			
			e.di=1;
			Push(S,e);//����·��
			if((curpos.x==end.x)&&(curpos.y==end.y))
				break;
			curpos=NextPos(curpos,1);//��ǰλ�õ�����
				curstep++;
		
		}
		else
		{
			if(!StackEmpty(S))
			{
				Pop(S,e);//��ջ
				while(e.di==4&&(!StackEmpty(S)))
				{
					MakePrint(e.seat);
					Pop(S,e);
				}
				if(e.di<4)
				{
					e.di++;
					Push(S,e);
					curpos = NextPos(e.seat,e.di);
				}
			}
		}
	}while(!StackEmpty(S));

while(S.top!=S.base)
{
setfillcolor(BLACK);
fillcircle(146,38,10);
fillcircle(S.top->seat.x,S.top->seat.y,5);
--S.top;
}
	MOUSEMSG	m;
while(1)
	 {
		 m = GetMouseMsg();
		 switch(m.uMsg)
		 {
			 case  WM_LBUTTONDOWN://750,400,850,430);
				 if(m.x > 750 && m.x < 850 && m.y > 400 && m.y < 430)
				 {
					cleardevice();
					//putimage(0, 0, &img2);
					Choicepage();
					MazePathShow();
				 }
				 
		 }
	 }
	return ;
}
void MazeOnePath()
{
	SqStack S;
	InitStack(S);
	MissionOnemap();
	int curstep;
	PosType start,curpos,end;
	SElemType e;
	
	memset(visit, 0, sizeof(visit));//��Ԫ��ȫ��Ϊ0
	start.x=38;//x = 38;y = 362
	start.y=362;
	curpos.x=38;
	curpos.y=362;
	curstep=1;
	end.x=722;
	end.y=290;
	do
	{
		if(Passone(curpos))//�����ǰλ�ÿ���ͨ�� ����δ���߹�
		{
			FootPrint(curpos);//�����㼣
			e.ord=curstep;
			e.seat=curpos;
			
			e.di=1;
			Push(S,e);//����·��
			if((curpos.x==end.x)&&(curpos.y==end.y))
				goto P;
			curpos=NextPos(curpos,1);//��ǰλ�õ�����
				curstep++;
		
		}
		else
		{
			if(!StackEmpty(S))
			{
				Pop(S,e);//��ջ
				while(e.di==4&&(!StackEmpty(S)))
				{
					MakePrint(e.seat);
					Pop(S,e);
				}
				if(e.di<4)
				{
					e.di++;
					Push(S,e);
					curpos = NextPos(e.seat,e.di);
				}
			}
		}
	}while(!StackEmpty(S));

P:while(S.top!=S.base)
{
setfillcolor(BLACK);
fillcircle(38,362,10);
fillcircle(S.top->seat.x,S.top->seat.y,5);
--S.top;
}
  	MOUSEMSG	m;
while(1)
	 {
		 m = GetMouseMsg();
		 switch(m.uMsg)
		 {
			 case  WM_LBUTTONDOWN://750,400,850,430);
				 if(m.x > 750 && m.x < 850 && m.y > 400 && m.y < 430)
				 {
					cleardevice();
					//putimage(0, 0, &img2);
					Choicepage();
					MazePathShow();
				 }
				 
		 }
	 }
	return ;

}

void MazePathShow()//ѡ�����·���ؿ�
{

	int i,j;
	MOUSEMSG m;
		setfillcolor(BLACK);
		fillrectangle(390,130,495,160);
		outtextxy(410,138,_T("��  ��  1"));
		fillrectangle(390,180,495,210);
		outtextxy(410,188,_T("��  ��  2"));
		fillrectangle(390,230,495,260);
		outtextxy(410,238,_T("��  ��  3"));
		fillrectangle(390,280,495,310);
		outtextxy(410,288,_T("��  ��  4"));
		fillrectangle(590,150,695,180);
		outtextxy(603,158,_T("�Զ���ؿ�1"));
		fillrectangle(590,200,695,230);
		outtextxy(603,208,_T("�Զ���ؿ�2"));
		fillrectangle(590,250,695,280);
		outtextxy(623,258,_T("��  ��"));
		
	while(1)	{
					m=GetMouseMsg();
					switch(m.uMsg)
					{
					case  WM_LBUTTONDOWN:
								if(m.x>390&&m.x<495&&m.y>130&&m.y<160)//�ؿ�1
								{
									cleardevice();
									MazeOnePath();
								}
								else
									if(m.x>390&&m.x<495&&m.y>180&&m.y<210)//�ؿ�2
									{
											cleardevice();
											MazeTwoPath();
									}
								else
									if(m.x>390&&m.x<495&&m.y>230&&m.y<260)//�ؿ�3
									{
											cleardevice();
											MazeThreePath();
									}
								else
									if(m.x>390&&m.x<495&&m.y>280&&m.y<310)//�ؿ�4
									{
											cleardevice();
											MazefourPath();//�ؿ�4  ��ͬ
									}
								else
									if(m.x>590&&m.x<695&&m.y>150&&m.y<180)//���˹ؿ�1
									{
											cleardevice();
											MazePOnePath();//���˹ؿ�1
									}
								else
									if(m.x>590&&m.x<695&&m.y>200&&m.y<230)//���˹ؿ�2
									{
											cleardevice();
											MazePTwoPath();//���˹ؿ�2
									}
								else
									if(m.x>590&&m.x<695&&m.y>250&&m.y<280)//����
									{
											 cleardevice();
											pageshow_();
									}
								break;
			}
		}
return;
}
void main()
{
	initgraph(1080,580);
	pageshow();
	//Missiononemap();
	//MazePath();
	hide();
	 getch();
	closegraph();
}