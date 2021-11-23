/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

/* This function constructs a new dynamic array. */ 
HeapPriorityQueue::HeapPriorityQueue() {
	arraySize = 1;
	pointer = new string[arraySize];
}

/* This function destructs allocated memory. */ 
HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] pointer;
}

/* This function returns the number of elements in the priority queue. */ 
int HeapPriorityQueue::size() {
	int theSize = 0;
	for(int i = 0; i < arraySize; i++){
		if(pointer[i] != ""){
			theSize++;
		} else {
			break;
		}
	} 
	return theSize;
}

/* This function tells whether the priority queue is empty or not. */ 
bool HeapPriorityQueue::isEmpty() {
	if(pointer[0] == "") return true;
	return false;
}

/* This function adds a new value to the priority queue. */
void HeapPriorityQueue::enqueue(string value) {
	if(pointer[0] == "") arraySize = 1;
	/* Variable declarations. */ 
	int newValueIndex = 0;
	int lastStop = 0;
	bool newValueWasPlaced = false;
	int nearLastElementPosition = arraySize / 2 - 2;
	/* This chunk of code tries to add a new value to the queue. */ 
	for(int i = nearLastElementPosition; i < arraySize; i++){
		if(pointer[i] == ""){
			pointer[i] = value;
			newValueIndex = i;
			newValueWasPlaced = true;
			break;
		}
	} 
	/* If the queue appears to be full, this chunk of code increases its size and
	   adds the new element (This time successfully). */ 
	lastStop = arraySize;
	if(!newValueWasPlaced){
		increaseSize();
		pointer[lastStop] = value;
		newValueIndex = lastStop;
	}
	/* This chunk of code executes the bubble-up steps. */ 
	if(((newValueIndex + 1) / 2 - 1) < arraySize && ((newValueIndex + 1) / 2 - 1) >= 0){
		while(pointer[(newValueIndex + 1) / 2 - 1] > pointer[newValueIndex]){
			string temproraryValue = pointer[(newValueIndex + 1) / 2 - 1];
			pointer[(newValueIndex + 1) / 2 - 1] = pointer[newValueIndex];
			pointer[newValueIndex] = temproraryValue;
			newValueIndex = (newValueIndex + 1) / 2 - 1;
			if(!(((newValueIndex + 1) / 2 - 1) < arraySize && ((newValueIndex + 1) / 2 - 1) >= 0)) break;
		}
	}
}

/* If the priority queue is empty, this function files an error. Otherwise, 
   it returns the lexicographically first element of the priority queue. */ 
string HeapPriorityQueue::peek() {
	if(pointer[0] == ""){
		error("Unable to perform your command, because the Priority Queue is empty.");
		return "";
	} 
	string lexicographicallyFirst = pointer[0];
	return lexicographicallyFirst;
}

/* If the priority queue is empty, this function files an error. Otherwise, 
   it removes the lexicographically first element from the queue and returns it. */ 
string HeapPriorityQueue::dequeueMin() {
	/* If the priority queue is empty, files an error. */ 
	if(pointer[0] == ""){
		error("Unable to perform your command, because the Priority Queue is empty.");
		return "";
	} 
	/* If the priority queue is not empty, removes and returns lexicographically first 
	   element from the queue. */ 
	string lexicographicallyFirst = pointer[0];
	int lastNodeIndex = -1;
	/* This chunk of code tries to find the last value index in the queue. */ 
	for(int i = 0; i < arraySize; i++){
		if(pointer[i] == ""){
			lastNodeIndex = i - 1;
			break;
		}
	}
	/* If the code fails to find a last value, the size of the queue gets increased. */ 
	int lastStop = arraySize;
	if(lastNodeIndex == -1){
		increaseSize(); 
		lastNodeIndex = lastStop - 1;
	}  
	/* The last value is put on the first index position in the queue. */ 
	pointer[0] = pointer[lastNodeIndex];
	pointer[lastNodeIndex] = "";
	/* Variable declarations for the bubble-down steps. */
	int bubbleDownIndex = 0;
	int firstChild = (bubbleDownIndex + 1) * 2 - 1;
	int secondChild = (bubbleDownIndex + 1) * 2;
	string temproraryValue;
	bool control = false;
	/* This chunk of code deals with carrying out the bubble-down steps. */ 
	while(pointer[firstChild] != "" && pointer[bubbleDownIndex] > pointer[firstChild] ||
		pointer[secondChild] != "" && pointer[bubbleDownIndex] > pointer[secondChild]){
		if(pointer[firstChild] != "" && pointer[secondChild] != "" && pointer[secondChild] <= pointer[firstChild]){
			swapParentAndChild(pointer, secondChild, bubbleDownIndex);
		} else {
			swapParentAndChild(pointer, firstChild, bubbleDownIndex);
		}
		if(((bubbleDownIndex + 1) * 2) < arraySize){
			firstChild = (bubbleDownIndex + 1) * 2 - 1;
			secondChild = (bubbleDownIndex + 1) * 2;
			control = true;
		} 
		if(control){
			control = false;	
		} else {
			break;
		}
	} 
	return lexicographicallyFirst;
} 

/* This function increases the size of the dynamic array. */ 
void HeapPriorityQueue::increaseSize(){
	int expandedSize = (arraySize + 1) * 2;
	string* newPointer = new string[expandedSize]; 
	for(int i = 0; i < arraySize; i++){
		newPointer[i] = pointer[i];
	}
	pointer = new string[expandedSize];
	for(int i = 0; i < arraySize; i++){
		pointer[i] = newPointer[i];
	}
	arraySize = expandedSize;
	delete[] newPointer;
}

/* This function swaps the positions of the Parent node and the Child node. */ 
void HeapPriorityQueue::swapParentAndChild(string* &pointer, int childIndex, int& bubbleDownIndex){
	string temproraryValue = pointer[bubbleDownIndex];
	pointer[bubbleDownIndex] = pointer[childIndex];
	pointer[childIndex] = temproraryValue;
	bubbleDownIndex = childIndex; 
} 