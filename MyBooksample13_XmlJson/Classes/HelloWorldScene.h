#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "tinyxml2/tinyxml2.h"
#include "Box2D\Box2D.h"
#include "GLES-Render.h"

USING_NS_CC;

#define SCALE_RATIO 32.0

using namespace tinyxml2;
using namespace cocos2d::network;

class HelloWorld : public cocos2d::Layer
{
public:

	b2World *world;


	Sprite *ball;
	Sprite *pTouchedSprite;
	float ballX;
	float ballY;

	b2Body *ballBody;
	b2CircleShape ballShape;
	b2BodyDef ballBodyDef;


	void addWall(float w, float h, float px, float py); 
	void defineBall();
	


	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);
	GLESDebugDraw* m_debugDraw;


	void update(float dt);

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void HelloWorld::getXmlValue(const char* url);
	void HelloWorld::loadXml(HttpClient *sender, HttpResponse *response);


	void menuCloseCallback(cocos2d::Ref* pSender);

	virtual void  onEnter();

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event *unused_event);

protected:
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCmd;
};

#endif // __HELLOWORLD_SCENE_H__
