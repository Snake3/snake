#ifndef __EARTH_SNAKE_H__
#define __EARTH_SNAKE_H__

#include <vector>
#include "SnakeNode.h"
#include "Snake.h"

class EarthSnake:public Snake
{
public:
	EarthSnake();
	bool eat(SnakeNode*);
	void HeadMove();
	//void judgeOver();
};

#endif 