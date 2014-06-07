#pragma once
#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <vector>
#include "SnakeNode.h"

class Snake
{
public:
	Snake();
	std::vector<SnakeNode*> snakeBody;
	SnakeNode* snakeHead;
	virtual bool eat(SnakeNode*,int*) = 0;
	void BodyMove();
	virtual void HeadMove() = 0;
};

#endif