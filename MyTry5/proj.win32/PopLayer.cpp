/*对话框场景类的具体实现*/
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

		//设置这个层的背景图片，并且设置其位置为整个屏幕的中点
		CCSprite * background = CCSprite::create("dialogbg.png");
		m_bgSprite = background;
		background->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(background);

		//获得背景图片的大小
		CCSize contentSize = background->getContentSize();
		m_size = contentSize;

		//添加俩个菜单在这个层中
		CCMenuItemImage * item1 = CCMenuItemImage::create("ok.png",
			"ok.png","ok.png",
			this,menu_selector(PopLayer::yesButton));

		CCMenu* menu = CCMenu::create(item1,NULL);
		menu->alignItemsHorizontallyWithPadding(5);
		menu->setPosition(ccp(contentSize.width/2,contentSize.height/3));
		//kCCMenuHandlerPriority的值为-128，代表的是菜单按钮的触摸优先级
		//设置menu优先级，这里设置为普通menu的二倍减一，原因看下边
		menu->setTouchPriority(kCCMenuHandlerPriority-1);

		background->addChild(menu);

		//设置题目和文本内容
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
	//kCCMenuHandlerPriority=-128，将这个值设置为-128的二倍，可以比下边的层的优先级高
	//而且ccTouchBegan的返回值为true，说明其他的层将接受不到这个触摸消息了，只有这个层上边的
	//菜单的优先级比他还要打，所以它上边的菜单是可以接收到触摸消息的
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,
		kCCMenuHandlerPriority,true);
}

bool PopLayer::ccTouchBegan(CCTouch* touch,CCEvent* pevent)
{
	//this->removeFromParentAndCleanup(true);
	// 因为拦截了所有消息(包括按钮) 所以需要将消息手动传给模态对话框上的按钮
	/*if (menu) {
		menu->ccTouchBegan(touch, pevent);
		menu->ccTouchMoved(touch, pevent);
	}*/
	return true;
}

//点击菜单按钮的时候调用的事件处理函数
void PopLayer::yesButton(CCObject* object)
{
	this->removeFromParentAndCleanup(true);
}

//设置这个层的题目
void PopLayer::setTitle()
{
	//CCLabelTTF * title = CCLabelTTF::create("Tips","",24);
	CCLabelBMFont * title = CCLabelBMFont::create("HighScores","futura-48.fnt");
	title->setPosition(ccp(m_size.width/2,m_size.height-title->getContentSize().height/2));
	m_bgSprite->addChild(title);
}

//设置层的内容
void PopLayer::setContent()
{
	//最高分纪录
	char a[20];
	int HighScores = CCUserDefault::sharedUserDefault()->getIntegerForKey("Hiscores");

	CCLabelBMFont * content = CCLabelBMFont::create(itoa(HighScores,a,10), "markerFelt.fnt");
	content->setPosition(ccp(m_size.width/2,m_size.height/2));

	m_bgSprite->addChild(content);
}