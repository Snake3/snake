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
//extern vector<SnakeNode*> barriers;
extern int count1,count2;
extern int GameScore;
extern int level;
bool winFlag = false;
int action = 0;
clock_t earthStart = 0;
clock_t marsStart = 0;
int earth = 2;
int mars = 2;
CCTMXLayer* flagLayer;
CCTMXTiledMap* tileMap;

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
	this->ChooseMap();
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
	tileMap->addChild(menu); 

	CCLabelTTF* labelText1 = CCLabelTTF ::create("Scores1:", "STKaiti", 24);
	labelText1->setPosition(ccp(400,456));
	addChild(labelText1);

	//加载图片数字
	label1 =CCLabelAtlas::create("0", "DigitalFont2.png", 15, 32, '0');
	label1->setPosition(ccp(460, 437));
	addChild(label1);

	CCLabelTTF* labelText2 = CCLabelTTF ::create("Your Scores:", "STKaiti", 24);
	labelText2->setPosition(ccp(600,456));
	addChild(labelText2);

	label2 =CCLabelAtlas::create("0", "DigitalFont1.png", 15, 31, '0');
	label2->setPosition(ccp(690, 437));
	addChild(label2);

	this->initSnakeBody();
	this->schedule(schedule_selector(Game::gameLogic1),speed);
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

	//最高分金币等写入本地文件
	if(this->isHaveSaveFile())
	{
		CCLog("此项目已存在保存数据的xml文件");
	}
	else
	{
		CCLog("此项目不存在保存数据的xml文件，当你看到此打印已默认创建了xml文件");
	}

    return true;
}

void Game::ChooseMap()
{
	char a[20];
	string b =  "Level";
	b += itoa(level,a,10);
	b += ".tmx";
	CCString map = b;
	tileMap = CCTMXTiledMap::create(map.getCString());
	CCTMXLayer* backLayer = tileMap->layerNamed("Tile Layer 1");
	CCAssert(backLayer, "Can not find layer named by (Tile Layer 1)");
	this->addChild(tileMap); // 地图加到layer上面

	flagLayer = tileMap->layerNamed("Tile Layer 2");
	flagLayer->setVisible(false);
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

////在障碍物里
bool Game::isInObstacle(CCPoint point)
{
	//CCTMXLayer* ObstacleLayer = tileMap->layerNamed("Tile Layer 2");
	int oneTileId = flagLayer->tileGIDAt(point);//根据tilemap坐标得到层上物体的id

	//层上什么物体都没有
	if (oneTileId == 0)
	{
		return false;
	}

	CCDictionary* propertileOnOneTile = tileMap->propertiesForGID(oneTileId);
	const CCString* Obstacle = propertileOnOneTile->valueForKey("Obstacle");

	//判断如果新位置是碰撞属性true，不可以移动
	if(Obstacle && Obstacle->compare("true") == 0)//碰撞
	{
		return true;
	}
	
	return false;
}

//清除、消失的函数
void Game::myDefine(CCNode* who)
{	
	//从图层中删去
	who->removeFromParentAndCleanup(true);
}

void Game::createFood(EarthSnake* earthSnake,MarsSnake* marsSnake,bool haveEat){
	bool flag = true;
	//srand((unsigned)time(0));

	//两蛇合并
	vector<SnakeNode*> huoxingSnake, TwoSnake;
	TwoSnake = earthSnake->snakeBody;
	TwoSnake.push_back(earthSnake->snakeHead);
	huoxingSnake = marsSnake->snakeBody;
	huoxingSnake.push_back(marsSnake->snakeHead);
	TwoSnake.insert(TwoSnake.begin(),marsSnake->snakeBody.begin(),marsSnake->snakeBody.end());

	if(haveEat){
	//sFood->row = rand()%23 + 1;  
	//sFood->col = rand()%14;
	sFood->generate();
	while(flag){
			for(unsigned int i=0;i<TwoSnake.size();i++){
					if(((TwoSnake[i]->row == sFood->row)&&(TwoSnake[i]->col == sFood->col))){
						sFood->row = rand()%25;
						sFood->col = rand()%15;
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
				//for(unsigned int i=0;i<barriers.size();i++){
					while(isInObstacle(ccp(sFood->row, 14 - sFood->col))){
						sFood->row = rand()%25;
						sFood->col = rand()%15;
						//i = 0;
						flag = true;
					}
				//}
			}
	}
}

//地球蛇吃到特殊食物的3种行为
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

//火星蛇吃到特殊食物的3种行为
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

//计算出地球蛇下个位置每个节点的坐标
void Game::gameLogic1(float dt)  
{     
	if(((clock() - earthStart) > 3000) && (earth == 1)){
		this->schedule(schedule_selector(Game::gameLogic2),speed);
		earthStart = 0;
		earth = 2;
	}
	else if(((clock() - earthStart) > 3000) && (earth == 0)){
		this->schedule(schedule_selector(Game::gameLogic1),speed);
		earthStart = 0;
		earth = 2;
	}

	bool haveEat = false;
	earthSnake->snakeHead->dir = direction;
	earthSnake->BodyMove();
	earthSnake->HeadMove();

	haveEat = earthSnake->eat(sFood,&action);
	if(haveEat)
	{
		earthDoAction(action);
	}
	createFood(earthSnake,marsSnake,haveEat);
	if(haveEat)
	{
		this->setEarthSnakeScores(earthSnake->getEarthSnakeScores());
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("cheer.wav");
	}

	this->drawEarth(earthSnake);
	this->drawFood(sFood);
}

//计算出火星蛇下个位置每个节点的坐标以及赢的条件
void Game::gameLogic2(float dt)  
{     
	if(((clock() - marsStart) > 3000) && (mars == 1)){
		this->schedule(schedule_selector(Game::gameLogic1),speed);
		marsStart = 0;
		mars = 2;
	}
	else if(((clock() - marsStart) > 3000) && (mars == 0)){
		this->schedule(schedule_selector(Game::gameLogic2),speed);
		marsStart = 0;
		mars = 2;
	}
	
	bool haveEat = false;
	marsSnake->BodyMove();
	bool UpFlag, DownFlag, LeftFlag, RightFlag;

	if(marsSnake->snakeHead->col + 1 > 14)
		UpFlag = true;
	else
		UpFlag = isInObstacle(ccp(marsSnake->snakeHead->row, 14 - marsSnake->snakeHead->col - 1));
	if(marsSnake->snakeHead->col - 1 < 0)
		DownFlag = true;
	else
		DownFlag = isInObstacle(ccp(marsSnake->snakeHead->row, 14 - marsSnake->snakeHead->col + 1));
	if(marsSnake->snakeHead->row - 1 < 0)
		LeftFlag = true;
	else
		LeftFlag = isInObstacle(ccp(marsSnake->snakeHead->row - 1, 14 - marsSnake->snakeHead->col));
	if(marsSnake->snakeHead->row + 1 > 24)
		RightFlag = true;
	else
		RightFlag = isInObstacle(ccp(marsSnake->snakeHead->row + 1, 14 - marsSnake->snakeHead->col));

	winFlag = marsSnake->MarsSnakeHeadMove(sFood,earthSnake,UpFlag,DownFlag,LeftFlag,RightFlag);
	
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
		this->win();
		return;
	}
}

//游戏结束的响应，赢了或者输了
void Game::gameEndResponse()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	
	if(count2 != 0)
	{
		GameScore = earthSnake->getEarthSnakeScores().getEarthSnakeEatScores();
	}
	else
	{
		GameScore = 0;
	}

	int Hiscores = CCUserDefault::sharedUserDefault()->getIntegerForKey("Hiscores");
	int coins = CCUserDefault::sharedUserDefault()->getIntegerForKey("Coins");
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Coins", GameScore + coins);

	if(GameScore > Hiscores)
	{
		//我们这里简单存储条数据
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Hiscores", GameScore);
		CCUserDefault::sharedUserDefault()->flush();//这里一定要提交写入哦，否则不会记录到xml中，下次启动游戏你就获取不到value了。
	}
	this->restart();
}

//游戏赢了的响应
void Game::win()
{
	this->unscheduleAllSelectors();
	this->gameEndResponse();
	CCDirector::sharedDirector()->replaceScene(WinBattle::scene());
	winFlag = false;

}

//游戏输了的响应
void Game::lose()
{
	this->gameEndResponse();
	CCDirector::sharedDirector()->replaceScene(LoseGame::scene());
}

//判断是否输
void Game::judgeOver()
{
	//撞墙
	if(earthSnake->snakeHead->col >= 15 || earthSnake->snakeHead->col < 0 || earthSnake->snakeHead->row < 0 || earthSnake->snakeHead->row >= 25)
	{
		 this->lose();
	}
	//撞自己
	for(unsigned int i=0;i<earthSnake->snakeBody.size();i++)  
	{  
		if((earthSnake->snakeHead->col == earthSnake->snakeBody[i]->col) && (earthSnake->snakeHead->row == earthSnake->snakeBody[i]->row))
		{
			this->lose();
		}
	}
	//撞火星蛇
	vector<SnakeNode*> huoBody = marsSnake->snakeBody;
	huoBody.push_back(marsSnake->snakeHead);
	for(unsigned int i=0;i<huoBody.size();i++)
	{  
		if((earthSnake->snakeHead->col == huoBody[i]->col) && (earthSnake->snakeHead->row == huoBody[i]->row))
		{
			this->lose(); 
		}
	}
	//撞障碍物
	/*CCPoint HeadPos = new CCPoint();
	HeadPos.setPoint(earthSnake->snakeHead->row, earthSnake->snakeHead->col);
	for(unsigned int i=0;i<barriers.size();i++)
	{  */
	if(isInObstacle(ccp(earthSnake->snakeHead->row, 14 - earthSnake->snakeHead->col)))
	{
		this->lose(); 
	}
	//}
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
	int i = (int)(sFood->foodType);
	char name[10];
	ostringstream oss;
	oss << i;
	string num = oss.str() + ".png";
	strcpy(name,num.c_str());
	CCSprite *food=CCSprite::create(name);
	//CCSprite *food=CCSprite::create("p8.png");
	food->setPosition(ccp(sFood->row*32+16,sFood->col*32+16));
	tileMap->addChild(food,2);
	food->runAction(disFood);

	for(unsigned int i=0;i<marsSnake->snakeBody.size();i++)  
	{  
		CCAction *disaBody=CCSequence::create(delay,disappear,NULL);
		CCSprite *abody=CCSprite::create("p7.png");
		abody->setPosition(ccp(marsSnake->snakeBody[i]->row*32+16,marsSnake->snakeBody[i]->col*32+16));
		tileMap->addChild(abody,1);
		abody->runAction(disaBody);
	}

}

void Game::drawMars(MarsSnake *marsSnake)
{
	CCFiniteTimeAction * delay = CCDelayTime::create(speed);
	CCCallFuncN* disappear = CCCallFuncN::create(this,callfuncN_selector(Game::myDefine));
	CCAction *seq = CCSequence::create(delay,disappear,NULL);
	CCAction *disahead = CCSequence::create(delay,disappear,NULL);

	//火星蛇头
	CCSprite *ahead=CCSprite::create("p6.png");
	ahead->setPosition(ccp(marsSnake->snakeHead->row*32+16,marsSnake->snakeHead->col*32+16));
	tileMap->addChild(ahead,2);
	ahead->runAction(disahead);

	for(unsigned int i=0;i<marsSnake->snakeBody.size();i++)  
	{  
		CCAction *disaBody=CCSequence::create(delay,disappear,NULL);
		CCSprite *abody=CCSprite::create("p7.png");
		abody->setPosition(ccp(marsSnake->snakeBody[i]->row*32+16,marsSnake->snakeBody[i]->col*32+16));
		tileMap->addChild(abody,1);
		abody->runAction(disaBody);
	}
}

void Game::drawEarth(EarthSnake *earthSnake)
{
	CCFiniteTimeAction * delay = CCDelayTime::create(speed);
	CCCallFuncN* disappear = CCCallFuncN::create(this,callfuncN_selector(Game::myDefine));
	CCAction *seq = CCSequence::create(delay,disappear,NULL);
	CCAction *disahead = CCSequence::create(delay,disappear,NULL);

	//绘制蛇头  
	CCSprite *head=CCSprite::create("p9.png");
	head->setPosition(ccp(earthSnake->snakeHead->row*32+16,earthSnake->snakeHead->col*32+16));
	tileMap->addChild(head,2);
	head->runAction(seq);

	//绘制身体  
	for(unsigned int i=0;i<earthSnake->snakeBody.size();i++)  
	{  
		CCAction *disBody=CCSequence::create(delay,disappear,NULL);
		CCSprite *body=CCSprite::create("p5.png");
		body->setPosition(ccp(earthSnake->snakeBody[i]->row*32+16,earthSnake->snakeBody[i]->col*32+16));
		tileMap->addChild(body,1);
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
	marsSnake->getMarsSnakeScores().setMarsSnakeEatScores(count1);
	earthSnake->getEarthSnakeScores().setEarthSnakeEatScores(count2);
	//GameScore = 0;
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
				//this->schedule(schedule_selector(Game::gameLogic),speed);
			}
		}
		else
		{//Left
			if((earthSnake->snakeHead->dir != LEFT) && (earthSnake->snakeHead->dir != RIGHT))
			{
				//this->unscheduleAllSelectors();
				direction = LEFT;
				//this->schedule(schedule_selector(Game::gameLogic),speed);
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
				//this->schedule(schedule_selector(Game::gameLogic),speed);
			}
		}
		else
		{//Down
			if((earthSnake->snakeHead->dir != DOWN) && (earthSnake->snakeHead->dir != UP))
			{
				//this->unscheduleAllSelectors();
				direction = DOWN;
				//this->schedule(schedule_selector(Game::gameLogic),speed);
			}
		}
	}

	return;
}

void Game::setMarsSnakeScores(Score scores)
{
	MarsSnakeScores = scores;
	char b[20];
	label1->setString(itoa(MarsSnakeScores.getMarsSnakeEatScores(),b,10));

	/*当然不会用这种方法啦
	string content;
	int a = MarsSnakeScores.getMarsSnakeEatScores();

	if (a) 
	{ 
		for (; a; a /= 10)  
			content.push_back('0' + a % 10);  
		reverse(content.begin(), content.end());  
	} 
	else 
	{ 
		content.push_back('0'); 
	}

	label1->setString(content.c_str());
	*/
}

void Game::setEarthSnakeScores(Score scores)
{
	EarthSnakeScores = scores;
	char a[20];
	label2->setString(itoa(EarthSnakeScores.getEarthSnakeEatScores(),a,10));
}

//当前项目是否存在存储的xml文件
bool Game::isHaveSaveFile()
{
	if(!CCUserDefault::sharedUserDefault()->getBoolForKey("isHaveSaveFileXml")) 
	{ 
		CCUserDefault::sharedUserDefault()->setBoolForKey("isHaveSaveFileXml", true);
		CCUserDefault::sharedUserDefault()->flush();//提交
		//        CCLog("存储文件不存在,头次开始加载游戏");
		return false;
	}else{
		//        CCLog("存储文件已存在");
		return true;
	}
}