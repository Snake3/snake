#include "HelloWorldScene.h"
#include "Game.h"

using namespace cocos2d;

float y = 16;
float x = 80;

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
	//��������
	CCSprite* bg = CCSprite::create("grid5.jpg");
	//λ����ͼƬ����Ϊ׼
	bg->setPosition(ccp(161,160));
	this->addChild(bg);

	//������
	snake = CCSprite::create("p7.png");
	snake->setPosition(ccp(16,144));
	this->addChild(snake);
	//setTouchEnabled(true);�����Ѿ�������

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//�������ְ�ť 
	auto labelResume = CCLabelTTF::create("Resume", "����", 18); 
	auto labelPause = CCLabelTTF::create("Pause", "����", 18); 
	auto labelBack = CCLabelTTF::create("Main Menu", "����", 18); 

	//�����
	CCMenuItemImage *pUpItem = CCMenuItemImage::create("Up.png","Up.png",this,menu_selector(Game::setDirection) );
	CCMenuItemImage *pDownItem = CCMenuItemImage::create("Down.png","Down.png",this,menu_selector(Game::setDirection) );
	CCMenuItemImage *pLeftItem = CCMenuItemImage::create("Left.png","Left.png",this,menu_selector(Game::setDirection) );
	CCMenuItemImage *pRightItem = CCMenuItemImage::create("Right.png","Right.png",this,menu_selector(Game::setDirection) );

	auto uiTry = CCMenuItemLabel::create(labelResume, this, menu_selector(Game::responseFunc)); 
    uiTry->setTag(1); 
	uiTry->setPosition(ccp(size.width-90,250)); 
      
    auto uiPause = CCMenuItemLabel::create(labelPause, this, menu_selector(Game::responseFunc)); 
    uiPause->setTag(2); 
    uiPause->setPosition(ccp(size.width-90,230)); 
      
    auto uiBack = CCMenuItemLabel::create(labelBack, this, menu_selector(Game::menuCloseCallback)); 
    uiBack->setTag(3); 
    uiBack->setPosition(ccp(size.width-90,210)); 	
      
	pUpItem->setTag(4);
	pUpItem->setPosition(ccp(size.width-80,150)); 
	
	pDownItem->setTag(5);
	pDownItem->setPosition(ccp(size.width-80,70)); 

	pLeftItem->setTag(6);
	pLeftItem->setPosition(ccp(size.width-120,110)); 

	pRightItem->setTag(7);
	pRightItem->setPosition(ccp(size.width-40,110)); 

    auto menu = CCMenu::create(uiTry,uiPause,uiBack,pUpItem,pDownItem,pLeftItem,pRightItem, NULL); 
    menu->setPosition(CCPointZero); 
    this->addChild(menu); 
	
	this->schedule(schedule_selector(Game::gameLogic),2);
	this->schedule(schedule_selector(Game::update));

	this->setTouchEnabled(true);

	//���ϳ�ʼ��
	_projs = new CCArray;
	_snake2s = new CCArray;

	//Class::create ����Ҫ�ֶ��ͷ�
	//new:��Ҫ�ֶ��ͷ�

    return true;
}

void Game::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) // �����¼���Ӧ����
{
	//pTouches�Ǵ�����
	CCTouch* touch = (CCTouch*)pTouches->anyObject();
	//�õ�UI����ϵ�µ�λ��,(0,0)�����Ͻ�
	CCPoint locInView = touch->getLocationInView();
	//ת��Ϊcocos2d������ϵ,(0,0)�����½�
	CCPoint loc = CCDirector::sharedDirector()->convertToGL(locInView); //��UI����任��cococs2d�е�����

	if(loc.x <= 20)// �������ڳ�������಻����
	{
		return;
	}

	CCSize screenSize = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite* proj = CCSprite::create("Projectile.png");
	proj->setPosition(ccp(20, screenSize.height/2.0));
	this->addChild(proj);//�������ھ���
	//�ӵ������ͬʱҲ�ӵ���������
	_projs->addObject(proj);
	proj->setTag(2);

	//�������,�����������Ƶ��ó�
	double dx = loc.x - 20;
	double dy = loc.y - screenSize.height / 2.0;
	double d = sqrt(dx * dx + dy * dy);// �����㵽������ľ���

	//D����Ļ�ߴ磬�����ǣ�D=���ţ�480*480+320*320��
	double D = sqrt(screenSize.width * screenSize.width + screenSize.height * screenSize.height);// �ܵ����о���

	double ratio = D / d;
	double endx = ratio * dx + 20;// ���յ��x����
	double endy = ratio * dy + screenSize.height / 2.0;// ���յ��y����

	CCMoveTo* move = CCMoveTo::create(D/320, ccp(endx,endy));
	CCCallFuncN* moveFinish = CCCallFuncN::create(this, callfuncN_selector(Game::myDefine));
	CCAction* actions = CCSequence::create(move, moveFinish,NULL);
	proj->runAction(actions);
}

void Game::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector() ->resume();
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

void Game::responseFunc(CCObject* obj)
{	
	CCMoveTo* move = CCMoveTo::create(1.0f,ccp(280,280));

	//float x = 48;
	//CCDelayTime* delay = CCDelayTime::create(3.5f);
	//CCSequence* actions = CCSequence::create(move,delay,NULL);
	
	//float y = 145;
	//float x = 20;

	#if 0
	//�˶�����ʧ����
	///////////////��һ�ַ�ʽ/////////////
	CCCallFuncN* disappear = CCCallFuncN::create(this,callfuncN_selector(Game::myDefine));
	CCAction* actions = CCSequence::create(move, disappear, NULL);
	snake->runAction(actions);

	///////////////�ڶ��ַ�ʽ/////////////
	///////���ַ�ʽ������β˵�������////////
	CCFiniteTimeAction* hideAction = CCHide::create(); 
	CCAction* actions = CCSequence::create(move, hideAction, NULL);
	snake->runAction(actions);

	//λ�ñ仯���˶�
	//Ҫ��ע�ͺ���case1�Ķ���
	CCJumpTo* jump = CCJumpTo::create(2.0f,ccp(280,280),180,3);
	CCFiniteTimeAction* placeAction = CCPlace::create(ccp(50, 10));   
	CCAction* action = CCSequence::create(placeAction, jump, NULL);
	snake->runAction(action);
	#endif	

	int i = dynamic_cast<CCMenuItemLabel*>(obj)->getTag();
	switch (i) 
	{ 
	case 1: 
		CCDirector::sharedDirector() ->resume();
		snake->runAction(move);
		
		#if 0
		if(snake->getPositionX() <= 304)
		{
			//snake->removeFromParentAndCleanup(true);
			snake->setPosition(ccp(x,145));
			//CCSequence* actions = CCSequence::create(move,delay,NULL);
			x += 32;
			this->addChild(snake);
			//y += 32;
			//snake->runAction(delay);
		}
		#endif
		
		break; 
	case 2: 
		pauseGame(obj);
		break; 
	case 3: 
		CCDirector::sharedDirector()->end();
		break;
	default: 
		break; 
	} 
}

void Game::pauseGame(CCObject* sender)    
{    
	CCDirector::sharedDirector() ->pause();     
	//resumeGameItem->setIsVisible(true);    
	//pauseGameItem ->setIsVisible(false);    
}    

void Game::myDefine(CCNode* who)
{
	//who->setPosition(ccp(0,0));
	//who->setScale(2);//����һ��
	
	//��ͼ����ɾȥ
	who->removeFromParentAndCleanup(true);

	int tag = who->getTag();

	if(1==tag)
	{
		_snake2s->removeObject(who);
	}
	else if(2==tag)
	{
		_projs->removeObject(who);
	}
}

void Game::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	//��ȡ����ָ�������е�һ��Ԫ��
    CCSetIterator it = pTouches->begin();
	//����ת��Ϊ������Ϣ
    CCTouch* touch = (CCTouch*)(*it);
	//ȡ�ô���λ��
	CCPoint touchLocation = touch->getLocation();  
	//���þ���λ��Ϊ����λ�á�
	 snake->setPosition(touchLocation);
}

void Game::createTarget()
{
	//�ڶ���������
	CCSprite* snake2 = CCSprite::create("p8.png");

	CCSize screenSize = CCDirector::sharedDirector()->getVisibleSize();
	int y = rand()%(int)(screenSize.height);

	snake2->setPosition(ccp(screenSize.width-20,y));
	this->addChild(snake2);
	//�ӵ������ͬʱҲ�ӵ���������
	_snake2s->addObject(snake2);
	snake2->setTag(1);

	CCMoveTo* move = CCMoveTo::create(2,ccp(0,y));
	CCCallFuncN* disappear = CCCallFuncN::create(this,callfuncN_selector(Game::myDefine));
	CCAction* actions = CCSequence::create(move, disappear, NULL);
	snake2->runAction(actions);

}

void Game::gameLogic(float dt)
{
	this->createTarget();
}

Game::~Game()
{
	if(_projs != NULL)
	{
		_projs->release();
	}

	if(_snake2s != NULL)
	{
		_snake2s->release();
	}
}

//���ڼ��Ϻ͹��Ｏ�ϵ���ײ���
void Game::update(float delta) // delta = 1.0 / fps
{
	CCArray* targetToDelete = new CCArray;
	CCArray* projToDelete = new CCArray;
	CCObject* itarget;
	CCObject* iproj;
	CCARRAY_FOREACH(_snake2s, itarget){
		CCSprite* target = (CCSprite*)itarget;

		CCRect targetZone = CCRectMake(target->getPositionX(),
			target->getPositionY(),
			target->getContentSize().width,
			target->getContentSize().height);

		CCARRAY_FOREACH(_projs, iproj){
			CCSprite* proj = (CCSprite*)iproj;
			CCRect projZone = CCRectMake(proj->getPositionX(),
				proj->getPositionY(),
				proj->getContentSize().width,
				proj->getContentSize().height);

			if (projZone.intersectsRect(targetZone)){
				projToDelete->addObject(iproj);
				targetToDelete->addObject(itarget);
			}
		} // end of iterate projectile


	} // end of iterate target

	CCARRAY_FOREACH(projToDelete, iproj){
		_projs->removeObject(iproj);
		CCSprite* proj = (CCSprite*)iproj;
		proj->removeFromParentAndCleanup(true);
	}

	CCARRAY_FOREACH(targetToDelete, itarget){
		_snake2s->removeObject(itarget);
		CCSprite* target = (CCSprite*)itarget;
		target->removeFromParentAndCleanup(true);
	}

	targetToDelete->release();
	projToDelete->release();
}

void Game::setDirection(CCObject* obj)
{
	//this->schedule(schedule_selector(Game::run),1);
	int i = dynamic_cast<CCMenuItemImage*>(obj)->getTag();
	switch (i) 
	{ 
	case 4: //Up
		//��ɾ��������ʱ��
		this->unschedule(schedule_selector(Game::runDown));
		this->unschedule(schedule_selector(Game::runLeft));
		this->unschedule(schedule_selector(Game::runRight));
		this->schedule(schedule_selector(Game::runUp),1);
		break; 
	case 5: //Down
		this->unschedule(schedule_selector(Game::runUp));
		this->unschedule(schedule_selector(Game::runLeft));
		this->unschedule(schedule_selector(Game::runRight));
		this->schedule(schedule_selector(Game::runDown),1);
		break; 
	case 6: //Left
		this->unschedule(schedule_selector(Game::runDown));
		this->unschedule(schedule_selector(Game::runUp));
		this->unschedule(schedule_selector(Game::runRight));
		this->schedule(schedule_selector(Game::runLeft),1);
		break;
	case 7: //Right
		this->unschedule(schedule_selector(Game::runDown));
		this->unschedule(schedule_selector(Game::runLeft));
		this->unschedule(schedule_selector(Game::runUp));
		this->schedule(schedule_selector(Game::runRight),1);
		break;
	default: 
		break; 
	} 
}

//�����ϵ�ѭ��
void Game::runUp(float dt)
{
	this->runUpMain();
}

void Game::runUpMain()
{
	//���������ϵ�̰����
	CCSprite* snake3 = CCSprite::create("p9.png");
	//snake3->setPosition(ccp(80,144));
	
	snake3->setPosition(ccp(x,y));
	y += 32;

	//�ж�ײǽ����
	if(snake3->getPositionY() > 304)
	{
		CCDirector::sharedDirector()->end();
	}

	this->addChild(snake3);
	CCDelayTime* delay = CCDelayTime::create(1);
	CCCallFuncN* disappear = CCCallFuncN::create(this,callfuncN_selector(Game::myDefine));
	CCAction* actions = CCSequence::create(delay, disappear, NULL);
	snake3->runAction(actions);
}

//�����µ�ѭ��
void Game::runDown(float dt)
{
	this->runDownMain();
}

void Game::runDownMain()
{
	//���������ϵ�̰����
	CCSprite* snake3 = CCSprite::create("p9.png");
	//snake3->setPosition(ccp(80,144));

	snake3->setPosition(ccp(x,y));
	y -= 32;

	//�ж�ײǽ����
	if(snake3->getPositionY() < 16)
	{
		CCDirector::sharedDirector()->end();
	}

	this->addChild(snake3);
	CCDelayTime* delay = CCDelayTime::create(1);
	CCCallFuncN* disappear = CCCallFuncN::create(this,callfuncN_selector(Game::myDefine));
	CCAction* actions = CCSequence::create(delay, disappear, NULL);
	snake3->runAction(actions);
}

//�������ѭ��
void Game::runLeft(float dt)
{
	this->runLeftMain();
}

void Game::runLeftMain()
{
	//���������ϵ�̰����
	CCSprite* snake3 = CCSprite::create("p9.png");
	//snake3->setPosition(ccp(80,144));

	snake3->setPosition(ccp(x,y));
	x -= 32;

	//�ж�ײǽ����
	if(snake3->getPositionX() < 16)
	{
		CCDirector::sharedDirector()->end();
	}

	this->addChild(snake3);
	CCDelayTime* delay = CCDelayTime::create(1);
	CCCallFuncN* disappear = CCCallFuncN::create(this,callfuncN_selector(Game::myDefine));
	CCAction* actions = CCSequence::create(delay, disappear, NULL);
	snake3->runAction(actions);
}

//�����ҵ�ѭ��
void Game::runRight(float dt)
{
	this->runRightMain();
}

void Game::runRightMain()
{
	//���������ϵ�̰����
	CCSprite* snake3 = CCSprite::create("p9.png");
	//snake3->setPosition(ccp(80,144));

	snake3->setPosition(ccp(x,y));
	x += 32;

	//�ж�ײǽ����
	if(snake3->getPositionX() > 304)
	{
		CCDirector::sharedDirector()->end();
	}

	this->addChild(snake3);
	CCDelayTime* delay = CCDelayTime::create(1);
	CCCallFuncN* disappear = CCCallFuncN::create(this,callfuncN_selector(Game::myDefine));
	CCAction* actions = CCSequence::create(delay, disappear, NULL);
	snake3->runAction(actions);
}