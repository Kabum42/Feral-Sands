#include "TowerShot.h"

TowerShot::TowerShot(float floorSize2, Vec3 origin, Entity* enemy)
{
	floorSize = floorSize2;
	_active = false;
	_radius = 20;
	_num_in_array = NULL;
	_type = "tower_shot";
	_health = 200;
	_injured = 0;
	
	_speed = 15;
	_damage = 20;

	_range = NULL;
	
	//_initial_position = origin;
	_target = enemy;
	_sprite = Sprite3D::create("Shot.obj", "ShotTurret.png");
	_sprite->setPosition3D(origin+Vec3(0,0,100));
	//Vec3 target_position = _target->_sprite->getPosition3D();
	//_sprite->setRotation3D(Vec3(90, 0, acos(target_position.z - origin.z)*180/M_PI));
	//_sprite->setRotation3D(Vec3(90, 0, 0));
	_sprite->setScale(5);

	_eventDispatcher->addCustomEventListener("EnterFrame", [=](EventCustom* event_enter_frame) {
		float* data = static_cast<float*>(event_enter_frame->getUserData());
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


TowerShot::~TowerShot(void)
{
	removeFromParentAndCleanup(true);
}


void TowerShot::update(float dt)
{

	if (_sprite != NULL) {

		if (_target != NULL && _target->_sprite == NULL) {
			// AUTODESTRUCCION
			_active = false;
			_sprite->removeFromParentAndCleanup(true);
			_sprite = NULL;
			_eventDispatcher->removeEventListenersForTarget(this);
				
			float* data_mobile = new float[1];
			data_mobile[0] = _num_in_array;
			EventCustom event_mobile("remove_mobile");
			event_mobile.setUserData(data_mobile);
			_eventDispatcher->dispatchEvent(&event_mobile);
		}
		else if (_target != NULL) {

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

		}

	}

	
}