using namespace std;
#include "cocos2d.h"
USING_NS_CC;

#ifndef QUADBEZIER_H
#define QUADBEZIER_H

class QuadBezier
{

public:

	Point initial_point;
	Point control_point;
	Point end_point;

	QuadBezier(void);
	QuadBezier(Point initial_point2, Point control_point2, Point end_point2);
	~QuadBezier(void);
};

#endif