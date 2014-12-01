using namespace std;
#include "cocos2d.h"
#include "Entity.h"
#include "PathStone.h"
USING_NS_CC;

#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Entity
{

public:
	bool _principio;
	PathStone* path;
	float seconds_enemy;
	float position_z_enemy;
	Point initial_point_enemy;
	Point position1;
	Point position2;
	String s_enemy;
	int scale_enemy;
	bool established_location;
	Point location;
	int num_location;

	Enemy(void);
	Enemy(String s_enemy2, Point initial_point_enemy2, PathStone* path2, float seconds_enemy2);
	~Enemy(void);

	void Enemy::update(float dt);
	void Enemy::rotateToVec2(Sprite3D* s, Vec2 v);
	void Enemy::harmNexus();
	void Enemy::chooseLocation();

	//Sprite3D* Enemy::sprite(void);
};

#endif