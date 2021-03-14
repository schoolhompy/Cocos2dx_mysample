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

	gameRunning = false;
    
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
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
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


    // add "HelloWorld" splash screen"
    background = Sprite::create("background.png");
	background->setPosition(Vec2(0, 0));
	background->setAnchorPoint(Vec2(0, 0));
	this->addChild(background, 0);

	auto *spriteMoveTo = MoveBy::create(1.0f, Vec2(-10.0f, 0));
	RepeatForever *repeatStudent2 = RepeatForever::create(spriteMoveTo);
	background->runAction(repeatStudent2);





	pHero = Sprite::create("bird.png");
	pHero->setPosition(Vec2(visibleSize.width / 2 - 50, visibleSize.height / 2));
	
	this->addChild(pHero, 0);


	this->scheduleUpdate();

    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	if (gameRunning == false) {
		this->schedule(schedule_selector(HelloWorld::pipeschedule), 2.0f);
		gameRunning = true;
	}

	pHero->stopAllActions();


	auto *pStudentFallDown = MoveBy::create(0.1f, Vec2(0, -10.0f));
	RepeatForever *repeatStudent2 = RepeatForever::create(pStudentFallDown);
	repeatStudent2->setTag(100);
	pHero->runAction(repeatStudent2);

	auto *pStudent2Jump = JumpBy::create(0.9f, Point(0, 80), 80, 1);
	EaseInOut *action_1 = EaseInOut::create(pStudent2Jump, 3.0);    // action, Åº¼º
	Sequence *pStudent2Action1 = Sequence::create(action_1, NULL);

	auto *pStudent2Rotate1 = RotateTo::create(0.3f, -60);
	auto *pStudent2Rotate2 = RotateTo::create(0.3f, 90);
	Sequence *pStudent2Action2 = Sequence::create(pStudent2Rotate1, pStudent2Rotate2, NULL);
	Spawn *spawn = Spawn::create(pStudent2Action1, pStudent2Action2, NULL);
	spawn->setTag(101);

	pHero->runAction(pStudent2Action1);
}



void HelloWorld::update(float delta)
{



	if (pHero->getPositionY() < 0.0f)
	{
		gameOver->setVisible(true);
		Director::getInstance()->pause();
		return;
	}
	if (background->getPositionX() < 800.0f - 480.0f){
		background->setPosition(Vec2(0, 0));
	}


	Vector<Node*> allNodes = this->getChildren();
	for (auto& node : allNodes)
	{
		if (dynamic_cast<Sprite*>(node))
		{ //It is Sprite 
			Sprite *target = dynamic_cast<Sprite*>(node);
			//Do whatever you like
			if (target->getTag() == 100 && target->getBoundingBox().containsPoint(pHero->getPosition()) == true)
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

void HelloWorld::pipeschedule(float delta)
{

	score++;
	scorelabel->setString(StringUtils::format("SCORE :%d", score));

	int pipeY = random(120, 300);

	Sprite *pPipe = Sprite::create("pipe.png");
	pPipe->setPosition(320, pipeY);
	pPipe->setAnchorPoint(Vec2(0, 1.0f));
	pPipe->setTag(100);
	this->addChild(pPipe, 0);

	auto *pPipeMove = MoveBy::create(2.5f, Vec2(-500, 0));
	RemoveSelf *enermyRemove = RemoveSelf::create(true);

	Sequence *pStudent2Action1 = Sequence::create(pPipeMove, enermyRemove, NULL);
	pPipe->runAction(pStudent2Action1);



	Sprite *pPipe2 = Sprite::create("pipe.png");
	pPipe2->setPosition(320, pipeY + 150);
	pPipe2->setFlipY(true);
	pPipe2->setAnchorPoint(Vec2(0, 0));
	pPipe2->setTag(100);
	this->addChild(pPipe2, 0);

	auto *pPipeMove2 = MoveBy::create(2.5f, Vec2(-500, 0));
	RemoveSelf *enermyRemove2 = RemoveSelf::create(true);

	Sequence *pStudent2Action2 = Sequence::create(pPipeMove2, enermyRemove2, NULL);
	pPipe2->runAction(pStudent2Action2);



}