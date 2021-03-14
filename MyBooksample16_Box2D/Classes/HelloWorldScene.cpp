#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();// ::create();
	PhysicsWorld *world = scene->getPhysicsWorld();
	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	world->setGravity(Vec2(0,-120.0f));
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
   // you can create scene with following comment code instead of using csb file.
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//사방벽 그림
	auto wallBody = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height +30), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	wallBody->setContactTestBitmask(1);

	wall = Node::create();
	wall->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y-15));

	wall->setPhysicsBody(wallBody);
	this->addChild(wall);


	//공
	ball = Sprite::create("CloseNormal.png");
	ball->setPosition(Vec2(950, 500));
	auto physicsBody = PhysicsBody::createCircle(ball->getContentSize().width / 2, PhysicsMaterial(0, 1.3, 0));
	physicsBody->setDynamic(true);
	ball->setPhysicsBody(physicsBody);
	//충돌체크용 
	physicsBody->setContactTestBitmask(true);
	physicsBody->setCollisionBitmask(2);
	//회전
	//physicsBody->setAngularVelocity(10); // 계속증가
	//physicsBody->setAngularDamping(1); //감소정도
	//physicsBody->setAngularVelocityLimit(120); //최대증가

	//이동
	//physicsBody->setVelocity(Vec2(300,27)); // 계속증가
	//physicsBody->setVelocityLimit(500); //감소정도
	//physicsBody->setLinearDamping(0.1); //최대증가
	/*
	//force 포스가 함ㄲ
	physicsBody->applyForce(Vec2(100, 50));

	//Torque 점점 더 빠르게 돌기
	physicsBody->applyTorque(400);

	//iMpuls 충돌?
	physicsBody->applyImpulse(Vec2(400, 700));
	*/
	//

	this->addChild(ball);

	//------------------------------------------------------------------------------------------------------
	//오른쪽 공 나오는 벽, rightBallWall
	//denity  밀도
	//반발계수
	//마찰계수
	auto rightBallWallPhysics = PhysicsBody::createBox(Size(10, 550), PhysicsMaterial(1,0.2,0));
	rightBallWallPhysics->setDynamic(false);
	//physicsBody1->setContactTestBitmask(true);
	rightBallWallPhysics->setCollisionBitmask(2);
	rightBallWallPhysics->setGravityEnable(false);

	Node *rightBallWall = Node::create();
	rightBallWall->setPosition(Vec2(900,300));
	rightBallWall->setPhysicsBody(rightBallWallPhysics);
	this->addChild(rightBallWall);


	

	/*//box2 anchor
	boxAcchor2 = Node::create();
	auto physicsBodyAnchor2 = PhysicsBody::create(PHYSICS_INFINITY, PHYSICS_INFINITY);
	boxAcchor2->setPhysicsBody(physicsBodyAnchor2);
	boxAcchor2->getPhysicsBody()->setDynamic(false);
	this->addChild(boxAcchor2);

	
	auto physicsBodyAnchor2 = PhysicsBody::createBox(Size(50, 50));
	physicsBodyAnchor2->setDynamic(true);
	physicsBodyAnchor2->setContactTestBitmask(1);

	boxAcchor2 = Node::create();
	boxAcchor2->setPosition(box2->getPosition() - Vec2(100,0));
	//boxAcchor2->setRotation(60);
	boxAcchor2->setPhysicsBody(physicsBodyAnchor2);
	this->addChild(boxAcchor2);*/


	//collision
	auto contactLIstener = EventListenerPhysicsContact::create();
	contactLIstener->onContactBegin = [](PhysicsContact& contact){
		
		auto shapeA = contact.getShapeA();
		auto bodyA = shapeA->getBody();

		auto shapeB = contact.getShapeB();
		auto bodyB = shapeB->getBody();
		
		log("A-> %d B-> %d", bodyA->getCollisionBitmask(), bodyB->getCollisionBitmask());
		//Collisionbitmask 가 같아야 충돌로 체크하도록함
		if (bodyA->getCollisionBitmask() != bodyB->getCollisionBitmask()) {
			log("contact begin");
			return true;
			
		}
		return true;
		
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactLIstener, this);

	this->scheduleUpdate();
   
	
    return true;
}

void HelloWorld::onEnter()
{
	Layer::onEnter();


	log("onEnter");
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	_world = Director::getInstance()->getRunningScene()->getPhysicsWorld();


	//--------------------------------------------------------
	//왼쪽 패들
	//--------------------------------------------------------
	Vec2 PaddingPosition = Vec2(200, 75);
	auto physicsBody2 = PhysicsBody::createBox(Size(200, 20),PHYSICSBODY_MATERIAL_DEFAULT);
	physicsBody2->setDynamic(true);
	physicsBody2->setContactTestBitmask(true);
	physicsBody2->setCollisionBitmask(2);
	physicsBody2->setPositionOffset(Vec2(100, 0));
	physicsBody2->setGravityEnable(false);

	box2 = Node::create();
	box2->setPosition(PaddingPosition);
	//box2->setRotation(60);
	//box2->setAnchorPoint(Vec2(0, 0.5f));
	box2->setPhysicsBody(physicsBody2);
	this->addChild(box2);

	//box2 anchor 테스트용
	boxAcchor2 = Node::create();
	auto physicsBodyAnchor2 = PhysicsBody::create(PHYSICS_INFINITY, PHYSICS_INFINITY);
	boxAcchor2->setPhysicsBody(physicsBodyAnchor2);
	boxAcchor2->setPosition(box2->getPosition() );
	boxAcchor2->getPhysicsBody()->setDynamic(false);
	physicsBodyAnchor2->setContactTestBitmask(10);
	physicsBodyAnchor2->setCollisionBitmask(1);
	physicsBodyAnchor2->setGravityEnable(false);
	physicsBodyAnchor2->setDynamic(false);
	this->addChild(boxAcchor2);
	

	//physicsBody2->setAngularDamping(1); //감소정도
	//physicsBody2->setAngularVelocityLimit(120); //최대증가


	auto pivot = PhysicsJointPin::construct(physicsBodyAnchor2, box2->getPhysicsBody(), PaddingPosition);
	//pivot->setMaxForce(5000.0f * physicsBody2->getMass());	
	_world->addJoint(pivot);



	_PaddleHandler = Node::create();

	auto touchBody = PhysicsBody::create(PHYSICS_INFINITY, PHYSICS_INFINITY);
	_PaddleHandler->setPhysicsBody(touchBody);
	_PaddleHandler->setPosition(PaddingPosition + Vec2(200,0));
	touchBody->setGravityEnable(false);
	touchBody->setDynamic(false);
	this->addChild(_PaddleHandler);
	PhysicsJointPin *joint = PhysicsJointPin::construct(touchBody, box2->getPhysicsBody(), PaddingPosition + Vec2(200, 0));

	joint->setMaxForce(5000.0f * box2->getPhysicsBody()->getMass());
	_world->addJoint(joint);

	_PaddleHandler->runAction(MoveBy::create(0, Vec2(0, -50)));


	//--------------------------------------------------------
	//오른쪽  패들
	//--------------------------------------------------------
	Vec2 PaddingPositionRight = Vec2(690, 75);
	auto physicsBody2Right = PhysicsBody::createBox(Size(200, 20), PHYSICSBODY_MATERIAL_DEFAULT);
	physicsBody2Right->setDynamic(true);
	physicsBody2Right->setContactTestBitmask(true);
	physicsBody2Right->setCollisionBitmask(2);
	physicsBody2Right->setPositionOffset(Vec2(-100, 0));
	physicsBody2Right->setGravityEnable(false);

	Node *box2Right = Node::create();
	box2Right->setPosition(PaddingPositionRight);
	//box2->setRotation(60);
	//box2->setAnchorPoint(Vec2(0, 0.5f));
	box2Right->setPhysicsBody(physicsBody2Right);
	this->addChild(box2Right);

	//box2 anchor 테스트용
	Node *boxAcchor2Right = Node::create();
	auto physicsBodyAnchor2Right = PhysicsBody::create(PHYSICS_INFINITY, PHYSICS_INFINITY);
	boxAcchor2Right->setPhysicsBody(physicsBodyAnchor2Right);
	boxAcchor2Right->setPosition(box2Right->getPosition());
	boxAcchor2Right->getPhysicsBody()->setDynamic(false);
	physicsBodyAnchor2Right->setContactTestBitmask(10);
	physicsBodyAnchor2Right->setCollisionBitmask(1);
	physicsBodyAnchor2Right->setGravityEnable(false);
	physicsBodyAnchor2Right->setDynamic(false);
	this->addChild(boxAcchor2Right);


	//physicsBody2->setAngularDamping(1); //감소정도
	//physicsBody2->setAngularVelocityLimit(120); //최대증가


	auto pivotRight = PhysicsJointPin::construct(physicsBodyAnchor2Right, box2Right->getPhysicsBody(), PaddingPositionRight);
	//pivot->setMaxForce(5000.0f * physicsBody2->getMass());	
	_world->addJoint(pivotRight);



	_PaddleHandlerRight = Node::create();

	auto touchBodyRight = PhysicsBody::create(PHYSICS_INFINITY, PHYSICS_INFINITY);
	_PaddleHandlerRight->setPhysicsBody(touchBodyRight);
	_PaddleHandlerRight->setPosition(PaddingPositionRight - Vec2(200, 0));
	touchBodyRight->setGravityEnable(false);
	touchBodyRight->setDynamic(false);
	this->addChild(_PaddleHandlerRight);
	PhysicsJointPin *jointRight = PhysicsJointPin::construct(touchBodyRight, box2Right->getPhysicsBody(), PaddingPositionRight - Vec2(200, 0));

	jointRight->setMaxForce(5000.0f * box2Right->getPhysicsBody()->getMass());
	_world->addJoint(jointRight);

	_PaddleHandlerRight->runAction(MoveBy::create(0, Vec2(0, -50)));










	//--------------------------------------------------------
	//상단 삼각
	//--------------------------------------------------------
	Point spritePointsTopRight[3] =
	{
		Point(0, 0), Point(50, 0), Point(50, -50)
	};

	Node *_TopRightTriAngle = Node::create();
	auto TopRightBody = PhysicsBody::createPolygon(spritePointsTopRight, 3, PhysicsMaterial(1, 0, 1));
	_TopRightTriAngle->setPhysicsBody(TopRightBody);
	_TopRightTriAngle->setPosition(Vec2(908, 638));
	TopRightBody->setGravityEnable(false);
	TopRightBody->setDynamic(false);
	this->addChild(_TopRightTriAngle);

	//box2->setRotation(60);
	//--------------------------------------------------------
	//슈터 스프링
	//--------------------------------------------------------
	Vec2 SooterPosition = Vec2(930, 0);
	auto ShooterphysicsBody0 = PhysicsBody::createBox(Size(45, 20), PHYSICSBODY_MATERIAL_DEFAULT);
	ShooterphysicsBody0->setDynamic(false);
	ShooterphysicsBody0->setContactTestBitmask(true);
	ShooterphysicsBody0->setCollisionBitmask(2);
	ShooterphysicsBody0->setGravityEnable(false);

	Node* _Shooter0 = Node::create(); // 고정체1
	_Shooter0->setPosition(SooterPosition);
	_Shooter0->setPhysicsBody(ShooterphysicsBody0);
	this->addChild(_Shooter0);


	Node *_Shooter = Node::create();
	auto ShootertouchBody = PhysicsBody::createBox(Size(45, 20), PHYSICSBODY_MATERIAL_DEFAULT);
	_Shooter->setPhysicsBody(ShootertouchBody);
	_Shooter->setPosition(SooterPosition + Vec2(0, 100));
	ShootertouchBody->setGravityEnable(false);
	ShootertouchBody->setDynamic(true);
	this->addChild(_Shooter);

	PhysicsJointSpring *spring = PhysicsJointSpring::construct(ShooterphysicsBody0, ShootertouchBody, Vec2::ZERO, Vec2(0, 0), 2000.0f, 100.0f);
	spring->setMaxForce(5000.0f * box2->getPhysicsBody()->getMass());
	_world->addJoint(spring);


	//--------------------------------------------------------
	//왼쪽 삼각
	//--------------------------------------------------------
	Point spritePoints[3] =
	{
		Point(0, 0), Point(0, 40), Point(200, 0)
	};

	Node *_bottomTriAngle = Node::create();
	auto enemyBody = PhysicsBody::createPolygon(spritePoints, 3, PhysicsMaterial(1, 0, 1));
	_bottomTriAngle->setPhysicsBody(enemyBody);
	_bottomTriAngle->setPosition(Vec2(0, 0));
	enemyBody->setGravityEnable(false);
	enemyBody->setDynamic(false);
	this->addChild(_bottomTriAngle);


	//--------------------------------------------------------
	//왼쪽 사각 중간
	//--------------------------------------------------------
	Point spritePointsTemp2[4] =
	{
		Point(0, 0), Point(0, 120), Point(40, 80), Point(40, 40)
	};

	Node *_bottomTriAngleTemp2 = Node::create();
	auto enemyBodyTemp2 = PhysicsBody::createPolygon(spritePointsTemp2, 4, PhysicsMaterial(1, 0, 1));
	_bottomTriAngleTemp2->setPhysicsBody(enemyBodyTemp2);
	_bottomTriAngleTemp2->setPosition(Vec2(0, 300));
	enemyBodyTemp2->setGravityEnable(false);
	enemyBodyTemp2->setDynamic(false);
	this->addChild(_bottomTriAngleTemp2);




	//--------------------------------------------------------
	//왼쪽 패들 옆 몸통
	//--------------------------------------------------------
	Point spritePointsRightBlock[5] =
	{
		Point(0, 0), Point(0, 145), Point(40, 170), Point(140, 0), Point(140, -40)
	};

	Node *_RightBlock = Node::create();
	auto RightBlockBody = PhysicsBody::createPolygon(spritePointsRightBlock, 5, PhysicsMaterial(1, 0.1f, 0.1f));
	_RightBlock->setPhysicsBody(RightBlockBody);
	_RightBlock->setPosition(Vec2(55, 90));
	RightBlockBody->setGravityEnable(false);
	RightBlockBody->setDynamic(false);
	this->addChild(_RightBlock);




	//--------------------------------------------------------
	//오른쪽 삼각
	//--------------------------------------------------------
	Point spritePoints2[3] =
	{
		Point(0, 0), Point(200, 40), Point(200, 0)
	};

	Node *_bottomTriAngle2 = Node::create();
	auto enemyBody2 = PhysicsBody::createPolygon(spritePoints2, 3, PhysicsMaterial(1, 0, 1));
	_bottomTriAngle2->setPhysicsBody(enemyBody2);
	_bottomTriAngle2->setPosition(Vec2(690, 0)); // 왼쪽 슈터라인이 70 = 960 - 270
	enemyBody2->setGravityEnable(false);
	enemyBody2->setDynamic(false);
	this->addChild(_bottomTriAngle2);

	//--------------------------------------------------------
	//오른쪽 사각 중간
	//--------------------------------------------------------
	Point spritePointsTemp3[4] =
	{
		Point(0, 0), Point(0, 40), Point(40, 80), Point(40, -40)
	};

	Node *_bottomTriAngleTemp3 = Node::create();
	auto enemyBodyTemp3 = PhysicsBody::createPolygon(spritePointsTemp3, 4, PhysicsMaterial(1, 0, 1));
	_bottomTriAngleTemp3->setPhysicsBody(enemyBodyTemp3);
	_bottomTriAngleTemp3->setPosition(Vec2(850, 340));//960 - 70 -
	enemyBodyTemp3->setGravityEnable(false);
	enemyBodyTemp3->setDynamic(false);
	this->addChild(_bottomTriAngleTemp3);


	//--------------------------------------------------------
	//오른쪽 패들 옆 몸통
	//--------------------------------------------------------
	Point spritePointsRightBlock2[5] =
	{
		Point(0, 0), Point(100, 170), Point(145, 145), Point(145, 0), Point(0,-40)
	};

	Node *_RightBlock2 = Node::create();
	auto RightBlockBody2 = PhysicsBody::createPolygon(spritePointsRightBlock2, 5, PhysicsMaterial(1, 0.1f, 0.1f));
	_RightBlock2->setPhysicsBody(RightBlockBody2);
	_RightBlock2->setPosition(Vec2(700, 90));
	RightBlockBody2->setGravityEnable(false);
	RightBlockBody2->setDynamic(false);
	this->addChild(_RightBlock2);


	//--------------------------------------------------------
	//튀김공
	//--------------------------------------------------------


	//공
	Node *_BoundCircle = Node::create();
	_BoundCircle->setPosition(Vec2(270 , 370));
	auto physicsBodyCircle = PhysicsBody::createCircle(70, PhysicsMaterial(1, 1.3, 0));
	physicsBodyCircle->setDynamic(false);
	_BoundCircle->setPhysicsBody(physicsBodyCircle);
	//충돌체크용 
	physicsBodyCircle->setContactTestBitmask(true);
	physicsBodyCircle->setCollisionBitmask(2);
	this->addChild(_BoundCircle);

	//공2
	Node *_BoundCircle2 = Node::create();
	_BoundCircle2->setPosition(Vec2(130, 520));
	auto physicsBodyCircle2 = PhysicsBody::createCircle(70, PhysicsMaterial(1, 1.3, 0));
	physicsBodyCircle2->setDynamic(false);
	_BoundCircle2->setPhysicsBody(physicsBodyCircle2);
	//충돌체크용 
	physicsBodyCircle2->setContactTestBitmask(true);
	physicsBodyCircle2->setCollisionBitmask(2);
	this->addChild(_BoundCircle2);


	//공3
	Node *_BoundCircle3 = Node::create();
	_BoundCircle3->setPosition(Vec2(770, 470));
	auto physicsBodyCircle3 = PhysicsBody::createCircle(70, PhysicsMaterial(1, 1.3, 0));
	physicsBodyCircle3->setDynamic(false);
	_BoundCircle3->setPhysicsBody(physicsBodyCircle3);
	//충돌체크용 
	physicsBodyCircle3->setContactTestBitmask(true);
	physicsBodyCircle3->setCollisionBitmask(2);
	this->addChild(_BoundCircle3);

	//------------------------------------------------------------------------------------------------------



	//--------------------------------------------------------
	//회전막대
	//--------------------------------------------------------
	Vec2 PaddingPositionRotater = Vec2(530, 450);
	auto physicsBody2Rotater = PhysicsBody::createBox(Size(150, 20), PHYSICSBODY_MATERIAL_DEFAULT);
	physicsBody2Rotater->setDynamic(true);
	physicsBody2Rotater->setContactTestBitmask(true);
	physicsBody2Rotater->setCollisionBitmask(2);
	physicsBody2Rotater->setGravityEnable(false);
	physicsBody2Rotater->setAngularDamping(0.2f); //감소정도

	Node *box2Rotater = Node::create();
	box2Rotater->setPosition(PaddingPositionRotater);
	//box2->setRotation(60);
	//box2->setAnchorPoint(Vec2(0, 0.5f));
	box2Rotater->setPhysicsBody(physicsBody2Rotater);
	this->addChild(box2Rotater);



	Node *_box2RotaterPivot = Node::create();

	auto touchBodyRotaterPivot = PhysicsBody::create(PHYSICS_INFINITY, PHYSICS_INFINITY);
	_box2RotaterPivot->setPhysicsBody(touchBodyRotaterPivot);
	_box2RotaterPivot->setPosition(PaddingPositionRight);
	touchBodyRotaterPivot->setGravityEnable(false);
	touchBodyRotaterPivot->setDynamic(false);
	this->addChild(_box2RotaterPivot);


	auto pivotRightRotater = PhysicsJointPin::construct(touchBodyRotaterPivot, physicsBody2Rotater, PaddingPositionRotater);
	//pivot->setMaxForce(5000.0f * physicsBody2->getMass());	
	_world->addJoint(pivotRightRotater);


}


void HelloWorld::update(float delta)
{
	log("%f", box2->getRotation());
	if (bLeftArm) {
	//	box2->setRotation(box2->getRotation() + 10);
			//boxAcchor3->setRotation(boxAcchor3->getRotation() + 5);
	}
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{

	auto *PaddleOn = Sequence::create(
		MoveTo::create(0.1f, Vec2(200, 75) + Vec2(200,50)),
		DelayTime::create(0.2f),
		MoveTo::create(0.1f, Vec2(200, 75) + Vec2(200, -50)),
		NULL);
	_PaddleHandler->runAction(PaddleOn);


	auto *PaddleOn2 = Sequence::create(
		MoveTo::create(0.1f, Vec2(690, 75) - Vec2(200, -50)),
		DelayTime::create(0.2f),
		MoveTo::create(0.1f, Vec2(690, 75) - Vec2(200, +50)),
		NULL);
	_PaddleHandlerRight->runAction(PaddleOn2);


	bLeftArm = true;
	log("touched onTouchBegan");
	Point location = touch->getLocation();

	auto shapes = _world->getShapes(location);

	log("shapes.size() %d", shapes.size());
	if (shapes.size() <= 0) return false;

	PhysicsShape* shape = shapes.front();
	PhysicsBody* body = shape->getBody();
	if (body != nullptr){
		
		_touchNode = Node::create();
		
		this->addChild(_touchNode);
		auto touchBody = PhysicsBody::create(PHYSICS_INFINITY, PHYSICS_INFINITY);
		_touchNode->setPhysicsBody(touchBody);
		_touchNode->getPhysicsBody()->setDynamic(false);
		_touchNode->setPosition(location);
		PhysicsJointPin *joint = PhysicsJointPin::construct(touchBody, body, location);

		joint->setMaxForce(5000.0f * body->getMass());
		_world->addJoint(joint);
		return true;

	}
	
	return false;
}

void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	
	//log("touched onTouchMoved");
	if (_touchNode != nullptr)
	{
		//_PaddleHandler->setPosition(touch->getLocation());
		_touchNode->setPosition(touch->getLocation());
		//boxAcchor2->setPosition(touch->getLocation());
		//ball->setPosition(touch->getLocation());
	}
}

void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	
	log("touched onTouchEnded");
	if (_touchNode != nullptr)
	{
		_touchNode->removeFromParent();
		_touchNode = nullptr;
	}
}
void HelloWorld::onTouchCancelled(Touch* touch, Event* unused_event){
	log("onTouchCancelled");
}