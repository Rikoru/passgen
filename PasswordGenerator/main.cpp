#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

void GeneratePass(int passLength, int runAmount, bool wantLetters, bool wantSymbols, ostream& outstream);

int main()
{
	//Declare and initialize variables
	int length = 0;						//Length of password to be generated
	int attempts = 0;					//Amount of attempts for length input
	int amountGen = 0;					//Amount of passwords to generate
	bool failure = false;				//Failure to input the length
	bool alphabet = false;				//Whether or not to include letters
	bool symbols = false;				//Whether or not to include symbols
	ofstream outFile;					//The stream for the output file
	char outName[80] = {'\0'};			//The name of the output file
	string prompt;						//Prompts that accept yes/no/true/false
	//time_t t = time(0);					//Acquire current time
	//struct tm * now = localtime(&t);	//Structure to display current time

	//Give the header for the program
	cout << "===================================" << endl
		 << "==== RANDOM PASSWORD GENERATOR ====" << endl
		 << "===================================" << endl;
	
	//Request password length
	cout << "= Input integer for length of =====" << endl
		 << "= password to generate: 8 to 256 ==" << endl;
	while (attempts <= 6)
	{
		cin.clear();
		cin.sync();
		cout << "===================================" << endl
			 << "===================== " << "Attempts: " << attempts << " =" << endl;
		cout << "> ";
		if (!(cin >> length))
		{
			if (attempts < 6)
			{
				cerr << "-ERROR: Invalid length, try again!" << endl;
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
				cerr << "-ERROR: Not within specified range!" << endl;
				attempts++;
				continue;
			}
			else
			{
				failure = true;
				break;
			}
		}
		else
		{
			break;
		}
	}
	
	//Check if too many attempts have been performed
	if (failure == true)
	{
		cerr << "Too many attempts. Rerun program." << endl;
		system("PAUSE");
		return -1;
	}

	cin.clear();
	cin.sync();

	//Check for wanting letters
	cout << "===================================" << endl
		 << "== Should letters be in password? =" << endl
		 << "== true/yes/YES/y/Yes if you want =" << endl
		 << "===================================" << endl
		 << "> ";
	cin >> prompt;
	if (prompt == "true" || prompt == "yes" || prompt == "YES" || prompt == "y" || prompt == "Yes")
	{
		cout << "You chose to include letters" << endl;
		alphabet = true;
	}
	else
	{
		cout << "You chose to not include letters" << endl;
		alphabet = false;
	}
	
	prompt = "no";
	cin.clear();
	cin.sync();

	//Check for wanting symbols
	cout << "===================================" << endl
		 << "== Should symbols be in password? =" << endl
		 << "== true/yes/YES/y/Yes if you want =" << endl
		 << "===================================" << endl
		 << "> ";
	cin >> prompt;
	if (prompt == "true" || prompt == "yes" || prompt == "YES" || prompt == "y" || prompt == "Yes")
	{
		cout << "You chose to include symbols" << endl;
		symbols = true;
	}
	else
	{
		cout << "You chose to not include symbols" << endl;
		symbols = false;
	}

	cin.clear();
	cin.sync();

	//Request amount of passwords to generate
	while (amountGen < 1 || amountGen > 100)
	{
		cin.clear();
		cin.sync();
		cout << "===================================" << endl
			 << "= How many passwords to generate? =" << endl
			 << "= Must be between 1 and 100 =======" << endl
			 << "===================================" << endl
			 << "> ";
		cin >> amountGen;
	}
	

	//Request output file name
	cout << "===================================" << endl
		 << "==== Input an output file name ====" << endl
		 << "===================================" << endl
		 << "> ";
	cin >> outName;

	//Try to create the file specified
	outFile.open(outName, ios::app);
	if (outFile.fail())
	{
		cerr << "===================================" << endl
			 << "-ERROR: Failed to create file " << outName << endl
			 << "===================================" << endl;
		system("PAUSE");
		return -1;
	}

	////Display time of generation
	//outFile << "Time of generation: "
	//		<< (now->tm_year + 1900) << '-'
	//		<< (now->tm_mon + 1) << '-'
	//		<< now->tm_mday << endl;

	//Send to function
	for (int pass = 1; pass <= amountGen; pass++)
	{
		if (pass == 1)
		{
			outFile << "= " << "Length: " << setw(4) << length << " ==== Amount: " << setw(4) << amountGen << ' ';
			for (int equalism = 33; equalism < (length - 1); equalism++)
			{
				outFile << '=';
			}
			outFile << '=' << endl;
		}
		GeneratePass(length, pass, alphabet, symbols, outFile);
		cout << "============ " << "Generated: " << setw(4) << pass << " / " << setw(4) << amountGen << endl;
	}

	//Announce completion
	cout << "===================================" << endl
		 << "==== Success, check your file =====" << endl
		 << "===================================" << endl;

	outFile.close();
	system("PAUSE");
	return 0;
}

//Function to generate password
void GeneratePass(int passLength, int runAmount, bool wantLetters, bool wantSymbols, ostream& outstream)
{
	unsigned int tempo = (unsigned int)time(0);
	srand(tempo % (runAmount + (tempo/100)));
	char letters[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	char symbo[11] = { '!', '#', '@', '~', '$', '^', '.', ',', '-', '+', '%' };
	
	if (passLength < 34)
	{
		for (int spacer = 0; spacer < (34 - passLength); spacer++)
		{
			outstream << ' ';
		}
	}

	for (int p = 0; p < passLength; p++)
	{
		if (wantLetters == true && (p % 5 == 0))
		{
			outstream << letters[rand() % 26];
		}
		else if (wantSymbols == true && (p % 7 == 0))
		{
			outstream << symbo[rand() % 11];
		}
		else
		{
			outstream << (rand() % 10);
		}
	}

	outstream << endl;
}