#ifndef __EARTH_SNAKE_H__
#define __EARTH_SNAKE_H__

#include <vector>
#include "SnakeNode.h"
#include "Snake.h"
#include "Score.h"

class EarthSnake:public Snake
{
public:
	EarthSnake();
	bool eat(SnakeNode*, int*);
	void HeadMove();
	Score getEarthSnakeScores();
	//void judgeOver();
private:
	Score EarthSnakeScores;
};

#endif 