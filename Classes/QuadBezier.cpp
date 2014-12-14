#include "QuadBezier.h"

QuadBezier::QuadBezier(void) {

}

QuadBezier::QuadBezier(Point initial_point2, Point control_point2, Point end_point2) {

	initial_point = initial_point2;
	control_point = control_point2;
	end_point = end_point2;

}


QuadBezier::~QuadBezier(void)
{
	//delete _object;
}
