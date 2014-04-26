#include "huoxingSnakeNode.h"

extern SnakeNode *sFood;
vector<SnakeNode*> asnakeBody;		//���������ߵ����壬��������ͷ

SnakeNode *aHead= new huoxingSnakeNode();	//��������ͷ�ڵ��ʼ��

void huoxingSnakeNode::BodyMove()
{
	for(int i = asnakeBody.size()-1; i>=0; i--)  
	{   
		//snΪָ��allBodyԪ�ص�ָ�룬ͨ��sn�ɸ���allBodyԪ�ص�ֵ�������µ��¸�λ��
		//��ȡ�������ϵ�ĳ���ڵ�
		SnakeNode * sn = (SnakeNode *)asnakeBody.at(i);  

		//��������ǰ��Ľڵ㸳ֵ������Ľڵ㣬ʵ���߽ڵ���ǰ�ƶ�һ��λ��
		if(i>0)   
		{   
			//����ýڵ㲻�ǵ�һ���ڵ�,��ô�ýڵ����һ�����������ǰһ��������꣨���ﲻ�ö���ͣ�����ߵĶ�����  
			SnakeNode * snpre = (SnakeNode *)asnakeBody.at(i-1);  

			//�������кͷ���
			sn->dir = snpre->dir;  
			sn->row = snpre->row;  
			sn->col = snpre->col;  
		}  


		//����ͷ��λ�ø�ֵ����������ͷ����ڵ�
		else if(i==0)  
		{  
			//���i=0���ǵ�һ���ڵ㣬��ͷ��������Ǹýڵ������  
			sn->dir = aHead->dir;  
			sn->row = aHead->row;  
			sn->col = aHead->col;  
		}  
	}
}

void huoxingSnakeNode::HeadMove()
{
	//������ͷ���ƶ�����,�����پ���,�����ƶ����ȣ�bug������������
	if ((aHead->row)!=(sFood->row))
	{ 
		if(sFood->row < aHead->row)
		{	//ʳ������ͷ���
			aHead->row--;
			aHead->dir=LEFT;
		}
		else if(sFood->row > aHead->row)
		{	//ʳ������ͷ�ұ�
			aHead->row++;
			aHead->dir=RIGHT;
		}
	}  
	else if ((aHead->col!=sFood->col))
	{
		if(sFood->col < aHead->col)
		{	//ʳ������ͷ�·�
			aHead->col--;
			aHead->dir=DOWN;
		}
		if(sFood->col > aHead->col)
		{	//ʳ������ͷ�Ϸ�
			aHead->col++;
			aHead->dir=UP;
		} 
	} 
}

void huoxingSnakeNode::eat()
{
	//�����ߵ���ײ���
	if(aHead->row==sFood->row&&aHead->col==sFood->col)
	{
		//ʳ��ӵ�ǰλ����ʧ�������������һ������  
		sFood->row = rand()%10;  
		sFood->col = rand()%10;  


		//������嵽����  
		SnakeNode * sn = new SnakeNode();//����һ���µĽڵ㣨Ҳ���ǳԵ����Ǹ�ʳ�������ŵ��ߵ�β����  
		SnakeNode * lastNode = NULL;  
		//��ȡ�ߵ����һ���ڵ㣬���allBody��size()Ϊ0����˵�����ǵ�һ�β�ʳ����ô�������һ���ڵ�Ҳ������ͷ����  
		if(asnakeBody.size()>0)  
			lastNode = (SnakeNode *)asnakeBody.back();  
		else  
			lastNode = aHead;//���һ���ڵ�����ͷ  


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
		asnakeBody.push_back(sn);//���µĽڵ���뵽�ߵ�������
	}
}