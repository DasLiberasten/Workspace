#include "base.h"


//+
Base::Base()
{
	Obj_type = GameObjectType_Base;

	Obj_width = BaseColumns;
	Obj_height = BaseRows;

	Obj_health = BaseHealth;
	Obj_destroy = false;
}


void Base::render(Render* rs)
{
	int row = int(Obj_y);
	int column = int(Obj_x);

	for (int r = 0; r < BaseRows; r++)
		for (int c = 0; c < BaseColumns; c++)
		{
			ConsoleSymbolData sd;

			switch (Obj_health)
			{
			case 3: sd = BaseImageNormal[r][c]; break;
			case 2: sd = BaseImageDamaged[r][c]; break;
			default: sd = BaseImageBroken[r][c]; break;
			}

			rs->drawChar(row + r, column + c, sd.symbol, sd.symbolColor, sd.backgroundColor);
		}
}