using namespace std;
#include "cocos2d.h"
#include "Entity.h"
USING_NS_CC;

#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Entity
{

	//Sprite3D* _sprite;
public:
	//Sprite3D* _sprite;
	ccBezierConfig _bezier;
	float seconds_enemy;
	float position_z_enemy;
	Point initial_point_enemy;
	Point position1;
	Point position2;
	String s_enemy;
	int scale_enemy;

	Enemy(void);
	Enemy(String s_enemy2, Point initial_point_enemy2, ccBezierConfig bezier_enemy2, float seconds_enemy2);
	~Enemy(void);

	void Enemy::update(float dt);
	void Enemy::rotateToVec2(Sprite3D* s, Vec2 v);

	//Sprite3D* Enemy::sprite(void);
};

#endif