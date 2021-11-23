/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: Shorena Janjghava.
 * This file is the starter project for the Flesch-Kincaid problem.
 */

#include <iostream>
#include <fstream> 
#include "console.h"
#include "filelib.h"
#include "tokenscanner.h"
using namespace std;

// Standard constant values for the Flesch­Kincaid grade level formula.

const double C0 = -15.59;
const double C1 = 0.39;
const double C2 = 11.8;

// Function prototype declarations.

void readTheFile(int& numWords, int& numSyllables, int& numSentences);
void countNumerosities(int& numWords, int& numSyllables, int& numSentences, string token);
bool isWord(char symbol);
void countSyllables(int& numSyllables, int& vowelsWithinEachWord, string token);
bool isVowel(char letter);
bool isSentence(char punctuation);
void checkSpecialCase(int& numWords, int& numSentences);
void finalOutput(int numWords, int numSyllables, int numSentences);
double grade(int numWords, int numSyllables, int numSentences);

// This function reads a file and depicts the number of words, sentences and
// syllables in that file and its Flesch­Kincaid grade level.

int main() {
	int numWords = 0;
	int numSyllables = 0;
	int numSentences = 0;
	readTheFile(numWords, numSyllables, numSentences);
	checkSpecialCase(numWords, numSentences);
	finalOutput(numWords, numSyllables, numSentences);
    return 0;
}

// The job of this function is to read a file indicated by the user and
// calculate specific properties.

void readTheFile(int& numWords, int& numSyllables, int& numSentences){
	ifstream input;
		string inputFileName = promptUserForFile(input, "Enter input file name: "); 
		TokenScanner scanner(input);
		scanner.ignoreWhitespace();
		scanner.addWordCharacters("'");
		while (scanner.hasMoreTokens()) {
			string token = scanner.nextToken();
			countNumerosities(numWords, numSyllables, numSentences, token);
		}
		input.close();
}

// The job of this function is to calculate specific properties necessary for
// the Flesch­Kincaid grade level formula.

void countNumerosities(int& numWords, int& numSyllables, int& numSentences, string token){
	if(isWord(token[0])){
				numWords++;
				int vowelsWithinEachWord = 0; 
				countSyllables(numSyllables, vowelsWithinEachWord, token);
	}
	if(isSentence(token[0])) numSentences++;
}

// The job of this function is to detect whether a certain member of the 
// file is a word or not.

bool isWord(char symbol){
	if(symbol >= 'A' && symbol <= 'Z' || symbol >= 'a' && symbol <= 'z'){
		return true;
	} else {
		return false;
	}
}

// The job of this function is to calculate the number of syllables within
// each word.

void countSyllables(int& numSyllables, int& vowelsWithinEachWord, string token){
	for(int j = 0; j < token.length(); j++){ 
		if(j == 0 && isVowel(token[j])){ 
			numSyllables++;
			vowelsWithinEachWord++;
		}
		if(j > 0 && j < token.length() - 1 && isVowel(token[j]) && !isVowel(token[j - 1])){ 
			numSyllables++;
			vowelsWithinEachWord++;
		}
		if(j > 0 && j == token.length() - 1 && isVowel(token[j]) && (vowelsWithinEachWord == 0 || 
		  (token[j] != 'e' && token[j] != 'E' && !isVowel(token[j - 1])))){
			numSyllables++;
		}
		if(j == token.length() - 1 && vowelsWithinEachWord == 0 && !isVowel(token[j])){ 
			numSyllables++;
		}
	}
}

// The job of this function is to detect whether a certain letter
// is a vowel or not.

bool isVowel(char letter){
	if(letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u' || letter == 'y' ||
	   letter == 'A' || letter == 'E' || letter == 'I' || letter == 'O' || letter == 'U' || letter == 'Y'){
		return true;
	} else {
		return false;
	}
}

// The job of this function is to detect whether the given input is
// a sentence or not.

bool isSentence(char punctuation){
	if(punctuation == '!' || punctuation == '.' || punctuation == '?'){
		return true;
	} else {
		return false;
	}
}

// The job of this function is to check the special case when the file does not 
// appear to have any words or sentences in it (to avoid division by zero).

void checkSpecialCase(int& numWords, int& numSentences){
	if(numWords == 0) numWords = 1;
	if(numSentences == 0) numSentences = 1;
}

// The job of this function is to depict the final results to the user.

void finalOutput(int numWords, int numSyllables, int numSentences){
	double gradeLevel = grade(numWords, numSyllables, numSentences);
	cout << "Words: " << numWords << endl;
	cout << "Syllables: " << numSyllables << endl;
	cout << "Sentences: " << numSentences << endl;
	cout << "Grade level: " << gradeLevel << endl;
}

// The job of this method is to calculate the Flesch­Kincaid grade level.

double grade(int numWords, int numSyllables, int numSentences){
	double grade = C0 + C1 * ((double)numWords / numSentences) + C2 * ((double)numSyllables / numWords);
	return grade;
}














				