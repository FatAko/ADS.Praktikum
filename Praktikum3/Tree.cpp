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
void Tree::deleteAll(TreeNode* ptr) {	// Löscht alle Knoten
	if (ptr != nullptr) {
		deleteAll(ptr->getLeft());
		deleteAll(ptr->getLeft());
		delete ptr;
	}
}



void Tree::balance(TreeNode* ptr) {

}
bool Tree::split4Node(TreeNode* ptr) {
	//Falls Knoten nicht nullptr und Kinder nicht nullptr und Kinder rot
	if (ptr != nullptr && ptr->getLeft() != nullptr && ptr->getRight() != nullptr && !ptr->getRed() && ptr->getLeft()->getRed() && ptr->getRight()->getRed()) //Falls Knoten schwarz und Nachfolger rot
	{
		ptr->setRed(true);
		ptr->getLeft()->setRed(false);
		ptr->getRight()->setRed(false);
		return true;
	}
	else return false;
}
int Tree::printRBCriterion(TreeNode* ptr) {
	return 0;
}
bool Tree::rotateTreeRight(TreeNode* ptry, TreeNode* ptrx) {
	if (ptrx != nullptr && ptry != nullptr)
	{
		ptry->setLeft(ptrx->getRight());// Rechter Teilbaum von X  = Linker Teilbaum von Y
		if (ptry->getRight() != nullptr)
		{
			ptrx->getRight()->setParent(ptry);
		}
		ptrx->setParent(ptry->getParent());
		if (ptry->getParent() == nullptr)
		{
			anker = ptrx;
		}
		else if (ptry == ptry->getParent()->getLeft())
		{
			ptry->getParent()->setLeft(ptrx);
		}
		else
		{
			ptry->getParent()->setRight(ptrx);
		}
		ptry->setLeft(ptrx);
		ptry->setParent(ptrx);
		return true;
	}
	else return false;
}
bool Tree::rotateTreeLeft(TreeNode* ptrx, TreeNode* ptry) {
	if (ptrx != nullptr && ptry != nullptr)
	{
		ptrx->setRight(ptry->getLeft());// Rechter Teilbaum von X  = Linker Teilbaum von Y
		if (ptry->getLeft() != nullptr)
		{
			ptry->getLeft()->setParent(ptrx);
		}
		ptry->setParent(ptrx->getParent());
		if (ptrx->getParent() == nullptr)
		{
			anker = ptry;
		}
		else if (ptrx == ptrx->getParent()->getLeft())
		{
			ptrx->getParent()->setLeft(ptry);
		}
		else
		{
			ptrx->getParent()->setRight(ptry);
		}
		ptry->setLeft(ptrx);
		ptrx->setParent(ptry);
		return true;
	}
	else return false;
}
void Tree::printLevelOrder() {
	return;
}
void Tree::printLevelOrder(int p) {
	return;
}

////////////////Einfügen///////////////////////
bool Tree::addNode(std::string name, int age, double income, int postCode) {
	int nodeOrderID = age + postCode + income;
	TreeNode* ptr1 = anker,* newNode = new TreeNode(nodeOrderID, currentNodeChronologicalID++, name, age, income, postCode, true);
	while (true) { //Einfügepos finden und Knoten platzieren
		split4Node(ptr1);
		if (anker == nullptr) { //falls Baum leer -> farbe des Knotens schwarz
			anker = newNode; //Einzufügender Knoten wird zum Anker
			newNode->setRed(false); //Knoten wird schwarz
			break;
		} else { //Falls mehrere Knoten vorhanden
			if (nodeOrderID > ptr1->getNodeOrderID()) { //betrachte linken Teilbaum
				if (ptr1->getRight() == nullptr) {
					newNode->setParent(ptr1); //dem Einzufügendem Knoten den aktuellen Knoten als Parent übergeben
					ptr1->setRight(newNode); //dem aktuellem Knoten den einzufügendn Knoten rechts anhängen
					break;
				} else 
					ptr1 = ptr1->getRight();
			}
			else if (nodeOrderID < ptr1->getNodeOrderID()) { //betrachte rechten Teilbaum 
				if (ptr1->getLeft() == nullptr) {
					newNode->setParent(ptr1); //dem Einzufügendem Knoten den aktuellen Knoten als Parent übergeben
					ptr1->setLeft(newNode); //dem aktuellem Knoten den einzufügendn Knoten links anhängen
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
	if (ptr1 != nullptr) {
		if (ptr1 != nullptr && ptr1->getName() == name) //Wurzel
			result = 1;

		if (ptr1->getLeft() != nullptr) //linker Teilbaum
			searchPreOrder(ptr1->getLeft(), result, name);

		if (ptr1->getRight() != nullptr) //rechter Teilbaum
			searchPreOrder(ptr1->getRight(), result, name);
	}
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
bool Tree::searchOrderID(int orderID) {
	TreeNode* ptr1 = anker;
	int result = 0;
	search_OrderID(ptr1, result, orderID);
	return result;
}
void search_OrderID(TreeNode* ptr1, int& result, int orderID) {
	if (ptr1 != nullptr)
	{
		if (ptr1 != nullptr && ptr1->getNodeOrderID() == orderID) //Wurzel
			result = 1;

		if (ptr1->getLeft() != nullptr) //linker Teilbaum
			search_OrderID(ptr1->getLeft(), result, orderID);

		if (ptr1->getRight() != nullptr) //rechter Teilbaum
			search_OrderID(ptr1->getRight(), result, orderID);
	}
}
////////////Ausgabe Funktionen////////////////////
void Tree::printAll() {
	TreeNode* ptr1 = anker;
	cout << "ID | Name | Age | Income | PostCode | OrderID" << endl;
	cout << "---+------------+-------+-----------+-------+-------" << endl;
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

