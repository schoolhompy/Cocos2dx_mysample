#ifndef __GAMEMAIN_SCENE_H__
#define __GAMEMAIN_SCENE_H__

#include "tinyxml2/tinyxml2.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "network/HttpClient.h"
#include "sqlite3.h"

USING_NS_CC;

using namespace tinyxml2;
using namespace cocos2d::network;

using namespace cocos2d::ui;

typedef std::vector<std::string>      MyAvatar;
typedef std::map <std::string, MyAvatar> MyAvatarSetMap;

class GameMain : public cocos2d::Layer, public EditBoxDelegate
{
public:
	cocos2d::Label *lbHiMessage;
	cocos2d::Layer *editBoxLayer;

	cocos2d::Layer *womanLayer;
	cocos2d::Layer *manLayer;


	cocos2d::Sprite *womanBody;
	cocos2d::Sprite *manBody;

	sqlite3 *pdb ;
	std::string DBpath;

	static cocos2d::Scene* createScene();
	static int visitCount;
	static std::string a;


	MyAvatar mapAvatar;
	MyAvatarSetMap mapAvatarSet;

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);



	void getXmlValue(const char* url);
	void loadXml(HttpClient *sender, HttpResponse *response);




	// implement the "static create()" method manually
	CREATE_FUNC(GameMain);

private:
	virtual void editBoxEditingDidBegin(EditBox *editBox);
	virtual void editBoxEditingDidEnd(EditBox *editBox);
	virtual void editBoxTextChanged(EditBox *editBox, const std::string& text);
	virtual void editBoxReturn(EditBox *editBox);

	void changeLabel(const char *str, int visitCount);
	void GameMain::getHttpData();
	std::vector<std::string> GameMain::split(const  std::string& s, const std::string& delim); 
	void GameMain::avatarInit(std::string whichMan, std::string whichFace, std::string cloth);

	void GameMain::changeBody();
	void GameMain::changeFace();
	void GameMain::changeCloth();
	void GameMain::saveAvatar();
};


#endif // __GAMEMAIN_SCENE_H__
