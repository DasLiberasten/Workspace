#include "render.h"
#include <cstdio>


// +
Render::Render()
{
	ConsoleHandle = 0;

	for (int r = 0; r < kScreenRows; r++)
	{
		for (int c = 0; c < kScreenColumns; c++)
		{
			Picture_backBuffer[r][c].symbol = 0;
			Picture_backBuffer[r][c].symbolColor = Gray;
			Picture_backBuffer[r][c].backgroundColor = Black;

			Picture_screenBuffer[r][c] = Picture_backBuffer[r][c];
		}
	}
}

void Render::init()
{
	ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(ConsoleHandle, &cursorInfo);
}

void Render::clear()
{
	for (int r = 0; r < kScreenRows; r++)
	{
		for (int c = 0; c < kScreenColumns; c++)
		{
			Picture_backBuffer[r][c].symbol = 0;
			Picture_backBuffer[r][c].backgroundColor = Black;
		}
	}
}

void Render::drawChar(int r, int c, char symbol, ConsoleColor symbolColor, ConsoleColor backgroundColor)
{
	if (r < 0 || c < 0 || r >= kScreenRows || c >= kScreenColumns)
		return;

	Picture_backBuffer[r][c].symbol = symbol;
	Picture_backBuffer[r][c].symbolColor = symbolColor;
	Picture_backBuffer[r][c].backgroundColor = backgroundColor;
}

void Render::drawText(int r, int c, const char* text, ConsoleColor symbolColor, ConsoleColor backgroundColor)
{
	int column = c;
	char symbol = *text;

	while (symbol != 0)
	{
		drawChar(r, column, symbol, symbolColor, backgroundColor);

		text++;
		column++;
		symbol = *text;
	}
}

void Render::flush()
{
	bool screenBufferModified = false;

	for (int r = 0; r < kScreenRows; r++)
	{
		for (int c = 0; c < kScreenColumns; c++)
		{
			if ((Picture_backBuffer[r][c].symbol != Picture_screenBuffer[r][c].symbol)
				|| (Picture_backBuffer[r][c].symbolColor != Picture_screenBuffer[r][c].symbolColor)
				|| (Picture_backBuffer[r][c].backgroundColor != Picture_screenBuffer[r][c].backgroundColor))
			{
				// Copy symbol data from back to screen buffer
				Picture_screenBuffer[r][c] = Picture_backBuffer[r][c];

				// Draw symbol in (r,c) position
				setConsoleCursor(r, c);
				setConsoleColor(Picture_screenBuffer[r][c].symbolColor, Picture_screenBuffer[r][c].backgroundColor);
				printf("%c", Picture_screenBuffer[r][c]);

				screenBufferModified = true;
			}
		}
	}

	// Return console cursor to (0,0)
	if (screenBufferModified)
		setConsoleCursor(0, 0);
}

void Render::setConsoleCursor(int r, int c)
{
	COORD cursorCoord;
	cursorCoord.X = c;
	cursorCoord.Y = r;
	SetConsoleCursorPosition(ConsoleHandle, cursorCoord);
}

void Render::setConsoleColor(ConsoleColor symbolColor, ConsoleColor backgroundColor)
{
	unsigned char consoleColor = symbolColor | (backgroundColor << 4);
	SetConsoleTextAttribute(ConsoleHandle, consoleColor);
}