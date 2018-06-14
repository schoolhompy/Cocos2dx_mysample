#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include<string>

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

	wordPos[101] = "{{44, 210}, {51, 68}}";//Rect(44, 42, 51, 68) //RectFromString(
	wordPos[102] = "{{95, 210}, {67, 68}}";
	wordPos[103] = "{{162, 210}, {72, 68}}";
	wordPos[104] = "{{234, 210}, {30, 68}}";
	wordPos[105] = "{{264, 210}, {52, 68}}";
	wordPos[106] = "{{316, 210}, {63, 68}}";
	/*
	wordPos.insert(101, "{{44, 42}, {51, 68}}");//Rect(44, 42, 51, 68) //RectFromString(
	wordPos.insert(102, "{{95, 42}, {67, 68}}");
	wordPos.insert(103, "{{162, 42}, {72, 68}}");
	wordPos.insert(104, "{{234, 42}, {30, 68}}");
	wordPos.insert(105, "{{264, 42}, {52, 68}}");
	wordPos.insert(106, "{{316, 42}, {63, 68}}");*/



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


	scorelabel = Label::createWithTTF("SCORE:0", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	scorelabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - scorelabel->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(scorelabel, 1);



	gameOver = Label::createWithTTF("GREAT !!!", "fonts/Marker Felt.ttf", 60);
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



	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("family.plist");


	float baseX = 50.0f;
	float baseY = 50.0f;

	auto wordSPrite_f = Sprite::createWithSpriteFrameName("word_f.png");
	wordSPrite_f->setPosition(baseX, baseY);
	//wordSPrite_f->setAnchorPoint(Vec2(0, 0));
	baseX += wordSPrite_f->getContentSize().width;
	wordSPrite_f->setTag(101);
	this->addChild(wordSPrite_f);
	words.pushBack(wordSPrite_f);

	auto wordSPrite_a = Sprite::createWithSpriteFrameName("word_a.png");
	wordSPrite_a->setPosition(baseX, baseY);
	//wordSPrite_a->setAnchorPoint(Vec2(0, 0));
	baseX += wordSPrite_a->getContentSize().width;
	wordSPrite_a->setTag(102);
	this->addChild(wordSPrite_a);
	words.pushBack(wordSPrite_a);

	auto wordSPrite_m = Sprite::createWithSpriteFrameName("word_m.png");
	wordSPrite_m->setPosition(baseX, baseY);
	//wordSPrite_m->setAnchorPoint(Vec2(0, 0));
	baseX += wordSPrite_m->getContentSize().width;
	wordSPrite_m->setTag(103);
	this->addChild(wordSPrite_m);
	words.pushBack(wordSPrite_m);

	auto wordSPrite_i = Sprite::createWithSpriteFrameName("word_i.png");
	wordSPrite_i->setPosition(baseX, baseY);
	//wordSPrite_i->setAnchorPoint(Vec2(0, 0));
	baseX += wordSPrite_i->getContentSize().width;
	wordSPrite_i->setTag(104);
	this->addChild(wordSPrite_i);
	words.pushBack(wordSPrite_i);

	auto wordSPrite_l = Sprite::createWithSpriteFrameName("word_l.png");
	wordSPrite_l->setPosition(baseX, baseY);
	//wordSPrite_l->setAnchorPoint(Vec2(0, 0));
	baseX += wordSPrite_l->getContentSize().width;
	wordSPrite_l->setTag(105);
	this->addChild(wordSPrite_l);
	words.pushBack(wordSPrite_l);

	auto wordSPrite_y = Sprite::createWithSpriteFrameName("word_y.png");
	wordSPrite_y->setPosition(baseX, baseY);
	//wordSPrite_y->setAnchorPoint(Vec2(0, 0));
	wordSPrite_y->setTag(106);
	this->addChild(wordSPrite_y);
	words.pushBack(wordSPrite_y);
	


	score = words.size();



	this->addChild(pHero, 0);


	this->scheduleUpdate();

	return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	log("menuCloseCallback");
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
	EaseInOut *action_1 = EaseInOut::create(pStudent2Jump, 3.0);    // action, 탄성
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


				/*gameOver->setVisible(true);
				Director::getInstance()->pause();
				return;
				*/

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

void HelloWorld::onEnter()
{
	Layer::onEnter();

	log("onENter");
	//...

	auto listener = EventListenerTouchOneByOne::create();

	// 핸들링된 터치 이벤트를 터치 이벤트 array에서 지우겠다는 의미이다.
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	// 터치리스너의 우선순위를 (노드가) 화면에 그려진 순서대로 한다.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


}

bool HelloWorld::onTouchBegan(Touch* touch, Event* unused_event){

	if (score == 0)  return true;

	Point location = touch->getLocation();
	//.....

	for (Sprite* pSprite : words)
	{
		if (pSprite->getBoundingBox().containsPoint(location) == true) {

			originalXY = pSprite->getPosition();


			log("Touched %i", pSprite->getTag());
			pTouchedSprite = pSprite;

			break;
		}

	}

	return true;

}

void HelloWorld::onTouchMoved(Touch* touch, Event* unused_event){
	
	Point location = touch->getLocation();
	if (pTouchedSprite) {
		pTouchedSprite->setPosition(location);
	}
	
}

void HelloWorld::onTouchCancelled(Touch* touch, Event* unused_event){
	log("onTouchCancelled");
}

void HelloWorld::onTouchEnded(Touch* touch, Event* unused_event){
	log("onTouchEnded" );

	Point location = touch->getLocation();

	if (!pTouchedSprite) return;

	std::map<int, std::string>::iterator itr = wordPos.begin();
	while (itr != wordPos.end()){
		auto key = itr->first;
		auto rectString = itr->second;

		Rect checkRect = RectFromString(rectString);

		if (checkRect.containsPoint(location) == true && pTouchedSprite->getTag() == key) {
			log("contraintPoint %i", key);
			originalXY = Point(checkRect.origin.x + pTouchedSprite->getContentSize().width / 2, checkRect.origin.y + pTouchedSprite->getContentSize().height / 2);
			score--;
		}

		

		++itr;
	}

	auto shootActionTest1 = CallFunc::create([&]() {
		pTouchedSprite = 0;

		if (score == 0) {
			gameOver->setVisible(true);
			Director::getInstance()->pause();
			return;

		}
	});

	auto *pPipeMove2 = MoveTo::create(0.3f, originalXY);

	Sequence *pStudent2Action2 = Sequence::create(pPipeMove2, shootActionTest1, NULL);
	pTouchedSprite->runAction(pStudent2Action2);

	log("score %i", score);
	
}