#ifndef __GAME_H__
#define __GAME_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"

//ö��
typedef enum {  
	UP=1,  
	DOWN=2,  
	LEFT=3,  
	RIGHT=4  
}DIR_DEF;

//�ߵĽڵ�
class SnakeNode
{
public:  
	int row;//�ڼ���  
	int col;//�ڼ���  
	int dir;//����  
	SnakeNode()
	{
		row = rand()%10;  //0~9
		col = rand()%10;
		dir=1;//������
	}
};

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
	//��ʾ�ߵĺ���
	void draw(std::vector<SnakeNode*> allBody,SnakeNode* sHead,SnakeNode* sFood);

	//��������¸�λ�����Խڵ������
	void gameLogic(float dt);
	//������ƺ���
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

	// array ���� ɾ��Ч�ʵ� �����ҡ�����Ч�ʸ� 
	// list     ���� ɾ��Ч�ʸߣ����ҡ�����Ч�� ��
	// ��ɾ��������֡����ڳ��֡�����ײ���õĴ�����
	// ������ 1.0/fps ʱ�����һ�α���        �õĴ�����
	// ѡ��array

	//���Ｏ�Ϻͷ��ڼ���
	//cocos2d::CCArray* _snake2s;
	//cocos2d::CCArray* _projs;
//protected:
	//SnakeNode *sBody;  //̰ʳ��
	//cocos2d::CCArray* allBody;//�ߵ�����

};

#endif  // __HELLOWORLD_SCENE_H_