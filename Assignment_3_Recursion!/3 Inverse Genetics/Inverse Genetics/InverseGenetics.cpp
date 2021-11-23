/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: Shorena Janjghava.
 * Section: Nikoloz Adeishvili.
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 */

#include <iostream>
#include <fstream>
#include "console.h"
#include "set.h"
#include "simpio.h"
using namespace std;

/* Instance variable declaration. */

Vector<string> combination;

/* Function prototype declarations. */

Map<char, Set<string> > loadCodonMap();
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);
void baseCase();
void recursiveCase(string protein, Map<char, Set<string> >& codons);
void removeAminoAcid(string& protein);
void addAminoAcid(string& protein, char currentAminoAcid);

/* This function creates a database for codons, inputs amino acid
   sequence from the user and outputs all possible RNA strands for it. */

int main() {

	/* Create a database for codons. */

    Map<char, Set<string> > codons = loadCodonMap();

	/* Generate and output all possible combinations. */

	string protein = getLine("Enter Protein: ");
	listAllRNAStrandsFor(protein, codons);

    return 0;
}

/* This function creates a database for codons by reading in and
   analyzing a proper file. */ 

Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;
    string codon;
    char protein;
    while (input >> codon >> protein) {
        result[protein] += codon;
    }
    return result;
}

/* This recursive function outputs all possible RNA strands that can
   represent the amino acid sequence inputed by the user. */

void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons){
	if(protein == ""){
		baseCase();
	} else {
		recursiveCase(protein, codons);
	}
}

/* The job of this function is to act as a base case for the
   recursive function. */ 

void baseCase(){
	if(!combination.isEmpty()){
		for(int i = 0; i < combination.size(); i++){
			if(i != combination.size() - 1){
				cout << combination[i];
			} else {
				cout << combination[i] << endl;
			}
		}
	} else {
		cout << endl;
	}
}

/* The job of this function is to act as a recursive case for the
   recursive function. */ 

void recursiveCase(string protein, Map<char, Set<string> >& codons){
	foreach(string str in codons[protein[0]]){
		combination.add(str);
		char currentAminoAcid = protein[0];
		removeAminoAcid(protein);
		listAllRNAStrandsFor(protein, codons);
		combination.remove(combination.size() - 1);
		addAminoAcid(protein, currentAminoAcid);
	} 
}

/* This function removes one amino acid from the protein string. */

void removeAminoAcid(string& protein){
	if(protein.length() == 1){
		protein = "";
	} else {
		protein = protein.substr(1);
	}
}

/* This function adds current amino acid to the protein string. */

void addAminoAcid(string& protein, char currentAminoAcid){
	if(protein == ""){
		protein = currentAminoAcid;
	} else {
		protein = currentAminoAcid + protein;
	}
}