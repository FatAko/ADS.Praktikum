/*************************************************
* ADS Praktikum 2.1
* RingNode.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "RingNode.h"

RingNode::RingNode(int pOldAge, std::string pDescription, std::string pData) : oldAge{ pOldAge }, description{ pDescription }, data{ pData } {};

int RingNode::getAge() {
	return this->oldAge;
}

void RingNode::setAge(int age) {
	this->oldAge = age;
}

std::string RingNode::getDescription() {
	return this->description;
}

void RingNode::setDescription(std::string description) {
	this->description = description;
}

std::string RingNode::getData() {
	return this->data;
}

void RingNode::setData(std::string data) {
	this->data = data;
}

RingNode* RingNode::getNext() {
	return this->next;
}

void RingNode::setNext(RingNode* next) {
	this->next = next;
}