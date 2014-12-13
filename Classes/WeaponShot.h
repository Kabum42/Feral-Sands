using namespace std;
#include "cocos2d.h"
#include "Entity.h"
#include <math.h>
USING_NS_CC;

class WeaponShot : public Entity
{
	int floorSize;
	Vec3 _origin;
	Vec3 _direction;
	int _speed;
	int _range;
	float _time;
	float _timeLimit;

	//Sprite3D* _sprite;
public:
	//Sprite3D* _sprite;

	WeaponShot(int floorSize2, Vec3, Vec3);
	~WeaponShot(void);

	void WeaponShot::update(float dt);

	//Sprite3D* WeaponShot::sprite(void);
};