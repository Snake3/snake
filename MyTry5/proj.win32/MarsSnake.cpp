#include "HelloWorldScene.h"
#include "Game.h"
#include "SnakeNode.h"
#include "MarsSnake.h"

using namespace cocos2d;

	MarsSnake::MarsSnake(){
		snakeHead = new SnakeNode();
	}

	int MarsSnake::eat(SnakeNode* sFood){
		int haveEat = 0;
		//火星蛇的碰撞检测
	if(snakeHead->row==sFood->row&&snakeHead->col==sFood->col)
	{
		haveEat = 1;
		//食物从当前位置消失，随机出现在下一个坐标    

		//添加身体到集合  
		SnakeNode * sn = new SnakeNode();//创建一个新的节点（也就是吃掉的那个食物），将其放到蛇的尾巴上  
		SnakeNode * lastNode = NULL;  
		//获取蛇的最后一个节点，如果snakeBody的size()为0，则说明蛇是第一次捕食，那么它的最后一个节点也就是蛇头啦。  
		if(snakeBody.size()>0)  
			lastNode = (SnakeNode *)snakeBody.back();  
		else  
			lastNode = snakeHead;//最后一个节点是蛇头  


		//通过最后一个节点的方向来个新的节点初始化横、列坐标  
		switch(lastNode->dir)  
		{  
		case UP:  
			sn->row = lastNode->row;  
			sn->col = lastNode->col-1;  
			break;  

		case DOWN:  
			sn->row = lastNode->row;  
			sn->col = lastNode->col+1;  
			break;  

		case LEFT:  
			sn->row = lastNode->row+1;  
			sn->col = lastNode->col;  
			break;  

		case RIGHT:  
			sn->row=lastNode->row-1;  
			sn->col=lastNode->col;  
			break;		
		} 
		snakeBody.push_back(sn);//将新的节点加入到蛇的身体中
	}
	return haveEat;
	}

	void MarsSnake::BodyMove(){
		for(int i = snakeBody.size()-1; i>=0; i--)  
	{   
		//sn为指向snakeBody元素的指针，通过sn可更改snakeBody元素的值，即跟新到下个位置
		//获取蛇身体上的某个节点
		SnakeNode * sn = (SnakeNode *)snakeBody.at(i);  

		//把蛇身体前面的节点赋值给后面的节点，实现蛇节点向前移动一个位置
		if(i>0)   
		{   
			//如果该节点不是第一个节点,那么该节点的下一个坐标就是其前一个点的坐标（这里不用多解释，玩过蛇的都懂）  
			SnakeNode * snpre = (SnakeNode *)snakeBody.at(i-1);  

			//更改行列和方向
			sn->dir = snpre->dir;  
			sn->row = snpre->row;  
			sn->col = snpre->col;  
		}  


		//把蛇头的位置赋值给紧接在蛇头后面节点
		else if(i==0)  
		{  
			//如果i=0则是第一个节点，蛇头的坐标便是该节点的坐标  
			sn->dir = snakeHead->dir;  
			sn->row = snakeHead->row;  
			sn->col = snakeHead->col;  
		}  
	}
	}

	void MarsSnake::HeadMove(SnakeNode* sFood){
		//火星蛇头的移动方向,曼哈顿距离,左右移动优先，bug：穿过蛇身体
	if ((snakeHead->row)!=(sFood->row))
	{ 
		if(sFood->row < snakeHead->row)
		{	//食物在蛇头左边
			snakeHead->row--;
			snakeHead->dir=LEFT;
		}
		else if(sFood->row > snakeHead->row)
		{	//食物在蛇头右边
			snakeHead->row++;
			snakeHead->dir=RIGHT;
		}
	}  
	else if ((snakeHead->col!=sFood->col))
	{
		if(sFood->col < snakeHead->col)
		{	//食物在蛇头下方
			snakeHead->col--;
			snakeHead->dir=DOWN;
		}
		if(sFood->col > snakeHead->col)
		{	//食物在蛇头上方
			snakeHead->col++;
			snakeHead->dir=UP;
		} 
	}  
	}