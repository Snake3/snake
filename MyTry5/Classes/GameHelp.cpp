#include "HelloWorldScene.h"
#include "GameHelp.h"

using namespace cocos2d;

CCScene* GameHelp::scene()
{
    auto scene = CCScene::create(); 
	auto layer = GameHelp::create(); 
	scene->addChild(layer); 
	return scene;
}

// on "init" you need to initialize your instance
bool GameHelp::init()
{
	if(!CCLayer::init()) 
	{ 
		return false; 
	} 
	
	CCSprite* pSprite2 = CCSprite::create("background1.jpg");
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    pSprite2->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pSprite2, 0);

	ccColor3B color = ccc3(0, 0, 0);
	//创建帮助文字 
	auto labelHelp = CCLabelTTF::create("Mouse Click and Move", "宋体", 24); 
	labelHelp->setColor(color);
	labelHelp->setPosition(CCPoint(210,160)); 
	this->addChild(labelHelp); 

	//创建返回按钮
	auto labelBack = CCLabelTTF::create("MainMenu", "宋体", 18); 
	labelBack->setColor(color);
	//auto uiBack = CCMenuItemLabel::create(labelBack, this, menu_selector(GameHelp::menuBackToMain)); 
	//uiBack->setPosition(CCPoint(50,50)); 

	CCMenuItemImage* itemBack = CCMenuItemImage::create("back.png",
		"back.png",
		"back.png",
		this,
		menu_selector(GameHelp::menuBackToMain));
	itemBack->setPosition(ccp(20,30));

	//CCSprite* pSprite = CCSprite::create("back.png");
	//auto uiBack = CCMenuItem::create(pSprite, menu_selector(GameHelp::menuBackToMain)); 
    //pSprite->setPosition(CCPoint(50,50));
    //this->addChild(pSprite, 0);

	auto menu = CCMenu::create(itemBack,NULL); 
	menu->setPosition(CCPoint(0,0)); 
	this->addChild(menu); 

	return true;
}

void GameHelp::menuBackToMain(CCObject* pSender) 
{ 
	//CCDirector::sharedDirector()->end();
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
} 

