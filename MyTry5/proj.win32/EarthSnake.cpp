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
	//��ײ���(ֻ���ж���ͷλ�ú�ʳ��λ���Ƿ�һ�����ѣ�
	//�����ͷ�ĺᡢ��λ��һ����˵���߳Ե������ʳ��  
	if(snakeHead->row == sFood->row && snakeHead->col == sFood->col) 
	{   
		haveEat = true;
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
		snakeBody.push_back(sn);//���µĽڵ���뵽�ߵ������С�  
	} 
	return haveEat;
	}

void EarthSnake::BodyMove(){
		//�ƶ��ߵ�����,��������ͷ  
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

void EarthSnake::HeadMove(){
	//����snakeHead��ֵ���ж���ͷ�ƶ��ķ��򣬴Ӷ��������ͷ�¸�λ�õ������Լ��ƶ�����
	Game *game = NULL;
	switch(snakeHead->dir)  
	{  
	case UP:  
		snakeHead->col++;//����  
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


