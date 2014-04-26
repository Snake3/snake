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
	//火星蛇的碰撞检测
	if(snakeHead->row==sFood->row&&snakeHead->col==sFood->col)
	{
		haveEat = 1;
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

void MarsSnake::BodyMove()
{
	for(int i = snakeBody.size()-1; i>=0; i--)  
	{   
		//sn为指向snakeBody元素的指针，通过sn可更改snakeBody元素的值，即跟新到下个位置
		//获取蛇身体上的某个节点
		SnakeNode * sn = (SnakeNode *)snakeBody.at(i);  

		//把蛇身体前面的节点赋值给后面的节点，实现蛇节点向前移动一个位置
		if(i>0)   
		{   
			//如果该节点不是第一个节点,那么该节点的下一个坐标就是其前一个点的坐标（这里不用多解释，玩过蛇的都懂）  
			SnakeNode * snpre = (SnakeNode *)snakeBody.at(i-1);  

			//更改行列和方向
			sn->dir = snpre->dir;  
			sn->row = snpre->row;  
			sn->col = snpre->col;  
		}  


		//把蛇头的位置赋值给紧接在蛇头后面节点
		else if(i==0)  
		{  
			//如果i=0则是第一个节点，蛇头的坐标便是该节点的坐标  
			sn->dir = snakeHead->dir;  
			sn->row = snakeHead->row;  
			sn->col = snakeHead->col;  
		}  
	}
}

void MarsSnake::HeadMove(SnakeNode* sFood, EarthSnake* earthSnake)
{
	#if 0
//火星蛇头的移动方向,曼哈顿距离,左右移动优先，bug：穿过蛇身体
	if ((snakeHead->row)!=(sFood->row))
	{ 
		if(sFood->row < snakeHead->row)
		{	//食物在蛇头左边
			snakeHead->row--;
			snakeHead->dir=LEFT;
		}
		else if(sFood->row > snakeHead->row)
		{	//食物在蛇头右边
			snakeHead->row++;
			snakeHead->dir=RIGHT;
		}
	}  
	else if ((snakeHead->col!=sFood->col))
	{
		if(sFood->col < snakeHead->col)
		{	//食物在蛇头下方
			snakeHead->col--;
			snakeHead->dir=DOWN;
		}
		if(sFood->col > snakeHead->col)
		{	//食物在蛇头上方
			snakeHead->col++;
			snakeHead->dir=UP;
		} 
	}  
	#endif

	//AStar算法实现曼哈顿距离
	vector<SnakeNode*> OpenList, CloseList, pList;
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
		//从OpenList中删除当前节点p
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
		
		//OpenList与CloseList互斥,CloseList障碍物里面的节点不能出现在OpenList中
		for(unsigned openlistSize = 0; openlistSize < OpenList.size(); openlistSize++)
		{
			if(isContain(CloseList,OpenList[openlistSize]))
				OpenList.erase(OpenList.begin() + openlistSize);
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