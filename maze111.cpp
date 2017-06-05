/*3、走迷宫游戏
程序开始运行时显示一个迷宫地图，迷宫中央有一只老鼠，迷宫的右下方有一个粮仓。游戏的任务是使用键盘上的方向键操纵老鼠在规定的时间内走到粮仓处。
要求：1) 老鼠形象可辨认，可用键盘操纵老鼠上下左右移动；
2) 迷宫的墙足够结实，老鼠不能穿墙而过；
3) 正确检测结果，若老鼠在规定时间内走到粮仓处，提示成功，否则提示失败；
4) 添加编辑迷宫功能，可修改当前迷宫，修改内容：墙变路、路变墙；
5) 找出走出迷宫的所有路径，以及最短路径。利用序列化功能实现迷宫地图文件的存盘和读出等功能。
*/
#include"graphics.h"
#include"windows.h"
#include"conio.h"
#include"stdlib.h"
#include"stdio.h"
#define  UP 0x48//上
#define  DOWN 0x50//下
#define  LEFT 0x4b//左
#define  RIGHT 0x4d//右
#define  ESC   0x1b//ESC
#define  STACK_INT_SIZE  100
#define  STACKINCREMENT   10
#define  TURE   1
#define  FALSE  0
#define  OK     1
#define  OVERFLOW  -1
struct xydata{//储存迷宫数据的结构体
int mx;
int my;
struct xydata *next;
};

typedef struct{//储存当前坐标
int x;
int y;
}PosType;

typedef struct{//栈的元素类型
	int ord;
	PosType seat;
	int di;
}SElemType;

typedef struct{//栈的结构

	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

SqStack S;//栈S

struct xydata  *head1,*head2,*head3,*head4,*personal1,*personal2;//四个默认关卡和两个自定义关卡
IMAGE img;
int visit[20][15];
void pageshow_();//用于界面显示的函数
void Choice();//选择闯关的函数
void ChangeMaze();//选择修改迷宫的函数
void Choicepage();//选择闯关的函数的 界面
void Quitgame();//退出游戏相关函数
void Quitgame_();//退出游戏相关函数
int  colorflag;//颜色标志
int  timeflag;//时间标志
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
void SaveFile()//将数据存入文件的函数
{
	FILE *fp1;
			fp1 = (fopen("link_list1","wb"));//以二进制保存文件
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
			fp2 = (fopen("link_list2","wb"));//以二进制保存文件
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
			fp3 = (fopen("link_list3","wb"));//以二进制保存文件
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
			fp4 = (fopen("link_list4","wb"));//以二进制保存文件
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

	
	
		
			fp5 = (fopen("link_list5","wb"));//以二进制保存文件
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
			fp6 = (fopen("link_list6","wb"));//以二进制保存文件
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
void SaveData()//将迷宫数据储存在链表当中
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
void Changeone()//修改第一关
{	
	FILE *fp;
	int n=0;
	float mx,my;
	float x,j=220,y,i,ch;
	COLORREF color = WHITE;
	MOUSEMSG m;
	struct xydata *p1,*p2;
	setlinecolor(WHITE);
	outtextxy(800,100,_T("上下左右移动"));
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
	outtextxy(760,408,_T("返       回"));
	rectangle(750,450,850,480);
	outtextxy(760,458,_T("保       存"));
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
				{//用白颜色涂色
					setfillcolor(RGB(254,255,255));
					colorflag = 1;
				}
				else
				if(m.y > 250 && m.y < 350 && m.x > 750 && m.x < 850)
				{//用红颜色涂色
				setfillcolor(RED);
				colorflag = 2;
				}
				else 
					if(m.x > 750&&m.x < 850&&m.y > 450&&m.y < 480)//保存
						SaveData();
				else
					if(m.x > 750&&m.x < 850&&m.y > 400&&m.y < 430)//750,450,850,480返回
						{
							cleardevice();
							Choicepage();
							ChangeMaze();	
						}
				else 
					if(getpixel(m.x,m.y) == RGB(254,255,255) || getpixel(m.x,m.y) == RED)//涂色
				{
					setfillcolor(BLACK);
					floodfill(m.x,m.y,color);
				}
				else
				{
					if(colorflag == 1)//用白色填涂
					{
						setfillcolor(RGB(254,255,255));
						floodfill(m.x,m.y,color);
					}
				else
					if(colorflag == 2)//用红色填涂
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
	outtextxy(800,100,_T("上下左右移动"));
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
	outtextxy(760,408,_T("返       回"));
	rectangle(750,450,850,480);
	outtextxy(760,458,_T("保       存"));
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
			{//用白颜色涂色
				setfillcolor(RGB(254,255,255));
				colorflag = 1;
			}
			else
				if(m.y>250 && m.y<350 && m.x > 750 && m.x < 850)
				{//用红颜色涂色
					setfillcolor(RED);
					colorflag = 2;
				}
				else 
					if(m.x > 750 && m.x < 850 && m.y > 450 && m.y < 480)//保存
						SaveDatatwo();
				else
					if( m.x > 750 && m.x < 850 && m.y > 400 && m.y < 430)//750,450,850,480返回
					{
						cleardevice();
						Choicepage();
						ChangeMaze();	
					}
				else 
					if(getpixel(m.x,m.y) == RGB(254,255,255) || getpixel(m.x,m.y) == RED)//涂色
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
	outtextxy(800,100,_T("上下左右移动"));
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
		outtextxy(760,408,_T("返       回"));
		rectangle(750,450,850,480);
		outtextxy(760,458,_T("保       存"));
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
			{//用白颜色涂色
				setfillcolor(RGB(254,255,255));
				colorflag=1;
			}
			else
				if(m.y > 250 && m.y  < 350 && m.x > 750 && m.x < 850)
				{//用红颜色涂色
					setfillcolor(RED);
					colorflag=2;
				}
			else 
				if(m.x > 750 && m.x < 850 && m.y > 450 && m.y < 480)//保存
					SaveDatathree();
			else
				if(m.x > 750 && m.x < 850 && m.y > 400 && m.y < 430)//750,450,850,480返回
				{
					cleardevice();
					Choicepage();
					ChangeMaze();
				}
			else 
				if(getpixel(m.x,m.y) == RGB(254,255,255) || getpixel(m.x,m.y) == RED)//涂色
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
	outtextxy(800,100,_T("上下左右移动"));
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
	outtextxy(760,408,_T("返       回"));
	rectangle(750,450,850,480);
	outtextxy(760,458,_T("保       存"));
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
				{//用白颜色涂色
					setfillcolor(RGB(254,255,255));
					colorflag = 1;
				}
				else
					if(m.y > 250 && m.y < 350 && m.x > 750 && m.x < 850)
					{//用红颜色涂色
					setfillcolor(RED);
					colorflag = 2;
					}
				else 
					if(m.x > 750 && m.x < 850 && m.y > 450 && m.y < 480)//保存
						SaveDatafour();
				else
					if(m.x > 750 && m.x < 850 && m.y > 400 && m.y < 430)//750,450,850,480返回
					{
						cleardevice();
						Choicepage();
						ChangeMaze();		
					}
				else 
					if(getpixel(m.x,m.y) == RGB(254,255,255) || getpixel(m.x,m.y) == RED)//涂色
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
	outtextxy(800,100,_T("上下左右移动"));
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
	outtextxy(760,408,_T("返       回"));
	rectangle(750,450,850,480);
	outtextxy(760,458,_T("保       存"));
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
		{//用白颜色涂色
			setfillcolor(RGB(254,255,255));
			colorflag = 1;
		}
		else
			if(m.y > 250 && m.y < 350 && m.x > 750 && m.x < 850)
			{//用红颜色涂色
			setfillcolor(RED);
			colorflag = 2;
			}
			else 
				if(m.x > 750 && m.x < 850 && m.y > 450 && m.y < 480)//保存
					SaveDataPersonalOne();
				else
					if(m.x > 750 && m.x < 850 && m.y > 400 && m.y < 430)//750,450,850,480返回
					{
						cleardevice();
						Choicepage();
						ChangeMaze();
					}
			else if(getpixel(m.x,m.y) == RGB(254,255,255) || getpixel(m.x,m.y) == RED)//涂色
			{
				setfillcolor(BLACK);//如果当前颜色是黑色则用所选颜色填涂如果不是黑色则用黑色填涂
				floodfill(m.x,m.y,color);
			}
			else
			{
				if(colorflag==1)//如果colorflag==1则用白色填涂
				{
					setfillcolor(RGB(254,255,255));
					floodfill(m.x,m.y,color);
				}
				else
					if(colorflag==2)//如果colorflag==2则用红色填涂
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
	outtextxy(800,100,_T("上下左右移动"));
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
		outtextxy(760,408,_T("返       回"));
		rectangle(750,450,850,480);
		outtextxy(760,458,_T("保       存"));
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
		{//用白颜色涂色
			setfillcolor(RGB(254,255,255));
			colorflag = 1;
		}
		else
			if(m.y > 250 && m.y < 350 && m.x > 750 && m.x < 850)
			{//用红颜色涂色
			setfillcolor(RED);
			colorflag = 2;
			}
			else 
				if(m.x > 750 && m.x < 850 && m.y > 450 && m.y < 480)//保存
					SaveDataPersonalTwo();
				else
					if(m.x>750&&m.x<850&&m.y>400&&m.y<430)//750,450,850,480返回
					{
						cleardevice();
						Choicepage();
						ChangeMaze();
					}
			else if(getpixel(m.x,m.y) == RGB(254,255,255) || getpixel(m.x,m.y) == RED)//涂色
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
void Choicepage()//选择闯关关卡的界面函数
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
void ChangeMaze()//选择修改关卡
{
	MOUSEMSG m;
		setfillcolor(BLACK);
		fillrectangle(390,130,495,160);
		outtextxy(410,138,_T("关  卡  1"));
		fillrectangle(390,180,495,210);
		outtextxy(410,188,_T("关  卡  2"));
		fillrectangle(390,230,495,260);
		outtextxy(410,238,_T("关  卡  3"));
		fillrectangle(390,280,495,310);
		outtextxy(410,288,_T("关  卡  4"));
		fillrectangle(590,150,695,180);
		outtextxy(603,158,_T("自定义关卡1"));
		fillrectangle(590,200,695,230);
		outtextxy(603,208,_T("自定义关卡2"));
		fillrectangle(590,250,695,280);
		outtextxy(623,258,_T("返  回"));
		while(1)
		{
			m = GetMouseMsg();
			switch(m.uMsg)
			{
			case  WM_LBUTTONDOWN:
								if(m.x > 390 && m.x < 495 && m.y > 130 && m.y < 160)//关卡1
								{
									cleardevice();
									Changeone();
								}
								else
									if(m.x > 390 && m.x < 495 && m.y > 180 && m.y < 210)//关卡2
								{
									cleardevice();
									Changetwo();
								}
								else
									if(m.x > 390 && m.x < 495 && m.y > 230 && m.y < 260)//修改关卡3
								{
									cleardevice();
									Changethree();
								}
								else
									if(m.x > 390 && m.x < 495 && m.y > 280 && m.y < 310)//修改关卡4
								{
									cleardevice();
									Changefour();
								}
								else
									if(m.x > 590 && m.x < 695 && m.y > 150 && m.y < 180)//修改个人关卡1
								{
									cleardevice();
									ChangePensonalOne();
								}
								else
									if(m.x > 590 && m.x < 695 && m.y > 200 && m.y < 230)//修改个人关卡2
								{
									cleardevice();
									ChangePensonalTwo();
								}
								else
									if(m.x > 590 && m.x < 695 && m.y > 250 && m.y < 280)//返回
								{
									cleardevice();
									pageshow_();
								}
								break;
			}
		}
}
void Mission()//第一关
{
	int x,y,ch;
	char time[10],t=0;
	struct xydata *p1,*p2;
	COLORREF color=WHITE;
	MOUSEMSG	m;
	FILE *fp;
	timeflag=0;
	setlinecolor(WHITE);
	outtextxy(750,100,_T("上下左右移动  时间限制：20s"));
	outtextxy(750,290,_T("---->出口"));
	outtextxy(750,180,_T("开始时间"));
	outtextxy(850,180,_T("结束时间"));
	outtextxy(950,180,_T("用时"));
//	setwritemode(R2_XORPEN);
	for(x=20;x<=740;x+=36)
		line(x,20,x,560);
	for(y=20;y<=560;y+=36)
		line(20,y,740,y);
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("返       回"));
	rectangle(750,450,850,480);
	outtextxy(760,458,_T("重 新 闯 关"));
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
	x = 38;y = 362;//初始点
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
		if(x == 722 && y == 290)//终点
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
					outtextxy(835,260,_T("闯关成功"));
			}
			else
					outtextxy(835,260,_T("闯关失败"));
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
	outtextxy(750,100,_T("上下左右移动  时间限制：15s"));
	outtextxy(750,180,_T("开始时间"));
	outtextxy(850,180,_T("结束时间"));
	outtextxy(950,180,_T("用时"));
//	setwritemode(R2_XORPEN);
	for(x=20;x<=740;x+=36)
		line(x,20,x,560);
	for(y=20;y<=560;y+=36)
		line(20,y,740,y);
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("返       回"));
	rectangle(750,450,850,480);
	outtextxy(760,458,_T("重 新 闯 关"));
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
	x = 146;y = 38;//出口坐标722  542
	outtextxy(752,542,_T("---->出口"));
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
					outtextxy(835,260,_T("闯关成功"));
			}
			else
					outtextxy(835,260,_T("闯关失败"));
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
	outtextxy(750,100,_T("上下左右移动  时间限制：15s"));
	
	outtextxy(750,180,_T("开始时间"));
		outtextxy(850,180,_T("结束时间"));
		outtextxy(950,180,_T("用时"));
//	setwritemode(R2_XORPEN);
	for(x=20;x<=740;x+=36)
		line(x,20,x,560);
	for(y=20;y<=560;y+=36)
		line(20,y,740,y);
		
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("返       回"));
	rectangle(750,450,850,480);
	outtextxy(760,458,_T("重 新 闯 关"));
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
		x=38;y=74;//出口坐标  722 352
		outtextxy(752,362,_T("---->出口"));
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
					outtextxy(835,260,_T("闯关成功"));
			}
			else
					outtextxy(835,260,_T("闯关失败"));
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
	outtextxy(750,100,_T("上下左右移动  时间限制：15s"));
	
	outtextxy(750,180,_T("开始时间"));
		outtextxy(850,180,_T("结束时间"));
		outtextxy(950,180,_T("用时"));
//	setwritemode(R2_XORPEN);
	for(x=20;x<=740;x+=36)
		line(x,20,x,560);
	for(y=20;y<=560;y+=36)
		line(20,y,740,y);
		
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("返       回"));
	rectangle(750,450,850,480);
	outtextxy(760,458,_T("重 新 闯 关"));
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
		x=38;y=38;//出口坐标722  74
	outtextxy(752,74,_T("---->出口"));
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
		if(x==722&&y==74)//如果到达出口则停止计时 输出所用时间 
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
					outtextxy(835,260,_T("闯关成功"));
			}
			else
					outtextxy(835,260,_T("闯关失败"));
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
					 cleardevice();//清屏
						//putimage(0, 0, &img2);
					Choicepage();//选择闯关关卡界面
						Choice();//选择闯关关卡
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
void MissionPersonalOne()//自定义关卡1
{
		int x,y,ch;
	struct xydata *p1,*p2;
	COLORREF color=WHITE;//设定白色为填充色
	MOUSEMSG	m;
	char time[10],t=0;
	timeflag=0;
	SYSTEMTIME BT,ET;
		FILE *fp5;
	setlinecolor(WHITE);
	outtextxy(800,100,_T("上下左右移动"));
	
	outtextxy(750,290,_T("---->出口"));
	outtextxy(750,180,_T("开始时间"));
		outtextxy(850,180,_T("结束时间"));
		outtextxy(950,180,_T("用时"));
//	setwritemode(R2_XORPEN);
	for(x=20;x<=740;x+=36)
		line(x,20,x,560);
	for(y=20;y<=560;y+=36)
		line(20,y,740,y);
		
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("返       回"));
	rectangle(750,450,850,480);
	outtextxy(760,458,_T("重 新 闯 关"));
		fp5=(fopen("link_list5","rb"));//读取数据建立链表，储存迷宫数据
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
					outtextxy(835,260,_T("闯关成功"));
			}
			else
					outtextxy(835,260,_T("闯关失败"));
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
	outtextxy(800,100,_T("上下左右移动"));
	
	outtextxy(750,180,_T("开始时间"));
		outtextxy(850,180,_T("结束时间"));
		outtextxy(950,180,_T("用时"));
//	setwritemode(R2_XORPEN);
	for(x=20;x<=740;x+=36)
		line(x,20,x,560);
	for(y=20;y<=560;y+=36)
		line(20,y,740,y);
		
	rectangle(750,400,850,430);
	outtextxy(760,408,_T("返       回"));
	rectangle(750,450,850,480);
	outtextxy(760,458,_T("重 新 闯 关"));
		fp6=(fopen("link_list6","rb"));//读取文件建立链表，将数据转化成迷宫的道路
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
		outtextxy(752,362,_T("---->出口"));
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
			if(timeflag==0)//确保第一次移动的时候开始计时
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
		
			itoa(ET.wHour, time, 10);//将时间转换成字符串输出函数
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
					outtextxy(835,260,_T("闯关成功"));
			}
			else
					outtextxy(835,260,_T("闯关失败"));
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
					Choicepage();//选择闯关关卡的界面显示函数
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
void Choice()//选择闯关关卡
{
	int i,j;
	MOUSEMSG m;
		setfillcolor(BLACK);
		fillrectangle(390,130,495,160);
		outtextxy(410,138,_T("关  卡  1"));
		fillrectangle(390,180,495,210);
		outtextxy(410,188,_T("关  卡  2"));
		fillrectangle(390,230,495,260);
		outtextxy(410,238,_T("关  卡  3"));
		fillrectangle(390,280,495,310);
		outtextxy(410,288,_T("关  卡  4"));
		fillrectangle(590,150,695,180);
		outtextxy(603,158,_T("自定义关卡1"));
		fillrectangle(590,200,695,230);
		outtextxy(603,208,_T("自定义关卡2"));
		fillrectangle(590,250,695,280);
		outtextxy(623,258,_T("返  回"));
		
	while(1)	{
			m=GetMouseMsg();
			switch(m.uMsg)
			{
			case  WM_LBUTTONDOWN:
								if(m.x>390&&m.x<495&&m.y>130&&m.y<160)//关卡1
								{
									cleardevice();
									Mission();
								}
								else
									if(m.x>390&&m.x<495&&m.y>180&&m.y<210)//关卡2
									{
											cleardevice();
											Missiontwo();
									}
								else
									if(m.x>390&&m.x<495&&m.y>230&&m.y<260)//关卡3
									{
											cleardevice();
											Missionthree();
									}
								else
									if(m.x>390&&m.x<495&&m.y>280&&m.y<310)//关卡4
									{
											cleardevice();
											Missionfour();//关卡4  上同
									}
								else
									if(m.x>590&&m.x<695&&m.y>150&&m.y<180)//个人关卡1
									{
											cleardevice();
											MissionPersonalOne();//个人关卡1
									}
								else
									if(m.x>590&&m.x<695&&m.y>200&&m.y<230)//个人关卡2
									{
											cleardevice();
											MissionPersonalTwo();//个人关卡2
									}
								else
									if(m.x>590&&m.x<695&&m.y>250&&m.y<280)//返回
									{
											 cleardevice();
											pageshow_();
									}
								break;
			}
		}
}
void GameIntr()//游戏介绍函数
{
	MOUSEMSG m;
	outtextxy(340,130,_T("闯关模式：共有四关，在时间限制内完成即可通关。"));
	outtextxy(340,150,_T("修改迷宫：可以修改四个关卡，将墙变路，将路变墙,"));
	outtextxy(420,170,_T("点击右侧颜色区域即可修改。"));
	outtextxy(340,190,_T("最短路径：可以求得通关路径和最短路径。"));
	outtextxy(340,210,_T("退出游戏：点击即可退出游戏。"));
	outtextxy(340,270,_T("制作团队：康勇，邓秀文，李晋"));
	fillrectangle(640,300,745,330);
	outtextxy(655,310,_T("返          回"));
	while(1)
	{
			m=GetMouseMsg();
			switch(m.uMsg)
			{
				case  WM_LBUTTONDOWN:
							if(m.x>640&&m.x<745&&m.y>300&&m.y<330)//返回
							{
								 cleardevice();//清屏语句
								 pageshow_();//主界面显示
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
	outtextxy(510,108,_T("闯关模式"));
	fillrectangle(490,150,595,180);
	outtextxy(510,158,_T("修改迷宫"));
	fillrectangle(490,200,595,230);
	outtextxy(510,208,_T("通关路径"));
	fillrectangle(490,250,595,280);
	outtextxy(510,258,_T("游戏介绍"));
	fillrectangle(490,300,595,330);
	outtextxy(510,308,_T("退出游戏"));

	while(1)
	{
		m=GetMouseMsg();
		switch(m.uMsg)
		{
		case WM_LBUTTONDOWN:
			if(m.x>490&&m.x<595&&m.y>100&&m.y<130)//闯关模式
			{
				for(i=542.5,j=225;i>=320,j>=100;i-=1.88,j--)
				{
					fillrectangle(i,j,542.5-i+542.5,225-j+225);
					Sleep(1);
				}
				Choice();	
			}
			else
				if(m.x>490&&m.x<595&&m.y>150&&m.y<180)//修改迷宫
				{
					for(i=542.5,j=225;i>=320,j>=100;i-=1.88,j--)
						{
							fillrectangle(i,j,542.5-i+542.5,225-j+225);
							Sleep(1);
						}
					ChangeMaze();
				}
				else
					if(m.x>490&&m.x<595&&m.y>250&&m.y<280)//游戏介绍
					{
						for(i=542.5,j=225;i>=320,j>=100;i-=1.88,j--)
							{
								fillrectangle(i,j,542.5-i+542.5,225-j+225);
								Sleep(1);
							}
							GameIntr();
						}
					else
						if(m.x>490&&m.x<595&&m.y>300&&m.y<330)//退出游戏490,300,595,330
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
					if(m.x>490&&m.x<595&&m.y>200&&m.y<230)//最短路径490,200,595,230
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
	outtextxy(510,108,_T("闯关模式"));
	fillrectangle(490,150,595,180);
	outtextxy(510,158,_T("修改迷宫"));
	fillrectangle(490,200,595,230);
	outtextxy(510,208,_T("通关路径"));
	fillrectangle(490,250,595,280);
	outtextxy(510,258,_T("游戏介绍"));
	fillrectangle(490,300,595,330);
	outtextxy(510,308,_T("退出游戏"));
while(1)
	{
		m=GetMouseMsg();
		switch(m.uMsg)
		{
		case WM_LBUTTONDOWN:
			if(m.x>490&&m.x<595&&m.y>100&&m.y<130)//闯关模式
			{
			for(i=542.5,j=225;i>=320,j>=100;i-=1.88,j--)
				{
					fillrectangle(i,j,542.5-i+542.5,225-j+225);
					Sleep(1);
				}
				Choice();//选择闯关函数
				
				
			}
			else
				if(m.x>490&&m.x<595&&m.y>150&&m.y<180)//修改迷宫
				{
					for(i=542.5,j=225;i>=320,j>=100;i-=1.88,j--)
						{
							fillrectangle(i,j,542.5-i+542.5,225-j+225);
							Sleep(1);
						}
						ChangeMaze();//选择修改迷宫函数
					}
				else
					if(m.x>490&&m.x<595&&m.y>250&&m.y<280)//游戏介绍
					{
						for(i=542.5,j=225;i>=320,j>=100;i-=1.88,j--)
						{
							fillrectangle(i,j,542.5-i+542.5,225-j+225);
							Sleep(1);
						}
						GameIntr();//游戏介绍
					}
					else
				if(m.x>490&&m.x<595&&m.y>300&&m.y<330)//退出游戏490,300,595,330
				{
					
					for(i=320,j=100;i<=542.5,j<=225;i+=1.88,j++)
					
						{setfillcolor(BLACK);//设置黑色为填充色
							
							fillrectangle(i,j,542.5-i+542.5,225-j+225);
							Sleep(2);
						}
						cleardevice();
						Quitgame_();//退出游戏界面函数
						Quitgame();//退出游戏界面函数
					}
				else
					if(m.x>490&&m.x<595&&m.y>200&&m.y<230)//最短路径490,200,595,230
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
	COLORREF color=WHITE;//以白色为填充色
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
/*typedef struct{//储存当前坐标
int x;
int y;
}PosType;

typedef struct{//栈的结构

	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;


typedef struct{//栈的元素类型
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
	case 1:curpos.x-=36;break;//左邻
	case 2:curpos.x+=36;break;//右临
	case 3:curpos.y-=36;break;//上邻
	case 4:curpos.y+=36;break;//下邻
	}
	return curpos;
}

 void  Pop(SqStack &S,SElemType &e)
 {
	 //if(S.top == S.base)
		// r;//!!!!!
		e=*--S.top;//删除栈顶并返回当前栈顶元素
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
	outtextxy(760,408,_T("返       回"));
	outtextxy(750,290,_T("---->出口"));
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
	outtextxy(760,408,_T("返       回"));
	outtextxy(752,362,_T("---->出口"));

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
	outtextxy(760,408,_T("返       回"));
	outtextxy(750,290,_T("---->出口"));
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
	outtextxy(760,408,_T("返       回"));
	outtextxy(752,74,_T("---->出口"));
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
	outtextxy(760,408,_T("返       回"));
		outtextxy(752,362,_T("---->出口"));
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
	outtextxy(760,408,_T("返       回"));
	outtextxy(752,542,_T("---->出口"));
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
	
	memset(visit, 0, sizeof(visit));//将元素全置为0
	//x==722&&y==362)x=290;y=542;
	curpos.x=290;
	curpos.y=542;
	curstep=1;
	end.x=722;
	end.y=362;
	do
	{
		if(PassPTwo(curpos))//如果当前位置可以通过 并且未曾走过
		{
			FootPrint(curpos);//留下足迹
			e.ord=curstep;
			e.seat=curpos;
			
			e.di=1;
			Push(S,e);//加入路径
			if((curpos.x==end.x)&&(curpos.y==end.y))
				break;
			curpos=NextPos(curpos,1);//当前位置的左邻
				curstep++;
		
		}
		else
		{
			if(!StackEmpty(S))
			{
				Pop(S,e);//出栈
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
	
	memset(visit, 0, sizeof(visit));//将元素全置为0
	//x==722&&y==290)x=38;y=146;
	curpos.x=38;
	curpos.y=146;
	curstep=1;
	end.x=722;
	end.y=290;
	do
	{
		if(PassPOne(curpos))//如果当前位置可以通过 并且未曾走过
		{
			FootPrint(curpos);//留下足迹
			e.ord=curstep;
			e.seat=curpos;
			
			e.di=1;
			Push(S,e);//加入路径
			if((curpos.x==end.x)&&(curpos.y==end.y))
				break;
			curpos=NextPos(curpos,1);//当前位置的左邻
				curstep++;
		
		}
		else
		{
			if(!StackEmpty(S))
			{
				Pop(S,e);//出栈
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
	
	memset(visit, 0, sizeof(visit));//将元素全置为0
	//x=38;y=38;//出口坐标722  74
	curpos.x=38;
	curpos.y=38;
	curstep=1;
	end.x=722;
	end.y=74;
	do
	{
		if(PassFour(curpos))//如果当前位置可以通过 并且未曾走过
		{
			FootPrint(curpos);//留下足迹
			e.ord=curstep;
			e.seat=curpos;
			
			e.di=1;
			Push(S,e);//加入路径
			if((curpos.x==end.x)&&(curpos.y==end.y))
				break;
			curpos=NextPos(curpos,1);//当前位置的左邻
				curstep++;
		
		}
		else
		{
			if(!StackEmpty(S))
			{
				Pop(S,e);//出栈
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
	
	memset(visit, 0, sizeof(visit));//将元素全置为0
	start.x=38;//x=38;y=74;//出口坐标  722 362
	start.y=74;
	curpos.x=38;
	curpos.y=74;
	curstep=1;
	end.x=722;
	end.y=362;
	do
	{
		if(PassThree(curpos))//如果当前位置可以通过 并且未曾走过
		{
			FootPrint(curpos);//留下足迹
			e.ord=curstep;
			e.seat=curpos;
			
			e.di=1;
			Push(S,e);//加入路径
			if((curpos.x==end.x)&&(curpos.y==end.y))
				break;
			curpos=NextPos(curpos,1);//当前位置的左邻
				curstep++;
		
		}
		else
		{
			if(!StackEmpty(S))
			{
				Pop(S,e);//出栈
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
	
	memset(visit, 0, sizeof(visit));//将元素全置为0
	start.x=146;//x = 146;y = 38;//出口坐标722  542
	start.y=38;
	curpos.x=146;
	curpos.y=38;
	curstep=1;
	end.x=722;
	end.y=542;
	do
	{
		if(PassTwo(curpos))//如果当前位置可以通过 并且未曾走过
		{
			FootPrint(curpos);//留下足迹
			e.ord=curstep;
			e.seat=curpos;
			
			e.di=1;
			Push(S,e);//加入路径
			if((curpos.x==end.x)&&(curpos.y==end.y))
				break;
			curpos=NextPos(curpos,1);//当前位置的左邻
				curstep++;
		
		}
		else
		{
			if(!StackEmpty(S))
			{
				Pop(S,e);//出栈
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
	
	memset(visit, 0, sizeof(visit));//将元素全置为0
	start.x=38;//x = 38;y = 362
	start.y=362;
	curpos.x=38;
	curpos.y=362;
	curstep=1;
	end.x=722;
	end.y=290;
	do
	{
		if(Passone(curpos))//如果当前位置可以通过 并且未曾走过
		{
			FootPrint(curpos);//留下足迹
			e.ord=curstep;
			e.seat=curpos;
			
			e.di=1;
			Push(S,e);//加入路径
			if((curpos.x==end.x)&&(curpos.y==end.y))
				goto P;
			curpos=NextPos(curpos,1);//当前位置的左邻
				curstep++;
		
		}
		else
		{
			if(!StackEmpty(S))
			{
				Pop(S,e);//出栈
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

void MazePathShow()//选择最短路径关卡
{

	int i,j;
	MOUSEMSG m;
		setfillcolor(BLACK);
		fillrectangle(390,130,495,160);
		outtextxy(410,138,_T("关  卡  1"));
		fillrectangle(390,180,495,210);
		outtextxy(410,188,_T("关  卡  2"));
		fillrectangle(390,230,495,260);
		outtextxy(410,238,_T("关  卡  3"));
		fillrectangle(390,280,495,310);
		outtextxy(410,288,_T("关  卡  4"));
		fillrectangle(590,150,695,180);
		outtextxy(603,158,_T("自定义关卡1"));
		fillrectangle(590,200,695,230);
		outtextxy(603,208,_T("自定义关卡2"));
		fillrectangle(590,250,695,280);
		outtextxy(623,258,_T("返  回"));
		
	while(1)	{
					m=GetMouseMsg();
					switch(m.uMsg)
					{
					case  WM_LBUTTONDOWN:
								if(m.x>390&&m.x<495&&m.y>130&&m.y<160)//关卡1
								{
									cleardevice();
									MazeOnePath();
								}
								else
									if(m.x>390&&m.x<495&&m.y>180&&m.y<210)//关卡2
									{
											cleardevice();
											MazeTwoPath();
									}
								else
									if(m.x>390&&m.x<495&&m.y>230&&m.y<260)//关卡3
									{
											cleardevice();
											MazeThreePath();
									}
								else
									if(m.x>390&&m.x<495&&m.y>280&&m.y<310)//关卡4
									{
											cleardevice();
											MazefourPath();//关卡4  上同
									}
								else
									if(m.x>590&&m.x<695&&m.y>150&&m.y<180)//个人关卡1
									{
											cleardevice();
											MazePOnePath();//个人关卡1
									}
								else
									if(m.x>590&&m.x<695&&m.y>200&&m.y<230)//个人关卡2
									{
											cleardevice();
											MazePTwoPath();//个人关卡2
									}
								else
									if(m.x>590&&m.x<695&&m.y>250&&m.y<280)//返回
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