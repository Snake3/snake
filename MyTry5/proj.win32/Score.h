#ifndef __SCORE_H__
#define __SCORE_H__

class Score
{
public:
	int getEarthSnakeEatScores();
	void setEarthSnakeEatScores(int);
	int getMarsSnakeEatScores();
	void setMarsSnakeEatScores(int);
	Score();
private:
	int EarthSnakeEatScores;
	int MarsSnakeEatScores;
};

#endif