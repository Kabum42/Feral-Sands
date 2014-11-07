#include "PathStone.h"

USING_NS_CC;

Layer* layer = Layer::create();

//Sprite3D* *tiles;
Sprite3D* tiles [50] = { };

int number_tiles;
int paused_current = 0;
float seconds_total;
float seconds_current = 0;
Point initial_point;
ccBezierConfig bezier;


PathStone::PathStone() {

}

PathStone::PathStone(int number_tiles_2, float seconds_total_2, Point initial_point_2, ccBezierConfig bezier_2) {

	//tiles = new Sprite3D*[number_tiles];
	number_tiles = number_tiles_2;
	seconds_total = seconds_total_2;
	initial_point = initial_point_2;
	bezier = bezier_2;


	for (int i = 0; i < number_tiles; i++) {

		auto stone = Sprite3D::create("plano2.obj", "stone.png");
		stone->setPosition3D(Vec3(initial_point.x, initial_point.y, 0));
		stone->setRotation3D(Vec3(90, 0, 270));
		stone->setScale(3);
		//stone->setCameraMask(2);
		layer->addChild(stone, 0);

		tiles[i] = stone;

		auto action = CCBezierTo::create(seconds_total, bezier);
    
		stone->runAction(action);

	}

	layer->setCameraMask(2);

}

void PathStone::update(float dt) {

	if (paused_current != number_tiles) {

		seconds_current += dt;

		float aux = (seconds_total/number_tiles)*(paused_current+1);

		if (seconds_current >= aux) {

			tiles[paused_current]->pauseSchedulerAndActions();
			paused_current++;

		}

	}

}

Layer* PathStone::getLayer() {

	return layer;

}

void PathStone::deleteThis() {
	delete [] tiles;
}


PathStone::~PathStone(void)
{
}
