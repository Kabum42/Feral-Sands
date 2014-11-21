using namespace std;
#include "cocos2d.h"
#include "Entity.h"
USING_NS_CC;

class Nexus : public Entity
{

public:

	float position_z_nexus;
	int _life;

	Nexus(void);
	Nexus(Point initial_point_2);
	~Nexus(void);

	void Nexus::update(float dt);

	//Sprite3D* Nexus::sprite(void);
};