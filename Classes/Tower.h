#pragma once

#include "cocos2d.h"

class Tower
{
public:
	
	Tower::Tower();
	Tower::Tower(cocos2d::String s2, cocos2d::Point initial_point_2);

	void Tower::update(float dt);
	
	cocos2d::Layer* getLayer();

	void Tower::deleteThis(void);

	~Tower(void);
};