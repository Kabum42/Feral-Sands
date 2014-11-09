using namespace std;
#include "cocos2d.h"
#include <math.h>
USING_NS_CC;

class Tower : public cocos2d::Sprite3D
{

	//Sprite3D* _sprite;
public:
	Sprite3D* _sprite;
	float position_z_tower;

	Tower(void);
	Tower(String s2, Point initial_point_2);
	Tower(Vec3, Vec3);
	Layer* getLayer(void);
	~Tower(void);

	void Tower::update(float dt);

	//Sprite3D* Tower::sprite(void);
};