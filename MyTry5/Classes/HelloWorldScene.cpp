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

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

		
#if 0
        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

        // 2. Add a label shows "Hello World".

        // Create a label and initialize with string "Hello World".
        CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
        CC_BREAK_IF(! pLabel);

        // Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        pLabel->setPosition(ccp(size.width / 2, size.height - 50));

        // Add the label to HelloWorld layer as a child layer.
        this->addChild(pLabel, 1);

        // 3. Add add a splash screen, show the cocos2d splash image.
        CCSprite* pSprite = CCSprite::create("Background.png");
        CC_BREAK_IF(! pSprite);

        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pSprite, 0);

		CCSprite* pSprite3 = CCSprite::create("Grass Block.png");
        CC_BREAK_IF(! pSprite3);
        pSprite3->setPosition(ccp(size.width/2, size.height/2));
        this->addChild(pSprite3, 0);

		CCSprite* pSprite2 = CCSprite::create("p8.png");
        CC_BREAK_IF(! pSprite2);
        pSprite2->setPosition(ccp(size.width/2, size.height/2));
        this->addChild(pSprite2, 0);
#endif

	//创建文字按钮 
	ccColor3B color = ccc3(225, 0, 60);
	auto labelStart = CCLabelTTF::create("Start Game", "宋体", 18); 
	labelStart->setColor(color);
	auto labelHelp = CCLabelTTF::create("Game Help", "宋体", 18); 
	labelHelp->setColor(color);
	auto labelExit = CCLabelTTF::create("Exit Game", "宋体", 18); 
	labelExit->setColor(color);
	//CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
     //       "CloseNormal.png",
     //       "CloseSelected.png",
     //       this,
     //       menu_selector(HelloWorld::menuCloseCallback));
 
	auto uiStart = CCMenuItemLabel::create(labelStart, this, menu_selector(HelloWorld::responseFunc)); 
    uiStart->setTag(1); 
    uiStart->setPosition(CCPoint(50,200)); 
      
    auto uiHelp = CCMenuItemLabel::create(labelHelp, this, menu_selector(HelloWorld::menuCloseCallback)); 
    uiHelp->setTag(2); 
    uiHelp->setPosition(CCPoint(50,150)); 
      
    auto uiExit = CCMenuItemLabel::create(labelExit, this, menu_selector(HelloWorld::menuCloseCallback)); 
    uiExit->setTag(3); 
    uiExit->setPosition(CCPoint(50,50)); 
      
    auto menu = CCMenu::create(uiStart,uiHelp, uiExit, NULL); 
    menu->setPosition(CCPoint(0,0)); 
    this->addChild(menu, 1); 
	
	CCSprite* pSprite2 = CCSprite::create("HelloWorld.png");
    CC_BREAK_IF(! pSprite2);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    pSprite2->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pSprite2, 0);
	
	//添加一个怪物,蛇
	pSprite = CCSprite::create("p6.png");
	CC_BREAK_IF(! pSprite);
	pSprite->setPosition(ccp(250,20));
	CCAction* move = CCMoveTo::create(2.0f,ccp(100,20));
	pSprite->runAction(move);
	this->addChild(pSprite);

		bRet = true;
		//printf("retainCount after init: %d", pSprite->retainCount());
    } while (0);
	CCLog("HelloWorld::init() ", 2);
    return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	//C++形式的强制类型转换
	int i = dynamic_cast<CCMenuItemLabel*>(pSender)->getTag();
	switch (i) 
	{ 
		case 1: 
			CCLog("go to Game");
			
			break; 
		case 2: 
			CCLog("go to Help"); 
			CCDirector::sharedDirector()->replaceScene(GameHelp::scene()); 
			break; 
		case 3: 
			CCDirector::sharedDirector()->end();
			break;
		case 4: 
		{ 
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) 
				MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert"); 
			return; 
			#endif 
 
			CCDirector::sharedDirector()->end(); 
 
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
			exit(0); 
			#endif 
		} 
			break; 
		default: 
			break; 
		} 
	
		// "close" menu item clicked
	//CCLog("HelloWorld::menuCloseCallback(CCObject* pSender) ",3);
	//CCDirector::sharedDirector()->end();
}

void HelloWorld::responseFunc(CCObject* obj)
{
	CCDirector::sharedDirector()->replaceScene(SpeedSelect::scene()); 
}
