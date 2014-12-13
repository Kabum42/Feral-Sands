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
	

	_sprite = Sprite3D::create("Shot.obj", "airShot.jpg");
	_sprite->setPosition3D(_origin);
	_sprite->setRotation3D(_direction);
	_sprite->setScale(6*(floorSize/2048));
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