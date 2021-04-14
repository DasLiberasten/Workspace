#include "wall.h"

//+
Wall::Wall()
{
	Obj_type = GameObjectType_Wall;

	setImage(BrickWallImage, BrickWallSymbolColor, BrickWallBackgroundColor);
}


void Wall::render(Render* rs)
{
	int row = int(Obj_y);
	int column = int(Obj_x);

	rs->drawChar(row, column, Wall_image.symbol, Wall_image.symbolColor, Wall_image.backgroundColor);
}

void Wall::setImage(unsigned char symbol, ConsoleColor symbolColor, ConsoleColor bgColor)
{
	Wall_image.symbol = symbol;
	Wall_image.symbolColor = symbolColor;
	Wall_image.backgroundColor = bgColor;
}