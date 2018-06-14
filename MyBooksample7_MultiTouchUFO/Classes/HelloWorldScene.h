#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:

	cocos2d::Label *label;
	cocos2d::Layer *pHudLayer;
	cocos2d::Sprite *pTouchedSprite;
	cocos2d::Sprite *pHeroSprite;
	cocos2d::Sprite *pHeroBabySprite;
	cocos2d::Point originalXY;
	cocos2d::Vec2 touchingPoint;
	std::map<int, std::string> touchingSprites;

	bool isLeftJoystickPressed = false;
	bool isRightJoystickPressed = false;
	cocos2d::Vec2 velocity = cocos2d::Vec2(0, 0);
	cocos2d::Vec2 vPoint = cocos2d::Vec2(0, 10);

	float vangle = 0.0f;
	float vTankangle = 0.0f;

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	void bullet(float delta);

	void menuCloseCallback(cocos2d::Ref* pSender);



	virtual void  update(float delta);
	virtual void  onEnter();

	cocos2d::Vec2 updateVelocity(cocos2d::Vec2 point, cocos2d::Vec2 pzero);
	void updateBaby(cocos2d::Vec2 point);

	

	virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
};

#endif // __HELLOWORLD_SCENE_H__
