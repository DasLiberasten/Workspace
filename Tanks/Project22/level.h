#pragma once
#include "render.h"
#include "direction.h"



// Level 
const int LevelRows = kScreenRows;
const int LevelColumns = 80;
// Player
const int PlayerHealth = 16;
const int PlayerSpeed = 10;
// Enemy
const int EnemiesPerLevel = 10;
const int EnemiesInOneMoment = 5;
const int EnemyHealth = 2;
const int EnemySpeed = 5;
const float EnemySpawnTime = 10.0;
const float EnemyAnalizeTime = 0.5;
// Base
const int BaseColumns = 8;
const int BaseRows = 2;
const int BaseHealth = 3;
// Map
const char	Symbol_Player1 = '1';
const char	Symbol_Player2 = '2';
const char	Symbol_Tank = 'T';
const char	Symbol_BrickWall = '$';
const char	Symbol_SteelWall = '@';
const char	Symbol_Base = 'B';
const char	Symbol_EnemySpawner = 'S';
// Tank
const float TankCooldown = 0.5;
const int TankSize = 3;
// BrickWall
const char	BrickWallImage = 177;
const ConsoleColor BrickWallSymbolColor = DarkYellow;
const ConsoleColor BrickWallBackgroundColor = DarkRed;
// SteelWall
const char	SteelWallImage = 254;
const ConsoleColor SteelWallSymbolColor = Gray;
const ConsoleColor SteelWallBackgroundColor = DarkGray;
// Bullet data
const float kBulletSpeed = 25.0;
const char kBulletImage = '*';

const char Map[LevelRows][LevelColumns + 1] =
{
	"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
	"@S                                      @@                              S      @",
	"@                                       @@                                     @",
	"@                                       @@                                     @",
	"@   $$   $$   @@@$$$$$$ S         @@@        @@@ S    $$$$$$@@@   $$   $$      @",
	"@             @@@$$$$$$           @@@        @@@      $$$$$$@@@                @",
	"@                                 @@@        @@@                               @",
	"@        $$                       @@@@@@@@@@@@@@                 $$            @",
	"@                                       @@                                     @",
	"@                @@@                    @@             @@@                     @",
	"@                @@@                                   @@@                     @",
	"@@@   @@@$$$     $$$$$$$$$$$$                      $$$$$$$$$$$$     $$$@@@   @@@",
	"@@@   @@@$$      $$$$$$@@$$$$$$                  $$$$$$@@$$$$$$      $$@@@   @@@",
	"@@@   @@@$$$     $$$$$$@@@$$$$$                  $$$$$@@@$$$$$$     $$$@@@   @@@",
	"@                   $$$@@@@@$$$                  $$$@@@@@$$$                   @",
	"@                              @                @                              @",
	"@                                                                              @",
	"@                                                                              @",
	"@   $$$$$$$                                                          $$$$$$$   @",
	"@   $$$$$$$   @@@                                        $$$$$$@@@   $$$$$$$   @",
	"@   $$   $$   @@@                                              @@@   $$   $$   @",
	"@                             2   $$$$$$$$$$$$ 1                               @",
	"@                                 $$B       $$                                 @",
	"@                                 $$        $$                                 @",
	"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
};


enum TankColor
{
	TColor_1,
	TColor_2,
	TColor_3
};

struct TankImageCell
{
	unsigned char symbol;
	TankColor symbolColor;
	TankColor backgroundColor;
};

const TankImageCell kTankImage[Direction_MAX][TankSize][TankSize] =
{
	// Left
	{
		{ { 220, TColor_2, TColor_1 },{ 220, TColor_2, TColor_1 },{ 220, TColor_2, TColor_1 } },
		{ { 196, TColor_3, TColor_1 },{ 5, TColor_3, TColor_2 },{ 221, TColor_2, TColor_1 } },
		{ { 223, TColor_2, TColor_1 },{ 223, TColor_2, TColor_1 },{ 223, TColor_2, TColor_1 } }
	},
	// Up
	{
		{ { 220, TColor_2, TColor_1 },{ 124, TColor_3, TColor_1 },{ 220, TColor_2, TColor_1 } },
		{ { 219, TColor_2, TColor_2 },{ 5, TColor_3, TColor_2 },{ 219, TColor_2, TColor_2 } },
		{ { 223, TColor_2, TColor_1 },{ 0, TColor_1, TColor_1 },{ 223, TColor_2, TColor_1 } }
	},
	//Right
	{
		{ { 220, TColor_2, TColor_1 },{ 220, TColor_2, TColor_1 },{ 220, TColor_2, TColor_1 } },
		{ { 222, TColor_2, TColor_1 },{ 5, TColor_3, TColor_2 },{ 196, TColor_3, TColor_1 } },
		{ { 223, TColor_2, TColor_1 },{ 223, TColor_2, TColor_1 },{ 223, TColor_2, TColor_1 } }
	},
	// Down
	{
		{ { 220, TColor_2, TColor_1 },{ 0, TColor_1, TColor_1 },{ 220, TColor_2, TColor_1 } },
		{ { 219, TColor_2, TColor_2 },{ 5, TColor_3, TColor_2 },{ 219, TColor_2, TColor_2 } },
		{ { 223, TColor_2, TColor_1 },{ 124, TColor_3, TColor_1 },{ 223, TColor_2, TColor_1 } }
	}
};




const ConsoleColor Color01 = Black;
const ConsoleColor Color02 = Gray;
const ConsoleColor Color03 = Red;
const ConsoleColor Color04 = White;

const ConsoleSymbolData BaseImageNormal[BaseRows][BaseColumns] =
{
	{ { 10, Color03, Color01 },{ 220, Color02, Color01 },{ 250, Color01, Color04 },{ 250, Color01, Color04 },{ 250, Color01, Color04 },{ 250, Color01, Color04 },{ 220, Color02, Color01 },{ 10, Color03, Color01 } },
	{ { 0, Color01, Color01 },{ 220, Color02, Color01 },{ 250, Color01, Color04 },{ 170, Color01, Color02 },{ '3', Color01, Color02 },{ 250, Color01, Color04 },{ 220, Color02, Color01 },{ 0, Color01, Color01 } }
};

const ConsoleSymbolData BaseImageDamaged[BaseRows][BaseColumns] =
{
	{ { 0, Color01, Color01 },{ 0, Color01, Color01 },{ 250, Color01, Color04 },{ 250, Color01, Color04 },{ 0, Color01, Color01 },{ 250, Color01, Color04 },{ 220, Color02, Color01 },{ 10, Color03, Color01 } },
	{ { 0, Color01, Color01 },{ 220, Color02, Color01 },{ 250, Color01, Color04 },{ 170, Color02, Color01 },{ '2', Color02, Color01 },{ 250, Color01, Color04 },{ 220, Color02, Color01 },{ 0, Color01, Color01 } }
};

const ConsoleSymbolData BaseImageBroken[BaseRows][BaseColumns] =
{
	{ { 0, Color01, Color01 },{ 0, Color01, Color01 },{ 0, Color01, Color01 },{ 250, Color01, Color04 },{ 0, Color04, Color01 },{ 250, Color01, Color04 },{ 220, Color02, Color01 },{ 10, Color01, Color01 } },
	{ { 0, Color01, Color01 },{ 0, Color01, Color01 },{ 250, Color01, Color04 },{ 170, Color01, Color01 },{ '1', Color02, Color01 },{ 250, Color01, Color04 },{ 220, Color02, Color01 },{ 0, Color01, Color01 } }
};




