#include "spawner.h"
#include "Enemy.h"
#include "utils.h"



EnemySpawner::EnemySpawner()
{
	Obj_type = GameObjectType_EnemySpawner;


	SpawnTime = EnemySpawnTime;
	SpawnTimer = GetRandomFloat(0.0, SpawnTime);

	Obj_physical = false;
}


void EnemySpawner::update(float dt)
{
	GameObject::update(dt);

	SpawnTimer += dt;

	if (SpawnTimer > SpawnTime)
	{
		SpawnTimer = 0;

		int enemiesOnLevel = Obj_game->getObjectsCount(GameObjectType_TankEnemy);
		int enemiesStorageLeft = EnemiesPerLevel - enemiesOnLevel - Obj_game->getDiedEnemiesCount();

		if (enemiesStorageLeft > 0 && enemiesOnLevel < EnemiesInOneMoment)
			Obj_game->createObject(GameObjectType_TankEnemy, getX(), getY());
	}
}