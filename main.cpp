/*************************************************************
Giselle Northy
Oregon State Beaverhacks Summer 2018
Single Player Hangman

References:

http://rogerdudler.github.io/git-guide/


*************************************************************/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <cstdlib> // for random
#include <time.h> // initalize random
#include <vector>

#define NUM_GUESSES (1)


/****************************************************************************************


****************************************************************************************/
using namespace std;


int menu (string menuQuestion, int MIN, int MAX); // menu function 

int main()
{
	
	// declare variables and functions
	string guesses = "";
	string answerString;
	string displayWord;

	int guessesLeft = NUM_GUESSES;


	// open the file

	ifstream readFile;
	readFile.open("library.txt");

	
/****************************************************************************************
	Welcome to Hangman Menu function
****************************************************************************************/


	int choice;
	bool play; // initalize whether to play or not
	
	cout << "Hello and Welcome to Giselle's Single Player Hangman!\n";
	
	// call the starting menu

	choice = menu ("Press 1 to Start\nPress 2 to Quit\n", 1, 2);
				
	if (1 == choice)
	{
		play = true;
	}
	else if (2 == choice)
	{
		//play = false;
		return 0;
	}



// read the library file


	if (!readFile)
	{
		cout << "Can't fine the file!\n";
	}
	// https://stackoverflow.com/questions/3482064/counting-the-number-of-lines-in-a-text-file


/****************************************************************************************


****************************************************************************************/	
/*******************************

	This is for reading how many lines are in the file

********************************/	
	// ignore white space

	readFile.unsetf (ios_base::skipws);

	// count lines
		
	unsigned lineCount = count(istream_iterator<char>(readFile), istream_iterator<char>(), '\n');


	cout << "File has this many lines:" << lineCount << "\n"; 

	// This is for randoming the number-of-lines-in-a-text-file
	// http://www.cplusplus.com/reference/cstdlib/rand/


/****************************************************************************************
	Game functions
****************************************************************************************/	
	
	srand (time(NULL));
	
	bool playGame = true;
	
	while (playGame)
	{

		int random = rand() % lineCount;

		cout << "Random = " << random << "\n";

		// open file again to get the line

		
		// read the line
		
		int thing = 5;
		//getline(readFile)
		string phrase;
		
		ifstream readFileAgain;
		readFileAgain.open ("library.txt");
		
		for (int i = 0; i <= random; i++) // go through the file and pick the line # that was randomly picked above
		{
			getline (readFileAgain, answerString);
		}
		cout << " trying to get the line " << answerString << "\nNumber of characters in string: " << answerString.length() << endl;
		
		// Create the display word with a bunch of underscores
		for (int i = 0; i < (answerString.length() - 1); ++i)
		{
			if (answerString.at(i) == ' ')
			{
				displayWord = displayWord + " ";
			}
			else
			{
				displayWord = displayWord + "_";
			}
		}
		
		// make secret phase all uppercase
		// https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
		transform(answerString.begin(), answerString.end(), answerString.begin(), ::toupper);
		
	// check # of guesses left
		while (guessesLeft > 0)
		{
					
			cout << "Current word: " << displayWord << "\nGuessed letters " << guesses << "\nNumber of guesses left: " << guessesLeft << endl;

			// 1.a if guesses left 0, cout you lost!
			
			//else keep going call the function to get the guess some_character??

			// cin guess a character
			
			// input validation only 1 string length in size
			// input validation only letters through the alphabet
			// use function to change letters to uppercase
			string guess;
			
			cout << "Guess a letter!\n";
			cin >> guess;
			
			// input validation here
			guess.length();
			
			if (guess.length() > 1)
			{
				cout << "Too many letters. Only use 1 letter\n";
				continue; // continue means go back to top of loop
			}
			//convert guess to be upper case
			transform (guess.begin(), guess.end(),guess.begin(), ::toupper);
			
			// input validation only letters through the alphabet
			// https://stackoverflow.com/questions/7616867/how-to-test-a-string-for-letters-only
			if (guess.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos)
			{
				cout << "Please enter only 1 letter and no punctuation\n";
				continue;
			}
			
			// Check to see if this letter has already been guessed or not
			// http://www.cplusplus.com/reference/string/string/find/
			size_t found = guesses.find(guess);
				
			// checking to see if it is in the string
			if(found != string::npos) // if this true then it is in the string
			{
				cout << "You already guessed that.\n";
				// loop back to ask again ??
				continue;
			}
			
			// Add this guess to the list of guessed characters
			guesses = guesses + guess; // concatenate string together
			
			// check if the guess string is in the answer string
			
			//found = answerString.find(guess); // needs to find all of them in the answer String
			bool letterIsInAnswer = false;
			for (int i = 0; i < answerString.length(); ++i)
			{
				if (answerString.at(i) == guess.at(0))
				{
					//add it displayWord
					displayWord.at(i) = guess.at(0);
					
					// cout << "That letter is in the string\n";
					
					letterIsInAnswer = true;
				}
			}
			
			// check if we found a letter or not
			if (letterIsInAnswer == false)
			{
				--guessesLeft;
			}
			
			// see if the player has won, see if there are any underscores left in the display word
			found = displayWord.find("_");
			if (found == string::npos)
			{
				cout << displayWord << endl;
				break;
			}
			
			
			// cout << "Current Guesses string: " << guesses << "\n";
			
		
			// cin << 

		// check if character is already guessed
			// if character not already guessed
				// add it to guesses
				// check if in the word(s)
				// if not in word(s) -> --guesses left
					// in in word(s) -> update the vector and display ??

			//
			
		}
		if (0 == guessesLeft)
		{
			cout << "Sorry you lost!\n";
		}
		else
		{
			cout << "You win!\n";
			// add variable for wins ?
		}


		// reset guesses to having no guesses in it
		guesses = "";
		guessesLeft = NUM_GUESSES;
		displayWord = "";
		answerString = "";
		
		string playAgain;
		bool questionLoop = true;
		
		while (questionLoop == true)
		{
			cout << "Play again? Y or N\n";
			cin >> playAgain;
			
			if (playAgain.at(0) == 'Y' || playAgain.at(0) == 'y')
			{
				playGame = true;
				questionLoop = false;
			}
			else if (playAgain.at(0) == 'N' || playAgain.at(0) == 'n')
			{
				playGame = false;
				break;
			}
			else 
			{
				cout << "Does not compute - Try again!\n";
				questionLoop = true;
				//continue;
			}
		}
	}
	
	return 0;
}
	// End of MAIN

/****************************************************************************************
	Menu function with input validation
****************************************************************************************/

	
	int menu (string menuQuestion, int MIN, int MAX)
	{
		string menuChoice;
		
		while (true)
		{
			cout << menuQuestion;
			cin >> menuChoice;
			
			// check to see if they type in not a number
			if (menuChoice.find_first_not_of("1234567890") != string::npos)
			{
				cout << "Did not compute - Try again!\n";
				continue;
			}
			else
			{
				int convertMenuChoice = stoi(menuChoice); // convert input to an Int
				if (convertMenuChoice < MIN || convertMenuChoice > MAX)
				{
					cout << "Invaliad number - Try again!\n"; // makes sure the int is within the range
					continue;
				}
				return convertMenuChoice;
			}
		
		}	
	}

