/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: Shorena Janjghava.
 * Section: Nikoloz Adeishvili.
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function prototype declaration. */ 

bool isSubsequence(string text, string subsequence);

/* The job of this function is to input two strings from
   the user and output whether the second string is a 
   subsequence of the first. */ 

int main() {

	/* Input two strings. */

	string text = getLine("Text: ");
	string subsequence = getLine("Possible subsequence: ");

	/* Find out and ouput if the second string is a subsequence of the first. */ 

	if(isSubsequence(text, subsequence)){
		cout << "Is a subsequence." << endl;
	} else {
		cout << "Is not a subsequence." << endl;
	}

    return 0;
}

/* This recursive function detects whether the second string
   is a subsequence of the first. */ 

bool isSubsequence(string text, string subsequence){

	/* Base case. */ 

	if(text == "" && subsequence != "") return false;
	if(subsequence == ""){
		return true;
	} 
		
	/* Recursive case. */ 

	else {
		if(text[0] == subsequence[0]){
			text = text.substr(1);
			subsequence = subsequence.substr(1);
			return isSubsequence(text, subsequence);
		} else {
			text = text.substr(1);
			return isSubsequence(text, subsequence);
		}
	}
}