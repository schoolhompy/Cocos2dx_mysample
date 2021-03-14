#include "LogoDnd.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "LogoSugoi.h"

USING_NS_CC;

using namespace cocostudio::timeline;


Scene* LogoDnd::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LogoDnd::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LogoDnd::init()
{
	//  you can create scene with following comment code instead of using csb file.
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();



	Sprite *pLogoDnd = Sprite::create("logo_dnd.png");
	pLogoDnd->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(pLogoDnd);


	this->scheduleOnce(schedule_selector(LogoDnd::nextLogo), 1.0f);
	return true;
}

void LogoDnd::nextLogo(float v)
{


	Scene *pScene = TransitionFade::create(2.0f, LogoSugoi::createScene(),  ccColor3B(255,255,255));
	Director::getInstance()->replaceScene(pScene);
}