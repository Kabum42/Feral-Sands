#include "FireShot.h"


FireShot::FireShot(Vec3 start, Vec3 aim)
{

	_active = false;
	_health = 200;
	_injured = 0;
	_type = "fireshot";

	_origin = start;
	_direction = aim;
	_displacement = Vec3(0, 0, 0);

	_speed = 300 + (rand() % 50) -25;
	_deacceleration = 200 + (rand() % 100) - 50;
	_range = 100;
	_damage = 0.5;

	_sprite = Sprite3D::create("Shot.obj", "fire.jpg");
	_sprite->setPosition3D(_origin);
	_sprite->setRotation3D(_direction);
	_sprite->setScale(15/5);
	_shrink = 15;

	_radius = 20;

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

FireShot::~FireShot(void/*FireShot _object*/)
{
	removeFromParentAndCleanup(true);
	//removeChild(this);
}

void FireShot::update(float dt)
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