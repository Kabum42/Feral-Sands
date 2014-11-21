#include "TowerShot.h"

TowerShot::TowerShot(Vec3 start, Entity* enemy)
{

	_type = "towershot";

	_origin = start;
	_target = enemy;
	_direction = _target->_sprite->getPosition3D() - _origin;
	_direction.normalize();

	_speed = 750;

	_sprite = Sprite3D::create("boss.obj", "boss.png");
	_sprite->setPosition3D(_origin);
	// ARREGLAR ROTACIÓN (ME DA PEREZA)
	_sprite->setRotation3D(Vec3(_direction.x, _direction.y, _direction.z));
	_sprite->setScale(3);

	_radius = 20;


	_eventDispatcher->addCustomEventListener("EnterFrame", [=] (EventCustom* event){
		float* data = static_cast<float*>(event->getUserData());
		update(data[0]);
	});
}


TowerShot::~TowerShot(void)
{
	removeFromParentAndCleanup(true);
}

void TowerShot::update(float dt)
{
	if (_sprite != NULL) {
		_sprite->setPosition3D(_sprite->getPosition3D() + _speed*_direction*dt);
	}
}