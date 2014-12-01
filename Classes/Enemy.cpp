#include "Enemy.h"

Enemy::Enemy(void) {

}

Enemy::Enemy(String s_enemy2, Point initial_point_enemy2, PathStone* path2, float seconds_enemy2) {

	_principio = true;
	_active = false;
	_health = 200;
	_injured = 0;
	_type = "enemy";
	num_location = -1;
	established_location = false;
	
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
		
		if (!established_location) { 

			if (num_location < (198) ) {
				num_location++;
				location = Point(path->invisible_points[num_location].x, path->invisible_points[num_location].y);
				established_location = true;
			}
			else if (path->_nextPath != NULL) {
				num_location = -1;
				path = path->_nextPath;
			}
			else {
				harmNexus();
			}
		
		}
		else {

			Vec2 v = Vec2(location.x - _sprite->getPositionX(), location.y - _sprite->getPositionY());
			v.normalize();
			_sprite->setPositionX(_sprite->getPositionX() +v.x*dt*200);
			_sprite->setPositionY(_sprite->getPositionY() +v.y*dt*200);

			// ESTA COMPROBACION LO QUE VERIFICA ES QUE EL SIGNO DE LA DIRECCION TOMADA AHORA Y LA QUE SE TOMARIA EN UNA
			// PROXIMA ITERACION SON EL MISMO, SI NO LO SON, ES QUE RETROCEDERÍA, Y POR TANTO, HA LLEGADO AL PUNTO
			if (v.x * (location.x - _sprite->getPositionX()) < 0 || v.y * (location.y - _sprite->getPositionY()) < 0) {
				established_location = false;
			}
			else if (location.x == _sprite->getPositionX() && location.y == _sprite->getPositionY()) {
				established_location = false;
			}
			else {
				position1 = position2;
				position2 = Point(_sprite->getPositionX(), _sprite->getPositionY());

				rotateToVec2(_sprite, Vec2(position2.x - position1.x, position2.y - position1.y));
			}

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