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

/*
* Destruktor: Travesierung des Baumes und Löschen aller Knoten
*/
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

/*
* Einfügen: Suche iterativ nach der richtigen Position. Falls auf dem Weg schwarze Knoten mit zwei roten Nachfolgen gefunden
* werden, werden die Farben getauscht (außer bei der Wurzel). Nach dem einfügen Bottom-Up "aufräumen" 
*/
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

//Funktionen zur Manipulation des Baumes

/*
* Rechtsrotation: x wird Vorgänger von y, linker Teilbaum von y wird rechter Teilbaum von x (Falls y nicht die Wurzel auch noch parent ändern)
*/
bool Tree::rotateTreeRight(TreeNode* x, TreeNode* y) {
	if (x != nullptr && y != nullptr) { // falls beides gültige Knoten

		x->setLeft(y->getRight()); // Rechter Knoten von y wird linker Knoten von x

		if (y->getRight() != nullptr) // Falls Rechter kindknoten vorhanden wird dieser zum Vorgänger von x
			y->getRight()->setParent(x);

		y->setRight(x); // x wird zum Nachfolger von y
		if (x == anker) // Für den Fall das x die Wurzel ist, wird nun y die Wurzel
			anker = y;

		else { //ansonsten erhält y den vorherigen Vorgänger von x
			y->setParent(x->getParent());
			if (y->getParent()->getRight() == x) // Ermitteln um welchen Nachfolger es sich handelt (vom Parentknoten)
				y->getParent()->setRight(y);

			else y->getParent()->setLeft(y);

		}
		x->setParent(y); // Vorgänger von x wird y
		recolor(x, y); //umfärbung falls nötig
		return true;
	}
	else return false;
}
/*
* Linksrotation: y wird Vorgänger von x, rechter Teilbaum von x wird zum linken Teilbaum von y
*/
bool Tree::rotateTreeLeft(TreeNode* x, TreeNode* y) {
	if (x != nullptr && y != nullptr) { // falls beides gültige Knoten

		x->setRight(y->getLeft()); // Rechter Knoten von x wird rechter Knoten von y

		if (y->getLeft() != nullptr) // Falls Rechter kindknoten vorhanden wird dieser zum Vorgänger von y
			y->getLeft()->setParent(x);

		y->setLeft(x); // x wird zum Nachfolger von y
		if (x == anker) // Für den Fall das x die Wurzel ist, wird nun y die Wurzel
			anker = y;

		else { //ansonsten erhält x den vorherigen Vorgänger von y
			y->setParent(x->getParent());
			if (y->getParent()->getRight() == x) // Ermitteln um welchen Nachfolger es sich handelt (vom Parentknoten)
				y->getParent()->setRight(y);

			else y->getParent()->setLeft(y);

		}
		x->setParent(y); // Vorgänger von x wird y
		recolor(x, y); 
		return true;
	}
	else return false;
}
/*
* Hilfsfunktion zum "Aufräumen" : 4 Fälle zu beachten
*/
void Tree::balance(TreeNode* x) {
	if (x != nullptr)
	{
		// "Linie nach rechts" -> eine Linksrotation 
		if (x->getRight() != nullptr && x->getParent()->getRight() == x && x->getRight()->getRed())
			rotateTreeLeft(x->getParent(), x);

		// "Linie nach links" -> eine Rechtsrotation
		else if (x->getLeft() != nullptr && x->getParent()->getLeft() == x && x->getLeft()->getRed())
			rotateTreeRight(x->getParent(), x);

		// Knick nach rechts -> erst rechtsrotieren, dann links
		else if (x->getParent()->getRight() == x && x->getLeft()->getRed()) {
			rotateTreeRight(x, x->getLeft());
			rotateTreeLeft(x->getParent()->getParent(), x->getParent());
		}

		// Knick nach links -> erst linksrotieren, dann rechts
		else if (x->getParent()->getLeft() == x && x->getRight()->getRed()) {
			rotateTreeLeft(x, x->getRight());
			rotateTreeRight(x->getParent()->getParent(), x->getParent());
		}
	}
}
/*
* Hilfsfunktion zum "Aufräumen" : falls beim einfügen ein 4er Knoten gefunden wird -> Farbwechsel
*/
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
/*
* Hilfsfunktion zum rotieren : Farben anpassen nach der Rotation
*/
void recolor(TreeNode* x, TreeNode* y) {
	if (x != nullptr && y != nullptr) {
		bool c = false;
		c = y->getRed();
		y->setRed(x->getRed());
		x->setRed(c);
	}
}

void Tree::starterProofRBCriterion() {
	int result = 0;
	result = proofRBCriterion(anker);
	if (result != -1)
	{
		cout << "Der Baum ist schwarzausgeglichen und die Wurzel hat die Höhe " << result << "." << endl;
	}
	else
	{
		cout << "Der Baum ist nicht schwarzausgeglichen." << endl;
	}
}

int Tree::proofRBCriterion(TreeNode* ptr) {
	if (ptr != nullptr)
	{
		TreeNode* rechterTeilbaum = ptr->getRight();
		TreeNode* linkerTeilbaum = ptr->getLeft();

		int hoeheRechts = 0;
		int hoeheLinks = 0;

		//Fall 1: beide Nachfolger existieren nicht -> Blattknoten gefunden
		if (rechterTeilbaum == nullptr && linkerTeilbaum == nullptr)
			return 0; // Die Höhe 0 wird zurückgegeben

		if (rechterTeilbaum != nullptr && linkerTeilbaum != nullptr) // Beide Nachfolger vorhanden
		{
			hoeheRechts = proofRBCriterion(rechterTeilbaum); //rekursiver Aufruf zur Ermittlung der Höhe der Teilbäume
			hoeheLinks = proofRBCriterion(linkerTeilbaum);

			//Fall 2: Beide Nachfolger sind rot
			if (rechterTeilbaum->getRed() && linkerTeilbaum->getRed())
			{
				// Die Höhen der roten Knoten müssen übereinstimmen, ansonsten Fehler
				if (hoeheLinks == hoeheRechts)
				{
					return hoeheRechts;
				}
				else
				{
					return -1;
				}
			}
			//Fall 3: einer der Nachfolger ist rot, der andere schwarz
			if (rechterTeilbaum->getRed() && !linkerTeilbaum->getRed())
			{
				//Die Höhe des roten Knotens muss um eins höher sein als die Höhe des schwarzen Knotens
				if (hoeheRechts == hoeheLinks + 1)
				{
					return hoeheRechts;
				}
				else
				{
					return -1; // sonst Fehler
				}
			}
			else if (!rechterTeilbaum->getRed() && linkerTeilbaum->getRed())
			{
				//Die Höhe des roten Knotens muss um eins höher sein als die Höhe des schwarzen Knotens
				if (hoeheLinks == hoeheRechts + 1)
				{
					return hoeheLinks;
				}
				else
				{
					return -1; // sonst Fehler
				}
			}
			//Fall 4: beide Nachfolger sind schwarz
			if (!rechterTeilbaum->getRed() && !linkerTeilbaum->getRed())
			{
				//Die Höhen der schwarzen Knoten müssen gleich sein und es wird die Höhe der schwarzen Knoten + 1 zurückgegeben
				if (hoeheRechts == hoeheLinks)
				{
					return hoeheLinks + 1;
				}
			}
		}
		//Fall 5: Falls einer der Nachfolger nicht existiert
		else
		{
			if (rechterTeilbaum != nullptr && linkerTeilbaum == nullptr)
			{
				//Es gibt einen Nachfolger und dieser ist rot
				if (rechterTeilbaum->getRed())
				{
					hoeheLinks = hoeheRechts; //Bei roten Nachfolgeknoten wird die gleiche Höhe zurückgegeben
					return hoeheRechts;
				}
				//Es gibt einen Nachfolger und dieser ist schwarz
				else
				{
					hoeheLinks = hoeheRechts + 1; //Bei schwarzen Nachfolgeknoten wird die gleiche Höhe +1 zurückgegeben
					return hoeheRechts;
				}
			}
			else if (rechterTeilbaum == nullptr && linkerTeilbaum != nullptr)
			{
				//Es gibt einen Nachfolger und dieser ist rot
				if (linkerTeilbaum->getRed())
				{
					hoeheRechts = hoeheLinks;
					return hoeheLinks;
				}
				//Es gibt einen Nachfolger und dieser ist schwarz
				else
				{
					hoeheRechts = hoeheLinks + 1;
					return hoeheLinks;
				}
			}
			else
			{
				return -1;
			}
		}
		return -1;
	}
	else
	{
		return -1; // Fehler erkannt
	}
	return -1;
}

// Suchfunktionen

/*
* Suchen: Baum travesieren und true ausgeben falls gesuchter Knoten gefunden wird
*/
bool Tree::searchNode(std::string name) {
	TreeNode* ptr1 = anker;
	int result = 0;
	searchPreOrder(ptr1, result, name);
	return result;
}
/*
* Suchen Hilfsmethode: PreOrder travesierung
*/
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

/*
* Levelorder: Travesiert Baum nach Levelorder und gibt gemäß 234 Struktur aus
*/
void Tree::printLevelOrder() {
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

/*
* Levelorder: Travesiert Baum nach Levelorder und gibt gemäß 234 Struktur aus (nur das Niveau, welches man per Parameter übergibt)
*/
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

/*
* Hilfmethode für die main: Levelorder: Travesiert Baum nach Levelorder und gibt gemäß Rot-Schwarz Baum aus
*/
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
/*
* Ausgabe aller Knoten mit Preorder-verfahren
*/
void Tree::printAll() {
	TreeNode* ptr1 = anker;
	cout << endl;
	cout << "ID | Name       | Alter | Einkommen |  PLZ  |  Pos  " << endl;
	cout << "---+------------+-------+-----------+-------+-------" << endl;
	printAllPreOrder(ptr1);
}
/*
* Hilfsfunktion für printAll()
*/
void printAllPreOrder(TreeNode* ptr1) {
	if (ptr1 != nullptr) {
		cout << setw(3) << ptr1->getNodeChronologicalID() << "|" << setw(12) << ptr1->getName() << "|" << setw(7) << ptr1->getAge() << "|" << setw(11)
			<< ptr1->getIncome() << "|" << setw(7) << ptr1->getPostCode() << "|" << setw(7) << ptr1->getNodeOrderID() << endl;

		printAllPreOrder(ptr1->getLeft());
		printAllPreOrder(ptr1->getRight());
	}
}
/*
* Hilfsfunktionen für die main: suchen und alle Knoten mit dem entsprchenden Namen ausgeben
*	Baum wird preOrder travesiert und gefundene Knoten werden in einer Liste gespeichert.
*	Ausgebe der Liste
*/
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



