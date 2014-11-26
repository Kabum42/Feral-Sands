#include "Tower.h"

String s;
Point initial_point_tower;
int scale_tower;

Tower::Tower(void) {

}

Tower::Tower(String s2, Point initial_point_2) {

	
	s = s2;
	initial_point_tower = initial_point_2;

	scale_tower = 60;

	// ESTE RADIO ES PERFECTO, NO TOCAR
	_radius = scale_tower*1;

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
			float cameraAngle = 34;
			Point* data = static_cast<Point*>(event->getUserData());
			Point* point_sprite = new Point(_sprite->getPositionX(), _sprite->getPositionY());
			float distance = sqrt(pow(data->x - point_sprite->x, 2) + pow(data->y - point_sprite->y, 2));
			if (distance < 2000 && !_sprite->isVisible()) {
				_sprite->setVisible(true);
			}
			else if (distance >= 2000 && _sprite->isVisible()) {
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

		position_z_tower += dt*scale_tower*10;
		_sprite->setPositionZ(position_z_tower);

	}
	
}