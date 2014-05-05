#include "HelloWorldScene.h"
#include "Game.h"
#include "Snake.h"

Snake::Snake()
{
	snakeHead = new SnakeNode();
}

void Snake::BodyMove()
{
		for(int i = this->snakeBody.size()-1; i>=0; i--)  
	{   
		//sn为指向snakeBody元素的指针，通过sn可更改snakeBody元素的值，即跟新到下个位置
		//获取蛇身体上的某个节点
		SnakeNode * sn = (SnakeNode *)this->snakeBody.at(i);  

		//把蛇身体前面的节点赋值给后面的节点，实现蛇节点向前移动一个位置
		if(i>0)   
		{   
			//如果该节点不是第一个节点,那么该节点的下一个坐标就是其前一个点的坐标（这里不用多解释，玩过蛇的都懂）  
			SnakeNode * snpre = (SnakeNode *)this->snakeBody.at(i-1);  

			//更改行列和方向
			sn->dir = snpre->dir;  
			sn->row = snpre->row;  
			sn->col = snpre->col;  
		}  


		//把蛇头的位置赋值给紧接在蛇头后面节点
		else if(i==0)  
		{  
			//如果i=0则是第一个节点，蛇头的坐标便是该节点的坐标  
			sn->dir = this->snakeHead->dir;  
			sn->row = this->snakeHead->row;  
			sn->col = this->snakeHead->col;  
		}  
	}
}
