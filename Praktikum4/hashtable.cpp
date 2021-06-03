#include "hashtable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int size) {
	hashTable = new vector<int>;
	hashTable->resize(size);
	for (int i = 0; i < size; i++)
	{
		hashTable->at(i) = -1;
	}
	this->size = size;
	this->elements = 0;
	this->collisionCount = 0;
}

HashTable::~HashTable()
{
	delete hashTable;
}

int HashTable::hashValue(int item) {

	int index = -1;
	int i = 0;
	while (true)
	{
		index = ((item + i * i) % getSize());
		if (hashTable->at(index) != -1)
		{
			collisionCount++;
			i++;
		}
		else
		{
			return index;
		}
	}
}

int HashTable::insert(int item) {
	
	int index = hashValue(item);
	hashTable->at(index) = item;
	elements++;
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
