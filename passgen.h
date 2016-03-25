#ifndef _PASSGEN_H_
#define _PASSGEN_H_
#include <iostream> //Input-output
#include <random> //PRNG stuff
#include <algorithm> //Transform function

class Passgen {
public:
	Passgen();
	~Passgen();

	//length, amount, lowercase, uppercase, symbols
	Passgen(int len, int amt, bool smA, bool lgA, bool sym);

	//Outputs value to standard out
	void printPass(bool outMeta);
	void printMeta();

private:
	int length;
	int amount;
	bool lowercase;
	bool uppercase;
	bool symbols;
};

Passgen::Passgen() {
	length = 8;
	amount = 1;
	lowercase = false;
	uppercase = false;
	symbols = false;
}

Passgen::Passgen(int len, int amt, bool smA, bool lgA, bool sym) {
	if (len < 6) length = 6;
	else if (len > 256) length = 256;
	else length = len;

	if (amt < 1) amount = 1;
	else if (amt > 1000) amount = 1000;
	else amount = amt;

	lowercase = smA;
	uppercase = lgA;
	symbols = sym;
}

Passgen::~Passgen() {
	//Nothing to destroy, vectors are magic
}

void Passgen::printPass(bool outMeta) {
	if (length > 1 && outMeta) printMeta();
	for (int i = 0; i < amount; i++) {

		//Initializes random number generator
		std::random_device rd;
		std::mt19937 mt(rd());

		//Provides boundaries for where to distribute numbers
		std::uniform_int_distribution<int> numDist(0, 9); //Random distribution for numbers
		std::uniform_int_distribution<int> letDist(0, 25); //Random distribution for letters
		std::uniform_int_distribution<int> symDist(0, 13); //Random distribution for symbols
			
		//Determines which options can be used for the output
		std::vector<int> choices = {1}; //Always include numbers
		if (lowercase) choices.push_back(2); //Include lowercase
		if (uppercase) choices.push_back(3); //Include uppercase
		if (symbols) choices.push_back(4); //Include symbols
		std::uniform_int_distribution<int> typeDist(0, choices.size() - 1);

		//Storage of characters available
		char lowerCase[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
		char upperCase[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
		char symbo[14] = { '!', '#', '@', '~', '$', '^', '.', ',', '-', '+', '%', '?', '*', '=' };
		
		//Prints to output file
		for (int p = 0; p < length; p++)
		{
			switch (choices[typeDist(mt)])
			{
			case 1: //Numbers
				std::cout << numDist(mt);
				break;
			case 2: //Lowercase
				std::cout << lowerCase[letDist(mt)];
				break;
			case 3: //Uppercase
				std::cout << upperCase[letDist(mt)];
				break;
			case 4: //Symbols
				std::cout << symbo[symDist(mt)];
				break;
			}
		}
		std::cout << "\n";
	}
}

void Passgen::printMeta() {
	std::cout << "PasswordGenerator | length: " << length << " | amount: " << amount << "\n";
}







#endif //_PASSGEN_H_