#include "Tower.h"

USING_NS_CC;

Layer* layer_tower = Layer::create();

String s;
Point initial_point_tower;
float position_z_tower = 0;
Sprite3D* tower;
int scale_tower;


Tower::Tower() {

}

Tower::Tower(String s2, Point initial_point_2) {

	//tiles = new Sprite3D*[number_tiles];
	s = s2;
	initial_point_tower = initial_point_2;

	scale_tower = 3;

	position_z_tower = -90*scale_tower;

	tower = Sprite3D::create("tower.obj", "stone.png");
	tower->setPosition3D(Vec3(initial_point_tower.x, initial_point_tower.y, position_z_tower));
	tower->setRotation3D(Vec3(90, 0, 270));
	tower->setScale(scale_tower);
	//stone->setCameraMask(2);
	layer_tower->addChild(tower, 0);

	layer_tower->setCameraMask(2);

}

void Tower::update(float dt) {

	if (position_z_tower < 0) {

		position_z_tower += dt*scale_tower*50;
		tower->setPositionZ(position_z_tower);

	}

}

Layer* Tower::getLayer() {

	return layer_tower;

}

void Tower::deleteThis() {
	
}


Tower::~Tower(void)
{
}
