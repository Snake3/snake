#include "HelloWorldScene.h"
#include "Game.h"
//#include "EarthSnake.h"
#include "MarsSnake.h"

//using namespace cocos2d;

MarsSnake::MarsSnake()
{
	snakeHead = new SnakeNode();
}

int MarsSnake::eat(SnakeNode* sFood)
{
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

void MarsSnake::BodyMove()
{
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

void MarsSnake::HeadMove(SnakeNode* sFood, EarthSnake* earthSnake)
{
	#if 0
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
	#endif

	//AStar�㷨ʵ�������پ���
	vector<SnakeNode*> OpenList, CloseList, pList;
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
		//pu->GValue = p->GValue + 1;
		//pu->FValue = pu->HValue + pu->GValue;
		pu->dir = UP;
		pd->HValue = abs(pd->col - sFood->col) + abs(pd->row - sFood->row);
		//pd->GValue = p->GValue + 1;
		//pd->FValue = pd->HValue + pd->GValue;
		pd->dir = DOWN;
		pl->HValue = abs(pl->col - sFood->col) + abs(pl->row - sFood->row);
		//pl->GValue = p->GValue + 1;
		//pl->FValue = pl->GValue + pl->HValue;
		pl->dir = LEFT;
		pr->HValue = abs(pr->col - sFood->col) + abs(pr->row - sFood->row);
		//pr->GValue = p->GValue + 1;
		//pr->FValue = pr->GValue + pr->HValue;
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
			if(adj[b]->col > 9 || adj[b]->col < 0 || adj[b]->row > 9 || adj[b]->row < 0)
			{	
				//c = b;
				adj.erase(adj.begin() + b);
				adjSize--;
			}
			else
			{
				b++;
			}
		}
		
		OpenList.insert(OpenList.end(),adj.begin(),adj.end());

		/*
		//��OpenList��ɾ����ǰ�ڵ�p
		//int k = 0;
		for(unsigned int j = 0; j < OpenList.size();)
		{
			if(OpenList[j]->row == p->row && OpenList[j]->col == p->col)
			{
				//k = j;
				OpenList.erase(OpenList.begin() + j);
			}
			else
			{
				j++;
			}
		}
		*/
		CloseList.push_back(p);

		
		//p = adj[temp];
		//CloseList.push_back(p);
		//aHead = p;
		
		//OpenList��CloseList����,CloseList�ϰ�������Ľڵ㲻�ܳ�����OpenList��
		for(unsigned openlistSize = 0; openlistSize < OpenList.size(); openlistSize++)
		{
			if(isContain(CloseList,OpenList[openlistSize]))
				OpenList.erase(OpenList.begin() + openlistSize);
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

		int smallest=100,temp = 0;
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
			/*
			for(; m < OpenList.size(); m++)
			{
				if(adj[c]->col == OpenList[m]->col && adj[c]->row == OpenList[m]->row)
					m = c;
			}
			*/
		}
		
		if(adjSize < 1)
		{
			CCDirector::sharedDirector()->end();
		}
		while(isContain(CloseList,adj[temp]))
		{
			if(adjSize < 1)
			{
				CCDirector::sharedDirector()->end();
			}
			
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

	}
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