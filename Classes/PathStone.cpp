#include "PathStone.h"


PathStone::PathStone() {

}


PathStone::PathStone(int number_tiles_2, float seconds_total_2, Point initial_point_2, ccBezierConfig bezier_2) {

	_active = false;
	layer = Layer::create();
	paused_current = 0;
	seconds_current = 0;
	paused_invisible = 0;
	seconds_invisible = 0;
	invisible_helper = NULL;
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

			layer->addChild(stone, 0, ""+i);

			tiles[i] = stone;

		}


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

	if (_active && invisible_helper == NULL) {
		for (int i = 0; i < number_tiles; i++) {

			auto action = CCBezierTo::create(seconds_total, bezier);
			tiles[i]->runAction(action);

		}
		
		invisible_helper = Sprite3D::create("floor.obj", "alquitran.png");
		invisible_helper->setPosition3D(Vec3(initial_point.x, initial_point.y, 0));
		invisible_helper->setRotation3D(Vec3(90, 0, 270));
		invisible_helper->setScale(3);
		//invisible_helper->setVisible(false);
		auto action = CCBezierTo::create(seconds_total, bezier);
		invisible_helper->runAction(action);
		layer->addChild(invisible_helper, 0);
		invisible_helper->setVisible(false);

		layer->setCameraMask(2);
	}

	if (_active && paused_current != number_tiles) {
		
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

		
		seconds_invisible += dt;

		aux = ((float)seconds_total/(200.0f))*(paused_invisible);

		if (seconds_invisible >= aux) {

			float aux_x = invisible_helper->getPositionX();
			float aux_y = invisible_helper->getPositionY();
			invisible_points[paused_invisible] = Point(aux_x, aux_y);
			paused_invisible++;

		}

		if (paused_current == number_tiles && _nextPath != NULL) {
			_nextPath->_active = true;
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
