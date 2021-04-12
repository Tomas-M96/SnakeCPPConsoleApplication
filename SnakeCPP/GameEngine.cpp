#include "GameEngine.h"

wchar_t* GameEngine::fillScreen()
{
	wchar_t* screen = new wchar_t[screenWidth * screenHeight];
	for (int i = 0; i < screenWidth * screenHeight; i++)
	{
		screen[i] = L' ';
	}
	return screen;
}

HANDLE GameEngine::createScreenBuffer()
{
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	return hConsole;
	//DWORD dwBytesWritten = 0;
}

void GameEngine::processInput(int& snakeDirection, bool& keyRight, bool& keyLeft, bool& prevKeyRight, bool& prevKeyLeft)
{
	auto t1 = std::chrono::system_clock::now();
	while ((std::chrono::system_clock::now() - t1) < ((snakeDirection % 2 == 1) ? std::chrono::milliseconds(120) : std::chrono::milliseconds(200)))
	{

		keyRight = GetAsyncKeyState(VK_RIGHT) != 0;
		keyLeft = GetAsyncKeyState(VK_LEFT) != 0;

		if (keyRight && !prevKeyRight)
		{
			snakeDirection++;
			if (snakeDirection == 4)
				snakeDirection = 0;
		}

		if (keyLeft && !prevKeyLeft)
		{
			snakeDirection--;
			if (snakeDirection == -1)
				snakeDirection = 3;
		}

		prevKeyRight = keyRight;
		prevKeyLeft = keyLeft;
	}
}

void GameEngine::gameLogic(int snakeDirection, std::list<Vector2>& snake, bool& isSnakeDead, Vector2& foodPos, Vector2& enemyPos, int& score)
{
	//Generate random seed
	srand(time(NULL));

	//Update Snake Position
	switch (snakeDirection)
	{
	case 0: //UP
		snake.push_front({ snake.front().x, snake.front().y - 1 });
		break;
	case 1: //RIGHT
		snake.push_front({ snake.front().x + 1, snake.front().y });
		break;
	case 2: //DOWN
		snake.push_front({ snake.front().x, snake.front().y + 1 });
		break;
	case 3: //LEFT
		snake.push_front({ snake.front().x - 1, snake.front().y });
		break;
	default:
		break;
	}

	//Collision Detection
	//Detect Snake V World
	if (snake.front().x < 0 || snake.front().x >= screenWidth)
		isSnakeDead = true;
	if (snake.front().y < 3 || snake.front().y >= screenHeight)
		isSnakeDead = true;


	//Detect Snake V Food
	if (snake.front().x == foodPos.x && snake.front().y == foodPos.y)
	{
		score++;

		//while (screen[foodPos.y * screenWidth + foodPos.x] != L' ');
		//{
		foodPos.x = rand() % screenWidth;
		foodPos.y = (rand() % (screenHeight - 3)) + 3;
		enemyPos.x = rand() % screenWidth;
		enemyPos.y = (rand() % (screenHeight - 3)) + 3;
		//}

		for (int i = 0; i < 5; i++)
			snake.push_back({ snake.back().x, snake.back().y });
	}

	//Detect Snake V Enemy
	if (snake.front().x == enemyPos.x && snake.front().y == enemyPos.y)
	{
		isSnakeDead = true;
	}

	//Detect Snake V Snake
	for (std::list<Vector2>::iterator i = snake.begin(); i != snake.end(); i++)
		if (i != snake.begin() && i->x == snake.front().x && i->y == snake.front().y)
			isSnakeDead = true;

	snake.pop_back();
}

void GameEngine::drawToScreen(wchar_t* screen, int score, std::list<Vector2>& snake, bool isSnakeDead, Vector2& foodPos, Vector2& enemyPos, const HANDLE& hConsole, DWORD& dwBytesWritten)
{
	//Clear Screen
	for (int i = 0; i < screenWidth * screenHeight; i++)
		screen[i] = L' ';

	//Draw Stats & Border
	for (int i = 0; i < screenWidth; i++)
	{
		screen[i] = L'=';
		screen[2 * screenWidth + i] = L'=';
	}
	wsprintf(&screen[screenWidth + 5], L"SNAKE                 SCORE: %d", score);

	//Draw Snake Body
	for (auto s : snake)
		screen[s.y * screenWidth + s.x] = isSnakeDead ? L'x' : L'O';

	//Draw Snake Head
	screen[snake.front().y * screenWidth + snake.front().x] = isSnakeDead ? L'X' : L'@';

	//Draw Food
	screen[foodPos.y * screenWidth + foodPos.x] = L'£';

	//Draw Enemy
	screen[enemyPos.y * screenWidth + enemyPos.x] = L'X';

	if (isSnakeDead)
		wsprintf(&screen[15 * screenWidth + 40], L"PRESS SPACE TO PLAY AGAIN OR ESCAPE TO QUIT");

	//Display Frame
	WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, { 0, 0 }, &dwBytesWritten);
}
