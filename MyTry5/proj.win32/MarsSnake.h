#ifndef __MARS_SNAKE_H__
#define __MARS_SNAKE_H__

#include <vector>
#include "SnakeNode.h"
#include "EarthSnake.h"

using namespace cocos2d;

class MarsSnake{
public:
	MarsSnake();
	std::vector<SnakeNode*> snakeBody;
	SnakeNode* snakeHead;
	int eat(SnakeNode*);
	void BodyMove();
	void HeadMove(SnakeNode* sFood,EarthSnake* earthSnake);
	bool isContain(std::vector<SnakeNode*> List, SnakeNode* obj);
};

#endif