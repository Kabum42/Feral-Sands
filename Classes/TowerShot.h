#ifndef TOWERSHOT_H
#define TOWERSHOT_H

using namespace std;
#include "cocos2d.h"
#include "Entity.h"
#include <math.h>
#include "SimpleAudioEngine.h"
USING_NS_CC;

class TowerShot : public Entity
{
public:

	int _speed;
	Vec3 _direction;
	float _distance;
	int _damage;

	TowerShot(Vec3, Entity*);
	~TowerShot(void);
	
	void TowerShot::update(float dt);
};

#endif