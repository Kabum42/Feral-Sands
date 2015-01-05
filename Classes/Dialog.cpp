#include "Dialog.h"

Dialog::Dialog(void) {

}

Dialog::Dialog(String text2) {

	_text = text2;
	_nextDialog = NULL;

}

Dialog::~Dialog(void)
{
	//delete _object;
	// CAMBIAR TRANSPARENCIA (DE 0 a 255)
	// _sprite->setOpacity(128);
}








