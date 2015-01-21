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
	Animation3D* moveAnimation;
	Animate3D* moveAnimate;
	Action* moveAction;
	//Mesh* legsLex;
	//AttachNode* legsLex;
	Bone3D* legsLex;
	//Skeleton3D* skeletonLex;
	Sprite3D* torsoLex;
	Bone3D* torsoBoneLex;
	Sprite3D* weaponModel;

	Animation3D* idleAnimation;
	Animate3D* idleAnimate;
	Action* idleAction;

	bool moving;
	bool forward;

	float floorSize;
	Point initial_point_player;
	int scale_player;
	float position_z_player;
	float dashing;
	Vec2 dashingVector;
	int _weapon;
	bool _resurrect;

	bool normalShooting;
	bool fireShooting;
	bool airCharging;

	float energyN;
	float energyF;
	float energyA;

	float speed;
	float speed_cooldown;

	Player(void);
	Player(int floorSize2, Point initial_point_Player2);
	~Player(void);

	void Player::update(float dt);

	//Sprite3D* Player::sprite(void);
};

#endif
