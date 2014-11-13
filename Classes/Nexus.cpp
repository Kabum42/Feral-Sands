#include "Nexus.h"

Point initial_point_nexus;
int scale_nexus;

Nexus::Nexus(void) {

}

Nexus::Nexus(Point initial_point_2) {

	
	initial_point_nexus = initial_point_2;

	scale_nexus = 30;

	// ESTE RADIO ES PERFECTO, NO TOCAR
	_radius = scale_nexus*1;

	position_z_nexus = -4*scale_nexus;

	_sprite = Sprite3D::create("tower.obj", "stone.png");
	_sprite->setPosition3D(Vec3(initial_point_nexus.x, initial_point_nexus.y, position_z_nexus));
	_sprite->setRotation3D(Vec3(90, 0, 270));
	_sprite->setScale(scale_nexus);
	_sprite->setColor(Color3B(0, 0, 200));

	
	_eventDispatcher->addCustomEventListener("EnterFrame", [=](EventCustom* event) {
		float* data = static_cast<float*>(event->getUserData());
		update(data[0]);
	});
	
	

}

Nexus::~Nexus(void)
{
	//delete _object;
}

void Nexus::update(float dt)
{
	
	if (position_z_nexus < 4*scale_nexus) {

		position_z_nexus += dt*scale_nexus*10;
		_sprite->setPositionZ(position_z_nexus);

	}
	
}