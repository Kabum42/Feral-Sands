using namespace std;
#include "cocos2d.h"
#include "Entity.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

#ifndef PLAYER_H
#define PLAYER_H

class Player : public Entity
{

public:
	float floorSize;
	Point initial_point_player;
	int scale_player;
	float position_z_player;
	float dashing;
	Vec2 dashingVector;
	int _weapon;
	bool _resurrect;

	float speed;
	float speed_cooldown;

	Player(void);
	Player(int floorSize2, Point initial_point_Player2);
	~Player(void);

	void Player::update(float dt);

	//Sprite3D* Player::sprite(void);
};

#endif
