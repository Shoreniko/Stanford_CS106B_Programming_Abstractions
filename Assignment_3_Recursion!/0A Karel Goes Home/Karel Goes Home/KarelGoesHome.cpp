/*
 * File: KarelGoesHome.cpp
 * ----------------------
 * Name: Shorena Janjghava.
 * Section: Nikoloz Adeishvili.
 * This file is the starter project for the Karel Goes Home
 * warmup problem for Assignment #3.
 */

/* This solution works faster and in greater numbers than the
   original solution (thanks to one simple tweak at line 40). */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function prototype declaration. */

int numPathsHome(int street, int avenue);

/* This function inputs street and avenue numbers from the user and 
   outputs the number of shortest paths available from the specific
   position to the origin. */

int main() {
	int street = getInteger("Enter street number: ");
	int avenue = getInteger("Enter avenue number: ");
	cout << "The number of shortest paths is: " << numPathsHome(street, avenue) << endl;
    return 0;
}

/* This recursive function calculates the number of short paths available
   from the specific position to the origin. */

int numPathsHome(int street, int avenue){
	if(street < 1 || avenue < 1){
		return 0;
	}
	if(street == 1 || avenue == 1){
		return 1;
	} else {
		return numPathsHome(street - 1, avenue) + numPathsHome(street, avenue - 1);
	}
} 