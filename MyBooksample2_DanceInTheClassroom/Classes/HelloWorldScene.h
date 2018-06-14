#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class HelloWorld : public cocos2d::Layer
{
public:
	bool act1;
	bool teacherAngry;
	cocos2d::Sprite* pTeacher;

	cocos2d::Sprite* studentBase1;
	cocos2d::Sprite* studentBase2;
	cocos2d::Sprite* studentBase3;

	cocos2d::Sprite* studentDance1;
	cocos2d::Sprite* studentDance2;
	cocos2d::Node* studentDance3;

	cocos2d::Label* scorelabel;
	cocos2d::Label* gameOver;

	cocos2d::Menu *mnuDanceTime;
	int score;

	void teacherAngrySchedule(float delta);
	void teacherScheduleOnce(float delta);
	void tAction();
	cocos2d::Animate *animate;
	cocos2d::Animate *animate2;


	cocos2d::SpriteFrame *spframe1;
	cocos2d::SpriteFrame *spframe2;
	cocos2d::SpriteFrame *spframe3;


	cocos2d::Animation *animation;
	cocos2d::Animation *animation2;


	cocos2d::RepeatForever *rf1;
	cocos2d::RepeatForever *rf2;
	cocos2d::RepeatForever *pTeaherRepeat;

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	void seatDown();
	void danceTime();
	

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void update(float delta);
};


#endif // __HELLOWORLD_SCENE_H__
