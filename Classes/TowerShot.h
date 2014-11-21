using namespace std;
#include "cocos2d.h"
#include "Entity.h"
#include <math.h>
USING_NS_CC;

class TowerShot : public Entity
{
	Vec3 _origin;
	Vec3 _direction;
	int _speed;
	int _range;
	float _time;
	Entity* _target;

	//Sprite3D* _sprite;
public:
	//Sprite3D* _sprite;

	TowerShot(Vec3, Entity*);
	~TowerShot(void);

	void TowerShot::update(float dt);

	//Sprite3D* WeaponShot::sprite(void);
};