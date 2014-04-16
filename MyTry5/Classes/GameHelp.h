#ifndef __Snake__GameHelp__H__
#define __Snake__GameHelp__H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

class GameHelp : public cocos2d::CCLayer
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    void menuBackToMain(CCObject* pSender);
    CREATE_FUNC(GameHelp);
};

#endif  // __HELLOWORLD_SCENE_H__