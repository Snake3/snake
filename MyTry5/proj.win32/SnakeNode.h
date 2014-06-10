#ifndef __SNAKE_NODE_H__
#define __SNAKE_NODE_H__

enum type{
	strawberry = 1,
	banana = 2,
	orange = 3,
	pear = 4,
	apple = 5,
	mango = 6,
	persimmon = 7,
	kiwi = 8,
	pineapple = 9,
	cherry = 10,
	wind = 11,
	fire = 12,
	thunder = 13,
	ice = 14
};

class SnakeNode
{
public: 
	int row;//第几行  
	int col;//第几列  
	int dir;//方向
	int HValue;
	SnakeNode();
	type foodType;
	int generate();
};

#endif 