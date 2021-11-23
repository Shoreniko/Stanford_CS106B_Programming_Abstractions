/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: Shorena Janjghava.
 * Section: Nikoloz Adeishvili.
 * This file is the starter project for the Random Writer problem
 */

#include <iostream>
#include <fstream>
#include "filelib.h"
#include "simpio.h"
#include "console.h"
#include "vector.h"
#include "map.h"
#include "foreach.h"
#include "set.h"
#include "random.h"
using namespace std;

// Function prototype declarations.

void valueIsOutOfRange(int markovOrder);
void saveFileData(ifstream& input, Vector<char>& fullText);
bool orderGreaterThanText(Vector<char>& fullText, int markovOrder);
void analyzeText(Vector<char>& fullText, int markovOrder, Map<string, Vector<char> >& theSequences);
string findMostFrequentSeed(Map<string, Vector<char> >& theSequences);
void generateRandomText(string theSeed, Map<string, Vector<char> >& theSequences, int markovOrder);

// Constant variable.

const int RANDOM_TEXT_LENGTH = 2000;

// This code initialises certain elements, reads in information
// inputed by the user, analyses that information and generates
// a random text.

int main() {
	ifstream input;
	string fileName = promptUserForFile(input, "Enter the source text: ");
	int markovOrder = getInteger("Enter the Markov order [1-10]: ");
	valueIsOutOfRange(markovOrder);
	cout << "Processing file..." << endl;
	Map<string, Vector<char> > theSequences;
	Vector<char> fullText;
	saveFileData(input, fullText);
	if(orderGreaterThanText(fullText, markovOrder)) return 0; 
	analyzeText(fullText, markovOrder, theSequences);
	string theSeed = findMostFrequentSeed(theSequences);
	generateRandomText(theSeed, theSequences, markovOrder);
    return 0;
}

// This code deals with the situation when the Markov number entered
// by the user is out of range.

void valueIsOutOfRange(int markovOrder){
	while(markovOrder < 1 || markovOrder > 10){
		cout << "That value is out of range." << endl;
		markovOrder = getInteger("Enter the Markov order [1-10]: ");
	}
}

// The job of this function is to save data from the file indicated by
// the user.

void saveFileData(ifstream& input, Vector<char>& fullText){
	char oneChar;
	while(input.get(oneChar)){
		fullText.add(oneChar);
	}
}

// This function checks whether the Markov number is greater than the
// file text data or not.

bool orderGreaterThanText(Vector<char>& fullText, int markovOrder){
	if(fullText.size() < markovOrder){
		cout << "" << endl;
		return true;
	} else {
		return false;
	}
}

// The job of this function is to analyze the text by counting special
// properties. 

void analyzeText(Vector<char>& fullText, int markovOrder, Map<string, Vector<char> >& theSequences){
	string oneSequence;
	for(int i = 0; i < fullText.size() - markovOrder; i++){
		for(int j = 0; j < markovOrder; j++){
			oneSequence += fullText[i + j];
		}
		if(oneSequence.length() == markovOrder){
			char followingChar = fullText[i + markovOrder];
			theSequences[oneSequence].add(followingChar);
			oneSequence = "";
		}
	}
}

// The job of this function is to find the most frequent seed
// in the file text.

string findMostFrequentSeed(Map<string, Vector<char> >& theSequences){
	string longestSeed = "";
	foreach(string seedKey in theSequences){
		if(theSequences[longestSeed].size() < theSequences[seedKey].size()){
			longestSeed = seedKey;
		} 
	} 
	return longestSeed;
}

// The job of this function is to generate the random text. 

void generateRandomText(string theSeed, Map<string, Vector<char> >& theSequences, int markovOrder){
	string output = theSeed;
	while(output.length() != RANDOM_TEXT_LENGTH){
		if(theSequences.containsKey(output.substr(output.length() - markovOrder))){
			string key = output.substr(output.length() - markovOrder);
			int maxIndex = theSequences[key].size();
			char nextRandomChar = theSequences.get(key)[randomInteger(0, maxIndex - 1)];
			output += nextRandomChar;
		} else {
			cout << output << endl;
			break;
		}
	}
	cout << output << endl;
}