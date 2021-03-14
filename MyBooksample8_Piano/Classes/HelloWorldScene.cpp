#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"


USING_NS_CC;
using namespace experimental;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//  you can create scene with following comment code instead of using csb file.
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	musicExt = "ogg";
#else 
	musicExt = "m4a";
#endif


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);



	AudioEngine::preload("1.mp3", [=](bool isSuccess){

		if (isSuccess == true) {

			backaudioid = AudioEngine::play2d("1.mp3");
			label->setString(StringUtils::format("duration %f", AudioEngine::getDuration(backaudioid)));
			
		}
	});





	// add "HelloWorld" splash screen"
	Sprite * back = Sprite::create("background.png");

	// position the sprite on the center of the screen
	back->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(back, 0);




	pHudLayer = Layer::create();
	pHudLayer->setPosition(Vec2::ZERO);

	for (int i = 1; i < 9; i++){
		auto sprite1 = Sprite::create("gunban.png");
		sprite1->setPosition(Vec2(40+(50*(i-1)), 160));
		sprite1->setName(StringUtils::format("gunban%d", i));
		sprite1->setTag(i);
		pHudLayer->addChild(sprite1, 0);
	}

	this->addChild(pHudLayer);



	
	//AudioEngine::setFinishCallback(audioid, CC_CALLBACK_2(HelloWorld::finishCallBack, this));

	return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	log("menuCloseCallback");

}

void HelloWorld::update(float delta)
{
}


void HelloWorld::onEnter()
{
	Layer::onEnter();

	log("onENter");
	//...

	auto listener = EventListenerTouchAllAtOnce::create();

	// 핸들링된 터치 이벤트를 터치 이벤트 array에서 지우겠다는 의미이다.
	//listener->setSwallowTouches(true);


	listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(HelloWorld::onTouchesCancelled, this);
	listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);

	// 터치리스너의 우선순위를 (노드가) 화면에 그려진 순서대로 한다.
	_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

	log("duration %f", AudioEngine::getProfile(backaudioid));
	
	
}

void HelloWorld::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, Event* event){

	Touch* touch;
	Vec2 touchPoint;
	for (int index = 0; index < touches.size(); index++)
	{
		touch = touches[index];
		touchPoint = touch->getLocation();
		int touchIndex = touch->getID();
		std::stringstream ss;
		ss << touchIndex;
		//label->setString(label->getString() + ss.str());

		//search hud
		Vector<Node*> allNodes = pHudLayer->getChildren();
		for (auto& node : allNodes)
		{
			if (dynamic_cast<Sprite*>(node))
			{ //It is Sprite 
				Sprite *pSprite = dynamic_cast<Sprite*>(node);
				if (pSprite->getBoundingBox().containsPoint(touchPoint) == true)
				{

					//audio
					AudioEngine::play2d(StringUtils::format("gunban%d.mp3", pSprite->getTag()));
					AudioEngine::setCurrentTime(backaudioid, pSprite->getTag()*60);

					AudioEngine::setPitch(backaudioid, pSprite->getTag() /10.0f);;
				
					log("duration %f %d", AudioEngine::getDuration(backaudioid), pSprite->getTag());
					label->setString(StringUtils::format("duration %f", AudioEngine::getCurrentTime(backaudioid)));
					
				}
			}
		}//for

	}//for


}

void HelloWorld::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, Event* event)
{

	Touch* touch;
	Vec2 touchPoint;

	Sprite *pSprite;
	for (int index = 0; index < touches.size(); index++)
	{
		touch = touches[index];
		touchPoint = touch->getLocation();
		int touchIndex = touch->getID();
	}//for

}



void HelloWorld::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, Event* event)
{
	log("onTouchCancelled");
}

void HelloWorld::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, Event* event)
{
	log("onTouchEnded");


	Touch* touch;
	Vec2 touchPoint;
	for (int index = 0; index < touches.size(); index++)
	{
		touch = touches[index];
		touchPoint = touch->getLocation();
		int touchIndex = touch->getID();



	}//for


}