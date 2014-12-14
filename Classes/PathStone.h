#ifndef PATHSTONE_H
#define PATHSTONE_H

using namespace std;
#include "cocos2d.h"
#include "QuadBezier.h"
USING_NS_CC;

class PathStone : public Sprite3D
{

public:
	float floorSize;
	bool _active;
	Sprite3D* tiles[50];
	Point invisible_points[200];
	Layer* layer;
	int number_tiles;
	Point initial_point;
	QuadBezier* bezier;
	PathStone* _nextPath;
	
	PathStone(void);
	PathStone(int floorSize2, int number_tiles_2, QuadBezier* bezier_2);

	void PathStone::update(float dt);
	
	Layer* getLayer();
	void setNextPath(PathStone* nextPath2);

	~PathStone(void);
};

#endif

