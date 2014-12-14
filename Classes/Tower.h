using namespace std;
#include "cocos2d.h"
#include "Entity.h"
#include "TowerShot.h"
USING_NS_CC;

class Tower : public Entity
{
	
public:

	float floorSize;
	float _cooldown;
	float position_z_tower;
	String _subtype;

	Tower(void);
	Tower(int floorSize2, String s2, Point initial_point_2);
	~Tower(void);

	void Tower::update(float dt);
};