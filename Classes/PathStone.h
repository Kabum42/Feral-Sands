#ifndef PATHSTONE_H
#define PATHSTONE_H

using namespace std;
#include "cocos2d.h"
USING_NS_CC;

class PathStone : public Sprite3D
{

public:
	bool _active;
	Sprite3D* tiles[50];
	Sprite3D* invisible_helper;
	Point invisible_points[200];
	float seconds_invisible;
	int paused_invisible;
	Layer* layer;
	int number_tiles;
	int paused_current;
	float seconds_total;
	float seconds_current;
	Point initial_point;
	ccBezierConfig bezier;
	PathStone* _nextPath;
	
	PathStone(void);
	PathStone(int number_tiles_2, float seconds_total_2, cocos2d::Point initial_point_2, cocos2d::ccBezierConfig bezier_2);

	void PathStone::update(float dt);
	
	Layer* getLayer();
	void setNextPath(PathStone* nextPath2);

	~PathStone(void);
};

#endif

