//Std includes
#include <iostream>
#include <list>
#include <thread>
#include <iomanip>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>

//Headers
#include <Windows.h>
#include "../header/main.h"


const int screenWidth { 120 };
const int screenHeight{ 30 };

float playerX = 8.0f;
float playerY = 3.0f;
float playerAngle = 0.0f;

int mapHeight = 16;
int mapWidth = 16;

float fov = 3.14159 / 4.0;
float depth = 16.0f;

int main()
{
	
	std::cout << std::setfill('=') << std::setw(60) << "SNAKE" << std::setfill('=') << std::setw(60) << std::endl;
	//std::cout << std::setfill('=') << "Main Menu" << std::setw(120) << std::endl;
	
	int input{};

	std::cout << "1.Play Game" << std::endl;
	std::cout << "2.High Scores" << std::endl;
	std::cout << "3.Quit" << std::endl;
	std::cin >> input;
	
	switch (input)
	{
	case 1:
		inputName();
		break;
	case 2:
		viewScores();
		break;
	case 3:
		break;
	}

	std::cout << "Thank you for playing" << std::endl;
	return 0;
}


void loadGame(PlayerScore* playerScore)
{
	//Create Screen variable and fill the screen
	wchar_t* screen = GameEngine::fillScreen();
	//Create screen buffer
	HANDLE hConsole = GameEngine::createScreenBuffer();
	DWORD dwBytesWritten = 0;

	while (1)
	{
		std::list<Vector2> snake{ { 60, 15 },{ 61, 15 },{ 62, 15 },{ 63, 15 },{ 64, 15 },{ 65, 15 },{ 66, 15 },{ 67, 15 },{ 68, 15 },{ 69, 15 } };
		//Randomise these two values
		Vector2 foodPos{ 30, 15 };
		Vector2 enemyPos{ 35, 15 };
		int score = 0;
		int snakeDirection = 3;
		bool isSnakeDead = false;
		bool keyLeft = false, keyRight = false, prevKeyLeft = false, prevKeyRight = false;

		while (!isSnakeDead)
		{
			//Timing & Input
			//Get Input
			GameEngine::processInput(snakeDirection, keyRight, keyLeft, prevKeyRight, prevKeyLeft);
			//Game Logic
			GameEngine::gameLogic(snakeDirection, snake, isSnakeDead, foodPos, enemyPos, score);
			//Display to Player
			GameEngine::drawToScreen(screen, score, snake, isSnakeDead, foodPos, enemyPos, hConsole, dwBytesWritten);
		}

		//Update Score
		playerScore->updateScore(score);

		//Wait for space input
		while (!GetAsyncKeyState(VK_SPACE))
		{
			//Capture ESC key
			if (GetAsyncKeyState(VK_ESCAPE))
			{
				FileReader::updateFile<PlayerScore>("scores.txt", *playerScore);
				delete playerScore;
				playerScore = NULL;
				delete screen;
				screen = NULL;
				return;
			}
		}
	}
}

void inputName()
{
	std::string name;
	std::cout << "What is your name: ";
	std::cin >> name;
	PlayerScore* playerScore = new PlayerScore(name);
	loadGame(playerScore);
}

void viewScores()
{
	std::vector<std::string> output = FileReader::readFile("scores.txt");
	std::vector<PlayerScore> scores {};

	for (auto item : output)
	{
		std::pair<std::string, int> record = regexScores(item);
		if (record.first != "")
			scores.push_back({ record.first, record.second });
	}

	//Need to sort by score

	for (auto item : scores)
	{
		std::cout << item << std::endl;
	}
}

std::pair<std::string, int> regexScores(std::string scoreText)
{
	std::smatch m;
	//Regex to find all numbers between <>
	std::regex scoreSearch{ "([<>]*[0-9]+[<>])" };
	//Regex to find all characters between <>
	std::regex nameSearch{ "([<>]*[A-Za-z]+[<>])" };
	std::string name{};
	std::string score{};
	
	std::regex_search(scoreText, m, nameSearch);
	for (auto x : m)
		name = x;

	std::regex_search(scoreText, m, scoreSearch);
	for (auto x : m)
		score = x;

	if (score != "" && name != "")
	{
		std::string newName{ name.substr(1, name.size() - 2) };
		int newScore { std::stoi(score.substr(1, score.size() - 2)) };
		return std::make_pair(std::string(newName), newScore);
	}
}


