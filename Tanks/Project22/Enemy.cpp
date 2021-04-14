#include "Enemy.h"
#include "utils.h"
#include "wall.h"
#include "bullet.h"

//+
TankEnemy::TankEnemy()
{
	Obj_type = GameObjectType_TankEnemy;
	Enemy_analizeTime = EnemyAnalizeTime;
	Enemy_analizeTimer = GetRandomFloat(0.0, Enemy_analizeTime);
	Enemy_lastAnalizeX = 0.0;
	Enemy_lastAnalizeY = 0.0;

	Obj_health = EnemyHealth;
	Tank_speed = EnemySpeed;


	setColor(Gray, DarkGray);
}

TankEnemy::~TankEnemy()
{
	Obj_game->increaseDiedEnemiesCount();
}

void TankEnemy::update(float dt)
{
	Tank::update(dt);

	Enemy_analizeTimer += dt;
	if (Enemy_analizeTimer >= Enemy_analizeTime)
	{
		Enemy_analizeTimer = 0;
		analize();
	}
}

void TankEnemy::analize()
{
	float x = 0.0;
	float y = 0.0;
	calculatePosition(&x, &y);

	float xDelta = 0.0;
	float yDelta = 0.0;

	switch (Obj_direction)
	{
	case Direction_Left: xDelta = -1.0; break;
	case Direction_Right: xDelta = 1.0; break;
	case Direction_Up: yDelta = -1.0; break;
	case Direction_Down: yDelta = 1.0; break;
	}


	GameObject* object = 0;
	int distance = 0;
	do
	{
		object = Obj_game->checkIntersects(x, y, 1, 1, 0);

		x += xDelta;
		y += yDelta;
		++distance;
	} while (object == 0);


	if (object->getType() == GameObjectType_Bullet)
	{
		if (((Bullet*)object)->getOwnerType() == GameObjectType_TankPlayer)
			fire();

		return;
	}


	if (object->getType() == GameObjectType_TankPlayer
		|| object->getType() == GameObjectType_Base)
	{
		fire();
		return;
	}


	if (0 == rand() % 5)
	{
		moveRandomDirection();
		return;
	}


	switch (object->getType())
	{
	case GameObjectType_Wall:
		if (((Wall*)object)->getInvulnerability() == false)
		{
			fire();
			return;
		}
		break;
	}


	if (distance == 1
		|| ((int)Enemy_lastAnalizeX == (int)getX() && (int)Enemy_lastAnalizeY == (int)getY()))
	{
		moveRandomDirection();
		return;
	}

	Enemy_lastAnalizeX = getX();
	Enemy_lastAnalizeY = getY();
}

void TankEnemy::moveRandomDirection()
{
	Direction prevDirection = getDirection();
	Direction newDirection;
	do
	{
		newDirection = (Direction)(rand() % ((int)Direction_MAX));
	} while (prevDirection == newDirection);

	move(newDirection);
}