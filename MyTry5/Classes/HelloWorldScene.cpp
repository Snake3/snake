#include "HelloWorldScene.h"
//#include <stdio.h>
#include "GameHelp.h"
#include "Game.h"
#include "SpeedSelect.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

	CCLog("HelloWorld::scene() ",1);
    // return the scene
    return scene;
}

bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		CCSprite* pSprite2 = CCSprite::create("HelloWorld.png");
		CC_BREAK_IF(! pSprite2);
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		pSprite2->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(pSprite2);

		CCMenuItemImage *pPlayItem = CCMenuItemImage::create("play.png","play.png",this,menu_selector(HelloWorld::menuCloseCallback));
		pPlayItem->setTag(1);
		pPlayItem->setPosition(ccp(400,345)); 

		CCMenuItemImage *pHelpItem = CCMenuItemImage::create("help.png","help.png",this,menu_selector(HelloWorld::menuCloseCallback));
		pHelpItem->setTag(2);
		pHelpItem->setPosition(ccp(400,275));

		CCMenuItemImage *pExitItem = CCMenuItemImage::create("exit.png","exit.png",this,menu_selector(HelloWorld::menuCloseCallback));
		pExitItem->setTag(3);
		pExitItem->setPosition(ccp(396,151));

		auto menu = CCMenu::create(pPlayItem, pHelpItem, pExitItem, NULL); 
		menu->setPosition(CCPointZero); 
		pSprite2->addChild(menu); 

		bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	//C++形式的强制类型转换
	int i = dynamic_cast<CCMenuItemImage*>(pSender)->getTag();
	switch (i) 
	{ 
		case 1: 
			//CCLog("go to Game");
			CCDirector::sharedDirector()->replaceScene(SpeedSelect::scene()); 
			break; 
		case 2: 
			//CCLog("go to Help"); 
			CCDirector::sharedDirector()->replaceScene(GameHelp::scene()); 
			break; 
		case 3: 
			CCDirector::sharedDirector()->end();
			break;
		default: 
			break; 
	} 
}
