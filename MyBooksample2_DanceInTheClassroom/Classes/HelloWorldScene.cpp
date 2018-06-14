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
	this->scheduleUpdate();

	act1 = false;

	teacherAngry = false;
    
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
	mnuDanceTime = Menu::create(closeItem, NULL);
	mnuDanceTime->setPosition(Vec2::ZERO);
	this->addChild(mnuDanceTime, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label


	gameOver = Label::createWithTTF("GAME OVER", "fonts/Marker Felt.ttf", 60);
	gameOver->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	gameOver->setColor(Color3B::RED);
	gameOver->setVisible(false);
	this->addChild(gameOver, 150);


	score = 0;
    
	scorelabel = Label::createWithTTF("Score : 0", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
	scorelabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - scorelabel->getContentSize().height));

    // add the label as a child to this layer
	this->addChild(scorelabel, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("background.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);


	//--tables
	Sprite *pTables = Sprite::create("tables.png");
	pTables->setPosition(Vec2(233, 47));
	this->addChild(pTables, 1);

	//--chairs
	Sprite *pChairs = Sprite::create("chairs.png");
	pChairs->setPosition(Vec2(233, 20));
	this->addChild(pChairs, 10);




	//--teacher
	pTeacher = Sprite::create("teacher_1.png");
	pTeacher->setPosition(Vec2(150, 170));
	this->addChild(pTeacher, 0);



	spframe1 = SpriteFrame::create("teacher_1.png", Rect(0, 0, 94, 166));
	spframe2 = SpriteFrame::create("teacher_2.png", Rect(0, 0, 94, 166));	

	animation = Animation::create();
	animation->setDelayPerUnit(0.3f);
	animation->addSpriteFrame(spframe1);
	animation->addSpriteFrame(spframe2);
	animate = Animate::create(animation);
	rf1 = RepeatForever::create(animate);
	rf1->setTag(101);
	rf1->retain();
	

	HelloWorld::tAction();


	this->scheduleOnce(schedule_selector(HelloWorld::teacherAngrySchedule), 1.0f);

	//student1-------------------------------------------------------------------
	studentBase1 = Sprite::create("student1_0.png");
	studentBase1->setPosition(Vec2(90, 50));//105/236/370
	this->addChild(studentBase1, 5);


	studentDance1 = Sprite::create("student1_1.png");
	studentDance1->setPosition(Vec2(90, 120));//105/236/370
	this->addChild(studentDance1, 5);

	SpriteFrame *spStudent1_1 = SpriteFrame::create("student1_1.png", Rect(0, 0, 100, 150));
	SpriteFrame *spStudent1_2 = SpriteFrame::create("student1_2.png", Rect(0, 0, 100, 150));

	Animation *animationStudent1 = Animation::create();
	animationStudent1->setDelayPerUnit(0.1f);
	animationStudent1->addSpriteFrame(spStudent1_1);
	animationStudent1->addSpriteFrame(spStudent1_2);
	Animate *aniStudent = Animate::create(animationStudent1);
	RepeatForever *repeatStudent1 = RepeatForever::create(aniStudent);
	repeatStudent1->setTag(101);
	repeatStudent1->retain();
	studentDance1->runAction(repeatStudent1);


	//student2-------------------------------------------------------------------
	studentBase2 = Sprite::create("student2_0.png");
	studentBase2->setPosition(Vec2(230, 50));//105/236/370
	this->addChild(studentBase2, 5);

	studentDance2 = Sprite::create("student2.png");
	studentDance2->setPosition(Vec2(245, 120));//105/236/370
	this->addChild(studentDance2, 5);

	auto *pStudent2Jump = JumpTo::create(1.0, Point(245, 120), 50, 1);
	auto *pStudent2JumpReturn = pStudent2Jump->reverse();
	Sequence *pStudent2Action1 = Sequence::create(pStudent2Jump, pStudent2JumpReturn, NULL);
	RepeatForever *repeatStudent2 = RepeatForever::create(pStudent2Action1);
	studentDance2->runAction(repeatStudent2);



	//student3-------------------------------------------------------------------
	studentBase3 = Sprite::create("student3_0.png");
	studentBase3->setPosition(Vec2(380, 50));//105/236/370
	this->addChild(studentBase3, 5);

	 studentDance3 = CSLoader::createNode("student3.csb");
	this->addChild(studentDance3, 5);
	studentDance3->setPosition(Point(370, 120));

	cocostudio::timeline::ActionTimeline* action = CSLoader::createTimeline("student3.csb");
	action->play("dance", true);
	studentDance3->runAction(action);


	this->seatDown();

    return true;
}

void HelloWorld::teacherAngrySchedule(float delta)
{

	teacherAngry = true;
	pTeacher->pause();
	

	pTeacher->setTexture(Director::getInstance()->getTextureCache()->addImage("teacher_3.png"));
	//this->getActionManager()->pauseTarget(pTeacher);
	
	this->scheduleOnce(schedule_selector(HelloWorld::teacherScheduleOnce), 1.0f);
	


}

void HelloWorld::teacherScheduleOnce(float delta)
{
	teacherAngry = false;
	pTeacher->setTexture(Director::getInstance()->getTextureCache()->addImage("teacher_1.png"));

	pTeacher->resume();

	//pTeacher->setTexture(Director::getInstance()->getTextureCache()->addImage("teacher_1.png"));


	int ttime = random(3, 5);
	this->scheduleOnce(schedule_selector(HelloWorld::teacherAngrySchedule), (float)ttime);



}

void HelloWorld::tAction(){
	pTeacher->runAction(rf1);

	auto *pTeacherMove = MoveBy::create(3.0, Point(190, 0));
	auto *pTeacherMoveReturn = pTeacherMove->reverse();
	Sequence *pTeaherAction1 = Sequence::create(pTeacherMove, pTeacherMoveReturn, NULL);



	pTeaherRepeat = RepeatForever::create(pTeaherAction1);
	pTeacher->runAction(pTeaherRepeat);

	pTeaherRepeat->setTag(110);





}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	if ( Director::getInstance()->isPaused() == true ){
		return;
	}

	act1 = !act1;


	if (act1 == false) {
		seatDown();
	}
	else{
		danceTime();
	}
	

	//Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::seatDown()
{
	studentDance1->pause();
	studentDance2->pause();
	studentDance3->pause();


	studentDance1->setVisible(false);
	studentDance2->setVisible(false);
	studentDance3->setVisible(false);

	studentBase1->setVisible(true);
	studentBase2->setVisible(true);
	studentBase3->setVisible(true);
}

void HelloWorld::danceTime()
{
	studentBase1->setVisible(false);
	studentBase2->setVisible(false);
	studentBase3->setVisible(false);


	studentDance1->resume();
	studentDance2->resume();
	studentDance3->resume();

	studentDance1->setVisible(true);
	studentDance2->setVisible(true);
	studentDance3->setVisible(true);

	//score++;
	//scorelabel->setString(StringUtils::format("SCORE :%d", score));

}

void HelloWorld::update(float delta){


	if (teacherAngry == true && act1 == true) {

		gameOver->setVisible(true);
		mnuDanceTime->setEnabled(false);
		Director::getInstance()->pause();
		return;
	}


	if (act1 == true)
	{
		score++;
		scorelabel->setString(StringUtils::format("SCORE :%d", score));
	}
	
}