using namespace std;
#include "cocos2d.h"
#include "Enemy.h"
#include "PathStone.h"
#include "Player.h"
USING_NS_CC;



class Wave : public Sprite3D
{

public:
	float floorSize;
	bool _active;
	String enemies_type [50];
	float enemies_delay [50];
	int num_enemies;
	int current_enemy;
	float current_delay;
	Point initial_point;
	PathStone* path;
	Player* player;

	Wave(int floorSize2, PathStone* path2, Player* player2);
	~Wave(void);

	void update(float dt);
	void addEnemy(String type, float e_delay);
};

