/*************************************************
* ADS Praktikum 2.1
* RingNode.h
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#pragma once
#include <string>

class RingNode{
	
private:
	int oldAge;
	std::string description;
	std::string data;
	RingNode* next;


public:
	RingNode();
	RingNode(int oldAge, std::string description, std::string data);
	int getAge();
	void setAge(int age);
	std::string getDescription();
	void setDescription(std::string description);
	std::string getData();
	void setData(std::string data);
	RingNode* getNext();
	void setNext(RingNode* next);
	
};
