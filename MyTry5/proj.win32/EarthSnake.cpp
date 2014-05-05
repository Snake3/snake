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


