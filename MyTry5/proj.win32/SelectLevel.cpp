#include "SelectLevel.h"
#include "Game.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

int level = 0;

CCScene* SelectLevel::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
		SelectLevel *layer = SelectLevel::create();
		CC_BREAK_IF(! layer);
		scene->addChild(layer);
	} while (0);

	return scene;
}

bool SelectLevel::init()
{
	//背景网格
	CCSprite* bg = CCSprite::create("LevelSelect.png");
	//位置以图片中心为准
	bg->setPosition(ccp(400,240));
	this->addChild(bg);

	CCMenuItemImage *Level1 = CCMenuItemImage::create("Level1.png","Level1.png",this,menu_selector(SelectLevel::menuCloseCallback));
	Level1->setTag(1);
	Level1->setPosition(ccp(90,413));

	CCMenuItemImage *Level2 = CCMenuItemImage::create("Level2.png","Level2.png",this,menu_selector(SelectLevel::menuCloseCallback));
	Level2->setTag(2);
	Level2->setPosition(ccp(194,415));

	CCMenuItemImage *Level3 = CCMenuItemImage::create("Level3.png","Level3.png",this,menu_selector(SelectLevel::menuCloseCallback));
	Level3->setTag(3);
	Level3->setPosition(ccp(298,416));

	CCMenuItemImage *LevelBack = CCMenuItemImage::create("LevelBack.png","LevelBack.png",this,menu_selector(SelectLevel::menuCloseCallback));
	LevelBack->setTag(123);
	LevelBack->setPosition(ccp(92,40));

	auto menu = CCMenu::create(Level1,Level2,Level3,LevelBack, NULL); 
	menu->setPosition(CCPointZero); 
	this->addChild(menu); 

	return true;
}

void SelectLevel::menuCloseCallback(CCObject* pSender)
{
	int i = dynamic_cast<CCMenuItemImage*>(pSender)->getTag();

	switch(i)
	{
		case 123:
			CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
			break;
		default:
			level = i;
			CCDirector::sharedDirector()->replaceScene(Game::scene());
			break;
	}
}