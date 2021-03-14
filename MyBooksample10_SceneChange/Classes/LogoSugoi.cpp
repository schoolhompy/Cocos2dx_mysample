#include "LogoSugoi.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameMainScene.h"


USING_NS_CC;

using namespace cocostudio::timeline;


Scene* LogoSugoi::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LogoSugoi::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LogoSugoi::init()
{
	//  you can create scene with following comment code instead of using csb file.
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();



	Sprite *pLogoSugoi = Sprite::create("logo_khjlab.png");
	pLogoSugoi->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(pLogoSugoi);




	this->scheduleOnce(schedule_selector(LogoSugoi::nextLogo), 3.0f);
	return true;
}

void LogoSugoi::nextLogo(float v)
{
	Scene *pScene = GameMain::createScene();
	Director::getInstance()->replaceScene(pScene);
}