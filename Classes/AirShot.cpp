#include "AirShot.h"


AirShot::AirShot(int floorSize2, Vec3 start, Vec3 aim, float pow)
{

	floorSize = floorSize2;
	_active = false;
	_health = 200;
	_injured = 0;
	_type = "airshot";

	_origin = start;
	_direction = aim;
	_displacement = Vec3(0, 0, 0);

	_speed = 300 + (rand() % 50) -25;
	_power = pow;
	_speed *= _power;
	_deacceleration = 200 + (rand() % 100) - 50;
	_range = 100;
	_damage = 0;
	

	_sprite = Sprite3D::create("Shot.obj", "ShotAir.png");
	_sprite->setPosition3D(_origin);
	_sprite->setPositionZ(80);
	_sprite->setRotation3D(_direction);
	_sprite->setScale(2*(floorSize/2048));
	_shrink = 60;

	_radius = 35;

	_time = 0;
	_timeLimit = 1;

	_direction.z += 90;
	_direction = Vec3(cos(_direction.z*M_PI/180),-sin(_direction.z*M_PI/180),0);
	_direction.normalize();

	_eventDispatcher->addCustomEventListener("EnterFrame", [=] (EventCustom* event){
		float* data = static_cast<float*>(event->getUserData());
		update(data[0]);
	});

	_eventDispatcher->addCustomEventListener("checkVisible", [=](EventCustom* event) {
		if (_active) {

			Point* data = static_cast<Point*>(event->getUserData());
			Point* point_sprite = new Point(_sprite->getPositionX(), _sprite->getPositionY());
			bool distance_bool = false;
			if ((data->x - point_sprite->x) < (350*(floorSize/2048)) && (data->x - point_sprite->x) > -(350*(floorSize/2048)) &&
				(data->y - point_sprite->y) < (120*(floorSize/2048)) && (data->y - point_sprite->y) > -(350*(floorSize/2048))) { distance_bool = true; }
			if (distance_bool && !_sprite->isVisible()) {
				_sprite->setVisible(true);
			}
			else if (!distance_bool && _sprite->isVisible()) {
				_sprite->setVisible(false);
			}
		}
	});
}

AirShot::~AirShot(void/*FireShot _object*/)
{
	removeFromParentAndCleanup(true);
	//removeChild(this);
}

void AirShot::update(float dt)
{

	if (_time < _timeLimit) {

		_time += dt;

	}

	if (_sprite != NULL) {

		_sprite->setPosition3D(_sprite->getPosition3D() + _speed*_direction*dt + Vec3(0,0,100*_time*dt) + _displacement*dt);
		_speed -= _deacceleration*_time*dt;
		_sprite->setScale(_sprite->getScale() - _shrink*_time*dt);

		if (_time >= _timeLimit) {
			
			_active = false;
			float* data = new float[1];
			data[0] = _num_in_array;
			EventCustom event("remove_mobile");
			event.setUserData(data);
			_eventDispatcher->dispatchEvent(&event);
			
			
			this->_sprite->removeFromParentAndCleanup(true);
			_sprite = NULL;
			_eventDispatcher->removeEventListenersForTarget(this);
			
			// AQUI PROBABLEMENTE HACE FALTA ALGUNA FORMA DE DELETEAR DEL TODO ESTE OBJETO, PERO delete this NO FUNCIONA
			
		}

	}
}