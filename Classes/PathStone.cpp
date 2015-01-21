#include "PathStone.h"


PathStone::PathStone() {

}


PathStone::PathStone(int floorSize2, int number_tiles_2, QuadBezier* bezier_2) {

	floorSize = floorSize2;
	_active = true;
	layer = Layer::create();
	number_tiles = number_tiles_2;
	bezier = bezier_2;
	initial_point = bezier->initial_point;
	_nextPath = NULL;


	for (int i = 0; i < number_tiles; i++) {

		float t = (float)i/(float)number_tiles;

		float aux_x = (float)bezier->initial_point.x*(float)pow((float)(1 - t), 2)
			+ (float)bezier->control_point.x*2*(float)(1 - t)*t
			+ (float)bezier->end_point.x*(float)pow(t, 2);

		float aux_y = (float)bezier->initial_point.y*(float)pow((float)(1 - t), 2)
			+ (float)bezier->control_point.y*2*(float)(1 - t)*t
			+ (float)bezier->end_point.y*(float)pow(t, 2);

		Sprite3D* stone = Sprite3D::create("PathStone.obj", "PathStoneText.png");
		stone->setPosition3D(Vec3(aux_x, aux_y, 0));
		stone->setRotation3D(Vec3(90, 0, 270));
		stone->setScale(20*(floorSize/2048));

		layer->addChild(stone, 0);

		tiles[i] = stone;

	}

	layer->setCameraMask(2);

	for (int i = 0; i < 200; i++) {

		float t = (float)i/(float)200;

		float aux_x = (float)bezier->initial_point.x*(float)pow((float)(1 - t), 2)
			+ (float)bezier->control_point.x*2*(float)(1 - t)*t
			+ (float)bezier->end_point.x*(float)pow(t, 2);

		float aux_y = (float)bezier->initial_point.y*(float)pow((float)(1 - t), 2)
			+ (float)bezier->control_point.y*2*(float)(1 - t)*t
			+ (float)bezier->end_point.y*(float)pow(t, 2);
		
		Point p = Point(aux_x, aux_y);
		invisible_points[i] = p;

	}

	// ESTO SIRVE PARA ORIENTAR LOS TILES
	for (int i = 0; i < number_tiles; i++) {

		int invisible_point_similar = ceil((float(float(i)/float(number_tiles))*200)+1);
		if (invisible_point_similar > 200) { invisible_point_similar = 200; }
		//CCLOG("This is a madafacking number: %d", invisible_point_similar);

		rotateToPoint(tiles[i], invisible_points[invisible_point_similar]);

		/*
		// VARIACIONES

		// VARIACION DE TAMAÑO
		int size_variation = 20;
		int aux_scale = tiles[i]->getScale()*float((100 - size_variation) + rand() % (size_variation*2))/100;
		tiles[i]->setScale(aux_scale);

		// VARIACION DE ROTACION
		int angle_variation = 10;
		int aux_angle = tiles[i]->getRotation3D().z - angle_variation + rand()%(angle_variation*2);
		tiles[i]->setRotation3D(Vec3(90, 0, aux_angle));
		*/

	}


	_eventDispatcher->addCustomEventListener("EnterFrame", [=](EventCustom* event) {
		float* data = static_cast<float*>(event->getUserData());
		update(data[0]);
	});

	_eventDispatcher->addCustomEventListener("checkVisible", [=](EventCustom* event) {	
		if (_active) {
			
			Point* data = static_cast<Point*>(event->getUserData());

			for (int i = 0; i < number_tiles; i++) {

				Point* point_sprite = new Point(tiles[i]->getPositionX(), tiles[i]->getPositionY());
				bool distance_bool = false;
				if ((data->x - point_sprite->x) < (350*(floorSize/2048)) && (data->x - point_sprite->x) > -(350*(floorSize/2048)) &&
				(data->y - point_sprite->y) < (120*(floorSize/2048)) && (data->y - point_sprite->y) > -(350*(floorSize/2048))) { distance_bool = true; }
				if (distance_bool && !tiles[i]->isVisible()) {
					tiles[i]->setVisible(true);
				}
				else if (!distance_bool && tiles[i]->isVisible()) {
					tiles[i]->setVisible(false);
				}

			}

		}
	});

}



void PathStone::update(float dt) {

}



Layer* PathStone::getLayer() {

	return layer;

}

void PathStone::setNextPath(PathStone* nextPath2) {

	_nextPath = nextPath2;

}



PathStone::~PathStone(void)
{
}

void PathStone::rotateToPoint(Sprite3D* s, Point p) {

	float vec_x = p.x - s->getPositionX();
	float vec_y = p.y - s->getPositionY();

	s->setRotation3D(Vec3(90, 0, -90 - atan2(vec_y, vec_x)*360/(2*M_PI)));

}
