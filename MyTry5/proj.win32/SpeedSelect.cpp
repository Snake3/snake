#include "SpeedSelect.h"
#include "HelloWorldScene.h"

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
	bg->setPosition(ccp(400,240));
	this->addChild(bg);

	ccColor3B color = ccc3(40, 240, 20);

	CCTextFieldTTF* text = CCTextFieldTTF::textFieldWithPlaceHolder(
		"Input Your Name...", "Arial", 24);
	text->setPosition(ccp(400, 320));
	text->setColor(ccc3(88,88,88));
	this->addChild(text);
	text->attachWithIME();//接受键盘输入信息

	//创建文字按钮 
	auto labelHigh = CCLabelTTF::create("High", "宋体", 19); 
	labelHigh->setColor(color);
	auto labelMiddle = CCLabelTTF::create("Middle", "宋体", 19); 
	labelMiddle->setColor(color);
	auto labelLow = CCLabelTTF::create("Low", "宋体", 19);
	labelLow->setColor(color);

	CCSprite* select = CCSprite::create("select.png");
	select->setPosition(ccp(375,291));
	this->addChild(select);

	auto uiHigh = CCMenuItemLabel::create(labelHigh, this, menu_selector(SpeedSelect::menuCloseCallback)); 
	uiHigh->setTag(1); 
	uiHigh->setPosition(ccp(300,258));

	auto uiMiddle = CCMenuItemLabel::create(labelMiddle, this, menu_selector(SpeedSelect::menuCloseCallback)); 
	uiMiddle->setTag(2); 
	uiMiddle->setPosition(ccp(390,258));

	auto uiLow = CCMenuItemLabel::create(labelLow, this, menu_selector(SpeedSelect::menuCloseCallback)); 
	uiLow->setTag(3); 
	uiLow->setPosition(ccp(480,258));

	auto menu = CCMenu::create(uiHigh,uiMiddle,uiLow, NULL); 
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
		speed = 0.3f;
		break; 
	case 2: 
		speed = 0.6f;
		break; 
	case 3: 
		speed = 1.0f;
		break;
	default: 
		break; 
	} 

	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}