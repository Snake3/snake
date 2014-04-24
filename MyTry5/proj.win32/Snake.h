#pragma once

#ifndef __SNAKE_NODE_H__
#define __SNAKE_NODE_H__

#include <vector>
#include "SnakeNode.h"

class Snake
{
public:
	vector<SnakeNode> snakeBody;
	SnakeNode* snakeHead;
	virtual void eat(){};
	virtual void BodyMove(){};
	virtual void HeadMove(){};
};

#endif 