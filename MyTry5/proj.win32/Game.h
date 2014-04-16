#ifndef __GAME_H__
#define __GAME_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

class Game : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

	void responseFunc(CCObject* obj);

    // implement the "static node()" method manually
    CREATE_FUNC(Game);
};

#endif  // __HELLOWORLD_SCENE_H__