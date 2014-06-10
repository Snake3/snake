#include "HelloWorldScene.h"
#include "Game.h"
#include "SnakeNode.h"

using namespace cocos2d; 

SnakeNode::SnakeNode()
{
	row = rand()%10;  //0~9
	col = rand()%10;
	dir=1;//∑ΩœÚ…œ
	foodType = orange;
}

int SnakeNode::generate()
{
	srand((unsigned)time(0));
	row = rand()%25;  
	col = rand()%15;
	foodType = (type)(rand()%14 + 1);
	return 0;
}