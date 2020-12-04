#ifndef __PROJ5_PRIORITY_QUEUE_HPP
#define __PROJ5_PRIORITY_QUEUE_HPP

#include "runtimeexcept.hpp"
#include <iostream>

const bool DEBUG = false;


class PriorityQueueEmptyException : public RuntimeException 
{
public:
	PriorityQueueEmptyException(const std::string & err) : RuntimeException(err) {}
};




template<typename Object>
class MyPriorityQueue
{
private:
	// fill in private member data here
	std::vector<Object> q; 
	void insertHelper(const Object & elem, unsigned index) ;
	void extractMinHelper(const Object &elem, unsigned index); 
	
public:
	// You also need a constructor and a destructor.
	MyPriorityQueue(){
	}
	
	~MyPriorityQueue(){
	}

 	size_t size() const noexcept;
	bool isEmpty() const noexcept;

	void insert(const Object & elem);


	// Note:  no non-const version of this one.  This is on purpose because
	// the interior contents should not be able to be modified due to the
	// heap property.  This isn't true of all priority queues but 
	// for this project, we will do this.
	// min and extractMin should throw PriorityQueueEmptyException if the queue is empty.
	const Object & min() const; 

	void extractMin(); 

};


template<typename Object>
size_t MyPriorityQueue<Object>::size() const noexcept
{
	return q.size()-1;
}



template<typename Object>
bool MyPriorityQueue<Object>::isEmpty() const noexcept
{
	return q.size() <= 1; 
}

template<typename Object>
void MyPriorityQueue<Object>::insert(const Object & elem) 
{

	
	if(q.size() == 0){
		q.push_back(elem);
		q.push_back(elem);
	}else{
		q.push_back(elem);
	}
	insertHelper(elem, q.size()-1);
}


template<typename Object>
void MyPriorityQueue<Object>::insertHelper(const Object & elem, unsigned index) 
{
	if(index<=1){
		return;
	}
	//fix locally(check if less than parent)
	Object parent = q.at(index/2);
	if(elem<parent){
		//swap
		std::swap(q[index], q[index/2]);
		insertHelper(elem, index/2);
	}else{
		return;
	}
}





template<typename Object>
const Object & MyPriorityQueue<Object>::min() const
{
	if(q.size() <= 1){
		throw PriorityQueueEmptyException("empty");
	}
	return q[1]; 
}



template<typename Object>
void MyPriorityQueue<Object>::extractMin() 
{
	if(q.size() <= 1){
		throw PriorityQueueEmptyException("empty");
	}

	Object elem = q.back(); //get last element
	q.pop_back(); //remove last
	q[1] = elem; //put last in first
	extractMinHelper(elem, 1);//fix
}

template<typename Object>
void MyPriorityQueue<Object>::extractMinHelper(const Object &elem, unsigned index) {
	//get smaller of the children and the position
	if(index*2>=q.size()){
		return;
	}

	Object min = q[index*2];
	unsigned minIndex = index*2;
	if(index*2+1>=q.size()){
		return;
	}
	if(q[index*2+1]<min){
		min = q[index*2+1];
		minIndex = index*2+1;
	}
	// if elem is bigger than a child, swap and attempt at new index
	if(min<elem){
		std::swap(q[index], q[minIndex]);
		extractMinHelper(elem, minIndex);
	}else{
		return ;//if this is already smaller than both chilren, done
	}
}

#endif 
