#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"

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

	auto winsize = Director::getInstance()->getWinSize();
	// add quit button
	auto label = Label::createWithSystemFont("QUIT", "sans", 32);
	auto quit = MenuItemLabel::create(label, [](Ref*){
		exit(0);
	});
	auto labelSize = label->getContentSize();
	quit->setPosition(Vec2(winsize.width / 2 - labelSize.width / 2 - 16,
		-winsize.height / 2 + labelSize.height / 2 + 16));
	addChild(Menu::create(quit, NULL));

	// add test menu
	createTestMenu();

    return true;
}

void HelloWorld::createTestMenu()
{
	MenuItemFont::setFontName("sans");
	Size size = Director::getInstance()->getWinSize();

	auto menu = Menu::create(MenuItemFont::create("log event", CC_CALLBACK_1(HelloWorld::onLogEvent, this)),
		MenuItemFont::create("log exception", CC_CALLBACK_1(HelloWorld::onLogException, this)),
		MenuItemFont::create("log social", CC_CALLBACK_1(HelloWorld::onLogSocial, this)),
		NULL);

	menu->alignItemsVerticallyWithPadding(5);
	menu->setPosition(Vec2(size.width / 2, size.height / 2));
	addChild(menu);
}

void HelloWorld::onLogEvent(cocos2d::Ref* sender)
{
	sdkbox::PluginGoogleAnalytics::logEvent("Test", "Click", "", 1);
	sdkbox::PluginGoogleAnalytics::dispatchHits();
	CCLOG("sdkbox::PluginGoogleAnalytics::logEvent(\"Test\", \"Click\", \"\", 1);");
}

void HelloWorld::onLogException(cocos2d::Ref* sender)
{
	sdkbox::PluginGoogleAnalytics::logException("Test Exception", true);
	sdkbox::PluginGoogleAnalytics::dispatchHits();
	CCLOG("sdkbox::PluginGoogleAnalytics::logException(\"Test Exception\", true);");
}

void HelloWorld::onLogSocial(cocos2d::Ref* sender)
{
	sdkbox::PluginGoogleAnalytics::logSocial("facebook", "share", "sdkbox");
	sdkbox::PluginGoogleAnalytics::dispatchHits();
	CCLOG("sdkbox::PluginGoogleAnalytics::logSocial(\"facebook\", \"share\", \"sdkbox\");");
}
