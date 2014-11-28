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

Nexus* nexus;
Player* boss;
Sprite3D* boss1;

int total_enemies = 0;
int dead_enemies = 0;

Entity* static_objects [200] = { };
int num_static_objects = 0;
Entity* mobile_objects [200] = { };
int num_mobile_objects = 0;

PathStone* active_pathstones [10] = { };
int num_active_pathstones = 0;

bool paused = false;

float cameraAngle = 34;
float zoom = 1000.0f;

Camera* camera;

bool enabledLights = true;
DirectionLight* sun;

Sprite3D* green_tower;

float nomefio = 0;

float point1_x = -1500;
float point1_y = -300;

float point2_x = -750;
float point2_y = 700;

float pointend_x = 0;
float pointend_y = 0;

bool menuTurrets = false;

bool leftTriggerPushed = false;
bool leftShoulderPushed = false;
bool startPushed = false;

float rightThumbX = 0;
float rightThumbY = 32767;

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

	_eventDispatcher->addCustomEventListener("nexus_life", [=](EventCustom* event){
		int* data_nexus = static_cast<int*>(event->getUserData());
		nexus->_life += data_nexus[0];
		if (nexus->_life <= 0) {
			nexus->_sprite->setColor(Color3B(200, 0, 0));
		}
	});

	_eventDispatcher->addCustomEventListener("enemy_dead", [=](EventCustom* event){
		dead_enemies++;
	});


	
	auto floor = Sprite3D::create("floor.obj", "sand.png");
	floor->setScale(1000);
	Vec3 corners_floor[8] = {};
	floor->getAABB().getCorners(corners_floor);
	floor->setPosition3D(Vec3(0, 0, -1));
	floor->setRotation3D(Vec3(90, 0, 0));
	floor->setCameraMask(2);
	this->addChild(floor, 0);
	
	Point p = Point(0, -500);

	boss = new Player(p);
	mobile_objects [num_mobile_objects] = boss;
	boss->_num_in_array = num_mobile_objects;
	num_mobile_objects++;
	boss->_sprite->setCameraMask(2);
	this->addChild(boss->_sprite, 0);

	green_tower = Sprite3D::create("Tower.obj", "stone.png");
	green_tower->setPosition3D(Vec3(0, 0, 0.44*60));
	green_tower->setRotation3D(Vec3(90, 0, 270));
	green_tower->setScale(60);
	green_tower->setCameraMask(2);
	green_tower->setColor(ccc3(0, 200, 0));
	green_tower->setVisible(false);
	this->addChild(green_tower, 0);
	
	p = Point(-2000, 0);
	ccBezierConfig bezier;
	bezier.controlPoint_1 = Point(point1_x, point1_y);
	bezier.controlPoint_2 = Point(point2_x, point2_y);
	bezier.endPosition = Point(pointend_x, pointend_y);


	PathStone* path = new PathStone(20, 1, p, bezier);
	this->addChild(path->getLayer());
	active_pathstones[num_active_pathstones] = path;
	num_active_pathstones++;

	Wave* w = new Wave(p, path);
	w->addEnemy("grunt", 1.5);
	w->addEnemy("grunt", 1);
	w->addEnemy("grunt", 2);
	w->addEnemy("grunt", 20);
	w->addEnemy("grunt", 2);
	w->addEnemy("grunt", 2);
	w->addEnemy("grunt", 2);
	w->addEnemy("grunt", 2);
	w->addEnemy("grunt", 2);
	total_enemies += w->num_enemies;
	w->_active = true;

	//
	p = Point(2000, 0);
	ccBezierConfig bezier2;
	bezier2.controlPoint_1 = Point(1500, 300);
	bezier2.controlPoint_2 = Point(750, -700);
	bezier2.endPosition = Point(0, 0);
	
	PathStone* path2 = new PathStone(20, 1, p, bezier2);
	this->addChild(path2->getLayer());
	active_pathstones[num_active_pathstones] = path2;
	num_active_pathstones++;
	
	Wave* w2 = new Wave(p, path2);
	w2->addEnemy("grunt", 1.5);
	w2->addEnemy("grunt", 1);
	w2->addEnemy("grunt", 2);
	w2->addEnemy("grunt", 20);
	w2->addEnemy("grunt", 2);
	w2->addEnemy("grunt", 2);
	w2->addEnemy("grunt", 2);
	w2->addEnemy("grunt", 2);
	w2->addEnemy("grunt", 2);
	total_enemies += w2->num_enemies;
	w2->_active = true;
	

	p = Point(0, 0);

	nexus = new Nexus(p);
	static_objects [num_static_objects] = nexus;
	num_static_objects++;
	nexus->_sprite->setCameraMask(2);
	this->addChild(nexus->_sprite, 1);

	Atrezzo* a;
	a = new Atrezzo(Point(500, 500), "rock");
	static_objects [num_static_objects] = a;
	num_static_objects++;
	a->_sprite->setCameraMask(2);
	this->addChild(a->_sprite, 1);

	camera = Camera::createPerspective(60, visibleSize.width/visibleSize.height, 1, 2000);
	camera->setCameraFlag(CameraFlag::USER1);
	camera->setRotation3D(Vec3(cameraAngle, 0, 0));
	this->addChild(camera, 1);

	if (enabledLights) {
		sun = DirectionLight::create(Vec3(0.0f, 0.0f, 1.0f), Color3B(255, 255, 127));
		//sun->retain();
		sun->setEnabled(true);
		addChild(sun);
		sun->setCameraMask(2);
	}
	

	/*
	auto directionalLight = DirectionLight::create(Vec3(-1.0f, -1.0f, 0.0f), Color3B(200, 200, 200));
	directionalLight->setLightFlag(LightFlag::LIGHT1);
	this->addChild(directionalLight);
	*/

	//now the bezier config declaration

	//SET BACKGROUND MUSIC
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sandstorm.wav", true);

	this->scheduleUpdate();

	return true;
}

void HelloWorld::update(float dt)
{
	
	if (!paused) {

		data[0] = dt;
		event.setUserData(data);
		_eventDispatcher->dispatchEvent(&event);

		EventCustom eventVisible("checkVisible");
		eventVisible.setUserData(new Point(boss->_sprite->getPositionX(), boss->_sprite->getPositionY()));
		_eventDispatcher->dispatchEvent(&eventVisible);

		if (enabledLights) {
			nomefio += dt/2;
			if (nomefio > 1) { nomefio = -1; }
			sun->setDirection(Vec3(0, nomefio, -1));
			sun->setColor(Color3B(255, 255 -(nomefio+1)*(128/2), 127 + (nomefio+1)*(128/2)));
		}

	}
	
	

	
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

			if (wButtons & XINPUT_GAMEPAD_START) {
				if (!startPushed) {
					paused = !paused;
					if (paused) {
						EventCustom event_paused("paused");
						_eventDispatcher->dispatchEvent(&event_paused);
					}
					else {
						EventCustom event_unpaused("unpaused");
						_eventDispatcher->dispatchEvent(&event_unpaused);
					}
				}
				startPushed = true;
			}

			else {
				startPushed = false;
			}

		if (!paused) {

			// COLOCAR TORRETA
		
			if(state.Gamepad.bLeftTrigger > 50) {
				if (!leftTriggerPushed && menuTurrets) {
				
					if (green_tower->getColor().r == 200) {

					}
					else if (green_tower->getColor().g == 200) {

						Point p = Point(boss->_sprite->getPositionX() + rightThumbX/100, boss->_sprite->getPositionY() + rightThumbY/100);

						Tower* t = new Tower("standard", p);
						static_objects [num_static_objects] = t;
						num_static_objects++;
						t->_sprite->setCameraMask(2);
						this->addChild(t->_sprite, 1);

					}
				
				}
				else if (!leftTriggerPushed && !menuTurrets && boss->dashing == 0 && (state.Gamepad.sThumbLX != 0 || state.Gamepad.sThumbLY != 0)) {

					Vec2 v = Vec2(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY);
					v.normalize();
					boss->dashingVector = v;
					boss->dashing = 0.5;

				}
				if (!leftTriggerPushed) leftTriggerPushed = true;
			}
			else {
				if (leftTriggerPushed) leftTriggerPushed = false;
			}
		
			
			// CONTROL DE PLAYER
			if (boss->dashing == 0) {
				boss->_sprite->setPosition3D(boss->_sprite->getPosition3D() + Vec3(state.Gamepad.sThumbLX*dt/70, state.Gamepad.sThumbLY*dt/70, 0));
			}

		
			if (wButtons & XINPUT_GAMEPAD_A)
				//boss->_sprite->setPosition3D(Vec3(800 / 2 + (rand() % 2) - 1 * rand() % 1 * 800 / 2, 600 / 2 + (rand() % 2) - 1 * rand() % 1 * 600 / 2, 100));
				boss->_sprite->setPosition3D(Vec3(0, -500, boss->_sprite->getPositionZ()));

			// ROTACION DE PLAYER
			if (state.Gamepad.sThumbRY != 0) rightThumbY = state.Gamepad.sThumbRY;
			if (state.Gamepad.sThumbRX != 0) rightThumbX = state.Gamepad.sThumbRX;

			boss->_sprite->setRotation3D(Vec3(90, 0, -90 - atan2(rightThumbY, rightThumbX)*360/(2*M_PI)));

			// DISPARO
		if(state.Gamepad.bRightTrigger != 0 && coolDownNow >= coolDownMax) {
			coolDownNow = state.Gamepad.bRightTrigger/255 * coolDownMax/2;
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("shoot.wav");
			WeaponShot* _shotInstance = new WeaponShot(boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D());
			addMobileObject(_shotInstance);
		}
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


	}

	else
	{
		// Controller is not connected 
	}

	// Irrelevant if controlles is connected

	if (!paused) {

		if (coolDownNow < coolDownMax) {
			coolDownNow += dt;
		}

		// BOSS 2 ROTATED TOWARDS BOSS 1
		//Point p = Point(boss->getPositionX(), boss->getPositionY());
		//rotateToPoint(boss2, p);
	
		// SE COLOCA LA TORRE DE PRUEBA EN EL LUGAR AL QUE APUNTAS Y SE PONE EN VERDE
		green_tower->setPosition3D(Vec3(boss->_sprite->getPositionX() + rightThumbX/100, boss->_sprite->getPositionY() + rightThumbY/100, 0.44*60));
		green_tower->setColor(ccc3(0, 200, 0));

		// SE COMPRUEBA QUE LA TORRE NO ESTÁ TOCANDO OTRO OBJETO ESTÁTICO
		for (int i = 0; i < num_static_objects; i++) {
			// 60*1 es el radio de la futura torre
			float total_radius = static_objects[i]->_radius + (60*1);

			if (pow(static_objects[i]->_sprite->getPositionX() - green_tower->getPositionX(), 2) + pow(static_objects[i]->_sprite->getPositionY() -green_tower->getPositionY(), 2) < pow(total_radius, 2)) {

				green_tower->setColor(ccc3(200, 0, 0));

			}
		}

		// SE COMPRUEBA QUE LA TORRE NO ESTÁ TOCANDO NINGUNA DE LAS PIEDRAS DE UN CAMINO
		for (int i = 0; i < num_active_pathstones; i++) {

			for (int j = 0; j < active_pathstones[i]->number_tiles; j++) {

				// 60*1 es el radio de la futura torre
				float stone_radius = 60;
				float total_radius = stone_radius + (60*1);

				if (pow(active_pathstones[i]->tiles[j]->getPositionX() - green_tower->getPositionX(), 2) + pow(active_pathstones[i]->tiles[j]->getPositionY() -green_tower->getPositionY(), 2) < pow(total_radius, 2)) {

					green_tower->setColor(ccc3(200, 0, 0));

				}

			}

		}

	
		// COLLISION DETECTION MOBILE VS MOBILE OBJECTS
	
			for (int i = 0; i < num_mobile_objects; i++) {
				for (int j = 0; j < num_mobile_objects; j++) {

					float total_radius = mobile_objects[i]->_radius + mobile_objects[j]->_radius;

					if (mobile_objects[i] != mobile_objects[j] && mobile_objects[i]->_health > 0 && mobile_objects[j]->_health > 0 && pow(mobile_objects[i]->_sprite->getPositionX() - mobile_objects[j]->_sprite->getPositionX(), 2) + pow(mobile_objects[i]->_sprite->getPositionY() - mobile_objects[j]->_sprite->getPositionY(), 2) < pow(total_radius, 2)) {
						// SON OBJETOS DIFERENTES Y COLISIONAN, Y ADEMAS LOS DOS ESTAN ACTIVOS (HEALTH > 0)

						if (mobile_objects[i]->_type.compare("shot") == 0 || mobile_objects[j]->_type.compare("shot") == 0) {
							// UNO DE LOS DOS ES UN SHOT
							if (mobile_objects[i]->_type.compare("enemy") == 0 || mobile_objects[j]->_type.compare("enemy") == 0) {
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
						else if (mobile_objects[i]->_type.compare("tower_shot") == 0 || mobile_objects[j]->_type.compare("tower_shot") == 0) {
							// UNO DE LOS DOS ES UN TOWER_SHOT
							if (mobile_objects[i]->_type.compare("enemy") == 0 || mobile_objects[j]->_type.compare("enemy") == 0) {
								// EL OTRO ES UN ENEMY
								TowerShot* bala;
								Entity* enemigo;

								if (mobile_objects[i]->_type.compare("tower_shot") == 0) bala = (TowerShot*) mobile_objects[i];
								if (mobile_objects[j]->_type.compare("tower_shot") == 0) bala = (TowerShot*) mobile_objects[j];

								if (mobile_objects[i]->_type.compare("enemy") == 0) enemigo = mobile_objects[i];
								if (mobile_objects[j]->_type.compare("enemy") == 0) enemigo = mobile_objects[j];

								// LA BALA MUERE
								bala->_health = 0;

								// EL ENEMIGO SE HIERE
								enemigo->_health -= bala->_damage;
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
						else if (mobile_objects[i]->_type.compare("player") == 0 || mobile_objects[j]->_type.compare("player") == 0) {
							// UNO DE LOS DOS ES EL JUGADOR

							if (mobile_objects[i]->_type.compare("enemy") == 0 || mobile_objects[j]->_type.compare("enemy") == 0) {
								// EL OTRO ES UN ENEMY
								Entity* player;
								Entity* enemigo;

								if (mobile_objects[i]->_type.compare("player") == 0) player = mobile_objects[i];
								if (mobile_objects[j]->_type.compare("player") == 0) player = mobile_objects[j];

								if (mobile_objects[i]->_type.compare("enemy") == 0) enemigo = mobile_objects[i];
								if (mobile_objects[j]->_type.compare("enemy") == 0) enemigo = mobile_objects[j];

								repulse(player, enemigo);

								// EL JUGADOR SE HIERE
								player->_health -= 20;
								if (player->_health > 0) { 
									CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hurt.wav");
									player->_sprite->setColor(Color3B(255, 0, 0));
									player->_injured = 0.1;
								}
								else {
									CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("explosion.wav");
									player->_health = 200;
									player->_sprite->setPosition3D(Vec3(0, -500, player->_sprite->getPositionZ()));
								}
							
							}
						}
						else {
						
							repulse(mobile_objects[i], mobile_objects[j]);

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

						if (mobile_objects[j]->_type.compare("enemy") == 0 && static_objects[i]->_type.compare("nexus") == 0) {

							Enemy* e = (Enemy*)mobile_objects[j];
							e->harmNexus();

						}
						else if (mobile_objects[j]->_type.compare("tower_shot") == 0) {
							// LOS TOWER_SHOT NO COLISIONAN CON NADA ESTATICO
						}
						else {

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
			}

		// TOWER TARGETING (STATIC VS MOBILE OBJECTS)

		for (int i = 0; i < num_static_objects; i++) {
				
			if (static_objects[i]->_type.compare("tower") == 0){
				
				if (static_objects[i]->_target == nullptr)
				{
					for (int j = 0; j < num_mobile_objects; j++)
					{
						//float total_radius = myTower->_range;
						if (mobile_objects[j]->_type.compare("enemy") == 0 && mobile_objects[j]->_health > 0){
							if (pow(static_objects[i]->_sprite->getPositionX() - mobile_objects[j]->_sprite->getPositionX(), 2) + pow(static_objects[i]->_sprite->getPositionY() - mobile_objects[j]->_sprite->getPositionY(), 2) < pow(static_objects[i]->_range, 2)) {
								static_objects[i]->_target = mobile_objects[j]; // Depurar: IMPLEMENT ITERATOR TO CHOOSE CLOSEST
							}
						}
					}
				}
			}
		}


			// DIE, BASTARDS, DIE!
		
			for (int i = 0; i < num_mobile_objects; i++) {

				if (mobile_objects[i]->_health <= 0) {

					if (mobile_objects[i]->_type.compare("enemy") == 0) {
						EventCustom event_dead("enemy_dead");
						_eventDispatcher->dispatchEvent(&event_dead);
					}

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
		
		if (nexus->_life > 0 && dead_enemies == total_enemies) {

			nexus->_sprite->setColor(Color3B(0, 255, 0));

		}

		camera->setRotation3D(Vec3(cameraAngle, 0, 0));
		camera->setPosition3D(Vec3(boss->_sprite->getPositionX(), boss->_sprite->getPositionY() - sin(cameraAngle*(2*M_PI)/360)*zoom, boss->_sprite->getPositionZ() + cos(cameraAngle*(2*M_PI)/360)*zoom ));

	}

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

void HelloWorld::repulse(Entity* e1, Entity* e2) {

	float total_radius = e1->_radius + e2->_radius;

	// COMPORTAMIENTO DE REPULSION
	float div = pow(total_radius, 2) / (pow(e1->_sprite->getPositionX() - e2->_sprite->getPositionX(), 2) + pow(e1->_sprite->getPositionY() - e2->_sprite->getPositionY(), 2));

	float* elements = new float[3];
	elements[0] = 0.5 * (abs(e1->_sprite->getPositionX() - e2->_sprite->getPositionX())*div - abs(e1->_sprite->getPositionX() - e2->_sprite->getPositionX()));
	if (e1->_sprite->getPositionX() < e2->_sprite->getPositionX()) elements[0] = -elements[0];
	elements[1] = 0.5 * (abs(e1->_sprite->getPositionY() - e2->_sprite->getPositionY())*div - abs(e1->_sprite->getPositionY() - e2->_sprite->getPositionY()));
	if (e1->_sprite->getPositionY() < e2->_sprite->getPositionY()) elements[1] = -elements[1];
	elements[2] = e2->_num_in_array;

	EventCustom event("object_collision");
	event.setUserData(elements);

	_eventDispatcher->dispatchEvent(&event);

	elements[0] = 0.5 * (abs(e2->_sprite->getPositionX() - e1->_sprite->getPositionX() )*div - abs(e2->_sprite->getPositionX() - e1->_sprite->getPositionX()));
	if (e1->_sprite->getPositionX() > e2->_sprite->getPositionX()) elements[0] = -elements[0];
	elements[1] = 0.5 * (abs(e2->_sprite->getPositionY() - e1->_sprite->getPositionY() )*div - abs(e2->_sprite->getPositionY() - e1->_sprite->getPositionY()));
	if (e1->_sprite->getPositionY() > e2->_sprite->getPositionY()) elements[1] = -elements[1];
	elements[2] = e1->_num_in_array;

	event.setUserData(elements);

	_eventDispatcher->dispatchEvent(&event);
	//FIN REPULSION

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
