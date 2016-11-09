// This code solves game fifteens (version 3*3) using bfs
//
#include <fstream>
#include <array>
#include <algorithm>
#include "Position.h"




int main()
{
	std::fstream file;
	file.open("puzzle.in", std::fstream::in);
	std::array<int, FieldSize*FieldSize> startPosition;
	for (int i = 0; i < FieldSize*FieldSize; ++i)
	{
		file >> startPosition[i];
	}
	Position P(startPosition);
	
	file.close();

	
	file.open("puzzle.out", std::fstream::out);
	if (P.is_solvable())
	{
		std::string result(P.bfs());
		file << result.size() << std::endl;
		file << result << std::endl;
	}
	else
		file << "-1";
	file.close();
}