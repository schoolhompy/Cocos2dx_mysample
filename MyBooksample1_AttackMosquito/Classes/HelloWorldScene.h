#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"


class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();
	int audioid;
	
	int iMosquitoDuration = 1;
	long ldLastMosquitoAppear = 0;

	cocos2d::Sprite* back;

    virtual bool init();

	cocos2d::Sprite* Chick;
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* redblue;
	cocos2d::ParticleSystem* particleTest;

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void stopscene(float f);
	void setViewPointCenter(cocos2d::Point position);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	virtual void onEnter();
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void finishCallBack(int audioID, std::string filePath);

	void createMosquito();

	void update(float delta);

	void mosquitoCallBack(Ref* pSender);


};

#endif // __HELLOWORLD_SCENE_H__
