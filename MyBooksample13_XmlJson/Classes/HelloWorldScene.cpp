#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#define CC_DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) * 0.01745329252f) // PI / 180

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
    /**  you can create scene with following comment code instead of using csb file.
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
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    **/
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();



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




	ball = Sprite::create("ball.png"); // is used for userdata which is used for simulation
	ball->setPosition(ccp(100, 100));
	ball->setTag(1);
	ball->setScale(0.7f);
	this->addChild(ball);





	//"http://openapi.tago.go.kr/openapi/service/ArvlInfoInqireService/getSttnAcctoSpcifyRouteBusArvlPrearngeInfoList?ServiceKey=BDKyR2AfTf2dlJ7l1LxFY4qZZlaLEFj7o35IC5Awh10vR79uXle2wxHuDTm2KrUyn0fOMWzn1UOBNtvR7SR3UA%3D%3D&cityCode=25&routeId=DJB30300038ND&nodeId=DJB8001169ND&numOfRows=999&pageSize=999&pageNo=1&startPage=1"
	
	
	/*HttpRequest* request = new HttpRequest();
	request->setRequestType(HttpRequest::Type::GET);
	request->setUrl();
	bool isNetWork = false;
	request->setResponseCallback([=](HttpClient* client, HttpResponse* response)
	{

		if (!response || !response->isSucceed())
		{
			// No internet connection

			CCLOG("No internet connection");
		}
		else
		{
			// Internet available

			CCLOG("Internet connection available %d", response->getResponseCode());

			std::vector<char>* buffer = response->getResponseData();
		

			CCLOG("Ibuffere %s", buffer);

		}
	});
	request->setTag("Get test");
	HttpClient::getInstance()->send(request);

	request->release();*/
	
	//this->getXmlValue("http://openapi.tago.go.kr/openapi/service/ArvlInfoInqireService/getSttnAcctoSpcifyRouteBusArvlPrearngeInfoList?ServiceKey=BDKyR2AfTf2dlJ7l1LxFY4qZZlaLEFj7o35IC5Awh10vR79uXle2wxHuDTm2KrUyn0fOMWzn1UOBNtvR7SR3UA%3D%3D&cityCode=25&routeId=DJB30300038ND&nodeId=DJB8001169ND&numOfRows=999&pageSize=999&pageNo=1&startPage=1");//("http://zetawiki.com/ex/php/quiz.xml");



	//중력벡터를 실행한다.
	b2Vec2 gravity = b2Vec2(0.0f, 0.0f);

	//박스투디 월드를 만든다.
	world = new b2World(gravity);
	//SetAllowSleeping = true 는 월드가 rest 상태이면 body 들을 멈추게 할건지 지정.
	world->SetAllowSleeping(false);
	world->SetContinuousPhysics(true);



	//디버그데이터를 그린다
	world->DrawDebugData();

	m_debugDraw = new GLESDebugDraw(PT_RATIO);
	world->SetDebugDraw(m_debugDraw);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_centerOfMassBit;
	m_debugDraw->SetFlags(flags);

	//이제 물이세상이 시작된다.

	this->defineBall();

	this->addWall(100, 10, (visibleSize.width / 2), visibleSize.height /2); //화면상단 밑이 0 상단이 height
	/*this->addWall(visibleSize.width, 10, (visibleSize.width / 2), 0); //하단 0,0
	this->addWall(10, visibleSize.height, 0, (visibleSize.height / 2)); //LEFT
	this->addWall(10, visibleSize.height, visibleSize.width, (visibleSize.height / 2)); //RIGHT*/


	this->scheduleUpdate();
    return true;
}


void HelloWorld::getXmlValue(const char* url)
{
	HttpRequest *request = new HttpRequest();
	request->setUrl(url);
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(CC_CALLBACK_2(HelloWorld::loadXml, this));
	HttpClient::getInstance()->send(request);
	request->release();
}

void HelloWorld::loadXml(HttpClient *sender, HttpResponse *response)
{
	if (!response->isSucceed())
	{
		return;
	}

	std::vector<char>* buffer = response->getResponseData();
	std::string _xml = std::string(buffer->begin(), buffer->end());

	tinyxml2::XMLDocument doc;
	if (doc.Parse(_xml.c_str()) == XML_NO_ERROR)
	{
		 XMLElement *test = doc.FirstChildElement();
		 XMLElement *bodyElement = test->FirstChildElement("body");
		 XMLElement *itemsElement = bodyElement->FirstChildElement("items");
		 XMLElement *childElement = itemsElement->FirstChildElement("item");

				tinyxml2::XMLElement* element_id = childElement->FirstChildElement("arrprevstationcnt");
				log("id:%s", element_id->GetText());
				tinyxml2::XMLElement* element_reach = childElement->FirstChildElement("arrtime");
				log("reach:%s", element_reach->GetText());
				tinyxml2::XMLElement* element_power = childElement->FirstChildElement("routeno");
				log("power:%s", element_power->GetText());
				tinyxml2::XMLElement* element_target = childElement->FirstChildElement("routetp");
				log("target:%s", element_target->GetText());
				
			

				auto sprite = Sprite::create("train.png");
				sprite->setPosition(Vec2(-100,60));
				this->addChild(sprite, 0);
				auto *pMoveto = MoveTo::create((float)std::stoi(element_reach->GetText()) / 100.0f, Vec2(580, 60));
				sprite->runAction(pMoveto);
			
		
	}
}



//--box2d

//벽생성
void HelloWorld::addWall(float w, float h, float px, float py) {

	log(" %f %f %f %f ", w, h, px, py);

	b2PolygonShape floorShape;

	/*
	SetAsBox 함수는 가로와 세로의 절반값을 변수로 입력 받습니다.
	위의 groundbox의 경우, x축으로 100 , y축으로 20 unit(box2d의 단위)가 됩니다.
	Box2D는 미터, 킬로그램, 초 단위로 설정되어있습니다.
	그래서 여러분은 미터 단위로 크기를 고려해야합니다.
	Box2D는 일반적으로 객체가 실제 세계의 물체 크기를 가질때 제일 잘 동작합니다.
	예를들어, 배럴(통)은 약 1 미터의 높이를 가집니다.
	소숫점 연산의 제한 때문에, box2D로 빙하의 이동이나 먼지 파편의 이동을 구현하는건 좋은 아이디어가 아닙니다.
	*/
	floorShape.SetAsBox(w / SCALE_RATIO, h / SCALE_RATIO);
	

	//fixture : body의 shape(형태), 밀도, 마찰, 복원력 등을 정의한다.
	b2FixtureDef floorFixture;
	floorFixture.density = 10000;
	floorFixture.friction = 0;
	floorFixture.restitution = 1;
	floorFixture.shape = &floorShape;
	
	b2BodyDef floorBodyDef;
	

	floorBodyDef.position.Set(px / SCALE_RATIO, py / SCALE_RATIO);
	floorBodyDef.type = b2_dynamicBody;
	
	b2Body *floorBody = world->CreateBody(&floorBodyDef);

	floorBody->SetTransform(floorBody->GetPosition(), CC_DEGREES_TO_RADIANS(30));

	floorBody->ApplyForce(b2Vec2(0, 0), floorBody->GetWorldCenter(),true);
	floorBody->SetGravityScale(0);


	floorBody->SetLinearDamping(0);
	floorBody->SetAngularDamping(0);

	floorBody->CreateFixture(&floorFixture);

}



void HelloWorld::defineBall(){
	//log("defineBall22");
	ballShape.m_radius = 25 / SCALE_RATIO;
	b2FixtureDef ballFixture;
	ballFixture.density = 10.0; // 밀도 (1 평방 미터 당 무게 (kg))
	ballFixture.friction = 0.0;//마찰 (friction) 마찰력 0 ~ 1
	ballFixture.restitution = 0.6; //반발(restitution) 물체가 다른 물체에 닿았을 때 튕기는 값
	ballFixture.shape = &ballShape;

	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.userData = ball;// ball;

	ballBodyDef.position.Set(240 / SCALE_RATIO, 260 / SCALE_RATIO);

	ballBody = world->CreateBody(&ballBodyDef);
	ballBody->CreateFixture(&ballFixture);
	ballBody->SetGravityScale(10);

	/*
	Damping은 body의 속도를 줄이기 위해 사용된다.
	Damping은 friction(마찰)과는 다른것으로, 마찰은 두body가 접촉했을 때만 일어난다.
	Damping은 friction의 대체용이 아니며, 둘 모두 동시에 사용되어져야 한다. (damping은 보통 공기저항등의 예를 말합니다)
	Damping은 0에서 무한대의 값을 가질 수 있으며, 보통은 0에서 0.1의 값 사이로 지정된다.
	보통은linearDamping의 값은 지정하지 않는데, 왜냐하면 물체가 떠있는 것처럼 보일 수 있기 때문이다. 다음과 같은 두 개의 damping이 존재한다.
	!  bodyDef.linearDamping = 0.0f;
	!  bodyDef.angularDamping = 0.01f;

	*/
	ballBody->SetLinearDamping(1);
	ballBody->SetAngularDamping(1);

	
}


// Simulate Physics
void HelloWorld::update(float dt){
	int positionIterations = 10;
	int velocityIterations = 10;
	
	


	world->Step(dt, velocityIterations, positionIterations);

	for (b2Body *body = world->GetBodyList(); body != NULL; body = body->GetNext())
	if (body->GetUserData())
	{
		Sprite *sprite = (Sprite *)body->GetUserData();
		sprite->setPosition(ccp(body->GetPosition().x * SCALE_RATIO, body->GetPosition().y * SCALE_RATIO));
		sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));


	}
	else{

		//log("nect");
		//body->ApplyForce(body->GetMass() * -world->GetGravity(), body->GetWorldCenter(),true);
		//body->SetTransform(b2Vec2(100, 10), 0);
		//body->ApplyForce(b2Vec2(0, 0), body->GetWorldCenter(), true);
		//body->SetGravityScale(0);
	}


	world->ClearForces();
	world->DrawDebugData();



}

void HelloWorld::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);

	_customCmd.init(_globalZOrder, transform, flags);
	_customCmd.func = CC_CALLBACK_0(HelloWorld::onDraw, this, transform, flags);
	renderer->addCommand(&_customCmd);
}


void HelloWorld::onDraw(const Mat4 &transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	world->DrawDebugData();
	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
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

void HelloWorld::menuCloseCallback(Ref* pSender)
{

	world->SetGravity(b2Vec2(0.0f, -3.0f));
}


bool HelloWorld::onTouchBegan(Touch* touch, Event* unused_event){


	Vec2 location = touch->getLocation();
	//.....

	if (ball->getBoundingBox().containsPoint(location) == true) {
		//world->ApplyLinearImpulse(force, body->GetPosition(), true); //to make it move.

	


		pTouchedSprite = ball;
		log("onTouchBegan");

	}


	return true;

}

void HelloWorld::onTouchMoved(Touch* touch, Event* unused_event){

	Vec2 location = touch->getLocation();
	if (pTouchedSprite) {
		for (b2Body *body = world->GetBodyList(); body != NULL; body = body->GetNext())
		if (body->GetUserData())
		{
			Sprite *sprite = (Sprite *)body->GetUserData();
			if (sprite == pTouchedSprite) {
				b2Vec2 a = b2Vec2(location.x/ SCALE_RATIO, location.y/ SCALE_RATIO);
				//body->ApplyLinearImpulse(a, body->GetPosition(), true); //to make it move.

				body->SetTransform(a, CC_DEGREES_TO_RADIANS(30));
			}



		}

		log("onTouchMoved");
		//pTouchedSprite->setPosition(location);
	}

}

void HelloWorld::onTouchCancelled(Touch* touch, Event* unused_event){
	log("onTouchCancelled");
}

void HelloWorld::onTouchEnded(Touch* touch, Event* unused_event){
	log("onTouchEnded");

	Vec2 location = touch->getLocation();

	if (pTouchedSprite) {
		pTouchedSprite = 0;
	}




}