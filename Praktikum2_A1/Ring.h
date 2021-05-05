/*************************************************
* ADS Praktikum 2.1
* Ring.h
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
// Ring .h
#pragma once
#include<string>
#include "catch.h"
#include"RingNode.h"

class Ring{
	
	private:
		int countNodes;
		RingNode* anker;
	public:
		Ring();
		void addNewNode(std::string description, std::string data);
		bool search(std::string data);
		void print();
		void updateAge();
		RingNode* getNode(std::string data);
		friend RingNode * get_anker(Ring& r);
		friend int get_countNodes(Ring& r);
};
