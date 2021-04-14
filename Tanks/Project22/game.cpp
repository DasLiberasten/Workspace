#include "game.h"
#include "level.h"
#include "wall.h"
#include "base.h"
#include "bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "spawner.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>

Game::Game()
{
	m_isGameActive = true;
	m_clockLastFrame = 0;

	for (int i = 0; i < ObjectsCountMax; i++)
		Game_objects[i] = 0;

	Game_base = 0;
	Game_player1 = 0;
	Game_player2 = 0;

	Game_diedEnemiesCount = 0;
}

void Game::setupSystem()
{
	srand(time(0));

	m_renderSystem.init();
}

void Game::initialize()
{
	shutdown();

	Game_diedEnemiesCount = 0;

	// Загрузка карты
	for (int r = 0; r < LevelRows; r++)
	{
		for (int c = 0; c < LevelColumns; c++)
		{
			char cellSymbol = Map[r][c];

			switch (cellSymbol)
			{
			case Symbol_BrickWall:
			{
				Wall* wall = (Wall*)createObject(GameObjectType_Wall, c, r);
				break;
			}

			case Symbol_SteelWall:
			{
				Wall* wall = (Wall*)createObject(GameObjectType_Wall, c, r);
				wall->setImage(SteelWallImage, SteelWallSymbolColor, SteelWallBackgroundColor);
				wall->setInvulnerability(true);
				break;
			}

			case Symbol_Base:
			{
				Game_base = createObject(GameObjectType_Base, c, r);
				break;
			}

			case Symbol_Player1:
			{
				TankPlayer* player1 = (TankPlayer*)createObject(GameObjectType_TankPlayer, c + 0.5, r + 0.5);
				player1->setColor(Red, White);
				player1->setKeys(0x25, 0x27, 0x26, 0x28, 0x20);
				Game_player1 = player1;

				break;
			}

			case Symbol_Player2:
			{
				TankPlayer* player2 = (TankPlayer*)createObject(GameObjectType_TankPlayer, c + 0.5, r + 0.5);
				player2->setColor(White, Red);
				player2->setKeys('A', 'D', 'W', 'S', 0x09);
				Game_player2 = player2;

				break;
			}

			case Symbol_EnemySpawner:
			{
				createObject(GameObjectType_EnemySpawner, c, r);
				break;
			}
			}
		}
	}
}

bool Game::loop()
{
	// Расчет прошедшего времени
	clock_t clockNow = clock();
	clock_t deltaClock = clockNow - m_clockLastFrame;
	float deltaTime = float(deltaClock) / CLOCKS_PER_SEC;
	m_clockLastFrame = clockNow;

	render();
	update(deltaTime);

	return m_isGameActive;
}

void Game::shutdown()
{
	for (int i = 0; i < ObjectsCountMax; i++)
		if (Game_objects[i] != 0)
		{
			delete Game_objects[i];
			Game_objects[i] = 0;
		}
}

void Game::render()
{
	m_renderSystem.clear();


	// Прорисовка всех объектов
	int objectsCount = 0;
	for (int i = 0; i < ObjectsCountMax; i++)
		if (Game_objects[i] != 0)
		{
			Game_objects[i]->render(&m_renderSystem);
			objectsCount++;
		}




	m_renderSystem.flush();
}

void Game::update(float dt)
{
	for (int i = 0; i < ObjectsCountMax; i++)
		if (Game_objects[i] != 0)
		{
			Game_objects[i]->update(dt);

			if (Game_objects[i]->getHealth() <= 0 && Game_objects[i]->getDestroyAfterDeath())
				destroyObject(Game_objects[i]);
		}


	if (Game_base && Game_base->getHealth() <= 0)
		initialize();


	if (Game_player1 && Game_player1->getHealth() <= 0)
	{
		destroyObject(Game_player1);
		Game_player1 = NULL;
	}


	if (Game_player2 && Game_player2->getHealth() <= 0)
	{
		destroyObject(Game_player2);
		Game_player2 = NULL;
	}


	if (Game_diedEnemiesCount == EnemiesPerLevel)
		initialize();
}

GameObject* Game::checkIntersects(float x, float y, float width, float height, GameObject* exceptObject)
{
	int r00 = int(y);
	int c00 = int(x);
	int r01 = r00 + height - 1;
	int c01 = c00 + width - 1;

	for (int i = 0; i < ObjectsCountMax; i++)
		if (Game_objects[i] != 0 && Game_objects[i]->getPhysical() && Game_objects[i] != exceptObject)
		{
			int r10 = int(Game_objects[i]->getY());
			int c10 = int(Game_objects[i]->getX());
			int r11 = r10 + Game_objects[i]->getHeight() - 1;
			int c11 = c10 + Game_objects[i]->getWidth() - 1;

			if (r00 <= r11 && r01 >= r10 && c00 <= c11 && c01 >= c10)
				return Game_objects[i];
		}

	return 0;
}

bool Game::moveObjectTo(GameObject* object, float x, float y)
{
	int r0 = int(y);
	int c0 = int(x);
	int r1 = r0 + object->getHeight() - 1;
	int c1 = c0 + object->getWidth() - 1;

	if (r0 < 0 || c0 < 0 || r1 >= LevelRows || c1 >= LevelColumns)
		return false;


	bool canMoveToCell = false;

	GameObject* otherObject = checkIntersects(x, y, object->getWidth(), object->getHeight(), object);

	if (otherObject)
		object->intersect(otherObject);
	else
		canMoveToCell = true;


	if (canMoveToCell)
	{
		object->setX(x);
		object->setY(y);
	}

	return canMoveToCell;
}

int Game::getObjectsCount(GameObjectType type)
{
	int totalCount = 0;

	for (int i = 0; i < ObjectsCountMax; i++)
	{
		if (Game_objects[i] == 0)
			continue;

		if (Game_objects[i]->getType() == type)
			totalCount++;
	}

	return totalCount;
}

GameObject* Game::createObject(GameObjectType type, float x, float y)
{

	for (int i = 0; i < ObjectsCountMax; i++)
	{
		if (Game_objects[i] == 0)
		{
			GameObject* object = 0;

			switch (type)
			{
			case GameObjectType_Wall:			object = new Wall();			break;
			case GameObjectType_Base:			object = new Base();			break;
			case GameObjectType_Bullet:			object = new Bullet();			break;
			case GameObjectType_TankPlayer:		object = new TankPlayer();		break;
			case GameObjectType_TankEnemy:		object = new TankEnemy();		break;
			case GameObjectType_EnemySpawner:	object = new EnemySpawner();	break;
			}

			if (object == 0)
				return 0;

			object->setGame(this);

			if (moveObjectTo(object, x, y) == false)
			{
				delete object;
				return 0;
			}

			Game_objects[i] = object;

			return object;
		}
	}

	return 0;
}

void Game::destroyObject(GameObject* object)
{
	for (int i = 0; i < ObjectsCountMax; i++)
	{
		if (Game_objects[i] == object)
		{
			delete Game_objects[i];
			Game_objects[i] = 0;

			return;
		}
	}
}

void Game::increaseDiedEnemiesCount()
{
	Game_diedEnemiesCount++;
}