#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

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



	// add "HelloWorld" splash screen"
	pTouchedSprite = Sprite::create("sprite.png");

	// position the sprite on the center of the screen
	pTouchedSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(pTouchedSprite, 10);





	// add "HelloWorld" splash screen"
	Sprite * back = Sprite::create("background.png");

	// position the sprite on the center of the screen
	back->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(back, 0);




	 pHudLayer = Layer::create();
	pHudLayer->setPosition(Vec2::ZERO);

	auto sprite1 = Sprite::create("arrow.png");
	sprite1->setPosition(Vec2(30, 50));
	sprite1->setName("hudLeft");
	pHudLayer->addChild(sprite1, 0);
	

	auto sprite2 = Sprite::create("arrow.png");
	sprite2->setPosition(Vec2(79, 50));
	sprite2->setName("hudRight");
	sprite2->setFlipX(true);
	pHudLayer->addChild(sprite2, 0);



	auto sprite3 = Sprite::create("button1.png");
	sprite3->setPosition(Vec2(400, 50));
	sprite3->setName("hudJump");
	pHudLayer->addChild(sprite3, 0);



	auto sprite4 = Sprite::create("button2.png");
	sprite4->setPosition(Vec2(450, 90));
	sprite4->setName("hudBomb");
	pHudLayer->addChild(sprite4, 0);

	this->addChild(pHudLayer);


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
					if (pSprite->getName().compare("hudRight") == 0 || pSprite->getName().compare("hudLeft") == 0)
					{

						originalXY = pSprite->getPosition();

						label->setString(pSprite->getName().c_str());
						log("Touched %s %i", pSprite->getName().c_str(), touchIndex);
						// pTouchedSprite = pSprite;

						auto *pPipeMove2 = MoveBy::create(0.2f, Vec2((pSprite->getName().compare("hudRight") == 0) ? 5 : -5, 0));
						auto *pRepeat = RepeatForever::create(pPipeMove2);
						pRepeat->setTag(90);//90 is move action
						pTouchedSprite->runAction(pRepeat);

						touchingSprites[touchIndex] = pSprite->getName().c_str();
					}

					if (pSprite->getName().compare("hudJump") == 0)
					{
						auto *pPipeMove3 = JumpBy::create(0.5f, Vec2(0,0),50,1);
						pTouchedSprite->runAction(pPipeMove3);
					}


					if (pSprite->getName().compare("hudBomb") == 0)
					{
						touchingSprites[touchIndex] = pSprite->getName().c_str();

						HelloWorld::bullet(0);
						this->schedule(schedule_selector(HelloWorld::bullet), 0.3f);

						
					}

					break;
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

		//search hud
		std::map<int, std::string>::iterator it;


		//  begin 때의 터치 번호와 이동의 터치 번호가 같으면.  end  가 아닌게 같아
		it = touchingSprites.find(touchIndex);
		if (it != touchingSprites.end())
		{
			pSprite = dynamic_cast<Sprite*>(pHudLayer->getChildByName(it->second));
			if (pSprite->getName().compare("hudBomb") == 0)
			{
				continue;
			}

			//같은 스프라이트 위에서 있지 있다면 통과
			if (pSprite->getBoundingBox().containsPoint(touchPoint) == true)
			{
				continue;
			}
			else
			{
				pTouchedSprite->stopActionByTag(90);
				touchingSprites.erase(it);
				/*if (pSprite->getName().compare("hudJump") == 0 || pSprite->getName().compare("hudBomb") == 0)
				{
					log("Delete %s ", pSprite->getName().c_str());

					touchingSprites.erase(it);
				}*/
				
			}
		}

		//search hud
		Vector<Node*> allNodes = pHudLayer->getChildren();
		for (auto& node : allNodes)
		{
			if (dynamic_cast<Sprite*>(node))
			{ //It is Sprite 
				pSprite = dynamic_cast<Sprite*>(node);

				//점프는 한번만
				if (pSprite->getName().compare("hudJump") == 0)
				{
					continue;
				} else if (pSprite->getName().compare("hudBomb") == 0)
				{
					
				}
				else {

					if (pSprite->getBoundingBox().containsPoint(touchPoint) == true)
					{

						originalXY = pSprite->getPosition();

						label->setString(pSprite->getName().c_str());
						// pTouchedSprite = pSprite;



						auto *pPipeMove2 = MoveBy::create(0.2f, Vec2((pSprite->getName().compare("hudRight") == 0) ? 5 : -5, 0));
						auto *pRepeat = RepeatForever::create(pPipeMove2);
						pRepeat->setTag(90);//90 is move action
						pTouchedSprite->runAction(pRepeat);
						touchingSprites[touchIndex] = pSprite->getName().c_str();
						break;
					}
				}
			}


		}//for


	}//for

}

void HelloWorld::bullet(float delta)
{
	log("bullet");
	Sprite* pSprite = Sprite::create("bullet1.png");
	pSprite->setPosition(pTouchedSprite->getPosition());

	auto *pPipeMove2 = MoveBy::create(0.5f, Vec2(400,0));
	pSprite->setTag(91);//91 is move action

	RemoveSelf *enermyRemove2 = RemoveSelf::create(true);

	Sequence *pStudent2Action2 = Sequence::create(pPipeMove2, enermyRemove2, NULL);

	pSprite->runAction(pStudent2Action2);

	this->addChild(pSprite);
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

		//search hud
		std::map<int, std::string>::iterator it;


		//  begin 때의 터치 번호와 이동의 터치 번호가 같으면.
		it = touchingSprites.find(touchIndex);
		if (it != touchingSprites.end())
		{
			Sprite *pSprite = dynamic_cast<Sprite*>(pHudLayer->getChildByName(it->second));

			
			if (pSprite->getBoundingBox().containsPoint(touchPoint) == true)
			{
				if (pSprite->getName().compare("hudRight") == 0 || pSprite->getName().compare("hudLeft") == 0)
				{

					log("Delete %s ", pSprite->getName().c_str());

					pTouchedSprite->stopActionByTag(90);
				}



			}

			if (pSprite->getName().compare("hudBomb") == 0)
			{
				log("hudBomb");
				this->unschedule(schedule_selector(HelloWorld::bullet));
			}
			touchingSprites.erase(it);

		}



	}//for


}