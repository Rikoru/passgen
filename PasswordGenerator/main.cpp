#include <iostream>		//Always needed
#include <random>		//PRNG stuff
#include <algorithm>	//Transform function
#include <fstream>		//File I/O
#include <iomanip>		//Convenient spacing
#include <string>		//Manipulate strings
using namespace std;

void MakeLine(int lineLength);
void PrintAttempt(int attemptAmount);
void EndProgram(string givenReason);
bool Prompt(string type, bool& choice);
void GeneratePass(int passLength, int runAmount, bool wantLower, bool wantUpper, bool wantSymbols, ostream& outstream);

int main()
{
	//Declare and initialize variables
	int length = 0;						//Length of password to be generated
	int attempts = 0;					//Amount of attempts for length input
	int amountGen = 0;					//Amount of passwords to generate
	bool failure = false;				//Failure to input the length
	bool smallAlpha = false;			//Inclusion of lowercase letters
	bool largeAlpha = false;			//Inclusion of uppercase letters
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
		PrintAttempt(attempts);
		cout << "> ";

		if (!(cin >> length))
		{
			if (attempts < 6)
			{
				cerr << "ERROR: Not an integer!" << endl << endl;
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
				cerr << "ERROR: Not within specified range!" << endl << endl;
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
	while (amountGen < 1 || amountGen > 100)
	{
		cin.clear();
		cin.sync();

		//Prints the prompt
		cout << endl;
		MakeLine(35);
		cout << endl << "Passwords to generate (1 to 100)" << endl;
		MakeLine(35);
		cout << endl;
		PrintAttempt(attempts);
		cout << "> ";
		cin >> amountGen;
		
		//Check range
		if (amountGen < 1 || amountGen > 100)
		{
			if (attempts < 6)
			{
				cerr << "ERROR: Not within specified range!" << endl;
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
			cout << endl;
			outFile << "= " << "Length: " << setw(4) << length << " ==== Amount: " << setw(4) << amountGen << ' ';
			for (int equalism = 33; equalism < (length - 1); equalism++)
			{
				outFile << '=';
			}
			outFile << '=' << endl;
		}
		GeneratePass(length, pass, smallAlpha, largeAlpha, symbols, outFile);
		MakeLine(13);
		cout << "Generated: " << setw(4) << pass << " / " << setw(4) << amountGen << endl;
	}
	outFile << endl;
	outFile.close();
	EndProgram("Success, enjoy your file.\n");
	return 0;
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

void PrintAttempt(int attemptAmount)
{
	MakeLine(19);
	cout << "Attempts: " << attemptAmount << " / 6" << endl;
	if (attemptAmount == 6)
	{
		cout << "[FINAL] ";
	}
}

//Prints failure message and ends program
void EndProgram(string givenReason)
{
	//Ensure nothing remains in the input stream
	cin.clear();
	cin.sync();

	cout << endl << givenReason << endl
		<< "Press Enter / Return key";
	cin.get();
}

bool Prompt(string type, bool& choice)
{
	//Initialize variable
	string ask = "no";

	//Print prompt
	cout << endl;
	MakeLine(35);
	cout << endl << "Should " << type << " be included?" << endl << "> ";
	cin.clear();
	cin.sync();
	getline(cin, ask);
	
	//Convert input to lowercase
	transform(ask.begin(), ask.end(), ask.begin(), ::tolower);
	
	//Convert type to capital letters
	transform(type.begin(), type.end(), type.begin(), ::toupper);

	cout << "[STATUS: " << type;

	//Check input
	if (ask == "true" || ask == "yes" || ask == "affirmative" || ask == "yeah" || ask.at(0) == 'y' )
	{
		cout << " ENABLED]" << endl;
		return true;
	}
	else if (ask == "ayy lmao")
	{
		cout << " ARE FOR HUMANS]" << endl
			 << "[THEREFORE, NOT INCLUDED]" << endl;
		return false;
	}
	else
	{
		cout << " DISABLED]" << endl;
		return false;
	}
}

//Function to generate password
void GeneratePass(int passLength, int runAmount, bool wantLower, bool wantUpper, bool wantSymbols, ostream& outstream)
{
	//Initializes random number generator
	random_device rd;
	mt19937 mt(rd());

	//Provides boundaries for where to distribute numbers
	uniform_int_distribution<int> dist(0, 9);				//Random distribution for numeral array
	uniform_int_distribution<int> dist2(0, 25);				//Random distribution for letter arrays
	uniform_int_distribution<int> dist3(0, 13);				//Random distribution for symbol array
	uniform_int_distribution<int> dist4(1, passLength + 1);
	
	//Initialize arrays
	int numeralHold[256] = { '\0' };
	char lowerHold[256] = { '\0' };
	char upperHold[256] = { '\0' };
	char symboHold[256] = { '\0' };

	//Storage of characters available
	char lowerCase[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	char upperCase[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	char symbo[14] = { '!', '#', '@', '~', '$', '^', '.', ',', '-', '+', '%', '?', '*', '=' };
	
	//Fills arrays of desired password length
	for (int p = 0; p <= passLength ; p++)
	{
		numeralHold[p] = dist(mt);
		if (wantLower == true) lowerHold[p] = lowerCase[dist2(mt)];
		if (wantUpper == true) upperHold[p] = upperCase[dist2(mt)];
		if (wantSymbols == true) symboHold[p] = symbo[dist3(mt)];
	}

	//Prints from arrays to output file
	for (int p = 1; p <= passLength; p++)
	{
		if (wantLower == true && (p % dist4(mt) == 0)) outstream << lowerHold[p];
		else if (wantUpper == true && (p % dist4(mt) == 0)) outstream << upperHold[p];
		else if (wantSymbols == true && (p % dist4(mt) == 0)) outstream << symboHold[p];
		else outstream << numeralHold[p];
	}
	outstream << endl;
}