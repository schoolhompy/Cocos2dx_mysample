#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
	cocos2d::Sprite *pTouchedSprite;
	cocos2d::Sprite *pSprite;

	cocos2d::Vec2 touchBeginPoint;
	cocos2d::Label *label;

	cocos2d::ParticleSystemQuad* explodeParticle ;

	cocos2d::Vec2 pntJoystickZero = cocos2d::Vec2(240, 160);

	bool isExploding = false;
	int spriteAngle = 270;

	int angle = 0;
	int score = 0;
	cocos2d::ParticleSystem* particleTest;

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual void  update(float delta);
	virtual void  onEnter();


	void wakefire(float dt);
	void zoompa(float dt);

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event *unused_event);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
