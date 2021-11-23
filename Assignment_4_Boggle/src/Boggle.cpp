/*
 * File: Boggle.cpp
 * ----------------
 * Name: Shorena Janjghava.
 * Section: Nikoloz Adeishvili.
 * This file is the main starter file for Assignment #4, Boggle.
 */

#include <iostream>
#include "foreach.h"
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
using namespace std;

/* Function prototype declarations. */
void gameOfBoggle();
void welcome();
void giveInstructions();
void gameSetup();
bool getYesOrNo(string prompt, string reprompt);
bool answerIsYes(string input);
bool answerIsNo(string input);
string getUserConfiguration();
void updateToSpecificBoard(string userConfiguration);
Vector<string> arrayToVector();
void shuffleCubes(Vector<string>& cubes);
void updateToRandomBoard(Vector<string>& cubes);
void displayTheBoard();
void humanTurn();
bool isMinLength(string word); 
bool isInLexicon(string word); 
bool isFirstGuess(string word);
bool isTraceable(string word);
bool searchForPaths(string& word, int row, int col);
string indicesToSequence(int row, int col);
void highlightTheWord();
void highlightProperCubes(int& row, int& col, bool highlightSwitch);
void sequenceToIndices(string sequence, int& row, int& col);
void computerTurn();
void findAllRemainingWords(string& word, int row, int col);
void displayComputerGuesses();
void playAgainOrQuit();

/* Constant variable declarations. */
const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;
const int BOARD_SIZE = 4;
const int MAX_CUBES = BOARD_SIZE * BOARD_SIZE; 
const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
const int CUBE_SIDES = 6;
const int MIN_WORD_LENGTH = 4;
const int HIGHLIGHT_DURATION = 400;

/* Instance variable declarations. */ 
Lexicon englishWords("EnglishWords.dat");
bool wantToPlayAgain = true;
Grid<char> board(BOARD_SIZE, BOARD_SIZE);
Set<string> wordsGuessedByHuman;
Set<string> usedIndices;
Set<string> wordsGuessedByComputer;

/* This function generates the well-known game of Boggle. */ 
int main() {
	GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
	gameOfBoggle();
    return 0;
}

/* This function handles the process of playing the game. */ 
void gameOfBoggle(){
	welcome();
    giveInstructions();
	while(wantToPlayAgain){
		gameSetup();
		humanTurn();
		computerTurn();
		playAgainOrQuit();
	}
}

/* This function outputs an introductory message to the user at the
   beginning of the game. */ 
void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/* This function outputs the instructions of the game to the user at
   the beginning of the game. */ 
void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

/* This function generates a random or a specific board for the game
   depending on the user's decision. */ 
void gameSetup(){
	drawBoard(BOARD_SIZE, BOARD_SIZE);
	cout << endl;
	cout << "I'll give you a chance to set up the board to your specification, which makes it easier to confirm your boggle program is working. " << endl;
	string prompt = "Do you want to force the board configuration? ";
	string reprompt = "Please answer yes or no.";
	if(getYesOrNo(prompt, reprompt)){
		string userConfiguration = getUserConfiguration();
		updateToSpecificBoard(userConfiguration);
	} else {
		Vector<string> cubes = arrayToVector();
		shuffleCubes(cubes);
		updateToRandomBoard(cubes);
	}
	displayTheBoard();
}

/* This function prompts a question for the user, determines the answer and
   reprompts if the answer was not specific enough. */
bool getYesOrNo(string prompt, string reprompt){
	string input = getLine(prompt);
	while(input == "" || (!answerIsYes(input) && !answerIsNo(input))){
		cout << reprompt << endl;
		input = getLine(prompt);
	} 
	if(answerIsYes(input)) return true; 
	if(answerIsNo(input)) return false;
}

/* If the beginning letter of the user's input is 'Y' (case-insensitive) 
   the function will regard it as a "Yes". */ 
bool answerIsYes(string input){
	if(input[0] == 'y' || input[0] == 'Y') return true;
	return false;
}

/* If the beginning letter of the user's input is 'N' (case-insensitive) 
   the function will regard it as a "No". */ 
bool answerIsNo(string input){
	if(input[0] == 'n' || input[0] == 'N') return true;
	return false;
}

/* This function asks the user for a specific board configuration and 
   reprompts if the input is too short. */ 
string getUserConfiguration(){
	cout << "Enter a " << MAX_CUBES << "-character string to identify which letters you want on the cubes. " << endl;
	cout << "The first 4 letters are the cubes on the top row from left to right, the next 4 letters are the second row, and so on. " << endl;
	string prompt = "Enter the string: ";
	string reprompt = "String must include " + integerToString(MAX_CUBES) + " characters! Try again: ";
	string userConfiguration = getLine(prompt);
	while(userConfiguration.size() < MAX_CUBES) userConfiguration = getLine(reprompt);
	return toUpperCase(userConfiguration);
}

/* This function updates the board to the specific configuration entered
   by the user. */ 
void updateToSpecificBoard(string userConfiguration){
	int currentLetterIndex = 0;
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			board[i][j] = userConfiguration[currentLetterIndex];
			currentLetterIndex++;
		}
	}
}

/* This function transforms data structure from an Array to a Vector. */ 
Vector<string> arrayToVector(){
	Vector<string> cubes(MAX_CUBES);
	for(int i = 0; i < MAX_CUBES; i++){
		cubes[i] = STANDARD_CUBES[i];
	}
	return cubes;
}

/* This function randomises the positions of the cubes on the board. */ 
void shuffleCubes(Vector<string>& cubes){
	for(int i = 0; i < cubes.size(); i++){
		int randomIndex = randomInteger(i, cubes.size() - 1);
		string temporary = cubes[i];
		cubes[i] = cubes[randomIndex];
		cubes[randomIndex] = temporary;
	}
}

/* This function randomises each cube value on the board. */ 
void updateToRandomBoard(Vector<string>& cubes){
	int currentCubeIndex = 0;
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			string cube = cubes[currentCubeIndex];
			int randomSide = randomInteger(0, CUBE_SIDES - 1);
			board[i][j] = cube[randomSide];
			currentCubeIndex++;
		}
	}
}

/* This function updates the board visually. */ 
void displayTheBoard(){
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			char letter = board[i][j];
			labelCube(i, j, letter);
		}
	}
}

/* This function handles the process of human's turn in the game. */ 
void humanTurn(){
	string prompt = "Enter a word: ";
	string word = getLine(prompt);
	while(word != ""){
		word = toUpperCase(word);
		if(isMinLength(word) && isInLexicon(word) && isFirstGuess(word) && isTraceable(word)){
			wordsGuessedByHuman.add(word);
			recordWordForPlayer(word, HUMAN);
		} else {
			cout << "You must enter an unfound yet traceable word from the dictionary of length 4+. " << endl;
		}
		word = getLine(prompt);
	}
}

/* This function checks whether the word satisfies the minimum length standard. */ 
bool isMinLength(string word){
	if(word.length() >= MIN_WORD_LENGTH) return true;
	return false;
}

/* This function checks whether the word exists in the lexicon of English words. */ 
bool isInLexicon(string word){
	if(englishWords.contains(word)) return true;
	return false;
}

/* This function checks whether the word has been correctly guessed before. */ 
bool isFirstGuess(string word){
	if(!wordsGuessedByHuman.contains(word)) return true;
	return false;
}

/* This function checks whether the word is traceable on the board. */ 
bool isTraceable(string word){
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			usedIndices.clear();
			if(searchForPaths(word, i, j)){
				highlightTheWord();
				return true;
			}
		}
	}
	return false;
}

/* This recursive function searches for a path on the board for a word guess
   from the user. */ 
bool searchForPaths(string& word, int row, int col){
	/* Base case. */ 
	if(word == "") return true;

	/* Recursive case. */ 
	else {
		if(board[row][col] == word[0]){
			usedIndices.add(indicesToSequence(row, col));
			if(word.length() <= 1){
				word = "";
				return searchForPaths(word, row, col);
			} else {
				char letter = word[0];
				word = word.substr(1);
				for(int m = -1; m < 2; m++){
					for(int n = -1; n < 2; n++){
						if(board.inBounds(row + m, col + n) && !usedIndices.contains(indicesToSequence(row + m, col + n)) 
							&& searchForPaths(word, row + m, col + n)) return true;
					}
				}
				word = letter + word;
				usedIndices.remove(indicesToSequence(row, col));
			}
		}
	}
	usedIndices.remove(indicesToSequence(row, col));
	return false;
}

/* This function converts the row and column numbers into a single sequence. */ 
string indicesToSequence(int row, int col){
	string sequence = integerToString(row) + integerToString(col);
	return sequence;
}

/* This function highlights a specific word on the display. */ 
void highlightTheWord(){
	int row;
	int col;
	highlightProperCubes(row, col, true);
	pause(HIGHLIGHT_DURATION);
	highlightProperCubes(row, col, false);
}

/* This function highlights or un-highlights each cube that
   belongs to the word. */ 
void highlightProperCubes(int& row, int& col, bool highlightSwitch){
	foreach(string sequence in usedIndices){
		sequenceToIndices(sequence, row, col);
		highlightCube(row, col, highlightSwitch);
	}
}

/* This function converts a single sequence into specific row and column numbers. */ 
void sequenceToIndices(string sequence, int& row, int& col){
	row = sequence[0] - '0';
	col = sequence[1] - '0';
}

/* This function handles the process of computer's turn in the game. */ 
void computerTurn(){
	for(int row = 0; row < BOARD_SIZE; row++){
		for(int col = 0; col < BOARD_SIZE; col++){
			for(int m = -1; m < 2; m++){
				for(int n = -1; n < 2; n++){
					if(!(m == 0 && n == 0) && board.inBounds(row + m, col + n)){
						string prefix = "";
						prefix += board[row][col];
						prefix += board[row + m][col + n];
						if(englishWords.containsPrefix(prefix)){
							usedIndices.clear();
							usedIndices.add(indicesToSequence(row, col));
							findAllRemainingWords(prefix, row + m, col + n);
						}
					}
				}
			}
		}
	}
	displayComputerGuesses();
}

/* This recursive function finds all the words omitted by the user on the board. */ 
void findAllRemainingWords(string& word, int row, int col){
	/* Base case. */ 
	if(word.length() == MAX_CUBES){
		if(englishWords.contains(word) && !wordsGuessedByHuman.contains(word)){
			wordsGuessedByComputer.add(word);
		}
		return;
	} 
	
	/* Recursive case. */ 
	else {
		if(word.length() >= MIN_WORD_LENGTH && englishWords.contains(word) && !wordsGuessedByHuman.contains(word)){
			wordsGuessedByComputer.add(word);
		}
		string tmp = indicesToSequence(row, col);
		usedIndices.add(indicesToSequence(row, col));
		for(int m = -1; m < 2; m++){
			for(int n = -1; n < 2; n++){
				int newRow = row + m;
				int newCol = col + n;
				if(board.inBounds(newRow, newCol) && !usedIndices.contains(indicesToSequence(newRow, newCol))){
					word += board[newRow][newCol];
					if(englishWords.containsPrefix(word)){
						findAllRemainingWords(word, newRow, newCol);
					}
					usedIndices.remove(indicesToSequence(newRow, newCol));
					word = word.substr(0, word.length() - 1);
				}
			}
		}
		usedIndices.remove(indicesToSequence(row, col));
	}
	usedIndices.remove(indicesToSequence(row, col));
	return;
}

/* This function updates the display with words found by the computer. */ 
void displayComputerGuesses(){
	foreach(string word in wordsGuessedByComputer){
		recordWordForPlayer(word, COMPUTER);
	}
}

/* This function finds out whether the user wants to play again or quit. */ 
void playAgainOrQuit(){
	string prompt = "Would you like to play again? ";
	string reprompt = "Please answer yes or no.";
	if(getYesOrNo(prompt, reprompt)){
		wordsGuessedByHuman.clear();
		usedIndices.clear();
		wordsGuessedByComputer.clear();
	} else {
		wantToPlayAgain = false;
	}
}