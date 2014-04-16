#include "HelloWorldScene.h"
//#include <stdio.h>
#include "Game.h"

using namespace cocos2d;

CCScene* Game::scene()
{
    CCScene * scene = NULL;
    do 
    {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        Game *layer = Game::create();
        CC_BREAK_IF(! layer);
        scene->addChild(layer);
    } while (0);

    return scene;
}

bool Game::init()
{
	//背景网格
	CCSprite* bg = CCSprite::create("grid5.jpg");
	bg->setPosition(ccp(161,160));
	this->addChild(bg);

	//精灵蛇
	CCSprite* snake = CCSprite::create("p7.png");
	snake->setPosition(ccp(142,46));
	this->addChild(snake);

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//创建文字按钮 
	auto labelTry = CCLabelTTF::create("Try Again", "宋体", 18); 
	auto labelPause = CCLabelTTF::create("Pause/Start", "宋体", 18); 
	auto labelBack = CCLabelTTF::create("Main Menu", "宋体", 18); 

	auto uiTry = CCMenuItemLabel::create(labelTry, this, menu_selector(Game::responseFunc)); 
    uiTry->setTag(1); 
	uiTry->setPosition(ccp(size.width-90,250)); 
      
    auto uiPause = CCMenuItemLabel::create(labelPause, this, menu_selector(Game::responseFunc)); 
    uiPause->setTag(2); 
    uiPause->setPosition(ccp(size.width-90,150)); 
      
    auto uiBack = CCMenuItemLabel::create(labelBack, this, menu_selector(Game::menuCloseCallback)); 
    uiBack->setTag(3); 
    uiBack->setPosition(ccp(size.width-90,50)); 
      
    auto menu = CCMenu::create(uiTry, uiPause, uiBack, NULL); 
    menu->setPosition(CCPointZero); 
    this->addChild(menu, 1); 

    return true;
}

void Game::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

void Game::responseFunc(CCObject* obj)
{
	//CCAction* move = CCMoveTo::create(2.0f,ccp(100,20));
	//pSprite->runAction(move);

}
