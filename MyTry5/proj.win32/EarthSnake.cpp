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


