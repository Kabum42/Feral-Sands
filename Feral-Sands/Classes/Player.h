using namespace std;
#include "cocos2d.h"
#include "Entity.h"
USING_NS_CC;

class Player : public Entity
{

public:

	Point initial_point_player;
	int scale_player;
	float position_z_player;

	Player(void);
	Player(Point initial_point_Player2);
	~Player(void);

	void Player::update(float dt);

	//Sprite3D* Player::sprite(void);
};