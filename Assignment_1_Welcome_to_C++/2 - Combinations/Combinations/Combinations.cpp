/*
 * File: Combinations.cpp
 * ----------------------
 * Name: Shorena Janjghava.
 * This file is the starter project for the Combinations problem.
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

// Function prototype declarations.

void outputMessage(int n, int k);
int combinations(int n, int k);

// The job of this function is to calculate the mathematical combinations
// function for integers n and k with values entered by the user.

int main() {
	int n = getInteger("n = ");
	int k = getInteger("k = ");
	outputMessage(n, k);
    return 0;
}

// This code displays the final message to the user.

void outputMessage(int n, int k){
	cout << "c(" << n << ", " << k << ") = " << combinations(n, k) << endl;
}

// This recursive function calculates the mathematical combinations
// function c(n, k).

int combinations(int n, int k){
	if(n == k || k == 0){
		return 1;
	} else {
		return combinations(n - 1, k - 1) + combinations(n - 1, k); 
	}
}

