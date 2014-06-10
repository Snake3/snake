#ifndef __GAME_H__
#define __GAME_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "EarthSnake.h"
#include "MarsSnake.h"
#include "Score.h"

//枚举
typedef enum {  
	UP=1,  
	DOWN=2,  
	LEFT=3,  
	RIGHT=4  
}DIR_DEF;

class Game : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	void responseFunc(CCObject* obj);

    // implement the "static node()" method manually
    CREATE_FUNC(Game);

	void myDefine(CCNode* who);
	void createTarget();

	//显示蛇的函数
	void drawFood(SnakeNode* sFood);
	void drawEarth(EarthSnake *earthSnake);
	void drawMars(MarsSnake *marsSnake);

	//是否在障碍物里
	bool isInObstacle(CCPoint point);
	void ChooseMap();

	void initSnakeBody();
	bool isHaveSaveFile();
	void gameEndResponse();
	void lose();
	void win();

	//计算出蛇下个位置所以节点的坐标
	void gameLogic1(float dt);
	void gameLogic2(float dt);
	void earthDoAction(int action);
	void marsDoAction(int action);

	void judgeOver();
	void createFood(EarthSnake*,MarsSnake*,bool haveEat);
	void restart();
	void setMarsSnakeScores(Score);
	void setEarthSnakeScores(Score);

	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
private:
	//CCSprite* bg;
	Score EarthSnakeScores, MarsSnakeScores;
	CCMenuItemImage *pPlayItem, *pPauseItem, *pMusicONItem, *pMusicOFFItem;
	CCLabelAtlas *label1, *label2;
	
};

#endif  // __HELLOWORLD_SCENE_H_