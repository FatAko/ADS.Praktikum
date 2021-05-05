/*************************************************
 * ADS Praktikum 2.2
 * Tree.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;


Tree::Tree() {
}
////////////////Destruktor///////////////////////
Tree::~Tree() {
	deleteAll(anker->getRight());
	delete anker;
}
void Tree::deleteAll(TreeNode* ptr) {	// Löscht alle Knoten im BST
	if (ptr != nullptr) {
		deleteAll(ptr->getLeft());
		deleteAll(ptr->getLeft());
		delete ptr;
	}
}

////////////////Löschen///////////////////////

bool Tree::deleteNode(int nodeOrderID) {
	TreeNode* ptr = anker, * ancestor = nullptr, * min, * temp, * minAncestor = nullptr;
	//zu löschenden Knoten Suchen
	ptr = searchNodenAncestor(ptr, nodeOrderID, ancestor);
	//falls der zu löschende Knoten die Wurzel ist
	if (ancestor == nullptr) {
		if (ptr->getRight() == nullptr && ptr->getLeft() == nullptr) { //kein Nachfolger
			anker = nullptr;
			delete ptr;
			return true;
		}
		else if (ptr->getRight() == nullptr || ptr->getLeft() == nullptr) {//ein Nachfolger
			if (ptr->getLeft() != nullptr) {
				anker = ptr->getLeft();
			}
			else {
				anker = ptr->getRight();
			}
		}
		else if (ptr->getRight() != nullptr && ptr->getLeft() != nullptr) {//zwei Nachfolger
			min = kleinstesRechts(ptr->getRight(), minAncestor);

			// Falls min noch einen rechten Teilbaum besitzt
			minAncestor->setLeft(min->getRight()); // temp die Position von min einnehmen lassen

			min->setLeft(ptr->getLeft());  //Min die nachvolger von Ptr übergeben
			if (ptr->getRight() != min) {
				min->setRight(ptr->getRight());
			}
			anker = min;
			delete ptr;
			return true;
		}
	}
	else {
		if (ptr->getRight() == nullptr && ptr->getLeft() == nullptr) {// Fall 1: keine Nachfolger 
			if (ancestor->getLeft() != nullptr && ancestor->getLeft()->getNodeOrderID() == ptr->getNodeOrderID()) {
				ancestor->setLeft(nullptr);
				delete ptr;
				return true;
			}
			else {
				ancestor->setRight(nullptr);
				delete ptr;
				return true;
			}
		}
		else if (ptr->getRight() == nullptr || ptr->getLeft() == nullptr) {// Fall 2: ein Nachfolger
			if (ancestor->getLeft() != nullptr && ancestor->getLeft()->getNodeOrderID() == ptr->getNodeOrderID()) {// linke Seite vom ancestor
				if (ptr->getLeft() != nullptr) {
					temp = ptr->getLeft();
					ptr->setLeft(nullptr);
					ancestor->setLeft(temp);
				}
				if (ptr->getRight() != nullptr) {
					temp = ptr->getRight();
					ptr->setRight(nullptr);
					ancestor->setLeft(temp);
				}
				delete ptr;
			}
			if (ancestor->getRight() != nullptr && ancestor->getRight()->getNodeOrderID() == ptr->getNodeOrderID()) //rechte Seite vom ancestor
			{
				if (ptr->getLeft() != nullptr)
				{
					temp = ptr->getLeft();
					ptr->setLeft(nullptr);
					ancestor->setRight(temp);
				}
				if (ptr->getRight() != nullptr)
				{
					temp = ptr->getRight();
					ptr->setRight(nullptr);
					ancestor->setRight(temp);
				}
				delete ptr;
			}
		}
		else if (ptr->getRight() != nullptr && ptr->getLeft() != nullptr) {// Fall 3: 2 Nachfolger
			min = kleinstesRechts(ptr->getRight(), minAncestor);
			if (min->getRight() != nullptr) {//falls min noch einen rechten Teilbaum besitzt
				temp = min->getRight();
				minAncestor->setLeft(temp);
			}
			else {
				minAncestor->setLeft(nullptr); //eig irreleeant
			}
			if (ptr->getLeft() == min) {
				min->setRight(ptr->getRight());
			}
			if (ptr->getRight() == min) {
				min->setLeft(ptr->getLeft());
			}
			min->setLeft(ptr->getLeft());
			min->setRight(ptr->getRight());
			ptr->setLeft(nullptr);
			ptr->setRight(nullptr);
			if (ancestor != nullptr && ancestor->getLeft()->getNodeOrderID() == ptr->getNodeOrderID()) {
				ancestor->setLeft(min);
			}
			else if (ancestor != nullptr && ancestor->getRight()->getNodeOrderID() == ptr->getNodeOrderID()) {
				ancestor->setRight(min);
			}
			delete ptr;
		}
	}
}
////////////////Einfügen///////////////////////
void Tree::addNode(std::string name, int age, double income, int postCode) {
	int nodeOrderID = age + postCode + income, nodeChronologicalID = 0;
	TreeNode* ptr1 = anker;
	while (true) {
		if (ptr1 == nullptr) { //falls Baum leer 
			TreeNode* newNode = new TreeNode(nodeOrderID, nodeChronologicalID, name, age, income, postCode);
			anker = newNode;
			break;
		} else {
			nodeChronologicalID++; //bei jedem durchlauf um 1 erhöhen
			if (nodeOrderID > ptr1->getNodeOrderID()) { //betrachte linken Teilbaum
				if (ptr1->getRight() == nullptr) {
					TreeNode* newNode = new TreeNode(nodeOrderID, nodeChronologicalID, name, age, income, postCode);
					ptr1->setRight(newNode);
					break;
				} else 
					ptr1 = ptr1->getRight();
			}
			else if (nodeOrderID < ptr1->getNodeOrderID()) { //betrachte rechten Teilbaum 
				if (ptr1->getLeft() == nullptr) {
					TreeNode* newNode = new TreeNode(nodeOrderID, nodeChronologicalID, name, age, income, postCode);
					ptr1->setLeft(newNode);
					break;
				} else 
					ptr1 = ptr1->getLeft();
			}
		}
	}
}

////////////Suchfunktionen////////////////////
bool Tree::searchNode(std::string name) {
	TreeNode* ptr1 = anker;
	int result = 0;
	searchPreOrder(ptr1, result, name);
	return result;
}
void searchPreOrder(TreeNode* ptr1, int& result, string name) {
	if (ptr1->getName() == name) //Wurzel
		result = 1;

	if (ptr1->getLeft() != nullptr) //linker Teilbaum
		searchPreOrder(ptr1->getLeft(), result, name);

	if (ptr1->getRight() != nullptr) //rechter Teilbaum
		searchPreOrder(ptr1->getRight(), result, name);
}
vector<TreeNode> Tree::getNodes(std::string name) {
	vector<TreeNode> vector;
	TreeNode* ptr = anker;
	get_Nodes(vector, ptr, name);
	return vector;
}
void get_Nodes(vector<TreeNode>& vector,TreeNode* ptr, std::string name) {
	if (ptr->getName() == name) //Wurzel
		vector.push_back(*(ptr));
	if (ptr->getLeft() != nullptr) //linker Teilbaum
		get_Nodes(vector,ptr->getLeft(),name);
	if (ptr->getRight() != nullptr) //rechter Teilbaum
		get_Nodes(vector, ptr->getRight(), name);
}
TreeNode* Tree::kleinstesRechts(TreeNode* ptr, TreeNode*& ancestor) {
	ancestor = ptr;
	while (ptr->getLeft() != nullptr)
	{
		ancestor = ptr;
		ptr = ptr->getLeft();
	}
	return ptr;
}
TreeNode* searchNodenAncestor(TreeNode* ptr1, int nodeOrderID, TreeNode*& successor) {
	if (ptr1 != nullptr) {
		if (ptr1->getLeft() != nullptr) {
			if (ptr1->getLeft()->getNodeOrderID() == nodeOrderID) {
				successor = ptr1;
				return ptr1->getLeft();
			}
		}
		if (ptr1->getRight() != nullptr) {
			if (ptr1->getRight()->getNodeOrderID() == nodeOrderID) {
				successor = ptr1;
				return ptr1->getRight();
			}
		}
		if (ptr1->getNodeOrderID() == nodeOrderID) //Wurzel
			return ptr1;
	}
	if (ptr1->getLeft() != nullptr) //linker Teilbaum
		return searchNodenAncestor(ptr1->getLeft(), nodeOrderID, successor);

	if (ptr1->getRight() != nullptr) //rechter Teilbaum
		return searchNodenAncestor(ptr1->getRight(), nodeOrderID, successor);
}

////////////Ausgabe Funktionen////////////////////
void Tree::printAll() {
	TreeNode* ptr1 = anker;
	printAllPreOrder(ptr1);
}
void printAllPreOrder(TreeNode* ptr1) {
	if (ptr1 != nullptr) {
		cout << setw(3) << ptr1->getNodeChronologicalID() << "|" << setw(12) << ptr1->getName() << "|" << setw(7) << ptr1->getAge() << "|" << setw(11)
			 << ptr1->getIncome() << "|" << setw(7) << ptr1->getPostCode() << "|" << setw(0) << ptr1->getNodeOrderID() << endl;

		printAllPreOrder(ptr1->getLeft());

		printAllPreOrder(ptr1->getRight());
	}
}
void printNodeList(vector<TreeNode> vector) {
	for (int i = 0; i < vector.size(); i++)
	{
		cout << "ID: " << vector.at(i).getNodeChronologicalID() << ", Name: " << vector.at(i).getName() << ", Age: " << vector.at(i).getAge() << ", Income: " 
			 << vector.at(i).getIncome() << ", PostCode: " << vector.at(i).getPostCode() << ", Order ID: " << vector.at(i).getNodeOrderID() << endl;
	}
}

