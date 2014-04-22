#ifndef __SPEED_SELECT_H__
#define __SPEED_SELECT_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"

class SpeedSelect : public cocos2d::CCLayer
{
public:
	virtual bool init();  
	static cocos2d::CCScene* scene();
	void menuCloseCallback(CCObject* pSender);
	CREATE_FUNC(SpeedSelect);


};

#endif 