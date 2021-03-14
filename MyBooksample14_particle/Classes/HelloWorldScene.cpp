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
    // 1. super init first
    if ( !Layer::init() )
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
    
    label = Label::createWithTTF("Score", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);



	ParticleSystemQuad* blackhole = ParticleSystemQuad::create("blackhole2.plist");
	//auto texture = Director::getInstance()->getTextureCache()->addImage("fire.png");
	//particleTest->setTexture(texture);
	blackhole->setScale(0.5);
	blackhole->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));


	this->addChild(blackhole);
    // add "HelloWorld" splash screen"
	pSprite = Sprite::create("ship.png");
	pSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, 100));
	pSprite->setAnchorPoint(Point(0.5f, 0.5f));
	this->addChild(pSprite, 0);



	particleTest = ParticleSystemQuad::create("particle_texture.plist");
	//auto texture = Director::getInstance()->getTextureCache()->addImage("fire.png");
	//particleTest->setTexture(texture);
	//particleTest->setScale(1);
	particleTest->setPosition(Point(pSprite->getContentSize().width / 2, 0));

	pSprite->addChild(particleTest);



	this->schedule(schedule_selector(HelloWorld::wakefire), 0.5f);
	this->schedule(schedule_selector(HelloWorld::zoompa), 0.3f);
	this->scheduleUpdate();


	Vec2 an = ccpRotateByAngle(Vec2(150, 0), Vec2(0, 0), CC_DEGREES_TO_RADIANS(270));
	an = an + Vec2(240, 160);
	pSprite->setPosition(an);

    return true;
}
void HelloWorld::zoompa(float dt)
{
	/*ParticleSystemQuad* particle = ParticleSystemQuad::create("zoompa.plist");

	particle->setPosition(240, 160);

	particle->setScale(1);
	particle->setOpacity(0.3f);
	//this->addChild(particle, 10);*/
}
void HelloWorld::wakefire(float dt)
{

	angle = random(0, 360);

	Vec2 an = ccpRotateByAngle(Vec2(700, 0), Vec2(0, 0), CC_DEGREES_TO_RADIANS(angle));
	an = an + Vec2(240, 160);
	float dtime = (float)random(2, 5);


	auto *scaleAndMoveTO = Spawn::create(ScaleTo::create(dtime, 2.0f), MoveTo::create(dtime, an), NULL);
	EaseIn *action_1 = EaseIn::create(scaleAndMoveTO, 4.0);    // action, 탄성

	auto *seq = Sequence::create(
		CCDelayTime::create(0.5f),
		Place::create(Vec2(240, 160)),
		action_1,
		RemoveSelf::create(),
		NULL);


	int randomSun = random(1, 7);
	if (randomSun == 3 || randomSun == 7) {

		Sprite *spSprite = Sprite::create("stars2.png");
		spSprite->setScale(0.0f);
		spSprite->setPosition(240, 160);
		spSprite->setAnchorPoint(Point(0.5f, 0.5f));
		spSprite->setTag(100);
		this->addChild(spSprite, 0);

		spSprite->runAction(seq);

		return;

	}

	ParticleSystemQuad* particle = ParticleSystemQuad::create("enermy.plist");

	/*
	particle->setAngle(270);                            // 각도
	particle->setDuration(10);                      // 발생시간
	particle->setGravity(Point(0, 0));      // 중력값(x, y는 위치가 아닌 중력치)
	particle->setLife(100);                           // 지속시간
	particle->setSpeed(200);                       // 속도
	particle->setScale(1);                           // 크기
	
	particle->setTexture(TextureCache::getInstance()->addImage("snow.png"));
	*/
	particle->setPosition(240, 160);

	particle->setScale(0);
	particle->setAngle(angle - 180);
	particle->setTag(101);
	this->addChild(particle, 10);

	//angle += 10;



	particle->runAction(seq);

}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
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
	_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);


}

void HelloWorld::update(float dt)
{

	//collision
	//collision
	//collision

	Vector<Node*> allNodes = this->getChildren();
	for (auto& node : allNodes)
	{
		if (dynamic_cast<Sprite*>(node))
		{ //It is Sprite 
			Sprite *target = dynamic_cast<Sprite*>(node);
			//Do whatever you like
			if (target->getTag() == 100 && pSprite->getBoundingBox().containsPoint(target->getPosition()) == true)
			{
				target->removeFromParentAndCleanup(true);

				score++;
				label->setString(StringUtils::format("SCORE :%d", score));
				log("collision");
			}//if

		}//if

		if (dynamic_cast<ParticleSystemQuad*>(node))
		{ //It is Sprite 

			//if (explodeParticle != 0) return;

			ParticleSystemQuad *parttarget = dynamic_cast<ParticleSystemQuad*>(node);
			if (parttarget->getTag() == 101 && pSprite->getBoundingBox().containsPoint(parttarget->getPosition()) == true)
			{
				if (isExploding) return;
				isExploding = true;
				explodeParticle = ParticleSystemQuad::create("explode.plist");

				explodeParticle->setPosition(pSprite->getPosition());

				auto callfunc0 = CallFunc::create([&](){
					isExploding = false;

				});

				explodeParticle->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), callfunc0, NULL));
				

				this->addChild(explodeParticle, 10);


				score--;
				if (score == 0) score = 0;
				label->setString(StringUtils::format("SCORE :%d", score));


				auto actionBlink = Blink::create(2, 5);
				pSprite->runAction(actionBlink);

				return;
				//parttarget->removeFromParentAndCleanup(true);
				log("explode");
			}
		}
		
		
	}//for

	//particle
	//particle
	//particle

	if (touchBeginPoint == Vec2::ZERO) return;

	if (touchBeginPoint.x > 240) {
		log("%f %f", touchBeginPoint.x, touchBeginPoint.x);
		//오른쪽회전
		// calculate Angle and length
		spriteAngle += 2;
		if (spriteAngle == 360) {
			spriteAngle = 0;
		}

	}
	else {
		spriteAngle -= 2;
		if (spriteAngle == 0) {
			spriteAngle = 360;
		}

	}
	Vec2 an = ccpRotateByAngle(Vec2(150, 0), Vec2(0, 0), CC_DEGREES_TO_RADIANS(spriteAngle));
	an = an + Vec2(240, 160);
	pSprite->setPosition(an);
	pSprite->setRotation( -1* (spriteAngle - 270));
	log("%f %f %d", touchBeginPoint.x, touchBeginPoint.x, spriteAngle);

}


bool HelloWorld::onTouchBegan(Touch* touch, Event* unused_event)
{

	Vec2 touchPoint;
	Point globalPoint;


	touchBeginPoint = touch->getLocation();
	pTouchedSprite = pSprite;

	return true;
}



void HelloWorld::onTouchMoved(Touch* touch, Event* unused_event)
{
	Vec2 touchPoint;

	
	touchPoint = touch->getLocation();
	touchBeginPoint = touch->getLocation();


}


void HelloWorld::onTouchCancelled(Touch* touch, Event* unused_event)
{
		log("onTouchCancelled");
}

void HelloWorld::onTouchEnded(Touch* touch, Event* unused_event)
{
		log("onTouchEnded");

	log("onTouchEnded");


	Vec2 touchPoint;
	

	touchBeginPoint = Vec2::ZERO;
	pTouchedSprite = 0;
}