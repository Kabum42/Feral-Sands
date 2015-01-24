#include "Player.h"

Player::Player(void) {

}

Player::Player(int floorSize2, Point initial_point_player2) {

	floorSize = floorSize2;
	_active = true;
	_resurrect = false;
	_health = 200;
	_injured = 0;
	_type = "player";
	_weapon = 0; // 0: Normal; 1: Fuego; 2: Aire;
	dashing = 0;
	speed = 1.5;
	speed_cooldown = 0;

	normalShooting = false;
	fireShooting = false;
	airCharging = false;

	moving = false;
	forward = true;

	energyN = 100;
	energyF = 100;
	energyA = 100;

	initial_point_player = initial_point_player2;

	scale_player = 40*(floorSize/2048);
	position_z_player = scale_player*4.7;

	_radius = scale_player*0.1;


	//_sprite = Sprite3D::create("Lex_High.obj", "stone.png");
	_sprite = Sprite3D::create("Lex.c3b","Lex_Uved_AO.png");
	_sprite->setPosition3D(Vec3(initial_point_player.x, initial_point_player.y, 0));
	_sprite->setRotation3D(Vec3(90, 0, 180));
	//_sprite->setScale(scale_player);
	_sprite->setScale(0.75);

	weaponModel = Sprite3D::create("Weapon.c3b", "WeaponText.png");
	_sprite->getAttachNode("FemaleBaseMesh:Spine")->addChild(weaponModel);
	weaponModel->setRotation3D(Vec3(90, 90, 0));
	weaponModel->setPosition3D(Vec3(0, -40, 20));
	weaponModel->setScale(12);
	//***********************************************************************************
	//legsLex = _sprite->getAttachNode("FemaleBaseMesh:Spine");
	
	//legsLex = _sprite->getSkeleton()->getBoneByName("FemaleBaseMesh:Spine");
	
	//float translation = 0;
	//float rotation = 0;
	//float scale = 0;
	//legsLex->setAnimationValue(&translation, &rotation, &scale);
	//legsLex->removeAllChildBone();

	/* THIS SHOULD WORK
	skeletonLex = _sprite->getSkeleton();
	skeletonLex->getBoneByName("FemaleBaseMesh:Spine")->removeAllChildBone();

	torsoLex = Sprite3D::create("Lex.c3b", "Lex_Uved_AO.png");
	_sprite->getAttachNode("FemaleBaseMesh:Spine")->addChild(torsoLex);
	torsoLex->setRotation3D(Vec3(0, 45, 45));
	*/
	//torsoLex = Sprite3D::create("Lex.c3b");
	//torsoBoneLex = torsoLex->getSkeleton()->getBoneByName("FemaleBaseMesh:Spine");
	//addChild(torsoLex);

	//legsLex->addChildBone(torsoBoneLex);
	//_sprite->getSkeleton()->getBoneByName("FemaleBaseMesh:Spine")->removeAllChildBone();
	//_sprite->getSkeleton()->getBoneByName("FemaleBaseMesh:Spine")->addChildBone(torsoLex->getSkeleton()->getBoneByName("FemaleBaseMesh:Spine"));
	

	//torsoLex->setRotation3D(Vec3(0, 45, 45));
	
	//_sprite->getSkeleton()->updateBoneMatrix();
	//***************************************************************************************************************

	moveAnimation = Animation3D::create("Lex.c3b");
	moveAnimate = Animate3D::create(moveAnimation);
	moveAnimate->setSpeed(3.0);
	moveAction = RepeatForever::create(moveAnimate);
	_sprite->runAction(moveAction);

	idleAnimation = Animation3D::create("Lex.c3b");
	idleAnimate = Animate3D::create(idleAnimation);
	idleAnimate->setSpeed(-1.0);
	idleAction = RepeatForever::create(idleAnimate);

	//_sprite->runAction(idleAction);
	


	_eventDispatcher->addCustomEventListener("EnterFrame", [=](EventCustom* event) {
		float* data = static_cast<float*>(event->getUserData());
		update(data[0]);
	});
	
	

}


Player::~Player(void)
{
	//delete _object;
}

void Player::update(float dt)
{

	if (_health > 0 && _active && !_resurrect) {

		if (_injured > 0) {

			_injured -= dt;
			if (_injured <= 0) { _sprite->setColor(Color3B(255, 255, 255)); }

		}

		if (dashing > 0) {

			float proportion = 0.5;

			if (dashing > (0.5 - proportion*0.5)) {
				_sprite->setPosition3D(_sprite->getPosition3D() + Vec3(dashingVector.x*(1/proportion)*32767*dt*speed/70, dashingVector.y*(1/proportion)*32767*dt*speed/70, 0));
			}
			else {
				_sprite->setPosition3D(_sprite->getPosition3D() + Vec3(dashingVector.x*(proportion)*32767*dt*speed/70, dashingVector.y*(proportion)*32767*dt*speed/70, 0));
			}

			dashing -= dt;
			if (dashing < 0) { dashing = 0; }
		}

		if (speed_cooldown > 0) {
			speed_cooldown -= dt;
			if (speed_cooldown < 0) { speed_cooldown = 0;}
			speed = 1;
		}
		else {
			speed = 1.5;
		}

	}
	else if (_active && _resurrect) {

		_sprite->setColor(Color3B(255, 255, 255));

		float max_health = 200;
		float seconds_to_full = 2;
		_health += (max_health/seconds_to_full)*dt;

		GLubyte ubyteComponent = static_cast<GLubyte>((_health/max_health) * 255.f); 
		_sprite->setOpacity(ubyteComponent);

		if (_health > max_health) {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("explosion.wav");
			_resurrect = false;
			_health = max_health;

			GLubyte ubyteComponent = static_cast<GLubyte>(255.f); 
			_sprite->setOpacity(ubyteComponent);
		}
	}

	if (energyN < 100 && !normalShooting) energyN += dt * 20; // 40 = 2.5 seg
	if (energyF < 100 && !fireShooting) energyF += dt * 20;
	if (energyA < 100 && !airCharging) energyA += dt * 40;
	
}
