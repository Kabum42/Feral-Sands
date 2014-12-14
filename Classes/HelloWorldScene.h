#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Entity.h"
#include "PathStone.h"
#include "Tower.h"
#include "TowerShot.h"
#include "WeaponShot.h"
#include "FireShot.h"
#include "AirShot.h"
#include "Enemy.h"
#include "Player.h"
#include "Nexus.h"
#include "Wave.h"
#include "Atrezzo.h"
#include "QuadBezier.h"

class HelloWorld : public cocos2d::Layer
{

public:
	float floorSize;
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	// Update Function
	void HelloWorld::update(float dt);

	void HelloWorld::rotateToPoint(cocos2d::Sprite3D* s, cocos2d::Point p);

	void HelloWorld::rotateToVec2(cocos2d::Sprite3D* s, cocos2d::Vec2 v);

	void HelloWorld::removeStaticObject(int num_in_array);

	void HelloWorld::removeMobileObject(int num_in_array);

	void HelloWorld::addMobileObject(Entity* e);
	
	void HelloWorld::addShot(Entity* e);

	void HelloWorld::repulse(Entity* e1, Entity* e2);

	void HelloWorld::static_repulse(Entity* static_e, Entity* mobile_e);

	void HelloWorld::readMapFromFile(const std::string nameOfFile);

    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

};

#endif // __HELLOWORLD_SCENE_H__
