#include "HelloWorldScene.h"
#include "Game.h"
#include "SnakeNode.h"

using namespace cocos2d; 

SnakeNode::SnakeNode()
{
	row = rand()%10;  //0~9
	col = rand()%10;
	dir=1;//∑ΩœÚ…œ
}