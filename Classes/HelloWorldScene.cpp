/*
TO DO:
-Eventos para evitar tener ochenta arrays.
-Pulsaciones de botones como eventos.
-Boss como clase Character que hereda de Sprite3D.
-Spawner como clase
-Crear funciones init para todos los elementos más importantes de la GameScreen(camera, layers, etc.)
-Crear el physicsworld que contenga todos los elementos y compruebe sus colisiones.
-Meter dentro del Character todo lo que sea pulsación de botones.
*/
#include "HelloWorldScene.h"

#include "XInput.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;

#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )  // Default to 24% of the +/- 32767 range.   This is a reasonable default value but can be altered if needed.

DWORD dwResult;
float data [1] = { };

Player* boss;
Sprite3D* boss1;
//Sprite3D* boss2;

Entity* static_objects [200] = { };
int num_static_objects = 0;
Entity* mobile_objects [200] = { };
int num_mobile_objects = 0;

bool paused = false;

float cameraAngle = 34;
float zoom = 1000.0f;

Camera* camera;

DirectionLight* sun;

Sprite3D* green_tower;

PathStone path;

//Point position1;
//Point position2;

float point1_x = 0;
float point1_y = -300;

float point2_x = 700;
float point2_y = 1500;

float pointend_x = 1800;
float pointend_y = 300;

bool menuTurrets = false;

bool leftTriggerPushed = false;
bool leftShoulderPushed = false;

float rightThumbX = 0;
float rightThumbY = 0;

float coolDownMax = 0.2;
float coolDownNow = coolDownMax;

EventCustom event("EnterFrame");
EventCustom event_add_mobile("add_mobile");

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




	_eventDispatcher->addCustomEventListener("object_collision", [=](EventCustom* event){
		float* elements = static_cast<float*>(event->getUserData());
		mobile_objects[(int)elements[2]]->_sprite->setPositionX(mobile_objects[(int)elements[2]]->_sprite->getPositionX() - elements[0]);
		mobile_objects[(int)elements[2]]->_sprite->setPositionY(mobile_objects[(int)elements[2]]->_sprite->getPositionY() - elements[1]);
	});

	_eventDispatcher->addCustomEventListener("remove_static", [=](EventCustom* event){
		float* data_static = static_cast<float*>(event->getUserData());
		removeStaticObject(data_static[0]);
	});
	
	_eventDispatcher->addCustomEventListener("remove_mobile", [=](EventCustom* event){
		float* data_mobile = static_cast<float*>(event->getUserData());
		removeMobileObject(data_mobile[0]);
	});
	
	
	_eventDispatcher->addCustomEventListener("add_mobile", [=](EventCustom* event){
		Entity* e = static_cast<Entity*>(event->getUserData());
		addMobileObject(e);
	});
	
	





	auto floor = Sprite3D::create("floor.obj", "sand.png");
	floor->setScale(100);
	Vec3 corners_floor[8] = {};
	floor->getAABB().getCorners(corners_floor);
	floor->setPosition3D(Vec3(0, 0, -1));
	floor->setRotation3D(Vec3(90, 0, 0));
	floor->setCameraMask(2);
	this->addChild(floor, 0);
	
	Point p = Point(400, 300);

	boss = new Player(p);
	mobile_objects [num_mobile_objects] = boss;
	boss->_num_in_array = num_mobile_objects;
	num_mobile_objects++;
	boss->_sprite->setCameraMask(2);
	this->addChild(boss->_sprite, 0);

	green_tower = Sprite3D::create("tower.obj", "stone.png");
	green_tower->setPosition3D(Vec3(0, 0, 4*30));
	green_tower->setRotation3D(Vec3(90, 0, 270));
	green_tower->setScale(30);
	green_tower->setCameraMask(2);
	green_tower->setColor(ccc3(0, 200, 0));
	green_tower->setVisible(false);
	this->addChild(green_tower, 0);
	
	p = Point(-500, 0);
	ccBezierConfig bezier;
	bezier.controlPoint_1 = Point(point1_x, point1_y);
	bezier.controlPoint_2 = Point(point2_x, point2_y);
	bezier.endPosition = Point(pointend_x, pointend_y);

	path = PathStone::PathStone(50, 5, p, bezier);
	this->addChild(path.getLayer());

	Wave* w = new Wave(p, bezier);
	w->addEnemy("grunt", 1);
	w->addEnemy("grunt", 1);
	w->addEnemy("grunt", 2);
	w->_active = true;

	p = Point(0, 0);

	Nexus* n = new Nexus(p);
	static_objects [num_static_objects] = n;
	num_static_objects++;
	n->_sprite->setCameraMask(2);
	this->addChild(n->_sprite, 1);

	camera = Camera::createPerspective(60, visibleSize.width/visibleSize.height, 1, 2000);
	camera->setCameraFlag(CameraFlag::USER1);
	camera->setRotation3D(Vec3(cameraAngle, 0, 0));
	this->addChild(camera, 1);

	sun = DirectionLight::create(Vec3(-1.0f, -1.0f, -1.0f), Color3B(255, 255, 255));
	sun->retain();
	sun->setEnabled(true);
	addChild(sun);
	sun->setCameraMask(2);

	/*
	auto directionalLight = DirectionLight::create(Vec3(-1.0f, -1.0f, 0.0f), Color3B(200, 200, 200));
	directionalLight->setLightFlag(LightFlag::LIGHT1);
	this->addChild(directionalLight);
	*/

	//SET BACKGROUND MUSIC
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sandstorm.wav", true);

	this->scheduleUpdate();

	return true;
}

void HelloWorld::update(float dt)
{
	
	data[0] = dt;
	event.setUserData(data);
	_eventDispatcher->dispatchEvent(&event);

	
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
		

		// COLOCAR TORRETA
		
		if(state.Gamepad.bLeftTrigger > 50) {
			if (!leftTriggerPushed && menuTurrets) {
				

				Point p = Point(boss->_sprite->getPositionX() + rightThumbX/100, boss->_sprite->getPositionY() + rightThumbY/100);

				Tower* t = new Tower("standard", p);
				static_objects [num_static_objects] = t;
				num_static_objects++;
				t->_sprite->setCameraMask(2);
				this->addChild(t->_sprite, 1);
				
				
			}
			if (!leftTriggerPushed) leftTriggerPushed = true;
		}
		else {
			if (leftTriggerPushed) leftTriggerPushed = false;
		}
		
			
		// CONTROL DE NAVE
		boss->_sprite->setPosition3D(boss->_sprite->getPosition3D() + Vec3(state.Gamepad.sThumbLX*dt/70, state.Gamepad.sThumbLY*dt/70, 0));

		
		if (wButtons & XINPUT_GAMEPAD_A)
			boss->_sprite->setPosition3D(Vec3(800 / 2 + (rand() % 2) - 1 * rand() % 1 * 800 / 2, 600 / 2 + (rand() % 2) - 1 * rand() % 1 * 600 / 2, 100));
		

		// ROTACION DE NAVE
		if (state.Gamepad.sThumbRY != 0) rightThumbY = state.Gamepad.sThumbRY;
		if (state.Gamepad.sThumbRX != 0) rightThumbX = state.Gamepad.sThumbRX;

		boss->_sprite->setRotation3D(Vec3(90, 0, -90 - atan2(rightThumbY, rightThumbX)*360/(2*M_PI)));

		// DISPARO
		
		if(state.Gamepad.bRightTrigger != 0 && coolDownNow >= coolDownMax) {
			coolDownNow = state.Gamepad.bRightTrigger/255 * coolDownMax/2;
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("shoot.wav");
			WeaponShot* _shotInstance = new WeaponShot(boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D());
			mobile_objects[num_mobile_objects] = _shotInstance;
			_shotInstance->_num_in_array = num_mobile_objects;
			num_mobile_objects++;
			_shotInstance->_sprite->setCameraMask(2);
			this->addChild(_shotInstance->_sprite, 1);
		}
		

		// ROTAR CAMARA
		if (wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) cameraAngle += 0.1;
		if (wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) cameraAngle -= 0.1;
		camera->setRotation3D(Vec3(cameraAngle, 0, 0));

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

		if(wButtons & XINPUT_GAMEPAD_DPAD_UP) zoom -= 5;
		if(wButtons & XINPUT_GAMEPAD_DPAD_DOWN) zoom += 5;

		

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
	
	green_tower->setPosition3D(Vec3(boss->_sprite->getPositionX() + rightThumbX/100, boss->_sprite->getPositionY() + rightThumbY/100, 4*30));

	//CHECKEAR STUPIDTEST
	/*
	if (current_s->_active) {
		current_s->placeEnemy();
		
		Point p = Point(-500, 0);
		ccBezierConfig bezier;
		bezier.controlPoint_1 = Point(point1_x, point1_y);
		bezier.controlPoint_2 = Point(point2_x, point2_y);
		bezier.endPosition = Point(pointend_x, pointend_y);
		Enemy* e;
		e = new Enemy("grunt", p, bezier, 5);
		event_add_mobile.setUserData(e);
		_eventDispatcher->dispatchEvent(&event_add_mobile);
		
		current_s->_active = false;
	}
	*/
	

	//UPDATE PATHS
	path.update(dt);
	
	// COLLISION DETECTION MOBILE VS MOBILE OBJECTS
	
		for (int i = 0; i < num_mobile_objects; i++) {
			for (int j = 0; j < num_mobile_objects; j++) {

				float total_radius = mobile_objects[i]->_radius + mobile_objects[j]->_radius;

				if (mobile_objects[i] != mobile_objects[j] && mobile_objects[i]->_health > 0 && mobile_objects[j]->_health > 0 && pow(mobile_objects[i]->_sprite->getPositionX() - mobile_objects[j]->_sprite->getPositionX(), 2) + pow(mobile_objects[i]->_sprite->getPositionY() - mobile_objects[j]->_sprite->getPositionY(), 2) < pow(total_radius, 2)) {
					// SON OBJETOS DIFERENTES Y COLISIONAN, Y ADEMAS LOS DOS ESTAN ACTIVOS (HEALTH > 0)

					if (mobile_objects[i]->_type.compare("shot") == 0 || mobile_objects[j]->_type.compare("shot") == 0) {
						// UNO DE LOS DOS ES UN SHOT
						if (mobile_objects[i]->_type.compare("player") == 0 || mobile_objects[j]->_type.compare("player") == 0) {
							// EL OTRO ES EL JUGADOR
						}
						else if (mobile_objects[i]->_type.compare("enemy") == 0 || mobile_objects[j]->_type.compare("enemy") == 0) {
							// EL OTRO ES UN ENEMY
							Entity* bala;
							Entity* enemigo;

							if (mobile_objects[i]->_type.compare("shot") == 0) bala = mobile_objects[i];
							if (mobile_objects[j]->_type.compare("shot") == 0) bala = mobile_objects[j];

							if (mobile_objects[i]->_type.compare("enemy") == 0) enemigo = mobile_objects[i];
							if (mobile_objects[j]->_type.compare("enemy") == 0) enemigo = mobile_objects[j];

							// LA BALA MUERE
							bala->_health = 0;

							// EL ENEMIGO SE HIERE
							enemigo->_health -= 20;
							if (enemigo->_health > 0) { 
								CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hurt.wav");
								enemigo->_sprite->setColor(Color3B(255, 0, 0));
								enemigo->_injured = 0.1;
							}
							else {
								CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("explosion.wav");
							}
						
						}
					
					}
					else {
						// COMPORTAMIENTO DE REPULSION
						float div = pow(total_radius, 2) / (pow(mobile_objects[i]->_sprite->getPositionX() - mobile_objects[j]->_sprite->getPositionX(), 2) + pow(mobile_objects[i]->_sprite->getPositionY() - mobile_objects[j]->_sprite->getPositionY(), 2));

						float* elements = new float[3];
						elements[0] = 0.5 * (abs(mobile_objects[i]->_sprite->getPositionX() - mobile_objects[j]->_sprite->getPositionX())*div - abs(mobile_objects[i]->_sprite->getPositionX() - mobile_objects[j]->_sprite->getPositionX()));
						if (mobile_objects[i]->_sprite->getPositionX() < mobile_objects[j]->_sprite->getPositionX()) elements[0] = -elements[0];
						elements[1] = 0.5 * (abs(mobile_objects[i]->_sprite->getPositionY() - mobile_objects[j]->_sprite->getPositionY())*div - abs(mobile_objects[i]->_sprite->getPositionY() - mobile_objects[j]->_sprite->getPositionY()));
						if (mobile_objects[i]->_sprite->getPositionY() < mobile_objects[j]->_sprite->getPositionY()) elements[1] = -elements[1];
						elements[2] = j;

						EventCustom event("object_collision");
						event.setUserData(elements);

						_eventDispatcher->dispatchEvent(&event);
					}

				}
				
			}
		}
		
		
		
		// COLLISION DETECTION STATIC VS MOBILE OBJECTS
		// VAN DESPUES QUE LA COLISION ENTRE MOVILES PORQUE LA COLISION ESTATICA SE TIENE QUE RESPETAR POR ENCIMA DE LA OTRA
		
		for (int i = 0; i < num_static_objects; i++) {
			for (int j = 0; j < num_mobile_objects; j++) {

				float total_radius = static_objects[i]->_radius + mobile_objects[j]->_radius;

				if (static_objects[i] != mobile_objects[j] && pow(static_objects[i]->_sprite->getPositionX() - mobile_objects[j]->_sprite->getPositionX(), 2) + pow(static_objects[i]->_sprite->getPositionY() - mobile_objects[j]->_sprite->getPositionY(), 2) < pow(total_radius, 2)) {

					float div = pow(total_radius, 2) / (pow(static_objects[i]->_sprite->getPositionX() - mobile_objects[j]->_sprite->getPositionX(), 2) + pow(static_objects[i]->_sprite->getPositionY() - mobile_objects[j]->_sprite->getPositionY(), 2));

					float* elements = new float[3];
					elements[0] = 0.5 * (abs(static_objects[i]->_sprite->getPositionX() - mobile_objects[j]->_sprite->getPositionX())*div - abs(static_objects[i]->_sprite->getPositionX() - mobile_objects[j]->_sprite->getPositionX()));
					if (static_objects[i]->_sprite->getPositionX() < mobile_objects[j]->_sprite->getPositionX()) elements[0] = -elements[0];
					elements[1] = 0.5 * (abs(static_objects[i]->_sprite->getPositionY() - mobile_objects[j]->_sprite->getPositionY())*div - abs(static_objects[i]->_sprite->getPositionY() - mobile_objects[j]->_sprite->getPositionY()));
					if (static_objects[i]->_sprite->getPositionY() < mobile_objects[j]->_sprite->getPositionY()) elements[1] = -elements[1];
					elements[2] = j;

					EventCustom event("object_collision");
					event.setUserData(elements);

					_eventDispatcher->dispatchEvent(&event);

				}

			}
		}


		// DIE, BASTARDS, DIE!
		
		for (int i = 0; i < num_mobile_objects; i++) {

			if (mobile_objects[i]->_health <= 0) {

				//mobile_objects[i]->_sprite->stopAllActions();
				mobile_objects[i]->_sprite->removeFromParentAndCleanup(true);
				mobile_objects[i]->_sprite = NULL;
				_eventDispatcher->removeEventListenersForTarget(mobile_objects[i]);
				
				float* data_mobile = new float[1];
				data_mobile[0] = mobile_objects[i]->_num_in_array;
				EventCustom event_mobile("remove_mobile");
				event_mobile.setUserData(data_mobile);
				_eventDispatcher->dispatchEvent(&event_mobile);

			}

		}
		
	

	camera->setRotation3D(Vec3(cameraAngle, 0, 0));
	camera->setPosition3D(Vec3(boss->_sprite->getPositionX(), boss->_sprite->getPositionY() - sin(cameraAngle*(2*M_PI)/360)*zoom, boss->_sprite->getPositionZ() + cos(cameraAngle*(2*M_PI)/360)*zoom ));

}

void HelloWorld::rotateToPoint(Sprite3D* s, Point p) {

	float vec_x = p.x - s->getPositionX();
	float vec_y = p.y - s->getPositionY();

	s->setRotation3D(Vec3(90, 0, -90 - atan2(vec_y, vec_x)*360/(2*M_PI)));

}

void HelloWorld::rotateToVec2(Sprite3D* s, Vec2 v) {

	s->setRotation3D(Vec3(90, 0, -90 - atan2(v.y, v.x)*360/(2*M_PI)));

}

void HelloWorld::removeStaticObject(int num_in_array) {

	for (int i = num_in_array; i < (num_static_objects-1); i++) {
		static_objects[i] = static_objects[i+1];
		static_objects[i]->_num_in_array = i;
	}

	// SI HACES ESTO, EXPLOTA
	//static_objects[num_static_objects] = NULL;
	num_static_objects--;

}

void HelloWorld::removeMobileObject(int num_in_array) {

	
	for (int i = num_in_array; i < (num_mobile_objects-1); i++) {
		mobile_objects[i] = mobile_objects[i+1];
		mobile_objects[i]->_num_in_array = i;
	}
	
	// SI HACES ESTO, EXPLOTA
	//mobile_objects[num_mobile_objects] = NULL;
	num_mobile_objects--;

}

void HelloWorld::addMobileObject(Entity* e) {
	
	mobile_objects [num_mobile_objects] = e;
	e->_num_in_array = num_mobile_objects;
	num_mobile_objects++;
	e->_sprite->setCameraMask(2);
	this->addChild(e->_sprite, 1);
	e->_active = true;
	
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
