#include "Wave.h"

Wave::Wave(Point initial_point2, PathStone* path2) {
	
	_active = false;
	current_delay = 0;
	initial_point = initial_point2;
	//bezier = bezier2;
	path = path2;
	num_enemies = 0;
	current_enemy = 0;

	
	_eventDispatcher->addCustomEventListener("EnterFrame", [=](EventCustom* event) {
		float* data = static_cast<float*>(event->getUserData());
		update(data[0]);
	});
	
}

Wave::~Wave(void)
{
	//delete _object;
}


void Wave::update(float dt)
{

	if (_active && current_enemy < num_enemies) {
	
		current_delay += dt;
	
		if (current_delay >= enemies_delay[current_enemy]) {
	
			Enemy* e = new Enemy(enemies_type[current_enemy], initial_point, path, 20);
			EventCustom event_add_mobile("add_mobile");
			event_add_mobile.setUserData(e);
			_eventDispatcher->dispatchEvent(&event_add_mobile);
			current_enemy++;
			current_delay = 0;

		}

	}
	
}


void Wave::addEnemy(String type, float e_delay) {

	enemies_type[num_enemies] = type;
	enemies_delay[num_enemies] = e_delay;
	num_enemies++;

}

