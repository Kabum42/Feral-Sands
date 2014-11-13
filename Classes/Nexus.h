using namespace std;
#include "cocos2d.h"
#include "Entity.h"
USING_NS_CC;

class Nexus : public Entity
{

	//Sprite3D* _sprite;
public:
	//Sprite3D* _sprite;
	float position_z_nexus;

	Nexus(void);
	Nexus(Point initial_point_2);
	~Nexus(void);

	void Nexus::update(float dt);

	//Sprite3D* Nexus::sprite(void);
};