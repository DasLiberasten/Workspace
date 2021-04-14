#pragma once
#include "render.h"
#include <ctime>
#include "gameObject.h"
#include "gameObjectType.h"


const int ObjectsCountMax = 1024;


class GameObject;


class Game
{
public:
	Game();

	void setupSystem();
	void initialize();
	bool loop();
	void shutdown();

	GameObject* createObject(GameObjectType type, float x, float y);
	void destroyObject(GameObject* object);
	GameObject* checkIntersects(float x, float y, float width, float height, GameObject* exceptObject);
	bool moveObjectTo(GameObject* object, float x, float y);
	int getObjectsCount(GameObjectType type);

	int getDiedEnemiesCount() { return Game_diedEnemiesCount; }
	void increaseDiedEnemiesCount();

private:
	void render();
	void update(float dt);

private:
	bool m_isGameActive;
	clock_t m_clockLastFrame;

	Render m_renderSystem;

	GameObject* Game_objects[ObjectsCountMax];

	GameObject* Game_base;
	GameObject* Game_player1;
	GameObject* Game_player2;

	int Game_diedEnemiesCount;
};
