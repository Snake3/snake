#include "HelloWorldScene.h"
#include "Game.h"
#include "SimpleAudioEngine.h"
#include "LoseGame.h"
#include "WinBattle.h"

using namespace cocos2d;

int direction = 1;					//初始化方向
extern float speed;
extern vector<SnakeNode*> barriers;
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
	bg = CCSprite::create("grid5.jpg");
	//位置以图片中心为准
	bg->setPosition(ccp(400,240));
	this->addChild(bg);

	CCSize size = CCDirector::sharedDirector()->getWinSize();	

	CCMenuItemImage *pExitItem = CCMenuItemImage::create("exit2.png","exit2Selected.png",this,menu_selector(Game::responseFunc));
	pExitItem->setTag(11);
	pExitItem->setPosition(ccp(35,436)); 

	CCMenuItemImage *pPlayItem = CCMenuItemImage::create("play2.png","play2Selected.png",this,menu_selector(Game::responseFunc));
	pPlayItem->setTag(12);
	pPlayItem->setPosition(ccp(120,436));

	CCMenuItemImage *pPauseItem = CCMenuItemImage::create("pause2.png","pause2Selected.png",this,menu_selector(Game::responseFunc));
	pPauseItem->setTag(13);
	pPauseItem->setPosition(ccp(168,436));

	auto menu = CCMenu::create(pExitItem, pPlayItem, pPauseItem, NULL); 
	menu->setPosition(CCPointZero); 
	bg->addChild(menu); 

	this->initSnakeBody();
	this->schedule(schedule_selector(Game::gameLogic),speed);
	
	if(speed == 0.3f)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("high.mp3",true);
	}
	else if(speed == 0.6f)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("middle.mp3",true);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("low.mp3",true);
	}

	//触摸屏幕响应事件
	this->setTouchEnabled(true);//使layer具有响应触摸事件的能力
	CCDirector::sharedDirector()->getTouchDispatcher()
		->addTargetedDelegate(this, 0, true);
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
	int i = dynamic_cast<CCMenuItemImage*>(obj)->getTag();
	switch (i) 
	{ 
	case 11: 
		CCDirector::sharedDirector()->end();
		break; 
	case 12: 
		CCDirector::sharedDirector()->resume();
		break; 
	case 13: 
		CCDirector::sharedDirector()->pause();  
		break;
	default: 
		break; 
	} 
}   

//清除、消失的函数
void Game::myDefine(CCNode* who)
{	
	//从图层中删去
	who->removeFromParentAndCleanup(true);
}

#if 0
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
#endif

void Game::createFood(EarthSnake* earthSnake,MarsSnake* marsSnake,bool haveEat){
	bool flag = true;
	srand((unsigned)time(0));
	if(haveEat){
	sFood->row = rand()%23 + 1;  
	sFood->col = rand()%14;
	while(flag){
			for(unsigned int i=0;i<marsSnake->snakeBody.size();i++){
					if(((marsSnake->snakeBody[i]->row == sFood->row)&&(marsSnake->snakeBody[i]->col == sFood->col))||((marsSnake->snakeHead->row == sFood->row)&&(marsSnake->snakeHead->col == sFood->col))){
						sFood->row = rand()%23 + 1;
						sFood->col = rand()%14;
						i = 0;
					}
				}
				flag = false;
				for(unsigned int i=0;i<earthSnake->snakeBody.size();i++){
					if(((earthSnake->snakeBody[i]->row == sFood->row)&&(earthSnake->snakeBody[i]->col == sFood->col))||((earthSnake->snakeHead->row == sFood->row)&&(earthSnake->snakeHead->col == sFood->col))){
						sFood->row = rand()%23 + 1;
						sFood->col = rand()%14;
						i = 0;
					}
				}
				flag = false;
				for(unsigned int i=0;i<barriers.size();i++){
					if(((barriers[i]->row == sFood->row)&&(barriers[i]->col == sFood->col))){
						sFood->row = rand()%23 + 1;
						sFood->col = rand()%14;
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
		this->restart();
		CCDirector::sharedDirector()->replaceScene(WinBattle::scene());
		winFlag = false;
		
		return;
	}
}

//输了的条件
void Game::judgeOver()
{
	//撞墙
	if(earthSnake->snakeHead->col >= 14 || earthSnake->snakeHead->col < 0 || earthSnake->snakeHead->row < 1 || earthSnake->snakeHead->row >= 24)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		this->restart();
		CCDirector::sharedDirector()->replaceScene(LoseGame::scene()); 
	}
	//撞自己
	for(unsigned int i=0;i<earthSnake->snakeBody.size();i++)  
	{  
		if((earthSnake->snakeHead->col == earthSnake->snakeBody[i]->col) && (earthSnake->snakeHead->row == earthSnake->snakeBody[i]->row))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			this->restart();
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
			this->restart();
			CCDirector::sharedDirector()->replaceScene(LoseGame::scene()); 
		}
	}
	//撞障碍物
	for(unsigned int i=0;i<barriers.size();i++)
	{  
		if((earthSnake->snakeHead->col == barriers[i]->col) && (earthSnake->snakeHead->row == barriers[i]->row))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			this->restart();
			CCDirector::sharedDirector()->replaceScene(LoseGame::scene()); 
		}
	}
}

//初始化蛇的身体，4个节点
void Game::initSnakeBody()
{
	SnakeNode *marsSnakeBody1 = new SnakeNode();
	marsSnakeBody1->row = 2;
	marsSnakeBody1->col = 3;
	marsSnake->snakeBody.push_back(marsSnakeBody1);
	SnakeNode *marsSnakeBody2 = new SnakeNode();
	marsSnakeBody2->row = 2;
	marsSnakeBody2->col = 2;
	marsSnake->snakeBody.push_back(marsSnakeBody2);
	SnakeNode *marsSnakeBody3 = new SnakeNode();
	marsSnakeBody3->row = 2;
	marsSnakeBody3->col = 1;
	marsSnake->snakeBody.push_back(marsSnakeBody3);
	SnakeNode *marsSnakeBody4 = new SnakeNode();
	marsSnakeBody4->row = 2;
	marsSnakeBody4->col = 0;
	marsSnake->snakeBody.push_back(marsSnakeBody4);

	SnakeNode *earthSnakeBody1 = new SnakeNode();
	earthSnakeBody1->row = 9;
	earthSnakeBody1->col = 3;
	earthSnake->snakeBody.push_back(earthSnakeBody1);
	SnakeNode *earthSnakeBody2 = new SnakeNode();
	earthSnakeBody2->row = 9;
	earthSnakeBody2->col = 2;
	earthSnake->snakeBody.push_back(earthSnakeBody2);
	SnakeNode *earthSnakeBody3 = new SnakeNode();
	earthSnakeBody3->row = 9;
	earthSnakeBody3->col = 1;
	earthSnake->snakeBody.push_back(earthSnakeBody3);
	SnakeNode *earthSnakeBody4 = new SnakeNode();
	earthSnakeBody4->row = 9;
	earthSnakeBody4->col = 0;
	earthSnake->snakeBody.push_back(earthSnakeBody4);
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
	bg->addChild(head,2);
	head->runAction(seq);

	
	//火星蛇头
	CCSprite *ahead=CCSprite::create("p6.png");
	ahead->setPosition(ccp(marsSnake->snakeHead->row*32+16,marsSnake->snakeHead->col*32+16));
	bg->addChild(ahead,2);
	ahead->runAction(disahead);


	//绘制食物  
	CCAction *disFood=CCSequence::create(delay,disappear,NULL);
	CCSprite *food=CCSprite::create("p8.png");
	food->setPosition(ccp(sFood->row*32+16,sFood->col*32+16));
	bg->addChild(food,2);
	food->runAction(disFood);

	//绘制身体  
	for(unsigned int i=0;i<earthSnake->snakeBody.size();i++)  
	{  
		CCAction *disBody=CCSequence::create(delay,disappear,NULL);
		CCSprite *body=CCSprite::create("p5.png");
		body->setPosition(ccp(earthSnake->snakeBody[i]->row*32+16,earthSnake->snakeBody[i]->col*32+16));
		bg->addChild(body,1);
		body->runAction(disBody);
	}  


	for(unsigned int i=0;i<marsSnake->snakeBody.size();i++)  
	{  
		CCAction *disaBody=CCSequence::create(delay,disappear,NULL);
		CCSprite *abody=CCSprite::create("p7.png");
		abody->setPosition(ccp(marsSnake->snakeBody[i]->row*32+16,marsSnake->snakeBody[i]->col*32+16));
		bg->addChild(abody,1);
		abody->runAction(disaBody);
	}

}

void Game::restart()
{
	direction = 1;
	earthSnake->snakeBody.clear();
	earthSnake->snakeHead->col = 5;
	earthSnake->snakeHead->row = 9;
	marsSnake->snakeBody.clear();
	marsSnake->snakeHead->col = 2;
	marsSnake->snakeHead->row = 5;
}

bool Game::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void Game::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	return;
}

//触摸屏幕来改变方向
void Game::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPos = pTouch->getLocation();

	CCPoint origPos;
	origPos.setPoint(earthSnake->snakeHead->row * 32 + 16, earthSnake->snakeHead->col * 32 + 16);
	CCPoint diff = ccpSub(touchPos,origPos);

	if(abs(diff.x) > abs(diff.y))
	{
		if(diff.x > 0)
		{//Right
			if((earthSnake->snakeHead->dir != RIGHT) && (earthSnake->snakeHead->dir != LEFT))
			{
				//this->unscheduleAllSelectors();
				direction = RIGHT;
				this->schedule(schedule_selector(Game::gameLogic),speed);
			}
		}
		else
		{//Left
			if((earthSnake->snakeHead->dir != LEFT) && (earthSnake->snakeHead->dir != RIGHT))
			{
				//this->unscheduleAllSelectors();
				direction = LEFT;
				this->schedule(schedule_selector(Game::gameLogic),speed);
			}
		}
	}
	else
	{
		if(diff.y > 0)
		{//Up
			if((earthSnake->snakeHead->dir != UP) && (earthSnake->snakeHead->dir != DOWN))
			{
				//方向切换会闪是因为这个原因
				//this->unscheduleAllSelectors();
				direction = UP;
				this->schedule(schedule_selector(Game::gameLogic),speed);
			}
		}
		else
		{//Down
			if((earthSnake->snakeHead->dir != DOWN) && (earthSnake->snakeHead->dir != UP))
			{
				//this->unscheduleAllSelectors();
				direction = DOWN;
				this->schedule(schedule_selector(Game::gameLogic),speed);
			}
		}
	}

	return;
}