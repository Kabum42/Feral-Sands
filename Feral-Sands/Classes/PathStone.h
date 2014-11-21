#pragma once

#include "cocos2d.h"

class PathStone
{
public:
	
	PathStone::PathStone();
	PathStone::PathStone(int number_tiles_2, float seconds_total_2, cocos2d::Point initial_point_2, cocos2d::ccBezierConfig bezier_2);

	void PathStone::update(float dt);
	
	cocos2d::Layer* getLayer();

	void PathStone::deleteThis(void);

	~PathStone(void);
};

