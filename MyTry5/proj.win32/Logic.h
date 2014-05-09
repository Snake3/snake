#ifndef __LOGIC_H__
#define __LOGIC_H__

#include "cocos2d.h"

class Logic
{
private:
	static Logic* mInstance;
public:
	~Logic();
	static Logic* getInstance();
	Logic();
	bool init();
};

#endif