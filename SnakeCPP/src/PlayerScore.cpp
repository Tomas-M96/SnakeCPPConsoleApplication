#include "../header/PlayerScore.h"

//Overloaded Insertion Operator
std::ostream& operator<<(std::ostream& os, const PlayerScore& obj)
{
	os << "Score: <" << obj.score << "> " << "Name: <" << obj.name << ">" << std::endl;
	return os;
}

//name Constructor
PlayerScore::PlayerScore(std::string name) : name{ name } {}

//name and score constructor
PlayerScore::PlayerScore(std::string name, int score) : name{ name }, score{ score } {}

//GetScore
int PlayerScore::getScore() { return score; }

//GetName
std::string PlayerScore::getName() { return name; }

//UpdateScore
void PlayerScore::updateScore(int newScore)
{
	score = newScore;
}

