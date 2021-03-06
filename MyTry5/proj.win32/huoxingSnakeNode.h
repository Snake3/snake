#ifndef __HUOXING_SNAKE_NODE_H__
#define __HUOXING_SNAKE_NODE_H__

#include <iostream>
#include "SnakeNode.h"

using namespace std;

//枚举
typedef enum {  
	UP=1,  
	DOWN=2,  
	LEFT=3,  
	RIGHT=4  
};

//蛇的节点
class huoxingSnakeNode : public SnakeNode
{

	int row;//第几行  
	int col;//第几列  
	int dir;//方向  
public:  
	huoxingSnakeNode()
	{
		row = rand()%10;  //0~9
		col = rand()%10;
		dir=1;//方向上
	}

	void BodyMove();
	void HeadMove();
	void eat();
};

#endif  