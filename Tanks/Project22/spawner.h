#pragma once
#include "gameObject.h"
#include "level.h"

class EnemySpawner
	: public GameObject
{
public:
	EnemySpawner();


	virtual void update(float dt);

private:
	float SpawnTimer;
	float SpawnTime;
};