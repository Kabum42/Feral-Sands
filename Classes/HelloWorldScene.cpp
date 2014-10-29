#include "HelloWorldScene.h"

#include "XInput.h"

USING_NS_CC;

#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )  // Default to 24% of the +/- 32767 range.   This is a reasonable default value but can be altered if needed.

DWORD dwResult;
Sprite3D* boss;

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
    //////////////////////////////
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
    
    auto label = LabelTTF::create("Die World", "Arial", 24);
    
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

	boss = Sprite3D::create("boss.obj", "boss.png");

	//boss->setPosition3D(Vec3(visibleSize.width / 2 + (rand()%2) -1 * rand()%1 * visibleSize.width / 2, visibleSize.height / 2 + (rand()%2) -1 * rand()%1 * visibleSize.height / 2, rand()%1 * 300));

	boss->setPosition3D(Vec3(400, 300, 100));

	//boss->setScale(rand()%1 * 20);

	boss->setScale(20);

	this->addChild(boss, 0);

	this->scheduleUpdate();
    
    return true;
}

void HelloWorld::update(float dt)
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	// Simply get the state of the controller from XInput.
	dwResult = XInputGetState(0, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected 

		if( (state.Gamepad.sThumbLX < INPUT_DEADZONE &&
                state.Gamepad.sThumbLX > -INPUT_DEADZONE ) &&
            ( state.Gamepad.sThumbLY < INPUT_DEADZONE &&
                state.Gamepad.sThumbLY > -INPUT_DEADZONE ) )
        {
            state.Gamepad.sThumbLX = 0;
            state.Gamepad.sThumbLY = 0;
        }

        if( ( state.Gamepad.sThumbRX < INPUT_DEADZONE &&
                state.Gamepad.sThumbRX > -INPUT_DEADZONE ) &&
            ( state.Gamepad.sThumbRY < INPUT_DEADZONE &&
                state.Gamepad.sThumbRY > -INPUT_DEADZONE ) )
        {
            state.Gamepad.sThumbRX = 0;
            state.Gamepad.sThumbRY = 0;
        }

		WORD wButtons = state.Gamepad.wButtons;

		if(wButtons & XINPUT_GAMEPAD_A)
			boss->setPosition3D(Vec3(800 / 2 + (rand()%2) -1 * rand()%1 * 800 / 2, 600 / 2 + (rand()%2) -1 * rand()%1 * 600 / 2, rand()%1 * 300));

		boss->setRotation3D(Vec3(-state.Gamepad.sThumbLY/1000,state.Gamepad.sThumbLX/1000,0));

		boss->setPosition3D(boss->getPosition3D() + Vec3(state.Gamepad.sThumbLX/4000,state.Gamepad.sThumbLY/4000,0));
	}
	else
	{
		// Controller is not connected 
	}

}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
