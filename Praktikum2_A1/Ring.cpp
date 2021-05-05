/*************************************************
* ADS Praktikum 2.1
* Ring.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
// Ring .cpp
#include "Ring.h"
#include <iostream>

Ring::Ring() {}

void Ring::addNewNode(std::string description, std::string data) {
	RingNode* newNode = new RingNode(0, description, data);
	if (anker == nullptr) //falls noch keine Elemente vorhanden
	{
		anker = newNode;
		newNode->setNext(newNode);
		countNodes = 1;
		
	}
	else if (anker->getNext() == nullptr) //falls nur ein Element vorhanden
	{
		anker->setNext(newNode);
		newNode->setNext(anker);
		anker = newNode;
		countNodes++;
		updateAge();
	}
	else if (countNodes < 6) //falls mehrere Elemente unter 6 vorhanden
	{
		newNode->setNext(anker->getNext());
		anker->setNext(newNode);
		anker = newNode;
		countNodes++;
		updateAge();
	}
	else //falls Ring voll ist
	{
		
		newNode->setNext(anker->getNext()->getNext());
		delete anker->getNext();
		anker->setNext(newNode);
		anker = newNode;
		countNodes = 6;
		updateAge();
	}
}

void Ring::updateAge() {
	RingNode* ptr1;
	ptr1 = anker->getNext();
	int age = countNodes-1;
	do
	{
		ptr1->setAge(age);
		age--;
		ptr1 = ptr1->getNext();
	} while (ptr1 != anker);
}

bool Ring::search(std::string data) {
	RingNode* ptr1;
	ptr1 = anker;
	do
	{
		if (ptr1->getData() == data)
		{
			return true;
		}
		ptr1 = ptr1->getNext();
	} while (ptr1 != anker);
	return false;
}

RingNode* Ring::getNode(std::string data) {
	RingNode* ptr1;
	ptr1 = anker;
	do
	{
		if (ptr1->getData() == data)
		{
			return ptr1;
		}
		ptr1 = ptr1->getNext();
	} while (ptr1 != anker);
	return ptr1 = nullptr;
}

void Ring::print() {
	int count = 0;
	RingNode* ptr1;
	ptr1 = anker;
	while (count < countNodes)
	{
		do
		{
			if (ptr1->getAge() == count)
			{
				std::cout << "Alter: " << ptr1->getAge() << ", Beschreibung: " << ptr1->getDescription() << ", Daten: " << ptr1->getData() << std::endl;
				if (count != countNodes-1)
				{
					std::cout << "--------------------------" << std::endl;
				}
				count++;
			}
			ptr1 = ptr1->getNext();
			if (countNodes == 1)
			{
				break;
			}
		} while (ptr1 != anker);
		ptr1 = anker;
	}
}