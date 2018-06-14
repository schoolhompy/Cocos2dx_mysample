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
    if ( !Layer::init() )
    {
        return false;
	}
	score = 0;

	this->scheduleUpdate();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
										   CC_CALLBACK_1(HelloWorld::menuCloseCallback1, this));
	
	//closeItem->setPosition(Vec2(visibleSize.width / 2 - closeItem->getContentSize().width/2, closeItem->getContentSize().height));

	auto closeItem2 = MenuItemImage::create(
										"CloseNormal.png",
										"CloseSelected.png",
										CC_CALLBACK_1(HelloWorld::menuCloseCallback2, this));


	//closeItem2->setPosition(Vec2(closeItem->getPositionX() + closeItem->getContentSize().width, closeItem2->getContentSize().height));

    // create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, closeItem2, NULL);
    //menu->setPosition(Vec2(100,100));
	menu->alignItemsHorizontally();
	log("pos %f", visibleSize.width / 2.0f );
	log("pos %f", visibleSize.width / 2.0f - (closeItem->getContentSize().width + closeItem2->getContentSize().width ) / 2.0f);

	menu->setPosition(Vec2(visibleSize.width / 2.0f, closeItem->getContentSize().height));
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
	scorelabel = Label::createWithTTF("SCORE:0", "fonts/Marker Felt.ttf", 24);

    // position the label on the center of the screen
	scorelabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - scorelabel->getContentSize().height));

    // add the label as a child to this layer
	this->addChild(scorelabel, 1);



	gameOver = Label::createWithTTF("GAME OVER", "fonts/Marker Felt.ttf", 60);
	gameOver->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	gameOver->setColor(Color3B::RED);
	gameOver->setVisible(false);
	this->addChild(gameOver, 150);


	Layer *pBackgroundLayer = Layer::create();
    // add "HelloWorld" splash screen"
	pBackground = Sprite::create("background.png");
	pBackground->setPosition(Vec2(0,0));
	pBackground->setAnchorPoint(Vec2(0, 0));
	pBackgroundLayer->addChild(pBackground, 0);
    //
	Sprite* zoomedImage = Sprite::createWithSpriteFrame(pBackground->getSpriteFrame());
	zoomedImage->setPosition(Vec2(0, 480));
	zoomedImage->setAnchorPoint(Vec2(0, 0));
	pBackgroundLayer->addChild(zoomedImage, 0);

	pBackgroundLayer->setPosition(Vec2(0, 0));
	pBackgroundLayer->setAnchorPoint(Vec2(0, 0));
	this->addChild(pBackgroundLayer, 0);

	auto *pBackgroundMove = MoveBy::create(3.0, Point(0,-480));
	auto *pBackgroundReposition = Place::create(Point(0, 0));
	Sequence *pTeaherAction1 = Sequence::create(pBackgroundMove, pBackgroundReposition, NULL);



	RepeatForever *pTeaherRepeat = RepeatForever::create(pTeaherAction1);
	pBackgroundLayer->runAction(pTeaherRepeat);


	//hero 

	pHero = Sprite::create("hero.png");
	pHero->setPosition(Vec2(80, 80));
	pHero->setAnchorPoint(Vec2(0, 0));
	this->addChild(pHero, 0);


    return true;
}


void HelloWorld::menuCloseCallback2(Ref* pSender)
{
	
	log("X %f", pHero->getPositionX());
	if (pHero->getPositionX() > 160.0f){
		return;
	}
	turnRight();
}
void HelloWorld::menuCloseCallback1(Ref* pSender)
{
	log("X %f", pHero->getPositionX());
	if (pHero->getPositionX() < 80.0f){
		return;
	}

	turnLeft();
}

void HelloWorld::turnLeft()
{
	auto *pHeroMoveLeft = MoveBy::create(0.2f, Point(-80, 0));
	Sequence *pTeaherAction1 = Sequence::create(pHeroMoveLeft, NULL);
	pHero->runAction(pTeaherAction1);

}

void HelloWorld::turnRight()
{
	auto *pHeroMoveRight = MoveBy::create(0.2f, Point(80, 0));
	Sequence *pTeaherAction1 = Sequence::create(pHeroMoveRight, NULL);
	pHero->runAction(pTeaherAction1);
}


void HelloWorld::createEnemy()
{
	int randompos = random(0, 3);

	Sprite *pEnermy = Sprite::create("enermy.png");
	pEnermy->setPosition(Vec2(80.0f * (float)randompos + (80 - pEnermy->getContentSize().width)/2, 480));
	pEnermy->setAnchorPoint(Vec2(0, 0));
	pEnermy->setTag(100);
	this->addChild(pEnermy, 0);


	auto *pEnermyRun = MoveTo::create(3.0f, Vec2(pEnermy->getPositionX(), -80));
	RemoveSelf *enermyRemove = RemoveSelf::create(true);

	Sequence *pEnermyAction1 = Sequence::create(pEnermyRun, enermyRemove, NULL);
	pEnermy->runAction(pEnermyAction1);

}

void HelloWorld::update(float delta)
{


		score++;
		scorelabel->setString(StringUtils::format("SCORE :%d", score));
	


	int enermyCreate = random(1, 100);
	if (enermyCreate == 15) {
		this->createEnemy();
	}

	if (pHero->getPositionX() < 0.0f){
		pHero->setPositionX(0.0f);
	}

	if (pHero->getPositionX() > 240.0f){
		pHero->setPositionX(240.0f);
	}
	//log("X %f", pHero->getPosition().x);

	Vector<Node*> allNodes = this->getChildren();
	for (auto& node : allNodes)
	{
		if (dynamic_cast<Sprite*>(node))
		{ //It is Sprite 
			Sprite *target = dynamic_cast<Sprite*>(node);
			//Do whatever you like
			if (target->getTag() == 100 && pHero->getBoundingBox().intersectsRect(target->getBoundingBox()) == true)
			{
				//target->removeFromParentAndCleanup(true);


				gameOver->setVisible(true);
				Director::getInstance()->pause();
				return;


				log("collision");
			}//if
		}//if
	}//for


}