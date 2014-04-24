#ifndef __MARS_SNAKE_H__
#define __MARS_SNAKE_H__

#include <vector>
#include "SnakeNode.h"

class MarsSnake{
public:
	MarsSnake();
	std::vector<SnakeNode*> snakeBody;
	SnakeNode* snakeHead;
	int eat(SnakeNode*);
	void BodyMove();
	void HeadMove(SnakeNode*);
};

#endif