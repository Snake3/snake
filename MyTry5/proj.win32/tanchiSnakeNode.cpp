#include "tanchiSnakeNode.h"
#include "Game.h"

vector<SnakeNode*> allBody;			//声明贪吃蛇的身体，不包括蛇头

extern SnakeNode *sFood;
SnakeNode *sHead = new tanchiSnakeNode();	//贪吃蛇蛇头节点初始化

void tanchiSnakeNode::BodyMove()
{
	//移动蛇的身体,不包括蛇头  
	for(int i = allBody.size()-1; i>=0; i--)  
	{   
		//sn为指向allBody元素的指针，通过sn可更改allBody元素的值，即跟新到下个位置
		//获取蛇身体上的某个节点
		SnakeNode * sn = (SnakeNode *)allBody.at(i);  

		//把蛇身体前面的节点赋值给后面的节点，实现蛇节点向前移动一个位置
		if(i>0)   
		{   
			//如果该节点不是第一个节点,那么该节点的下一个坐标就是其前一个点的坐标（这里不用多解释，玩过蛇的都懂）  
			SnakeNode * snpre = (SnakeNode *)allBody.at(i-1);  

			//更改行列和方向

			sn->dir = snpre->dir;  
			sn->row = snpre->row;  
			sn->col = snpre->col;  
		}  


		//把蛇头的位置赋值给紧接在蛇头后面节点
		else if(i==0)  
		{  
			//如果i=0则是第一个节点，蛇头的坐标便是该节点的坐标  
			sn->dir = sHead->dir;  
			sn->row = sHead->row;  
			sn->col = sHead->col;  
		}  
	}  
}

void tanchiSnakeNode::HeadMove()
{
	Game game;
	//根据sHead的值，判断蛇头移动的方向，从而计算出蛇头下个位置的坐标以及移动方向
	switch(sHead->dir)  
	{  
	case UP:  
		sHead->col++;//上移  
		game.judgeOver(); 
		break;  
	case DOWN:  
		sHead->col--;  
		game.judgeOver();  
		break;  
	case LEFT:  
		sHead->row--;  
		game.judgeOver();   
		break;  
	case RIGHT:  
		sHead->row++;  
		game.judgeOver();    
		break;  
	}   
}

void tanchiSnakeNode::eat()
{
	srand((unsigned)time(0));
	//碰撞检测(只是判断蛇头位置和食物位置是否一样而已）
	//如果蛇头的横、列位置一样，说明蛇吃到了这个食物  
	if(sHead->row == sFood->row && sHead->col == sFood->col) 
	{   
		//食物从当前位置消失，随机出现在下一个坐标  
		sFood->row = rand()%10;  
		sFood->col = rand()%10;  


		//添加身体到集合  
		SnakeNode * sn = new SnakeNode();//创建一个新的节点（也就是吃掉的那个食物），将其放到蛇的尾巴上  
		SnakeNode * lastNode = NULL;  
		//获取蛇的最后一个节点，如果allBody的size()为0，则说明蛇是第一次捕食，那么它的最后一个节点也就是蛇头啦。  
		if(allBody.size()>0)  
			lastNode = (SnakeNode *)allBody.back();  
		else  
			lastNode = sHead;//最后一个节点是蛇头  


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
		allBody.push_back(sn);//将新的节点加入到蛇的身体中。  
	} 
}