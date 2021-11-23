/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

/* This function constructs a new pointer. */ 
DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	front = NULL;
}

/* This function destructs allocated memory. */ 
DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
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
int DoublyLinkedListPriorityQueue::size() {
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
bool DoublyLinkedListPriorityQueue::isEmpty() {
	if(front == NULL) return true;
	return false;
}

/* This function adds a new value to the priority queue. */
void DoublyLinkedListPriorityQueue::enqueue(string value) {
	if(front == NULL){
		front = new ListNode(value);
		front->previous = NULL;
		front->next = NULL;
	} else {
		ListNode* current = front;
		while(current->next != NULL){
			current = current->next;
		}
		current->next = new ListNode(value);
		current->next->previous = current;
		current->next->next = NULL;
	}
}

/* If the priority queue is empty, this function files an error. Otherwise, 
   it returns the lexicographically first element of the priority queue. */ 
string DoublyLinkedListPriorityQueue::peek() {
	/* If the priority queue is empty, files an error. */
	if(front == NULL){
		error("Unable to perform your command, because the Priority Queue is empty.");
		return "";
	} 
	/* Pointer declarations. */ 
	ListNode* lexicographicallyFirstPointer = front;
	ListNode* current = front;
	/* This chunk of code finds the lexicographically first element of the queue. */ 
	string lexicographicallyFirst;
	findLexicographicallyFirst(current, lexicographicallyFirst, lexicographicallyFirstPointer);
	return lexicographicallyFirst;
}

/* If the priority queue is empty, this function files an error. Otherwise, 
   it removes the lexicographically first element from the queue and returns it. */ 
string DoublyLinkedListPriorityQueue::dequeueMin() {
	/* If the priority queue is empty, files an error. */
	if(front == NULL){
		error("Unable to perform your command, because the Priority Queue is empty.");
		return "";
	} 
	/* If there is only one ListNode, then this chunk of code will return it and the
	   DLL will have none ListNodes. */ 
	if(front->next == NULL){
		string lexicographicallyFirstPointer = front->data; //
		front = NULL;
		return lexicographicallyFirstPointer; //
	}
	/* Pointer declarations. */ 
	ListNode* lexicographicallyFirstPointer = front;
	ListNode* current = front;
	/* This chunk of code finds the lexicographically first element of the queue. */ 
	string lexicographicallyFirst;
	findLexicographicallyFirst(current, lexicographicallyFirst, lexicographicallyFirstPointer);
	/* This chunk of code handles the removal of the lexicographically first element 
	   from the DLL. */ 
	if(lexicographicallyFirstPointer->previous != NULL){
		lexicographicallyFirstPointer->previous->next = lexicographicallyFirstPointer->next;
	} else {
		front = lexicographicallyFirstPointer->next;
	}
	if(lexicographicallyFirstPointer->next != NULL) lexicographicallyFirstPointer->next->previous = lexicographicallyFirstPointer->previous;
	return lexicographicallyFirst;
}

/* This function finds the lexicographically first element in the priority queue. */ 
void DoublyLinkedListPriorityQueue::findLexicographicallyFirst(ListNode* &current, string& lexicographicallyFirst, ListNode* &lexicographicallyFirstPointer){
	while(current->next != NULL){
		if(lexicographicallyFirstPointer->data > current->data) lexicographicallyFirstPointer = current;
		current = current->next;
	}
	if(lexicographicallyFirstPointer->data > current->data) lexicographicallyFirstPointer = current;
	lexicographicallyFirst = lexicographicallyFirstPointer->data;
}