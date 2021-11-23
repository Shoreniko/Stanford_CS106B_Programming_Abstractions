/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

/* This function constructs a new pointer. */ 
LinkedListPriorityQueue::LinkedListPriorityQueue() {
	front = NULL;
}

/* This function destructs allocated memory. */ 
LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	ListNode* trash = front;
	ListNode* current; 
	while(trash != NULL) {
		current = trash->next;
		delete trash;
		trash = current;
	}
	front = NULL;
}

/* This function returns the number of elements in the priority queue. */ 
int LinkedListPriorityQueue::size() {
	int size = 0;
	if(front == NULL){
		return 0;
	} else {
		ListNode* current = front;
		while(current->next != NULL){
			size++;
			current = current->next;
		}
	}
	return size + 1;
}

/* This function tells whether the priority queue is empty or not. */ 
bool LinkedListPriorityQueue::isEmpty() {
	if(front == NULL) return true;
	return false;
}

/* This function adds a new value to the priority queue. */
void LinkedListPriorityQueue::enqueue(string value) {
	if(front == NULL){
		front = new ListNode(value);
	} else {
		/* Pointer declarations. */ 
		ListNode* current = front;
		ListNode* previous = NULL;
		/* This chunk of code enqueues a new value into the queue. */ 
		while(current != NULL){
			if(current->data >= value) break;
			previous = current;
			current = current->next;
		}
		if(previous == NULL){
			front = new ListNode(value);
			front->next = current;
		} else { 
			previous->next = new ListNode(value);
			previous->next->next = current;
		}
	}
}

/* If the priority queue is empty, this function files an error. Otherwise, 
   it returns the lexicographically first element of the priority queue. */ 
string LinkedListPriorityQueue::peek() {
	/* If the priority queue is empty, files an error. */
	if(front == NULL){
		error("Unable to perform your command, because the Priority Queue is empty.");
		return "";
	} 
	return front->data;
}

/* If the priority queue is empty, this function files an error. Otherwise, 
   it removes the lexicographically first element from the queue and returns it. */ 
string LinkedListPriorityQueue::dequeueMin() {
	/* If the priority queue is empty, files an error. */
	if(front == NULL){
		error("Unable to perform your command, because the Priority Queue is empty.");
		return "";
	}
	/* If there is only one ListNode, then this chunk of code will return it and the
	   DLL will have none ListNodes. */ 
	if(front->next == NULL){
		string lexicographicallyFirst = front->data;
		ListNode* trash = front; 
		front = NULL;
		delete trash; 
		return lexicographicallyFirst;
	} 
	/* This chunk of code removes the lexicographically first element from the queue. */ 
	string lexicographicallyFirst = front->data;
	ListNode* trash = front;
	front = front->next;
	delete trash;
	return lexicographicallyFirst;
}