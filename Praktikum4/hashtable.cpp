#include "hashtable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int size) {
	
	//*****************************
	// implement constructor here *
	//*****************************

}

HashTable::~HashTable()
{
	//****************************
	// implement destructor here *
	//****************************
}

int HashTable::hashValue(int item) {
	
	int index = -1; //dummy initializtation

	//******************************************
	// implement calculation of hashindex here *
	//******************************************

	return index;
}

int HashTable::insert(int item) {
	
	//******************************************
	// implement insertion of new element here *
	//******************************************

	return 0; //dummy return
}


int HashTable::at(int i) {
	return hashTable->at(i);
}

int HashTable::getCollisionCount() {
	return this->collisionCount;
}

int HashTable::getSize() {
	return this->size;
}

int HashTable::getElements() {
	return this->elements;
}
