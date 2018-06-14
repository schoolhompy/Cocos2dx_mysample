#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

static Point pntJoystickZero = Point(120, 120);
static float pntJoystickOutRange = 50.0f;
static float pntJoystickInRange = 25.0f;

static bool isPressedLeft = false;
static bool isPressedRight = false;

static bool isPointInCircle(CCPoint point, CCPoint center, float radius){
	float dx = (point.x - center.x);
	float dy = (point.y - center.y);
	return (radius >= sqrt((dx*dx) + (dy*dy)));
}

static CCPoint convertCoordinate(CCPoint point){
	return CCDirector::sharedDirector()->convertToGL(point);
}


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


	

		Sprite *back = Sprite::create("space.jpg");
		back->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		this->addChild(back);



	pHudLayer = Layer::create();
	pHudLayer->setPosition(Vec2::ZERO);


	pHeroSprite = Sprite::create("ufoBlue.png");
	pHeroSprite->setPosition(240, 160);
	this->addChild(pHeroSprite);



	pHeroBabySprite = Sprite::create("layergun.png");
	pHeroBabySprite->setPosition(Vec2(pHeroSprite->getContentSize().width*0.5, pHeroSprite->getContentSize().height*0.5));
	pHeroBabySprite->setName("herobaby");
	pHeroSprite->addChild(pHeroBabySprite);



	// 왼쪽 조이스틱
	Sprite *pimsi2 = Sprite::create("circle.png");
	pimsi2->setPosition(Vec2(pntJoystickZero.x, pntJoystickZero.y));
	pimsi2->setOpacity(150);
	pimsi2->setColor(Color3B::WHITE);
	pimsi2->setOpacity(128);
	pimsi2->setName("hudLeft_back");

	Sprite *pimsi1 = Sprite::create("circle.png");
	pimsi1->setScale(0.25f);
	pimsi1->setPosition(Vec2(pntJoystickZero.x, pntJoystickZero.y));
	pimsi1->setName("hudLeft");

	pHudLayer->addChild(pimsi2, 10);
	pHudLayer->addChild(pimsi1, 11);


	// 오른쪽 조이스틱
	Sprite *pimsi2_2 = Sprite::create("circle.png");
	pimsi2_2->setPosition(Vec2(pntJoystickZero.x + 200, pntJoystickZero.y));
	pimsi2_2->setOpacity(150);
	pimsi2_2->setOpacity(150);
	pimsi2_2->setColor(Color3B::WHITE);
	pimsi2_2->setName("hudRight_back");

	Sprite *pimsi1_2 = Sprite::create("circle.png");
	pimsi1_2->setScale(0.25f);
	pimsi1_2->setPosition(Vec2(pntJoystickZero.x + 200, pntJoystickZero.y));

	pimsi1_2->setName("hudRight");

	pHudLayer->addChild(pimsi2_2, 10);
	pHudLayer->addChild(pimsi1_2, 11);


	this->addChild(pHudLayer);

	this->scheduleUpdate();
	return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	log("menuCloseCallback");

}

void HelloWorld::update(float delta)
{

	if (isLeftJoystickPressed == true) {
		pHeroSprite->setPosition(pHeroSprite->getPosition() + velocity);
		//pHeroSprite->setRotation(vTankangle);
		
	}
	if (isRightJoystickPressed == true) {

		pHeroBabySprite->setRotation(vangle);
	}

	
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


}

void HelloWorld::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, Event* event){

	Touch* touch;
	Vec2 touchPoint;
	Point globalPoint;


	for (int index = 0; index < touches.size(); index++)
	{
		touch = touches[index];
		touchPoint = touch->getLocation();
		int touchIndex = touch->getID();

		globalPoint = convertCoordinate(touchPoint);

		if (isPointInCircle(touchPoint, pntJoystickZero, pntJoystickOutRange))
		{
			//search hud
			Vector<Node*> allNodes = pHudLayer->getChildren();
			for (auto& node : allNodes)
			{
				if (dynamic_cast<Sprite*>(node))
				{ //It is Sprite 
					Sprite *pSprite = dynamic_cast<Sprite*>(node);
					if (pSprite->getName().compare("hudLeft") == 0)
					{
						touchingSprites[touchIndex] = pSprite->getName().c_str();
						log("in it %s", pSprite->getName().c_str());
						pTouchedSprite = pSprite;
						isLeftJoystickPressed = true;
					}
					
				}
			}//for
		}

		if (isPointInCircle(touchPoint, Vec2(200,0) + pntJoystickZero, pntJoystickOutRange))
		{	
			//search hud
			Vector<Node*> allNodes = pHudLayer->getChildren();
			for (auto& node : allNodes)
			{
				if (dynamic_cast<Sprite*>(node))
				{ //It is Sprite 
					Sprite *pSprite = dynamic_cast<Sprite*>(node);
					if (pSprite->getName().compare("hudRight") == 0)
					{
						touchingSprites[touchIndex] = pSprite->getName().c_str();
						log("in it %s", pSprite->getName().c_str());
						pTouchedSprite = pSprite;
						isRightJoystickPressed = true;

						//this->bullet(0);
						this->schedule(schedule_selector(HelloWorld::bullet), 0.3f);
					}

				}
			}//for
		}

	}


}


void HelloWorld::updateBaby(Vec2 point1)
{

	// calculate Angle and length
	float dx = point1.x - (pntJoystickZero.x+200.0f);
	float dy = point1.y - pntJoystickZero.y;

	float radian = atan2(dx, dy); // in radians

	vangle = CC_RADIANS_TO_DEGREES(radian);

	float angle = vangle;
	if (angle < 0.0f) {
		angle = 360.0f + vangle;
	}

	vPoint = 30.0f *Point(sin(CC_DEGREES_TO_RADIANS(angle)), cos(CC_DEGREES_TO_RADIANS(angle)));
	//vPoint = 30.0f *Point(cos(CC_DEGREES_TO_RADIANS(angle)), sin(CC_DEGREES_TO_RADIANS(angle)));

	log("%f angle %f angle %f -> %f", vangle, angle, vPoint.x, vPoint.y);
	
}
Vec2 HelloWorld::updateVelocity(Vec2 point1, Vec2 pzero)
{
	// calculate Angle and length
	float dx = point1.x - pzero.x;
	float dy = point1.y - pzero.y;

	float distance = sqrt(dx*dx + dy*dy);
	float radian = atan2(dy, dx); // in radians

	vTankangle = CC_RADIANS_TO_DEGREES(radian);

	float angle = vTankangle;
	if (angle < 0.0f) {
		angle = 360.0f + angle;
	}
	vTankangle = angle;
	log(" vTankangle %f", vTankangle);

	if (distance > pntJoystickOutRange)
	{
		dx = cos(radian) * pntJoystickOutRange;
		dy = sin(radian) * pntJoystickOutRange;
	}



	if (distance>pntJoystickOutRange)
	{
		point1.x = pzero.x + cos(radian) * pntJoystickOutRange;
		point1.y = pzero.y + sin(radian) * pntJoystickOutRange;
	}

	pTouchedSprite->setPosition(point1);

	return CCPointMake(dx / pntJoystickInRange, dy / pntJoystickInRange);
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

		//search hud
		std::map<int, std::string>::iterator it;


		//  begin 때의 터치 번호와 이동의 터치 번호가 같으면.  end  가 아닌게 같아
		it = touchingSprites.find(touchIndex);
		if (it != touchingSprites.end())
		{
			log("in it %s", it->second.c_str());
			pSprite = dynamic_cast<Sprite*>(pHudLayer->getChildByName(it->second));
			//left 버튼이면.
			if (pSprite->getName().compare("hudLeft") == 0)
			{
				log("in hudLeft");
				velocity = this->updateVelocity(touchPoint, pntJoystickZero);
			}

			//right 버튼이면.
			if (pSprite->getName().compare("hudRight") == 0)
			{
				log("in hudRight");

				this->updateVelocity(touchPoint, Vec2(200,0) + pntJoystickZero);
				this->updateBaby(touchPoint);

			}

		
		}



	}//for

}

void HelloWorld::bullet(float delta)
{
	Sprite* pSprite = Sprite::create("laserBlue08.png");
	pSprite->setPosition(pHeroBabySprite->getParent()->convertToWorldSpace(pHeroBabySprite->getPosition()));

	auto *pPipeMove2 = MoveBy::create(0.2f, vPoint);
	pSprite->setTag(91);

	RepeatForever *enermyRemove2 = RepeatForever::create(pPipeMove2);
	//Sequence *pStudent2Action2 = Sequence::create(enermyRemove2, NULL);

	pSprite->runAction(enermyRemove2);

	this->addChild(pSprite);
}

void HelloWorld::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, Event* event)
{
	isLeftJoystickPressed = false;
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

		//search hud
		std::map<int, std::string>::iterator it;


		//  begin 때의 터치 번호와 이동의 터치 번호가 같으면.
		it = touchingSprites.find(touchIndex);
		if (it != touchingSprites.end())
		{
			Sprite *pSprite = dynamic_cast<Sprite*>(pHudLayer->getChildByName(it->second));


			
				if (pSprite->getName().compare("hudLeft") == 0)
				{

					pSprite->setPosition(pntJoystickZero);
					isLeftJoystickPressed = false;
					velocity = Vec2(0,0);
				}



				if (pSprite->getName().compare("hudRight") == 0)
				{
					this->unschedule(schedule_selector(HelloWorld::bullet));
					pSprite->setPosition(Vec2(200,0) + pntJoystickZero);
					isRightJoystickPressed = false;
					
				}



				
			

			touchingSprites.erase(it);

		}



	}//for


}