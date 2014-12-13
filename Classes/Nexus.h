using namespace std;
#include "cocos2d.h"
#include "Entity.h"
USING_NS_CC;

class Nexus : public Entity
{

public:

	int floorSize;
	float position_z_nexus;
	int _life;

	Nexus(void);
	Nexus(int floorSize2, Point initial_point_2);
	~Nexus(void);

	void Nexus::update(float dt);

};