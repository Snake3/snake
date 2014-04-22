#include "HelloWorldScene.h"
#include "Game.h"

using namespace cocos2d;

int direction = 1;					//��ʼ������
extern float speed;

vector<SnakeNode*> allBody;			//����̰���ߵ����壬��������ͷ
vector<SnakeNode*> asnakeBody;		//���������ߵ����壬��������ͷ

SnakeNode *sFood = new SnakeNode();	//ʳ��ڵ��ʼ��
SnakeNode *sHead = new SnakeNode();	//̰������ͷ�ڵ��ʼ��
SnakeNode *aHead= new SnakeNode();	//��������ͷ�ڵ��ʼ��

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

//������Ϸ��Ĳ˵���Ӧ
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

//��Ϸ��ͣ
void Game::pauseGame(CCObject* sender)    
{    
	CCDirector::sharedDirector() ->pause();     
}    

//�������ʧ�ĺ���
void Game::myDefine(CCNode* who)
{
	//who->setPosition(ccp(0,0));
	//who->setScale(2);//����һ��
	
	//��ͼ����ɾȥ
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

//����̰ʳ�ߵķ���
void Game::setDirection(CCObject* obj)
{

	//this->schedule(schedule_selector(Game::run),1);
	int i = dynamic_cast<CCMenuItemImage*>(obj)->getTag();
	switch (i) 
	{ 
	case UP:
		if((sHead->dir != UP) && (sHead->dir != DOWN))
		{
			//�����л���������Ϊ���ԭ��
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

//��������¸�λ��ÿ���ڵ������  
void Game::gameLogic(float dt)  
{     
	sHead->dir = direction;

	this->tanchiSnakeMoveBody();
	this->huoxingSnakeMoveBody();
	this->tanchiSnakeHeadMoveDirection();
	this->huoxingSnakeHeadMoveDirection();

	//��ʳ��
	this->tanchiSnakeEat();
	this->huoxingSnakeEat();

	this->draw(allBody,sHead,sFood);   
}

//�����ߺͻ���ʳ��
void Game::draw(std::vector<SnakeNode*> allBody,SnakeNode* sHead,SnakeNode* sFood)
{
	CCFiniteTimeAction * delay = CCDelayTime::create(speed);
	CCCallFuncN* disappear = CCCallFuncN::create(this,callfuncN_selector(Game::myDefine));
	CCAction *seq = CCSequence::create(delay,disappear,NULL);
	CCAction *disahead = CCSequence::create(delay,disappear,NULL);

	//������ͷ  
	CCSprite *head=CCSprite::create("p9.png");
	head->setPosition(ccp(sHead->row*32+16,sHead->col*32+16));
	this->addChild(head);
	head->runAction(seq);

	
	//������ͷ
	CCSprite *ahead=CCSprite::create("p7.png");
	ahead->setPosition(ccp(aHead->row*32+16,aHead->col*32+16));
	this->addChild(ahead);
	ahead->runAction(disahead);


	//����ʳ��  
	CCAction *disFood=CCSequence::create(delay,disappear,NULL);
	CCSprite *food=CCSprite::create("p8.png");
	food->setPosition(ccp(sFood->row*32+16,sFood->col*32+16));
	this->addChild(food);
	food->runAction(disFood);

	//��������  
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

//̰�����ƶ��ߵ�����,��������ͷ
void Game::tanchiSnakeMoveBody() 
{
	//�ƶ��ߵ�����,��������ͷ  
	for(int i = allBody.size()-1; i>=0; i--)  
	{   
		//snΪָ��allBodyԪ�ص�ָ�룬ͨ��sn�ɸ���allBodyԪ�ص�ֵ�������µ��¸�λ��
		//��ȡ�������ϵ�ĳ���ڵ�
		SnakeNode * sn = (SnakeNode *)allBody.at(i);  

		//��������ǰ��Ľڵ㸳ֵ������Ľڵ㣬ʵ���߽ڵ���ǰ�ƶ�һ��λ��
		if(i>0)   
		{   
			//����ýڵ㲻�ǵ�һ���ڵ�,��ô�ýڵ����һ�����������ǰһ��������꣨���ﲻ�ö���ͣ�����ߵĶ�����  
			SnakeNode * snpre = (SnakeNode *)allBody.at(i-1);  

			//�������кͷ���

			sn->dir = snpre->dir;  
			sn->row = snpre->row;  
			sn->col = snpre->col;  
		}  


		//����ͷ��λ�ø�ֵ����������ͷ����ڵ�
		else if(i==0)  
		{  
			//���i=0���ǵ�һ���ڵ㣬��ͷ��������Ǹýڵ������  
			sn->dir = sHead->dir;  
			sn->row = sHead->row;  
			sn->col = sHead->col;  
		}  
	}  
}
//̰���ߵ���ͷ�ƶ�����
void Game::tanchiSnakeHeadMoveDirection() 
{
	//����sHead��ֵ���ж���ͷ�ƶ��ķ��򣬴Ӷ��������ͷ�¸�λ�õ������Լ��ƶ�����
	switch(sHead->dir)  
	{  
	case UP:  
		sHead->col++;//����  
		if(sHead->col >= 10)  
		{  
			//sHead->col=0;//���������߽���ӵײ�����  
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
//̰���߳�ʳ��
void Game::tanchiSnakeEat() 
{
	//��ײ���(ֻ���ж���ͷλ�ú�ʳ��λ���Ƿ�һ�����ѣ�
	//�����ͷ�ĺᡢ��λ��һ����˵���߳Ե������ʳ��  
	if(sHead->row == sFood->row && sHead->col == sFood->col) 
	{   
		//ʳ��ӵ�ǰλ����ʧ�������������һ������  
		sFood->row = rand()%10;  
		sFood->col = rand()%10;  


		//������嵽����  
		SnakeNode * sn = new SnakeNode();//����һ���µĽڵ㣨Ҳ���ǳԵ����Ǹ�ʳ�������ŵ��ߵ�β����  
		SnakeNode * lastNode = NULL;  
		//��ȡ�ߵ����һ���ڵ㣬���allBody��size()Ϊ0����˵�����ǵ�һ�β�ʳ����ô�������һ���ڵ�Ҳ������ͷ����  
		if(allBody.size()>0)  
			lastNode = (SnakeNode *)allBody.back();  
		else  
			lastNode = sHead;//���һ���ڵ�����ͷ  


		//ͨ�����һ���ڵ�ķ��������µĽڵ��ʼ���ᡢ������  
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
		allBody.push_back(sn);//���µĽڵ���뵽�ߵ������С�  
	}  
}

//�������ƶ��ߵ�����,��������ͷ 
void Game::huoxingSnakeMoveBody() 
{
	for(int i = asnakeBody.size()-1; i>=0; i--)  
	{   
		//snΪָ��allBodyԪ�ص�ָ�룬ͨ��sn�ɸ���allBodyԪ�ص�ֵ�������µ��¸�λ��
		//��ȡ�������ϵ�ĳ���ڵ�
		SnakeNode * sn = (SnakeNode *)asnakeBody.at(i);  

		//��������ǰ��Ľڵ㸳ֵ������Ľڵ㣬ʵ���߽ڵ���ǰ�ƶ�һ��λ��
		if(i>0)   
		{   
			//����ýڵ㲻�ǵ�һ���ڵ�,��ô�ýڵ����һ�����������ǰһ��������꣨���ﲻ�ö���ͣ�����ߵĶ�����  
			SnakeNode * snpre = (SnakeNode *)asnakeBody.at(i-1);  

			//�������кͷ���
			sn->dir = snpre->dir;  
			sn->row = snpre->row;  
			sn->col = snpre->col;  
		}  


		//����ͷ��λ�ø�ֵ����������ͷ����ڵ�
		else if(i==0)  
		{  
			//���i=0���ǵ�һ���ڵ㣬��ͷ��������Ǹýڵ������  
			sn->dir = aHead->dir;  
			sn->row = aHead->row;  
			sn->col = aHead->col;  
		}  
	}
}
//�����ߵ���ͷ�ƶ�����
void Game::huoxingSnakeHeadMoveDirection() 
{
	//������ͷ���ƶ�����,�����پ���,�����ƶ����ȣ�bug������������
	if ((aHead->row)!=(sFood->row))
	{ 
		if(sFood->row < aHead->row)
		{	//ʳ������ͷ���
			aHead->row--;
			aHead->dir=LEFT;
		}
		else if(sFood->row > aHead->row)
		{	//ʳ������ͷ�ұ�
			aHead->row++;
			aHead->dir=RIGHT;
		}
	}  
	else if ((aHead->col!=sFood->col))
	{
		if(sFood->col < aHead->col)
		{	//ʳ������ͷ�·�
			aHead->col--;
			aHead->dir=DOWN;
		}
		if(sFood->col > aHead->col)
		{	//ʳ������ͷ�Ϸ�
			aHead->col++;
			aHead->dir=UP;
		} 
	}  
}
//�����߳�ʳ��
void Game::huoxingSnakeEat() 
{
	//�����ߵ���ײ���
	if(aHead->row==sFood->row&&aHead->col==sFood->col)
	{
		//ʳ��ӵ�ǰλ����ʧ�������������һ������  
		sFood->row = rand()%10;  
		sFood->col = rand()%10;  


		//������嵽����  
		SnakeNode * sn = new SnakeNode();//����һ���µĽڵ㣨Ҳ���ǳԵ����Ǹ�ʳ�������ŵ��ߵ�β����  
		SnakeNode * lastNode = NULL;  
		//��ȡ�ߵ����һ���ڵ㣬���allBody��size()Ϊ0����˵�����ǵ�һ�β�ʳ����ô�������һ���ڵ�Ҳ������ͷ����  
		if(asnakeBody.size()>0)  
			lastNode = (SnakeNode *)asnakeBody.back();  
		else  
			lastNode = aHead;//���һ���ڵ�����ͷ  


		//ͨ�����һ���ڵ�ķ��������µĽڵ��ʼ���ᡢ������  
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
		asnakeBody.push_back(sn);//���µĽڵ���뵽�ߵ�������
	}
}