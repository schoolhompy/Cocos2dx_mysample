#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


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

	// 백그라운드 컬러
	auto background = LayerColor::create(Color4B::WHITE,
		960,
		630);

	// 백그라운드 칼라 제 2 인수는 순서
	this->addChild(background, 0);


	//12.9 slider
	ui::Slider* pSlider = ui::Slider::create();
	pSlider->loadBarTexture("larabie-16.png");//CloseSelected.png
	pSlider->loadSlidBallTextures("CloseSelected.png");//CloseSelected.png
	pSlider->setPosition(Vec2(200, 200));

	pSlider->addEventListener(CC_CALLBACK_2(HelloWorld::sliderEvent,this));

	this->addChild(pSlider);
	
	//12.... Stepper 
	Sprite* minusSprite = Sprite::create("stepper-minus.png");
	Sprite* plusSprite = Sprite::create("stepper-plus.png");
	ControlStepper *pStepper = ControlStepper::create(minusSprite, plusSprite);


	pStepper->setPosition(Vec2(300, 300));
	
	pStepper->setMinimumValue(0.f);
	pStepper->setMaximumValue(10.f);
	pStepper->setValue(0);
	
	this->addChild(pStepper);

	

	//12.... SWITCH
	Sprite* maskSprite = Sprite::create("switch-mask.png");
	Sprite* onSprite = Sprite::create("switch-on.png");
	Sprite* offSprite = Sprite::create("switch-off.png");
	Sprite* thumbSprite = Sprite::create("switch-thumb.png");
	Label* onLabel = Label::create("On", "Arial", 16);
	Label* offLabel = Label::create("Off", "Arial", 16);

	ControlSwitch *switch1 = ControlSwitch::create(maskSprite, onSprite, offSprite, thumbSprite, onLabel, offLabel);
	switch1->setPosition(Vec2(400, 400));
	this->addChild(switch1);


	//12.... COLOUR PICKER

	ControlColourPicker *cPicker = ControlColourPicker::create();

	cPicker->setColor(ccc3(128, 128, 128));
	cPicker->setPosition(Vec2(300, 400));
	this->addChild(cPicker);




	//12... Potentionmete
	ControlPotentiometer* pMeter = ControlPotentiometer::create("potentiometerTrack.png", "potentiometerProgress.png", "potentiometerButton.png");
	pMeter->setPosition(Vec2(100, 500));

	this->addChild(pMeter);

	//12.... LISTVIEW

	ListView* listView = ListView::create();
	//SCROLLVIEW_DIR_VERTICAL  SCROLLVIEW_DIR_HORIZONTAL  
	listView->setBackGroundColor(Color3B(30, 30, 30));
	listView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
	listView->setDirection(SCROLLVIEW_DIR_VERTICAL);
	listView->setGravity(LISTVIEW_GRAVITY_CENTER_VERTICAL);
	listView->setTouchEnabled(true);
	listView->setBounceEnabled(true);
	//listView->setBackGroundImage("green_edit.png");
	listView->setBackGroundImageScale9Enabled(true);
	listView->setSize(Size(480, 260));
	listView->setPosition(Point(500,400));

	this->addChild(listView);


	//create model
	Button* default_button = Button::create("CloseNormal.png", "CloseSelected.png");
	default_button->setName("Title Button");




	Layout* default_item = Layout::create();
	default_item->setBackGroundColor(Color3B(255, 255, 255));
	default_item->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
	default_item->setTouchEnabled(true);
	default_item->setSize(default_button->getSize());
	default_button->setPosition(Point(default_item->getSize().width / 2.0f, default_item->getSize().height / 2.0f));
	default_item->addChild(default_button);

	//create model
	for (int i = 0; i < 10; ++i) {
		Button* custom_button = Button::create("CloseNormal.png", "CloseSelected.png");
		custom_button->setName("Title Button");
		custom_button->setScale9Enabled(true);
		custom_button->setSize(default_button->getSize());

		Layout* custom_item = Layout::create();
		custom_item->setSize(custom_button->getSize());
		custom_item->setBackGroundColor(Color3B(255, 255, 255));
		custom_item->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
		custom_button->setPosition(Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
		custom_item->addChild(custom_button);
		listView->pushBackCustomItem(custom_item);
	}

	//set model
	listView->setItemModel(default_item);


	

	//12.... SCROLLVIEW
	ImageView* imageView = ImageView::create("HelloWorld.png");
	imageView->setAnchorPoint(Vec2::ZERO);


	ui::ScrollView* scrollView = ui::ScrollView::create();
	scrollView->setDirection(ui::ScrollView::Direction::BOTH);
	//scrollView->setBackGroundImage("HelloWorld.png");
	scrollView->setBounceEnabled(true);
	scrollView->addChild(imageView);

	scrollView->setInnerContainerSize(Size(960, 640));
	scrollView->setContentSize(Size(300, 300));
	scrollView->setPosition(Point(100, 400));


	this->addChild(scrollView);


	//12.... TableVIEW

	Layout* tableLayout = Layout::create();
	tableLayout->setBackGroundColor(Color3B(255, 255, 255));
	tableLayout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
	tableLayout->setTouchEnabled(true);
	tableLayout->setSize(Size(200,400));

	this->addChild(tableLayout);

	// 테이블 헤더 공간
	TableView * tableView = TableView::create(this, Size(300,300));
	// 전체 테이블 표시
	// TableView * tableView = TableView :: create (this, window_size);

	// 전개 방향
	tableView->setDirection(TableView::Direction::VERTICAL);
	// 순서상에서 한에
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);

	// 추가
	tableView->setDelegate(this);
	tableLayout->addChild(tableView);
	tableView->reloadData();

	//12.... PageView

	Size windowSize = Size(300, 300);
	// PageView 를 만들 이에 레이아웃을 추가 해 나갈
	auto pageView = PageView::create();
	pageView->setTouchEnabled(true);
	pageView->setSize(windowSize);
	pageView->setBackGroundColor(Color3B(Color3B::RED));

	// 40 페이지 만들
	for (int i = 0; i < 40; i++) {

		// 레이아웃을 작성
		auto layout = Layout::create();
		layout->setSize(windowSize);

	

		// 텍스트
		auto label = Text::create(StringUtils::format("%d Pages ", (i + 1)), "Arial", 100);
		label->setColor(Color3B(Color3B::BLUE));
		label->setPosition(Vec2(layout->getContentSize().width / 2,
			layout->getContentSize().height / 2));
		layout->addChild(label);

		// 레이아웃을 add 하는
		pageView->addPage(layout);
	}

	// 이벤트 리스너를 추가 ( using namespace ui; 하지 않는다고 볼 수 없기 때문에주의)
	pageView->addEventListenerPageView
		(this, pagevieweventselector(HelloWorld::pageviewCallBack));

	pageView->setPosition(Vec2(300, 300));
	this->addChild(pageView);

	log("slider");




	//12.... WebView
	//안드로이드에선 잘된다.
	/*
		experimental::ui::WebView *webView = experimental::ui::WebView::create();
	// アーカーポンイント
	webView->setAnchorPoint(Point(0.5f, 0.5f));
	webView->setContentSize(Size(400 * 1.0f, 400 * 1.0f));
	webView->setPosition(Vec2(200,500));
	webView->loadURL("http://www.yahoo.co.jp/");

	this->addChild(webView, 1);


	//12.... VidepPlayer
	//안드로이드에선 잘된다.


	experimental::ui::VideoPlayer *vp = experimental::ui::VideoPlayer::create();
	// アーカーポンイント
	vp->setAnchorPoint(Point(0.0f, 0.5f));
	vp->setContentSize(Size(300 * 1.0f, 300 * 1.0f));
	vp->setPosition(Vec2(300, 200));
	vp->setFileName("a.mp4");

	this->addChild(vp, 10000);
	vp->play();
	*/
	return true;
}


// 콜백
void HelloWorld::pageviewCallBack(Ref * sender, PageViewEventType type)
{
	if (type == PAGEVIEW_EVENT_TURNING) {
		auto pageView = dynamic_cast < PageView *> (sender);
		// 선택되어있는 페이지를 기록
		log("% ld", pageView->getCurPageIndex() + 1);
	}
}



void HelloWorld::sliderEvent(Ref *sender, ui::Slider::EventType type)
{
	if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED){
		ui::Slider *slider = dynamic_cast<ui::Slider *>(sender);
		int percent = slider->getPercent();
		log("%d", percent);
	}
}


void HelloWorld::selectedItemEvent(cocos2d::Ref *pSender, ui::SEL_ListViewEvent type)
{


}


// 셀의 크기를 설정하는
Size HelloWorld::cellSizeForTable(TableView * table) {
	return Size(200, 25);
}

// 1 셀에 표시하는 Value 를 세트
TableViewCell * HelloWorld::tableCellAtIndex(TableView * table, ssize_t idx) {

	// 행 번호
	std::string id = StringUtils::format("% zd", idx);
	// 행 텍스트
	std::string text = StringUtils::format(" 라인 ");
	// 셀
	TableViewCell * cell = table->dequeueCell();

	cell = new TableViewCell();
	cell->autorelease();

	// 셀의 배경은 교대로 색상을 변경할
	auto background_color = Color3B::GREEN;
	if (idx % 2) {
		background_color = Color3B::BLUE;
	}

	// Background
	Sprite * bg = Sprite::create();
	bg->setAnchorPoint(Point(0, 0));
	bg->setTextureRect(Rect(0, 0, 200, 24));
	bg->setColor(background_color);
	bg->setTag(100);
	cell->addChild(bg);

	// 경계선
	Sprite * line = Sprite::create();
	line->setAnchorPoint(Point(0, 0));
	line->setTextureRect(Rect(0, 0, 200, 1));
	line->setColor(Color3B::WHITE);
	cell->addChild(line);

	// 이미지
	Sprite * imge_1 = Sprite::create("CloseNormal.png");
	imge_1->setAnchorPoint(Point(0, 0));
	imge_1->setPosition(Point(10, 0));
	cell->addChild(imge_1);

	// ID 텍스트 부분
	auto * label_1 = LabelTTF::create(id.c_str(),"Arial", 20);
	label_1->setAnchorPoint(Point(0, 0));
	label_1->setPosition(Point(110, 0));
	label_1->setColor(Color3B::WHITE);
	cell->addChild(label_1);

	// 텍스트 부분
	auto * label_2 = LabelTTF::create(text.c_str(),"Arial", 20);
	label_2->setAnchorPoint(Point(0, 0));
	label_2->setPosition(Point(210, 0));
	label_2->setColor(Color3B::WHITE);
	cell->addChild(label_2);

	return cell;
}

// 셀 수
ssize_t HelloWorld::numberOfCellsInTableView(TableView * table) {
	return 60;
}

// 셀이 터치되었을 때의 callback
void HelloWorld::tableCellTouched(TableView * table, TableViewCell * cell) {
	CCLOG("% zi 셀이 터치되었습니다 ", cell->getIdx());
}