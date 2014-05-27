#include "Score.h"

Score::Score()
{
	EarthSnakeEatScores = 0;
	MarsSnakeEatScores = 0;
}

int Score::getEarthSnakeEatScores()
{
	return EarthSnakeEatScores;
}

void Score::setEarthSnakeEatScores(int count)
{
	EarthSnakeEatScores = count;
}

int Score::getMarsSnakeEatScores()
{
	return MarsSnakeEatScores;
}

void Score::setMarsSnakeEatScores(int count)
{
	MarsSnakeEatScores = count;
}