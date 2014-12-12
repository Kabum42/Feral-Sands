using namespace std;
#include "cocos2d.h"
#include "Entity.h"
#include <math.h>
USING_NS_CC;

class AirShot : public Entity
{
	Vec3 _origin;
	
	int _range;
	float _time;
	float _timeLimit;

	//Sprite3D* _sprite;
public:
	//Sprite3D* _sprite;
	Vec3 _direction;
	float _speed;
	int _deacceleration;
	int _shrink;
	float _power;
	float _damage;
	AirShot(Vec3, Vec3, float);
	~AirShot(void);

	void AirShot::update(float dt);

	//Sprite3D* WeaponShot::sprite(void);
};