/****************************************************************************************
	Giselle Northy - OSU Post-Bacc CS Student
	Oregon State Beaverhacks Summer 2018
	Single Player Hangman Version 1.0

	My single player hangman randomly pickes a word or phrase from a game uses a txt library
	that the player needs to guess in order to win!

	Words can be added to library.txt so long as white spaces are not left on accident.

	Correct guesses don't count against total guesses. 

	Resources:

	A. Git guide http://rogerdudler.github.io/git-guide/
	B. Counting lines in a txt file https://stackoverflow.com/questions/3482064/counting-the-number-of-lines-in-a-text-file
	C. Randomizing http://www.cplusplus.com/reference/cstdlib/rand/
	D. Convert strings to upper or lower case https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
	E. Input validation only letters through the alphabet https://stackoverflow.com/questions/7616867/how-to-test-a-string-for-letters-only
	F. Check to see if this letter has already been guessed or not http://www.cplusplus.com/reference/string/string/find/
	G. English word list https://github.com/dwyl/english-words/blob/master/words_alpha.zip
****************************************************************************************/

	#include <iostream>
	#include <fstream>
	#include <algorithm>
	#include <iterator>
	#include <cstdlib> // for random
	#include <time.h> // initalize random

	// # of letter guesses allowed before losing
	#define NUM_GUESSES (10)


/****************************************************************************************
	Call menu function 1.
****************************************************************************************/
using namespace std;


int menu (string menuQuestion, int MIN, int MAX); 

int main()
{
	
	// declare variables
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
	bool play;
	
	cout << "Hello and Welcome to Giselle's Single Player Hangman!\n";
	
	// Call the starting menu
	choice = menu ("Press 1 to Start\nPress 2 to Quit\n", 1, 2);
				
	if (1 == choice)
	{
		play = true;
	}
	else if (2 == choice)
	{
		return 0;
	}

	// cannot read the library file
	if (!readFile)
	{
		cout << "Can't find the file!\n";
	}


/****************************************************************************************
	Reads how many lines (words or phrases) that are in the library file
	Resource: 
	B. Counting lines in a txt file https://stackoverflow.com/questions/3482064/counting-the-number-of-lines-in-a-text-file
****************************************************************************************/	

	// ignore white space
	readFile.unsetf (ios_base::skipws);

	// count lines
	unsigned lineCount = count(istream_iterator<char>(readFile), istream_iterator<char>(), '\n');

	// testing if string from library file is being read correctly
	//cout << "File has this many lines:" << lineCount << "\n";
	
/****************************************************************************************
	Game: finding the random #, getting the word or phrase to guess and initializing the
	display word.
	Resource: 
	C. Randomizing http://www.cplusplus.com/reference/cstdlib/rand/
****************************************************************************************/	
	
	srand (time(NULL));
	
	bool playGame = true;
	
	while (playGame)
	{
		// Randoming the number-of-lines-in-a-text-file
		int random = rand() % lineCount; 
		
		// for testing the random # generated
		//cout << "Random = " << random << "\n";

		string phrase;
		
		// read the file again to get the word or phrase that was randomly picked 	
		ifstream readFileAgain;
		readFileAgain.open ("library.txt");
		
		// go through the file and pick the line # that was randomly picked above
		for (int i = 0; i <= random; i++)
		{
			getline (readFileAgain, answerString);
		}
		
		// for testing the string for getting length correctly
		//cout << " trying to get the line " << answerString << "\nNumber of characters in string: " << answerString.length() << endl;
		
		// Create the display word with a bunch of underscores or empty spaces for space between words
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
		
		
/****************************************************************************************
	Displays the game couts to user, gueses left, what they've guessed and input validation
	Resources: 
	D. Convert strings to upper or lower case https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
	E. Input validation only letters through the alphabet https://stackoverflow.com/questions/7616867/how-to-test-a-string-for-letters-only
	F. Check to see if this letter has already been guessed or not http://www.cplusplus.com/reference/string/string/find/
****************************************************************************************/

		// make secret phrase all uppercase
		transform(answerString.begin(), answerString.end(), answerString.begin(), ::toupper);
		
		// check # of guesses left
		while (guessesLeft > 0)
		{
			// display the current word with __ for unguessed letters
			cout << "Current word: " << displayWord;
			
			cout << "\nLetters you've guessed: " << guesses << "\nYou have " << guessesLeft << " guesses left!" << endl;

			// declare guess - the letter player will guess
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
			if (guess.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos)
			{
				cout << "Please enter only 1 letter and no punctuation.\n";
				continue;
			}
			
			// Check to see if this letter has already been guessed or not
			size_t found = guesses.find(guess);
				
			// checking to see if it is in the string
			if(found != string::npos) // if this true then it is in the string
			{
				cout << "You already guessed that.\n";
				continue;
			}
			
			// Add this guess to the list of guessed characters and concatenate string together
			guesses = guesses + guess; 
			
			// check if the guess string is in the answer string
			bool letterIsInAnswer = false;
			for (int i = 0; i < answerString.length(); ++i)
			{
				if (answerString.at(i) == guess.at(0))
				{
					//add it displayWord
					displayWord.at(i) = guess.at(0);
					
					// for testing
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
				cout << "You correctly guessed: " << displayWord << ". Good job! :)" << endl;
				break;
			}
			
		}

		if (0 == guessesLeft)
		{
			cout << "Sorry you lost!\n";
		}
		else
		{
			cout << "You win!\n";
		}
		
/****************************************************************************************
	End of a game: Reset variables, ask user to play again or quit
****************************************************************************************/

		// reset guesses to having no guesses in it
		guesses = "";
		guessesLeft = NUM_GUESSES;
		displayWord = "";
		answerString = "";
		
		string playAgain;
		bool questionLoop = true;

		// Menu loop to play or quit after a game instance
		while (questionLoop == true)
		{
			cout << "Play again? Y or N\n";
			cin >> playAgain;
			
			if (playAgain.at(0) == 'Y' || playAgain.at(0) == 'y')
			{
				cout << "Playing again!\n";
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
			}
		}
	}
	
	return 0;
}
	// End of MAIN

/****************************************************************************************
	Menu function 1. with input validation
****************************************************************************************/
	
	int menu (string menuQuestion, int MIN, int MAX)
	{
		string menuChoice;
		
		while (true)
		{
			cout << menuQuestion;
			cin >> menuChoice;
			
			// check to see if they type is not a number
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

