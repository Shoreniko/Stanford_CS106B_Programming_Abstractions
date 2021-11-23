/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: Shorena Janjghava.
 * Section: Nikoloz Adeishvili.
 * This file is the starter project for the Word Ladder problem.
 */

#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
#include "queue.h"
#include "foreach.h"
using namespace std;

// Function prototype declarations.

int wordLadder();
bool userWantsToQuit(string startWord);
void initialPhase(string& startWord, string& endWord, Vector<string>& ladder, Queue<Vector<string> >& queue);
void findingTheLadder(Queue<Vector<string> >& queue, Lexicon& words, string startWord, string endWord, bool& ladderFound, bool& endWordIsFound, Lexicon& usedWords);
void finalOutput(Vector<string>& currentLadder, string endWord, bool& ladderFound, Queue<Vector<string> >& queue);
bool lastIsEndWord(Vector<string>& currentLadder, string endWord);
void newWordIsFound(string& lastWord, int j, char letter, Lexicon& words, Lexicon& usedWords, Vector<string>& currentLadder, string endWord, Queue<Vector<string> >& queue, bool& endWordIsFound);
void ladderIsNotFound(bool ladderFound);

// This function generates the word ladder problem.

int main() {
	wordLadder();
	return 0;
}

// The job of this function is to initialise elements, ask the user for input and 
// display a word ladder if there is one.

int wordLadder(){
		while(true){
		Lexicon words("EnglishWords.dat");
		Lexicon usedWords;
		Vector<string> ladder;
		Queue<Vector<string> > queue;
		bool ladderFound = false;
		bool endWordIsFound = false;
		string startWord = getLine("Enter the starting word (or nothing to quit): "); 
		if(userWantsToQuit(startWord)) return 0;
		string endWord = getLine("Enter the ending word: ");
		initialPhase(startWord, endWord, ladder, queue);
		findingTheLadder(queue, words, startWord, endWord, ladderFound, endWordIsFound, usedWords);
		ladderIsNotFound(ladderFound);
	}
}

// This code deals with the situation when the user wants to quit the program.

bool userWantsToQuit(string startWord){
	if(startWord == ""){
		cout << "Goodbye!" << endl;
		return true;
	} else {
		return false;
	}
}

// The job of this code is to prepare the program beforehand. 

void initialPhase(string& startWord, string& endWord, Vector<string>& ladder, Queue<Vector<string> >& queue){
	startWord = toLowerCase(startWord);
	endWord = toLowerCase(endWord);
	cout << "Searching..." << endl;
	ladder.add(startWord);
	queue.enqueue(ladder);
}

// The job of this code is to find the word ladder. 

void findingTheLadder(Queue<Vector<string> >& queue, Lexicon& words, string startWord, string endWord, bool& ladderFound, bool& endWordIsFound, Lexicon& usedWords){
	while(!queue.isEmpty() && words.contains(startWord) && words.contains(endWord)){
		Vector<string> currentLadder = queue.dequeue();
		finalOutput(currentLadder, endWord, ladderFound, queue);
		string lastWord = currentLadder.get(currentLadder.size() - 1);
		if(!endWordIsFound){ 
			for(int j = 0; j < lastWord.length(); j++){
				for(char letter = 'a'; letter <= 'z'; letter++){
					newWordIsFound(lastWord, j, letter, words, usedWords, currentLadder, endWord, queue, endWordIsFound);
				}
			}
		} 
	}
}

// The job of this code is to display a proper message to the user whenever
// the word ladder is found.

void finalOutput(Vector<string>& currentLadder, string endWord, bool& ladderFound, Queue<Vector<string> >& queue){
	if(lastIsEndWord(currentLadder, endWord)){
		cout << "Ladder found: ";
		foreach (string ladderWord in currentLadder){
			if(ladderWord == endWord){
				ladderFound = true;
				cout << endWord << endl;
				cout << endl;
				queue.clear();
			} else {
				cout << ladderWord << " -> ";
			}
		}
	}
}

// The job of this code is to check whether the last word of the
// ladder is the same as the destination (ending) word.

bool lastIsEndWord(Vector<string>& currentLadder, string endWord){
	string lastWord = currentLadder.get(currentLadder.size() - 1);
	if(lastWord == endWord){
		return true;
	} else {
		return false;
	}
}


// The job of this code is to find new words and add them to the current
// ladder. A word will be added to a ladder if it is legal (found in the
// english words' lexicon) and has not been used in a ladder yet.

void newWordIsFound(string& lastWord, int j, char letter, Lexicon& words, Lexicon& usedWords, Vector<string>& currentLadder, string endWord, Queue<Vector<string> >& queue, bool& endWordIsFound){
	if(lastWord[j] != letter){
		string newWord = lastWord;
		newWord[j] = letter;
		if(words.contains(newWord) && !usedWords.contains(newWord)){
			usedWords.add(newWord);
			Vector<string> newLadder = currentLadder;
			newLadder += newWord;
			if(newWord == endWord) endWordIsFound = true; 
			queue.enqueue(newLadder);
		}
	}
}

// This code outputs a message that tells the user that a word ladder
// was not found.

void ladderIsNotFound(bool ladderFound){
	if(!ladderFound){
		cout << "No word ladder could be found." << endl;
		cout << endl;
	}
}








