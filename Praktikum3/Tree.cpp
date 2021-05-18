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
#include <stack>
using namespace std;


Tree::Tree() {
	anker = nullptr;
	currentNodeChronologicalID = 0;
}


Tree::~Tree()
{
	deleteAll(anker);
}
void Tree::deleteAll(TreeNode* ptr) {
	if (ptr != nullptr) {
		deleteAll(ptr->getLeft());
		deleteAll(ptr->getRight());
		delete ptr;
	}
}

bool Tree::addNode(std::string name, int age, double income, int postCode) {
	int nodeOrderID = age + postCode + income;
	TreeNode* ptr1 = anker, * newNode = new TreeNode(nodeOrderID, currentNodeChronologicalID++, name, age, income, postCode, true);

	if (anker == nullptr) { //falls Baum leer -> farbe des Knotens schwarz
		anker = newNode; //Einzufügender Knoten wird zum Anker
		newNode->setRed(false); //Knoten wird schwarz
	}
	else
	{
		while (true) { //Einfügepos finden und Knoten platzieren
			split4Node(ptr1);
			if (nodeOrderID > ptr1->getNodeOrderID()) { //betrachte rechten Teilbaum
				if (ptr1->getRight() == nullptr) {
					newNode->setParent(ptr1); //dem Einzufügendem Knoten den aktuellen Knoten als Parent übergeben
					ptr1->setRight(newNode); //dem aktuellem Knoten den einzufügendn Knoten rechts anhängen
					break;
				}
				else
					ptr1 = ptr1->getRight();
			}
			else if (nodeOrderID < ptr1->getNodeOrderID()) { //betrachte linken Teilbaum 
				if (ptr1->getLeft() == nullptr) {
					newNode->setParent(ptr1); //dem Einzufügendem Knoten den aktuellen Knoten als Parent übergeben
					ptr1->setLeft(newNode); //dem aktuellem Knoten den einzufügendn Knoten links anhängen
					break;
				}
				else
					ptr1 = ptr1->getLeft();
			}
			else // nodeOrderID bereits vorhanden, Knoten wird nicht eingefügt, da bereits vorhanden
				return false;
		}
	}
	ptr1 = newNode;
	while (ptr1 != nullptr && ptr1->getParent() != anker) { // Baum von unten bis zur Wurzel durchlaufen

		if (ptr1->getRed() && ptr1->getParent()->getRed()) // Falls zwei Knoten übereinander rot
			balance(ptr1->getParent());//Fallunterscheidung -> Rotation

		ptr1 = ptr1->getParent();
	}
	return true;
}
bool Tree::rotateTreeRight(TreeNode* x, TreeNode* y) {
	if (x != nullptr && y != nullptr) {

		x->setLeft(y->getRight());

		if (y->getRight() != nullptr)
			y->getRight()->setParent(x);

		y->setRight(x);
		if (x == anker)
			anker = y;

		else {
			y->setParent(x->getParent());
			if (y->getParent()->getRight() == x)
				y->getParent()->setRight(y);

			else y->getParent()->setLeft(y);

		}
		x->setParent(y);
		recolor(x, y);
		return true;
	}
	else return false;
}

bool Tree::rotateTreeLeft(TreeNode* x, TreeNode* y) {
	if (x != nullptr && y != nullptr) {

		x->setRight(y->getLeft());

		if (y->getLeft() != nullptr)
			y->getLeft()->setParent(x);

		y->setLeft(x);
		if (x == anker)
			anker = y;

		else {
			y->setParent(x->getParent());
			if (y->getParent()->getRight() == x)
				y->getParent()->setRight(y);

			else y->getParent()->setLeft(y);

		}
		x->setParent(y);
		recolor(x, y);
		return true;
	}
	else return false;
}

void Tree::balance(TreeNode* x) {
	if (x != nullptr)
	{
		if (x->getRight() != nullptr && x->getParent()->getRight() == x && x->getRight()->getRed())
			rotateTreeLeft(x->getParent(), x);

		else if (x->getLeft() != nullptr && x->getParent()->getLeft() == x && x->getLeft()->getRed())
			rotateTreeRight(x->getParent(), x);

		else if (x->getParent()->getRight() == x && x->getLeft()->getRed()) {
			rotateTreeRight(x, x->getLeft());
			rotateTreeLeft(x->getParent()->getParent(), x->getParent());
		}
		else if (x->getParent()->getLeft() == x && x->getRight()->getRed()) {
			rotateTreeLeft(x, x->getRight());
			rotateTreeRight(x->getParent()->getParent(), x->getParent());
		}
	}
}

bool Tree::split4Node(TreeNode* ptr) {
	TreeNode* ptr1 = ptr;
	if (ptr1 != nullptr && ptr1->getLeft() != nullptr && ptr1->getRight() != nullptr
		&& !ptr1->getRed() && ptr1->getLeft()->getRed() && ptr1->getRight()->getRed())
	{
		if (ptr1 == anker) //Falls aktueller Knoten die Wurzel ist 
			ptr1->setRed(0); // färbe Wurzel schwarz
		else
			ptr1->setRed(1); // ansonsten Knoten rot

		ptr1->getLeft()->setRed(0);
		ptr1->getRight()->setRed(0);
		return true;
	}
	else return false;
}

void recolor(TreeNode* x, TreeNode* y) {
	if (x != nullptr && y != nullptr) {
		bool c = false;
		c = y->getRed();
		y->setRed(x->getRed());
		x->setRed(c);
	}
}

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

int Tree::proofRBCriterion(TreeNode* x) {
	return 0;
}

void Tree::printLevelOrder(void) {
	
}

void Tree::printLevelOrder(int parameter) {

}

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
vector<TreeNode> Tree::getNodes(std::string name) {
	vector<TreeNode> vector;
	TreeNode* ptr = anker;
	get_Nodes(vector, ptr, name);
	return vector;
}
void get_Nodes(vector<TreeNode>& vector, TreeNode* ptr, std::string name) {
	if (ptr->getName() == name) //Wurzel
		vector.push_back(*(ptr));
	if (ptr->getLeft() != nullptr) //linker Teilbaum
		get_Nodes(vector, ptr->getLeft(), name);
	if (ptr->getRight() != nullptr) //rechter Teilbaum
		get_Nodes(vector, ptr->getRight(), name);
}
void printNodeList(vector<TreeNode> vector) {
	for (int i = 0; i < vector.size(); i++)
	{
		cout << "ID: " << vector.at(i).getNodeChronologicalID() << ", Name: " << vector.at(i).getName() << ", Age: " << vector.at(i).getAge() << ", Income: "
			<< vector.at(i).getIncome() << ", PostCode: " << vector.at(i).getPostCode() << ", Order ID: " << vector.at(i).getNodeOrderID() << endl;
	}
}



