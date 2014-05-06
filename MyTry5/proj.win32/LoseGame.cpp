#include "LoseGame.h"
#include "SpeedSelect.h"

using namespace cocos2d;

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

		ccColor3B color = ccc3(225, 0, 200);

		CCSprite* pSprite = CCSprite::create("losebg.jpg");
		CC_BREAK_IF(!pSprite);
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		pSprite->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(pSprite);

		auto labelText = CCLabelTTF::create("Danger!!!", "宋体", 20); 
		labelText->setColor(color);
		labelText->setPosition(ccp(220,270));
		pSprite->addChild(labelText);

		auto labelText2 = CCLabelTTF::create("You want to:", "宋体", 18); 
		labelText2->setPosition(ccp(396,95));
		pSprite->addChild(labelText2);

		auto labelBack = CCLabelTTF::create("Save the Earth", "宋体", 18);
		auto uiStart = CCMenuItemLabel::create(labelBack, this, menu_selector(LoseGame::menuCloseCallback)); 
		uiStart->setTag(1); 
		uiStart->setPosition(ccp(396,75));

		auto menu = CCMenu::create(uiStart, NULL); 
		menu->setPosition(CCPointZero); 
		this->addChild(menu);
		
		/*
		auto labelLeave = CCLabelTTF::create("Move to Mars", "宋体", 18);
		auto uiExit = CCMenuItemLabel::create(labelLeave, this, menu_selector(LoseGame::menuCloseCallback)); 
		uiStart->setTag(2); 
		uiStart->setPosition(ccp(396,75));
		
		auto menu2 = CCMenu::create(uiExit, NULL); 
		menu2->setPosition(CCPointZero); 
		this->addChild(menu2); 
		*/

		bRet = true;
	} while (0);

	return bRet;
}

void LoseGame::menuCloseCallback(CCObject* pSender)
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