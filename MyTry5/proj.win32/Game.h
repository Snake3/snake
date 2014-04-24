#ifndef __GAME_H__
#define __GAME_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "EarthSnake.h"
#include "MarsSnake.h"

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
	//virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void myDefine(CCNode* who);
	void pauseGame(CCObject* sender);
	void createTarget();
	//void myGameLogic(float dt);
	//void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	//void update(float delta) /* delta = 1.0 / fps */;
	//~Game();
	void setDirection(CCObject* obj);
	//显示蛇的函数
	void draw(EarthSnake *earthSnake,MarsSnake *marsSnake,SnakeNode* sFood);

	//计算出蛇下个位置所以节点的坐标
	void gameLogic(float dt);
	void judgeOver();
	void createFood(EarthSnake*,MarsSnake*,int haveEat);

	//游戏分块逻辑
	/*
	void huoxingSnakeHeadMoveDirection();
	void tanchiSnakeHeadMoveDirection();

	void huoxingSnakeMoveBody();
	void tanchiSnakeMoveBody();

	void tanchiSnakeEat();
	void huoxingSnakeEat();
	*/

	//方向控制函数
	//void runUp(float dt);
	//void runUpMain();
	//void runDown(float dt);
	//void runDownMain();
	//void runLeft(float dt);
	//void runLeftMain();
	//void runRight(float dt);
	//void runRightMain();
//private:
	//cocos2d::CCSprite *snake;

	// array 插入 删除效率低 ；查找、遍历效率高 
	// list     插入 删除效率高；查找、遍历效率 低
	// 添删：怪物出现　飞镖出现　　碰撞　用的次数少
	// 遍历： 1.0/fps 时间进行一次遍历        用的次数多
	// 选用array

	//怪物集合和飞镖集合
	//cocos2d::CCArray* _snake2s;
	//cocos2d::CCArray* _projs;
//protected:
	//SnakeNode *sBody;  //贪食蛇
	//cocos2d::CCArray* snakeBody;//蛇的身体
};

#endif  // __HELLOWORLD_SCENE_H_