#include "GameMainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include <iostream>
#include "sqlite3.h"
#include <sqlite3\include\sqlite3.h>

#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"



USING_NS_CC;

using namespace cocostudio::timeline;

int GameMain::visitCount = 0;
std::string GameMain::a = "";

Scene* GameMain::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameMain::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameMain::init()
{

	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	//--sqlite3
	DBpath = FileUtils::getInstance()->getWritablePath() + "cocossave.db3";

	log("FileUtils::getInstance()->getWritablePath()%s", FileUtils::getInstance()->getWritablePath().c_str());

	std::string sql;
	int result;
	//result = sqlite3_open_v2(path.c_str(), &pdb, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
	result = sqlite3_open(DBpath.c_str(), &pdb);
	if (result != SQLITE_OK) {
		log("open database failed,  number%d", result);

	}
		

	char* error = NULL;
	auto create_sql = "create table user(body varchar(10) primary key NOT NULL DEFAULT 'man' , face varchar(10), cloth varchar(10))";
	result = sqlite3_exec(pdb, create_sql, NULL, NULL, &error);
	if (result != SQLITE_OK) log("error %s", error);



	auto insert_sql = "insert into user values('man', '', '')";
	result = sqlite3_exec(pdb, insert_sql, NULL, NULL, &error);
	if (result != SQLITE_OK) log("error %s", error);

	insert_sql = "insert into user values('woman', '', '')";
	result = sqlite3_exec(pdb, insert_sql, NULL, NULL, &error);

	if (result != SQLITE_OK) log("error %s", error);


	sqlite3_close(pdb);


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameMain::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...


	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("background.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	
		 a = UserDefault::getInstance()->getStringForKey("username");
		

		visitCount = UserDefault::getInstance()->getIntegerForKey("visitcount");
		log("%d", visitCount);



			editBoxLayer = Layer::create();
			editBoxLayer->setPosition(Vec2(240,160));
			this->addChild(editBoxLayer, 100);
			editBoxLayer->setVisible(false);

			//http://hyreno.blogspot.kr/2013/12/cocos2d-x-editbox.html
			auto editboxForID = EditBox::create(Size(400, 50), Scale9Sprite::create("ninepatchbackground.png", Rect(0, 0, 49, 49), Rect(9, 9, 30, 30)));

			//http://brbranch.jp/blog/201312/cocos2d-x/cocos2dx_ccscale9sprite/
			editboxForID->setPosition(Vec2(0, 0));
			editboxForID->setPlaceHolder("ID : ");                        //처음 보여주는 문자열
			editboxForID->setMaxLength(8);                                //최대로 입력받을수 잇는 문자의 길이
			editboxForID->setPlaceholderFontColor(Color3B::GREEN);        //문자열 색변경
			editboxForID->setFontColor(Color3B::BLUE);                    //입력한 문자열 색변경

			//키보드 오른쪽하단 enter키를 search로 변경
			editboxForID->setReturnType(EditBox::KeyboardReturnType::DONE);
			//키보드를 휴대폰 번호입력모드로 변경
			editboxForID->setInputMode(EditBox::InputMode::ANY);
			editboxForID->setDelegate(this);
			editBoxLayer->addChild(editboxForID);



		

	//menu layer
	Layer *menuLayer = Layer::create();
	menuLayer->setPosition(Vec2(245, 25));
	this->addChild(menuLayer, 1);

	lbHiMessage = Label::createWithTTF("Hi !", "fonts/arial.ttf", 18);// , Size(210, 50), TextHAlignment::LEFT, TextVAlignment::TOP);

	
	this->changeLabel(std::string(GameMain::a).c_str(), GameMain::visitCount);



	lbHiMessage->setPosition(Vec2(0, 270));
	lbHiMessage->setAnchorPoint(Vec2(0, 1));
	menuLayer->addChild(lbHiMessage, 1);

	auto menuSprite0_normal = Sprite::create("menuitemimage0.png");
	auto menuSprite1_normal = Sprite::create("menuitemimage1.png");
	auto menuSprite2_normal = Sprite::create("menuitemimage2.png");
	auto menuSprite3_normal = Sprite::create("menuitemimage3.png");
	auto menuSprite4_normal = Sprite::create("menuitemimage4.png");

	auto menuFont0 = MenuItemSprite::create(menuSprite0_normal, menuSprite0_normal, CC_CALLBACK_1(GameMain::menuCloseCallback, this));
	menuFont0->setTag(10);
	auto menuFont1 = MenuItemSprite::create(menuSprite1_normal, menuSprite1_normal, CC_CALLBACK_1(GameMain::menuCloseCallback, this));
	menuFont1->setTag(11);
	auto menuFont2 = MenuItemSprite::create(menuSprite2_normal, menuSprite2_normal, CC_CALLBACK_1(GameMain::menuCloseCallback, this));
	menuFont2->setTag(12);
	auto menuFont3 = MenuItemSprite::create(menuSprite3_normal, menuSprite3_normal, CC_CALLBACK_1(GameMain::menuCloseCallback, this));
	menuFont3->setTag(13);
	auto menuFont4 = MenuItemSprite::create(menuSprite4_normal, menuSprite4_normal, CC_CALLBACK_1(GameMain::menuCloseCallback, this));
	menuFont4->setTag(14);

	auto menuSp = Menu::create(menuFont0, menuFont1, menuFont2, menuFont3, menuFont4, NULL);
	//menuSp->setAnchorPoint(Vec2(0, 0.5f));

	menuSp->setPosition(Vec2(100,110));
	log("widht %d", (menuSp->getContentSize().width / 2));
	menuSp->alignItemsVertically();

	menuLayer->addChild(menuSp);


	//layer man
	manLayer = Layer::create();
	manLayer->setPosition(Vec2(0, 0));
	manLayer->setAnchorPoint(Vec2(0, 0));
	manLayer->setVisible(false);
	manLayer->setName("man");
	this->addChild(manLayer, 1);


	// add "HelloWorld" splash screen"
	manBody = Sprite::create("man_body.png");
	manBody->setAnchorPoint(Vec2(0, 1));
	manBody->setPosition(Vec2(0, 320));
	manLayer->addChild(manBody, 0);

	auto manCloth = Sprite::create("man_cloth.png");
	manCloth->setAnchorPoint(Vec2(0, 1));
	manCloth->setPosition(Vec2(5, 212));
	manCloth->setName("man_cloth1");
	manBody->addChild(manCloth, 1);


	auto manFace1 = Sprite::create("man_face1.png");
	manFace1->setAnchorPoint(Vec2(0, 1));
	manFace1->setPosition(Vec2(75, 270));
	manFace1->setName("man_face1");
	manBody->addChild(manFace1, 1);

	auto manFace2 = Sprite::create("man_face2.png");
	manFace2->setAnchorPoint(Vec2(0, 1));
	manFace2->setPosition(Vec2(75, 270));
	manFace2->setName("man_face2");
	manBody->addChild(manFace2, 1);


	//--------------

	//layer woman
	womanLayer = Layer::create();
	womanLayer->setPosition(Vec2(0, 0));
	womanLayer->setAnchorPoint(Vec2(0, 0));
	manLayer->setVisible(false);
	womanLayer->setName("woman");
	this->addChild(womanLayer, 1);


	// add "HelloWorld" splash screen"
	womanBody = Sprite::create("woman_body.png");
	womanBody->setAnchorPoint(Vec2(0, 1));
	womanBody->setPosition(Vec2(0, 320));
	womanLayer->addChild(womanBody, 0);

	auto womanCloth = Sprite::create("woman_cloth.png");
	womanCloth->setAnchorPoint(Vec2(0, 1));
	womanCloth->setPosition(Vec2(30, 188));
	womanCloth->setName("woman_cloth1");
	womanBody->addChild(womanCloth, 1);


	auto womanFace1 = Sprite::create("woman_face1.png");
	womanFace1->setAnchorPoint(Vec2(0, 1));
	womanFace1->setPosition(Vec2(73, 255));
	womanFace1->setName("woman_face1");
	womanBody->addChild(womanFace1, 1);

	auto womanFace2 = Sprite::create("woman_face2.png");
	womanFace2->setAnchorPoint(Vec2(0, 1));
	womanFace2->setPosition(Vec2(73, 255));
	womanFace2->setName("woman_face2");
	womanBody->addChild(womanFace2, 1);
	

	this->getHttpData();




	this->getXmlValue("http://openapi.tago.go.kr/openapi/service/ArvlInfoInqireService/getSttnAcctoArvlPrearngeInfoList?ServiceKey=BDKyR2AfTf2dlJ7l1LxFY4qZZlaLEFj7o35IC5Awh10vR79uXle2wxHuDTm2KrUyn0fOMWzn1UOBNtvR7SR3UA%3D%3D&cityCode=25&nodeId=DJB8001169ND&numOfRows=999&pageSize=999&pageNo=1&startPage=1");//("http://zetawiki.com/ex/php/quiz.xml");


	return true;
}



void GameMain::avatarInit(std::string whichMan, std::string whichFace, std::string cloth){
	log(" %s %s %s", whichMan.c_str(), whichFace.c_str(), cloth.c_str());
	Sprite *WhichBody = 0;
	
	if (whichMan.compare("woman") == 0) {
		(this->getChildByName("woman"))->setVisible(true);
		(this->getChildByName("man"))->setVisible(false);
		WhichBody = womanBody;
	}
	else{
		(this->getChildByName("woman"))->setVisible(false);
		(this->getChildByName("man"))->setVisible(true);
		WhichBody = manBody;
	}
	//change face
	if (whichFace.compare("face1") == 0) {
		WhichBody->getChildByName(whichMan + "_face1")->setVisible(true);
		WhichBody->getChildByName(whichMan + "_face2")->setVisible(false);
	}
	else{
		WhichBody->getChildByName(whichMan + "_face1")->setVisible(false);
		WhichBody->getChildByName(whichMan + "_face2")->setVisible(true);
	}

	//change cloth
	if (cloth.compare("cloth1") == 0) {
		WhichBody->getChildByName(whichMan + "_cloth1")->setVisible(true);
	}
	else{
		WhichBody->getChildByName(whichMan + "_cloth1")->setVisible(false);
	}

	
	
}

void GameMain::menuCloseCallback(Ref* pSender)
{
	MenuItem* pMenuItem = (MenuItem *)(pSender);
	int tag = (int)pMenuItem->getTag();
	switch (tag)
	{
	case 10:
		editBoxLayer->setVisible(true);

		CCLOG("item with i% tag selected", tag);
		break;
	case 11:
		this->changeBody();
		CCLOG("item with i% tag selected", tag);
		break;
	case 12:
		this->changeFace();
		CCLOG("item with i% tag selected", tag);
		break;
	case 13:
		this->changeCloth();
		CCLOG("item with i% tag selected", tag);
		break;
	case 14:
		this->saveAvatar();
		CCLOG("item with i% tag selected", tag);
		break;
	}

	log("menuCloseCallback");

}


void GameMain::saveAvatar()
{
	log("ORIGINAL %s %s %s ", mapAvatar.at(0).c_str(), mapAvatar.at(1).c_str(), mapAvatar.at(2).c_str());

	mapAvatarSet.erase(mapAvatar[0]);
	mapAvatarSet.insert(MyAvatarSetMap::value_type(mapAvatar[0], mapAvatar));


	for (auto pair : mapAvatarSet){
		log("key %s ", pair.first.c_str());
		log("value_tag %s %s %s ", pair.second.at(0).c_str(), pair.second.at(1).c_str(), pair.second.at(2).c_str());

		
		int result;
		//result = sqlite3_open_v2(path.c_str(), &pdb, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
		result = sqlite3_open(DBpath.c_str(), &pdb);
		if (result != SQLITE_OK) {
			log("open database failed,  number%d", result);

		}

		char sql[256];

		char* error = NULL;
		sprintf(sql, "delete from user where body='%s'", pair.second.at(0).c_str());
		result = sqlite3_exec(pdb, sql, NULL, NULL, &error);
		if (result != SQLITE_OK) log("error %s", error);

		sprintf(sql, "insert into user values('%s', '%s', '%s')", pair.second.at(0).c_str(), pair.second.at(1).c_str(), pair.second.at(2).c_str());
		result = sqlite3_exec(pdb, sql, NULL, NULL, &error);
		if (result != SQLITE_OK) log("error %s", error);

		sqlite3_close(pdb);

	}

}


void GameMain::changeBody() 
{
	if ( mapAvatar[0].compare("woman") == 0 ) {
		mapAvatar[0] = "man";
	}
	else{
		mapAvatar[0] = "woman";
	}
	if (mapAvatarSet.find(mapAvatar[0]) != mapAvatarSet.end())
	{
		mapAvatar = mapAvatarSet.at(mapAvatar[0]);
	}
	else{
		
		mapAvatarSet.insert(MyAvatarSetMap::value_type(mapAvatar[0], mapAvatar));
	}

	this->avatarInit(mapAvatar[0], mapAvatar[1], mapAvatar[2]);
}

void GameMain::changeFace()
{
	if (mapAvatar[1].compare("face1") == 0) {
		mapAvatar[1]= "face2";
	}
	else{
		mapAvatar[1] = "face1";
	}
	this->avatarInit(mapAvatar[0], mapAvatar[1], mapAvatar[2]);
}

void GameMain::changeCloth()
{
	if (mapAvatar[2].compare("cloth1") == 0) {
		mapAvatar[2] = "";
	}
	else{
		mapAvatar[2] = "cloth1";
	}
	this->avatarInit(mapAvatar[0], mapAvatar[1], mapAvatar[2]);

}


void GameMain::editBoxEditingDidBegin(EditBox *editBox) {
}

void GameMain::editBoxEditingDidEnd(EditBox *editBox) {
}

void GameMain::editBoxTextChanged(EditBox *editBox, const std::string& text) {

}

void GameMain::editBoxReturn(EditBox *editBox) {
	log("editbox -> %s", editBox->getText());
	//UserDefault::getInstance()->setStringForKey("username", NULL);

	editBoxLayer->setVisible(false);
	this->changeLabel(editBox->getText(), GameMain::visitCount);
}

void GameMain::changeLabel(const char *argStr, int visitCount){
	String *str = String::createWithFormat("Hi ! %s\nYou Visited %d Count.", argStr, visitCount);

	log("lbHiMessage -> %s", str);
	lbHiMessage->setString(str->getCString());
}

void GameMain::getHttpData(){
	HttpRequest* request = new HttpRequest();
	request->setRequestType(HttpRequest::Type::GET);
	request->setUrl("http://www.khjlab.com/cocos2dx/booksample/avatar.txt");
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
			std::string res;
			res.insert(res.begin(), buffer->begin(), buffer->end());
			log("response %s", res.c_str());

			mapAvatar = this->split(res, ",");
			log("%s", mapAvatar[0].c_str());
			log("%s", mapAvatar[1].c_str());
			log("%s", mapAvatar[2].c_str());
			
			this->avatarInit(mapAvatar[0], mapAvatar[1], mapAvatar[2]);
			
			mapAvatarSet.insert(MyAvatarSetMap::value_type(mapAvatar[0], mapAvatar));


		}
	});
	request->setTag("Get test");
	HttpClient::getInstance()->send(request);

	request->release();
}

std::vector<std::string> GameMain::split(const  std::string& s, const std::string& delim)
{
	std::vector<std::string> elems;
	size_t pos = 0;
	size_t len = s.length();
	size_t delim_len = delim.length();
	if (delim_len == 0) return elems;
	while (pos < len)
	{
		int find_pos = s.find(delim, pos);
		if (find_pos < 0)
		{
			elems.push_back(s.substr(pos, len - pos));
			break;
		}
		elems.push_back(s.substr(pos, find_pos - pos));
		pos = find_pos + delim_len;
	}
	return elems;
}






















void GameMain::getXmlValue(const char* url)
{
	HttpRequest *request = new HttpRequest();
	request->setUrl(url);
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(CC_CALLBACK_2(GameMain::loadXml, this));
	HttpClient::getInstance()->send(request);
	request->release();
}

void GameMain::loadXml(HttpClient *sender, HttpResponse *response)
{
	if (!response->isSucceed())
	{
		return;
	}

	std::vector<char>* buffer = response->getResponseData();
	std::string _xml = std::string(buffer->begin(), buffer->end());

	tinyxml2::XMLDocument doc;
	log("%s", _xml.c_str());
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
		sprite->setPosition(Vec2(-100, 60));
		this->addChild(sprite, 20000);
		auto *pMoveto = MoveTo::create((float)std::stoi(element_reach->GetText()) , Vec2(580, 60));
		sprite->runAction(pMoveto);


	}
}