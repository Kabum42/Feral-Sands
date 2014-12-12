using namespace std;
#include "cocos2d.h"
#include "Entity.h"
#include <math.h>
USING_NS_CC;

class FireShot : public Entity
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
	float _damage;
	FireShot(Vec3, Vec3);
	~FireShot(void);

	void FireShot::update(float dt);

	//Sprite3D* WeaponShot::sprite(void);
};