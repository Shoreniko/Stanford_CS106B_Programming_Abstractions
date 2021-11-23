/* 
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: Shorena Janjghava.
 * Section: Nikoloz Adeishvili.
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 */

#include <iostream>
#include <string>
#include "console.h"
#include "set.h"
#include "vector.h"
#include "simpio.h"
#include "foreach.h"
using namespace std;

/* Function prototype declarations. */

void generateCities(Set<string>& cities);
void generateHospitals(Vector< Set<string> >& locations, int numOfAllHospitals);
bool canOfferUniversalCoverage(Set<string>& cities, Vector< Set<string> >& locations, int numHospitals, Vector< Set<string> >& result);

/* The job of this function is to:
	- generate information about cities, hospitals and the cities that 
	they can cover.
	- show whether it is possible to cover all cities with limited
	amount of hospitals.
	- output one possible solution if it exists. */

int main() {

	/* Variable declarations. */

	Set<string> cities;
	Vector< Set<string> > locations;
	Vector< Set<string> > result;
	
	/* The process of generating information. */ 

	generateCities(cities);
	int numOfAllHospitals = getInteger("Number of all hospitals: ");
	generateHospitals(locations, numOfAllHospitals);
	int numHospitals = getInteger("Enter the number of hospitals to build: ");

	/* The process of generating a solution if there is one. */ 
	
	if(numHospitals > 0 && numHospitals <= numOfAllHospitals && canOfferUniversalCoverage(cities, locations, numHospitals, result)){
		cout << "Buildable. One possible solution: " << endl;
		cout << result << endl;
	} else {
		cout << "Not buildable." << endl;
	} 
	
    return 0;
}

/* The job of this function is to generate all cities by asking 
   the user for their names. */

void generateCities(Set<string>& cities){
	cout << "Enter the names of all the cities. Type 0 to stop." << endl;
	string cityNames = getLine("? ");
	while(cityNames != "0"){
		cities += cityNames;
		cityNames = getLine("? ");
	}
}

/* The job of this function is to generate all hospital values
   by asking the user which cities does each hospital cover. */

void generateHospitals(Vector< Set<string> >& locations, int numOfAllHospitals){
	Set<string> hospital;
	for(int i = 0; i < numOfAllHospitals; i++){
		cout << "Enter cities hospital " << i + 1 << " can cover. Type 0 to stop." << endl;
		string hospitalCity = getLine("? ");
		while(hospitalCity != "0"){
			hospital += hospitalCity;
			hospitalCity = getLine("? ");
		}
		locations.add(hospital);
		hospital.clear();
	}
}

/* This recursive function finds out whether it is possible to cover
   all cities by building given amount of hospitals or not. If there is
   is a solution then the result gets updated. */

bool canOfferUniversalCoverage(Set<string>& cities, Vector< Set<string> >& locations, int numHospitals, Vector< Set<string> >& result){
	
	/* Base case */

	if(numHospitals == 1){
		foreach (Set<string> oneHospital in locations){
			result += oneHospital;
			Set<string> allCoverableCities;
			for(int j = 0; j < result.size(); j++){
				allCoverableCities += result[j];
			}
			if(allCoverableCities == cities){
				return true;
			} else {
				result.remove(result.size() - 1);
				allCoverableCities.clear();
			}
		}
	} 
	
	/* Recursive case */

	else {
		int numOfCombinations = locations.size() - numHospitals + 1;
		for(int i = 0; i < numOfCombinations; i++){
			result += locations[i];
			locations.remove(i);
			bool control = canOfferUniversalCoverage(cities, locations, numHospitals - 1, result);
			if(control) return true;
			locations.insert(0, result[result.size() - 1]);
			result.remove(result.size() - 1);
		}
	}
	return false;
}