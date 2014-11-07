#include "WeaponShot.h"


WeaponShot::WeaponShot(Vec3 start, Vec3 aim)
{
	_origin = start;
	_direction = aim;

	_speed = 100;
	_range = 100;

	_sprite = Sprite3D::create("boss.obj", "boss.png");
	_sprite->setPosition3D(_origin);
	_sprite->setRotation3D(_direction);
	_sprite->setScale(3);


	_direction.z += 90;
	_direction = Vec3(cos(_direction.z*M_PI/180),-sin(_direction.z*M_PI/180),0);
	_direction.normalize();

	_eventDispatcher->addCustomEventListener("EnterFrame", [=] (EventCustom* event){
		update();
	});
}

WeaponShot::~WeaponShot(void/*WeaponShot _object*/)
{
	//delete _object;
}

void WeaponShot::update(void)
{
	_sprite->setPosition3D(_sprite->getPosition3D() + _speed*_direction);

	// CheckRange
	if ( sqrt(pow(_sprite->getPosition3D().x-_origin.x,2.0) + pow(_sprite->getPosition3D().y-_origin.y,2.0)) >= _range)
	{
		// Autodestruirse..?
		//this->getParent()->removeChild(this);
		//this->removeFromParentAndCleanup(true);
	}
}


/*Sprite3D* WeaponShot::sprite()
{
	return _sprite;
}*/