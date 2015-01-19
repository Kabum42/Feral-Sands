using namespace std;
#include "cocos2d.h"
#include "Player.h"
USING_NS_CC;

class Resource : public cocos2d::Sprite3D
{

public:
	float floorSize;
	Sprite3D* _sprite;
	Player* _player;

	Resource(void);
	Resource(int floorSize2, Point initial_point, Player* _player2);
	~Resource(void);

	void Resource::update(float dt);

};