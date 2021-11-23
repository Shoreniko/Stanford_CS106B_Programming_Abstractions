/*
 * File: RandomSubsets.cpp
 * ----------------------
 * Name: Shorena Janjghava.
 * Section: Nikoloz Adeishvili.
 * This file is the starter project for the Random Subsets problem
 * on Assignment #3.
 */

#include <iostream>
#include "set.h"
#include "random.h"
#include "console.h"
#include "simpio.h"
using namespace std;

// Function prototype declaration.

Set<int> randomSubsetOf(Set<int>& s);

// Constant variable declaration.

const int SENTINEL = -1;

/* This function inputs elements of a set from the user and 
   outputs one random subset of that set. */

int main() {

	/* Variable declaration. */ 

	Set<int> s;

	/* Create a set of elements inputed by the user. */ 

	cout << "Enter the elements of a set. Input " << SENTINEL << " to stop." << endl;

	int element = getInteger("? ");

	while(element != SENTINEL){
		s.add(element);
		element = getInteger("? ");
	}

	/* Output one random subset of a given set. */ 

	cout << "One random subset of your set looks like this: " << endl;
	s = randomSubsetOf(s);
	cout << s << endl;

    return 0;
}

/* This recursive function generates one random subset of a
   given set. */ 

Set<int> randomSubsetOf(Set<int>& s){

	/* Base case. */ 
	
	if(s.isEmpty()) return s;

	if(s.size() == 1){
		if(randomChance(0.5)){
			return s;
		} else {
			s.remove(s.first());
			return s;
		}
	} 
	
	/* Recursive case. */ 
	
	else {
		return randomSubsetOf(s - (s - s.first())) + randomSubsetOf(s - s.first());
	}
} 