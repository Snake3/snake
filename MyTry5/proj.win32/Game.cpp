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
	//背景网格
	CCSprite* bg = CCSprite::create("grid5.jpg");
	//位置以图片中心为准
	bg->setPosition(ccp(161,160));
	this->addChild(bg);

	//精灵蛇
	snake = CCSprite::create("p7.png");
	snake->setPosition(ccp(16,144));
	this->addChild(snake);
	//setTouchEnabled(true);后面已经设置了

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//创建文字按钮 
	auto labelResume = CCLabelTTF::create("Resume", "宋体", 18); 
	auto labelPause = CCLabelTTF::create("Pause", "宋体", 18); 
	auto labelBack = CCLabelTTF::create("Main Menu", "宋体", 18); 

	//方向键
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

	//集合初始化
	_projs = new CCArray;
	_snake2s = new CCArray;

	//Class::create 不需要手动释放
	//new:需要手动释放

    return true;
}

void Game::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) // 触摸事件响应函数
{
	//pTouches是触摸点
	CCTouch* touch = (CCTouch*)pTouches->anyObject();
	//得到UI坐标系下的位置,(0,0)在左上角
	CCPoint locInView = touch->getLocationInView();
	//转化为cocos2d的坐标系,(0,0)在左下角
	CCPoint loc = CCDirector::sharedDirector()->convertToGL(locInView); //从UI坐标变换到cococs2d中的坐标

	if(loc.x <= 20)// 触摸点在出发点左侧不处理
	{
		return;
	}

	CCSize screenSize = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite* proj = CCSprite::create("Projectile.png");
	proj->setPosition(ccp(20, screenSize.height/2.0));
	this->addChild(proj);//创建飞镖精灵
	//加到界面的同时也加到集合上来
	_projs->addObject(proj);
	proj->setTag(2);

	//计算距离,相似三角形推导得出
	double dx = loc.x - 20;
	double dy = loc.y - screenSize.height / 2.0;
	double d = sqrt(dx * dx + dy * dy);// 触摸点到出发点的距离

	//D是屏幕尺寸，这里是：D=根号（480*480+320*320）
	double D = sqrt(screenSize.width * screenSize.width + screenSize.height * screenSize.height);// 总的运行距离

	double ratio = D / d;
	double endx = ratio * dx + 20;// 最终点的x坐标
	double endy = ratio * dy + screenSize.height / 2.0;// 最终点的y坐标

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
	//运动后消失动作
	///////////////第一种方式/////////////
	CCCallFuncN* disappear = CCCallFuncN::create(this,callfuncN_selector(Game::myDefine));
	CCAction* actions = CCSequence::create(move, disappear, NULL);
	snake->runAction(actions);

	///////////////第二种方式/////////////
	///////这种方式点击两次菜单不报错////////
	CCFiniteTimeAction* hideAction = CCHide::create(); 
	CCAction* actions = CCSequence::create(move, hideAction, NULL);
	snake->runAction(actions);

	//位置变化后运动
	//要先注释后面case1的动作
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
	//who->setScale(2);//扩大一倍
	
	//从图层中删去
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
	//获取触点指针容器中第一个元素
    CCSetIterator it = pTouches->begin();
	//将其转化为触点信息
    CCTouch* touch = (CCTouch*)(*it);
	//取得触点位置
	CCPoint touchLocation = touch->getLocation();  
	//设置精灵位置为触点位置。
	 snake->setPosition(touchLocation);
}

void Game::createTarget()
{
	//第二条精灵蛇
	CCSprite* snake2 = CCSprite::create("p8.png");

	CCSize screenSize = CCDirector::sharedDirector()->getVisibleSize();
	int y = rand()%(int)(screenSize.height);

	snake2->setPosition(ccp(screenSize.width-20,y));
	this->addChild(snake2);
	//加到界面的同时也加到集合上来
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

//飞镖集合和怪物集合的碰撞检测
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
		//先删除其他定时器
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

//方向上的循环
void Game::runUp(float dt)
{
	this->runUpMain();
}

void Game::runUpMain()
{
	//真正意义上的贪吃蛇
	CCSprite* snake3 = CCSprite::create("p9.png");
	//snake3->setPosition(ccp(80,144));
	
	snake3->setPosition(ccp(x,y));
	y += 32;

	//判断撞墙结束
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

//方向下的循环
void Game::runDown(float dt)
{
	this->runDownMain();
}

void Game::runDownMain()
{
	//真正意义上的贪吃蛇
	CCSprite* snake3 = CCSprite::create("p9.png");
	//snake3->setPosition(ccp(80,144));

	snake3->setPosition(ccp(x,y));
	y -= 32;

	//判断撞墙结束
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

//方向左的循环
void Game::runLeft(float dt)
{
	this->runLeftMain();
}

void Game::runLeftMain()
{
	//真正意义上的贪吃蛇
	CCSprite* snake3 = CCSprite::create("p9.png");
	//snake3->setPosition(ccp(80,144));

	snake3->setPosition(ccp(x,y));
	x -= 32;

	//判断撞墙结束
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

//方向右的循环
void Game::runRight(float dt)
{
	this->runRightMain();
}

void Game::runRightMain()
{
	//真正意义上的贪吃蛇
	CCSprite* snake3 = CCSprite::create("p9.png");
	//snake3->setPosition(ccp(80,144));

	snake3->setPosition(ccp(x,y));
	x += 32;

	//判断撞墙结束
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