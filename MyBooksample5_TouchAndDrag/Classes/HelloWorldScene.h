#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
	std::map<int, std::string> wordPos;
	bool gameRunning;
	cocos2d::Vector<cocos2d::Sprite*> words;

	cocos2d::Sprite *pTouchedSprite;
	cocos2d::Point originalXY;


	
	int score;
	cocos2d::Label* scorelabel;
	cocos2d::Label* gameOver;

	cocos2d::Sprite *pHero;
	cocos2d::Sprite *background;

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);


	void menuCloseCallback(cocos2d::Ref* pSender);

	void pipeschedule(float delta);


	virtual void  update(float delta);
	virtual void  onEnter();


	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event *unused_event);


};

#endif // __HELLOWORLD_SCENE_H__
