#pragma once
#include "gameObject.h"
#include "level.h"



class Tank
	: public GameObject
{
public:
	Tank();

	virtual void update(float dt);
	virtual void render(Render* rs);

	void setColor(ConsoleColor tankColor1, ConsoleColor tankColor2);

	void move(Direction direction);
	void fire();


protected:
	void calculatePosition(float* x, float* y);

protected:
	ConsoleSymbolData Tank_tankImage[Direction_MAX][TankSize][TankSize];

	float Tank_CooldownTime;
	float Tank_speed;
};
