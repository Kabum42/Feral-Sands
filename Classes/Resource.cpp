#include "Resource.h"
#include "Player.h"

Point initial_point_nexus;
int scale_nexus;

Resource::Resource(void) {

}

Resource::Resource(Point initial_point, Player* _player2) {
	
	_player = _player2;

	_sprite = Sprite3D::create("Shot.obj", "stone.png");
	_sprite->setPosition3D(Vec3(initial_point.x, initial_point.y, 0));
	_sprite->setRotation3D(Vec3(90, 0, 270));
	_sprite->setScale(1);
	_sprite->setColor(Color3B(200, 0, 0));

	GLubyte ubyteComponent = static_cast<GLubyte>(0.7f * 255.f); 
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

Resource::~Resource(void)
{
	//delete _object;
}

void Resource::update(float dt)
{
	
}