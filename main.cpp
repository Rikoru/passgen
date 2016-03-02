#include <iostream>		//Always needed
#include <random>		//PRNG stuff
#include <algorithm>	//Transform function
#include <fstream>		//File I/O
#include <iomanip>		//Convenient spacing
#include <string>		//Manipulate strings
#include <cstring>		//Manipulate c-strings

void PrintHelp(std::ostream &outstream);
void GeneratePass(int passLength, bool wantLower, bool wantUpper, bool wantSymbols, std::ostream &outstream);

int main(int argc, char* argv[])
{
	//Declare and initialize variables
	int length = 8; //Length of password to be generated
	int amountGen = 1; //Amount of passwords to generate
	bool smallAlpha = false; //Inclusion of lowercase letters
	bool largeAlpha = false; //Inclusion of uppercase letters
	bool symbols = false; //Whether or not to include symbols
	bool needHelp = false; //Whether or not to show the help file				
	
	//Check if program is running in stdout mode
	if (argc <= 1) needHelp = true;

	for (int i = 0; i < argc; i++) 
	{
		if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0))
		{
			needHelp = true;
		}
		if ((strcmp(argv[i], "-a") == 0) || (strcmp(argv[i], "--smallalpha") == 0))
		{
			smallAlpha = true; //Enable small letters
		}
		if ((strcmp(argv[i], "-A") == 0) || (strcmp(argv[i], "--largealpha") == 0))
		{
			largeAlpha = true; //Enable capital letters
		}
		if ((strcmp(argv[i], "-s") == 0) || (strcmp(argv[i], "--symbol") == 0))
		{
			symbols = true; //Enable symbols
		}
		if ((strcmp(argv[i], "-n") == 0) || (strcmp(argv[i], "--amount") == 0))
		{
			//Make sure not at end of arguments
			if (!(i + 1 >= argc))
			{
				amountGen = atoi(argv[i + 1]);
				if (amountGen < 1) amountGen = 1;
				if (amountGen > 1000) amountGen = 1000;
			}
		}
		if ((strcmp(argv[i], "-l") == 0) || (strcmp(argv[i], "--length") == 0))
		{
			//Make sure not at end of arguments
			if (!(i + 1 >= argc))
			{
				//Set the length of passwords to generate
				length = atoi(argv[i + 1]);
				if (length < 6) length = 6;
				if (length > 256) length = 256;
			}
		}
	}
		
	if (needHelp) {
		PrintHelp(std::cout);
	}
	else {
		for (int i = 1; i <= amountGen; i++)
		{
			if (i == 1 && amountGen != 1)
			{
				std::cout << "PasswordGenerator | length: " << length << " | amount: " << amountGen << "\n";
			}
			GeneratePass(length, smallAlpha, largeAlpha, symbols, std::cout);
		}
	}
	return 0;
}

//Displays help and exits program
void PrintHelp(std::ostream &outstream)
{
	outstream << "Password Generator\n\n" << '\t' << "It generates passwords!\n\n"
		<< "Available Commands\n\n"
		<< '\t' << "-h | --help = Opens this help file.\n\n"
		<< '\t' << "-a | --smallalpha = Enables lowercase letters.\n\n"
		<< '\t' << "-A | --largealpha = Enables uppercase letters.\n\n"
		<< '\t' << "-s | --symbol = Enables symbols to be generated.\n\n"
		<< '\t' << "-n | --amount = Specify how many passwords to generate.\n"
		<< '\t' << "e.g. \'passgen -n 6\' will generate 6 passwords.\n"
		<< '\t' << "Max amount to generate: 100 normally, 1000 for stdout.\n\n"
		<< '\t' << "-l | --length = Specify length of passwords to generate.\n"
		<< '\t' << "e.g. \'passgen -l 32\' will generate a 32 digit password.\n"
		<< '\t' << "Max length to generate: 256 characters.\n\n"
		<< "More commands are likely to be added with time, stay tuned.\n";
}

//Function to generate password
void GeneratePass(int passLength, bool wantLower, bool wantUpper, bool wantSymbols, std::ostream &outstream)
{
	//Initializes random number generator
	std::random_device rd;
	std::mt19937 mt(rd());

	//Provides boundaries for where to distribute numbers
	std::uniform_int_distribution<int> numDist(0, 9);		//Random distribution for numbers
	std::uniform_int_distribution<int> letDist(0, 25);		//Random distribution for letters
	std::uniform_int_distribution<int> symDist(0, 13);		//Random distribution for symbols
		
	//Determines which options can be used for the output
	std::vector<int> choices = {1};			//Always include numbers
	if (wantLower) choices.push_back(2);	//Include lowercase
	if (wantUpper) choices.push_back(3);	//Include uppercase
	if (wantSymbols) choices.push_back(4);	//Include symbols
	std::uniform_int_distribution<int> typeDist(0, choices.size() - 1);

	//Storage of characters available
	char lowerCase[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	char upperCase[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	char symbo[14] = { '!', '#', '@', '~', '$', '^', '.', ',', '-', '+', '%', '?', '*', '=' };
	
	//Prints to output file
	for (int p = 0; p < passLength; p++)
	{
		switch (choices[typeDist(mt)])
		{
		case 1:			//Numbers
			outstream << numDist(mt);
			break;
		case 2:			//Lowercase
			outstream << lowerCase[letDist(mt)];
			break;
		case 3:			//Uppercase
			outstream << upperCase[letDist(mt)];
			break;
		case 4:			//Symbols
			outstream << symbo[symDist(mt)];
			break;
		}
	}
	outstream << "\n";
}