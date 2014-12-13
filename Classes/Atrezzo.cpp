#include "Atrezzo.h"

int scale;

Atrezzo::Atrezzo(void) {

}

Atrezzo::Atrezzo(Point initial_point_2, String type2) {
	
	_type = "atrezzo";


	if (type2.compare("rock") == 0) {
		scale = 200/5;
		_radius = scale*0.5;
		_sprite = Sprite3D::create("Rock.obj", "stone.png");
	}
	else {
		_sprite = Sprite3D::create("Tower.obj", "stone.png");
	}

	
	_sprite->setPosition3D(Vec3(initial_point_2.x, initial_point_2.y, 0));
	_sprite->setRotation3D(Vec3(90, 0, 270));
	_sprite->setScale(scale);

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

Atrezzo::~Atrezzo(void)
{
	//delete _object;
}

