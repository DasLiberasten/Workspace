#include "bullet.h"
#include "wall.h"


//+
Bullet::Bullet()
{
	Obj_type = GameObjectType_Bullet;
	m_ownerType = GameObjectType_None;

	setImage(kBulletImage, DarkGray, Black);
}


void Bullet::render(Render* rs)
{
	int row = int(Obj_y);
	int column = int(Obj_x);

	rs->drawChar(row, column, m_image.symbol, m_image.symbolColor, m_image.backgroundColor);
}

void Bullet::intersect(GameObject* object)
{

	setHealth(0);

	object->doDamage(1);
}

void Bullet::setImage(char symbol, ConsoleColor symbolColor, ConsoleColor bgColor)
{
	m_image.symbol = symbol;
	m_image.symbolColor = symbolColor;
	m_image.backgroundColor = bgColor;
}