#include "LoseGame.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

int GameScore = 0;

CCScene* LoseGame::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		LoseGame *layer = LoseGame::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	return scene;
}

bool LoseGame::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());

		CCSprite* pSprite5 = CCSprite::create("losebg.png");
		CC_BREAK_IF(!pSprite5);
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		pSprite5->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(pSprite5);

		char a[20];
		labelText1 = CCLabelTTF ::create();
		labelText1->setFontName("Calibri");
		labelText1->setFontSize(20);
		labelText1->setString(itoa(GameScore,a,10));
		labelText1->setPosition(ccp(481,100));
		this->addChild(labelText1);

		CCMenuItemImage *pTryItem = CCMenuItemImage::create("try.png","try.png",this,menu_selector(LoseGame::menuCloseCallback));
		pTryItem->setTag(1);
		pTryItem->setPosition(ccp(398,28)); 

		auto menu = CCMenu::create(pTryItem, NULL); 
		menu->setPosition(CCPointZero); 
		this->addChild(menu);
		
		bRet = true;
	} while (0);

	return bRet;
}

void LoseGame::menuCloseCallback(CCObject* pSender)
{
	//C++形式的强制类型转换
	int i = dynamic_cast<CCMenuItemImage*>(pSender)->getTag();
	switch (i) 
	{ 
	case 1: 
		CCDirector::sharedDirector()->replaceScene(HelloWorld::scene()); 
		break; 
		/*
	case 2: 
		CCDirector::sharedDirector()->end();
		break; 
		*/
	default: 
		break; 
	} 
}

void LoseGame::setEarthSnakeEatCount(int count)
{
	EarthSnakeEatCount = count;
}

int LoseGame::getEarthSnakeEatCount()
{
	return EarthSnakeEatCount;
}