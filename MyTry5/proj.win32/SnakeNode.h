#ifndef __SNAKE_NODE_H__
#define __SNAKE_NODE_H__

enum type{
		strawberry = 1,
		banana = 2,
		orange = 3,
		pear = 4,
		apple = 5,
		mouse = 10,
		wind = 6,
		fire = 7,
		thunder = 8,
		ice = 9
	};

class SnakeNode
{
public: 
	int row;//第几行  
	int col;//第几列  
	int dir;//方向
	int HValue;
	type foodType;
	int generate();
	SnakeNode();	
};

#endif 