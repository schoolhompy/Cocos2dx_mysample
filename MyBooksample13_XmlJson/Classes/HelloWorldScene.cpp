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



	//�߷º��͸� �����Ѵ�.
	b2Vec2 gravity = b2Vec2(0.0f, 0.0f);

	//�ڽ����� ���带 �����.
	world = new b2World(gravity);
	//SetAllowSleeping = true �� ���尡 rest �����̸� body ���� ���߰� �Ұ��� ����.
	world->SetAllowSleeping(false);
	world->SetContinuousPhysics(true);



	//����׵����͸� �׸���
	world->DrawDebugData();

	m_debugDraw = new GLESDebugDraw(PT_RATIO);
	world->SetDebugDraw(m_debugDraw);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_centerOfMassBit;
	m_debugDraw->SetFlags(flags);

	//���� ���̼����� ���۵ȴ�.

	this->defineBall();

	this->addWall(100, 10, (visibleSize.width / 2), visibleSize.height /2); //ȭ���� ���� 0 ����� height
	/*this->addWall(visibleSize.width, 10, (visibleSize.width / 2), 0); //�ϴ� 0,0
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

//������
void HelloWorld::addWall(float w, float h, float px, float py) {

	log(" %f %f %f %f ", w, h, px, py);

	b2PolygonShape floorShape;

	/*
	SetAsBox �Լ��� ���ο� ������ ���ݰ��� ������ �Է� �޽��ϴ�.
	���� groundbox�� ���, x������ 100 , y������ 20 unit(box2d�� ����)�� �˴ϴ�.
	Box2D�� ����, ų�α׷�, �� ������ �����Ǿ��ֽ��ϴ�.
	�׷��� �������� ���� ������ ũ�⸦ ����ؾ��մϴ�.
	Box2D�� �Ϲ������� ��ü�� ���� ������ ��ü ũ�⸦ ������ ���� �� �����մϴ�.
	�������, �跲(��)�� �� 1 ������ ���̸� �����ϴ�.
	�Ҽ��� ������ ���� ������, box2D�� ������ �̵��̳� ���� ������ �̵��� �����ϴ°� ���� ���̵� �ƴմϴ�.
	*/
	floorShape.SetAsBox(w / SCALE_RATIO, h / SCALE_RATIO);
	

	//fixture : body�� shape(����), �е�, ����, ������ ���� �����Ѵ�.
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
	ballFixture.density = 10.0; // �е� (1 ��� ���� �� ���� (kg))
	ballFixture.friction = 0.0;//���� (friction) ������ 0 ~ 1
	ballFixture.restitution = 0.6; //�ݹ�(restitution) ��ü�� �ٸ� ��ü�� ����� �� ƨ��� ��
	ballFixture.shape = &ballShape;

	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.userData = ball;// ball;

	ballBodyDef.position.Set(240 / SCALE_RATIO, 260 / SCALE_RATIO);

	ballBody = world->CreateBody(&ballBodyDef);
	ballBody->CreateFixture(&ballFixture);
	ballBody->SetGravityScale(10);

	/*
	Damping�� body�� �ӵ��� ���̱� ���� ���ȴ�.
	Damping�� friction(����)���� �ٸ�������, ������ ��body�� �������� ���� �Ͼ��.
	Damping�� friction�� ��ü���� �ƴϸ�, �� ��� ���ÿ� ���Ǿ����� �Ѵ�. (damping�� ���� �������׵��� ���� ���մϴ�)
	Damping�� 0���� ���Ѵ��� ���� ���� �� ������, ������ 0���� 0.1�� �� ���̷� �����ȴ�.
	������linearDamping�� ���� �������� �ʴµ�, �ֳ��ϸ� ��ü�� ���ִ� ��ó�� ���� �� �ֱ� �����̴�. ������ ���� �� ���� damping�� �����Ѵ�.
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

	// �ڵ鸵�� ��ġ �̺�Ʈ�� ��ġ �̺�Ʈ array���� ����ڴٴ� �ǹ��̴�.
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	// ��ġ�������� �켱������ (��尡) ȭ�鿡 �׷��� ������� �Ѵ�.
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