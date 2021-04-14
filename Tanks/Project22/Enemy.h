#pragma once
#include "tank.h"



class TankEnemy
	: public Tank
{
public:
	TankEnemy();
	~TankEnemy();

	void update(float dt);

protected:

	void analize();
	void moveRandomDirection();

protected:
	float Enemy_analizeTimer;
	float Enemy_analizeTime;

	float Enemy_lastAnalizeX;
	float Enemy_lastAnalizeY;
};
