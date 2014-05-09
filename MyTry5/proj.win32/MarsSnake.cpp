#include "HelloWorldScene.h"
#include "Game.h"
//#include "EarthSnake.h"
#include "MarsSnake.h"

//using namespace cocos2d;

vector<SnakeNode*> barriers;

MarsSnake::MarsSnake()
{
	snakeHead = new SnakeNode();
}

void MarsSnake::HeadMove(){}

//ʯͷ�������Ƶ��ϰ�������
void MarsSnake::addCloseList()
{	//16������ֵ
	SnakeNode *point1 = new SnakeNode();
	point1->row = 13;
	point1->col = 12;
	CloseList.push_back(point1);
	SnakeNode *point2 = new SnakeNode();
	point2->row = 13;
	point2->col = 11;
	CloseList.push_back(point2);
	SnakeNode *point3 = new SnakeNode();
	point3->row = 14;
	point3->col = 12;
	CloseList.push_back(point3);
	SnakeNode *point4 = new SnakeNode();
	point4->row = 14;
	point4->col = 11;
	CloseList.push_back(point4);
	SnakeNode *point5 = new SnakeNode();
	point5->row = 15;
	point5->col = 12;
	CloseList.push_back(point5);
	SnakeNode *point6 = new SnakeNode();
	point6->row = 15;
	point6->col = 11;
	CloseList.push_back(point6);
	SnakeNode *point7 = new SnakeNode();
	point7->row = 18;
	point7->col = 7;
	CloseList.push_back(point7);
	SnakeNode *point8 = new SnakeNode();
	point8->row = 19;
	point8->col = 7;
	CloseList.push_back(point8);
	SnakeNode *point9 = new SnakeNode();
	point9->row = 20;
	point9->col = 7;
	CloseList.push_back(point9);
	SnakeNode *point10 = new SnakeNode();
	point10->row = 18;
	point10->col = 8;
	CloseList.push_back(point10);
	SnakeNode *point11 = new SnakeNode();
	point11->row = 19;
	point11->col = 8;
	CloseList.push_back(point11);
	SnakeNode *point12 = new SnakeNode();
	point12->row = 20;
	point12->col = 8;
	CloseList.push_back(point12);
	SnakeNode *point13 = new SnakeNode();
	point13->row = 3;
	point13->col = 8;
	CloseList.push_back(point13);
	SnakeNode *point14 = new SnakeNode();
	point14->row = 7;
	point14->col = 10;
	CloseList.push_back(point14);
	SnakeNode *point15 = new SnakeNode();
	point15->row = 6;
	point15->col = 5;
	CloseList.push_back(point15);
	SnakeNode *point16 = new SnakeNode();
	point16->row = 18;
	point16->col = 2;
	CloseList.push_back(point16);

	for(int i = 1; i <= 16; i++)
	{
		barriers.push_back(CloseList[CloseList.size() - i]);
	}
}

bool MarsSnake::eat(SnakeNode* sFood)
{
	bool haveEat = false;
	//�����ߵ���ײ���
	if(snakeHead->row==sFood->row&&snakeHead->col==sFood->col)
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
		snakeBody.push_back(sn);//���µĽڵ���뵽�ߵ�������
	}
	return haveEat;
}

bool MarsSnake::MarsSnakeHeadMove(SnakeNode* sFood, EarthSnake* earthSnake)
{
	//AStar�㷨ʵ�������پ���
	vector<SnakeNode*> OpenList;
	//��ǰ�ڵ�p�������ڽڵ�
	SnakeNode *p = new SnakeNode();

	SnakeNode *pu = new SnakeNode();
	SnakeNode *pd = new SnakeNode();
	SnakeNode *pl = new SnakeNode();
	SnakeNode *pr = new SnakeNode();

	//���ߺϲ�
	vector<SnakeNode*> huoxingSnake, tanchiSnake;
	tanchiSnake = earthSnake->snakeBody;
	tanchiSnake.push_back(earthSnake->snakeHead);
	huoxingSnake = snakeBody;
	huoxingSnake.push_back(snakeHead);
	tanchiSnake.insert(tanchiSnake.begin(),snakeBody.begin(),snakeBody.end());

	CloseList = tanchiSnake;
	this->addCloseList();

	//p = aHead;
	//p->GValue = 0;
	OpenList.push_back(snakeHead);

	

	unsigned int m = 0;
	if (!OpenList.empty() && !isContain(OpenList,sFood))
	{
		//p->GValue = p->GValue + 1;
		p->col = snakeHead->col;
		p->row = snakeHead->row;
		//��ȡȨֵ��С�ڵ�Ϊ��ǰ�ڵ�p����ǰ�ڵ��OpenList���Ƴ�
		pu->row = p->row;
		pu->col = (p->col) + 1;
		pd->row = p->row;
		pd->col = (p->col)-1;
		pl->row = (p->row)-1;
		pl->col = p->col;
		pr->row = (p->row)+1;
		pr->col = p->col;

		pu->HValue = abs(pu->col - sFood->col) + abs(pu->row - sFood->row);
		pu->dir = UP;
		pd->HValue = abs(pd->col - sFood->col) + abs(pd->row - sFood->row);
		pd->dir = DOWN;
		pl->HValue = abs(pl->col - sFood->col) + abs(pl->row - sFood->row);
		pl->dir = LEFT;
		pr->HValue = abs(pr->col - sFood->col) + abs(pr->row - sFood->row);
		pr->dir = RIGHT;

		//���ڽڵ����OpenList��
		vector<SnakeNode*> adj;

		adj.push_back(pu);
		adj.push_back(pd);
		adj.push_back(pl);
		adj.push_back(pr);

		//int c = 0;
		//ɾ�������߽�����ڽڵ�
		unsigned int adjSize = 4;
		for(unsigned int b = 0; b < adjSize;)
		{
			if(adj[b]->col > 13 || adj[b]->col < 0 || adj[b]->row > 23 || adj[b]->row < 1)
			{	
				//c = b;
				CloseList.push_back(adj[b]);
				
				adj.erase(adj.begin() + b);
				adjSize--;
			}
			else
			{
				b++;
			}
		}
		
		if(isContain(CloseList,pu) && isContain(CloseList,pd) && isContain(CloseList,pl) && isContain(CloseList,pr))
		{
			return true;
			//exit(1);
		}
		OpenList.insert(OpenList.end(),adj.begin(),adj.end());		

		CloseList.push_back(p);
		
		
		//p = adj[temp];
		//CloseList.push_back(p);
		//aHead = p;
		
		//OpenList��CloseList����,CloseList�ϰ�������Ľڵ㲻�ܳ�����OpenList��
		for(unsigned openlistSize = 0; openlistSize < OpenList.size(); )
		{
			if(isContain(CloseList,OpenList[openlistSize]))
				OpenList.erase(OpenList.begin() + openlistSize);
			else
				openlistSize++;
		}
		//���ڽڵ������CloseList�ϰ�������ɾ��
		for(unsigned int e = 0; e < adjSize;)
		{
			if(isContain(CloseList,adj[e]))
			{	
				//c = b;
				adj.erase(adj.begin() + e);
				adjSize--;
			}
			else
			{
				e++;
			}
		}
		
		

		int smallest=900,temp = 0;
		for(unsigned int k = 0; k < adjSize; k++)
		{
			smallest = min(smallest,adj[k]->HValue);
		}
		for(unsigned int c = 0; c < adjSize; c++)
		{
			if(smallest == adj[c]->HValue)
			{
				temp = c;
				break;
			}
		}
		
		
		
		while(isContain(CloseList,adj[temp]))
		{
			
			for(unsigned int adjLength = 0; adjLength < adjSize;)
			{
				if(adjLength == temp)
				{
					adj.erase(adj.begin()+temp);
					adjSize--;
				}
				else
				{
					adjLength++;
				}
			}

			for(unsigned int k = 1; k < adjSize; k++)
			{
				smallest = min(smallest,adj[k]->HValue);
			}
			for(unsigned int r = 0; r < adjSize; r++)
			{
				if(smallest == adj[r]->HValue)
				{
					temp = r;
					break;
				}
			}
			
		}

		p = adj[temp];
		//pList.push_back(p);
		snakeHead->col = p->col;
		snakeHead->row = p->row;
		snakeHead->dir = p->dir;

	}
	return false;
	//p = pList[0];
	//snakeHead->col = p->col;
	//snakeHead->row = p->row;
}

//�����ߵ�OpenList��CloseList���ж��Ƿ�����ĺ���
bool MarsSnake::isContain(vector<SnakeNode*> List, SnakeNode* obj)
{
	for (unsigned int i = 0; i < List.size(); i++)
	{
		while(obj->col == List[i]->col && obj->row == List[i]->row)
		{
			return true;
		}
	}
	return false;
}