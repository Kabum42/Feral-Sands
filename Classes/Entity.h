#ifndef ENTITY_H
#define ENTITY_H

using namespace std;
#include "cocos2d.h"
USING_NS_CC;

class Entity : public cocos2d::Sprite3D
{

public:

	bool _active;
	Sprite3D* _sprite;
	float _radius;
	int _num_in_array;
	String _type;
	float _health;

	float _range;		//TOWER
	Entity* _target;	//TOWER

	Vec3 _displacement;

	float _injured;

	Entity(void);
	~Entity(void);

};

#endif