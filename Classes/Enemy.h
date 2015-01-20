using namespace std;
#include "cocos2d.h"
#include "Entity.h"
#include "PathStone.h"
#include "Player.h"
USING_NS_CC;

#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Entity
{

public:
	float floorSize;
	bool _principio;
	PathStone* path;
	PathStone* aux_path;
	float aux_distance;
	float seconds_enemy;
	float position_z_enemy;
	Point initial_point_enemy;
	Point position1;
	Point position2;
	String _subtype;
	int scale_enemy;
	bool established_location;
	Point location;
	int num_location;
	float _speed;
	Player* player;
	bool slowed;
	int value;

	Enemy(void);
	Enemy(int floorSize2, String s_enemy2, Point initial_point_enemy2, PathStone* path2, float seconds_enemy2, Player* player2);
	~Enemy(void);

	void Enemy::update(float dt);
	void Enemy::rotateToVec2(Sprite3D* s, Vec2 v);
	void Enemy::harmNexus();
	void Enemy::followPath(float dt);
	void Enemy::followPlayer(float dt);
	void Enemy::recursiveCompare(PathStone* p, bool first_iteration);

	//Sprite3D* Enemy::sprite(void);
};

#endif