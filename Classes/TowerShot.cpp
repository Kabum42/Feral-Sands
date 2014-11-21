#include "TowerShot.h"

TowerShot::TowerShot(Vec3 start, Entity* enemy)
{

	_type = "towershot";
	
	_active = false;
	_health = 200;

	_origin = start;
	_target = enemy;
	_direction = _target->_sprite->getPosition3D() - _origin;
	_direction.normalize();

	_speed = 50;

	_sprite = Sprite3D::create("boss.obj", "boss.png");
	_sprite->setPosition3D(_origin);
	// ARREGLAR ROTACIÓN (ME DA PEREZA)
	_sprite->setRotation3D(Vec3(_direction.x, _direction.y, _direction.z));
	_sprite->setScale(300);

	_radius = 20;

	
	_eventDispatcher->addCustomEventListener("EnterFrame", [=] (EventCustom* event){
		float* data = static_cast<float*>(event->getUserData());
		update(data[0]);
	});


	EventCustom event_add_mobile("add_mobile");
	event_add_mobile.setUserData(this);
	_eventDispatcher->dispatchEvent(&event_add_mobile);
}


TowerShot::~TowerShot(void)
{
	removeFromParentAndCleanup(true);
}

void TowerShot::update(float dt)
{
	if (_sprite != NULL) {
		_direction = _target->_sprite->getPosition3D() - _sprite->getPosition3D();
		//_direction = Vec3(0,0,0) - _sprite->getPosition3D();
		_direction.normalize();
		_sprite->setPosition3D(_sprite->getPosition3D() + _speed*_direction/**dt*/);
	}
}