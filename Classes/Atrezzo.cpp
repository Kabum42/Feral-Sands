#include "Atrezzo.h"

int scale;

Atrezzo::Atrezzo(void) {

}

Atrezzo::Atrezzo(int floorSize2, Point initial_point_2, String type2) {
	
	floorSize = floorSize2;
	_type = "atrezzo";


	if (type2.compare("rock") == 0) {
		scale = 40*(floorSize/2048);
		_radius = scale*1;
		_sprite = Sprite3D::create("Rock.obj", "RockText.png");
	}
	else if (type2.compare("rock2") == 0) {
		scale = 40*(floorSize/2048);
		_radius = scale*0.5;
		_sprite = Sprite3D::create("Rock2.obj", "Rock2Text.png");
	}
	else if (type2.compare("rock3") == 0) {
		scale = 40*(floorSize/2048);
		_radius = scale*0.5;
		_sprite = Sprite3D::create("Rock3.obj", "Rock3Text.png");
	}
	else if (type2.compare("rock4") == 0) {
		scale = 40*(floorSize/2048);
		_radius = scale*0.5;
		_sprite = Sprite3D::create("Rock4.obj", "Rock4Text.png");
	}
	else if (type2.compare("palmTree") == 0) {
		scale = 50*(floorSize/2048);
		_radius = scale*0.05;
		_sprite = Sprite3D::create("PalmTree.obj", "PalmTreeText.png");
	}
	else if (type2.compare("pilar") == 0) {
		scale = 100*(floorSize/2048);
		_radius = scale*0.2;
		_sprite = Sprite3D::create("Pilar.obj", "PilarText.png");
	}
	else if (type2.compare("pilar2") == 0) {
		scale = 100*(floorSize/2048);
		_radius = scale*0.2;
		_sprite = Sprite3D::create("Pilar.obj", "PilarText.png");
	}
	else if (type2.compare("gate") == 0) {
		scale = 50*(floorSize/2048);
		_radius = scale*0.2;
		_sprite = Sprite3D::create("Gate.obj", "GateText.png");
	}
	else if (type2.compare("ruin") == 0) {
		scale = 50*(floorSize/2048);
		_radius = scale*0.2;
		_sprite = Sprite3D::create("RuinStructure.obj", "RuinStructureText.png");
	}

	
	_sprite->setPosition3D(Vec3(initial_point_2.x, initial_point_2.y, 0));
	_sprite->setRotation3D(Vec3(90, 0, rand() % 360));
	if (type2.compare("pilar2") == 0) _sprite->setRotation3D(Vec3(0, 0, 220));
	_sprite->setScale(scale);

	_eventDispatcher->addCustomEventListener("checkVisible", [=](EventCustom* event) {
		if (_active) {

			Point* data = static_cast<Point*>(event->getUserData());
			Point* point_sprite = new Point(_sprite->getPositionX(), _sprite->getPositionY());
			bool distance_bool = false;
			if ((data->x - point_sprite->x) < (350*(floorSize/2048)) && (data->x - point_sprite->x) > -(350*(floorSize/2048)) &&
				(data->y - point_sprite->y) < (150*(floorSize/2048)) && (data->y - point_sprite->y) > -(350*(floorSize/2048))) { distance_bool = true; }
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

