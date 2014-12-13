#include "Tower.h"

Point initial_point_tower;
int scale_tower;

Tower::Tower(void) {

}

Tower::Tower(int floorSize2, String _subtype2, Point initial_point_2) {

	floorSize = floorSize2;
	_type = "tower";
	_subtype = _subtype2;
	_target = nullptr;
	_cooldown = 0; // ARREGLAR: Tiempo que tarde en salir la torre

	initial_point_tower = initial_point_2;

	if (_subtype.compare("standard") == 0) {
		scale_tower = 12*(floorSize/2048);

		// ESTE RADIO ES PERFECTO, NO TOCAR
		_radius = scale_tower*1;


		// RANGO DE SELECCIÓN DE OBJETIVOS ENEMIGOS
		_range = 500;

		position_z_tower = -1*scale_tower;

		_sprite = Sprite3D::create("Tower.obj", "stone.png");
		_sprite->setPosition3D(Vec3(initial_point_tower.x, initial_point_tower.y, position_z_tower));
		_sprite->setRotation3D(Vec3(90, 0, 270));
		_sprite->setScale(scale_tower);
	}
	else if (_subtype.compare("slow") == 0) {
		
		scale_tower = 30*(floorSize/2048);

		_radius = scale_tower*0.5;

		position_z_tower = 1;

		_sprite = Sprite3D::create("Floor.obj", "alquitran.png");
		_sprite->setPosition3D(Vec3(initial_point_tower.x, initial_point_tower.y, position_z_tower));
		_sprite->setRotation3D(Vec3(90, 0, 270));
		_sprite->setScale(scale_tower);
	}

	
	_eventDispatcher->addCustomEventListener("EnterFrame", [=](EventCustom* event) {
		float* data = static_cast<float*>(event->getUserData());
		update(data[0]);
	});
	
	_eventDispatcher->addCustomEventListener("checkVisible", [=](EventCustom* event) {
		if (_active) {

			Point* data = static_cast<Point*>(event->getUserData());
			Point* point_sprite = new Point(_sprite->getPositionX(), _sprite->getPositionY());
			bool distance_bool = false;
			if ((data->x - point_sprite->x) < 1750 && (data->x - point_sprite->x) > -1750 &&
				(data->y - point_sprite->y) < 700 && (data->y - point_sprite->y) > -1750) { distance_bool = true; }
			if (distance_bool && !_sprite->isVisible()) {
				_sprite->setVisible(true);
			}
			else if (!distance_bool && _sprite->isVisible()) {
				_sprite->setVisible(false);
			}
		}
	});

}

Tower::~Tower(void)
{
	//delete _object;
}

void Tower::update(float dt)
{

	if (_subtype.compare("standard") == 0) {

		if (position_z_tower < 0) {

			position_z_tower += dt*scale_tower * 10;
			_sprite->setPositionZ(position_z_tower);
		}
		else {
			if (_cooldown > 0) {
				_cooldown -= dt;
				if (_cooldown < 0) { _cooldown = 0; }
			}	

			if (_target != nullptr && _cooldown == 0)
			{
				_cooldown = 1; // ESTE ES EL COOLDOWN
				Vec3 tower_position = _sprite->getPosition3D();
				TowerShot* newTowerShot = new TowerShot(tower_position, _target);
				EventCustom event_add_shot("add_mobile");
				event_add_shot.setUserData(newTowerShot);
				_eventDispatcher->dispatchEvent(&event_add_shot);
				//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("shoot.wav");
			}
		
			if(_target != nullptr && _target != NULL && _target->_sprite != nullptr && _target->_sprite != NULL && _target->_health > 0)
			{
				if(pow(_sprite->getPositionX() - _target->_sprite->getPositionX(), 2) + pow(_sprite->getPositionY() - _target->_sprite->getPositionY(), 2) > pow(_range, 2))
				{
					_target = nullptr;
				}
			}
			else { _target = nullptr; }
		}

	}
	
	
}