/**********
Things to do:

Read the file
Read each file by line
add a random # generator
vectors for answer word, guesses and display word

vector with display word initialized to _ for each letter




**********/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <cstdlib> // for random
#include <time.h> // initalize random

using namespace std;

int main()
{
	

	ifstream readFile;
	readFile.open("library.txt");
	
/****************
Use this to read the file lines testing http://www.cplusplus.com/forum/beginner/191283/
	

	string word; // the word in the text file	
	while(getline(readFile, word))
	{
		cout << "This is a word:" << word << endl;
	}

	cout << "did all the words\n";

********************************/	
	// bool play; // initalize whether to play or not
	
	
	// cout << "Hello and welcome to HangMAN!\n";
	// menu("1. Start\n2. Quit", 1, 2);
	
	// if(1 = choice)
	// {
		// play = true;
	// }
	// else(2 = choice)
	// {
		// play = false;
	// }


// menu function
// menu(string phrase, string choice)
// {
	// if(choice != "1234567890")
	// {
		// cout "Try again!";
	// }
// }


// read the library file


	if(!readFile)
	{
		cout << "Can't fine the file!\n";
	}
	// https://stackoverflow.com/questions/3482064/counting-the-number-of-lines-in-a-text-file

/*******************************

	This is for reading how many lines are in the file

********************************/	
	// ignore white space

	readFile.unsetf(ios_base::skipws);

	// count lines
		
	unsigned lineCount = count(istream_iterator<char>(readFile), istream_iterator<char>(), '\n');


	cout << "File has this many lines:" << lineCount << "\n"; 

	// This is for randoming the number-of-lines-in-a-text-file
	// http://www.cplusplus.com/reference/cstdlib/rand/

	srand (time(NULL));

	int random = rand() % lineCount + 1;

	cout << "Random = " << random << "\n";

	//readFile.close("library.txt");
	
	// open file again to get the line

	
	// read the line
	
	int thing = 5;
	//getline(readFile)
	string phrase;
	
	ifstream readFileAgain;
	readFileAgain.open("library.txt");
	
	for(int i = 0; i <= random; i++)
	{
		getline(readFileAgain, phrase);
	}
	cout << "trying to get the line " << phrase;

	cout << "random again " << 


	
	return 0;
}