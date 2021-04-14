#include "gameObject.h"
#include "level.h"


GameObject::GameObject()
{
	Obj_game = 0;
	Obj_type = GameObjectType_None;

	Obj_x = 0.0;
	Obj_y = 0.0;
	Obj_xSpeed = 0.0;
	Obj_ySpeed = 0.0;

	Obj_width = 1;
	Obj_height = 1;

	Obj_health = 1;
	Obj_destroy = true;
	Obj_invulnerability = false;

	Obj_physical = true;

	Obj_direction = Direction_Up;
}

GameObject::~GameObject()
{

}

void GameObject::render(Render* rs)
{

}

void GameObject::update(float dt)
{
	int oldRow = int(Obj_y);
	int oldColumn = int(Obj_x);

	float newY = Obj_y + Obj_ySpeed * dt;
	float newX = Obj_x + Obj_xSpeed * dt;

	int newRow = int(newY);
	int newColumn = int(newX);


	if (oldColumn != newColumn)
		Obj_game->moveObjectTo(this, newX, Obj_y);
	else
		Obj_x = newX;

	if (oldRow != newRow)
		Obj_game->moveObjectTo(this, Obj_x, newY);
	else
		Obj_y = newY;
}

void GameObject::intersect(GameObject* object)
{

}

void GameObject::doDamage(int damage)
{
	if (getInvulnerability())
		return;

	if (Obj_health > damage)
		Obj_health -= damage;
	else
		Obj_health = 0;
}