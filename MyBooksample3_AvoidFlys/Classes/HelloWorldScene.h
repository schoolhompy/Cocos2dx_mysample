#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
	int score;
	cocos2d::Sprite* pBackground;
	cocos2d::Sprite* pHero;


	cocos2d::Label* scorelabel;
	cocos2d::Label* gameOver;

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
	// a selector callback
	void menuCloseCallback1(cocos2d::Ref* pSender);
	void menuCloseCallback2(cocos2d::Ref* pSender);
	void update(float delta);

	void turnLeft();
	void turnRight();
	
	void createEnemy();

};

#endif // __HELLOWORLD_SCENE_H__
