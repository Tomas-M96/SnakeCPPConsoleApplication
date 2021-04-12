#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <ostream>

class FileReader
{
public:
	template <typename T>
	static void updateFile(std::string fileName, T object)
	{
		std::fstream fileIn{ fileName, std::ios::in | std::ios::out | std::ios::app};

		if (fileIn)
		{
			fileIn << object << std::endl;
		}
		else
		{
			std::cerr << "FILEREADER ERROR: File cannot be read" << std::endl;
		}
		fileIn.close();
	}

	static std::vector<std::string> readFile(std::string fileName)
	{
		//Load Scores
		std::ifstream fileOut{ fileName, std::ios::out };
		std::vector<std::string> lines;

		//Display Scores
		if (fileOut)
		{
			std::string line;
			while (!fileOut.eof())
			{
				std::getline(fileOut, line);
				lines.push_back(line);
			}
			fileOut.close();
			return lines;
		}
		else
		{
			std::cerr << "FILEREADER ERROR: File cannot be read" << std::endl;
		}
	}
};

#endif // !FILEREADER_H