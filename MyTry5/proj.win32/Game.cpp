#include "HelloWorldScene.h"
#include "Game.h"
#include "SimpleAudioEngine.h"
#include "LoseGame.h"
#include "WinBattle.h"

using namespace cocos2d;

int direction = 1;					//初始化方向
extern float speed;
bool winFlag = false;

SnakeNode *sFood = new SnakeNode();	//食物节点初始化
EarthSnake *earthSnake = new EarthSnake();
MarsSnake *marsSnake = new MarsSnake();

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
	//位置以图片中心为准
	bg->setPosition(ccp(161,160));
	this->addChild(bg);

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//创建文字按钮 
	auto labelResume = CCLabelTTF::create("Resume", "宋体", 18); 
	auto labelPause = CCLabelTTF::create("Pause", "宋体", 18); 
	auto labelBack = CCLabelTTF::create("Main Menu", "宋体", 18); 

	//方向键
	CCMenuItemImage *pUpItem = CCMenuItemImage::create("Up.png","UpSelected.png",this,menu_selector(Game::setDirection) );
	CCMenuItemImage *pDownItem = CCMenuItemImage::create("Down.png","DownSelected.png",this,menu_selector(Game::setDirection) );
	CCMenuItemImage *pLeftItem = CCMenuItemImage::create("Left.png","LeftSelected.png",this,menu_selector(Game::setDirection) );
	CCMenuItemImage *pRightItem = CCMenuItemImage::create("Right.png","RightSelected.png",this,menu_selector(Game::setDirection) );

	auto uiTry = CCMenuItemLabel::create(labelResume, this, menu_selector(Game::responseFunc)); 
    uiTry->setTag(11); 
	uiTry->setPosition(ccp(size.width-90,250)); 
      
    auto uiPause = CCMenuItemLabel::create(labelPause, this, menu_selector(Game::responseFunc)); 
    uiPause->setTag(12); 
    uiPause->setPosition(ccp(size.width-90,230)); 
      
    auto uiBack = CCMenuItemLabel::create(labelBack, this, menu_selector(Game::menuCloseCallback)); 
    uiBack->setTag(13); 
    uiBack->setPosition(ccp(size.width-90,210)); 	
      
	pUpItem->setTag(1);
	pUpItem->setPosition(ccp(size.width-80,150)); 
	
	pDownItem->setTag(2);
	pDownItem->setPosition(ccp(size.width-80,70)); 

	pLeftItem->setTag(3);
	pLeftItem->setPosition(ccp(size.width-120,110)); 

	pRightItem->setTag(4);
	pRightItem->setPosition(ccp(size.width-40,110)); 

    auto menu = CCMenu::create(uiTry,uiPause,uiBack,pUpItem,pDownItem,pLeftItem,pRightItem, NULL); 
    menu->setPosition(CCPointZero); 
    this->addChild(menu); 
	
	//this->schedule(schedule_selector(Game::myGameLogic),1);
	this->schedule(schedule_selector(Game::gameLogic),speed);
	
	if(speed == 0.4f)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("high.mp3",true);
	}
	else if(speed == 0.7f)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("middle.mp3",true);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("low.mp3",true);
	}

    return true;
}

void Game::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector() ->pause();
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

//进入游戏后的菜单响应
void Game::responseFunc(CCObject* obj)
{	
	int i = dynamic_cast<CCMenuItemLabel*>(obj)->getTag();
	switch (i) 
	{ 
	case 11: 
		CCDirector::sharedDirector() ->resume();
		break; 
	case 12: 
		pauseGame(obj);
		break; 
	case 13: 
		CCDirector::sharedDirector()->end();
		break;
	default: 
		break; 
	} 
}

//游戏暂停
void Game::pauseGame(CCObject* sender)    
{    
	CCDirector::sharedDirector() ->pause();     
}    

//清除、消失的函数
void Game::myDefine(CCNode* who)
{	
	//从图层中删去
	who->removeFromParentAndCleanup(true);
}

//设置贪食蛇的方向
void Game::setDirection(CCObject* obj)
{

	//this->schedule(schedule_selector(Game::run),1);
	int i = dynamic_cast<CCMenuItemImage*>(obj)->getTag();
	switch (i) 
	{ 
	case UP:
		if((earthSnake->snakeHead->dir != UP) && (earthSnake->snakeHead->dir != DOWN))
		{
			//方向切换会闪是因为这个原因
			//this->unscheduleAllSelectors();
			direction = UP;
			this->schedule(schedule_selector(Game::gameLogic),speed);
		}
		break; 
	case DOWN:
		if((earthSnake->snakeHead->dir != DOWN) && (earthSnake->snakeHead->dir != UP))
		{
			//this->unscheduleAllSelectors();
			direction = DOWN;
			this->schedule(schedule_selector(Game::gameLogic),speed);
		}
		break; 
	case LEFT:
		if((earthSnake->snakeHead->dir != LEFT) && (earthSnake->snakeHead->dir != RIGHT))
		{
			//this->unscheduleAllSelectors();
			direction = LEFT;
			this->schedule(schedule_selector(Game::gameLogic),speed);
		}
		break;
	case RIGHT:
		if((earthSnake->snakeHead->dir != RIGHT) && (earthSnake->snakeHead->dir != LEFT))
		{
			//this->unscheduleAllSelectors();
			direction = RIGHT;
			this->schedule(schedule_selector(Game::gameLogic),speed);
		}
		break;
	default: 
		break;
	}
}

void Game::createFood(EarthSnake* earthSnake,MarsSnake* marsSnake,bool haveEat){
	bool flag = true;
	srand((unsigned)time(0));
	if(haveEat){
	sFood->row = rand()%10;  
	sFood->col = rand()%10;
	while(flag){
			for(unsigned int i=0;i<marsSnake->snakeBody.size();i++){
					if(((marsSnake->snakeBody[i]->row == sFood->row)&&(marsSnake->snakeBody[i]->col == sFood->col))||((marsSnake->snakeHead->row == sFood->row)&&(marsSnake->snakeHead->col == sFood->col))){
						sFood->row = rand()%10;
						sFood->col = rand()%10;
						i = 0;
					}
				}
				flag = false;
				for(unsigned int i=0;i<earthSnake->snakeBody.size();i++){
					if(((earthSnake->snakeBody[i]->row == sFood->row)&&(earthSnake->snakeBody[i]->col == sFood->col))||((earthSnake->snakeHead->row == sFood->row)&&(earthSnake->snakeHead->col == sFood->col))){
						sFood->row = rand()%10;
						sFood->col = rand()%10;
						i = 0;
						flag = true;
					}
				}
			}
	}
}


//计算出蛇下个位置每个节点的坐标及判断赢的条件
void Game::gameLogic(float dt)  
{     
	bool haveEat = false;
	earthSnake->snakeHead->dir = direction;

	earthSnake->BodyMove();
	marsSnake->BodyMove();

	earthSnake->HeadMove();
	winFlag = marsSnake->MarsSnakeHeadMove(sFood,earthSnake);

	

	haveEat = earthSnake->eat(sFood);
	createFood(earthSnake,marsSnake,haveEat);
	if(haveEat)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("cheer.wav");
	}
	
	haveEat = marsSnake->eat(sFood);
	createFood(earthSnake,marsSnake,haveEat);
	if(haveEat)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("cheer.wav");
	}

	this->draw(earthSnake,marsSnake,sFood);

	//赢的条件
	if(winFlag)
	{
		this->unscheduleAllSelectors();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		CCDirector::sharedDirector()->
			CCDirector::sharedDirector()->replaceScene(WinBattle::scene());
		winFlag = false;
		
		return;
	}
}

//输了的条件
void Game::judgeOver()
{
	//撞墙
	if(earthSnake->snakeHead->col >= 10 || earthSnake->snakeHead->col < 0 || earthSnake->snakeHead->row < 0 || earthSnake->snakeHead->row >= 10)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		//this->~CCLayer();
		CCDirector::sharedDirector()->replaceScene(LoseGame::scene()); 
	}
	//撞自己
	for(unsigned int i=0;i<earthSnake->snakeBody.size();i++)  
	{  
		if((earthSnake->snakeHead->col == earthSnake->snakeBody[i]->col) && (earthSnake->snakeHead->row == earthSnake->snakeBody[i]->row))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			CCDirector::sharedDirector()->replaceScene(LoseGame::scene()); 
		}
	}
	//撞火星蛇
	vector<SnakeNode*> huoBody = marsSnake->snakeBody;
	huoBody.push_back(marsSnake->snakeHead);
	for(unsigned int i=0;i<huoBody.size();i++)
	{  
		if((earthSnake->snakeHead->col == huoBody[i]->col) && (earthSnake->snakeHead->row == huoBody[i]->row))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			CCDirector::sharedDirector()->replaceScene(LoseGame::scene()); 
		}
	}
}

//绘制蛇和绘制食物
void Game::draw(EarthSnake *earthSnake,MarsSnake *marsSnake,SnakeNode* sFood)
{
	CCFiniteTimeAction * delay = CCDelayTime::create(speed);
	CCCallFuncN* disappear = CCCallFuncN::create(this,callfuncN_selector(Game::myDefine));
	CCAction *seq = CCSequence::create(delay,disappear,NULL);
	CCAction *disahead = CCSequence::create(delay,disappear,NULL);

	//绘制蛇头  
	CCSprite *head=CCSprite::create("p9.png");
	head->setPosition(ccp(earthSnake->snakeHead->row*32+16,earthSnake->snakeHead->col*32+16));
	this->addChild(head);
	head->runAction(seq);

	
	//火星蛇头
	CCSprite *ahead=CCSprite::create("p6.png");
	ahead->setPosition(ccp(marsSnake->snakeHead->row*32+16,marsSnake->snakeHead->col*32+16));
	this->addChild(ahead);
	ahead->runAction(disahead);


	//绘制食物  
	CCAction *disFood=CCSequence::create(delay,disappear,NULL);
	CCSprite *food=CCSprite::create("p8.png");
	food->setPosition(ccp(sFood->row*32+16,sFood->col*32+16));
	this->addChild(food);
	food->runAction(disFood);

	//绘制身体  
	for(unsigned int i=0;i<earthSnake->snakeBody.size();i++)  
	{  
		CCAction *disBody=CCSequence::create(delay,disappear,NULL);
		CCSprite *body=CCSprite::create("p5.png");
		body->setPosition(ccp(earthSnake->snakeBody[i]->row*32+16,earthSnake->snakeBody[i]->col*32+16));
		this->addChild(body);
		body->runAction(disBody);
	}  


	for(unsigned int i=0;i<marsSnake->snakeBody.size();i++)  
	{  
		CCAction *disaBody=CCSequence::create(delay,disappear,NULL);
		CCSprite *abody=CCSprite::create("p7.png");
		abody->setPosition(ccp(marsSnake->snakeBody[i]->row*32+16,marsSnake->snakeBody[i]->col*32+16));
		this->addChild(abody);
		abody->runAction(disaBody);
	}

}
