#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <Windows.h>
#include <list>
#include <thread>
#include "Vector2.h"

class GameEngine
{
private:
	static const int screenWidth{ 120 };
	static const int screenHeight{ 30 };
public:
	static wchar_t* fillScreen();
	static HANDLE createScreenBuffer();
	static void processInput(int& snakeDirection, bool& keyRight, bool& keyLeft, bool& prevKeyRight, bool& prevKeyLeft);
	static void gameLogic(int snakeDirection, std::list<Vector2>& snake, bool& isSnakeDead, Vector2& foodPos, Vector2& enemyPos, int& score);
	static void drawToScreen(wchar_t* screen, int score, std::list<Vector2>& snake, bool isSnakeDead, Vector2& foodPos, Vector2& enemyPos, const HANDLE& hConsole, DWORD& dwBytesWritten);
};

#endif // !GAMEENGINE_H
