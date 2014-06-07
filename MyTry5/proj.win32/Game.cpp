#include "HelloWorldScene.h"
#include "Game.h"
#include "SimpleAudioEngine.h"
#include "LoseGame.h"
#include "WinBattle.h"
#include <Windows.h>
#include <time.h>

using namespace cocos2d;

int direction = 1;					//初始化方向
extern float speed;
extern vector<SnakeNode*> barriers;
extern int count1,count2;
extern int LoseGameScore;
bool winFlag = false;
int action = 0;
clock_t earthStart = 0;
clock_t marsStart = 0;
int earth = 2;
int mars = 2;

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

	pPlayItem = CCMenuItemImage::create("play2.png","play2Selected.png",this,menu_selector(Game::responseFunc));
	pPlayItem->setTag(12);
	pPlayItem->setPosition(ccp(120,436));
	pPlayItem->setVisible(false);

	pPauseItem = CCMenuItemImage::create("pause2.png","pause2Selected.png",this,menu_selector(Game::responseFunc));
	pPauseItem->setTag(13);
	pPauseItem->setPosition(ccp(120,436));
	pPauseItem->setVisible(true);

	pMusicOFFItem = CCMenuItemImage::create("musicOFF.png","musicOFFSelected.png",this,menu_selector(Game::responseFunc));
	pMusicOFFItem->setTag(14);
	pMusicOFFItem->setPosition(ccp(168,436));
	pMusicOFFItem->setVisible(false);

	pMusicONItem = CCMenuItemImage::create("musicON.png","musicONSelected.png",this,menu_selector(Game::responseFunc));
	pMusicONItem->setTag(15);
	pMusicONItem->setPosition(ccp(168,436));
	pMusicONItem->setVisible(true);

	auto menu = CCMenu::create(pExitItem, pPlayItem, pPauseItem, pMusicOFFItem, pMusicONItem, NULL); 
	menu->setPosition(CCPointZero); 
	bg->addChild(menu); 

	CCLabelTTF* labelText1 = CCLabelTTF ::create("Scores1:", "STKaiti", 24);
	//CCLabelTTF* labelText = CCLabelTTF::labelWithString("YourScores:","MarkerFelt-Thin",20);
	//labelText->setColor(color);
	labelText1->setPosition(ccp(400,456));
	addChild(labelText1);

	//加载图片数字
	label1 =CCLabelAtlas::create("0", "DigitalFont2.png", 15, 32, '0');
	label1->setPosition(ccp(460, 437));
	addChild(label1);

	CCLabelTTF* labelText2 = CCLabelTTF ::create("Your Scores:", "STKaiti", 24);
	//CCLabelTTF* labelText = CCLabelTTF::labelWithString("YourScores:","MarkerFelt-Thin",20);
	//labelText->setColor(color);
	labelText2->setPosition(ccp(600,456));
	addChild(labelText2);

	label2 =CCLabelAtlas::create("0", "DigitalFont1.png", 15, 31, '0');
	label2->setPosition(ccp(690, 437));
	addChild(label2);

	this->initSnakeBody();

	this->schedule(schedule_selector(Game::gameLogic1),speed);
	//this->unschedule(schedule_selector(Game::gameLogic1));
	this->schedule(schedule_selector(Game::gameLogic2),speed);
	
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
		pPauseItem->setVisible(true);
		pPlayItem->setVisible(false);
		CCDirector::sharedDirector()->resume();
		break; 
	case 13: 
		pPauseItem->setVisible(false);
		pPlayItem->setVisible(true);
		CCDirector::sharedDirector()->pause();  
		break;
	case 14: 
		pMusicOFFItem->setVisible(false);
		pMusicONItem->setVisible(true);
		//音效开关失灵
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		break;
	case 15: 
		pMusicOFFItem->setVisible(true);
		pMusicONItem->setVisible(false);
		//音效禁不了
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
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

	//两蛇合并
	vector<SnakeNode*> huoxingSnake, TwoSnake;
	TwoSnake = earthSnake->snakeBody;
	TwoSnake.push_back(earthSnake->snakeHead);
	huoxingSnake = marsSnake->snakeBody;
	huoxingSnake.push_back(marsSnake->snakeHead);
	TwoSnake.insert(TwoSnake.begin(),marsSnake->snakeBody.begin(),marsSnake->snakeBody.end());

	if(haveEat){
		sFood->generate();
		while(flag){
			for(unsigned int i=0;i<TwoSnake.size();i++){
					if(((TwoSnake[i]->row == sFood->row)&&(TwoSnake[i]->col == sFood->col))){
						sFood->row = rand()%23 + 1;
						sFood->col = rand()%14;
						i = 0;
					}
				}
				flag = false;
				/*
				for(unsigned int i=0;i<earthSnake->snakeBody.size();i++){
					if(((earthSnake->snakeBody[i]->row == sFood->row)&&(earthSnake->snakeBody[i]->col == sFood->col))||((earthSnake->snakeHead->row == sFood->row)&&(earthSnake->snakeHead->col == sFood->col))){
						sFood->row = rand()%23 + 1;
						sFood->col = rand()%14;
						i = 0;
					}
				}
				flag = false;
				*/
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

void Game::earthDoAction(int action){
	if(action == 12){
		earthStart = clock();
		earth = 1;
		this->unschedule(schedule_selector(Game::gameLogic2));
		this->schedule(schedule_selector(Game::gameLogic2),0.8f);
	}
	else if(action == 13){
		earthStart = clock();
		earth = 0;
		this->unschedule(schedule_selector(Game::gameLogic1));
		this->schedule(schedule_selector(Game::gameLogic1),0.2f);
	}
	/*else if(action == 11){
		start = clock();
		this->unschedule(schedule_selector(Game::gameLogic1));
		this->schedule(schedule_selector(Game::gameLogic1),5.0f);
		//绘制蛇头  
		CCSprite *head=CCSprite::create("p9.png");
		head->setPosition(ccp(earthSnake->snakeHead->row*32+16,earthSnake->snakeHead->col*32+16));
		bg->addChild(head,2);
		//head->runAction(seq);

		//绘制身体  
		for(unsigned int i=0;i<earthSnake->snakeBody.size();i++)  
		{  
			//CCAction *disBody=CCSequence::create(delay,disappear,NULL);
			CCSprite *body=CCSprite::create("p5.png");
			body->setPosition(ccp(earthSnake->snakeBody[i]->row*32+16,earthSnake->snakeBody[i]->col*32+16));
			bg->addChild(body,1);
			//body->runAction(disBody);
		} 
		//this->schedule(schedule_selector(Game::gameLogic1),8.0f);
	}*/
	else if(action == 11){
		earthStart = clock();
		earthSnake->snakeBody.pop_back();
		earthSnake->snakeBody.pop_back();
	}
}

void Game::marsDoAction(int action){
	if(action == 12){
		marsStart = clock();
		mars = 1;
		this->unschedule(schedule_selector(Game::gameLogic1));
		this->schedule(schedule_selector(Game::gameLogic1),0.8f);
	}
	else if(action == 13){
		marsStart = clock();
		mars = 0;
		this->unschedule(schedule_selector(Game::gameLogic2));
		this->schedule(schedule_selector(Game::gameLogic2),0.2f);
	}
	/*else if(action == 11){
		this->unschedule(schedule_selector(Game::gameLogic1));
		
		//绘制蛇头  
		CCSprite *head=CCSprite::create("p9.png");
		head->setPosition(ccp(earthSnake->snakeHead->row*32+16,earthSnake->snakeHead->col*32+16));
		bg->addChild(head,2);
		//head->runAction(seq);

		//绘制身体  
		for(unsigned int i=0;i<earthSnake->snakeBody.size();i++)  
		{  
			//CCAction *disBody=CCSequence::create(delay,disappear,NULL);
			CCSprite *body=CCSprite::create("p5.png");
			body->setPosition(ccp(earthSnake->snakeBody[i]->row*32+16,earthSnake->snakeBody[i]->col*32+16));
			bg->addChild(body,1);
			//body->runAction(disBody);
		} 
		//this->schedule(schedule_selector(Game::gameLogic1),8.0f);
	}*/
	else if(action == 11){
		marsStart = clock();
		marsSnake->snakeBody.pop_back();
		marsSnake->snakeBody.pop_back();
	}
}

//计算出蛇下个位置每个节点的坐标及判断赢的条件
void Game::gameLogic1(float dt)  
{     
	if(((clock() - earthStart) > 3000) && (earth == 1)){
		//this->schedule(schedule_selector(Game::gameLogic1),speed);
		this->schedule(schedule_selector(Game::gameLogic2),speed);
		earthStart = 0;
		earth = 2;
	}
	else if(((clock() - earthStart) > 3000) && (earth == 0)){
		//this->schedule(schedule_selector(Game::gameLogic1),speed);
		this->schedule(schedule_selector(Game::gameLogic1),speed);
		earthStart = 0;
		earth = 2;
	}
	
	bool haveEat = false;
	earthSnake->snakeHead->dir = direction;

	earthSnake->BodyMove();
	//marsSnake->BodyMove();

	earthSnake->HeadMove();
	//winFlag = marsSnake->MarsSnakeHeadMove(sFood,earthSnake);

	

	haveEat = earthSnake->eat(sFood,&action);
	if(haveEat)
		earthDoAction(action);
	
	

	createFood(earthSnake,marsSnake,haveEat);
	if(haveEat)
	{
		this->setEarthSnakeScores(earthSnake->getEarthSnakeScores());
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("cheer.wav");
	}
	/*
	haveEat = marsSnake->eat(sFood);
	createFood(earthSnake,marsSnake,haveEat);
	if(haveEat)
	{
		this->setMarsSnakeScores(marsSnake->getMarsSnakeScores());
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("cheer.wav");
	}
	*/
	this->drawEarth(earthSnake);
	this->drawFood(sFood);

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

void Game::gameLogic2(float dt)  
{     
	if(((clock() - marsStart) > 3000) && (mars == 1)){
		this->schedule(schedule_selector(Game::gameLogic1),speed);
		//this->schedule(schedule_selector(Game::gameLogic2),speed);
		marsStart = 0;
		mars = 2;
	}
	else if(((clock() - marsStart) > 3000) && (mars == 0)){
		this->schedule(schedule_selector(Game::gameLogic2),speed);
		//this->schedule(schedule_selector(Game::gameLogic2),speed);
		marsStart = 0;
		mars = 2;
	}
	
	bool haveEat = false;
	//earthSnake->snakeHead->dir = direction;

	//earthSnake->BodyMove();
	marsSnake->BodyMove();

	//earthSnake->HeadMove();
	winFlag = marsSnake->MarsSnakeHeadMove(sFood,earthSnake);

	

	//haveEat = earthSnake->eat(sFood);
	//createFood(earthSnake,marsSnake,haveEat);
	/*if(haveEat)
	{
		//is->setEarthSnakeScores(earthSnake->getEarthSnakeScores());
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("cheer.wav");
	}*/
	
	haveEat = marsSnake->eat(sFood,&action);
	if(haveEat)
		marsDoAction(action);

	createFood(earthSnake,marsSnake,haveEat);
	if(haveEat)
	{
		this->setMarsSnakeScores(marsSnake->getMarsSnakeScores());
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("cheer.wav");
	}

	this->drawMars(marsSnake);
	this->drawFood(sFood);

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
		LoseGameScore = earthSnake->getEarthSnakeScores().getEarthSnakeEatScores();
		CCDirector::sharedDirector()->replaceScene(LoseGame::scene()); 
	}
	//撞自己
	for(unsigned int i=0;i<earthSnake->snakeBody.size();i++)  
	{  
		if((earthSnake->snakeHead->col == earthSnake->snakeBody[i]->col) && (earthSnake->snakeHead->row == earthSnake->snakeBody[i]->row))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			this->restart();
			LoseGameScore = earthSnake->getEarthSnakeScores().getEarthSnakeEatScores();
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
			LoseGameScore = earthSnake->getEarthSnakeScores().getEarthSnakeEatScores();
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
			LoseGameScore = earthSnake->getEarthSnakeScores().getEarthSnakeEatScores();
			CCDirector::sharedDirector()->replaceScene(LoseGame::scene()); 
		}
	}
}

//初始化蛇的身体，4个节点
void Game::initSnakeBody()
{
	SnakeNode *marsSnakeBody1 = new SnakeNode();
	marsSnakeBody1->row = marsSnake->snakeHead->row;
	marsSnakeBody1->col = marsSnake->snakeHead->col - 1;
	marsSnake->snakeBody.push_back(marsSnakeBody1);
	SnakeNode *marsSnakeBody2 = new SnakeNode();
	marsSnakeBody2->row = marsSnake->snakeHead->row;
	marsSnakeBody2->col = marsSnake->snakeHead->col - 2;
	marsSnake->snakeBody.push_back(marsSnakeBody2);
	SnakeNode *marsSnakeBody3 = new SnakeNode();
	marsSnakeBody3->row = marsSnake->snakeHead->row;
	marsSnakeBody3->col = marsSnake->snakeHead->col - 3;
	marsSnake->snakeBody.push_back(marsSnakeBody3);
	SnakeNode *marsSnakeBody4 = new SnakeNode();
	marsSnakeBody4->row = marsSnake->snakeHead->row;
	marsSnakeBody4->col = marsSnake->snakeHead->col - 4;
	marsSnake->snakeBody.push_back(marsSnakeBody4);

	SnakeNode *earthSnakeBody1 = new SnakeNode();
	earthSnakeBody1->row = earthSnake->snakeHead->row;
	earthSnakeBody1->col = earthSnake->snakeHead->col - 1;
	earthSnake->snakeBody.push_back(earthSnakeBody1);
	SnakeNode *earthSnakeBody2 = new SnakeNode();
	earthSnakeBody2->row = earthSnake->snakeHead->row;
	earthSnakeBody2->col = earthSnake->snakeHead->col - 2;
	earthSnake->snakeBody.push_back(earthSnakeBody2);
	SnakeNode *earthSnakeBody3 = new SnakeNode();
	earthSnakeBody3->row = earthSnake->snakeHead->row;
	earthSnakeBody3->col = earthSnake->snakeHead->col - 3;
	earthSnake->snakeBody.push_back(earthSnakeBody3);
	SnakeNode *earthSnakeBody4 = new SnakeNode();
	earthSnakeBody4->row = earthSnake->snakeHead->row;
	earthSnakeBody4->col = earthSnake->snakeHead->col - 4;
	earthSnake->snakeBody.push_back(earthSnakeBody4);
}

//绘制蛇和绘制食物
void Game::drawFood(SnakeNode* sFood)
{
	CCFiniteTimeAction * delay = CCDelayTime::create(speed);
	CCCallFuncN* disappear = CCCallFuncN::create(this,callfuncN_selector(Game::myDefine));
	CCAction *seq = CCSequence::create(delay,disappear,NULL);
	CCAction *disahead = CCSequence::create(delay,disappear,NULL);

	//绘制食物  
	CCAction *disFood=CCSequence::create(delay,disappear,NULL);
	//string name = (sFood->foodType).ToString("f");
	//string name = "r";
	//sFood->foodType;
	int i = (int)(sFood->foodType);
	char name[10];
	ostringstream oss;
	oss << i;
	string num = oss.str() + ".png";
	strcpy(name,num.c_str());
	CCSprite *food=CCSprite::create(name);
	food->setPosition(ccp(sFood->row*32+16,sFood->col*32+16));
	bg->addChild(food,2);
	food->runAction(disFood);
}

void Game::drawMars(MarsSnake *marsSnake){
	CCFiniteTimeAction * delay = CCDelayTime::create(speed);
	CCCallFuncN* disappear = CCCallFuncN::create(this,callfuncN_selector(Game::myDefine));
	CCAction *seq = CCSequence::create(delay,disappear,NULL);
	CCAction *disahead = CCSequence::create(delay,disappear,NULL);

	//火星蛇头
	CCSprite *ahead=CCSprite::create("p6.png");
	ahead->setPosition(ccp(marsSnake->snakeHead->row*32+16,marsSnake->snakeHead->col*32+16));
	bg->addChild(ahead,2);
	ahead->runAction(disahead);

	for(unsigned int i=0;i<marsSnake->snakeBody.size();i++)  
	{  
		CCAction *disaBody=CCSequence::create(delay,disappear,NULL);
		CCSprite *abody=CCSprite::create("p7.png");
		abody->setPosition(ccp(marsSnake->snakeBody[i]->row*32+16,marsSnake->snakeBody[i]->col*32+16));
		bg->addChild(abody,1);
		abody->runAction(disaBody);
	}
}

void Game::drawEarth(EarthSnake *earthSnake){
	CCFiniteTimeAction * delay = CCDelayTime::create(speed);
	CCCallFuncN* disappear = CCCallFuncN::create(this,callfuncN_selector(Game::myDefine));
	CCAction *seq = CCSequence::create(delay,disappear,NULL);
	CCAction *disahead = CCSequence::create(delay,disappear,NULL);

	//绘制蛇头  
	CCSprite *head=CCSprite::create("p9.png");
	head->setPosition(ccp(earthSnake->snakeHead->row*32+16,earthSnake->snakeHead->col*32+16));
	bg->addChild(head,2);
	head->runAction(seq);

	//绘制身体  
	for(unsigned int i=0;i<earthSnake->snakeBody.size();i++)  
	{  
		CCAction *disBody=CCSequence::create(delay,disappear,NULL);
		CCSprite *body=CCSprite::create("p5.png");
		body->setPosition(ccp(earthSnake->snakeBody[i]->row*32+16,earthSnake->snakeBody[i]->col*32+16));
		bg->addChild(body,1);
		body->runAction(disBody);
	} 
}

void Game::restart()
{
	direction = 1;
	earthSnake->snakeBody.clear();
	earthSnake->snakeHead->col = 4;
	earthSnake->snakeHead->row = 9;
	marsSnake->snakeBody.clear();
	marsSnake->snakeHead->col = 2;
	marsSnake->snakeHead->row = 4;

	count1 = 0;
	count2 = 0;
	marsSnake->getMarsSnakeScores().setMarsSnakeEatScores(0);
	earthSnake->getEarthSnakeScores().setEarthSnakeEatScores(0);

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
				//this->schedule(schedule_selector(Game::gameLogic1),speed);
				//this->schedule(schedule_selector(Game::gameLogic2),speed);
			}
		}
		else
		{//Left
			if((earthSnake->snakeHead->dir != LEFT) && (earthSnake->snakeHead->dir != RIGHT))
			{
				//this->unscheduleAllSelectors();
				direction = LEFT;
				//this->schedule(schedule_selector(Game::gameLogic1),speed);
				//this->schedule(schedule_selector(Game::gameLogic2),speed);
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
				//this->schedule(schedule_selector(Game::gameLogic1),speed);
				//this->schedule(schedule_selector(Game::gameLogic2),speed);
			}
		}
		else
		{//Down
			if((earthSnake->snakeHead->dir != DOWN) && (earthSnake->snakeHead->dir != UP))
			{
				//this->unscheduleAllSelectors();
				direction = DOWN;
				//this->schedule(schedule_selector(Game::gameLogic1),speed);
				//this->schedule(schedule_selector(Game::gameLogic2),speed);
			}
		}
		//this->schedule(schedule_selector(Game::gameLogic2),0.3);
	}

	return;
}

void Game::setMarsSnakeScores(Score scores)
{
	MarsSnakeScores = scores;
	char b[20];
	label1->setString(itoa(MarsSnakeScores.getMarsSnakeEatScores(),b,10));
}

void Game::setEarthSnakeScores(Score scores)
{
	EarthSnakeScores = scores;
	char a[20];
	label2->setString(itoa(EarthSnakeScores.getEarthSnakeEatScores(),a,10));
}