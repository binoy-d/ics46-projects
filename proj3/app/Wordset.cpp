#include "Wordset.hpp"
#include <string>
#include <cmath>
#include <iostream>
const int BASE_TO_USE = 41; 
const double LOAD_LIMIT = 0.27;
const std::string EMPTY = "*";

// returns s, as a number in the given base, mod the given modulus
int hashFunction(std::string s, int base, int mod)
{
	if(s.length() == 0){
		return 0;
	}
	unsigned total = 0;
	unsigned power = 0;
	for(int i = s.length()-1; i>=0; i--){
		int digit = s[i]-'a';
		total+=(digit*pow(base, power));
		power++;
	}
	return total%mod; 
}


WordSet::WordSet():
	table{new std::string[SIZES[0]]},
	sizeIndex{0},
	numItems{0}
{
	for(unsigned i = 0; i<SIZES[0]; ++i){
		table[i] = EMPTY;
	}

}

WordSet::~WordSet()
{
	delete[] table;
}

void WordSet::insert(std::string s)
{
	int hash = hashFunction(s, BASE_TO_USE, SIZES[sizeIndex]);
	int index = hash;

	//taken straight from zybooks
	unsigned numProbed = 0;
	unsigned i = 0;
	while(numProbed<SIZES[sizeIndex]){
		if(isEmptyAt(index)){
			table[index] = s;
			numItems++;
			break;
		}
		//increment i and recompute index
		i++;
		index = (hash+(i*i))%SIZES[sizeIndex];
		//increment number of indexes probed
		numProbed++;
	}
	if(getLoadFactor()>LOAD_LIMIT){
		reHash();
	}
	
}

void WordSet::reHash(){
	unsigned previousCapacity = getCapacity();
	sizeIndex++;
	numItems = 0;

	std::string* previousTable = table;//save to delete later
	table = new std::string[getCapacity()];//init new array with new size

	for(unsigned i = 0; i<getCapacity(); ++i){
		table[i] = EMPTY;
	}
	for(unsigned i = 0; i<previousCapacity; ++i){
		if(previousTable[i]!=EMPTY){
			insert(previousTable[i]);
		}
	}
	delete[] previousTable;
}

bool WordSet::contains(std::string s) const
{
	int hash = hashFunction(s, BASE_TO_USE, SIZES[sizeIndex]);
	int index = hash;

	//taken straight from zybooks
	unsigned numProbed = 0;
	unsigned i = 0;
	while(numProbed<SIZES[sizeIndex]){
		if(table[index] == s){
			return true;
		}
		//increment i and recompute index
		i++;
		index = (hash+(i*i))%SIZES[sizeIndex];
		//increment number of indexes probed
		numProbed++;
	}
	return false;  // stub, not correct.
}

// return how many distinct strings are in the set
int WordSet::getCount() const
{
	return numItems; // this is not the right answer. 
}

// return how large the underlying array is.
int WordSet::getCapacity() const
{
	return SIZES[sizeIndex]; 
}



//PRIVATE MEMBER FUNCTIONS


double WordSet::getLoadFactor() const{
	return 1.0*numItems/getCapacity();
}



bool WordSet::isEmptyAt(unsigned index) const{
	return table[index]==EMPTY;
}