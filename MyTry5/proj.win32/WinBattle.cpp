#include "WinBattle.h"
#include "SpeedSelect.h"

using namespace cocos2d;

CCScene* WinBattle::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		WinBattle *layer = WinBattle::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	return scene;
}

bool WinBattle::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());

		ccColor3B color = ccc3(20, 0, 225);

		CCSprite* pSprite = CCSprite::create("winbg.png");
		CC_BREAK_IF(!pSprite);
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		pSprite->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(pSprite);

		auto labelText = CCLabelTTF::create("You win!!!", "宋体", 24); 
		labelText->setColor(color);
		labelText->setPosition(ccp(380,380));
		pSprite->addChild(labelText);

		auto labelText2 = CCLabelTTF::create("Next to:", "宋体", 18); 
		labelText2->setColor(color);
		labelText2->setPosition(ccp(380,340));
		pSprite->addChild(labelText2);

		auto labelBack = CCLabelTTF::create("Try again", "宋体", 18);
		labelBack->setColor(color);
		auto uiStart = CCMenuItemLabel::create(labelBack, this, menu_selector(WinBattle::menuCloseCallback)); 
		uiStart->setTag(1); 
		uiStart->setPosition(ccp(380,312));

		auto menu = CCMenu::create(uiStart, NULL); 
		menu->setPosition(CCPointZero); 
		this->addChild(menu);

		CCMenuItemImage *winImage = CCMenuItemImage::create("win.png","win.png");
		winImage->setPosition(ccp(390, 255));
		pSprite->addChild(winImage);

		bRet = true;
	} while (0);

	return bRet;
}

void WinBattle::menuCloseCallback(CCObject* pSender)
{
	//C++形式的强制类型转换
	int i = dynamic_cast<CCMenuItemLabel*>(pSender)->getTag();
	switch (i) 
	{ 
	case 1: 
		CCDirector::sharedDirector()->replaceScene(SpeedSelect::scene()); 
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