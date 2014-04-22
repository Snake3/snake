#include "HelloWorldScene.h"
#include "Game.h"

using namespace cocos2d;

int direction = 1;					//初始化方向
extern float speed;

vector<SnakeNode*> allBody;			//声明贪吃蛇的身体，不包括蛇头
vector<SnakeNode*> asnakeBody;		//声明火星蛇的身体，不包括蛇头

SnakeNode *sFood = new SnakeNode();	//食物节点初始化
SnakeNode *sHead = new SnakeNode();	//贪吃蛇蛇头节点初始化
SnakeNode *aHead= new SnakeNode();	//火星蛇蛇头节点初始化

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
	CCMenuItemImage *pUpItem = CCMenuItemImage::create("Up.png","Up.png",this,menu_selector(Game::setDirection) );
	CCMenuItemImage *pDownItem = CCMenuItemImage::create("Down.png","Down.png",this,menu_selector(Game::setDirection) );
	CCMenuItemImage *pLeftItem = CCMenuItemImage::create("Left.png","Left.png",this,menu_selector(Game::setDirection) );
	CCMenuItemImage *pRightItem = CCMenuItemImage::create("Right.png","Right.png",this,menu_selector(Game::setDirection) );

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
	//who->setPosition(ccp(0,0));
	//who->setScale(2);//扩大一倍
	
	//从图层中删去
	who->removeFromParentAndCleanup(true);

	/*
	int tag = who->getTag();

	if(1==tag)
	{
		_snake2s->removeObject(who);
	}
	else if(2==tag)
	{
		_projs->removeObject(who);
	}
	*/
}

//设置贪食蛇的方向
void Game::setDirection(CCObject* obj)
{

	//this->schedule(schedule_selector(Game::run),1);
	int i = dynamic_cast<CCMenuItemImage*>(obj)->getTag();
	switch (i) 
	{ 
	case UP:
		if((sHead->dir != UP) && (sHead->dir != DOWN))
		{
			//方向切换会闪是因为这个原因
			this->unscheduleAllSelectors();
			direction = UP;
			this->schedule(schedule_selector(Game::gameLogic),speed);
		}
		break; 
	case DOWN:
		if((sHead->dir != DOWN) && (sHead->dir != UP))
		{
			this->unscheduleAllSelectors();
			direction = DOWN;
			this->schedule(schedule_selector(Game::gameLogic),speed);
		}
		break; 
	case LEFT:
		if((sHead->dir != LEFT) && (sHead->dir != RIGHT))
		{
			this->unscheduleAllSelectors();
			direction = LEFT;
			this->schedule(schedule_selector(Game::gameLogic),speed);
		}
		break;
	case RIGHT:
		if((sHead->dir != RIGHT) && (sHead->dir != LEFT))
		{
			this->unscheduleAllSelectors();
			direction = RIGHT;
			this->schedule(schedule_selector(Game::gameLogic),speed);
		}
		break;
	default: 
		break;
	}
}

//计算出蛇下个位置每个节点的坐标  
void Game::gameLogic(float dt)  
{     
	sHead->dir = direction;

	this->tanchiSnakeMoveBody();
	this->huoxingSnakeMoveBody();
	this->tanchiSnakeHeadMoveDirection();
	this->huoxingSnakeHeadMoveDirection();

	//吃食物
	this->tanchiSnakeEat();
	this->huoxingSnakeEat();

	this->draw(allBody,sHead,sFood);   
}

//绘制蛇和绘制食物
void Game::draw(std::vector<SnakeNode*> allBody,SnakeNode* sHead,SnakeNode* sFood)
{
	CCFiniteTimeAction * delay = CCDelayTime::create(speed);
	CCCallFuncN* disappear = CCCallFuncN::create(this,callfuncN_selector(Game::myDefine));
	CCAction *seq = CCSequence::create(delay,disappear,NULL);
	CCAction *disahead = CCSequence::create(delay,disappear,NULL);

	//绘制蛇头  
	CCSprite *head=CCSprite::create("p9.png");
	head->setPosition(ccp(sHead->row*32+16,sHead->col*32+16));
	this->addChild(head);
	head->runAction(seq);

	
	//火星蛇头
	CCSprite *ahead=CCSprite::create("p7.png");
	ahead->setPosition(ccp(aHead->row*32+16,aHead->col*32+16));
	this->addChild(ahead);
	ahead->runAction(disahead);


	//绘制食物  
	CCAction *disFood=CCSequence::create(delay,disappear,NULL);
	CCSprite *food=CCSprite::create("p8.png");
	food->setPosition(ccp(sFood->row*32+16,sFood->col*32+16));
	this->addChild(food);
	food->runAction(disFood);

	//绘制身体  
	for(unsigned int i=0;i<allBody.size();i++)  
	{  
		CCAction *disBody=CCSequence::create(delay,disappear,NULL);
		CCSprite *body=CCSprite::create("p9.png");
		body->setPosition(ccp(allBody[i]->row*32+16,allBody[i]->col*32+16));
		this->addChild(body);
		body->runAction(disBody);
	}  


	for(unsigned int i=0;i<asnakeBody.size();i++)  
	{  
		CCAction *disaBody=CCSequence::create(delay,disappear,NULL);
		CCSprite *abody=CCSprite::create("p7.png");
		abody->setPosition(ccp(asnakeBody[i]->row*32+16,asnakeBody[i]->col*32+16));
		this->addChild(abody);
		abody->runAction(disaBody);
	}

}

//贪吃蛇移动蛇的身体,不包括蛇头
void Game::tanchiSnakeMoveBody() 
{
	//移动蛇的身体,不包括蛇头  
	for(int i = allBody.size()-1; i>=0; i--)  
	{   
		//sn为指向allBody元素的指针，通过sn可更改allBody元素的值，即跟新到下个位置
		//获取蛇身体上的某个节点
		SnakeNode * sn = (SnakeNode *)allBody.at(i);  

		//把蛇身体前面的节点赋值给后面的节点，实现蛇节点向前移动一个位置
		if(i>0)   
		{   
			//如果该节点不是第一个节点,那么该节点的下一个坐标就是其前一个点的坐标（这里不用多解释，玩过蛇的都懂）  
			SnakeNode * snpre = (SnakeNode *)allBody.at(i-1);  

			//更改行列和方向

			sn->dir = snpre->dir;  
			sn->row = snpre->row;  
			sn->col = snpre->col;  
		}  


		//把蛇头的位置赋值给紧接在蛇头后面节点
		else if(i==0)  
		{  
			//如果i=0则是第一个节点，蛇头的坐标便是该节点的坐标  
			sn->dir = sHead->dir;  
			sn->row = sHead->row;  
			sn->col = sHead->col;  
		}  
	}  
}
//贪吃蛇的蛇头移动方向
void Game::tanchiSnakeHeadMoveDirection() 
{
	//根据sHead的值，判断蛇头移动的方向，从而计算出蛇头下个位置的坐标以及移动方向
	switch(sHead->dir)  
	{  
	case UP:  
		sHead->col++;//上移  
		if(sHead->col >= 10)  
		{  
			//sHead->col=0;//超过顶部边界后便从底部出来  
			CCDirector::sharedDirector()->end();
		}  
		break;  
	case DOWN:  
		sHead->col--;  
		if(sHead->col < 0)  
		{  
			//sHead->col=9;  
			CCDirector::sharedDirector()->end();
		}  
		break;  
	case LEFT:  
		sHead->row--;  
		if(sHead->row < 0)  
		{  
			//sHead->row=9;  
			CCDirector::sharedDirector()->end();
		}  
		break;  
	case RIGHT:  
		sHead->row++;  
		if(sHead->row >= 10)  
		{  
			//sHead->row=0;  
			CCDirector::sharedDirector()->end();
		}  
		break;  
	}   
}
//贪吃蛇吃食物
void Game::tanchiSnakeEat() 
{
	//碰撞检测(只是判断蛇头位置和食物位置是否一样而已）
	//如果蛇头的横、列位置一样，说明蛇吃到了这个食物  
	if(sHead->row == sFood->row && sHead->col == sFood->col) 
	{   
		//食物从当前位置消失，随机出现在下一个坐标  
		sFood->row = rand()%10;  
		sFood->col = rand()%10;  


		//添加身体到集合  
		SnakeNode * sn = new SnakeNode();//创建一个新的节点（也就是吃掉的那个食物），将其放到蛇的尾巴上  
		SnakeNode * lastNode = NULL;  
		//获取蛇的最后一个节点，如果allBody的size()为0，则说明蛇是第一次捕食，那么它的最后一个节点也就是蛇头啦。  
		if(allBody.size()>0)  
			lastNode = (SnakeNode *)allBody.back();  
		else  
			lastNode = sHead;//最后一个节点是蛇头  


		//通过最后一个节点的方向来个新的节点初始化横、列坐标  
		switch(lastNode->dir)  
		{  

		case UP:  
			sn->row = lastNode->row;  
			sn->col = lastNode->col-1;  
			break;  

		case DOWN:  
			sn->row = lastNode->row;  
			sn->col = lastNode->col+1;  
			break;  

		case LEFT:  
			sn->row = lastNode->row+1;  
			sn->col = lastNode->col;  
			break;  

		case RIGHT:  
			sn->row=lastNode->row-1;  
			sn->col=lastNode->col;  
			break;  

		}  
		allBody.push_back(sn);//将新的节点加入到蛇的身体中。  
	}  
}

//火星蛇移动蛇的身体,不包括蛇头 
void Game::huoxingSnakeMoveBody() 
{
	for(int i = asnakeBody.size()-1; i>=0; i--)  
	{   
		//sn为指向allBody元素的指针，通过sn可更改allBody元素的值，即跟新到下个位置
		//获取蛇身体上的某个节点
		SnakeNode * sn = (SnakeNode *)asnakeBody.at(i);  

		//把蛇身体前面的节点赋值给后面的节点，实现蛇节点向前移动一个位置
		if(i>0)   
		{   
			//如果该节点不是第一个节点,那么该节点的下一个坐标就是其前一个点的坐标（这里不用多解释，玩过蛇的都懂）  
			SnakeNode * snpre = (SnakeNode *)asnakeBody.at(i-1);  

			//更改行列和方向
			sn->dir = snpre->dir;  
			sn->row = snpre->row;  
			sn->col = snpre->col;  
		}  


		//把蛇头的位置赋值给紧接在蛇头后面节点
		else if(i==0)  
		{  
			//如果i=0则是第一个节点，蛇头的坐标便是该节点的坐标  
			sn->dir = aHead->dir;  
			sn->row = aHead->row;  
			sn->col = aHead->col;  
		}  
	}
}
//火星蛇的蛇头移动方向
void Game::huoxingSnakeHeadMoveDirection() 
{
	//火星蛇头的移动方向,曼哈顿距离,左右移动优先，bug：穿过蛇身体
	if ((aHead->row)!=(sFood->row))
	{ 
		if(sFood->row < aHead->row)
		{	//食物在蛇头左边
			aHead->row--;
			aHead->dir=LEFT;
		}
		else if(sFood->row > aHead->row)
		{	//食物在蛇头右边
			aHead->row++;
			aHead->dir=RIGHT;
		}
	}  
	else if ((aHead->col!=sFood->col))
	{
		if(sFood->col < aHead->col)
		{	//食物在蛇头下方
			aHead->col--;
			aHead->dir=DOWN;
		}
		if(sFood->col > aHead->col)
		{	//食物在蛇头上方
			aHead->col++;
			aHead->dir=UP;
		} 
	}  
}
//火星蛇吃食物
void Game::huoxingSnakeEat() 
{
	//火星蛇的碰撞检测
	if(aHead->row==sFood->row&&aHead->col==sFood->col)
	{
		//食物从当前位置消失，随机出现在下一个坐标  
		sFood->row = rand()%10;  
		sFood->col = rand()%10;  


		//添加身体到集合  
		SnakeNode * sn = new SnakeNode();//创建一个新的节点（也就是吃掉的那个食物），将其放到蛇的尾巴上  
		SnakeNode * lastNode = NULL;  
		//获取蛇的最后一个节点，如果allBody的size()为0，则说明蛇是第一次捕食，那么它的最后一个节点也就是蛇头啦。  
		if(asnakeBody.size()>0)  
			lastNode = (SnakeNode *)asnakeBody.back();  
		else  
			lastNode = aHead;//最后一个节点是蛇头  


		//通过最后一个节点的方向来个新的节点初始化横、列坐标  
		switch(lastNode->dir)  
		{  
		case UP:  
			sn->row = lastNode->row;  
			sn->col = lastNode->col-1;  
			break;  

		case DOWN:  
			sn->row = lastNode->row;  
			sn->col = lastNode->col+1;  
			break;  

		case LEFT:  
			sn->row = lastNode->row+1;  
			sn->col = lastNode->col;  
			break;  

		case RIGHT:  
			sn->row=lastNode->row-1;  
			sn->col=lastNode->col;  
			break;		
		} 
		asnakeBody.push_back(sn);//将新的节点加入到蛇的身体中
	}
}