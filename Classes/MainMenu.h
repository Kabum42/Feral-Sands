#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "cocos2d.h"
//#include "HelloWorldScene.h"
//#include "XInput.h"

USING_NS_CC;

class MainMenu : public cocos2d::Layer
{
public:

	Sprite* title;
	Sprite* loading;
	MenuItemImage* closeBtn;

	void goToHelloWorldScene(Ref *pSender);
	void toHelloWorldScene();
	void btnToControls(Ref *pSender);
	void btnToCredits(Ref *pSender);
	void closeBtnAction(Ref *pSender);
	void menuAnimations(float dt);
	
	void showControls();
	void hideControls();
	void showCredits();
	void hideCredits();
	
	void DOWN();
	void UP();
	void A();
	void B();
	
	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	void menuCloseCallback(cocos2d::Ref* pSender);
	
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainMenu);
};

#endif
