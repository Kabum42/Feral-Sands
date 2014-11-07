using namespace std;
#include "cocos2d.h"
#include <math.h>
USING_NS_CC;

class WeaponShot : public cocos2d::Sprite3D
{
	Vec3 _origin;
	Vec3 _direction;
	int _speed;
	int _range;

	//Sprite3D* _sprite;
public:
	Sprite3D* _sprite;

	WeaponShot(Vec3, Vec3);
	~WeaponShot(void);

	void WeaponShot::update(void);

	//Sprite3D* WeaponShot::sprite(void);
};