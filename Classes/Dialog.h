using namespace std;
#include "cocos2d.h"
USING_NS_CC;

#ifndef DIALOG_H
#define DIALOG_H

class Dialog
{

public:
	std::string _text;
	Dialog* _nextDialog;

	Dialog(void);
	Dialog(std::string text2);
	~Dialog(void);

};

#endif