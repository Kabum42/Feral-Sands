#include "MainMenu.h"
#include "HelloWorldScene.h"
#include "XInput.h"

USING_NS_CC;

Sprite* background;
Sprite* controls;
Sprite* credits;
Sprite* highlight;
Size visibleSize;

bool m_pressed_UP = false;
bool m_pressed_DOWN = false;
bool m_pressed_W = false;
bool m_pressed_S = false;

bool m_pressed_SPACE = false;
bool m_pressed_ENTER = false;
bool m_pressed_Q = false;

bool gamepad_UP = false;
bool gamepad_DOWN = false;
bool gamepad_A = false;
bool gamepad_START = false;
bool gamepad_B = false;
bool gamepad_Y = false;

DWORD dwordResult;

float tiempo = 0.0f;	//Time accumulator to track floating movement
int amplitude = 15;		//Floating movement amplitude
int speed = 1;			//Floating movement speed

int selection = 1;
bool submenu = false;

Point titleOrigin;



Scene* MainMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenu::create();
    scene->addChild(layer);

    return scene;
}


bool MainMenu::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(MainMenu::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(MainMenu::keyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	background = Sprite::create("Background.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	background->setScale(1.75, 1.75);
	addChild(background, 0);

	
	controls = Sprite::create("ControlScheme.png");
	controls->setVisible(false);
	controls->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(controls, 3);
	credits = Sprite::create("Credits.png");
	credits->setVisible(false);
	credits->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(credits, 3);
	
	
	highlight = Sprite::create("Highlight.png");
	highlight->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 120 - 92 * selection);
	addChild(highlight, 0);


    title = Sprite::create("title.png");
	title->setPosition(visibleSize.width / 2, visibleSize.height / 1.2);
	title->setScale(0.5, 0.5);
	titleOrigin = title->getPosition();
	this->addChild(title, 2);

	auto playBtn = MenuItemImage::create("PlayBtn.png", "PlayBtnPressed.png", CC_CALLBACK_1(MainMenu::goToHelloWorldScene, this));
	auto controlsBtn = MenuItemImage::create("controlsBtn.png", "controlsBtnPressed.png", CC_CALLBACK_1(MainMenu::btnToControls, this));
	auto creditsBtn = MenuItemImage::create("creditsBtn.png", "creditsBtnPressed.png", CC_CALLBACK_1(MainMenu::btnToCredits, this));
	closeBtn = MenuItemImage::create("closeBtn.png", "closeBtnPressed.png", CC_CALLBACK_1(MainMenu::closeBtnAction, this));
	closeBtn->setVisible(false);

	auto menu = Menu::create(playBtn,controlsBtn,creditsBtn,closeBtn,NULL);
	menu->setPosition(visibleSize.width/2, visibleSize.height/2.4 - 20);
	menu->alignItemsVerticallyWithPadding(visibleSize.height/30);
	this->addChild(menu, 1);
	closeBtn->setPosition(0, -213);

	loading = Sprite::create("Loading.png");
	loading->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	loading->setVisible(false);
	addChild(loading, 4);
	
	
	this->schedule(schedule_selector(MainMenu::menuAnimations), 0.05);

    return true;
}

void MainMenu::goToHelloWorldScene(Ref *pSender) {
	if (!submenu) toHelloWorldScene();
}
void MainMenu::toHelloWorldScene(){
	//background->setVisible(false);
	//this->removeChild(background);
	loading->setVisible(true);
	//while (!loading->isVisible()){}
	//loading->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene)); //va a HelloWorldScene con un fundido
	//Director::getInstance()->replaceScene(scene);
}

void MainMenu::btnToControls(Ref *pSender) {
	if (!submenu){
		showControls();
		submenu = true;
		selection = 2;
		highlight->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 120 - 92 * selection);
	}
}

void MainMenu::btnToCredits(Ref *pSender) {
	if (!submenu){
		showCredits();
		submenu = true;
		selection = 3;
		highlight->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 120 - 92 * selection);
	}
}

void MainMenu::closeBtnAction(Ref *pSender) {
	B();
}

void MainMenu::menuAnimations(float dt){
	
	tiempo += dt*speed;
	title->setPosition(titleOrigin.x, titleOrigin.y + amplitude*cos(tiempo));
	
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	dwordResult = XInputGetState(0, &state);
	WORD wButtons = state.Gamepad.wButtons;

	if (wButtons & XINPUT_GAMEPAD_DPAD_UP) {
		if (!gamepad_UP){
			UP();
			gamepad_UP = true;
		}
	}
	else { gamepad_UP = false; }
	if (wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
		if (!gamepad_DOWN){
			DOWN();
			gamepad_DOWN = true;
		}
	}
	else { gamepad_DOWN = false; }
	if (wButtons & XINPUT_GAMEPAD_A) {
		if (!gamepad_A){
			A();
			gamepad_A = true;
		}
	}
	else { gamepad_A = false; }
	if (wButtons & XINPUT_GAMEPAD_START) {
		if (!gamepad_START){
			A();
			gamepad_START = true;
		}
	}
	else { gamepad_START = false; }
	if (wButtons & XINPUT_GAMEPAD_B) {
		if (!gamepad_B){
			B();
			gamepad_B = true;
		}
	}
	else { gamepad_B = false; }
	if (wButtons & XINPUT_GAMEPAD_Y) {
		if (!gamepad_Y){
			B();
			gamepad_Y = true;
		}
	}
	else { gamepad_Y = false; }

}

// Reacciones Menu
void MainMenu::showControls() {
	controls->setVisible(true);
	closeBtn->setVisible(true);
}
void MainMenu::hideControls() {
	controls->setVisible(false);
	closeBtn->setVisible(false);
}
void MainMenu::showCredits(){
	credits->setVisible(true);
	closeBtn->setVisible(true);
}
void MainMenu::hideCredits(){
	credits->setVisible(false);
	closeBtn->setVisible(false);
}

// Acciones Menu
void MainMenu::DOWN() {
	if (!submenu){
		selection++;
		if (selection == 4) selection = 1;
		highlight->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 120 - 92 * selection);
	}
}
void MainMenu::UP() {
	if (!submenu){
		selection--;
		if (selection == 0) selection = 3;
		highlight->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 120 - 92 * selection);
	}
}
void MainMenu::A() {
	if (!submenu){
		submenu = true;
		switch(selection){
			case 1:
				toHelloWorldScene();
				break;
			case 2:
				showControls();
				break;
			case 3:
				showCredits();
				break;
			default:
				break;
		}
	}
	else{
		submenu = false;
		hideControls();
		hideCredits();
	}
}
void MainMenu::B() {
	if(submenu){
		submenu = false;
		hideControls();
		hideCredits();
	}
	else { CC_CALLBACK_1(MainMenu::menuCloseCallback, this); }
}


// Controles por Teclado
void MainMenu::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{

	if (keyCode == EventKeyboard::KeyCode::KEY_W) { 
		if (!m_pressed_W){
			UP();
			m_pressed_W = true;
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		if (!m_pressed_S){
			DOWN();
			m_pressed_S = true;
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		if (!m_pressed_UP){
			UP();
			m_pressed_UP = true;
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		if (!m_pressed_DOWN){
			DOWN();
			m_pressed_DOWN = true;
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		if (!m_pressed_SPACE){
			A();
			m_pressed_SPACE = true;
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
		if (!m_pressed_ENTER){
			A();
			m_pressed_ENTER = true;
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_Q) {
		if (!m_pressed_Q){
			B();
			m_pressed_Q = true;
		}
	}

}

void MainMenu::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{

	if (keyCode == EventKeyboard::KeyCode::KEY_W) { 
		m_pressed_W = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		m_pressed_S = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		m_pressed_UP = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		m_pressed_DOWN = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		m_pressed_SPACE = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
		m_pressed_ENTER = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_Q) {
		m_pressed_Q = false;
	}
}


// EXIT GAME
void MainMenu::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

