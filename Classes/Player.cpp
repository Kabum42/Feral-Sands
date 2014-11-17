#include "Player.h"

Player::Player(void) {

}

Player::Player(Point initial_point_player2) {

	_active = false;
	_health = 200;
	_injured = 0;
	_type = "player";

	initial_point_player = initial_point_player2;

	scale_player = 20;
	position_z_player = 100;

	_radius = scale_player*1.0;


	_sprite = Sprite3D::create("Lex_High.obj");
	_sprite->setPosition3D(Vec3(initial_point_player.x, initial_point_player.y, position_z_player));
	_sprite->setRotation3D(Vec3(90, 0, 180));
	_sprite->setScale(scale_player);

	
	_eventDispatcher->addCustomEventListener("EnterFrame", [=](EventCustom* event) {
		float* data = static_cast<float*>(event->getUserData());
		update(data[0]);
	});
	
	

}


Player::~Player(void)
{
	//delete _object;
}

void Player::update(float dt)
{

	
}
