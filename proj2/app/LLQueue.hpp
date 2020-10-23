#ifndef __PROJ2_QUEUE_HPP
#define __PROJ2_QUEUE_HPP

#include "runtimeexcept.hpp"
#include <iostream>

class QueueEmptyException : public RuntimeException 
{
public:
	QueueEmptyException(const std::string & err) : RuntimeException(err) {}
};







template<typename Object>
//linked list implementation
class Node{
public:
	Object data;
	Node* next;
};

template<typename Object>
class LLQueue
{
private:
	// fill in private member data here
	size_t sz;
	Node<Object>* head;
	Node<Object>* tail;

public:
	LLQueue();

	//	These are copy constructors and  assignment operators. 
	// These should be "deep copies" -- copy the contents, not just a pointer to the front. 
	LLQueue(const LLQueue & st);
	LLQueue & operator=(const LLQueue & st);
	//destructor
	~LLQueue();

	size_t size() const noexcept;
	bool isEmpty() const noexcept;

	// We have two front() for the same reason the Stack in lecture week 2 had two top() functions.
	// If you do not know why there are two, your FIRST step needs to be to review your notes from that lecture.

	Object & front();
	const Object & front() const;

	void enqueue(const Object & elem);

	// does not return anything.  Just removes. 
	void dequeue();

	void print();
};

// TODO:  Fill in the functions here. 

//constructor
template <typename Object>
LLQueue<Object>::LLQueue(){
	sz = 0;
	head = nullptr;
	tail = nullptr;
}

//size()
template <typename Object>
size_t LLQueue<Object>::size() const noexcept{
	return sz;
}


//isEmpty()

template <typename Object>
bool LLQueue<Object>::isEmpty() const noexcept{
	return head==nullptr;
}

//front()
template <typename Object>
Object & LLQueue<Object>::front(){
	return head->data;
}


//const front()
template <typename Object>
const Object & LLQueue<Object>::front() const{
	return head->data;
}

//enqueue()
template <typename Object>
void LLQueue<Object>::enqueue(const Object & elem){
	sz++;
	//make a new node
	Node<Object>* newNode = new Node<Object>();
	
	//store this element as the data of new node
	newNode->data = elem;

	//since this node is last, its next is null
	newNode->next = nullptr;

	if(head == nullptr){
		//if this is first node
		//both head and tail point to newNode
		head = newNode;
		tail = newNode;
	}else{
		//point tail's next to this
		tail->next = newNode;
		//newNode is now the tail
		tail = newNode;
	}
}

template <typename Object>
void LLQueue<Object>::dequeue(){
	if(head == nullptr){
		throw QueueEmptyException("No elements to dequeue");
	}else{
		Node<Object>* oldhead = head;
		head  = head->next;
		delete oldhead;
		sz--;
	}
}

//destructor
template <typename Object>
LLQueue<Object>::~LLQueue(){
	while(head!=nullptr){
		//store next
		Node<Object>* nextNode = head->next;
		delete head;
		head = nextNode;//push head to next
	}
	//last node left
	delete head;
}



//print() a helper
template <typename Object>
void LLQueue<Object>::print(){
	Node<Object>* current = head;
	while(current!=nullptr){
		std::cout<<current->data<<",";
		current = current->next;
	}
	std::cout<<std::endl;

}

#endif 
