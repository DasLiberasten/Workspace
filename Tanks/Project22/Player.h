#pragma once
#include "tank.h"



class TankPlayer
	: public Tank
{
public:
	TankPlayer();

	void update(float dt);

	void setKeys(int keyLeft, int keyRight, int keyUp, int keyDown, int keyFire);

protected:
	int Clicked_keyLeft;
	int Clicked_keyRight;
	int Clicked_keyUp;
	int Clicked_keyDown;
	int Clicked_keyFire;
};
