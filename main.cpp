#include <iostream>		//Always needed
#include <fstream>		//File I/O
#include <iomanip>		//Convenient spacing
#include <string>		//Manipulate strings
#include <cstring>		//Manipulate c-strings
#include "passgen.h" //Generation functions

void PrintHelp(std::ostream &outstream);

int main(int argc, char* argv[])
{
	//Declare and initialize variables
	int length = 8; //Length of password to be generated
	int amountGen = 1; //Amount of passwords to generate
	bool smallAlpha = false; //Inclusion of lowercase letters
	bool largeAlpha = false; //Inclusion of uppercase letters
	bool symbols = false; //Whether or not to include symbols
	bool needHelp = false; //Whether or not to show the help file
	bool showMeta = true; //Whether or not to include metainfo
	char flagChar = '0'; //Replaced inside flag-checking loop			
	
	//Check if program is running in stdout mode
	if (argc <= 1) needHelp = true;

	for (int i = 0; i < argc; i++) 
	{
		if ((argv[i][0] == '-') && (argv[i][1] != '-'))
		{
			std::string temp = argv[i];
			for (int j = 1; j < temp.length(); j++)
			{
				flagChar = argv[i][j];
				if (flagChar == 'h')
				{
					needHelp = true;
					break;
				}
				else if (flagChar == 'm') showMeta = false;
				else if (flagChar == 'a') smallAlpha = true;
				else if (flagChar == 'A') largeAlpha = true;
				else if (flagChar == 's') symbols = true;
			}
		}
		if (needHelp || (strcmp(argv[i], "--help") == 0))
		{
			needHelp = true;
			break;
		}
		else if (strcmp(argv[i], "--nometa") == 0) showMeta = false;
		else if (strcmp(argv[i], "--smallalpha") == 0) smallAlpha = true;
		else if (strcmp(argv[i], "--largealpha") == 0) largeAlpha = true;
		else if (strcmp(argv[i], "--symbol") == 0) symbols = true;
		if ((strcmp(argv[i], "-n") == 0) || (strcmp(argv[i], "--amount") == 0))
		{
			//Make sure not at end of arguments
			if (!(i + 1 >= argc))
			{
				amountGen = atoi(argv[i + 1]);
				if (amountGen < 1) amountGen = 1;
				if (amountGen > 1000) amountGen = 1000;
			}
			else amountGen = 1;
		}
		if ((strcmp(argv[i], "-l") == 0) || (strcmp(argv[i], "--length") == 0))
		{
			//Make sure not at end of arguments
			if (!(i + 1 >= argc))
			{
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
		//Create a Passgen object using user-defined variables
		Passgen pg(length, amountGen, smallAlpha, largeAlpha, symbols);
		//Output based on amount requested
		pg.printPass(showMeta);
	}
	return 0;
}

//Displays help and exits program
void PrintHelp(std::ostream &outstream)
{
	outstream << "Password Generator\n\n" << '\t' << "It generates passwords!\n\n"
		<< "Available Commands\n\n"
		<< '\t' << "-h | --help = Opens this help file.\n\n"
		<< '\t' << "-m | --nometa = Skip metainformation about generation.\n\n"
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
