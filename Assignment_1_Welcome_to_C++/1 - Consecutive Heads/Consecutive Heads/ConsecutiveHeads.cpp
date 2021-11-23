/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: Shorena Janjghava.
 * This file is the starter project for the Consecutive Heads problem.
 */

#include <iostream>
#include "console.h"
#include "random.h"
using namespace std;

// Function prototype declarations.

void coinFlipSimulation(int& headsCount, int& flipCount);
void heads(int& headsCount, int& flipCount);
void tails(int& headsCount, int& flipCount);
void outputMessage(int flipCount);

// The job of this function is to simulate coin flips, stop after the tosses of 
// three consecutive heads and display the final message to the user. 

int main() {
	int headsCount = 0;
	int flipCount = 0;
	coinFlipSimulation(headsCount, flipCount);
	outputMessage(flipCount);
    return 0;
}

// This function simulates coin flips until three consecutive
// heads are tossed.

void coinFlipSimulation(int& headsCount, int& flipCount){
	while(headsCount != 3){
		if(randomChance(0.50)){
			heads(headsCount, flipCount);
		} else {
			tails(headsCount, flipCount);
		}
	}
}

// This function is called when heads are tossed.

void heads(int& headsCount, int& flipCount){
	cout << "heads" << endl;
	headsCount++;
	flipCount++;
}

// This function is called when tails are tossed.

void tails(int& headsCount, int& flipCount){
	cout << "tails" << endl;
	headsCount = 0;
	flipCount++;
}

// This function prints out a message informing the user how many flips
// it took to get three consecutive heads.

void outputMessage(int flipCount){
	cout << "It took " << flipCount << " flips to get 3 consecutive heads." << endl;
}