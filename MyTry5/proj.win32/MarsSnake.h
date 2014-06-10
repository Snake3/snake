#ifndef __MARS_SNAKE_H__
#define __MARS_SNAKE_H__

#include <vector>
#include "SnakeNode.h"
#include "EarthSnake.h"
#include "Snake.h"
#include "Score.h"

using namespace cocos2d;

class MarsSnake:public Snake
{
public:
	MarsSnake();
	bool eat(SnakeNode*,int*);
	void HeadMove();
	bool MarsSnakeHeadMove(SnakeNode* sFood, EarthSnake* earthSnake, bool UpFlag, bool DownFlag, bool LeftFlag, bool RightFlag);
	bool isContain(std::vector<SnakeNode*> List, SnakeNode* obj);
	//void addCloseList();
	Score getMarsSnakeScores();
private:
	vector<SnakeNode*> CloseList;
	Score MarsSnakeScores;
};

#endif