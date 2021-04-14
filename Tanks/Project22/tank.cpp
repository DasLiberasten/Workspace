#include "tank.h"
#include "bullet.h"


Tank::Tank()
{
	Obj_type = GameObjectType_Tank;

	Obj_width = TankSize;
	Obj_height = TankSize;

	Tank_speed = 0;
	Tank_CooldownTime = 0.0;

	setColor(DarkGray, Gray);
}

void Tank::update(float dt)
{
	GameObject::update(dt);

	if (Tank_CooldownTime > 0)
		Tank_CooldownTime -= dt;
}

void Tank::render(Render* rs)
{
	GameObject::render(rs);

	int row = int(Obj_y);
	int column = int(Obj_x);

	for (int r = 0; r < TankSize; r++)
		for (int c = 0; c < TankSize; c++)
		{
			ConsoleSymbolData sd = Tank_tankImage[Obj_direction][r][c];
			rs->drawChar(row + r, column + c, sd.symbol, sd.symbolColor, sd.backgroundColor);
		}
}

void Tank::setColor(ConsoleColor tankColor1, ConsoleColor tankColor2)
{
	for (int d = Direction_Left; d < Direction_MAX; d++)
		for (int r = 0; r < TankSize; r++)
			for (int c = 0; c < TankSize; c++)
			{
				Tank_tankImage[d][r][c].symbol = kTankImage[d][r][c].symbol;
				Tank_tankImage[d][r][c].symbolColor = Black;


				switch (kTankImage[d][r][c].symbolColor)
				{
				case TColor_1:
					Tank_tankImage[d][r][c].symbolColor = Black;
					break;

				case TColor_2:
					Tank_tankImage[d][r][c].symbolColor = tankColor1;
					break;

				case TColor_3:
					Tank_tankImage[d][r][c].symbolColor = tankColor2;
					break;
				}


				switch (kTankImage[d][r][c].backgroundColor)
				{
				case TColor_1:
					Tank_tankImage[d][r][c].backgroundColor = Black;
					break;

				case TColor_2:
					Tank_tankImage[d][r][c].backgroundColor = tankColor1;
					break;

				case TColor_3:
					Tank_tankImage[d][r][c].backgroundColor = tankColor2;
					break;
				}
			}
}

void Tank::move(Direction direction)
{
	setDirection(direction);

	setXSpeed(0);
	setYSpeed(0);

	switch (Obj_direction)
	{
	case Direction_Left: setXSpeed(-Tank_speed); break;
	case Direction_Right: setXSpeed(Tank_speed); break;
	case Direction_Up: setYSpeed(-Tank_speed); break;
	case Direction_Down: setYSpeed(Tank_speed); break;
	}
}

void Tank::fire()
{
	if (Tank_CooldownTime > 0)
		return ;

	Tank_CooldownTime = TankCooldown;

	float x = 0.0;
	float y = 0.0;
	float xSpeed = 0.0;
	float ySpeed = 0.0;

	calculatePosition(&x, &y);

	switch (Obj_direction)
	{
	case Direction_Left: xSpeed = -kBulletSpeed; break;
	case Direction_Right: xSpeed = kBulletSpeed; break;
	case Direction_Up: ySpeed = -kBulletSpeed; break;
	case Direction_Down: ySpeed = kBulletSpeed; break;
	}

	Bullet* bullet = (Bullet*)Obj_game->createObject(GameObjectType_Bullet, x, y);
	if (bullet)
	{
		bullet->setOwnerType(Obj_type);
		bullet->setXSpeed(xSpeed);
		bullet->setYSpeed(ySpeed);
	}
}

void Tank::calculatePosition(float* x, float* y)
{
	switch (Obj_direction)
	{
	case Direction_Left:
		(*x) = int(getX()) - 0.01;
		(*y) = int(getY()) + (getHeight() / 2.0);
		break;
	case Direction_Right:
		(*x) = int(getX()) + getHeight() + 0.01;
		(*y) = int(getY()) + (getHeight() / 2.0);
		break;
	case Direction_Up:
		(*y) = int(getY()) - 0.01;
		(*x) = int(getX()) + (getWidth() / 2.0);
		break;
	case Direction_Down:
		(*y) = int(getY()) + getWidth()+0.01;
		(*x) = int(getX()) + (getWidth() / 2.0);
		break;
	}
}
