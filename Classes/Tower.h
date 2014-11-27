using namespace std;
#include "cocos2d.h"
#include "Entity.h"
#include "TowerShot.h"
USING_NS_CC;

class Tower : public Entity
{
	float _cooldown;
public:
	float position_z_tower;

	Tower(void);
	Tower(String s2, Point initial_point_2);
	~Tower(void);

	void Tower::update(float dt);
};