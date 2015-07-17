#include <iostream>		//Always needed
#include <random>		//PRNG stuff
#include <algorithm>	//Transform function
#include <fstream>		//File I/O
#include <iomanip>		//Convenient spacing
#include <string>		//Manipulate strings
#include <cstring>		//Manipulate c-strings

void PrintHelp(bool stdOut, std::ostream &outstream);
void MakeLine(int lineLength);
void PrintAttempt(int attemptAmount);
void EndProgram(std::string givenReason);
bool Prompt(std::string type, bool &choice);
void GeneratePass(int passLength, int runAmount, bool wantLower, bool wantUpper, bool wantSymbols, std::ostream &outstream);

int main(int argc, char* argv[])
{
	//Declare and initialize variables
	int length = 8;						//Length of password to be generated
	int attempts = 0;					//Amount of attempts for length input
	int amountGen = 1;					//Amount of passwords to generate
	bool failure = false;				//Failure to input the length
	bool smallAlpha = false;			//Inclusion of lowercase letters
	bool largeAlpha = false;			//Inclusion of uppercase letters
	bool symbols = false;				//Whether or not to include symbols
	bool correctAmount = false;			//Whether or not valid amount was given
	bool printStdOut = false;			//Whether or not to print to stdout
	bool needHelp = false;				//Whether or not help is needed
	bool gui = false;					//Whether the 'wizard' is displayed
	std::ofstream outFile;				//The stream for the output file
	char outName[80] = { '\0' };		//The name of the output file
	
	//Check if program is running in stdout mode
	if (argc <= 1) gui = true;
	for (int i = 0; i < argc; i++)
	{
		if ((strcmp(argv[i], "-c") == 0) || (strcmp(argv[i], "--stdout") == 0))
		{
			printStdOut = true;
		}
		if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0))
		{
			if (printStdOut || argc == 2)
			{
				PrintHelp(printStdOut, std::cout); //Display help and exit
				return 0;
			}
			else needHelp = true;
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
		if ((strcmp(argv[i], "-o") == 0) || (strcmp(argv[i], "--output") == 0))
		{
			//Make sure not at end of arguments
			if (!(i + 1 >= argc))
			{
				//copy 79 characters to the output name
				//overridden by stdout being present
				strncpy_s(outName, 80, argv[i + 1], _TRUNCATE);
			}
		}
	}
	// simplify things, use more functions
	// make life easier
	if (printStdOut == false)
	{
		if (gui)
		{
			//Give the header for the program
			MakeLine(35);
			std::cout << std::endl << "==== RANDOM PASSWORD GENERATOR ====" << std::endl;
			MakeLine(35);

			//Request password length
			std::cout << std::endl << "Input integer (8 to 256) for length" << std::endl;

			while (attempts <= 6)
			{
				std::cin.clear();
				std::cin.sync();
				MakeLine(35);
				std::cout << std::endl;

				//Line for amount of attempts
				PrintAttempt(attempts);
				std::cout << "> ";

				if (!(std::cin >> length))
				{
					if (attempts < 6)
					{
						std::cerr << "ERROR: Not an integer!" << std::endl << std::endl;
						attempts++;
						continue;
					}
					else
					{
						failure = true;
						break;
					}

				}
				else if (length < 8 || length > 256)
				{
					if (attempts < 6)
					{
						std::cerr << "ERROR: Not within specified range!" << std::endl << std::endl;
						attempts++;
						continue;
					}
					else
					{
						failure = true;
						break;
					}
				}
				else break;
			}

			//Check if too many attempts have been performed
			if (failure == true)
			{
				EndProgram("Too many attempts!");
				return -1;
			}

			//Check for wanting letters and symbols
			smallAlpha = Prompt("lowercase letters", smallAlpha);
			largeAlpha = Prompt("uppercase letters", largeAlpha);
			symbols = Prompt("symbols", symbols);

			//Request amount of passwords to generate
			do
			{
				//Reset for loop
				correctAmount = false;
				std::cin.clear();
				std::cin.sync();

				//Prints the prompt
				std::cout << std::endl;
				MakeLine(35);
				std::cout << std::endl << "How many passwords to generate " << std::endl
					<< "Input an integer (1 to 100)" << std::endl;
				MakeLine(35);
				std::cout << std::endl;
				PrintAttempt(attempts);
				std::cout << "> ";
				try
				{
					std::cin >> amountGen;

					//Check range
					if (amountGen < 1 || amountGen > 100)
					{
						if (attempts < 6)
						{
							std::cerr << "ERROR: Not within specified range!" << std::endl;
							attempts++;
							continue;
						}
						else
						{
							failure = true;
							break;
						}
					}
					else correctAmount = true;
				}
				catch (...)
				{
					std::cerr << "ERROR: Could not understand input!" << std::endl;
					attempts++;
					if (attempts >= 6)
					{
						failure = true;
						break;
					}
				}
			} while (correctAmount == false);

			//Check if too many attempts have been performed
			if (failure == true)
			{
				EndProgram("Too many attempts!");
				return -1;
			}
			
			//Request output file name
			MakeLine(35);
			std::cout << std::endl << "Input a file name to use for output" << std::endl << "> ";
		} //if gui
		try
		{
			if (gui)
			{
				std::cin.clear();
				std::cin.sync();
				std::cin >> outName;
			}

			//Try to create the file specified
			outFile.open(outName, std::ios::app);
			if (outFile.fail())
			{
				outFile.close();
				std::cerr << "ERROR: Failed to create file " << outName << std::endl;
				MakeLine(35);
				EndProgram("Couldn't create file!");
				return -1;
			}
		}
		catch (...)
		{
			outFile.close();
			std::cerr << "ERROR: Critical failure, shutting down" << std::endl;
			EndProgram("Critical failure!");
			return -1;
		}
		
		//Send to function
		for (int pass = 1; pass <= amountGen; pass++)
		{
			if (pass == 1)
			{
				std::cout << std::endl;
				outFile << "PasswordGenerator | length: " << length << " | amount: " << amountGen << "\n";
			}
			GeneratePass(length, pass, smallAlpha, largeAlpha, symbols, outFile);
			std::cout << "Generated: " << std::setw(4) << pass << " / " << std::setw(4) << amountGen << std::endl;
		}
		outFile << std::endl;
		outFile.close();
		if (gui) EndProgram("Success, enjoy your file.\n");
	}
	else if (needHelp)
	{
		PrintHelp(printStdOut, std::cout);
	}
	else
	{
		for (int i = 0; i < amountGen; i++)
		{
			if (i == 0 && amountGen != 1)
			{
				std::cout << "PasswordGenerator | length: " << length << " | amount: " << amountGen << "\n";
			}
			GeneratePass(length, i+1, smallAlpha, largeAlpha, symbols, std::cout);
		}
	}
	return 0;
}

//Displays help and exits program
void PrintHelp(bool stdOut, std::ostream &outstream)
{
	outstream << "Password Generator\n\n" << '\t' << "It generates passwords!\n\n"
		<< "Available Commands\n\n"
		<< '\t' << "-c | --stdout = Prints only to standard output.\n"
		<< '\t' << "Adding this will negate the use of an output file.\n\n"
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
		<< '\t' << "-o | --output = Specify the filename to output to.\n"
		<< '\t' << "e.g. \'passgen -o test.txt\' will generate 1 8-digit password.\n" 
		<< '\t' << "Overridden by using \'-c | --stdout\', pointless to combine them.
		\n\n"
		<< "More commands are likely to be added with time, stay tuned.\n";
	if (stdOut) EndProgram("no"); //Keeps the command window open until enter is pressed
}

//Produces lines across screen
void MakeLine(int lineLength)
{
	for (int i = 0; i < lineLength; i++)
	{
		std::cout << '=';
	}
	std::cout << ' ';
}

//Displays how many attempts remain (of arbitrary 6)
void PrintAttempt(int attemptAmount)
{
	MakeLine(19);
	std::cout << "Attempts: " << attemptAmount << " / 6" << std::endl;
	if (attemptAmount == 6)
	{
		std::cout << "[FINAL] ";
	}
}

//Prints failure message and ends program
void EndProgram(std::string givenReason)
{
	//Ensure nothing remains in the input stream
	std::cin.clear();
	std::cin.sync();

	if (givenReason != "no") std::cout << std::endl << givenReason << std::endl;
	std::cout << "Press Enter / Return key to exit";
	std::cin.get();
}

//Asks if a type is desired
bool Prompt(std::string type, bool &choice)
{
	//Initialize variable
	std::string ask = "\0";
	std::cin.clear();
	std::cin.sync();
	//Print prompt
	std::cout << std::endl;
	MakeLine(35);
	std::cout << std::endl << "Should " << type << " be included?" << std::endl << "> ";
	std::cin.clear();
	std::cin.sync();
	while (ask == "\0") {
		getline(std::cin, ask);
	}
		
	//Convert input to lowercase
	transform(ask.begin(), ask.end(), ask.begin(), ::tolower);
	
	//Convert type to capital letters
	transform(type.begin(), type.end(), type.begin(), ::toupper);

	std::cout << "[STATUS: " << type;

	//Check input
	try {
		if (ask == "true" || ask == "yes" || ask == "affirmative" || ask == "yeah" || ask.at(0) == 'y')
		{
			std::cout << " ENABLED]" << std::endl;
			return true;
		}
		else
		{
			std::cout << " DISABLED]" << std::endl;
			return false;
		}
	}
	catch (...)
	{
		std::cerr << "[ERROR - DEFAULTING TO FALSE]" << std::endl;
		return false;
	}
}

//Function to generate password
void GeneratePass(int passLength, int runAmount, bool wantLower, bool wantUpper, bool wantSymbols, std::ostream &outstream)
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
	outstream << std::endl;
}