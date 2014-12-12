#include "PathStone.h"


PathStone::PathStone() {

}


PathStone::PathStone(int number_tiles_2, QuadBezier* bezier_2) {

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
		
			Sprite3D* stone = Sprite3D::create("Floor.obj", "stone.png");
			stone->setPosition3D(Vec3(aux_x, aux_y, 0));
			stone->setRotation3D(Vec3(90, 0, 270));
			stone->setScale(100);

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
				if ((data->x - point_sprite->x) < 1750 && (data->x - point_sprite->x) > -1750 &&
					(data->y - point_sprite->y) < 600 && (data->y - point_sprite->y) > -1750) { distance_bool = true; }
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
