#pragma once
#include <Windows.h>
#include "consoleColor.h"




// +
const int kScreenRows = 25;
const int kScreenColumns = 80;


struct ConsoleSymbolData
{
	char symbol;
	ConsoleColor symbolColor;
	ConsoleColor backgroundColor;
};


class Render
{
public:
	Render();

	void init();
	void clear();
	void drawChar(int r, int c, char symbol, ConsoleColor symbolColor, ConsoleColor backgroundColor);
	void drawText(int r, int c, const char* text, ConsoleColor symbolColor, ConsoleColor backgroundColor);
	void flush();

private:
	void setConsoleCursor(int r, int c);
	void setConsoleColor(ConsoleColor symbolColor, ConsoleColor backgroundColor);

private:
	HANDLE ConsoleHandle;
	ConsoleSymbolData Picture_backBuffer[kScreenRows][kScreenColumns];
	ConsoleSymbolData Picture_screenBuffer[kScreenRows][kScreenColumns];
};
