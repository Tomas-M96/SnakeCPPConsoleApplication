#ifndef PLAYERSCORE_H
#define PLAYERSCORE_H

#include <iostream>
#include <string>

class PlayerScore
{
	friend std::ostream& operator<<(std::ostream& os, const PlayerScore& obj);

private:
	std::string name;
	int score;
public:
	PlayerScore(std::string name);
	PlayerScore(std::string name, int score);
	int getScore();
	std::string getName();
	void updateScore(int newScore);

	//Destructor
	~PlayerScore()
	{
		//std::cout << "PlayerScore object destroyed." << std::endl;
	}
};

#endif