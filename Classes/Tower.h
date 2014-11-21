using namespace std;
#include "cocos2d.h"
#include "Entity.h"
USING_NS_CC;

class Tower : public Entity
{
	//Sprite3D* _sprite;
	int _cooldown;
public:
	//Sprite3D* _sprite;
	float position_z_tower;
	//float _range;

	Tower(void);
	Tower(String s2, Point initial_point_2);
	~Tower(void);

	void Tower::update(float dt);


	//Sprite3D* Tower::sprite(void);
};