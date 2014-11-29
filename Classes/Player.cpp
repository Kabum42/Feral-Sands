#include "Player.h"

Player::Player(void) {

}

Player::Player(Point initial_point_player2) {

	_active = true;
	_health = 200;
	_injured = 0;
	_type = "player";
	dashing = 0;
	speed = 1.5;
	speed_cooldown = 0;

	initial_point_player = initial_point_player2;

	scale_player = 20;
	position_z_player = scale_player*4.7;

	_radius = scale_player*1.0;


	_sprite = Sprite3D::create("Lex_High.obj", "stone.png");
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

	if (_health > 0 && _active) {

		if (_injured > 0) {

			_injured -= dt;
			if (_injured <= 0) { _sprite->setColor(Color3B(255, 255, 255)); }

		}

		if (dashing > 0) {

			float proportion = 0.5;

			if (dashing > (0.5 - proportion*0.5)) {
				_sprite->setPosition3D(_sprite->getPosition3D() + Vec3(dashingVector.x*(1/proportion)*32767*dt*speed/70, dashingVector.y*(1/proportion)*32767*dt*speed/70, 0));
			}
			else {
				_sprite->setPosition3D(_sprite->getPosition3D() + Vec3(dashingVector.x*(proportion)*32767*dt*speed/70, dashingVector.y*(proportion)*32767*dt*speed/70, 0));
			}

			dashing -= dt;
			if (dashing < 0) { dashing = 0; }
		}

		if (speed_cooldown > 0) {
			speed_cooldown -= dt;
			if (speed_cooldown < 0) { speed_cooldown = 0;}
			speed = 1;
		}
		else {
			speed = 1.5;
		}

	}
	
}
