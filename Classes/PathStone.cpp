#include "PathStone.h"


PathStone::PathStone() {

}


PathStone::PathStone(int number_tiles_2, float seconds_total_2, Point initial_point_2, ccBezierConfig bezier_2) {

	_active = true;
	layer = Layer::create();
	paused_current = 0;
	seconds_current = 0;
	number_tiles = number_tiles_2;
	seconds_total = seconds_total_2;
	initial_point = initial_point_2;
	bezier = bezier_2;
	_nextPath = NULL;


	for (int i = 0; i < number_tiles; i++) {

		Sprite3D* stone = Sprite3D::create("floor.obj", "stone.png");
		stone->setPosition3D(Vec3(initial_point.x, initial_point.y, 0));
		stone->setRotation3D(Vec3(90, 0, 270));
		stone->setScale(3);
		auto action = CCBezierTo::create(seconds_total, bezier);
		stone->runAction(action);

		layer->addChild(stone, 0, ""+i);

		tiles[i] = stone;

	}

	layer->setCameraMask(2);

	_eventDispatcher->addCustomEventListener("EnterFrame", [=](EventCustom* event) {
		float* data = static_cast<float*>(event->getUserData());
		update(data[0]);
	});

	_eventDispatcher->addCustomEventListener("checkVisible", [=](EventCustom* event) {	
		if (_active) {
			
			Point* data = static_cast<Point*>(event->getUserData());

			for (int i = 0; i < number_tiles; i++) {

				Point* point_sprite = new Point(tiles[i]->getPositionX(), tiles[i]->getPositionY());
				bool distance_bool = false;
				if ((data->x - point_sprite->x) < 1750 && (data->x - point_sprite->x) > -1750 &&
					(data->y - point_sprite->y) < 600 && (data->y - point_sprite->y) > -1750) { distance_bool = true; }
				if (distance_bool && !tiles[i]->isVisible()) {
					tiles[i]->setVisible(true);
				}
				else if (!distance_bool && tiles[i]->isVisible()) {
					tiles[i]->setVisible(false);
				}

			}

		}
	});

}



void PathStone::update(float dt) {

	if (paused_current != number_tiles) {
		
		if (paused_current == 0) {
			tiles[paused_current]->pauseSchedulerAndActions();
			paused_current++;
		}
		
		seconds_current += dt;

		float aux = (seconds_total/(number_tiles-1))*(paused_current);

		if (seconds_current >= aux) {

			tiles[paused_current]->pauseSchedulerAndActions();
			paused_current++;

		}
		
	}

}



Layer* PathStone::getLayer() {

	return layer;

}

void PathStone::setNextPath(PathStone* nextPath2) {

	_nextPath = nextPath2;

}



PathStone::~PathStone(void)
{
}
