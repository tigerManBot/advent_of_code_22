#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class Elf_Pair
{
private:
	//uppers are inclusive!
	int first_lower;
	int first_upper;
	int second_lower;
	int second_upper;
	
public:
	Elf_Pair(int f_lower, int f_upper, int s_lower, int s_upper)
	{	
		first_lower = f_lower;
		first_upper = f_upper;
		second_lower = s_lower;
		second_upper = s_upper;
	}

	bool is_fully_contained()
	{
		bool first_contains_second = first_lower <= second_lower && first_upper >= second_upper;
		bool second_contains_first = second_lower <= first_lower && second_upper >= first_upper;
		return first_contains_second || second_contains_first;
	}

	bool is_overlapped()
	{
		return (first_lower >= second_lower && first_lower <= second_upper) ||
				(second_lower >= first_lower && second_lower <= first_upper);
	}
};

std::vector<Elf_Pair> read_pairs(const char*);
const char* process_command_line(int, const char*);

int main(int argc, char* argv[])
{
	std::cout << '\n';

	std::vector<Elf_Pair> elf_pairs = read_pairs( process_command_line(argc, argv[1]) );

	//Both
	int fully_contained_counter = 0;
	int overlap_counter = 0;
	for (auto& pair : elf_pairs)
	{
		if (pair.is_fully_contained())
		{
			fully_contained_counter++;
		}

		if (pair.is_overlapped())
		{
			overlap_counter++;
		}
	}
	std::cout << "Part one: " << fully_contained_counter << "\n";
	std::cout << "Part two: " << overlap_counter << "\n";

	
	std::cout << '\n';
	return 0;
}

std::vector<Elf_Pair> read_pairs(const char* filename)
{
	std::ifstream in_file;
	in_file.open(filename);
	if (!in_file)
	{
		std::cout << "\nError with file read.\nFile: " << filename << "\n";
		exit(1);
	}

	std::vector<Elf_Pair> elf_pairs;

	std::string line;
	int lower_number, upper_number , second_lower, second_upper;
	while (!in_file.eof())
	{
		getline(in_file, line, '-');
		lower_number = stoi(line);
		getline(in_file, line, ',');
		upper_number = stoi(line);

		getline(in_file, line, '-');
		second_lower = stoi(line);
		getline(in_file, line);
		second_upper = stoi(line);

		elf_pairs.push_back( Elf_Pair(lower_number, upper_number, second_lower, second_upper) );
	}	

	in_file.close();
	return elf_pairs;
}


const char* process_command_line(int argc, const char* argument)
{
	if (argc < 2)
	{
		std::cout << "Error: Must include command line argument to indicate which file to run.\n";
		std::cout << "An argument of '1' will read the smaller file, anything else will read the bigger file\n\n";
		exit(1);
	}

	return (*argument == '1') ? "small.txt" : "big.txt"; 
}