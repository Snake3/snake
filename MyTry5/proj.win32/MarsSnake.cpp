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

//石头、仙人掌等障碍物的添加
void MarsSnake::addCloseList()
{	//16个坐标值
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
	//火星蛇的碰撞检测
	if(snakeHead->row==sFood->row&&snakeHead->col==sFood->col)
	{
		haveEat = true;
		//食物从当前位置消失，随机出现在下一个坐标    

		//添加身体到集合  
		SnakeNode * sn = new SnakeNode();//创建一个新的节点（也就是吃掉的那个食物），将其放到蛇的尾巴上  
		SnakeNode * lastNode = NULL;  
		//获取蛇的最后一个节点，如果snakeBody的size()为0，则说明蛇是第一次捕食，那么它的最后一个节点也就是蛇头啦。  
		if(snakeBody.size()>0)  
			lastNode = (SnakeNode *)snakeBody.back();  
		else  
			lastNode = snakeHead;//最后一个节点是蛇头  


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
		snakeBody.push_back(sn);//将新的节点加入到蛇的身体中
	}
	return haveEat;
}

bool MarsSnake::MarsSnakeHeadMove(SnakeNode* sFood, EarthSnake* earthSnake)
{
	//AStar算法实现曼哈顿距离
	vector<SnakeNode*> OpenList;
	//当前节点p及其相邻节点
	SnakeNode *p = new SnakeNode();

	SnakeNode *pu = new SnakeNode();
	SnakeNode *pd = new SnakeNode();
	SnakeNode *pl = new SnakeNode();
	SnakeNode *pr = new SnakeNode();

	//两蛇合并
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
		//获取权值最小节点为当前节点p，当前节点从OpenList中移除
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

		//相邻节点放入OpenList中
		vector<SnakeNode*> adj;

		adj.push_back(pu);
		adj.push_back(pd);
		adj.push_back(pl);
		adj.push_back(pr);

		//int c = 0;
		//删除超出边界的相邻节点
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
		
		//OpenList与CloseList互斥,CloseList障碍物里面的节点不能出现在OpenList中
		for(unsigned openlistSize = 0; openlistSize < OpenList.size(); )
		{
			if(isContain(CloseList,OpenList[openlistSize]))
				OpenList.erase(OpenList.begin() + openlistSize);
			else
				openlistSize++;
		}
		//相邻节点出现在CloseList障碍物中则删除
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

//火星蛇的OpenList和CloseList的判断是否包含的函数
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