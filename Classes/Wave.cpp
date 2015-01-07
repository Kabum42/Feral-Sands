#include "Wave.h"

Wave::Wave(int floorSize2, PathStone* path2, Player* player2) {
	
	floorSize = floorSize2;
	_active = false;
	current_delay = 0;
	initial_point = path2->initial_point;
	//bezier = bezier2;
	path = path2;
	num_enemies = 0;
	current_enemy = 0;
	player = player2;

	// ESTO NO SE USA PARA NADA; SOLO PARA CREAR UN ENEMIGO AL VUELO DESDE WAVE Y QUE NO HAYA UN DELAY A POSTERIORI
	Enemy* e = new Enemy(floorSize, "grunt", initial_point, path, 20, player);
	e = new Enemy(floorSize, "dog", initial_point, path, 20, player);
	e = new Enemy(floorSize, "ghost", initial_point, path, 20, player);
	e = new Enemy(floorSize, "tank", initial_point, path, 20, player);
	
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
	
			Enemy* e = new Enemy(floorSize, enemies_type[current_enemy], initial_point, path, 20, player);
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

