#include "SpeedSelect.h"
#include "Game.h"

using namespace cocos2d;

float speed = 1.0f;

CCScene* SpeedSelect::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
		SpeedSelect *layer = SpeedSelect::create();
		CC_BREAK_IF(! layer);
		scene->addChild(layer);
	} while (0);

	return scene;
}

bool SpeedSelect::init()
{
	//背景网格
	CCSprite* bg = CCSprite::create("Background.png");
	//位置以图片中心为准
	bg->setPosition(ccp(240,160));
	this->addChild(bg);

	ccColor3B color = ccc3(40, 240, 20);
	//创建文字按钮 
	auto labelSelect = CCLabelTTF::create("Select Speed Level:","宋体",20);
	labelSelect->setColor(color);
	auto labelHigh = CCLabelTTF::create("High", "宋体", 17); 
	labelHigh->setColor(color);
	auto labelMiddle = CCLabelTTF::create("Middle", "宋体", 17); 
	labelMiddle->setColor(color);
	auto labelLow = CCLabelTTF::create("Low", "宋体", 17);
	labelLow->setColor(color);

	//labelSelect->setPosition(ccp(120,237));
	//labelSelect->setVisible(true);
	auto uiSelect = CCMenuItemLabel::create(labelSelect, this, menu_selector(SpeedSelect::menuCloseCallback)); 
	uiSelect->setPosition(ccp(195,197));

	auto uiHigh = CCMenuItemLabel::create(labelHigh, this, menu_selector(SpeedSelect::menuCloseCallback)); 
	uiHigh->setTag(1); 
	uiHigh->setPosition(ccp(120,150));

	auto uiMiddle = CCMenuItemLabel::create(labelMiddle, this, menu_selector(SpeedSelect::menuCloseCallback)); 
	uiMiddle->setTag(2); 
	uiMiddle->setPosition(ccp(200,150));

	auto uiLow = CCMenuItemLabel::create(labelLow, this, menu_selector(SpeedSelect::menuCloseCallback)); 
	uiLow->setTag(3); 
	uiLow->setPosition(ccp(291,150));

	auto menu = CCMenu::create(uiSelect,uiHigh,uiMiddle,uiLow, NULL); 
	menu->setPosition(CCPointZero); 
	this->addChild(menu); 

	return true;
}

void SpeedSelect::menuCloseCallback(CCObject* pSender)
{
	int i = dynamic_cast<CCMenuItemLabel*>(pSender)->getTag();
	switch (i) 
	{ 
	case 1: 
		speed = 0.4f;
		break; 
	case 2: 
		speed = 0.7f;
		break; 
	case 3: 
		speed = 1.0f;
		break;
	default: 
		break; 
	} 

	CCDirector::sharedDirector()->replaceScene(Game::scene());
}