#ifndef __MARS_SNAKE_H__
#define __MARS_SNAKE_H__

#include <vector>
#include "SnakeNode.h"
#include "EarthSnake.h"
#include "Snake.h"

using namespace cocos2d;

class MarsSnake:public Snake
{
public:
	MarsSnake();
	bool eat(SnakeNode*);
	void HeadMove();
	bool MarsSnakeHeadMove(SnakeNode* sFood,EarthSnake* earthSnake);
	bool isContain(std::vector<SnakeNode*> List, SnakeNode* obj);
};

#endif