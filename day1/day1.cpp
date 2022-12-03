//Instructions: https://adventofcode.com/2022/day/1
#include <iostream>
#include <queue>
#include <fstream>
#include <string>

std::priority_queue<int> get_elf_data(const char*);
int sum_of_top_three_elves(std::priority_queue<int>&);

int main(int argc, char* argv[])
{
	std::cout << '\n';

	std::priority_queue<int> elves = get_elf_data(argv[1]);

	std::cout << "Elf with most calories: " << elves.top() << "\n";	//End of part one

	std::cout << "Sum of top three elves: " << sum_of_top_three_elves(elves) << "\n";	//part two

	std::cout << '\n';
	return 0;
}

std::priority_queue<int> get_elf_data(const char* which_file)
{
	//choose which file to open based on command line arg
	std::string filename = (*which_file == '1') ? "day1_small" : "day1_big.txt";

	//open file and make sure it's valid
	std::ifstream in_file;
	in_file.open(filename);
	if (!in_file)
	{
		std::cout << "Error with file read.\nFile: " << filename << "\n";
		exit(1);
	}

	//parse file and store into elves
	std::string temp_reader;
	int current_elf_calories = 0;	//current elf's calories as a running sum
	std::priority_queue<int> elves;

	while (!in_file.eof())
	{
		getline(in_file, temp_reader, '\n');
		if (temp_reader.empty())
		{
			//done reading the current elf's calories.
			elves.push(current_elf_calories);
			current_elf_calories = 0;	//on to the next elf so clear the listt
		}
		else
		{
			current_elf_calories += stoi(temp_reader);
		}
	}

	in_file.close();

	return elves;
}

int sum_of_top_three_elves(std::priority_queue<int>& elves)
{
	int running_sum = 0;

	//requires the top three elves
	for (int i = 0; i < 3; i++)
	{
		running_sum += elves.top();
		elves.pop();
	}
	return running_sum;
}
