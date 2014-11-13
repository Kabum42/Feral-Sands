#ifndef ENTITY_H
#define ENTITY_H

using namespace std;
#include "cocos2d.h"
USING_NS_CC;

class Entity : public cocos2d::Sprite3D
{

public:

	Sprite3D* _sprite;
	float _radius;

	Entity(void);
	~Entity(void);

};

#endif