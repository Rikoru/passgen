#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

void GeneratePass(int passLength, int runAmount, bool wantLetters, bool wantSymbols, ostream& outstream);
void MakeLine(int lineLength);
char EndProgram(string givenReason);
void Prompt(string type, bool &choice);

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
	char outName[80] = { '\0' };		//The name of the output file

	//Give the header for the program
	MakeLine(35);
	cout << endl << "==== RANDOM PASSWORD GENERATOR ====" << endl;
	MakeLine(35);

	//Request password length
	cout << endl << "Input integer (8 to 256) for length" << endl;

	while (attempts <= 6)
	{
		cin.clear();
		cin.sync();
		MakeLine(35);
		cout << endl;

		//Line for amount of attempts
		MakeLine(19);
		cout << "Attempts: " << attempts << " / 6" << endl << "> ";
		if (attempts == 6)
		{
			cout << "(last attempt) ";
		}
		if (!(cin >> length))
		{
			if (attempts < 6)
			{
				cerr << endl << "ERROR: Invalid length, try again!" << endl;
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
				cerr << endl << "ERROR: Not within specified range!" << endl;
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
		EndProgram("Too many attempts!");
		return -1;
	}

	//Check for wanting letters and symbols
	Prompt("letters", alphabet);
	Prompt("symbols", symbols);

	//Request amount of passwords to generate
	while (amountGen < 1 || amountGen > 100)
	{
		cin.clear();
		cin.sync();

		//Print prompt
		MakeLine(35);
		cout << endl << "Amount of passwords to generate: ";
		cin >> amountGen;
		if (amountGen < 1 || amountGen > 100)
		{
			cout << "Please enter a number between 1 and 100";
		}
	}
	
	//Request output file name
	MakeLine(35); 
	cout << endl << "Input an output file name: ";
	cin >> outName;

	//Try to create the file specified
	outFile.open(outName, ios::app);
	if (outFile.fail())
	{
		MakeLine(35);
		cerr << endl << "ERROR: Failed to create file " << outName << endl;
		MakeLine(35);
		EndProgram("Couldn't create file!");
		return -1;
	}

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
		MakeLine(13);
		cout << "Generated: " << setw(4) << pass << " / " << setw(4) << amountGen << endl;
	}

	outFile.close();
	EndProgram("Success, check your file.");
	return 0;
}

void Prompt(string type, bool &choice)
{
	//Initialize variables
	string ask = "no";
	
	//Print prompt
	MakeLine(35);
	cout << endl << "Would you like to include " << type << "?" << endl << "> ";
	cin.clear();
	cin.sync();
	cin >> ask;
	
	//Convert input to lowercase
	transform(ask.begin(), ask.end(), ask.begin(), ::tolower);
	
	//Check input
	if (ask == "true" || "yes" || "affirmative" || "yeah" || "y")
	{
		cout << endl << "You chose to include " << type << endl;
		choice = true;
	}
	else
	{
		cout << "You chose to not include " << type << endl;
		choice = false;
	}
}

//Produces lines across screen
void MakeLine(int lineLength)
{
	for (int i = 0; i < lineLength; i++)
	{
		cout << '=';
	}
	cout << ' ';
}

//Prints failure message and ends program
char EndProgram(string givenReason)
{
	char tempChar[80] = { '\0' };
	
	cin.clear();
	cin.sync();

	cout << endl << givenReason << endl 
		 << "Input any character to end program: ";
	cin >> tempChar;

	return tempChar[0];
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