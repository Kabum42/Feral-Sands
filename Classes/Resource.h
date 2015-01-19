using namespace std;
#include "cocos2d.h"
#include "Player.h"
USING_NS_CC;

class Resource : public Entity
{

public:
	float floorSize;
	Player* _player;
	Vec2 escape;
	float time_passed;
	int value;

	Resource(void);
	Resource(int floorSize2, Point initial_point, Player* _player2, int value2);
	~Resource(void);

	void Resource::update(float dt);

};