/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

/* This function constructs a new vector. */ 
VectorPriorityQueue::VectorPriorityQueue() {
	Vector<string> priorityQueue;
}

/* The destructor function is empty since ~Vector() exists. */ 
VectorPriorityQueue::~VectorPriorityQueue() {
	
}

/* This function returns the number of elements in the priority queue. */ 
int VectorPriorityQueue::size() {
	return priorityQueue.size();
}

/* This function tells whether the priority queue is empty or not. */ 
bool VectorPriorityQueue::isEmpty() {
	if(priorityQueue.isEmpty()) return true;
	return false;
}

/* This function adds a new value to the priority queue. */ 
void VectorPriorityQueue::enqueue(string value) {
	priorityQueue.add(value);
}

/* If the priority queue is empty, this function files an error. Otherwise, 
   it returns the lexicographically first element of the priority queue. */ 
string VectorPriorityQueue::peek() {
	if(!priorityQueue.isEmpty()){
		string lexicographicallyFirst = priorityQueue[0];
		/* This chunk of code finds and returns the lexicographically first element. */ 
		for(int i = 0; i < priorityQueue.size(); i++){
			if(priorityQueue[i] < lexicographicallyFirst) lexicographicallyFirst = priorityQueue[i];
		}
		return lexicographicallyFirst;
	} else {
		error("Unable to perform your command, because the Priority Queue is empty.");
	}
	return "";
}

/* If the priority queue is empty, this function files an error. Otherwise, 
   it removes the lexicographically first element from the queue and returns it. */ 
string VectorPriorityQueue::dequeueMin() {
	if(!priorityQueue.isEmpty()){
		int index = 0;
		string lexicographicallyFirst = priorityQueue[0];
		/* This chunk of code finds the lexicographically first element and
		   remembers its index for later deletion. */ 
		for(int i = 0; i < priorityQueue.size(); i++){
			if(priorityQueue[i] < lexicographicallyFirst){
				lexicographicallyFirst = priorityQueue[i];
				index = i;
			}
		}
		/* This chunk of code handles the first element (which also was
		   the lexicographically first element) removal. */ 
		priorityQueue.set(index, priorityQueue[priorityQueue.size() - 1]);
		priorityQueue.remove(priorityQueue.size() - 1);
		return lexicographicallyFirst;
	} else {
		error("Unable to perform your command, because the Priority Queue is empty.");
	}
	return "";
}