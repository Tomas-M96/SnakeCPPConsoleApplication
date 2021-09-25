#ifndef MAIN_H
#define MAIN_H

#include "PlayerScore.h"
#include "Vector2.h"
#include "FileReader.h"
#include "GameEngine.h"

void inputName();
void loadGame(PlayerScore* playerScore);
void viewScores();
std::pair<std::string, int> regexScores(std::string scoreText);

#endif 
