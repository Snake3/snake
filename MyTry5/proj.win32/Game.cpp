#include "HelloWorldScene.h"
#include "Game.h"
#include "SimpleAudioEngine.h"
#include "LoseGame.h"
#include "WinBattle.h"
#include <Windows.h>
#include <time.h>

using namespace cocos2d;

int direction = 1;					//��ʼ������
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

SnakeNode *sFood = new SnakeNode();	//ʳ��ڵ��ʼ��
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

	//����ͼƬ����
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

	//������Ļ��Ӧ�¼�
	this->setTouchEnabled(true);//ʹlayer������Ӧ�����¼�������
	CCDirector::sharedDirector()->getTouchDispatcher()
		->addTargetedDelegate(this, 0, true);

	//��߷ֽ�ҵ�д�뱾���ļ�
	if(this->isHaveSaveFile())
	{
		CCLog("����Ŀ�Ѵ��ڱ������ݵ�xml�ļ�");
	}
	else
	{
		CCLog("����Ŀ�����ڱ������ݵ�xml�ļ������㿴���˴�ӡ��Ĭ�ϴ�����xml�ļ�");
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
	this->addChild(tileMap); // ��ͼ�ӵ�layer����

	flagLayer = tileMap->layerNamed("Tile Layer 2");
	flagLayer->setVisible(false);
}

void Game::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector() ->pause();
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

//������Ϸ��Ĳ˵���Ӧ
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
		//��Ч����ʧ��
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		break;
	case 15: 
		pMusicOFFItem->setVisible(true);
		pMusicONItem->setVisible(false);
		//��Ч������
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		break;
	default: 
		break; 
	} 
}   

////���ϰ�����
bool Game::isInObstacle(CCPoint point)
{
	//CCTMXLayer* ObstacleLayer = tileMap->layerNamed("Tile Layer 2");
	int oneTileId = flagLayer->tileGIDAt(point);//����tilemap����õ����������id

	//����ʲô���嶼û��
	if (oneTileId == 0)
	{
		return false;
	}

	CCDictionary* propertileOnOneTile = tileMap->propertiesForGID(oneTileId);
	const CCString* Obstacle = propertileOnOneTile->valueForKey("Obstacle");

	//�ж������λ������ײ����true���������ƶ�
	if(Obstacle && Obstacle->compare("true") == 0)//��ײ
	{
		return true;
	}
	
	return false;
}

//�������ʧ�ĺ���
void Game::myDefine(CCNode* who)
{	
	//��ͼ����ɾȥ
	who->removeFromParentAndCleanup(true);
}

void Game::createFood(EarthSnake* earthSnake,MarsSnake* marsSnake,bool haveEat){
	bool flag = true;
	//srand((unsigned)time(0));

	//���ߺϲ�
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

//�����߳Ե�����ʳ���3����Ϊ
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
		//������ͷ  
		CCSprite *head=CCSprite::create("p9.png");
		head->setPosition(ccp(earthSnake->snakeHead->row*32+16,earthSnake->snakeHead->col*32+16));
		bg->addChild(head,2);
		//head->runAction(seq);

		//��������  
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

//�����߳Ե�����ʳ���3����Ϊ
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
		
		//������ͷ  
		CCSprite *head=CCSprite::create("p9.png");
		head->setPosition(ccp(earthSnake->snakeHead->row*32+16,earthSnake->snakeHead->col*32+16));
		bg->addChild(head,2);
		//head->runAction(seq);

		//��������  
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

//������������¸�λ��ÿ���ڵ������
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

//������������¸�λ��ÿ���ڵ�������Լ�Ӯ������
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

	//Ӯ������
	if(winFlag)
	{
		this->win();
		return;
	}
}

//��Ϸ��������Ӧ��Ӯ�˻�������
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
		//��������򵥴洢������
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Hiscores", GameScore);
		CCUserDefault::sharedUserDefault()->flush();//����һ��Ҫ�ύд��Ŷ�����򲻻��¼��xml�У��´�������Ϸ��ͻ�ȡ����value�ˡ�
	}
	this->restart();
}

//��ϷӮ�˵���Ӧ
void Game::win()
{
	this->unscheduleAllSelectors();
	this->gameEndResponse();
	CCDirector::sharedDirector()->replaceScene(WinBattle::scene());
	winFlag = false;

}

//��Ϸ���˵���Ӧ
void Game::lose()
{
	this->gameEndResponse();
	CCDirector::sharedDirector()->replaceScene(LoseGame::scene());
}

//�ж��Ƿ���
void Game::judgeOver()
{
	//ײǽ
	if(earthSnake->snakeHead->col >= 15 || earthSnake->snakeHead->col < 0 || earthSnake->snakeHead->row < 0 || earthSnake->snakeHead->row >= 25)
	{
		 this->lose();
	}
	//ײ�Լ�
	for(unsigned int i=0;i<earthSnake->snakeBody.size();i++)  
	{  
		if((earthSnake->snakeHead->col == earthSnake->snakeBody[i]->col) && (earthSnake->snakeHead->row == earthSnake->snakeBody[i]->row))
		{
			this->lose();
		}
	}
	//ײ������
	vector<SnakeNode*> huoBody = marsSnake->snakeBody;
	huoBody.push_back(marsSnake->snakeHead);
	for(unsigned int i=0;i<huoBody.size();i++)
	{  
		if((earthSnake->snakeHead->col == huoBody[i]->col) && (earthSnake->snakeHead->row == huoBody[i]->row))
		{
			this->lose(); 
		}
	}
	//ײ�ϰ���
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

//��ʼ���ߵ����壬4���ڵ�
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

//�����ߺͻ���ʳ��
void Game::drawFood(SnakeNode* sFood)
{
	CCFiniteTimeAction * delay = CCDelayTime::create(speed);
	CCCallFuncN* disappear = CCCallFuncN::create(this,callfuncN_selector(Game::myDefine));
	CCAction *seq = CCSequence::create(delay,disappear,NULL);
	CCAction *disahead = CCSequence::create(delay,disappear,NULL);

	//����ʳ��  
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

	//������ͷ
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

	//������ͷ  
	CCSprite *head=CCSprite::create("p9.png");
	head->setPosition(ccp(earthSnake->snakeHead->row*32+16,earthSnake->snakeHead->col*32+16));
	tileMap->addChild(head,2);
	head->runAction(seq);

	//��������  
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

//������Ļ���ı䷽��
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
				//�����л���������Ϊ���ԭ��
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

	/*��Ȼ���������ַ�����
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

//��ǰ��Ŀ�Ƿ���ڴ洢��xml�ļ�
bool Game::isHaveSaveFile()
{
	if(!CCUserDefault::sharedUserDefault()->getBoolForKey("isHaveSaveFileXml")) 
	{ 
		CCUserDefault::sharedUserDefault()->setBoolForKey("isHaveSaveFileXml", true);
		CCUserDefault::sharedUserDefault()->flush();//�ύ
		//        CCLog("�洢�ļ�������,ͷ�ο�ʼ������Ϸ");
		return false;
	}else{
		//        CCLog("�洢�ļ��Ѵ���");
		return true;
	}
}