/*对话框场景类的头文件*/
#ifndef _POP_LAYER_H_
#define _POP_LAYER_H_
#include "cocos2d.h"

using namespace cocos2d;

class PopLayer : public CCLayerColor
{
public:
	static CCScene * scene();
	bool init();
	CREATE_FUNC(PopLayer);
private:
	//注册触摸事件，实现ccTouchBegan()方法
	void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch * touch,CCEvent * pevent);
	//在弹出的对话框上加俩个按钮，以下的函数是对应的按钮的处理事件
	void yesButton(CCObject * object);
	//void noButton(CCObject * object);
	//设置对话框的title
	void setTitle();
	//设置对话框的文本内容
	void setContent();
	//m_size代表的是对话框背景的大小
	CCSize m_size;
	//对话框的背景精灵
	CCSprite * m_bgSprite;
};
#endif