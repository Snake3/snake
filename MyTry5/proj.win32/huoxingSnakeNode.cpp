#include "huoxingSnakeNode.h"

extern SnakeNode *sFood;
vector<SnakeNode*> asnakeBody;		//声明火星蛇的身体，不包括蛇头

SnakeNode *aHead= new huoxingSnakeNode();	//火星蛇蛇头节点初始化

void huoxingSnakeNode::BodyMove()
{
	for(int i = asnakeBody.size()-1; i>=0; i--)  
	{   
		//sn为指向allBody元素的指针，通过sn可更改allBody元素的值，即跟新到下个位置
		//获取蛇身体上的某个节点
		SnakeNode * sn = (SnakeNode *)asnakeBody.at(i);  

		//把蛇身体前面的节点赋值给后面的节点，实现蛇节点向前移动一个位置
		if(i>0)   
		{   
			//如果该节点不是第一个节点,那么该节点的下一个坐标就是其前一个点的坐标（这里不用多解释，玩过蛇的都懂）  
			SnakeNode * snpre = (SnakeNode *)asnakeBody.at(i-1);  

			//更改行列和方向
			sn->dir = snpre->dir;  
			sn->row = snpre->row;  
			sn->col = snpre->col;  
		}  


		//把蛇头的位置赋值给紧接在蛇头后面节点
		else if(i==0)  
		{  
			//如果i=0则是第一个节点，蛇头的坐标便是该节点的坐标  
			sn->dir = aHead->dir;  
			sn->row = aHead->row;  
			sn->col = aHead->col;  
		}  
	}
}

void huoxingSnakeNode::HeadMove()
{
	//火星蛇头的移动方向,曼哈顿距离,左右移动优先，bug：穿过蛇身体
	if ((aHead->row)!=(sFood->row))
	{ 
		if(sFood->row < aHead->row)
		{	//食物在蛇头左边
			aHead->row--;
			aHead->dir=LEFT;
		}
		else if(sFood->row > aHead->row)
		{	//食物在蛇头右边
			aHead->row++;
			aHead->dir=RIGHT;
		}
	}  
	else if ((aHead->col!=sFood->col))
	{
		if(sFood->col < aHead->col)
		{	//食物在蛇头下方
			aHead->col--;
			aHead->dir=DOWN;
		}
		if(sFood->col > aHead->col)
		{	//食物在蛇头上方
			aHead->col++;
			aHead->dir=UP;
		} 
	} 
}

void huoxingSnakeNode::eat()
{
	//火星蛇的碰撞检测
	if(aHead->row==sFood->row&&aHead->col==sFood->col)
	{
		//食物从当前位置消失，随机出现在下一个坐标  
		sFood->row = rand()%10;  
		sFood->col = rand()%10;  


		//添加身体到集合  
		SnakeNode * sn = new SnakeNode();//创建一个新的节点（也就是吃掉的那个食物），将其放到蛇的尾巴上  
		SnakeNode * lastNode = NULL;  
		//获取蛇的最后一个节点，如果allBody的size()为0，则说明蛇是第一次捕食，那么它的最后一个节点也就是蛇头啦。  
		if(asnakeBody.size()>0)  
			lastNode = (SnakeNode *)asnakeBody.back();  
		else  
			lastNode = aHead;//最后一个节点是蛇头  


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
		asnakeBody.push_back(sn);//将新的节点加入到蛇的身体中
	}
}