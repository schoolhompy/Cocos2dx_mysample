#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"


USING_NS_CC;
USING_NS_CC_EXT;

using namespace cocos2d::ui;

using namespace extension;


class HelloWorld : public cocos2d::Layer,
	public TableViewDataSource,
	public TableViewDelegate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void sliderEvent(Ref *sender,Slider::EventType type);

	void selectedItemEvent(Ref *pSender, SEL_ListViewEvent type);

	//pageView
	void pageviewCallBack(cocos2d::Ref * psender, cocos2d::ui::PageViewEventType type);

	// TableViewDataSource 추상 메소드
	virtual Size cellSizeForTable(TableView * table);
	virtual TableViewCell * tableCellAtIndex(TableView * table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView * table);

	// TableViewDelegate 추상 메소드
	virtual void tableCellTouched(TableView * table, TableViewCell * cell);

	// TableViewDelegate 가 계승하고있는 ScrollView 의 추상 메소드
	virtual void scrollViewDidScroll(ui::ScrollView * view) {};
	virtual void scrollViewDidZoom(ui::ScrollView * view) {};
};

#endif // __HELLOWORLD_SCENE_H__
