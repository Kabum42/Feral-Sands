#include "Tower.h"

String s;
Point initial_point_tower;
int scale_tower;

Tower::Tower(void) {

}

Tower::Tower(String s2, Point initial_point_2) {

	_type = "tower";
	_target = nullptr;
	_cooldown = 0; // ARREGLAR: Tiempo que tarde en salir la torre

	s = s2;
	initial_point_tower = initial_point_2;

	scale_tower = 60;

	// ESTE RADIO ES PERFECTO, NO TOCAR
	_radius = scale_tower*1;


	// RANGO DE SELECCIÓN DE OBJETIVOS ENEMIGOS
	_range = 500;

	position_z_tower = -0.44*scale_tower;

	_sprite = Sprite3D::create("Tower.obj", "stone.png");
	_sprite->setPosition3D(Vec3(initial_point_tower.x, initial_point_tower.y, position_z_tower));
	_sprite->setRotation3D(Vec3(90, 0, 270));
	_sprite->setScale(scale_tower);

	
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
				(data->y - point_sprite->y) < 600 && (data->y - point_sprite->y) > -1750) { distance_bool = true; }
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
	
	if (position_z_tower < 0.44*scale_tower) {

		position_z_tower += dt*scale_tower * 10;
		_sprite->setPositionZ(position_z_tower);
	}
	else {
		if (_cooldown > 0)
			_cooldown -= 1; // AJUSTAR TEMPORALMENTE

		if (_target != nullptr && _cooldown == 0)
		{
			_cooldown = 200;
			Vec3 tower_position = _sprite->getPosition3D();
			TowerShot* newTowerShot = new TowerShot(tower_position, _target);
			EventCustom event_add_shot("add_shot");
			event_add_shot.setUserData(newTowerShot);
			_eventDispatcher->dispatchEvent(&event_add_shot);
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