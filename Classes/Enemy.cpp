#include "Enemy.h"

Enemy::Enemy(void) {

}

Enemy::Enemy(String s_enemy2, Point initial_point_enemy2, PathStone* path2, float seconds_enemy2) {

	_principio = true;
	_active = false;
	_health = 200;
	_injured = 0;
	_type = "enemy";
	
	s_enemy = s_enemy2;
	initial_point_enemy = initial_point_enemy2;
	seconds_enemy = seconds_enemy2;

	scale_enemy = 20;
	position_z_enemy = scale_enemy*4.7;

	_radius = scale_enemy*1.0;

	position2 = initial_point_enemy2;

	path = path2;

	_sprite = Sprite3D::create("Enemy.obj", "stone.png");
	_sprite->setPosition3D(Vec3(initial_point_enemy.x, initial_point_enemy.y, position_z_enemy));
	_sprite->setRotation3D(Vec3(90, 0, 270));
	_sprite->setScale(scale_enemy);

	
	_eventDispatcher->addCustomEventListener("EnterFrame", [=](EventCustom* event) {
		float* data = static_cast<float*>(event->getUserData());
		update(data[0]);
	});

	_eventDispatcher->addCustomEventListener("paused", [=](EventCustom* event) {
		if (_health > 0 && _active) {
			_sprite->pauseSchedulerAndActions();
		}
	});

	_eventDispatcher->addCustomEventListener("unpaused", [=](EventCustom* event) {
		if (_health > 0 && _active) {
			_sprite->resumeSchedulerAndActions();
		}
	});

	_eventDispatcher->addCustomEventListener("checkVisible", [=](EventCustom* event) {
		if (_health > 0 && _active) {

			Point* data = static_cast<Point*>(event->getUserData());
			Point* point_sprite = new Point(_sprite->getPositionX(), _sprite->getPositionY());
			bool distance_bool = false;
			if ((data->x - point_sprite->x) < 1750 && (data->x - point_sprite->x) > -1750 &&
				(data->y - point_sprite->y) < 600 && (data->y - point_sprite->y) > -1750) { distance_bool = true; }
			if (distance_bool && !_sprite->isVisible()) {
				_sprite->setVisible(true);
			}
			else if (!distance_bool && _sprite->isVisible()) {
				_sprite->setVisible(false);
			}
		}
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

			if (_principio) {

				auto action = CCBezierTo::create(seconds_enemy, path->bezier);
				_sprite->runAction(action);
				_principio = false;

			}

			else {

				if (path->_nextPath == NULL) {

					// HACERLE DAÑO AL NEXUS

					harmNexus();

				}
				else {

				}

			}


			
		
		}
		else {

			position1 = position2;
			position2 = Point(_sprite->getPositionX(), _sprite->getPositionY());

			rotateToVec2(_sprite, Vec2(position2.x - position1.x, position2.y - position1.y));

		}

	}

	
}

void Enemy::harmNexus() {

	_active = false;

	int* data = new int[1];
	data[0] = -1;
	EventCustom event("nexus_life");
	event.setUserData(data);
	_eventDispatcher->dispatchEvent(&event);

	float* data2 = new float[1];
	data2[0] = _num_in_array;
	EventCustom event2("remove_mobile");
	event2.setUserData(data2);
	_eventDispatcher->dispatchEvent(&event2);
			
	EventCustom event_dead("enemy_dead");
	_eventDispatcher->dispatchEvent(&event_dead);

	this->_sprite->removeFromParentAndCleanup(true);
	_sprite = NULL;
	_eventDispatcher->removeEventListenersForTarget(this);
			
	// AQUI PROBABLEMENTE HACE FALTA ALGUNA FORMA DE DELETEAR DEL TODO ESTE OBJETO, PERO delete this NO FUNCIONA

}

void Enemy::rotateToVec2(Sprite3D* s, Vec2 v) {

	s->setRotation3D(Vec3(90, 0, -90 - atan2(v.y, v.x)*360/(2*M_PI)));

}