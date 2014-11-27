using namespace std;
#include "cocos2d.h"
#include "Entity.h"
USING_NS_CC;

class Atrezzo : public Entity
{

public:

	//int _life;

	Atrezzo(void);
	Atrezzo(Point initial_point_2, String type2);
	~Atrezzo(void);

};