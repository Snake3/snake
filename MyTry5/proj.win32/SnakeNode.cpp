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

int SnakeNode::generate(){
	srand((unsigned)time(0));
	row = rand()%23 + 1;  
	col = rand()%14;
	foodType = type(rand()%10 + 1);
	return 0;
}