//Challenge instructions: https://adventofcode.com/2022/day/3

//run with command line arguemnt: 1   to read from the smaller file, anything else will read from the bigger input file
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <string>
#include <set>
#include <algorithm>

void process_command_line(int argc, char* argv[]);
std::vector<std::string> read_rucksacks(const char*);
std::unordered_map<char, int> get_letter_map();

int main(int argc, char* argv[])
{
	std::cout << '\n';
	process_command_line(argc, argv);
	
	//PART ONE: 
	std::vector<std::string> rucksacks = read_rucksacks(argv[1]);

	std::unordered_map<char, int> letter_map = get_letter_map();	//points guide for each character
	
	//vars for breaking the string into two parts
	int half_size;
	std::string first_compartment, second_compartment;	//two halves of the main string
	int sum = 0;

	for (auto& str : rucksacks)
	{	
		//divide the current string into two halves
		half_size = str.length() / 2;
		first_compartment = str.substr(0, half_size);
		second_compartment = str.substr(first_compartment.length(), half_size);
		
		for (int i = 0; i < half_size; i++)
		{
			//std::string::npos is sort of like "end" in a map search
			if (first_compartment.find(second_compartment[i]) != std::string::npos)
			{
				sum += letter_map[second_compartment[i]];
				break;
			}
		}

	}

	std::cout << "sum: " << sum << "\n";

	//PART TWO
	sum = 0;
	for (int i = 0; i < rucksacks.size(); i += 3)
	{
		std::set<char> first, second, third;

		for (auto& current_char : rucksacks[i])
		{
			first.insert(current_char);
		}

		for (auto& current_char : rucksacks[i + 1])
		{
			second.insert(current_char);
		}

		for (auto& current_char : rucksacks[i + 2])
		{
			third.insert(current_char);
		}
		
		std::set<char> common;
		std::set_intersection(first.begin(), first.end(), second.begin(), second.end(),
							std::inserter(common, common.begin()));
		
		std::set<char> common2;
		std::set_intersection(common.begin(), common.end(), third.begin(), third.end(),
								std::inserter(common2, common2.begin()));

		sum += letter_map[*(common2.begin())];	//will be left with only one character, the priority.
	}

	std::cout << sum << "\n";
	std::cout << '\n';
	return 0;
}

std::vector<std::string> read_rucksacks(const char* which_file)
{
	//choose which file to open based on command line arg
	std::string filename = (*which_file == '1') ? "small.txt" : "big.txt";

	//open file and make sure it's valid
	std::ifstream in_file;
	in_file.open(filename);
	if (!in_file)
	{
		std::cout << "\nError with file read.\nFile: " << filename << "\n";
		exit(1);
	}

	std::vector<std::string> rucksacks;
	std::string line;
	while (!in_file.eof())
	{
		if (getline(in_file, line))
		{
			rucksacks.push_back(line);
		}
	}

	in_file.close();
	return rucksacks;

}

//makes it much easier to calcualte the priority value for any individual character
std::unordered_map<char, int> get_letter_map()
{
	std::unordered_map<char, int> letter_map;

	int counter = 1;
	for (char letter = 'a'; letter <= 'z'; letter++)
	{
		letter_map.insert( {letter, counter} );
		counter++;
	}
	
	for (char letter = 'A'; letter <= 'Z'; letter++)
	{
		letter_map.insert( {letter, counter} );
		counter++;
	}

	return letter_map;
}

void process_command_line(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Error: Must include command line argument to indicate which file to run.\n";
		std::cout << "An argument of '1' will read the smaller file, anything else will read the bigger file\n\n";
		exit(1);
	}
}