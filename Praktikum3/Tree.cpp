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

	int Tree::proofRBCriterion(TreeNode * ptr) {
		if (ptr == nullptr) { return -1; } //Fehler
		TreeNode* rtb = ptr->getRight(), * ltb = ptr->getLeft();
		if (rtb == nullptr && ltb == nullptr) //Blattknoten wurde gefunden keine Nachfolger
		{
			return 0;
		}
		else if (rtb != nullptr && ltb != nullptr)
		{
			int rtb_hoehe = proofRBCriterion(rtb), ltb_hoehe = proofRBCriterion(ltb); //rekursiver aufruf für die höhe
			if (rtb->getRed() && ltb->getRed())//beide Nachfolger sind rot
			{
				if (rtb_hoehe == ltb_hoehe) return ltb_hoehe;
			}
			else if (!rtb->getRed() && !ltb->getRed()) //beide nachfolger sind schwarz
			{
				if (rtb_hoehe == ltb_hoehe) return ltb_hoehe + 1;
			}
			else if (rtb->getRed() ^ ltb->getRed()) //Ein Nachfolger ist rot und der andere schwarz 
			{
				if (rtb->getRed() && rtb_hoehe - ltb_hoehe == 1) return rtb_hoehe;
				if (ltb->getRed() && ltb_hoehe - rtb_hoehe == 1) return ltb_hoehe;

			}
			return -1;//Fehler, weil sonst schon return
		}
		else if ((rtb == nullptr) ^ (ltb == nullptr)) //Einer der beiden Nachfolger existiert nicht
		{
			if (rtb != nullptr) //rechter Nachfolger
			{
				int rtb_hoehe = proofRBCriterion(rtb);
				if (rtb->getRed())return rtb_hoehe;
				else return rtb_hoehe + 1;
			}
			else {//linker Nachfolger
				int ltb_hoehe = proofRBCriterion(ltb);
				if (ltb->getRed())return ltb_hoehe;
				else return ltb_hoehe + 1;
			}
		}
		return -1;
}

void Tree::LevelOrder() {
	cout << "ID | Name       | Alter | Einkommen |  PLZ  |  Pos  | Red " << endl;
	cout << "---+------------+-------+-----------+-------+-------+-------" << endl;
	queue<TreeNode*> nodeQueue;
	queue<int> niveauQueue;
	int aktNiv = 0;
	bool rechtsVorhanden = 0, linksVorhanden = 0, nivAusgabe = 0;
	int nivAlt = 0;
	if (anker != nullptr)
	{
		nodeQueue.push(anker);
		niveauQueue.push(aktNiv);
		while (true)
		{
			if (nodeQueue.empty())
				break;
			TreeNode* ptr = nodeQueue.front();
			aktNiv++;
			//linker Teilbaum
			if (ptr->getLeft() != nullptr && ptr->getLeft()->getRed()) // Falls Root einen roten rechten Nachfolger hat
			{
				linksVorhanden = 1;
				if (ptr->getLeft()->getLeft() != nullptr) // Falls Rechter roter Nachfolger einen linken schwarzen Nachfolger besitzt
				{
					nodeQueue.push(ptr->getLeft()->getLeft()); // Füge "Enkel" in die Queue ein
					niveauQueue.push(aktNiv);
				}
				if (ptr->getLeft()->getRight() != nullptr) // Falls Rechter roter Nachfolger einen rechten schwarzen Nachfolger besitzt
				{
					nodeQueue.push(ptr->getLeft()->getRight()); // Füge "Enkel" in die Queue ein
					niveauQueue.push(aktNiv);
				}

			}
			else if (ptr->getLeft() != nullptr && !ptr->getLeft()->getRed()) // Falls Root einen Schwarzen rechten Nachfolger hat
			{
				linksVorhanden = 0;
				nodeQueue.push(ptr->getLeft());
				niveauQueue.push(aktNiv);
			}
			//rechter Teilbaum
			if (ptr->getRight() != nullptr && ptr->getRight()->getRed()) // Falls Root einen roten rechten Nachfolger hat
			{
				rechtsVorhanden = 1;
				if (ptr->getRight()->getLeft() != nullptr) // Falls Rechter roter Nachfolger einen linken schwarzen Nachfolger besitzt
				{
					nodeQueue.push(ptr->getRight()->getLeft()); // Füge "Enkel" in die Queue ein
					niveauQueue.push(aktNiv);
				}
				if (ptr->getRight()->getRight() != nullptr) // Falls Rechter roter Nachfolger einen rechten schwarzen Nachfolger besitzt
				{
					nodeQueue.push(ptr->getRight()->getRight()); // Füge "Enkel" in die Queue ein
					niveauQueue.push(aktNiv);
				}

			}
			else if (ptr->getRight() != nullptr && !ptr->getRight()->getRed()) // Falls Root einen Schwarzen rechten Nachfolger hat
			{
				rechtsVorhanden = 0;
				nodeQueue.push(ptr->getRight());
				niveauQueue.push(aktNiv);
			}
			aktNiv--;
			//Niveau Ausgabe
			nivAlt = niveauQueue.front();
			//Überprüfe um was für Knoten es sich handelt + Ausgabe
			if (linksVorhanden && rechtsVorhanden)
			{
				cout << setw(3) << ptr->getLeft()->getNodeChronologicalID() << "|" << setw(12) << ptr->getLeft()->getName() << "|" << setw(7) << ptr->getLeft()->getAge() << "|" << setw(11)
					<< ptr->getLeft()->getIncome() << "|" << setw(7) << ptr->getLeft()->getPostCode() << "|" << setw(7) << ptr->getLeft()->getNodeOrderID() << setw(1) << "|" <<setw(2)<< ptr->getLeft()->getRed() << endl;

				cout << setw(3) << ptr->getNodeChronologicalID() << "|" << setw(12) << ptr->getName() << "|" << setw(7) << ptr->getAge() << "|" << setw(11)
					<< ptr->getIncome() << "|" << setw(7) << ptr->getPostCode() << "|" << setw(7) << ptr->getNodeOrderID() << setw(1) << "|" << setw(2) << ptr->getRed() << endl;


				cout << setw(3) << ptr->getRight()->getNodeChronologicalID() << "|" << setw(12) << ptr->getRight()->getName() << "|" << setw(7) << ptr->getRight()->getAge() << "|" << setw(11)
					<< ptr->getRight()->getIncome() << "|" << setw(7) << ptr->getRight()->getPostCode() << "|" << setw(7) << ptr->getRight()->getNodeOrderID() << setw(1) << "|" << setw(2) << ptr->getRight()->getRed() << endl;

			}
			else if (linksVorhanden)
			{
				cout << setw(3) << ptr->getLeft()->getNodeChronologicalID() << "|" << setw(12) << ptr->getLeft()->getName() << "|" << setw(7) << ptr->getLeft()->getAge() << "|" << setw(11)
					<< ptr->getLeft()->getIncome() << "|" << setw(7) << ptr->getLeft()->getPostCode() << "|" << setw(7) << ptr->getLeft()->getNodeOrderID() << setw(1) << "|" << setw(2) << ptr->getLeft()->getRed() << endl;


				cout << setw(3) << ptr->getLeft()->getNodeChronologicalID() << "|" << setw(12) << ptr->getName() << "|" << setw(7) << ptr->getAge() << "|" << setw(11)
					<< ptr->getIncome() << "|" << setw(7) << ptr->getPostCode() << "|" << setw(7) << ptr->getNodeOrderID() << setw(1) << "|" << setw(2) << ptr->getRed() << endl;

			}
			else if (rechtsVorhanden)
			{
				cout << setw(3) << ptr->getNodeChronologicalID() << "|" << setw(12) << ptr->getName() << "|" << setw(7) << ptr->getAge() << "|" << setw(11)
					<< ptr->getIncome() << "|" << setw(7) << ptr->getPostCode() << "|" << setw(7) << ptr->getNodeOrderID() << setw(1) << "|" << setw(2) << ptr->getRed() << endl;


				cout << setw(3) << ptr->getRight()->getNodeChronologicalID() << "|" << setw(12) << ptr->getRight()->getName() << "|" << setw(7) << ptr->getRight()->getAge() << "|" << setw(11)
					<< ptr->getRight()->getIncome() << "|" << setw(7) << ptr->getRight()->getPostCode() << "|" << setw(7) << ptr->getRight()->getNodeOrderID() << setw(1) << "|" << setw(2) << ptr->getRight()->getRed() << endl;

			}
			else
			{
				cout << setw(3) << ptr->getNodeChronologicalID() << "|" << setw(12) << ptr->getName() << "|" << setw(7) << ptr->getAge() << "|" << setw(11)
					<< ptr->getIncome() << "|" << setw(7) << ptr->getPostCode() << "|" << setw(7) << ptr->getNodeOrderID() << setw(1) << "|" << setw(2) << ptr->getRed() << endl;

			}
			linksVorhanden = 0;
			rechtsVorhanden = 0;
			nodeQueue.pop();
			niveauQueue.pop();
			//Niveau Upadate
			if (!niveauQueue.empty() && nivAlt != niveauQueue.front())
			{
				aktNiv++;
				nivAusgabe = 0;
			}
		}
		cout << endl;
	}
}

void Tree::printLevelOrder(void) {
	queue<TreeNode*> nodeQueue;
	queue<int> niveauQueue;
	int aktNiv = 0;
	bool rechtsVorhanden = 0, linksVorhanden = 0, nivAusgabe = 0;
	int nivAlt = 0;
	if (anker != nullptr)
	{
		nodeQueue.push(anker);
		niveauQueue.push(aktNiv);
		while (true)
		{
			if (nodeQueue.empty())
				break;
			TreeNode* ptr = nodeQueue.front();
			aktNiv++;
			//linker Teilbaum
			if (ptr->getLeft() != nullptr && ptr->getLeft()->getRed()) // Falls Root einen roten rechten Nachfolger hat
			{
				linksVorhanden = 1;
				if (ptr->getLeft()->getLeft() != nullptr) // Falls Rechter roter Nachfolger einen linken schwarzen Nachfolger besitzt
				{
					nodeQueue.push(ptr->getLeft()->getLeft()); // Füge "Enkel" in die Queue ein
					niveauQueue.push(aktNiv);
				}
				if (ptr->getLeft()->getRight() != nullptr) // Falls Rechter roter Nachfolger einen rechten schwarzen Nachfolger besitzt
				{
					nodeQueue.push(ptr->getLeft()->getRight()); // Füge "Enkel" in die Queue ein
					niveauQueue.push(aktNiv);
				}
				
			}
			else if (ptr->getLeft() != nullptr && !ptr->getLeft()->getRed()) // Falls Root einen Schwarzen rechten Nachfolger hat
			{
				linksVorhanden = 0;
				nodeQueue.push(ptr->getLeft());
				niveauQueue.push(aktNiv);
			}
			//rechter Teilbaum
			if (ptr->getRight() != nullptr && ptr->getRight()->getRed()) // Falls Root einen roten rechten Nachfolger hat
			{
				rechtsVorhanden = 1;
				if (ptr->getRight()->getLeft() != nullptr) // Falls Rechter roter Nachfolger einen linken schwarzen Nachfolger besitzt
				{
					nodeQueue.push(ptr->getRight()->getLeft()); // Füge "Enkel" in die Queue ein
					niveauQueue.push(aktNiv);
				}
				if (ptr->getRight()->getRight() != nullptr) // Falls Rechter roter Nachfolger einen rechten schwarzen Nachfolger besitzt
				{
					nodeQueue.push(ptr->getRight()->getRight()); // Füge "Enkel" in die Queue ein
					niveauQueue.push(aktNiv);
				}
				
			}
			else if (ptr->getRight() != nullptr && !ptr->getRight()->getRed()) // Falls Root einen Schwarzen rechten Nachfolger hat
			{
				rechtsVorhanden = 0;
				nodeQueue.push(ptr->getRight());
				niveauQueue.push(aktNiv);
			}
			aktNiv--;
			//Niveau Ausgabe
			if (!nivAusgabe)
			{
				cout << endl;
				cout << "Niv " << aktNiv << ": ";
				nivAusgabe = 1;
			}
			nivAlt = niveauQueue.front();
			//Überprüfe um was für Knoten es sich handelt + Ausgabe
			if (linksVorhanden && rechtsVorhanden)
			{
				cout << "(" << ptr->getLeft()->getNodeOrderID() << "," << ptr->getNodeOrderID() << "," << ptr->getRight()->getNodeOrderID() << ")";
			}
			else if (linksVorhanden)
			{
				cout << "(" << ptr->getLeft()->getNodeOrderID() << "," << ptr->getNodeOrderID() << ")";
			}
			else if (rechtsVorhanden)
			{
				cout << "(" << ptr->getNodeOrderID() << "," << ptr->getRight()->getNodeOrderID() << ")";
			}
			else
			{
				cout << "(" << ptr->getNodeOrderID() << ")";
			}
			linksVorhanden = 0;
			rechtsVorhanden = 0;
			nodeQueue.pop();
			niveauQueue.pop();
			//Niveau Upadate
			if (!niveauQueue.empty() && nivAlt != niveauQueue.front())
			{
				aktNiv++;
				nivAusgabe = 0;
			}
		}
		cout << endl;
	}
}

void Tree::printLevelOrder(int niv) {
	queue<TreeNode*> nodeQueue;
	queue<int> niveauQueue;
	int aktNiv = 0;
	bool rechtsVorhanden = 0, linksVorhanden = 0, nivAusgabe = 0;
	int nivAlt = 0;
	if (anker != nullptr)
	{
		nodeQueue.push(anker);
		niveauQueue.push(aktNiv);
		while (true)
		{
			if (nodeQueue.empty())
				break;
			TreeNode* ptr = nodeQueue.front();
			aktNiv++;
			//rechter Teilbaum
			if (ptr->getRight() != nullptr && ptr->getRight()->getRed()) // Falls Root einen roten rechten Nachfolger hat
			{
				rechtsVorhanden = 1;
				if (ptr->getRight()->getRight() != nullptr) // Falls Rechter roter Nachfolger einen rechten schwarzen Nachfolger besitzt
				{
					nodeQueue.push(ptr->getRight()->getRight()); // Füge "Enkel" in die Queue ein
					niveauQueue.push(aktNiv);
				}
				if (ptr->getRight()->getLeft() != nullptr) // Falls Rechter roter Nachfolger einen linken schwarzen Nachfolger besitzt
				{
					nodeQueue.push(ptr->getRight()->getLeft()); // Füge "Enkel" in die Queue ein
					niveauQueue.push(aktNiv);
				}
			}
			else if (ptr->getRight() != nullptr && !ptr->getRight()->getRed()) // Falls Root einen Schwarzen rechten Nachfolger hat
			{
				rechtsVorhanden = 0;
				nodeQueue.push(ptr->getRight());
				niveauQueue.push(aktNiv);
			}
			//linker Teilbaum
			if (ptr->getLeft() != nullptr && ptr->getLeft()->getRed()) // Falls Root einen roten rechten Nachfolger hat
			{
				linksVorhanden = 1;
				if (ptr->getLeft()->getRight() != nullptr) // Falls Rechter roter Nachfolger einen rechten schwarzen Nachfolger besitzt
				{
					nodeQueue.push(ptr->getLeft()->getRight()); // Füge "Enkel" in die Queue ein
					niveauQueue.push(aktNiv);
				}
				if (ptr->getLeft()->getLeft() != nullptr) // Falls Rechter roter Nachfolger einen linken schwarzen Nachfolger besitzt
				{
					nodeQueue.push(ptr->getLeft()->getLeft()); // Füge "Enkel" in die Queue ein
					niveauQueue.push(aktNiv);
				}
			}
			else if (ptr->getLeft() != nullptr && !ptr->getLeft()->getRed()) // Falls Root einen Schwarzen rechten Nachfolger hat
			{
				linksVorhanden = 0;
				nodeQueue.push(ptr->getLeft());
				niveauQueue.push(aktNiv);
			}
			aktNiv--;
			if (aktNiv == niv)
			{
				//Niveau Ausgabe
				if (!nivAusgabe)
				{
					cout << endl;
					cout << "Niv " << aktNiv << ": ";
					nivAusgabe = 1;
				}
				nivAlt = niveauQueue.front();
				//Überprüfe um was für Knoten es sich handelt + Ausgabe
				if (linksVorhanden && rechtsVorhanden)
				{
					cout << "(" << ptr->getLeft()->getNodeOrderID() << "," << ptr->getNodeOrderID() << "," << ptr->getRight()->getNodeOrderID() << ")";
				}
				else if (linksVorhanden)
				{
					cout << "(" << ptr->getLeft()->getNodeOrderID() << "," << ptr->getNodeOrderID() << ")";
				}
				else if (rechtsVorhanden)
				{
					cout << "(" << ptr->getNodeOrderID() << "," << ptr->getRight()->getNodeOrderID() << ")";
				}
				else
				{
					cout << "(" << ptr->getNodeOrderID() << ")";
				}
			}
			linksVorhanden = 0;
			rechtsVorhanden = 0;
			nodeQueue.pop();
			niveauQueue.pop();
			//Niveau Upadate
			if (!niveauQueue.empty() && nivAlt != niveauQueue.front())
			{
				aktNiv++;
				nivAusgabe = 0;
			}
		}
		cout << endl;
	}
}

void Tree::printAll() {
	TreeNode* ptr1 = anker;
	cout << endl;
	cout << "ID | Name       | Alter | Einkommen |  PLZ  |  Pos  " << endl;
	cout << "---+------------+-------+-----------+-------+-------" << endl;
	printAllPreOrder(ptr1);
}
void printAllPreOrder(TreeNode* ptr1) {
	if (ptr1 != nullptr) {
		cout << setw(3) << ptr1->getNodeChronologicalID() << "|" << setw(12) << ptr1->getName() << "|" << setw(7) << ptr1->getAge() << "|" << setw(11)
			<< ptr1->getIncome() << "|" << setw(7) << ptr1->getPostCode() << "|" << setw(7) << ptr1->getNodeOrderID() << endl;

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



