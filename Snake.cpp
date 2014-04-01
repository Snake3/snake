#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
using namespace std;
#define COUT cout<<"■"
struct Body
{
	int x,y;
	Body *next;
};
int Food=0,Food_x,Food_y,Direction=4,Grade,Score=0;
Body *body001=new Body[sizeof(Body)];

class posi
{
public:
	void Position(int, int);
};
void posi::Position(int x,int y)
{
	COORD pos= {y-1,x-1};
	HANDLE Out=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Out,pos);
}



class Prt
{
public:
	void Prt_Map();
	void Prt_Sneak();
};
void Prt::Prt_Map()
{
	int i;
	posi *posit;
	//画横
	for(i=1; i<=80; i+=2)
	{
		posit->Position(1,i);
		COUT;
		posit->Position(24,i);
		COUT;
	}//x:2~23 共22个
	//画竖
	for(i=1; i<=24; i++)
	{
		posit->Position(i,1);
		COUT;
		posit->Position(i,57);
		COUT;//y:3~55共27个
		posit->Position(i,79);
		COUT;
	}
}
void Prt::Prt_Sneak()
{
	Body *p;
	posi *posit;
	p=body001;
	posit->Position(p->x,p->y);
	cout<<"H";
	p=p->next;
	while(p!=NULL)
	{
		posit->Position(p->x,p->y);
		cout<<"X";
		p=p->next;
	}
	posit->Position(Food_x,Food_y);
	cout<<"⊙";
	posit->Position(7,63);
	cout<<"Score: "<<Score;
	posit->Position(10,63);
	cout<<"Grade: "<<Grade;
}

class Food_Snake
{
public:
	void Creat_Food();
};
void Food_Snake::Creat_Food()
{
	if(Food==0)
	{
		srand((int)time(0));
		Food_x=rand()%21+2;
		int temp=rand()%52+3;
		if(temp%2==0)
			Food_y=temp+1;
		else Food_y=temp;
		Food=1;
	}
}

class Movemant
{
public:
	void Move();
};
void Movemant::Move()
{
	Body *p=new Body[sizeof(Body)],*q,*temp=new Body[sizeof(Body)];
	posi *posit;
	//方向：w,上
	if(Direction==1)
	{
		//吃食物
		if(body001->x==(Food_x+1)&&body001->y==Food_y)
		{
			temp->x=Food_x;
			temp->y=Food_y;
			temp->next=body001;
			body001=temp;
			Food=0;
			Score+=5;
		}
		//没吃食物，没撞墙没撞自己时
		else
		{
			temp->x=body001->x-1;
			temp->y=body001->y;
			temp->next=body001;
			body001=temp;
			q=body001;
			while((q->next)->next!=NULL)q=q->next;
			posit->Position((q->next)->x,(q->next)->y);
			//移动过后的尾节点p的next设置为空字符串
			//然后删除，置空
			cout<<" ";
			delete(q->next);
			q->next=NULL;
		}
	}
	if(Direction==2)
	{
		if(body001->x==Food_x&&body001->y==(Food_y+2))
		{
			temp->x=Food_x;
			temp->y=Food_y;
			temp->next=body001;
			body001=temp;
			Food=0;
			Score+=5;
		}
		else
		{
			temp->x=body001->x;
			temp->y=body001->y-2;
			temp->next=body001;
			body001=temp;
			q=body001;
			while((q->next)->next!=NULL)q=q->next;
			posit->Position((q->next)->x,(q->next)->y);
			cout<<" ";
			delete(q->next);
			q->next=NULL;
		}
	}
	if(Direction==3)
	{
		if(body001->x==(Food_x-1)&&body001->y==Food_y)
		{
			temp->x=Food_x;
			temp->y=Food_y;
			temp->next=body001;
			body001=temp;
			Food=0;
			Score+=5;
		}
		else
		{
			temp->x=body001->x+1;
			temp->y=body001->y;
			temp->next=body001;
			body001=temp;
			q=body001;
			while((q->next)->next!=NULL)q=q->next;
			posit->Position((q->next)->x,(q->next)->y);
			cout<<" ";
			delete(q->next);
			q->next=NULL;
		}
	}
	if(Direction==4)
	{
		if(body001->x==Food_x&&body001->y==(Food_y-2))
		{
			temp->x=Food_x;
			temp->y=Food_y;
			temp->next=body001;
			body001=temp;
			Food=0;
			Score+=5;
		}
		else
		{
			temp->x=body001->x;
			temp->y=body001->y+2;
			temp->next=body001;
			body001=temp;
			q=body001;
			while((q->next)->next!=NULL)q=q->next;
			posit->Position((q->next)->x,(q->next)->y);
			cout<<" ";
			delete(q->next);
			q->next=NULL;
		}
	}
}

class Game_Snake
{	
public:
	void Game();
	int JudgeOver();
	void CreatSneak();
};
void Game_Snake::Game()
{
	
	while(1)
	{
		Movemant *m;
		Food_Snake *fs;
		Prt *prt;
		if(JudgeOver()==1)return;
		//w,上,1
		if(GetAsyncKeyState(87)&&Direction!=3)Direction=1;
		//A,左,2
		if(GetAsyncKeyState(65)&&Direction!=4)Direction=2;
		//S,下,3
		if(GetAsyncKeyState(83)&&Direction!=1)Direction=3;
		//D，右,4
		if(GetAsyncKeyState(68)&&Direction!=2)Direction=4;
		fs->Creat_Food();
		m->Move();
		prt->Prt_Sneak();
		Sleep(550-Grade*50);
	}
}
//判断是否结束，1代表结束，0代表未结束
int Game_Snake::JudgeOver()
{
	Body *p;
	p=body001->next;
	//到边界
	if(body001->y==1||body001->y==57||body001->x==1||body001->x==24)
		return 1;
	/*
	if(body001->y==3||body001->y==55||body001->x==2||body001->x==23)
	{
		
		if(GetAsyncKeyState(87)&&(Direction==2 || Direction==4))
		{
			Direction=1;
			return 0;
		}
		if(GetAsyncKeyState(83)&&(Direction==2 || Direction==4))
		{
			Direction=3;
			return 0;
		}
		if(GetAsyncKeyState(65)&&(Direction==1 || Direction==3))
		{
			Direction=2;
			return 0;
		}
		if(GetAsyncKeyState(68)&&(Direction==1 || Direction==3))
		{
			Direction=4;
			return 0;
		}
		
		Sleep(550-Grade*50);
		return 1;		
	}
	*/
	//头没有触碰到自己时
	while(!(p->x==body001->x&&p->y==body001->y))
	{
		if(p->next==NULL)return 0;
		p=p->next;
	}	
	return 1;
}

void Game_Snake::CreatSneak()
{
	Body *body002=new Body[sizeof(Body)];
	Body *body003=new Body[sizeof(Body)];
	Body *body004=new Body[sizeof(Body)];
	Body *body005=new Body[sizeof(Body)];
	body001->x=11;
	body001->y=35;
	body002->x=11;
	body002->y=33;
	body003->x=11;
	body003->y=31;
	body004->x=11;
	body004->y=29;
	body005->x=11;
	body005->y=27;
	body001->next=body002;
	body002->next=body003;
	body003->next=body004;
	body004->next=body005;
	body005->next=NULL;
}

void main()
{
	Game_Snake *gs;
	posi *posit;
	Prt *prt;
	posit->Position(11,24);
	cout<<"W,A,S,D to control";
	posit->Position(12,24);
	cout<<"Plese Select Grade:[1~10]";
	cin>>Grade;
	if(Grade<1||Grade>10)
	{
		cout<<"Wrong Input!"<<endl;
		return;
	}
	system("cls");
	gs->CreatSneak();
	prt->Prt_Map();
	prt->Prt_Sneak();
	gs->Game();
	system("cls");
	posit->Position(12,35);
	cout<<"You Lost !"<<endl;
	posit->Position(13,31);
	cout<<"You Got "<<Score<<" Scores"<<endl;
	posit->Position(24,29);
	getch();
}