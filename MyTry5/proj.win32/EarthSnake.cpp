#include "HelloWorldScene.h"
#include "Game.h"

#include "EarthSnake.h"

using namespace cocos2d;

EarthSnake::EarthSnake(){
	snakeHead = new SnakeNode();
}

bool EarthSnake::eat(SnakeNode* sFood){
		bool haveEat = false;
		srand((unsigned)time(0));
	//碰撞检测(只是判断蛇头位置和食物位置是否一样而已）
	//如果蛇头的横、列位置一样，说明蛇吃到了这个食物  
	if(snakeHead->row == sFood->row && snakeHead->col == sFood->col) 
	{   
		haveEat = true;
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
		snakeBody.push_back(sn);//将新的节点加入到蛇的身体中。  
	} 
	return haveEat;
	}

void EarthSnake::BodyMove(){
		//移动蛇的身体,不包括蛇头  
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

void EarthSnake::HeadMove(){
	//根据snakeHead的值，判断蛇头移动的方向，从而计算出蛇头下个位置的坐标以及移动方向
	Game *game = NULL;
	switch(snakeHead->dir)  
	{  
	case UP:  
		snakeHead->col++;//上移  
		game->judgeOver(); 
		break;  
	case DOWN:  
		snakeHead->col--;  
		game->judgeOver();   
		break;  
	case LEFT:  
		snakeHead->row--;  
		game->judgeOver();   
		break;  
	case RIGHT:  
		snakeHead->row++;  
		game->judgeOver();   
		break;  
	}   
}


