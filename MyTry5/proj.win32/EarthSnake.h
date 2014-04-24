#ifndef __EARTH_SNAKE_H__
#define __EARTH_SNAKE_H__

#include <vector>
#include "SnakeNode.h"

class EarthSnake
{
public:
	EarthSnake();
	std::vector<SnakeNode*> snakeBody;
	SnakeNode* snakeHead;
	int eat(SnakeNode*);
	void BodyMove();
	void HeadMove();
	void judgeOver();
};

#endif 