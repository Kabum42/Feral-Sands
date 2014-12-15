#include "Nexus.h"
#include "Enemy.h"

Point initial_point_nexus;
int scale_nexus;

Nexus::Nexus(void) {

}

Nexus::Nexus(int floorSize2, Point initial_point_2) {
	
	floorSize = floorSize2;
	_life = 5;
	_type = "nexus";

	initial_point_nexus = initial_point_2;

	scale_nexus = 80*(floorSize/2048);

	// ESTE RADIO ES PERFECTO, NO TOCAR
	_radius = scale_nexus*1;

	position_z_nexus = -0.44*scale_nexus;

	_sprite = Sprite3D::create("Shield.obj", "stone.png");
	_sprite->setPosition3D(Vec3(initial_point_nexus.x, initial_point_nexus.y, position_z_nexus));
	_sprite->setRotation3D(Vec3(90, 0, 270));
	_sprite->setScale(scale_nexus);
	_sprite->setColor(Color3B(0, 0, 200));
	GLubyte ubyteComponent = static_cast<GLubyte>(0.4f * 255.f); 
	_sprite->setOpacity(ubyteComponent);

	
	_eventDispatcher->addCustomEventListener("EnterFrame", [=](EventCustom* event) {
		float* data = static_cast<float*>(event->getUserData());
		update(data[0]);
	});

	_eventDispatcher->addCustomEventListener("checkVisible", [=](EventCustom* event) {
		if (true) {

			Point* data = static_cast<Point*>(event->getUserData());
			Point* point_sprite = new Point(_sprite->getPositionX(), _sprite->getPositionY());
			bool distance_bool = false;
			if ((data->x - point_sprite->x) < (350*(floorSize/2048)) && (data->x - point_sprite->x) > -(350*(floorSize/2048)) &&
				(data->y - point_sprite->y) < (200*(floorSize/2048)) && (data->y - point_sprite->y) > -(350*(floorSize/2048))) { distance_bool = true; }
			if (distance_bool && !_sprite->isVisible()) {
				_sprite->setVisible(true);
			}
			else if (!distance_bool && _sprite->isVisible()) {
				_sprite->setVisible(false);
			}
		}
	});
	
	

}

Nexus::~Nexus(void)
{
	//delete _object;
}

void Nexus::update(float dt)
{
	
	if (position_z_nexus < 0) {

		position_z_nexus += dt*scale_nexus*10;
		_sprite->setPositionZ(position_z_nexus);

	}
	
}