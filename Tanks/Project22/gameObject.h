#pragma once
#include "render.h"
#include "direction.h"
#include "game.h"
#include "gameObjectType.h"


class Game;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();


	virtual void render(Render* rs);
	virtual void update(float dt);

	virtual void intersect(GameObject* object);

	GameObjectType getType() { return Obj_type; }

	void setGame(Game* game) { Obj_game = game; }

	void setX(float x) { Obj_x = x; }
	float getX() { return Obj_x; }

	void setY(float y) { Obj_y = y; }
	float getY() { return Obj_y; }

	void setXSpeed(float xSpeed) { Obj_xSpeed = xSpeed; }
	float getXSpeed() { return Obj_xSpeed; }

	void setYSpeed(float ySpeed) { Obj_ySpeed = ySpeed; }
	float getYSpeed() { return Obj_ySpeed; }

	void setWidth(int width) { Obj_width = width; }
	int getWidth() { return Obj_width; }

	void setHeight(int height) { Obj_height = height; }
	int getHeight() { return Obj_height; }

	void setHealth(int health) { Obj_health = health; }
	int getHealth() { return Obj_health; }

	void setDestroyAfterDeath(bool destroyAfterDeath) { Obj_destroy = destroyAfterDeath; }
	bool getDestroyAfterDeath() { return Obj_destroy; }

	void setInvulnerability(bool invulnerable) { Obj_invulnerability = invulnerable; }
	bool getInvulnerability() { return Obj_invulnerability; }

	void setPhysical(bool physical) { Obj_physical = physical; }
	bool getPhysical() { return Obj_physical; }

	void setDirection(Direction direction) { Obj_direction = direction; }
	Direction getDirection() { return Obj_direction; }

	void doDamage(int damage);

protected:
	Game* Obj_game;
	GameObjectType Obj_type;

	float Obj_x;
	float Obj_y;
	float Obj_xSpeed;
	float Obj_ySpeed;

	int Obj_width;
	int Obj_height;

	int Obj_health;
	bool Obj_destroy;
	bool Obj_invulnerability;

	bool Obj_physical;

	Direction Obj_direction;
};

