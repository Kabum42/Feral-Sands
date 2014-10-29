#include "HelloWorldScene.h"

#include "XInput.h"

USING_NS_CC;

#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )  // Default to 24% of the +/- 32767 range.   This is a reasonable default value but can be altered if needed.

DWORD dwResult;
Sprite3D* boss;

Sprite* point1;
Sprite* point2;
Sprite* pointend;

float point1_x = 200.0f;
float point1_y = 200.0f;

float point2_x = 300.0f;
float point2_y = 100.0f;

float pointend_x = 400.0f;
float pointend_y = 200.0f;

bool paused = false;

float cameraAngle = 34;
float zoom = 500.0f;

float rightThumbX = 0;
float rightThumbY = 32767;

Camera* camera;

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
	sprite->setCameraMask(2);

	boss = Sprite3D::create("boss.obj", "boss.png");

	//boss->setPosition3D(Vec3(visibleSize.width / 2 + (rand()%2) -1 * rand()%1 * visibleSize.width / 2, visibleSize.height / 2 + (rand()%2) -1 * rand()%1 * visibleSize.height / 2, rand()%1 * 300));

	boss->setPosition3D(Vec3(400, 300, 0));

	// LO GIRA A LA DERECHA
	//boss->setRotation3D(Vec3(0,90,0));
	boss->setRotation3D(Vec3(90, 0, 180));

	//boss->setScale(rand()%1 * 20);

	boss->setScale(20);

	this->addChild(boss, 0);

	boss->setCameraMask(2);
	camera = Camera::createPerspective(60, visibleSize.width/visibleSize.height, 1, 2000);
	camera->setCameraFlag(CameraFlag::USER1);
	this->addChild(camera, 1);
	camera->setRotation3D(Vec3(cameraAngle, 0, 0));
	
	//camera->setPosition3D(Vec3(boss->getPositionX(),boss->getPositionY(),boss->getPositionZ() + zoom));


	/* BEZIER PUNTITOS DIBUJADOS

	point1 = Sprite::create("point1.png");
	point1->setPosition(Vec2(point1_x, point1_y));
	this->addChild(point1, 0);

	point2 = Sprite::create("point2.png");
	point2->setPosition(Vec2(point2_x, point2_y));
	this->addChild(point2, 0);

	pointend = Sprite::create("pointend.png");
	pointend->setPosition(Vec2(pointend_x, pointend_y));
	this->addChild(pointend, 0);
    
	*/

	//now the bezier config declaration

	


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

		// CONTROL DE NAVE

		if(wButtons & XINPUT_GAMEPAD_A)
			boss->setPosition3D(Vec3(800 / 2 + (rand()%2) -1 * rand()%1 * 800 / 2, 600 / 2 + (rand()%2) -1 * rand()%1 * 600 / 2, rand()%1 * 300));

		boss->setPosition3D(boss->getPosition3D() + Vec3(state.Gamepad.sThumbLX/4000,state.Gamepad.sThumbLY/4000,0));
		
		// ROTACION DE NAVE
		if (state.Gamepad.sThumbRY != 0) rightThumbY = state.Gamepad.sThumbRY;
		if (state.Gamepad.sThumbRX != 0) rightThumbX = state.Gamepad.sThumbRX;

		boss->setRotation3D(Vec3(90, 0, -90 - atan2(rightThumbY, rightThumbX)*360/(2*M_PI)));

		
		

		/* BEZIERS

		point1_x += state.Gamepad.sThumbLX/4000;
		point1_y += state.Gamepad.sThumbLY/4000;

		point2_x += state.Gamepad.sThumbRX/4000;
		point2_y += state.Gamepad.sThumbRY/4000;

		if(wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) pointend_x += 5;
		if(wButtons & XINPUT_GAMEPAD_DPAD_LEFT) pointend_x -= 5;
		if(wButtons & XINPUT_GAMEPAD_DPAD_UP) pointend_y += 5;
		if(wButtons & XINPUT_GAMEPAD_DPAD_DOWN) pointend_y -= 5;

		point1->setPosition(Vec2(point1_x, point1_y));
		point2->setPosition(Vec2(point2_x, point2_y));
		pointend->setPosition(Vec2(pointend_x, pointend_y));
	
		if (boss->numberOfRunningActions() == 0 && !paused) { 

			boss->setPosition3D(Vec3(0, 300, 100));

			ccBezierConfig bezier;
			bezier.controlPoint_1 = Point(point1_x, point1_y);
			bezier.controlPoint_2 = Point(point2_x, point2_y);
			bezier.endPosition = Point(pointend_x, pointend_y);

			auto action = CCBezierTo::create(3, bezier);
    
			boss->runAction(action);
			
		}

		if(wButtons & XINPUT_GAMEPAD_START) {
			if (!paused) {
				paused = true;
				boss->pauseSchedulerAndActions();
			}
			else {
				paused = false;
				boss->resumeSchedulerAndActions();
			}
		}

		*/

		if (wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) cameraAngle += 0.1;
		if (wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) cameraAngle -= 0.1;
		camera->setRotation3D(Vec3(cameraAngle, 0, 0));

		// SEGUIR AL PERSONAJE
		if(wButtons & XINPUT_GAMEPAD_DPAD_UP) zoom -= 5;
		if(wButtons & XINPUT_GAMEPAD_DPAD_DOWN) zoom += 5;
		//camera->setPosition3D(Vec3(boss->getPositionX(),boss->getPositionY() -zoom,boss->getPositionZ() +zoom));
		camera->setPosition3D(Vec3(boss->getPositionX(), boss->getPositionY() - sin(cameraAngle*(2*M_PI)/360)*zoom, boss->getPositionZ() + cos(cameraAngle*(2*M_PI)/360)*zoom ));
		
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
