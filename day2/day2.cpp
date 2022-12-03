//Instructions: https://adventofcode.com/2022/day/2
#include <iostream>
#include <unordered_map>
#include <array>
#include <vector>
#include <fstream>

std::vector<std::array<char, 2>>  readAndStore(const char*);
void print_moves(const std::vector<std::array<char, 2>>&);

int main(int argc, char* argv[])
{
	std::cout << '\n';

	//Part One
	std::vector<std::array<char, 2>> moves = readAndStore(argv[1]);

	int points = 0;
	std::unordered_map<char, int> points_map;
	points_map['X'] = 1;
	points_map['Y'] = 2;
	points_map['Z'] = 3;

	//move.back() is your move, move.front() is the oppoenents move
	for (auto& move : moves)
	{
		//points for your move
		points += points_map[move.back()];

		//result-based points
		if (move.back() == move.front())
		{
			points += 3;
		}
		else if ((points_map[move.back()] - 1) % 3 == points_map[move.front()] % 3)
		{
			points += 6;
		}

	}
	std::cout << points << "\n";

	//Part Two
	std::unordered_map<char, std::array<char, 2>> result_map;
	//Value: index 0 is a win for that key, index 1 is a loss for that key
	result_map['X'] = { 'Z', 'Y' };
	result_map['Y'] = { 'X', 'Z' };
	result_map['Z'] = { 'Y', 'X' };

	points = 0;
	for (auto& move : moves)
	{
		switch (move.back())
		{
		case 'X':
			//you have to lose
			points += points_map[result_map[move.front()][0]];	// index 0 is a win for your opponent
			break;
		case 'Y':
			//you have to draw
			points += points_map[move.front()];
			points += 3;	//results-based points	
			break;
		case 'Z':
			//you have to win
			points += points_map[result_map[move.front()][1]];	// index 1 is a loss for your opponent
			points += 6;	//results-based points
			break;
		default:
			std::cout << "\nFml\n";
			exit(1);
		}
	}
	std::cout << points << "\n";

	std::cout << '\n';
	return 0;
}

std::vector<std::array<char, 2>> readAndStore(const char* which_file)
{
	//choose which file to open based on command line arg
	std::string filename = (*which_file == '1') ? "day2_small.txt" : "day2_big.txt";

	//open file and make sure it's valid
	std::ifstream in_file;
	in_file.open(filename);
	if (!in_file)
	{
		std::cout << "Error with file read.\nFile: " << filename << "\n";
		exit(1);
	}

	std::unordered_map<char, char> conversion_guide;
	conversion_guide['A'] = 'X';
	conversion_guide['B'] = 'Y';
	conversion_guide['C'] = 'Z';

	std::vector<std::array<char, 2>> moves;
	char opp_move, your_move;
	while (!in_file.eof())
	{
		if (in_file >> opp_move >> your_move)
		{
			opp_move = conversion_guide[opp_move];	//converts opponenets moves to be similar to yours. (EX: A -> X)
			moves.push_back({ opp_move, your_move });
		}
	}

	return moves;
}

void print_moves(const std::vector<std::array<char, 2>>& moves)
{
	for (auto& move : moves)
	{
		std::cout << "opp: " << move.front() << "\tyou: " << move.back() << "\n";
	}
}