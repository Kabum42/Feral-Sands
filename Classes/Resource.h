using namespace std;
#include "cocos2d.h"
USING_NS_CC;

class Resource : public cocos2d::Sprite3D
{

public:

	Sprite3D* _sprite;
	Player* _player;

	Resource(void);
	Resource(Point initial_point, Player* _player2);
	~Resource(void);

	void Resource::update(float dt);

};