#include "HelloWorldScene.h"

#include "XInput.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;

#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )  // Default to 24% of the +/- 32767 range.   This is a reasonable default value but can be altered if needed.

HelloWorld* mainLayer;

DWORD dwResult;
Sprite3D* boss;
Sprite3D* boss1;

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

Sprite3D* boss2;

Sprite3D* green_tower;

PathStone path;

Tower towers [50] = { };
int num_towers = 0;

Point position1;
Point position2;

Sprite* point1;
Sprite* point2;
Sprite* pointend;

float point1_x = 0;
float point1_y = -300;

float point2_x = 700;
float point2_y = 1500;

float pointend_x = 1800;
float pointend_y = 300;

bool paused = false;

bool menuTurrets = false;

bool leftTriggerPushed = false;
bool leftShoulderPushed = false;

float cameraAngle = 34;
float zoom = 1000.0f;

float rightThumbX = 0;
float rightThumbY = 0;

float coolDownMax = 0.5;
float coolDownNow = coolDownMax;

Camera* camera;

Scene* HelloWorld::createScene()
{
<<<<<<< HEAD
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    mainLayer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(mainLayer);
=======
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);
>>>>>>> origin/AMS

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
<<<<<<< HEAD
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
	sprite->setCameraMask(2);
    this->addChild(sprite, 0);
=======
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
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

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

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
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	sprite->setCameraMask(2);
>>>>>>> origin/AMS

	auto floor = Sprite3D::create("plano2.obj", "sand.png");
	floor->setScale(100);
	Vec3 corners_floor[8] = {};
	floor->getAABB().getCorners(corners_floor);
	floor->setPosition3D(Vec3(0, 0, -1));
	floor->setRotation3D(Vec3(90, 0, 0));
	floor->setCameraMask(2);
	this->addChild(floor, 0);
	
	boss = Sprite3D::create("boss.obj", "boss.png");
<<<<<<< HEAD
	boss->setPosition3D(Vec3(400, 300, 100));
	boss->setRotation3D(Vec3(90, 0, 180));
	boss->setScale(20);
	boss->setCameraMask(2);
	this->addChild(boss, 0);
=======

	//boss->setPosition3D(Vec3(visibleSize.width / 2 + (rand()%2) -1 * rand()%1 * visibleSize.width / 2, visibleSize.height / 2 + (rand()%2) -1 * rand()%1 * visibleSize.height / 2, rand()%1 * 300));

	boss->setPosition3D(Vec3(400, 300, 0));

	// LO GIRA A LA DERECHA
	//boss->setRotation3D(Vec3(0,90,0));
	boss->setRotation3D(Vec3(90, 0, 180));
>>>>>>> origin/AMS

	
	boss2 = Sprite3D::create("boss.obj", "boss.png");
	boss2->setPosition3D(Vec3(-500, 0, 100));
	boss2->setRotation3D(Vec3(90, 0, 270));
	boss2->setScale(20);
	boss2->setCameraMask(2);
	boss2->setColor(Color3B::YELLOW);
	//boss2->getAABB();
	this->addChild(boss2, 0);

	position2 = Point(-500, 0);

	green_tower = Sprite3D::create("tower.obj", "stone.png");
	green_tower->setPosition3D(Vec3(0, 0, 0));
	green_tower->setRotation3D(Vec3(90, 0, 270));
	green_tower->setScale(3);
	green_tower->setCameraMask(2);
	green_tower->setColor(ccc3(0, 200, 0));
	green_tower->setVisible(false);
	this->addChild(green_tower, 0);
	
	

	Point p = Point(-500, 0);
	ccBezierConfig bezier;
	bezier.controlPoint_1 = Point(point1_x, point1_y);
	bezier.controlPoint_2 = Point(point2_x, point2_y);
	bezier.endPosition = Point(pointend_x, pointend_y);


	
	path = PathStone::PathStone(20, 5, p, bezier);

	this->addChild(path.getLayer());


	p = Point(0, 0);

	Tower t = Tower::Tower("standard", p);
	towers[num_towers] = t;
	num_towers++;
	this->addChild(t.getLayer());
	
	
	

	camera = Camera::createPerspective(60, visibleSize.width/visibleSize.height, 1, 2000);
	camera->setCameraFlag(CameraFlag::USER1);
	camera->setRotation3D(Vec3(cameraAngle, 0, 0));
	this->addChild(camera, 1);

	/*
	auto directionalLight = DirectionLight::create(Vec3(-1.0f, -1.0f, 0.0f), Color3B(200, 200, 200));
	directionalLight->setLightFlag(LightFlag::LIGHT1);
	this->addChild(directionalLight);
	*/
	

	cocos2d::log("LOL");

	// BEZIER PUNTITOS DIBUJADOS

	point1 = Sprite::create("point1.png");
	point1->setPosition(Vec2(point1_x, point1_y));
	point1->setCameraMask(2);
	this->addChild(point1, 0);

	point2 = Sprite::create("point2.png");
	point2->setPosition(Vec2(point2_x, point2_y));
	point2->setCameraMask(2);
	this->addChild(point2, 0);

	pointend = Sprite::create("pointend.png");
	pointend->setPosition(Vec2(pointend_x, pointend_y));
	pointend->setCameraMask(2);
	this->addChild(pointend, 0);
    
	

	//now the bezier config declaration

	


	boss->setCameraMask(2);

	boss1 = Sprite3D::create("boss.obj", "boss.png");

	//boss->setPosition3D(Vec3(visibleSize.width / 2 + (rand()%2) -1 * rand()%1 * visibleSize.width / 2, visibleSize.height / 2 + (rand()%2) -1 * rand()%1 * visibleSize.height / 2, rand()%1 * 300));

	boss1->setPosition3D(Vec3(0, 300, 0));

	// LO GIRA A LA DERECHA
	//boss->setRotation3D(Vec3(0,90,0));
	boss1->setRotation3D(Vec3(90, 0, 180));

	//boss->setScale(rand()%1 * 20);

	boss1->setScale(20);

	this->addChild(boss1, 0);

	boss1->setCameraMask(2);

	camera = Camera::createPerspective(60, visibleSize.width / visibleSize.height, 1, 2000);
	camera->setCameraFlag(CameraFlag::USER1);
	this->addChild(camera, 1);
	camera->setRotation3D(Vec3(cameraAngle, 0, 0));

	_eventDispatcher->addCustomEventListener("object_collision", [=](EventCustom* event){
		float* elements = static_cast<float*>(event->getUserData());
		boss1->setPositionX(boss1->getPositionX() - elements[0]);
		boss1->setPositionY(boss1->getPositionY() - elements[1]);
	});

	/*auto bossOBB = OBB(boss->getAABB());

	Vec3 corners[8] = {};

	bossOBB.getCorners(corners);

	drawOBB = DrawNode3D::create();
	drawOBB->drawCube(corners, Color4F(1.0, 1.0, 1.0, 1.0));
	this->addChild(drawOBB, 0);

	drawOBB->setCameraMask(2);*/

	//drawOBB->setAnchorPoint(boss->getPosition());

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

	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	// Simply get the state of the controller from XInput.
	dwResult = XInputGetState(0, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected 

		if ((state.Gamepad.sThumbLX < INPUT_DEADZONE &&
			state.Gamepad.sThumbLX > -INPUT_DEADZONE) &&
			(state.Gamepad.sThumbLY < INPUT_DEADZONE &&
			state.Gamepad.sThumbLY > -INPUT_DEADZONE))
		{
			state.Gamepad.sThumbLX = 0;
			state.Gamepad.sThumbLY = 0;
		}

		if ((state.Gamepad.sThumbRX < INPUT_DEADZONE &&
			state.Gamepad.sThumbRX > -INPUT_DEADZONE) &&
			(state.Gamepad.sThumbRY < INPUT_DEADZONE &&
			state.Gamepad.sThumbRY > -INPUT_DEADZONE))
		{
			state.Gamepad.sThumbRX = 0;
			state.Gamepad.sThumbRY = 0;
		}

		WORD wButtons = state.Gamepad.wButtons;

<<<<<<< HEAD
		
		// COLOCAR TORRETA
		if(state.Gamepad.bLeftTrigger > 50) {
			if (!leftTriggerPushed && menuTurrets) {
				
				Vec3 corners[8] = {};
				green_tower->getAABB().getCorners(corners);
				Point p = Point(boss->getPositionX() + rightThumbX/100 +(corners[5].x - corners[0].x)/2, boss->getPositionY() + rightThumbY/100 -(corners[5].y - corners[0].y)/2);
				
				Tower t = Tower::Tower("standard", p);
				towers[num_towers] = t;
				num_towers++;
				
			}
			leftTriggerPushed = true;
		}
		else {
			leftTriggerPushed = false;
		}
			
		// CONTROL DE NAVE
		boss->setPosition3D(boss->getPosition3D() + Vec3(state.Gamepad.sThumbLX/4000,state.Gamepad.sThumbLY/4000,0));
		
=======
		// CONTROL DE NAVE

		if (wButtons & XINPUT_GAMEPAD_A)
			boss->setPosition3D(Vec3(800 / 2 + (rand() % 2) - 1 * rand() % 1 * 800 / 2, 600 / 2 + (rand() % 2) - 1 * rand() % 1 * 600 / 2, rand() % 1 * 300));

		boss->setPosition3D(boss->getPosition3D() + Vec3(state.Gamepad.sThumbLX / 4000, state.Gamepad.sThumbLY / 4000, 0));

		//drawOBB->setPosition3D(drawOBB->getPosition3D() + Vec3(state.Gamepad.sThumbLX / 4000, state.Gamepad.sThumbLY / 4000, 0));

>>>>>>> origin/AMS
		// ROTACION DE NAVE
		if (state.Gamepad.sThumbRY != 0) rightThumbY = state.Gamepad.sThumbRY;
		if (state.Gamepad.sThumbRX != 0) rightThumbX = state.Gamepad.sThumbRX;

<<<<<<< HEAD
		boss->setRotation3D(Vec3(90, 0, -90 - atan2(rightThumbY, rightThumbX)*360/(2*M_PI)));
			

		if(state.Gamepad.bRightTrigger != 0 && coolDownNow >= coolDownMax) {
			coolDownNow = 0;
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("shoot.wav");
		}
			
		

		// ROTAR CAMARA
		//if (wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) cameraAngle += 0.1;
		//if (wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) cameraAngle -= 0.1;

		// MENU DE TORRETAS
		if (wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
			
			if (!leftShoulderPushed) {

				menuTurrets = !menuTurrets;

				if (menuTurrets) {
					green_tower->setVisible(true);
				}
				else {
					green_tower->setVisible(false);
				}

			}

			leftShoulderPushed = true;

		}

		else {

			leftShoulderPushed = false;

		}


		// VIBRACION
		/*
		if (wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
			// ESTA VIBRACIÓN NO DEBERÍA EXPERIMENTARSE AL PULSAR EL BOTÓN, LA DEBERÍA PROVOCAR LA PROPIA
			// CLASE DE LA TORRETA, MIENTRAS SE ESTÁ ALZANDO, ACOMPAÑADA DE SONIDO Y DE PARTÍCULAS DE POLVO
			vibration.wLeftMotorSpeed = 20000;
			vibration.wRightMotorSpeed = 20000;
			XInputSetState(0, &vibration);
		}
		else {
			vibration.wLeftMotorSpeed = 0;
			vibration.wRightMotorSpeed = 0;
			XInputSetState(0, &vibration);
		}
		*/


		// SEGUIR AL PERSONAJE
		if(wButtons & XINPUT_GAMEPAD_DPAD_UP) zoom -= 5;
		if(wButtons & XINPUT_GAMEPAD_DPAD_DOWN) zoom += 5;
		//camera->setPosition3D(Vec3(boss->getPositionX(), boss->getPositionY() - sin(cameraAngle*(2*M_PI)/360)*zoom, boss->getPositionZ() + cos(cameraAngle*(2*M_PI)/360)*zoom ));
		
=======
		boss->setRotation3D(Vec3(90, 0, -90 - atan2(rightThumbY, rightThumbX) * 360 / (2 * M_PI)));

		//drawOBB->setRotation3D(Vec3(0, 0, -90 - atan2(rightThumbY, rightThumbX) * 360 / (2 * M_PI)));

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
		if (wButtons & XINPUT_GAMEPAD_DPAD_UP) zoom -= 5;
		if (wButtons & XINPUT_GAMEPAD_DPAD_DOWN) zoom += 5;
		//camera->setPosition3D(Vec3(boss->getPositionX(),boss->getPositionY() -zoom,boss->getPositionZ() +zoom));
		camera->setPosition3D(Vec3(boss->getPositionX(), boss->getPositionY() - sin(cameraAngle*(2 * M_PI) / 360)*zoom, boss->getPositionZ() + cos(cameraAngle*(2 * M_PI) / 360)*zoom));

		if (pow(boss->getPositionX() - boss1->getPositionX(), 2) + pow(boss->getPositionY() - boss1->getPositionY(), 2) < pow(300, 2)){

			float div = pow(300, 2) / (pow(boss->getPositionX() - boss1->getPositionX(), 2) + pow(boss->getPositionY() - boss1->getPositionY(), 2));

			float* elements = new float[2];
			elements[0] = 0.5 * (abs(boss->getPositionX() - boss1->getPositionX())*div - abs(boss->getPositionX() - boss1->getPositionX()));
			if (boss->getPositionX() < boss1->getPositionX()) elements[0] = -elements[0];
			elements[1] = 0.5 * (abs(boss->getPositionY() - boss1->getPositionY())*div - abs(boss->getPositionY() - boss1->getPositionY()));
			if (boss->getPositionY() < boss1->getPositionY()) elements[1] = -elements[1];

			EventCustom event("object_collision");
			event.setUserData(elements);

			_eventDispatcher->dispatchEvent(&event);

		}

>>>>>>> origin/AMS
	}
	else
	{
		// Controller is not connected 

	}

	// Irrelevant if controlles is connected

	if (coolDownNow < coolDownMax) {
		coolDownNow += dt;
	}

	// BOSS 2 ROTATED TOWARDS BOSS 1
	//Point p = Point(boss->getPositionX(), boss->getPositionY());
	//rotateToPoint(boss2, p);

	//rightThumbY 
	//rightThumbX 
	//boss->setRotation3D(Vec3(90, 0, -90 - atan2(rightThumbY, rightThumbX)*360/(2*M_PI)));

	Vec3 corners[8] = {};
	green_tower->getAABB().getCorners(corners);
	
	green_tower->setPosition3D(Vec3(boss->getPositionX() + rightThumbX/100 +(corners[5].x - corners[0].x)/2, boss->getPositionY() + rightThumbY/100 -(corners[5].y - corners[0].y)/2, 0));

	//UPDATE TOWERS
	
	for (int i = 0; i < num_towers; i++) {
		towers[i].update(dt);
		//towers[i].getLayer()->setPositionX(towers[i].getLayer()->getPositionX()+1);
	}

	//UPDATE PATHS
	path.update(dt);

	
	
	point1->setPosition(Vec2(point1_x, point1_y));
	point2->setPosition(Vec2(point2_x, point2_y));
	pointend->setPosition(Vec2(pointend_x, pointend_y));
	
	if (boss2->numberOfRunningActions() == 0 && !paused) { 

		boss2->setPosition3D(Vec3(-500, 0, 100));

		ccBezierConfig bezier;
		bezier.controlPoint_1 = Point(point1_x, point1_y);
		bezier.controlPoint_2 = Point(point2_x, point2_y);
		bezier.endPosition = Point(pointend_x, pointend_y);

		auto action = CCBezierTo::create(5, bezier);
    
		boss2->runAction(action);
			
	}

	else {

		position1 = position2;
		position2 = Point(boss2->getPositionX(), boss2->getPositionY());

		rotateToVec2(boss2, Vec2(position2.x - position1.x, position2.y - position1.y));

	}
	
	// FIN BEZIERS

	camera->setRotation3D(Vec3(cameraAngle, 0, 0));
	camera->setPosition3D(Vec3(boss->getPositionX(), boss->getPositionY() - sin(cameraAngle*(2*M_PI)/360)*zoom, boss->getPositionZ() + cos(cameraAngle*(2*M_PI)/360)*zoom ));

}

void HelloWorld::rotateToPoint(Sprite3D* s, Point p) {

	float vec_x = p.x - s->getPositionX();
	float vec_y = p.y - s->getPositionY();

	s->setRotation3D(Vec3(90, 0, -90 - atan2(vec_y, vec_x)*360/(2*M_PI)));

}

void HelloWorld::rotateToVec2(Sprite3D* s, Vec2 v) {

	s->setRotation3D(Vec3(90, 0, -90 - atan2(v.y, v.x)*360/(2*M_PI)));

}


void HelloWorld::menuCloseCallback(Ref* pSender)
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
