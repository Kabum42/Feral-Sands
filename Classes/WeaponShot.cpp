#include "WeaponShot.h"


WeaponShot::WeaponShot(int floorSize2, Vec3 start, Vec3 aim)
{

	floorSize = floorSize2;
	_active = false;
	_health = 200;
	_injured = 0;
	_type = "shot";

	_origin = start;
	_direction = aim;

	_speed = 3000;
	_range = 100;

	_sprite = Sprite3D::create("Shot.obj", "stone.png");
	_sprite->setPosition3D(_origin);
	_sprite->setRotation3D(_direction);
	_sprite->setScale(5*(floorSize/2048));

	_radius = 20;

	_time = 0;
	_timeLimit = 2;

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

WeaponShot::~WeaponShot(void/*WeaponShot _object*/)
{
	removeFromParentAndCleanup(true);
	//removeChild(this);
}

void WeaponShot::update(float dt)
{

	if (_time < _timeLimit) {

		_time += dt;

	}

	if (_sprite != NULL) {

		_sprite->setPosition3D(_sprite->getPosition3D() + _speed*_direction*dt);

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
			this->removeAllComponents();
			
		}

	}
}