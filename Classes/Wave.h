using namespace std;
#include "cocos2d.h"
#include "Enemy.h"
#include "PathStone.h"
USING_NS_CC;



class Wave : public Sprite3D
{

public:
	bool _active;
	String enemies_type [50];
	float enemies_delay [50];
	int num_enemies;
	int current_enemy;
	float current_delay;
	Point initial_point;
	//ccBezierConfig bezier;
	PathStone* path;
	Enemy* lol;

	Wave(Point initial_point2, PathStone* path2);
	~Wave(void);

	void update(float dt);
	void addEnemy(String type, float e_delay);
};

