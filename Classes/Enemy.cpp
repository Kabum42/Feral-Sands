#include "Enemy.h"

Enemy::Enemy(void) {

}

Enemy::Enemy(String s_enemy2, Point initial_point_enemy2, ccBezierConfig bezier_enemy2, float seconds_enemy2) {

	_active = false;
	_health = 200;
	_injured = 0;
	_type = "enemy";
	
	s_enemy = s_enemy2;
	initial_point_enemy = initial_point_enemy2;
	seconds_enemy = seconds_enemy2;

	scale_enemy = 20;
	position_z_enemy = 100;

	_radius = scale_enemy*1.0;

	position2 = initial_point_enemy2;

	_bezier = bezier_enemy2;

	_sprite = Sprite3D::create("Lex_Low.obj");
	_sprite->setPosition3D(Vec3(initial_point_enemy.x, initial_point_enemy.y, position_z_enemy));
	_sprite->setRotation3D(Vec3(90, 0, 270));
	_sprite->setScale(scale_enemy);

	
	_eventDispatcher->addCustomEventListener("EnterFrame", [=](EventCustom* event) {
		float* data = static_cast<float*>(event->getUserData());
		update(data[0]);
	});
	
	

}

Enemy::~Enemy(void)
{
	//delete _object;
}

void Enemy::update(float dt)
{

	if (_health > 0 && _active) {

		if (_injured > 0) {

			_injured -= dt;
			if (_injured <= 0) { _sprite->setColor(Color3B(255, 255, 255)); }

		}
		
		if (_sprite->numberOfRunningActions() == 0) { 
		
			_sprite->setPosition3D(Vec3(initial_point_enemy.x, initial_point_enemy.y, position_z_enemy));

			auto action = CCBezierTo::create(seconds_enemy, _bezier);
    
			_sprite->runAction(action);
		
		}
		else {

			position1 = position2;
			position2 = Point(_sprite->getPositionX(), _sprite->getPositionY());

			rotateToVec2(_sprite, Vec2(position2.x - position1.x, position2.y - position1.y));

		}
		
	}

	
}

void Enemy::rotateToVec2(Sprite3D* s, Vec2 v) {

	s->setRotation3D(Vec3(90, 0, -90 - atan2(v.y, v.x)*360/(2*M_PI)));

}