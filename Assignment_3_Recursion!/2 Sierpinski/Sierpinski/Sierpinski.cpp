/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: Shorena Janjghava. 
 * Section: Nikoloz Adeishvili. 
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 */

#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "gtypes.h"
#include "simpio.h"
using namespace std;

/* Function prototype declaration. */ 

void drawSierpinskiTriangle(GWindow& gw, int length, int order, GPoint origin); 

/* Constant variable declaration. */ 

/* This constant variable is used for calculating the altitude of
   an equilateral triangle. */ 

const double ALTITUDE_COEFFICIENT = sqrt(3.0) * 0.5; 

/* This function inputs information from user and outputs 
   proper Sierpinski triagle. */ 

int main() {

	/* Variable declaration. */ 

    GWindow gw;
	gw.setVisible(true);

	/* Gather information from the user. */ 

	int length = getInteger("Length: ");
	while(length < 0){
		length = getInteger("Length: ");
	}
	int order = getInteger("Order: ");
	while(order < 0){
		order = getInteger("Order: ");
	}

	/* Calculate triangle properties. */ 

	double altitude = ALTITUDE_COEFFICIENT * length;
	GPoint origin((gw.getWidth() - length) / 2, gw.getHeight() - (gw.getHeight() - altitude) / 2);

	/* Draw the Sierpinski triangle. */ 

	drawSierpinskiTriangle(gw, length, order, origin);

    return 0;
}

/* This recursive function draws the sierpinski triangle according
   to user-given properties. */ 

void drawSierpinskiTriangle(GWindow& gw, int length, int order, GPoint origin){

	/* Base case. */ 

	if(order == 0){
		GPoint secondPos = gw.drawPolarLine(origin, length, 60);
		GPoint thirdPos = gw.drawPolarLine(secondPos, length, 300);
		gw.drawPolarLine(thirdPos, length, 180);
	} 
	
	/* Recursive case. */ 
	
	else {
		for(int i = 0; i < 3; i++){
			if(i == 0){
				drawSierpinskiTriangle(gw, length / 2, order - 1, origin);
			} else if(i == 1){
				double altitude = ALTITUDE_COEFFICIENT * (length / 2);
				GPoint secondOrigin(origin.getX() + length / 4, origin.getY() - altitude);
				drawSierpinskiTriangle(gw, length / 2, order - 1, secondOrigin);
			} else if(i == 2){
				GPoint thirdOrigin(origin.getX() + length / 2, origin.getY());
				drawSierpinskiTriangle(gw, length / 2, order - 1, thirdOrigin);
			} 
		}
	}
}

