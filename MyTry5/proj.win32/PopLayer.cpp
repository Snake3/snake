/*�Ի��򳡾���ľ���ʵ��*/
#include "PopLayer.h"

using namespace std;

CCScene * PopLayer::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		PopLayer * layer = PopLayer::create();
		scene->addChild(layer);
	}
	while(0);

	return scene;
}

bool PopLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(25, 25, 25, 125)));
		
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		//���������ı���ͼƬ������������λ��Ϊ������Ļ���е�
		CCSprite * background = CCSprite::create("dialogbg.png");
		m_bgSprite = background;
		background->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(background);

		//��ñ���ͼƬ�Ĵ�С
		CCSize contentSize = background->getContentSize();
		m_size = contentSize;

		//��������˵����������
		CCMenuItemImage * item1 = CCMenuItemImage::create("ok.png",
			"ok.png","ok.png",
			this,menu_selector(PopLayer::yesButton));

		CCMenu* menu = CCMenu::create(item1,NULL);
		menu->alignItemsHorizontallyWithPadding(5);
		menu->setPosition(ccp(contentSize.width/2,contentSize.height/3));
		//kCCMenuHandlerPriority��ֵΪ-128��������ǲ˵���ť�Ĵ������ȼ�
		//����menu���ȼ�����������Ϊ��ͨmenu�Ķ�����һ��ԭ���±�
		menu->setTouchPriority(kCCMenuHandlerPriority-1);

		background->addChild(menu);

		//������Ŀ���ı�����
		this->setTitle();
		this->setContent();

		this->setTouchEnabled(true);
		bRet = true;
	}
	while(0);

	return bRet;
}

void PopLayer::registerWithTouchDispatcher()
{
	//kCCMenuHandlerPriority=-128�������ֵ����Ϊ-128�Ķ��������Ա��±ߵĲ�����ȼ���
	//����ccTouchBegan�ķ���ֵΪtrue��˵�������Ĳ㽫���ܲ������������Ϣ�ˣ�ֻ��������ϱߵ�
	//�˵������ȼ�������Ҫ���������ϱߵĲ˵��ǿ��Խ��յ�������Ϣ��
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,
		kCCMenuHandlerPriority,true);
}

bool PopLayer::ccTouchBegan(CCTouch* touch,CCEvent* pevent)
{
	//this->removeFromParentAndCleanup(true);
	// ��Ϊ������������Ϣ(������ť) ������Ҫ����Ϣ�ֶ�����ģ̬�Ի����ϵİ�ť
	/*if (menu) {
		menu->ccTouchBegan(touch, pevent);
		menu->ccTouchMoved(touch, pevent);
	}*/
	return true;
}

//����˵���ť��ʱ����õ��¼�������
void PopLayer::yesButton(CCObject* object)
{
	this->removeFromParentAndCleanup(true);
}

//������������Ŀ
void PopLayer::setTitle()
{
	//CCLabelTTF * title = CCLabelTTF::create("Tips","",24);
	CCLabelBMFont * title = CCLabelBMFont::create("HighScores","futura-48.fnt");
	title->setPosition(ccp(m_size.width/2,m_size.height-title->getContentSize().height/2));
	m_bgSprite->addChild(title);
}

//���ò������
void PopLayer::setContent()
{
	//��߷ּ�¼
	char a[20];
	int HighScores = CCUserDefault::sharedUserDefault()->getIntegerForKey("Hiscores");

	CCLabelBMFont * content = CCLabelBMFont::create(itoa(HighScores,a,10), "markerFelt.fnt");
	content->setPosition(ccp(m_size.width/2,m_size.height/2));

	m_bgSprite->addChild(content);
}