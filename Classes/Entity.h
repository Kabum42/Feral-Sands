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
<<<<<<< HEAD
	float _range;		//TOWER
	Entity* _target;	//TOWER
=======
	float _injured;
>>>>>>> origin/master

	Entity(void);
	~Entity(void);

};

#endif