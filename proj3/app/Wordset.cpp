#include "Wordset.hpp"
#include <string>
#include <iostream>
const int BASE_TO_USE = 41; 
const double LOAD_LIMIT = 0.27;
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
		unsigned pow = 1;
		for(unsigned j = 0; j<power; ++j){
			pow*=base;
		}
		total+=(digit*pow);
		
		power++;
	}
	return total%mod; 
}

WordSet::WordSet():
	table{new Entry[SIZES[0]]},
	sizeIndex{0},
	numItems{0}
{
	initTable();
}


void WordSet::initTable(){
	for(unsigned i = 0; i<SIZES[sizeIndex]; ++i){
		table[i].status = 0;
		table[i].key = "";
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
	unsigned i = 0;
	while(i<SIZES[sizeIndex]){
		if(table[index].status == 0){
			Entry newEntry = {s, 1};
			table[index] = newEntry;
			numItems++;
			break;
		}
		//increment i and recompute index
		i++;
		index = (hash+(i*i))%SIZES[sizeIndex];
	}
	if(1.0*numItems/getCapacity()>LOAD_LIMIT){
		rehash();
	}
}

void WordSet::rehash(){
	int previousCapacity = getCapacity();
	sizeIndex++;
	numItems = 0;

	Entry* previousTable = table;//save to delete later
	table = new Entry[SIZES[sizeIndex]]();//init new array with new size
	initTable();
	for(int i = 0; i<previousCapacity; ++i){
		if(previousTable[i].status!=0){
			insert(previousTable[i].key);
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
		if(table[index].status!=0 && table[index].key == s){
			return true;
		}
		//increment i and recompute index
		i++;
		index = (hash+(i*i))%SIZES[sizeIndex];
		//increment number of indexes probed
		numProbed++;
	}
	return false;  
}

// return how many distinct strings are in the set
int WordSet::getCount() const
{
	return numItems; 
}

// return how large the underlying array is.
int WordSet::getCapacity() const
{
	return SIZES[sizeIndex]; 
}

