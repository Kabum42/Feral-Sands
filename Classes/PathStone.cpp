#include "PathStone.h"


PathStone::PathStone() {

}


PathStone::PathStone(int number_tiles_2, float seconds_total_2, Point initial_point_2, ccBezierConfig bezier_2) {

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
