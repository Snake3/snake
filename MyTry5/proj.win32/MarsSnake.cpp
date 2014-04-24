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
		//�����ߵ���ײ���
	if(snakeHead->row==sFood->row&&snakeHead->col==sFood->col)
	{
		haveEat = 1;
		//ʳ��ӵ�ǰλ����ʧ�������������һ������    

		//������嵽����  
		SnakeNode * sn = new SnakeNode();//����һ���µĽڵ㣨Ҳ���ǳԵ����Ǹ�ʳ�������ŵ��ߵ�β����  
		SnakeNode * lastNode = NULL;  
		//��ȡ�ߵ����һ���ڵ㣬���snakeBody��size()Ϊ0����˵�����ǵ�һ�β�ʳ����ô�������һ���ڵ�Ҳ������ͷ����  
		if(snakeBody.size()>0)  
			lastNode = (SnakeNode *)snakeBody.back();  
		else  
			lastNode = snakeHead;//���һ���ڵ�����ͷ  


		//ͨ�����һ���ڵ�ķ��������µĽڵ��ʼ���ᡢ������  
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
		snakeBody.push_back(sn);//���µĽڵ���뵽�ߵ�������
	}
	return haveEat;
	}

	void MarsSnake::BodyMove(){
		for(int i = snakeBody.size()-1; i>=0; i--)  
	{   
		//snΪָ��snakeBodyԪ�ص�ָ�룬ͨ��sn�ɸ���snakeBodyԪ�ص�ֵ�������µ��¸�λ��
		//��ȡ�������ϵ�ĳ���ڵ�
		SnakeNode * sn = (SnakeNode *)snakeBody.at(i);  

		//��������ǰ��Ľڵ㸳ֵ������Ľڵ㣬ʵ���߽ڵ���ǰ�ƶ�һ��λ��
		if(i>0)   
		{   
			//����ýڵ㲻�ǵ�һ���ڵ�,��ô�ýڵ����һ�����������ǰһ��������꣨���ﲻ�ö���ͣ�����ߵĶ�����  
			SnakeNode * snpre = (SnakeNode *)snakeBody.at(i-1);  

			//�������кͷ���
			sn->dir = snpre->dir;  
			sn->row = snpre->row;  
			sn->col = snpre->col;  
		}  


		//����ͷ��λ�ø�ֵ����������ͷ����ڵ�
		else if(i==0)  
		{  
			//���i=0���ǵ�һ���ڵ㣬��ͷ��������Ǹýڵ������  
			sn->dir = snakeHead->dir;  
			sn->row = snakeHead->row;  
			sn->col = snakeHead->col;  
		}  
	}
	}

	void MarsSnake::HeadMove(SnakeNode* sFood){
		//������ͷ���ƶ�����,�����پ���,�����ƶ����ȣ�bug������������
	if ((snakeHead->row)!=(sFood->row))
	{ 
		if(sFood->row < snakeHead->row)
		{	//ʳ������ͷ���
			snakeHead->row--;
			snakeHead->dir=LEFT;
		}
		else if(sFood->row > snakeHead->row)
		{	//ʳ������ͷ�ұ�
			snakeHead->row++;
			snakeHead->dir=RIGHT;
		}
	}  
	else if ((snakeHead->col!=sFood->col))
	{
		if(sFood->col < snakeHead->col)
		{	//ʳ������ͷ�·�
			snakeHead->col--;
			snakeHead->dir=DOWN;
		}
		if(sFood->col > snakeHead->col)
		{	//ʳ������ͷ�Ϸ�
			snakeHead->col++;
			snakeHead->dir=UP;
		} 
	}  
	}