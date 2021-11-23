/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: Shorena Janjghava.
 * This file is the starter project for the Numeric Conversions problem.
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

// Function prototype declarations.

string intToString(int intToConvert);
int stringToInt(string stringToConvert);

// This function converts positive and non-positive numbers entered by the user
// from string to an integer format and vice versa and depicts final results.

int main() {
	int intToConvert = getInteger("Enter a number (integer format): ");
	string stringToConvert = getLine("Enter a number (string format): ");
	cout << "Integer to string: " << intToString(intToConvert) << endl;
	cout << "String to integer: " << stringToInt(stringToConvert) << endl;
    return 0;
}

// This recursive function converts positive and non-positive numbers
// from an integer to string format.

string intToString(int intToConvert){ 
	if(intToConvert > -10 && intToConvert < 0){
		return "-" + string() + char(-intToConvert + '0');
	}
	if(intToConvert < 10 && intToConvert >= 0){
		return string() + char(intToConvert + '0');
	} else {
		if(intToConvert < 0){
			return intToString(intToConvert / 10) + intToString(-intToConvert % 10);
		} else {
			return intToString(intToConvert / 10) + intToString(intToConvert % 10);
		}
	}
}

// This recursive function converts positive and non-positive numbers
// from string to an integer format.

int stringToInt(string stringToConvert){
	if(stringToConvert[0] == '-' && stringToConvert.length() == 2){
		return -1 * int(stringToConvert[1] - '0');
	}
	if(stringToConvert.length() == 1){
		return int(stringToConvert[0] - '0');
	}  else {
		if(stringToConvert[0] == '-'){
			return stringToInt(stringToConvert.substr(0, stringToConvert.length() - 1)) * 10 + 
				   -1 * stringToInt(string() + stringToConvert[stringToConvert.length() - 1]);
		} else {
			return stringToInt(stringToConvert.substr(0, stringToConvert.length() - 1)) * 10 + 
				   stringToInt(string() + stringToConvert[stringToConvert.length() - 1]);
		}
	}
}




