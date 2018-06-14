#include "HelloWorldScene.h"
#include "audio/include/AudioEngine.h"
#include "network/HttpClient.h"

USING_NS_CC;
using namespace experimental;
using namespace network;

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
    //////////////////////////////
    // 1. super init first
	if (!LayerColor::initWithColor(ccc4(0, 0, 0, 255)))
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

	auto back = Sprite::create("babyroom.png");
	back->setPosition(Point(0, 0));
	back->setAnchorPoint(Point(0, 0));
	this->addChild(back);


	auto menuFont1 = MenuItemImage::create("babysleeping.png", "babyfire.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	auto menu = Menu::create(menuFont1, NULL);
	menu->alignItemsVertically();
	this->addChild(menu,2);

	this->scheduleUpdate();

	//audio

	audioid = AudioEngine::play2d("Kalimba.mp3");
	AudioEngine::setFinishCallback(audioid, CC_CALLBACK_2(HelloWorld::finishCallBack, this));


    return true;
}

bool toggle = false;
void HelloWorld::menuCloseCallback(Ref* pSender)
{
	auto sprite2 = Sprite::create("Fart.png");

	// position the sprite on the center of the screen
	sprite2->setAnchorPoint(Point(0, 0.5));
	sprite2->setPosition(Point(240, 160));
	sprite2->setScale(0.1f);

	// add the sprite as a child to this layer
	this->addChild(sprite2, 1);

	ScaleTo *pAction1 = ScaleTo::create(1.5f, 1.0f);
	DelayTime *pAction2 = DelayTime::create(1.2f);
	FadeTo *pAction3 = FadeTo::create(0.3f, 0);
	TintTo *pColorAction = TintTo::create(1.5f, 255, 186, 0);
	Sequence *pSeq = Sequence::create(pAction2, pAction3, NULL);


	Spawn *pSpawn = Spawn::create(pAction1, pSeq, pColorAction, NULL);

	sprite2->runAction(pSpawn);

	Rect rect = Rect(160, 100, 320, 220);
	for (const auto &child : this->getChildren())
	{
		if (child->getTag() == 10) 
		{
			
			if (rect.containsPoint(child->getPosition()))
			{	
				// 지정된 영역에 포인트가 포함되어 있는 경우
				log("%f = %f", child->getPositionX(), child->getPositionY());
				this->removeChild(child, true);
				break;
			}
		}
	}

	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::update(float delta){

	long nowTime = utils::getTimeInMilliseconds();

	long seconds = nowTime - ldLastMosquitoAppear;

	//log("%i = %ld - %ld ", seconds, ldLastMosquitoAppear, nowTime);
	if (seconds > 500 && cocos2d::RandomHelper::random_int(1, 2) == 1) {
		createMosquito();
		ldLastMosquitoAppear = utils::getTimeInMilliseconds();
	}
}

void  HelloWorld::createMosquito(){

	auto pMosquito = Sprite::create("mosquito.png");
	pMosquito->setTag(10);
	int xpos1 = cocos2d::RandomHelper::random_int(0, 160);
	int xpos2 = cocos2d::RandomHelper::random_int(320, 480);


	int ypos1 = cocos2d::RandomHelper::random_int(0, 100);
	int ypos2 = cocos2d::RandomHelper::random_int(220, 320);

	int xpos = 0, ypos = 0;

	if (cocos2d::RandomHelper::random_int(1, 2) == 1) {
		xpos = xpos1;
		pMosquito->setFlipX(true);
	}
	else {
		xpos = xpos2;
	}
	if (cocos2d::RandomHelper::random_int(1, 2) == 1) {
		ypos = ypos1;
	}
	else{
		ypos = ypos2;
	}

	pMosquito->setPosition(Point(xpos, ypos));

	int iMoquitoActionTime = cocos2d::RandomHelper::random_int(2, 4);

	DelayTime *pMosquitoDutation = DelayTime::create(1.0f);
	ScaleTo *pMosquitoActionScale = ScaleTo::create((float)iMoquitoActionTime, 0.3f);
	MoveTo *pMosquitoActionMove = MoveTo::create((float)iMoquitoActionTime, Point(240.0f, 160.0f));
	//RemoveSelf *actionRemove = RemoveSelf::create();

	auto cbSound = CallFuncN::create(CC_CALLBACK_1(HelloWorld::mosquitoCallBack, this));

	Spawn *pMosquitoSpawnAction = Spawn::create(pMosquitoActionScale, pMosquitoActionMove, NULL);

	Sequence *pMosquitoSequenceAction = Sequence::create(pMosquitoDutation, pMosquitoSpawnAction, cbSound, NULL);// 
	

	pMosquito->runAction(pMosquitoSequenceAction);

	this->addChild(pMosquito, 10);

}


void HelloWorld::stopscene(float f) 
{

	Director::getInstance()->pause();   //화면 정지

}

void HelloWorld::onEnter(){
	Layer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	log("hehe");

	// 터치리스너의 우선순위를 (노드가) 화면에 그려진 순서대로 한다.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	ldLastMosquitoAppear = utils::getTimeInMilliseconds();
	
}

void HelloWorld::onTouchEnded(Touch* touch, Event* unused_event){

	CCPoint touchedPoint3 = touch->getLocation();
	auto chickAction1 = MoveTo::create(1, touchedPoint3);
	Chick->runAction(chickAction1);
	return;

		CCPoint touchedPoint2 = touch->getLocation();
		particleTest->setPosition(touchedPoint2);
	return;
	CCPoint touchedPoint = touch->getLocation();
	touchedPoint = convertToNodeSpace(touchedPoint);

	Point playersPos = Chick->getPosition();
	CCPoint diff = touchedPoint - playersPos;

	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playersPos.x += _tileMap->getTileSize().width;
		}
		else {
			playersPos.x -= _tileMap->getTileSize().width;
		}
	}
	else {
		if (diff.y > 0) {
			playersPos.y += _tileMap->getTileSize().height;
		}
		else {
			playersPos.y -= _tileMap->getTileSize().height;
		}
	}

	// safety check on the bounds of the map
	if (playersPos.x <= (_tileMap->getMapSize().width * _tileMap->getTileSize().width) &&
		playersPos.y <= (_tileMap->getMapSize().height * _tileMap->getTileSize().height) &&
		playersPos.y >= 0 &&
		playersPos.x >= 0)
	{
	//	Chick->setPosition(playersPos);
		int x = playersPos.x / _tileMap->getTileSize().width;
		int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - playersPos.y) / _tileMap->getTileSize().height;

		int tileGid = redblue->tileGIDAt(Point(x,y));
		if (tileGid) {
			Value& properties = _tileMap->propertiesForGID(tileGid);
			if (!properties.isNull()) {
				ValueMap map = properties.asValueMap();
				bool isRunnable = map.at("isRunnable").asBool();
				if (isRunnable == true) {
					auto chickAction = MoveTo::create(0.3, playersPos);
					Chick->runAction(chickAction);
				}
			}
		}
	}
	this->setViewPointCenter(Chick->getPosition());
}
bool HelloWorld::onTouchBegan(Touch* touch, Event* unused_event){
	return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* unused_event){
	return;

}

void HelloWorld::setViewPointCenter(Point position) {

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	CCPoint actualPosition = ccp(x, y);

	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	this->setPosition(viewPoint);
}



void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

}


void HelloWorld::finishCallBack(int audioID, std::string filePath)
{
	log("sound end");


}



void HelloWorld::mosquitoCallBack(Ref* pSender)
{
	auto label3 = Label::create("Exit", "Arial", 250);

	auto menuFont3 = MenuItemLabel::create(label3, [](Ref* pSender2){

		Director::getInstance()->end();
	});

	auto menu = Menu::create(menuFont3, NULL);
	menu->alignItemsVertically();

	Node *nd = (Node*)(pSender);
	nd->getParent()->getParent()->addChild(menu);

	log("%s", typeid(*nd).name());
	Director::getInstance()->pause();


	
}