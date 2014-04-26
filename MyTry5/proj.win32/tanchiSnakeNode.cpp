#include "tanchiSnakeNode.h"
#include "Game.h"

vector<SnakeNode*> allBody;			//����̰���ߵ����壬��������ͷ

extern SnakeNode *sFood;
SnakeNode *sHead = new tanchiSnakeNode();	//̰������ͷ�ڵ��ʼ��

void tanchiSnakeNode::BodyMove()
{
	//�ƶ��ߵ�����,��������ͷ  
	for(int i = allBody.size()-1; i>=0; i--)  
	{   
		//snΪָ��allBodyԪ�ص�ָ�룬ͨ��sn�ɸ���allBodyԪ�ص�ֵ�������µ��¸�λ��
		//��ȡ�������ϵ�ĳ���ڵ�
		SnakeNode * sn = (SnakeNode *)allBody.at(i);  

		//��������ǰ��Ľڵ㸳ֵ������Ľڵ㣬ʵ���߽ڵ���ǰ�ƶ�һ��λ��
		if(i>0)   
		{   
			//����ýڵ㲻�ǵ�һ���ڵ�,��ô�ýڵ����һ�����������ǰһ��������꣨���ﲻ�ö���ͣ�����ߵĶ�����  
			SnakeNode * snpre = (SnakeNode *)allBody.at(i-1);  

			//�������кͷ���

			sn->dir = snpre->dir;  
			sn->row = snpre->row;  
			sn->col = snpre->col;  
		}  


		//����ͷ��λ�ø�ֵ����������ͷ����ڵ�
		else if(i==0)  
		{  
			//���i=0���ǵ�һ���ڵ㣬��ͷ��������Ǹýڵ������  
			sn->dir = sHead->dir;  
			sn->row = sHead->row;  
			sn->col = sHead->col;  
		}  
	}  
}

void tanchiSnakeNode::HeadMove()
{
	Game game;
	//����sHead��ֵ���ж���ͷ�ƶ��ķ��򣬴Ӷ��������ͷ�¸�λ�õ������Լ��ƶ�����
	switch(sHead->dir)  
	{  
	case UP:  
		sHead->col++;//����  
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
	//��ײ���(ֻ���ж���ͷλ�ú�ʳ��λ���Ƿ�һ�����ѣ�
	//�����ͷ�ĺᡢ��λ��һ����˵���߳Ե������ʳ��  
	if(sHead->row == sFood->row && sHead->col == sFood->col) 
	{   
		//ʳ��ӵ�ǰλ����ʧ�������������һ������  
		sFood->row = rand()%10;  
		sFood->col = rand()%10;  


		//������嵽����  
		SnakeNode * sn = new SnakeNode();//����һ���µĽڵ㣨Ҳ���ǳԵ����Ǹ�ʳ�������ŵ��ߵ�β����  
		SnakeNode * lastNode = NULL;  
		//��ȡ�ߵ����һ���ڵ㣬���allBody��size()Ϊ0����˵�����ǵ�һ�β�ʳ����ô�������һ���ڵ�Ҳ������ͷ����  
		if(allBody.size()>0)  
			lastNode = (SnakeNode *)allBody.back();  
		else  
			lastNode = sHead;//���һ���ڵ�����ͷ  


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
		allBody.push_back(sn);//���µĽڵ���뵽�ߵ������С�  
	} 
}