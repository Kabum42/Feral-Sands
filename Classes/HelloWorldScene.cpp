﻿/*
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

#define COCOS2D_DEBUG 1


USING_NS_CC;

#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )  // Default to 24% of the +/- 32767 range.   This is a reasonable default value but can be altered if needed.

bool pressed_W = false;
bool pressed_A = false;
bool pressed_S = false;
bool pressed_D = false;

bool pressed_UP = false;
bool pressed_LEFT = false;
bool pressed_DOWN = false;
bool pressed_RIGHT = false;

bool pressed_SPACE = false;
bool pressed_SPACE_PUSHED = false;

bool pressed_ENTER = false;
bool pressed_ENTER_PUSHED = false;

Vec2 mouse_position = Vec2(0, 0);
bool mouse_clicked = false;

DWORD dwResult;
float data [1] = { };

Sprite* minimapa;
Sprite* player_arrow;

Sprite* vida;
Sprite* sinvida;

Sprite* dialog_box;
Sprite* button_a;
Sprite* button_enter;

Dialog* active_dialog = NULL;
Label* dialog_label;

Label* top_label;
Label* stop_label;

<<<<<<< HEAD
int resources = 0;
=======
int deuda_resources = 0;
int resources = 1000;
>>>>>>> origin/master
Sprite* resource;
Label* resources_label;

Sprite* icon_dash;
Sprite* icon_tower;
Sprite* icon_slow;
Sprite* icon_monster;

Sprite* gun_normal;
Sprite* gun_fire;
Sprite* gun_air;

Sprite* bar_back;
Sprite* bar;

Nexus* nexus;
Player* boss;
Sprite3D* boss1;

int total_enemies = 0;
int dead_enemies = 0;

Entity* static_objects [400] = { };
int num_static_objects = 0;
Entity* mobile_objects [200] = { };
int num_mobile_objects = 0;
Sprite* enemy_points [200] = { };

PathStone* active_pathstones [10] = { };
int num_active_pathstones = 0;

bool paused = false;

float cameraAngle = 34;
float zoom;

Camera* camera;

bool enabledLights = false;
DirectionLight* sun;

Sprite3D* green_tower;
Sprite3D* green_slow;
Sprite3D* green_monster;

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
bool rightShoulderPushed = false;
bool startPushed = false;
bool aPushed = false;

float rightThumbX = 0;
float rightThumbY = 32767;

float coolDownMax = 0.2;
float coolDownNow = coolDownMax;
float coolDownFireNow = coolDownMax;
float coolDownAirNow = coolDownMax;
float airPower = 0;

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

	floorSize = 2048*5;
	//floorSize = 1024;
	zoom = 200*(floorSize/2048);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object

	/*
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

	*/

    // create menu, it's an autorelease object

	/*
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	*/

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    top_label = Label::createWithTTF("Prueba OMFG","fonts/Volkoff.otf", 32);
    top_label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - top_label->getContentSize().height));
    this->addChild(top_label, 1);
	top_label->setVisible(false);

<<<<<<< HEAD
	minimapa = Sprite::create("sand.png");
=======
	stop_label = Label::createWithTTF("PAUSE","fonts/Volkoff.otf", 32);
    stop_label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - top_label->getContentSize().height -50));
    this->addChild(stop_label, 1);
	stop_label->setVisible(false);

	minimapa = Sprite::create("sand_guia.png");
>>>>>>> origin/master
	minimapa->setScale(0.0625); // ESTO ES 1/16, pasando de 2048 pixeles a 128
	minimapa->setPositionX(960 -minimapa->getBoundingBox().size.width/2 -6 -10);
	minimapa->setPositionY(640 -minimapa->getBoundingBox().size.height/2 -6 -10);
	this->addChild(minimapa, 1);

	for (int aux_bla = 0; aux_bla < 200; aux_bla++) {
		Sprite* aux_spr = Sprite::create("enemy_point.png");
		this->addChild(aux_spr, 1);
		aux_spr->setVisible(false);
		enemy_points[aux_bla] = aux_spr;
	}

	player_arrow = Sprite::create("player_arrow.png");
	this->addChild(player_arrow, 1);

	auto marco = Sprite::create("marco_minimapa.png");
	marco->setPositionX(960 -marco->getBoundingBox().size.width/2 -10);
	marco->setPositionY(640 -marco->getBoundingBox().size.height/2 -10);
	this->addChild(marco, 1);

	vida = Sprite::create("icon_vida.png");
	vida->setPositionX(vida->getBoundingBox().size.width/2 +10);
	vida->setPositionY(640 -vida->getBoundingBox().size.height/2 -10);
	this->addChild(vida, 1);

	sinvida = Sprite::create("icon_sinvida.png");
	sinvida->setScaleX(0);
	sinvida->setPositionX(vida->getBoundingBox().size.width/2 +(74*(1-sinvida->getScaleX())) +21 +10);
	sinvida->setPositionY(640 -vida->getBoundingBox().size.height/2 -10);
	this->addChild(sinvida, 1);

	resource = Sprite::create("resource.png");
	resource->setScaleX(0.3);
	resource->setScaleY(0.3);
	resource->setPositionX(resource->getBoundingBox().size.width/2 +20);
	resource->setPositionY(640 -resource->getBoundingBox().size.height/2 -70);
	this->addChild(resource, 1);

	resources_label = Label::createWithTTF("0","fonts/Volkoff.otf", 32);
	resources_label->setColor(Color3B(255, 255, 255));
    resources_label->setPosition(Vec2(resource->getPositionX() +resource->getBoundingBox().size.width/2 + resources_label->getBoundingBox().size.width/2 +10, resource->getPositionY()));
    this->addChild(resources_label, 1);

	auto cara = Sprite::create("icon_cara.png");
	cara->setPositionX(cara->getBoundingBox().size.width/2 +10);
	cara->setPositionY(640 -cara->getBoundingBox().size.height/2 -10);
	this->addChild(cara, 1);


	icon_dash = Sprite::create("icon_dash.png");
	icon_dash->setPositionX(icon_dash->getBoundingBox().size.width/2 +10);
	icon_dash->setPositionY(icon_dash->getBoundingBox().size.height/2 +10);
	icon_dash->setVisible(true);
	this->addChild(icon_dash, 1);

	icon_tower = Sprite::create("icon_tower.png");
	icon_tower->setPositionX(icon_tower->getBoundingBox().size.width/2 +10);
	icon_tower->setPositionY(icon_tower->getBoundingBox().size.height/2 +10);
	icon_tower->setVisible(false);
	this->addChild(icon_tower, 1);

	icon_slow = Sprite::create("icon_slow.png");
	icon_slow->setPositionX(icon_slow->getBoundingBox().size.width/2 +10);
	icon_slow->setPositionY(icon_slow->getBoundingBox().size.height/2 +10);
	icon_slow->setVisible(false);
	this->addChild(icon_slow, 1);

	icon_monster = Sprite::create("icon_monster.png");
	icon_monster->setPositionX(icon_monster->getBoundingBox().size.width/2 +10);
	icon_monster->setPositionY(icon_monster->getBoundingBox().size.height/2 +10);
	icon_monster->setVisible(false);
	this->addChild(icon_monster, 1);


	gun_normal = Sprite::create("gun_normal.png");
	gun_normal->setPositionX(960 -gun_normal->getBoundingBox().size.width/2 -10);
	gun_normal->setPositionY(gun_normal->getBoundingBox().size.height/2 +10);
	gun_normal->setVisible(true);
	this->addChild(gun_normal, 1);

	gun_fire = Sprite::create("gun_fire.png");
	gun_fire->setPositionX(960 -gun_fire->getBoundingBox().size.width/2 -10);
	gun_fire->setPositionY(gun_fire->getBoundingBox().size.height/2 +10);
	gun_fire->setVisible(false);
	this->addChild(gun_fire, 1);

	gun_air = Sprite::create("gun_air.png");
	gun_air->setPositionX(960 -gun_air->getBoundingBox().size.width/2 -10);
	gun_air->setPositionY(gun_air->getBoundingBox().size.height/2 +10);
	gun_air->setVisible(false);
	this->addChild(gun_air, 1);

	bar_back = Sprite::create("bar_back.png");
	bar_back->setPositionX(960 - bar_back->getBoundingBox().size.width / 2 - 30);
	bar_back->setPositionY(bar_back->getBoundingBox().size.height / 2 + 30);
	this->addChild(bar_back, 1);

	bar = Sprite::create("bar.png");
	bar->setPositionX(960 - bar->getBoundingBox().size.width / 2 - 30);
	bar->setPositionY(bar->getBoundingBox().size.height / 2 + 30);
	this->addChild(bar, 1);



	dialog_box = Sprite::create("dialog_box.png");
	dialog_box->setPositionX(960/2);
	dialog_box->setPositionY(dialog_box->getBoundingBox().size.height/2 +10);
	this->addChild(dialog_box, 1);
	dialog_box->setVisible(false);

	//dialog_label = Label::createWithBMFont("Prueba", "fonts/konqa32.fnt");
	dialog_label = Label::createWithTTF("Prueba","fonts/Volkoff.otf", 32);
	dialog_label->setColor(Color3B(0, 0, 0));
    dialog_label->setPosition(Vec2(visibleSize.width/2, dialog_box->getPositionY()));
    this->addChild(dialog_label, 1);

	Dialog* dialog_1 = new Dialog("Hi! Welcome to Feral Sands!");

	Dialog* dialog_2 = new Dialog("You can move around with the left joystick");
	dialog_1->_nextDialog = dialog_2;

	Dialog* dialog_3 = new Dialog("or using WASD if you don't have a gamepad");
	dialog_2->_nextDialog = dialog_3;


	active_dialog = dialog_1;


	CCAnimation * anim = CCAnimation::create();
	anim->addSpriteFrameWithFileName("button_a_01.png");
	anim->addSpriteFrameWithFileName("button_a_02.png");
	anim->setLoops(-1); // for infinit loop animation
    anim->setDelayPerUnit(0.3f);

	button_a = Sprite::create("button_a_01.png");
	button_a->setPositionX(960 -button_a->getBoundingBox().size.width/2 -42);
	button_a->setPositionY(button_a->getBoundingBox().size.height/2 +15);
	this->addChild(button_a, 1);
	button_a->runAction(CCAnimate::create(anim));
	button_a->setVisible(false);

	CCAnimation * anim2 = CCAnimation::create();
	anim2->addSpriteFrameWithFileName("button_enter_01.png");
	anim2->addSpriteFrameWithFileName("button_enter_02.png");
	anim2->setLoops(-1); // for infinit loop animation
    anim2->setDelayPerUnit(0.3f);

	button_enter = Sprite::create("button_enter_01.png");
	button_enter->setPositionX(960 -button_enter->getBoundingBox().size.width/2 -42);
	button_enter->setPositionY(button_enter->getBoundingBox().size.height/2 +25);
	this->addChild(button_enter, 1);
	button_enter->runAction(CCAnimate::create(anim2));
	button_enter->setVisible(false);


	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::keyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = [=](Event* event){
        auto mouse = (EventMouse*)event;
		mouse_position = Vec2(mouse->getCursorX(), mouse->getCursorY());
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	
	

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
		if (nexus->_life < 0) { nexus->_life = 0; }
		if (nexus->_life == 0) {
			nexus->_sprite->setColor(Color3B(200, 0, 0));
		}
	});

	_eventDispatcher->addCustomEventListener("enemy_dead", [=](EventCustom* event){
		dead_enemies++;
	});


	
	auto floor = Sprite3D::create("Floor.obj", "sand.png");
	floor->setScale(floorSize);
	Vec3 corners_floor[8] = {};
	floor->getAABB().getCorners(corners_floor);
	floor->setPosition3D(Vec3(0, 0, -1));
	floor->setRotation3D(Vec3(90, 0, 0));
	floor->setCameraMask(2);
	this->addChild(floor, 0);

	auto walls = Sprite3D::create("Mountains.obj", "MountainsText.png");
	walls->setScale(100 * (floorSize / 2048));
	walls->setRotation3D(Vec3(90, 0, 0));
	walls->setCameraMask(2);
	this->addChild(walls, 0);

	/*
	auto lake = Sprite3D::create("Lake.obj");
	lake->setScale(100 * (floorSize / 2048));
	lake->setRotation3D(Vec3(90, 0, 0));
	lake->setPosition3D(Vec3(-5*(floorSize/2048), -520*(floorSize/2048), 0));
	lake->setCameraMask(2);
	this->addChild(lake, 0);
	*/
	
	Point p = Point(0, 0);

	boss = new Player(floorSize, p);
	mobile_objects [num_mobile_objects] = boss;
	boss->_num_in_array = num_mobile_objects;
	num_mobile_objects++;
	boss->_sprite->setCameraMask(2);
	this->addChild(boss->_sprite, 0);

	green_tower = Sprite3D::create("Tower.obj", "stone.png");
	green_tower->setScale(12*(floorSize/2048));
	green_tower->setCameraMask(2);
	green_tower->setColor(ccc3(0, 200, 0));
	green_tower->setVisible(false);
	this->addChild(green_tower, 0);

	green_slow = Sprite3D::create("Floor.obj", "alquitran.png");
	green_slow->setScale(30*(floorSize/2048));
	green_slow->setCameraMask(2);
	green_slow->setColor(ccc3(0, 200, 0));
	green_slow->setVisible(false);
	this->addChild(green_slow, 0);

	green_monster = Sprite3D::create("Floor.obj", "monster.png");
	green_monster->setScale(30*(floorSize/2048));
	green_monster->setCameraMask(2);
	green_monster->setColor(ccc3(0, 200, 0));
	green_monster->setVisible(false);
	this->addChild(green_monster, 0);
	
	// ESTO NO FUNCIONA, TENGO QUE FABRICARME MI PROPIA CLASE PARA CREAR BEZIERS QUADRATICAS, USANDO LA FUNCION AQUELLA GUAY
	// SERA UNA CLASE SIMPLE QUE SOLAMENTE TIENE 3 PARÁMETROS; PUNTO INICIAl, CONTROl POINT y PUNTO FINAL

	/*
	ccBezierConfig bezier;
	bezier.controlPoint_1 = Point(-1650, -500);
	bezier.endPosition = Point(-1300, 0);
	*/

<<<<<<< HEAD
	QuadBezier* q = new QuadBezier(Point(-400*(floorSize/2048), 0), Point(-330*(floorSize/2048), -200*(floorSize/2048)), Point(-260*(floorSize/2048), 0));
=======
	Atrezzo* ruin = new Atrezzo(floorSize, Point(30*(floorSize/2048), -100*(floorSize/2048)), "ruin");
	static_objects [num_static_objects] = ruin;
	num_static_objects++;
	ruin->_sprite->setCameraMask(2);
	this->addChild(ruin->_sprite, 1);
	rotateToPoint(ruin->_sprite, Point(0, 0));
	ruin->_sprite->setRotation3D(Vec3(90, 0, ruin->_sprite->getRotation3D().z +180));

	ruin = new Atrezzo(floorSize, Point(-90*(floorSize/2048), -55*(floorSize/2048)), "ruin");
	static_objects [num_static_objects] = ruin;
	num_static_objects++;
	ruin->_sprite->setCameraMask(2);
	this->addChild(ruin->_sprite, 1);
	rotateToPoint(ruin->_sprite, Point(0, 0));
	ruin->_sprite->setRotation3D(Vec3(90, 0, ruin->_sprite->getRotation3D().z +180));

	ruin = new Atrezzo(floorSize, Point(-90*(floorSize/2048), 55*(floorSize/2048)), "ruin");
	static_objects [num_static_objects] = ruin;
	num_static_objects++;
	ruin->_sprite->setCameraMask(2);
	this->addChild(ruin->_sprite, 1);
	rotateToPoint(ruin->_sprite, Point(0, 0));
	ruin->_sprite->setRotation3D(Vec3(90, 0, ruin->_sprite->getRotation3D().z +180));

	ruin = new Atrezzo(floorSize, Point(-10*(floorSize/2048), 100*(floorSize/2048)), "ruin");
	static_objects [num_static_objects] = ruin;
	num_static_objects++;
	ruin->_sprite->setCameraMask(2);
	this->addChild(ruin->_sprite, 1);
	rotateToPoint(ruin->_sprite, Point(0, 0));
	ruin->_sprite->setRotation3D(Vec3(90, 0, ruin->_sprite->getRotation3D().z +180));

	ruin = new Atrezzo(floorSize, Point(90*(floorSize/2048), 55*(floorSize/2048)), "ruin");
	static_objects [num_static_objects] = ruin;
	num_static_objects++;
	ruin->_sprite->setCameraMask(2);
	this->addChild(ruin->_sprite, 1);
	rotateToPoint(ruin->_sprite, Point(0, 0));
	ruin->_sprite->setRotation3D(Vec3(90, 0, ruin->_sprite->getRotation3D().z +180));

	ruin = new Atrezzo(floorSize, Point(110*(floorSize/2048), -50*(floorSize/2048)), "ruin");
	static_objects [num_static_objects] = ruin;
	num_static_objects++;
	ruin->_sprite->setCameraMask(2);
	this->addChild(ruin->_sprite, 1);
	rotateToPoint(ruin->_sprite, Point(0, 0));
	ruin->_sprite->setRotation3D(Vec3(90, 0, ruin->_sprite->getRotation3D().z +180));

	// PATHSTONES, EMPIEZA POR LA DE LA IZQUIERDA DEL TODO Y SIGUE EN SENTIDO DE LAS AGUJAS DEL RELOJ

	Atrezzo* gate = new Atrezzo(floorSize, Point(-940*(floorSize/2048), -20*(floorSize/2048)), "gate");
	static_objects [num_static_objects] = gate;
	num_static_objects++;
	gate->_sprite->setCameraMask(2);
	this->addChild(gate->_sprite, 1);
	gate->_sprite->setRotation3D(Vec3(90, 0, 140));

	QuadBezier* q = new QuadBezier(Point(-900*(floorSize/2048), 0), Point(-750*(floorSize/2048), 100*(floorSize/2048)), Point(-600*(floorSize/2048), 0));
>>>>>>> origin/master

	PathStone* path = new PathStone(floorSize, 10, q);
	this->addChild(path->getLayer());
	active_pathstones[num_active_pathstones] = path;
	num_active_pathstones++;


	q = new QuadBezier(Point(-260*(floorSize/2048), 0), Point(-200*(floorSize/2048), 200*(floorSize/2048)), Point(-140*(floorSize/2048), 0));

	PathStone* path2 = new PathStone(floorSize, 15, q);
	this->addChild(path2->getLayer());
	active_pathstones[num_active_pathstones] = path2;
	num_active_pathstones++;

	q = new QuadBezier(Point(-140*(floorSize/2048), 0), Point(-70*(floorSize/2048), -200*(floorSize/2048)), Point(0, 0));

	PathStone* path3 = new PathStone(floorSize, 6, q);
	this->addChild(path3->getLayer());
	active_pathstones[num_active_pathstones] = path3;
	num_active_pathstones++;
	
	path->_nextPath = path2;
	path2->_nextPath = path3;
<<<<<<< HEAD
	

=======




	gate = new Atrezzo(floorSize, Point(-360*(floorSize/2048), 840*(floorSize/2048)), "gate");
	static_objects [num_static_objects] = gate;
	num_static_objects++;
	gate->_sprite->setCameraMask(2);
	this->addChild(gate->_sprite, 1);
	gate->_sprite->setRotation3D(Vec3(90, 0, 310));
	
	q = new QuadBezier(Point(-380*(floorSize/2048), 800*(floorSize/2048)), Point(-520*(floorSize/2048), 600*(floorSize/2048)), Point(-290*(floorSize/2048), 575*(floorSize/2048)));

	PathStone* path11 = new PathStone(floorSize, 8, q);
	this->addChild(path11->getLayer());
	active_pathstones[num_active_pathstones] = path11;
	num_active_pathstones++;

	q = new QuadBezier(Point(-290*(floorSize/2048), 575*(floorSize/2048)), Point(-30*(floorSize/2048), 500*(floorSize/2048)), Point(-100*(floorSize/2048), 350*(floorSize/2048)));

	PathStone* path12 = new PathStone(floorSize, 7, q);
	this->addChild(path12->getLayer());
	active_pathstones[num_active_pathstones] = path12;
	num_active_pathstones++;

	q = new QuadBezier(Point(-100*(floorSize/2048), 350*(floorSize/2048)), Point(-200*(floorSize/2048), 250*(floorSize/2048)), Point(0, 0));

	PathStone* path13 = new PathStone(floorSize, 9, q);
	this->addChild(path13->getLayer());
	active_pathstones[num_active_pathstones] = path13;
	num_active_pathstones++;

	path11->_nextPath = path12;
	path12->_nextPath = path13;
	
	

	gate = new Atrezzo(floorSize, Point(435*(floorSize/2048), 765*(floorSize/2048)), "gate");
	static_objects [num_static_objects] = gate;
	num_static_objects++;
	gate->_sprite->setCameraMask(2);
	this->addChild(gate->_sprite, 1);
	gate->_sprite->setRotation3D(Vec3(90, 0, 310));

	q = new QuadBezier(Point(410*(floorSize/2048), 730*(floorSize/2048)), Point(350*(floorSize/2048), 625*(floorSize/2048)), Point(400*(floorSize/2048), 500*(floorSize/2048)));

	PathStone* path21 = new PathStone(floorSize, 7, q);
	this->addChild(path21->getLayer());
	active_pathstones[num_active_pathstones] = path21;
	num_active_pathstones++;

	q = new QuadBezier(Point(400*(floorSize/2048), 500*(floorSize/2048)), Point(400*(floorSize/2048), 330*(floorSize/2048)), Point(250*(floorSize/2048), 330*(floorSize/2048)));

	PathStone* path22 = new PathStone(floorSize, 7, q);
	this->addChild(path22->getLayer());
	active_pathstones[num_active_pathstones] = path22;
	num_active_pathstones++;

	q = new QuadBezier(Point(250*(floorSize/2048), 330*(floorSize/2048)), Point(100*(floorSize/2048), 230*(floorSize/2048)), Point(0, 0));

	PathStone* path23 = new PathStone(floorSize, 12, q);
	this->addChild(path23->getLayer());
	active_pathstones[num_active_pathstones] = path23;
	num_active_pathstones++;

	path21->_nextPath = path22;
	path22->_nextPath = path23;



	gate = new Atrezzo(floorSize, Point(900*(floorSize/2048), 20*(floorSize/2048)), "gate");
	static_objects [num_static_objects] = gate;
	num_static_objects++;
	gate->_sprite->setCameraMask(2);
	this->addChild(gate->_sprite, 1);
	gate->_sprite->setRotation3D(Vec3(90, 0, -40));

	q = new QuadBezier(Point(870*(floorSize/2048), -5*(floorSize/2048)), Point(800*(floorSize/2048), -100*(floorSize/2048)), Point(700*(floorSize/2048), 0));

	PathStone* path31 = new PathStone(floorSize, 6, q);
	this->addChild(path31->getLayer());
	active_pathstones[num_active_pathstones] = path31;
	num_active_pathstones++;

	q = new QuadBezier(Point(700*(floorSize/2048), 0), Point(500*(floorSize/2048), 200*(floorSize/2048)), Point(300*(floorSize/2048), 50*(floorSize/2048)));

	PathStone* path32 = new PathStone(floorSize, 12, q);
	this->addChild(path32->getLayer());
	active_pathstones[num_active_pathstones] = path32;
	num_active_pathstones++;

	q = new QuadBezier(Point(300*(floorSize/2048), 50*(floorSize/2048)), Point(200*(floorSize/2048), -50*(floorSize/2048)), Point(0, 0));

	PathStone* path33 = new PathStone(floorSize, 8, q);
	this->addChild(path33->getLayer());
	active_pathstones[num_active_pathstones] = path33;
	num_active_pathstones++;

	path31->_nextPath = path32;
	path32->_nextPath = path33;


	gate = new Atrezzo(floorSize, Point(500*(floorSize/2048), -750*(floorSize/2048)), "gate");
	static_objects [num_static_objects] = gate;
	num_static_objects++;
	gate->_sprite->setCameraMask(2);
	this->addChild(gate->_sprite, 1);
	gate->_sprite->setRotation3D(Vec3(90, 0, 90));

	q = new QuadBezier(Point(500*(floorSize/2048), -700*(floorSize/2048)), Point(650*(floorSize/2048), -500*(floorSize/2048)), Point(400*(floorSize/2048), -300*(floorSize/2048)));

	PathStone* path41 = new PathStone(floorSize, 12, q);
	this->addChild(path41->getLayer());
	active_pathstones[num_active_pathstones] = path41;
	num_active_pathstones++;

	q = new QuadBezier(Point(400*(floorSize/2048), -300*(floorSize/2048)), Point(310*(floorSize/2048), -230*(floorSize/2048)), Point(280*(floorSize/2048), -350*(floorSize/2048)));

	PathStone* path42 = new PathStone(floorSize, 4, q);
	this->addChild(path42->getLayer());
	active_pathstones[num_active_pathstones] = path42;
	num_active_pathstones++;

	q = new QuadBezier (Point(280*(floorSize/2048), -350*(floorSize/2048)), Point(200*(floorSize/2048), -470*(floorSize/2048)), Point(100*(floorSize/2048), -380*(floorSize/2048)));

	PathStone* path43 = new PathStone(floorSize, 4, q);
	this->addChild(path43->getLayer());
	active_pathstones[num_active_pathstones] = path43;
	num_active_pathstones++;

	q = new QuadBezier (Point(100*(floorSize/2048), -380*(floorSize/2048)), Point(40*(floorSize/2048), -330*(floorSize/2048)), Point(130*(floorSize/2048), -280*(floorSize/2048)));

	PathStone* path44 = new PathStone(floorSize, 3, q);
	this->addChild(path44->getLayer());
	active_pathstones[num_active_pathstones] = path44;
	num_active_pathstones++;

	q = new QuadBezier (Point(130*(floorSize/2048), -280*(floorSize/2048)), Point(190*(floorSize/2048), -130*(floorSize/2048)), Point(0, 0));

	PathStone* path45 = new PathStone(floorSize, 8, q);
	this->addChild(path45->getLayer());
	active_pathstones[num_active_pathstones] = path45;
	num_active_pathstones++;


	path41->_nextPath = path42;
	path42->_nextPath = path43;
	path43->_nextPath = path44;
	path44->_nextPath = path45;




	gate = new Atrezzo(floorSize, Point(-380*(floorSize/2048), -830*(floorSize/2048)), "gate");
	static_objects [num_static_objects] = gate;
	num_static_objects++;
	gate->_sprite->setCameraMask(2);
	this->addChild(gate->_sprite, 1);
	gate->_sprite->setRotation3D(Vec3(90, 0, 90));

	q = new QuadBezier(Point(-380*(floorSize/2048), -780*(floorSize/2048)), Point(-520*(floorSize/2048), -500*(floorSize/2048)), Point(-290*(floorSize/2048), -325*(floorSize/2048)));

	PathStone* path51 = new PathStone(floorSize, 15, q);
	this->addChild(path51->getLayer());
	active_pathstones[num_active_pathstones] = path51;
	num_active_pathstones++;

	q = new QuadBezier(Point(-290*(floorSize/2048), -325*(floorSize/2048)), Point(-50*(floorSize/2048), -200*(floorSize/2048)), Point(0, 0));

	PathStone* path52 = new PathStone(floorSize, 12, q);
	this->addChild(path52->getLayer());
	active_pathstones[num_active_pathstones] = path52;
	num_active_pathstones++;

	path51->_nextPath = path52;

	// WAVES

>>>>>>> origin/master
	Wave* w = new Wave(floorSize, path, boss);
	w->addEnemy("grunt", 1.5);
	w->addEnemy("dog", 1);
	w->addEnemy("tank", 1);
	w->addEnemy("ghost", 1);
	w->addEnemy("grunt", 20);
	w->addEnemy("grunt", 2);
	w->addEnemy("grunt", 2);
	w->addEnemy("grunt", 2);
	w->addEnemy("grunt", 2);
	w->addEnemy("grunt", 2);
	total_enemies += w->num_enemies;
	w->_active = true;

	p = Point(0, 0);

	nexus = new Nexus(floorSize, p);
	static_objects [num_static_objects] = nexus;
	num_static_objects++;
	nexus->_sprite->setCameraMask(2);
	this->addChild(nexus->_sprite, 1);
	/*
	Atrezzo* a;
	a = new Atrezzo(Point(300, 200), "rock");
	static_objects [num_static_objects] = a;
	num_static_objects++;
	a->_sprite->setCameraMask(2);
	this->addChild(a->_sprite, 1);
	*/

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
	
	// EXPERIMENTOS AL LEER UNA IMAGEN
	readMapFromFile("sourceMap.png");

	
	

	/*
	auto directionalLight = DirectionLight::create(Vec3(-1.0f, -1.0f, 0.0f), Color3B(200, 200, 200));
	directionalLight->setLightFlag(LightFlag::LIGHT1);
	this->addChild(directionalLight);
	*/

	//now the bezier config declaration

	//SET BACKGROUND MUSIC
	// La background music al usarse junto a efectos de sonido da lagazos del copón
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sandstorm.wav", true);

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

	if (paused) { // ESTA PAUSADO

<<<<<<< HEAD
=======
		EventCustom eventVisible("checkVisible");
		eventVisible.setUserData(new Point(boss->_sprite->getPositionX(), boss->_sprite->getPositionY()));
		_eventDispatcher->dispatchEvent(&eventVisible);

		stop_label->setVisible(true);

>>>>>>> origin/master
		if (dwResult == ERROR_SUCCESS) { // Controller is connected 

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
		}
		else { // Controller is not connected

		}

	}
	else { // NO ESTA PAUSADO
		if (active_dialog != NULL) { // HAY UN DIALOGO ACTIVO

			dialog_box->setVisible(true);
			if (dialog_label->getString() != active_dialog->_text) {
				dialog_label->setString(active_dialog->_text);
			}
			dialog_label->setVisible(true);

<<<<<<< HEAD
=======
			stop_label->setVisible(false);

			EventCustom eventVisible("checkVisible");
			eventVisible.setUserData(new Point(boss->_sprite->getPositionX(), boss->_sprite->getPositionY()));
			_eventDispatcher->dispatchEvent(&eventVisible);

>>>>>>> origin/master
			if (dwResult == ERROR_SUCCESS) { // Controller is connected 

				button_a->setVisible(true);
				button_enter->setVisible(false);

				WORD wButtons = state.Gamepad.wButtons;

				if (wButtons & XINPUT_GAMEPAD_A) {
					if (!aPushed) {
						active_dialog = active_dialog->_nextDialog;
					}
					aPushed = true;
				}
				else {
					aPushed = false;
				}
			}
			else { // Controller is not connected

				button_a->setVisible(false);
				button_enter->setVisible(true);

				if (pressed_ENTER_PUSHED) {
					active_dialog = active_dialog->_nextDialog;
				}

				pressed_SPACE_PUSHED = false;
				pressed_ENTER_PUSHED = false;

			}

			camera->setRotation3D(Vec3(cameraAngle, 0, 0));
			camera->setPosition3D(Vec3(boss->_sprite->getPositionX(), boss->_sprite->getPositionY() - sin(cameraAngle*(2*M_PI)/360)*zoom, boss->_sprite->getPositionZ() + cos(cameraAngle*(2*M_PI)/360)*zoom ));

		}
		else { // NO HAY NINGUN DIALOGO ACTIVO Y NO ESTA PAUSADO

			top_label->setVisible(true);
			std::string s_aux = std::to_string(nexus->_life) + "/5";
			top_label->setString(s_aux);
<<<<<<< HEAD
=======

			stop_label->setVisible(false);

>>>>>>> origin/master
			s_aux = std::to_string(resources);
			resources_label->setString(s_aux);
			resources_label->setPosition(Vec2(resource->getPositionX() +resource->getBoundingBox().size.width/2 + resources_label->getBoundingBox().size.width/2 +10, resource->getPositionY()));
			dialog_box->setVisible(false);
			dialog_label->setVisible(false);
			button_a->setVisible(false);
			button_enter->setVisible(false);

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

			sinvida->setScaleX((200 -boss->_health)/200);
			sinvida->setPositionX(vida->getBoundingBox().size.width/2 +(74*(1-sinvida->getScaleX())) +21 +10);

			player_arrow->setPositionX(960 -minimapa->getBoundingBox().size.width/2 -16 +(boss->_sprite->getPositionX()/(floorSize/2))*(128/2));
			player_arrow->setPositionY(640 -minimapa->getBoundingBox().size.height/2 -16 +(boss->_sprite->getPositionY()/(floorSize/2))*(128/2));
			player_arrow->setRotation(boss->_sprite->getRotation3D().z);

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

					if (state.Gamepad.bLeftTrigger > 50) {
						if (!leftTriggerPushed && menuTurrets) {

							if (green_tower->isVisible()) {

								if (green_tower->getColor().r == 200) {

								}
								else if (green_tower->getColor().g == 200) {

									Point p = Point(boss->_sprite->getPositionX() + (rightThumbX/500)*(floorSize/2048), boss->_sprite->getPositionY() + (rightThumbY/500)*(floorSize/2048));

									Tower* t = new Tower(floorSize, "standard", p);
									t->_sprite->setRotation3D(boss->_sprite->getRotation3D());
									static_objects[num_static_objects] = t;
									num_static_objects++;
									t->_sprite->setCameraMask(2);
									this->addChild(t->_sprite, 1);

								}

							}
							else if (green_slow->isVisible()) {

								if (green_slow->getColor().r == 200) {

								}
								else if (green_slow->getColor().g == 200) {

									Point p = Point(boss->_sprite->getPositionX() + (rightThumbX/500)*(floorSize/2048), boss->_sprite->getPositionY() + (rightThumbY/500)*(floorSize/2048));

									Tower* t = new Tower(floorSize, "slow", p);
									t->_sprite->setRotation3D(boss->_sprite->getRotation3D());
									static_objects[num_static_objects] = t;
									num_static_objects++;
									t->_sprite->setCameraMask(2);
									this->addChild(t->_sprite, 1);

								}

							}
							else if (green_monster->isVisible()) {

								if (green_monster->getColor().r == 200) {

								}
								else if (green_monster->getColor().g == 200) {

									Point p = Point(boss->_sprite->getPositionX() + (rightThumbX/500)*(floorSize/2048), boss->_sprite->getPositionY() + (rightThumbY/500)*(floorSize/2048));

									Tower* t = new Tower(floorSize, "monster", p);
									t->_sprite->setRotation3D(boss->_sprite->getRotation3D());
									static_objects[num_static_objects] = t;
									num_static_objects++;
									t->_sprite->setCameraMask(2);
									this->addChild(t->_sprite, 1);

								}

							}

						}
						else if (!leftTriggerPushed && !menuTurrets && boss->dashing == 0 && (state.Gamepad.sThumbLX != 0 || state.Gamepad.sThumbLY != 0) && !boss->_resurrect) {

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
					if (boss->dashing == 0 && !boss->_resurrect) {
						boss->_sprite->setPosition3D(boss->_sprite->getPosition3D() + Vec3(state.Gamepad.sThumbLX*dt*boss->speed / 70, state.Gamepad.sThumbLY*dt*boss->speed / 70, 0));
					}


					if (wButtons & XINPUT_GAMEPAD_A)
						//boss->_sprite->setPosition3D(Vec3(800 / 2 + (rand() % 2) - 1 * rand() % 1 * 800 / 2, 600 / 2 + (rand() % 2) - 1 * rand() % 1 * 600 / 2, 100));
						boss->_sprite->setPosition3D(Vec3(0, 0, boss->_sprite->getPositionZ()));


					// CHANGE WEAPON
					if (wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
						if (!rightShoulderPushed) {
							boss->_weapon += 1;
							if (boss->_weapon == 3) boss->_weapon = 0;

							if (boss->_weapon == 0) {
								gun_normal->setVisible(true);
								gun_fire->setVisible(false);
								gun_air->setVisible(false);
							}
							else if (boss->_weapon == 1) {
								gun_normal->setVisible(false);
								gun_fire->setVisible(true);
								gun_air->setVisible(false);
							}
							else if (boss->_weapon == 2) {
								gun_normal->setVisible(false);
								gun_fire->setVisible(false);
								gun_air->setVisible(true);
							}
						}
						rightShoulderPushed = true;
					}
					else {
						rightShoulderPushed = false;
					}


					// ROTACION DE PLAYER
					if (state.Gamepad.sThumbRY != 0) rightThumbY = state.Gamepad.sThumbRY;
					if (state.Gamepad.sThumbRX != 0) rightThumbX = state.Gamepad.sThumbRX;

					boss->_sprite->setRotation3D(Vec3(90, 0, -90 - atan2(rightThumbY, rightThumbX) * 360 / (2 * M_PI)));

					// DISPARO
					if (state.Gamepad.bRightTrigger != 0) {
						if (boss->_weapon == 0 && !boss->_resurrect){ //NORMAL
							if (coolDownNow >= coolDownMax && boss->energyN >= 2*2) {
								boss->normalShooting = true;
								boss->energyN -= 2;
								coolDownNow = state.Gamepad.bRightTrigger / 255 * coolDownMax / 2;
								CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("shoot.wav");
								WeaponShot* _shotInstance = new WeaponShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D());
								addMobileObject(_shotInstance);
							}
						}
						else if (boss->_weapon == 1 && !boss->_resurrect){ // FUEGO
							if (coolDownFireNow >= coolDownMax && boss->energyF >= 5*2){
								boss->fireShooting = true;
								boss->energyF -= 5;
								//coolDownFireNow = state.Gamepad.bRightTrigger / 255 * coolDownMax / 2;
								coolDownFireNow = 0.14;
								CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("shoot.wav");

								Vec3 _playerMovement = Vec3(state.Gamepad.sThumbLX / 70, state.Gamepad.sThumbLY / 70, 0);

								FireShot* _fireInstance = new FireShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, -14 + (rand() % 14) - 7));
								//_playerMovement = Vec3(_playerMovement.x * _fireInstance->_direction.x, _playerMovement.y * _fireInstance->_direction.y, 0);
								_fireInstance->_displacement = _playerMovement;
								addMobileObject(_fireInstance);

								_fireInstance = new FireShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, (rand() % 14) - 7));
								//_playerMovement = Vec3(_playerMovement.x * _fireInstance->_direction.x, _playerMovement.y * _fireInstance->_direction.y, 0);
								_fireInstance->_displacement = _playerMovement;
								addMobileObject(_fireInstance);

								_fireInstance = new FireShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 14 + (rand() % 14) - 7));
								//_playerMovement = Vec3(_playerMovement.x * _fireInstance->_direction.x, _playerMovement.y * _fireInstance->_direction.y, 0);
								_fireInstance->_displacement = _playerMovement;
								addMobileObject(_fireInstance);
							}
						}
						else if (boss->_weapon == 2 && !boss->_resurrect){ //AIRE
							if (coolDownAirNow >= coolDownMax){
								boss->airCharging = true;
								if (airPower < 5 && boss->energyA >= (log(airPower + 0.6) * 4 + 1) * 10 * 2.5) airPower += dt;
							}

						}

						if (boss->_weapon != 0) boss->normalShooting = false;
						else if (boss->_weapon != 1) boss->fireShooting = false;
						else if (boss->_weapon != 2) {
							boss->airCharging = false;
							airPower = 0;
						}
					}

					if (state.Gamepad.bRightTrigger == 0) {
						boss->normalShooting = false;
						boss->fireShooting = false;
						if (boss->_weapon == 2 && !boss->_resurrect){ //AIRE
							if (boss->airCharging){

								airPower = log(airPower + 0.6) * 4 + 1;
								boss->energyA -= airPower * 10 * 2.5;
								if (airPower >= 3.99) airPower = 8;

								boss->airCharging = false;
								coolDownAirNow = 0;

								CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("shoot.wav");


								AirShot* _airInstance;

								if (airPower == 8){
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, -30 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);

									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, -12 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, -6 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 0 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 6 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 12 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
								}

								if (airPower >= 3){
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, -24 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);

									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, -12 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, -6 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 0 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 6 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 12 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);

								}

								if (airPower >= 2){
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, -18 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);

									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, -12 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, -6 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 0 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 6 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 12 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
								}

								_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, -12 + (rand() % 6) - 3), airPower);
								addMobileObject(_airInstance);
								_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, -6 + (rand() % 6) - 3), airPower);
								addMobileObject(_airInstance);
								_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 0 + (rand() % 6) - 3), airPower);
								addMobileObject(_airInstance);
								_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 6 + (rand() % 6) - 3), airPower);
								addMobileObject(_airInstance);
								_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 12 + (rand() % 6) - 3), airPower);
								addMobileObject(_airInstance);

								if (airPower >= 2){
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 18 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);

									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, -12 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, -6 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 0 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 6 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 12 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
								}

								if (airPower >= 3){
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 24 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);

									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, -12 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, -6 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 0 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 6 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 12 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
								}

								if (airPower == 8) {
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 30 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);

									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, -12 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, -6 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 0 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 6 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
									_airInstance = new AirShot(floorSize, boss->_sprite->getPosition3D(), boss->_sprite->getRotation3D() + Vec3(0, 0, 12 + (rand() % 6) - 3), airPower);
									addMobileObject(_airInstance);
								}


								airPower = 0;
							}
						}
					}

					// BARRA ENERGÍA ARMAS
					if (boss->_weapon == 0){
						bar->setScaleX(boss->energyN / 100);
						bar->setColor(ccc3(200, 200, 0));
					}
					else if (boss->_weapon == 1) {
						bar->setScaleX(boss->energyF / 100);
						bar->setColor(ccc3(200, 0, 0));
					}
					else if (boss->_weapon == 2) {
						bar->setScaleX(boss->energyA / 100);
						bar->setColor(ccc3(0, 200, 200));
					}

					// ROTAR CAMARA
					/*
					if (wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) cameraAngle += 0.1;
					if (wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) cameraAngle -= 0.1;
					*/
					camera->setRotation3D(Vec3(cameraAngle, 0, 0));

					// MENU DE TORRETAS
					if (wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {

						if (!leftShoulderPushed) {

							if (!menuTurrets) {
								menuTurrets = true;
								green_tower->setVisible(true);

								icon_dash->setVisible(false);
								icon_tower->setVisible(true);
								icon_slow->setVisible(false);
								icon_monster->setVisible(false);
							}
							else if (menuTurrets && green_tower->isVisible()) {
								green_tower->setVisible(false);
								green_slow->setVisible(true);

								icon_dash->setVisible(false);
								icon_tower->setVisible(false);
								icon_slow->setVisible(true);
								icon_monster->setVisible(false);
							}
							else if (menuTurrets && green_slow->isVisible()) {
								green_slow->setVisible(false);
								green_monster->setVisible(true);

								icon_dash->setVisible(false);
								icon_tower->setVisible(false);
								icon_slow->setVisible(false);
								icon_monster->setVisible(true);
							}
							else {
								green_monster->setVisible(false);
								menuTurrets = false;

								icon_dash->setVisible(true);
								icon_tower->setVisible(false);
								icon_slow->setVisible(false);
								icon_monster->setVisible(false);
							}

							/*
							menuTurrets = !menuTurrets;
							if (menuTurrets) {
							green_tower->setVisible(true);
							}
							else {
							green_tower->setVisible(false);
							}
							*/

						}

						leftShoulderPushed = true;

					}

					else {

						leftShoulderPushed = false;

					}

					if (wButtons & XINPUT_GAMEPAD_DPAD_UP) zoom -= 5;
					if (wButtons & XINPUT_GAMEPAD_DPAD_DOWN) zoom += 5;



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

				Vec2 virtual_vec = Vec2(0, 0);

				if (pressed_W || pressed_UP) {
					virtual_vec.y -= 1;
				}
				if (pressed_S || pressed_DOWN) {
					virtual_vec.y += 1;
				}
				if (pressed_A || pressed_LEFT) {
					virtual_vec.x -= 1;
				}
				if (pressed_D || pressed_RIGHT) {
					virtual_vec.x += 1;
				}
				virtual_vec.normalize();

				// CONTROLA EL MOVIMIENTO
				if (boss->dashing == 0 && !boss->_resurrect) {
						boss->_sprite->setPosition3D(boss->_sprite->getPosition3D() + Vec3(virtual_vec.x*32767*dt*boss->speed / 70, -virtual_vec.y*32767*dt*boss->speed / 70, 0));
				}

				// CONTROLA EL DASHING
				if (pressed_SPACE_PUSHED && boss->dashing == 0 && (virtual_vec.x != 0 || virtual_vec.y != 0) && !boss->_resurrect) {

					Vec2 v = Vec2(virtual_vec.x, -virtual_vec.y);
					v.normalize();
					boss->dashingVector = v;
					boss->dashing = 0.5;

				}

				// CONTROLA LA ORIENTACION
				Vec2 virtual_vec_mouse = (mouse_position - Vec2(960/2, -640/2));
				virtual_vec_mouse.normalize();

				boss->_sprite->setRotation3D(Vec3(90, 0, -90 - atan2(virtual_vec_mouse.y*32767, virtual_vec_mouse.x*32767) * 360 / (2 * M_PI)));

				// SI NO SE PONE EN FALSE SE QUEDARIA EN TRUE HASTA QUE SE SOLTASE LA TECLA
				pressed_SPACE_PUSHED = false;
				pressed_ENTER_PUSHED = false;

			}

			// Irrelevant if controller is connected

			if (!paused) {

				if (coolDownNow < coolDownMax) {
					coolDownNow += dt;
				}
				if (coolDownFireNow < coolDownMax) {
					coolDownFireNow += dt;
				}
				if (coolDownAirNow < coolDownMax){
					coolDownAirNow += dt;
				}

				// SE CONTROLA QUE NO SE SALGA DEL RADIO DE LAS MOUNTAINS
				float aux_distance_player = sqrt(pow(boss->_sprite->getPositionX(), 2) + pow(boss->_sprite->getPositionY(), 2));
				float radius_mountains = 930;
				if (aux_distance_player > radius_mountains*(floorSize/2048)) {
					Vec2 distance_from_center = Vec2(boss->_sprite->getPositionX(), boss->_sprite->getPositionY());
					distance_from_center.normalize();
					boss->_sprite->setPosition3D(Vec3(distance_from_center.x*radius_mountains*(floorSize/2048), distance_from_center.y*radius_mountains*(floorSize/2048), boss->_sprite->getPositionZ()));
				}

				// BOSS 2 ROTATED TOWARDS BOSS 1
				//Point p = Point(boss->getPositionX(), boss->getPositionY());
				//rotateToPoint(boss2, p);
	
				// SE COLOCA LA TORRE DE PRUEBA EN EL LUGAR AL QUE APUNTAS Y SE PONE EN VERDE
				green_tower->setPosition3D(Vec3(boss->_sprite->getPositionX() + (rightThumbX/500)*(floorSize/2048), boss->_sprite->getPositionY() + (rightThumbY/500)*(floorSize/2048), 0));
				green_tower->setRotation3D(boss->_sprite->getRotation3D());
				green_tower->setColor(ccc3(0, 200, 0));

				green_slow->setPosition3D(Vec3(boss->_sprite->getPositionX() + (rightThumbX/500)*(floorSize/2048), boss->_sprite->getPositionY() + + (rightThumbY/500)*(floorSize/2048), 2));
				green_slow->setRotation3D(boss->_sprite->getRotation3D());
				green_slow->setColor(ccc3(0, 200, 0));

				green_monster->setPosition3D(Vec3(boss->_sprite->getPositionX() + (rightThumbX/500)*(floorSize/2048), boss->_sprite->getPositionY() + + (rightThumbY/500)*(floorSize/2048), 2));
				green_monster->setRotation3D(boss->_sprite->getRotation3D());
				green_monster->setColor(ccc3(0, 200, 0));

				// SE COMPRUEBA QUE LA TORRE NO ESTÁ TOCANDO OTRO OBJETO ESTÁTICO
				for (int i = 0; i < num_static_objects; i++) {
					// 60*1 es el radio de la futura torre
					float total_radius = static_objects[i]->_radius + 12*(floorSize/2048);

					if (pow(static_objects[i]->_sprite->getPositionX() - green_tower->getPositionX(), 2) + pow(static_objects[i]->_sprite->getPositionY() -green_tower->getPositionY(), 2) < pow(total_radius, 2)) {

						green_tower->setColor(ccc3(200, 0, 0));

					}

					total_radius = static_objects[i]->_radius + 20*(floorSize/2048);

					if (pow(static_objects[i]->_sprite->getPositionX() - green_slow->getPositionX(), 2) + pow(static_objects[i]->_sprite->getPositionY() -green_slow->getPositionY(), 2) < pow(total_radius, 2)) {

						green_slow->setColor(ccc3(200, 0, 0));

					}

					total_radius = static_objects[i]->_radius + 20*(floorSize/2048);

					if (pow(static_objects[i]->_sprite->getPositionX() - green_monster->getPositionX(), 2) + pow(static_objects[i]->_sprite->getPositionY() -green_monster->getPositionY(), 2) < pow(total_radius, 2)) {

						green_monster->setColor(ccc3(200, 0, 0));

					}

				}

				// SE COMPRUEBA QUE LA TORRE NO ESTÁ TOCANDO NINGUNO DE LOS PUNTOS DE LA BEZIER DE UN CAMINO
				for (int i = 0; i < num_active_pathstones; i++) {

					for (int j = 0; j < 200; j++) {

						// 60*1 es el radio de la futura torre
						float stone_radius = 12*(floorSize/2048);
						float total_radius = stone_radius + 12*(floorSize/2048);

						if (pow(active_pathstones[i]->invisible_points[j].x - green_tower->getPositionX(), 2) + pow(active_pathstones[i]->invisible_points[j].y -green_tower->getPositionY(), 2) < pow(total_radius, 2)) {

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
										Player* player;
										Entity* enemigo;

										if (mobile_objects[i]->_type.compare("player") == 0) player = (Player*)mobile_objects[i];
										if (mobile_objects[j]->_type.compare("player") == 0) player = (Player*)mobile_objects[j];

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
											player->_resurrect = true;
											player->_health = 0.01;
											player->_sprite->setPosition3D(Vec3(0, 0, player->_sprite->getPositionZ()));
										}
							
									}
									else if (mobile_objects[i]->_type.compare("resource") == 0 || mobile_objects[j]->_type.compare("resource") == 0) {
										// EL OTRO ES EL JUGADOR
										Resource* res;
										Player* player;

										if (mobile_objects[i]->_type.compare("resource") == 0) res = (Resource*)mobile_objects[i];
										if (mobile_objects[j]->_type.compare("resource") == 0) res = (Resource*)mobile_objects[j];

										res->_sprite->setVisible(false);
										res->_active = false;
										removeMobileObject(res->_num_in_array);
										
										resources += 20;

										//if (mobile_objects[i]->_type.compare("player") == 0) enemigo = mobile_objects[i];
										//if (mobile_objects[j]->_type.compare("player") == 0) enemigo = mobile_objects[j];
									}
								}

								else if (mobile_objects[i]->_type.compare("fireshot") == 0 || mobile_objects[j]->_type.compare("fireshot") == 0) {
									// UNO DE LOS DOS ES UNA PARTÍCULA DE FUEGO
									if (mobile_objects[i]->_type.compare("enemy") == 0 || mobile_objects[j]->_type.compare("enemy") == 0) {
										// EL OTRO ES UN ENEMY
										FireShot* bala;
										Entity* enemigo;

										if (mobile_objects[i]->_type.compare("fireshot") == 0) bala = (FireShot*)mobile_objects[i];
										if (mobile_objects[j]->_type.compare("fireshot") == 0) bala = (FireShot*)mobile_objects[j];

										if (mobile_objects[i]->_type.compare("enemy") == 0) enemigo = mobile_objects[i];
										if (mobile_objects[j]->_type.compare("enemy") == 0) enemigo = mobile_objects[j];

										// LA BALA NO MUERE

										// EL ENEMIGO SE HIERE
										enemigo->_health -= bala->_damage;
										if (enemigo->_health > 0) {
											//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hurt.wav");
											enemigo->_sprite->setColor(Color3B(255, 0, 0));
											enemigo->_injured = 0.1;
										}
										else {
											CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("explosion.wav");
										}
									}
								}
								else if (mobile_objects[i]->_type.compare("airshot") == 0 || mobile_objects[j]->_type.compare("fireshot") == 0) {
									// UNO DE LOS DOS ES UNA PARTÍCULA DE AIRE
									if (mobile_objects[i]->_type.compare("enemy") == 0 || mobile_objects[j]->_type.compare("enemy") == 0) {
										// EL OTRO ES UN ENEMY
										AirShot* bala;
										Entity* enemigo;

										if (mobile_objects[i]->_type.compare("airshot") == 0) bala = (AirShot*)mobile_objects[i];
										if (mobile_objects[j]->_type.compare("airshot") == 0) bala = (AirShot*)mobile_objects[j];

										if (mobile_objects[i]->_type.compare("enemy") == 0) enemigo = mobile_objects[i];
										if (mobile_objects[j]->_type.compare("enemy") == 0) enemigo = mobile_objects[j];

										// LA BALA NO MUERE
										repulse(bala, enemigo);
										// EL ENEMIGO SE HIERE
										enemigo->_health -= bala->_damage;
										if (enemigo->_health > 0) {
											//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hurt.wav");
											enemigo->_sprite->setColor(Color3B(255, 0, 0));
											enemigo->_injured = 0.1;
										}
										else {
											CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("explosion.wav");
										}
									}
								}
								else if (mobile_objects[i]->_type.compare("resource") == 0 || mobile_objects[j]->_type.compare("resource") == 0) {
									// UNO ES UN RESOURCE
									// NO CHOCA CON NADA
								}
								else if (mobile_objects[i]->_type.compare("enemy") == 0 && mobile_objects[j]->_type.compare("enemy") == 0) {
									//LOS DOS SON ENEMIGOS
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
								else if (mobile_objects[j]->_type.compare("player") == 0 && static_objects[i]->_type.compare("nexus") == 0) {
									// EL PLAYER PUEDE ATRAVESAR EL NEXO
								}
								else if ((mobile_objects[j]->_type.compare("shot") == 0 || mobile_objects[j]->_type.compare("airshot") == 0 || mobile_objects[j]->_type.compare("fireshot") == 0) && static_objects[i]->_type.compare("nexus") == 0) {
									// LOS SHOTS ATRAVIESAN EL NEXO
								}
								else if (mobile_objects[j]->_type.compare("tower_shot") == 0) {
									// LOS TOWER_SHOT NO COLISIONAN CON NADA ESTATICO
								}
								else if (mobile_objects[j]->_type.compare("resource") == 0) {
									// LOS RESOURCES NO COLISIONAN CON NADA ESTATICO
								}
								else if (static_objects[i]->_type.compare("tower") == 0) {
							
									Tower* t = (Tower*) static_objects[i];

									if (t->_subtype.compare("slow") == 0) {
								
										if (mobile_objects[j]->_type.compare("enemy") == 0) {
											((Enemy*) mobile_objects[j])->slowed = true;
										}

									}
									else if (t->_subtype.compare("monster") == 0) {

										if (t->_cooldown <= 0) {
											if (mobile_objects[j]->_type.compare("enemy") == 0) {
												((Enemy*)mobile_objects[j])->_health = 0;
												CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("explosion.wav");
												t->_cooldown = 4;
											}
										}

									}
									else {
										static_repulse(static_objects[i], mobile_objects[j]);
									}

								}
								else {

									static_repulse(static_objects[i], mobile_objects[j]);

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

							mobile_objects[i]->_active = false;

							if (mobile_objects[i]->_type.compare("enemy") == 0) {
								Resource* r = new Resource(floorSize, Point(mobile_objects[i]->_sprite->getPositionX(), mobile_objects[i]->_sprite->getPositionY()), boss);
								addMobileObject(r);
								r = new Resource(floorSize, Point(mobile_objects[i]->_sprite->getPositionX(), mobile_objects[i]->_sprite->getPositionY()), boss);
								addMobileObject(r);
								r = new Resource(floorSize, Point(mobile_objects[i]->_sprite->getPositionX(), mobile_objects[i]->_sprite->getPositionY()), boss);
								addMobileObject(r);
								r = new Resource(floorSize, Point(mobile_objects[i]->_sprite->getPositionX(), mobile_objects[i]->_sprite->getPositionY()), boss);
								addMobileObject(r);
								r = new Resource(floorSize, Point(mobile_objects[i]->_sprite->getPositionX(), mobile_objects[i]->_sprite->getPositionY()), boss);
								addMobileObject(r);

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

				// TODOS LOS PUNTOS ROJOS DEL MINIMAPA REPRESENTANDO ENEMIGOS SE RESETEAN
				for (int aux_bla = 0; aux_bla < 200; aux_bla++) {
					enemy_points[aux_bla]->setVisible(false);
				}

				// AQUI SE VUELVEN A PONER LOS PUNTOS ROJOS DE LOS ENEMIGOS
				for (int j = 0; j < num_mobile_objects; j++) {
					if (mobile_objects[j]->_type.compare("enemy") == 0) {
						enemy_points[j]->setVisible(true);
						enemy_points[j]->setPositionX(960 -minimapa->getBoundingBox().size.width/2 -16 +(mobile_objects[j]->_sprite->getPositionX()/(floorSize/2))*(128/2));
						enemy_points[j]->setPositionY(640 -minimapa->getBoundingBox().size.height/2 -16 +(mobile_objects[j]->_sprite->getPositionY()/(floorSize/2))*(128/2));
					}
				}
		
				if (nexus->_life > 0 && dead_enemies == total_enemies) {

					nexus->_sprite->setColor(Color3B(0, 255, 0));

				}

				camera->setRotation3D(Vec3(cameraAngle, 0, 0));
				camera->setPosition3D(Vec3(boss->_sprite->getPositionX(), boss->_sprite->getPositionY() - sin(cameraAngle*(2*M_PI)/360)*zoom, boss->_sprite->getPositionZ() + cos(cameraAngle*(2*M_PI)/360)*zoom ));

			}

		}
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

void HelloWorld::static_repulse(Entity* static_e, Entity* mobile_e) {

	float total_radius = static_e->_radius + mobile_e->_radius;

	float div = pow(total_radius, 2) / (pow(static_e->_sprite->getPositionX() - mobile_e->_sprite->getPositionX(), 2) + pow(static_e->_sprite->getPositionY() - mobile_e->_sprite->getPositionY(), 2));

	float* elements = new float[3];
	elements[0] = 0.5 * (abs(static_e->_sprite->getPositionX() - mobile_e->_sprite->getPositionX())*div - abs(static_e->_sprite->getPositionX() - mobile_e->_sprite->getPositionX()));
	if (static_e->_sprite->getPositionX() < mobile_e->_sprite->getPositionX()) elements[0] = -elements[0];
	elements[1] = 0.5 * (abs(static_e->_sprite->getPositionY() - mobile_e->_sprite->getPositionY())*div - abs(static_e->_sprite->getPositionY() - mobile_e->_sprite->getPositionY()));
	if (static_e->_sprite->getPositionY() < mobile_e->_sprite->getPositionY()) elements[1] = -elements[1];
	elements[2] = mobile_e->_num_in_array;

	EventCustom event("object_collision");
	event.setUserData(elements);

	_eventDispatcher->dispatchEvent(&event);

}

void HelloWorld::readMapFromFile(const std::string nameOfFile) {

	CCImage *img=  new CCImage();
	img->initWithImageFile(nameOfFile);

	int x=3;
    if(img->hasAlpha())
        x=4;

    unsigned char *data = new unsigned char[img->getDataLen()*x];   
    data = img->getData();
    // [0][0] => Left-Top Pixel !
    // But cocos2d Location Y-axis is Bottom(0) to Top(max)
	//CCLOG("This is a madafacking number: %d", 23);

	Color3B* rock = new Color3B(0, 0, 0);
	Color3B* rock2 = new Color3B(50, 50, 50);
	Color3B* rock3 = new Color3B(100, 100, 100);
	Color3B* rock4 = new Color3B(150, 150, 150);
	Color3B* palmTree = new Color3B(0, 255, 0);
	Color3B* pilar = new Color3B(255, 255, 0);
	Color3B* pilar2 = new Color3B(255, 200, 0);

    for(int i=0; i<img->getWidth(); i++)
    {
        for(int j=0; j<img->getHeight(); j++)
        {
            unsigned char *pixel = data + (i + j * img->getWidth()) * x;

           // You can see/change pixels' RGBA value(0-255) here !
            unsigned char r = *pixel;
            unsigned char g = *(pixel + 1);
            unsigned char b = *(pixel + 2) ;
            unsigned char a = *(pixel + 3);
			
			if (r == rock->r && g == rock->g && b == rock->b) {
				// ES UN PIXEL NIGGA
				float aux_w = float(i)/float(img->getWidth());
				float aux_h = 1 -(float(j)/float(img->getHeight()));

				//CCLOG("This is a madafacking number: %f", aux_w);
				//CCLOG("This is a madafacking number: %f", aux_h);

				Atrezzo* a;
				a = new Atrezzo(floorSize, Point( (aux_w*float(floorSize))-floorSize/2, (aux_h*float(floorSize))-floorSize/2), "rock");
				static_objects [num_static_objects] = a;
				num_static_objects++;
				a->_sprite->setCameraMask(2);
				this->addChild(a->_sprite, 1);
			}
			else if (r == rock2->r && g == rock2->g && b == rock2->b) {

				float aux_w = float(i)/float(img->getWidth());
				float aux_h = 1 -(float(j)/float(img->getHeight()));

				Atrezzo* a;
				a = new Atrezzo(floorSize, Point( (aux_w*float(floorSize))-floorSize/2, (aux_h*float(floorSize))-floorSize/2), "rock2");
				static_objects [num_static_objects] = a;
				num_static_objects++;
				a->_sprite->setCameraMask(2);
				this->addChild(a->_sprite, 1);
			}
			else if (r == rock3->r && g == rock3->g && b == rock3->b) {

				float aux_w = float(i)/float(img->getWidth());
				float aux_h = 1 -(float(j)/float(img->getHeight()));

				Atrezzo* a;
				a = new Atrezzo(floorSize, Point( (aux_w*float(floorSize))-floorSize/2, (aux_h*float(floorSize))-floorSize/2), "rock3");
				static_objects [num_static_objects] = a;
				num_static_objects++;
				a->_sprite->setCameraMask(2);
				this->addChild(a->_sprite, 1);
			}
			else if (r == rock4->r && g == rock4->g && b == rock4->b) {

				float aux_w = float(i)/float(img->getWidth());
				float aux_h = 1 -(float(j)/float(img->getHeight()));

				Atrezzo* a;
				a = new Atrezzo(floorSize, Point( (aux_w*float(floorSize))-floorSize/2, (aux_h*float(floorSize))-floorSize/2), "rock4");
				static_objects [num_static_objects] = a;
				num_static_objects++;
				a->_sprite->setCameraMask(2);
				this->addChild(a->_sprite, 1);
			}
			else if (r == palmTree->r && g == palmTree->g && b == palmTree->b) {

				float aux_w = float(i)/float(img->getWidth());
				float aux_h = 1 -(float(j)/float(img->getHeight()));

				Atrezzo* a;
				a = new Atrezzo(floorSize, Point( (aux_w*float(floorSize))-floorSize/2, (aux_h*float(floorSize))-floorSize/2), "palmTree");
				static_objects [num_static_objects] = a;
				num_static_objects++;
				a->_sprite->setCameraMask(2);
				this->addChild(a->_sprite, 1);
			}
			else if (r == pilar->r && g == pilar->g && b == pilar->b) {

				float aux_w = float(i)/float(img->getWidth());
				float aux_h = 1 -(float(j)/float(img->getHeight()));

				Atrezzo* a;
				a = new Atrezzo(floorSize, Point( (aux_w*float(floorSize))-floorSize/2, (aux_h*float(floorSize))-floorSize/2), "pilar");
				static_objects [num_static_objects] = a;
				num_static_objects++;
				a->_sprite->setCameraMask(2);
				this->addChild(a->_sprite, 1);
			}
			else if (r == pilar2->r && g == pilar2->g && b == pilar2->b) {

				float aux_w = float(i)/float(img->getWidth());
				float aux_h = 1 -(float(j)/float(img->getHeight()));

				Atrezzo* a;
				a = new Atrezzo(floorSize, Point( (aux_w*float(floorSize))-floorSize/2, (aux_h*float(floorSize))-floorSize/2), "pilar2");
				static_objects [num_static_objects] = a;
				num_static_objects++;
				a->_sprite->setCameraMask(2);
				this->addChild(a->_sprite, 1);
			}
			
			
        }
    }

}

void HelloWorld::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	//CCLOG("PULSADA LA TECLA : %x", keyCode);

	if (keyCode == EventKeyboard::KeyCode::KEY_W) { 
		//CCLOG("W key was pressed"); 
		pressed_W = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		pressed_A = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		pressed_S = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		pressed_D = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		pressed_UP = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		pressed_LEFT = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		pressed_DOWN = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		pressed_RIGHT = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		pressed_SPACE = true;
		pressed_SPACE_PUSHED = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
		pressed_ENTER = true;
		pressed_ENTER_PUSHED = true;
	}

}


void HelloWorld::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{

	if (keyCode == EventKeyboard::KeyCode::KEY_W) { 
		//CCLOG("W key was released"); 
		pressed_W = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		pressed_A = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		pressed_S = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		pressed_D = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		pressed_UP = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		pressed_LEFT = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		pressed_DOWN = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		pressed_RIGHT = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		pressed_SPACE = false;
		pressed_SPACE_PUSHED = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
		pressed_ENTER = false;
		pressed_ENTER_PUSHED = false;
	}

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
