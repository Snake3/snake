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
		//snΪָ��snakeBodyԪ�ص�ָ�룬ͨ��sn�ɸ���snakeBodyԪ�ص�ֵ�������µ��¸�λ��
		//��ȡ�������ϵ�ĳ���ڵ�
		SnakeNode * sn = (SnakeNode *)this->snakeBody.at(i);  

		//��������ǰ��Ľڵ㸳ֵ������Ľڵ㣬ʵ���߽ڵ���ǰ�ƶ�һ��λ��
		if(i>0)   
		{   
			//����ýڵ㲻�ǵ�һ���ڵ�,��ô�ýڵ����һ�����������ǰһ��������꣨���ﲻ�ö���ͣ�����ߵĶ�����  
			SnakeNode * snpre = (SnakeNode *)this->snakeBody.at(i-1);  

			//�������кͷ���
			sn->dir = snpre->dir;  
			sn->row = snpre->row;  
			sn->col = snpre->col;  
		}  


		//����ͷ��λ�ø�ֵ����������ͷ����ڵ�
		else if(i==0)  
		{  
			//���i=0���ǵ�һ���ڵ㣬��ͷ��������Ǹýڵ������  
			sn->dir = this->snakeHead->dir;  
			sn->row = this->snakeHead->row;  
			sn->col = this->snakeHead->col;  
		}  
	}
}
