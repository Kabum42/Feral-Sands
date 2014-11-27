#include "TowerShot.h"

TowerShot::TowerShot(Vec3 origin, Entity* enemy)
{
	_active = false;
	_radius = 20;
	_num_in_array = NULL;
	_type = "tower_shot";
	_health = 200;
	_injured = 0;
	
	_speed = 15;
	_damage = 50;

	_range = NULL;
	
	//_initial_position = origin;
	_target = enemy;
	_sprite = Sprite3D::create("boss.obj", "boss.png");
	_sprite->setPosition3D(origin+Vec3(0,0,100));
	//Vec3 target_position = _target->_sprite->getPosition3D();
	//_sprite->setRotation3D(Vec3(90, 0, acos(target_position.z - origin.z)*180/M_PI));
	//_sprite->setRotation3D(Vec3(90, 0, 0));
	_sprite->setScale(5);

	_eventDispatcher->addCustomEventListener("EnterFrame", [=](EventCustom* event_enter_frame) {
		float* data = static_cast<float*>(event_enter_frame->getUserData());
		update(data[0]);
	});
}


TowerShot::~TowerShot(void)
{
	removeFromParentAndCleanup(true);
}


void TowerShot::update(float dt)
{
	if (_target == nullptr || _target == NULL || _target->_sprite == nullptr || _target->_sprite == NULL || _target->_health == 0){
		_health = 0;
		this->removeChild(_sprite, true);
		this->removeFromParentAndCleanup(true);
		_sprite = NULL;
		RemoveSelf;
	}
		
	else if	(_sprite == nullptr || _sprite == NULL){
		_health = 0;
		this->removeChild(_sprite, true);
		this->removeFromParentAndCleanup(true);
		RemoveSelf;
	}
	else{
		//MOVEMENT
		_direction = _target->_sprite->getPosition3D() - _sprite->getPosition3D();
		_distance = _direction.length();
		_direction.normalize();
		_sprite->setPosition3D(_sprite->getPosition3D() + _direction*_speed);

		// ROTATION
		if (_direction.x == 0){
			if (_direction.y > 0){ _sprite->setRotation3D(Vec3(90, 0, 180)); }
			else{ _sprite->setRotation3D(Vec3(90, 0, 0)); }
		}
		else{ _sprite->setRotation3D(Vec3(90, 0, -90 - atan2(_direction.y, _direction.x) * 180 / M_PI)); }
	
		// COLISION
		if (_distance < _radius + _target->_radius){

			//	EL ENEMIGO SE HIERE
			_target->_health -= _damage;
			if (_target->_health > 0){
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hurt.wav");
				_target->_sprite->setColor(Color3B(255, 0, 0));
				_target->_injured = 0.1;
			}
			else{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("explosion.wav");
			}

			// LA BALA MUERE
			_health = 0;
			_sprite->removeFromParentAndCleanup(true);
			this->removeFromParentAndCleanup(true);
			this->removeChild(_sprite, true);
			_sprite = NULL;
			RemoveSelf;
			//_eventDispatcher->removeCustomEventListeners("EnterFrame");
		}

	}

	
}