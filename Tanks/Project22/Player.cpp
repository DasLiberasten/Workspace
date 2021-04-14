#include "Player.h"
#include "utils.h"


//+
TankPlayer::TankPlayer()
{
	Obj_type = GameObjectType_TankPlayer;

	Clicked_keyLeft = 0;
	Clicked_keyRight = 0;
	Clicked_keyUp = 0;
	Clicked_keyDown = 0;
	Clicked_keyFire = 0;

	Obj_health = PlayerHealth;
	Tank_speed = PlayerSpeed;

	Obj_destroy = false;
}

void TankPlayer::update(float dt)
{
	Tank::update(dt);

	if (IsKeyDown(Clicked_keyLeft))
		move(Direction_Left);
	else
		if (IsKeyDown(Clicked_keyRight))
			move(Direction_Right);
		else
			if (IsKeyDown(Clicked_keyUp))
				move(Direction_Up);
			else
				if (IsKeyDown(Clicked_keyDown))
					move(Direction_Down);
				else
				{
					setXSpeed(0);
					setYSpeed(0);
				}

	if (IsKeyDown(Clicked_keyFire))
		fire();
}

void TankPlayer::setKeys(int keyLeft, int keyRight, int keyUp, int keyDown, int keyFire)
{
	Clicked_keyLeft = keyLeft;
	Clicked_keyRight = keyRight;
	Clicked_keyUp = keyUp;
	Clicked_keyDown = keyDown;
	Clicked_keyFire = keyFire;
}