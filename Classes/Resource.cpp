#include "Resource.h"
#include "Player.h"

Resource::Resource(void) {

}

Resource::Resource(int floorSize2, Point initial_point, Player* _player2, int value2) {
	
	_active = true;
	_health = 1;
	floorSize = floorSize2;
	_player = _player2;
	_type = "resource";
	value = value2;
	time_passed = 0;

	float proportion = value/20;
	if (proportion < (1/1.5)) { proportion = (1/1.5); }
	if (proportion > 1.5) { proportion = 1.5; }

	_sprite = Sprite3D::create("Shot.obj", "stone.png");
	_sprite->setPosition3D(Vec3(initial_point.x, initial_point.y, 0));
	_sprite->setRotation3D(Vec3(90, 0, 270));
	_sprite->setScale(5*(floorSize/2048)*proportion);
	_sprite->setColor(Color3B(200, 0, 0));

	GLubyte ubyteComponent = static_cast<GLubyte>(0.7f * 255.f); 
	_sprite->setOpacity(ubyteComponent);

	_radius = 20;

	float angle = atan2(_sprite->getPositionY() - _player->_sprite->getPositionY(), _sprite->getPositionX() - _player->_sprite->getPositionX())*360/(2*M_PI);
	if ((rand() % 100) > 50) {
		angle += 30 + (rand() % (50));
	}
	else {
		angle -= 30 + (rand() % (50));
	}
	escape = Vec2(cos(angle*2*M_PI/(360)), sin(angle*2*M_PI/(360)));
	escape.normalize();

	speed = 75 + (rand() % (25));
	speed = speed/100;
	
	_eventDispatcher->addCustomEventListener("EnterFrame", [=](EventCustom* event) {
		float* data = static_cast<float*>(event->getUserData());
		update(data[0]);
	});

	_eventDispatcher->addCustomEventListener("checkVisible", [=](EventCustom* event) {
		
		if (_active) {
			
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
	if (_active) {
		time_passed += dt;

		Vec3 vec_to_player = Vec3(_player->_sprite->getPosition3D() - _sprite->getPosition3D());
		vec_to_player.normalize();

		_sprite->setPositionX(_sprite->getPositionX() + escape.x*dt*(0.3*5000) + vec_to_player.x*dt*(time_passed*5000)*speed);
		_sprite->setPositionY(_sprite->getPositionY() + escape.y*dt*(0.3*5000) + vec_to_player.y*dt*(time_passed*5000)*speed);
		_sprite->setPositionZ(_sprite->getPositionZ() + 0.5*dt*(0.3*5000) + vec_to_player.z*dt*(time_passed*5000)*speed);
	}
}