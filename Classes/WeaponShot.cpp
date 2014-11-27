#include "WeaponShot.h"


WeaponShot::WeaponShot(Vec3 start, Vec3 aim)
{

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
	_sprite->setScale(15);

	_radius = 20;

	_time = 0;

	_direction.z += 90;
	_direction = Vec3(cos(_direction.z*M_PI/180),-sin(_direction.z*M_PI/180),0);
	_direction.normalize();

	_eventDispatcher->addCustomEventListener("EnterFrame", [=] (EventCustom* event){
		float* data = static_cast<float*>(event->getUserData());
		update(data[0]);
	});
}

WeaponShot::~WeaponShot(void/*WeaponShot _object*/)
{
	removeFromParentAndCleanup(true);
	//removeChild(this);
}

void WeaponShot::update(float dt)
{

	if (_time < 2) {

		_time += dt;

	}

	if (_sprite != NULL) {

		_sprite->setPosition3D(_sprite->getPosition3D() + _speed*_direction*dt);

		if (_time >= 2) {
			
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

	// CheckRange
	/*
	if ( sqrt(pow(_sprite->getPosition3D().x-_origin.x,2.0) + pow(_sprite->getPosition3D().y-_origin.y,2.0)) >= _range)
	{
		// Autodestruirse..?
		//this->getParent()->removeChild(this);
		//this->removeFromParentAndCleanup(true);
		//removeFromParentAndCleanup(true);
		//removeChild(this);
	}
	*/
}


/*Sprite3D* WeaponShot::sprite()
{
	return _sprite;
}*/