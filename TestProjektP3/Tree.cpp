/*************************************************
 * ADS Praktikum 2.2
 * Tree.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iomanip>
#include <iostream>
#include <stack>


using namespace std;

Tree::Tree() {
	anker = nullptr;
	currentNodeChronologicalID = 0;
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
		else if (x->getParent()->getLeft() == x && x->getRight()->getRed() == true) {
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
			ptr1->setRed(false); // färbe Wurzel schwarz
		else
			ptr1->setRed(true); // ansonsten Knoten rot

		ptr1->getLeft()->setRed(false);
		ptr1->getRight()->setRed(false);
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

bool Tree::searchNode(string parameter_1) {
	bool yn = false;
	if (anker == nullptr) {
		return false;
	}
	else {
		TreeNode* ptr = anker;
		printPreorder(ptr, parameter_1, yn);
		if (yn == false) {
			cout << "+ Der zu suchende Datensatz existiert nicht" << endl;
		}
		return yn;
	}
}

int Tree::proofRBCriterion(TreeNode* x) {
	//Ein Fehler wird erkannt
	if (x == nullptr) {
		return -1;//-1 soll zuruck gegeben werden
	}
	TreeNode* linker_nachfolger = x->getLeft();
	TreeNode* rechter_nachfolger = x->getRight();
	//Einer der Nachfolger existiert nicht
	if (linker_nachfolger == nullptr && rechter_nachfolger != nullptr) {//Rechter Nachfolger existiert jedoch linker Nachfolger nicht    
		int rechte_hoehe = proofRBCriterion(rechter_nachfolger);//rekursiver Aufruf
		if (rechter_nachfolger->getRed() == true) {//Beim roten Nachfolgeknoten wird die gleiche Hohe zuruck gegegben
			return rechte_hoehe;
		}
		else {//Beim schwarzen Nachfolgeknoten die Hohe + 1 wird zuruckgegeben
			return rechte_hoehe + 1;
		}
	}
	////Falls einer der Nachfolger nicht existiert, wird die Hohe des anderen Knotens ubernommen: beim schwarzen Nachfolgeknoten die Hohe + 1, beim roten Nachfolgeknoten wird die gleiche Hohe zuruck gegegben.
	else if (linker_nachfolger != nullptr && rechter_nachfolger == nullptr) {//Linker Nachfolger existiert jedoch rechter Nachfolger nicht
		int linke_hoehe = proofRBCriterion(linker_nachfolger);//rekursiver Aufruf
		if (linker_nachfolger->getRed() == true) {//Beim roten Nachfolgeknoten wird die gleiche Hohe zuruck gegegben
			return linke_hoehe;
		}
		else {//Beim schwarzen Nachfolgeknoten die Hohe + 1 wird zuruckgegeben
			return linke_hoehe + 1;
		}
	}
	//beide Nachfolger existieren nicht
	else if (linker_nachfolger == nullptr && rechter_nachfolger == nullptr) {
		return 0;//Ein Blattknoten ist gefunden, die Hohe 0 wird zuruckgegeben
	}

	else if (linker_nachfolger != nullptr && rechter_nachfolger != nullptr) {
		//beide Nachfolger sind rot
		if (linker_nachfolger->getRed() == true && rechter_nachfolger->getRed() == true) {
			int linke_hoehe = proofRBCriterion(linker_nachfolger);//rekursiver Aufruf
			int rechte_hoehe = proofRBCriterion(rechter_nachfolger);//rekursiver Aufruf
			if (linke_hoehe == rechte_hoehe) {//Die Hohen der schwarzen Knoten mussen gleich sein
				return linke_hoehe;//Es wird die Hohe der schwarzen Nachfolgerknoten + 1 zuruck gegeben
			}
		}
		//beide Nachfolger sind schwarz
		else if (linker_nachfolger->getRed() == false && rechter_nachfolger->getRed() == false) {
			int linke_hoehe = proofRBCriterion(linker_nachfolger);//rekursiver Aufruf
			int rechte_hoehe = proofRBCriterion(rechter_nachfolger);//rekursiver Aufruf
			if (linke_hoehe == rechte_hoehe) {//Die Hohen der schwarzen Knoten mussen gleich sein
				return linke_hoehe + 1;//Es wird die Hohe der schwarzen Nachfolgerknoten + 1 zuruck gegeben
			}
		}
		//einer der Nachfolger ist rot, der andere schwarz
		else if (linker_nachfolger->getRed() == false && rechter_nachfolger->getRed() == true) {
			int hoehe_des_roten_Knotens = proofRBCriterion(rechter_nachfolger);//rekursiver Aufruf
			int hoehe_des_schwarzen_Knotens = proofRBCriterion(linker_nachfolger);//rekursiver Aufruf
			if (hoehe_des_roten_Knotens - hoehe_des_schwarzen_Knotens == 1) {//Die Hohe des roten Knotens muss um eins hoher sein als die Hohe des schwarzen Nachfolgeknotens.
				return hoehe_des_roten_Knotens;//Es wird die Hohe des roten Knotens zuruck gegeben
			}
		}
		//einer der Nachfolger ist rot, der andere schwarz 
		else if (linker_nachfolger->getRed() == true && rechter_nachfolger->getRed() == false) {
			int hoehe_des_roten_Knotens = proofRBCriterion(linker_nachfolger);//rekursiver Aufruf
			int hoehe_des_schwarzen_Knotens = proofRBCriterion(rechter_nachfolger);//rekursiver Aufruf
			if (hoehe_des_roten_Knotens - hoehe_des_schwarzen_Knotens == 1) {//Die Hohe des roten Knotens muss um eins hoher sein als die Hohe des schwarzen Nachfolgeknotens.
				return hoehe_des_roten_Knotens;//Es wird die Hohe des roten Knotens zuruck gegeben
			}
		}
	}
}

void Tree::printLevelOrder(void) {
	queue<TreeNode*> nodeQueue;//Schwarze Knoten werden hier gespeichert
	queue<int> niveauQueue;//Das Niveau des Knoten
	int anfangs_niveau = 0;
	//Anfang	
	nodeQueue.push(anker);//Wurzel speichern
	niveauQueue.push(0);//Wurzel hat das Niveau 0

	while (nodeQueue.empty() == false) {
		TreeNode* ptr = nodeQueue.front();//ptr zeigt auf dem ersten Element der Warteschlange	
		if (niveauQueue.front() == 0 || niveauQueue.front() > anfangs_niveau) {//Wir aendern das Niveau
			cout << endl << "Niv. " << niveauQueue.front() << ": ";
			if (niveauQueue.front() > anfangs_niveau) {
				anfangs_niveau++;
			}
		}
		cout << "(";//Ausgabe beginnt hier
		// Linker Nachfolger
		if (ptr->getLeft() != nullptr) { // Der linke Nachfolger existiert		
			if (ptr->getLeft()->getRed() == false) { // Der linke Nachfolger ist schwarz
				nodeQueue.push(ptr->getLeft());
				niveauQueue.push(anfangs_niveau + 1);
			}
			else { // Der linke Nachfolger ist rot
				cout << ptr->getLeft()->getNodeOrderID() << ", ";
				// Wenn der rote Nachfolger keinen linken Nachfolger hat
				if (ptr->getLeft()->getLeft() != nullptr) {
					nodeQueue.push(ptr->getLeft()->getLeft());
					niveauQueue.push(anfangs_niveau + 1);
				}
				// Wenn der rote Nachfolger keinen rechten Nachfolger hat
				if (ptr->getLeft()->getRight() != nullptr) {
					nodeQueue.push(ptr->getLeft()->getRight());
					niveauQueue.push(anfangs_niveau + 1);
				}
			}
		}//Der linke Nachfolger existiert nicht

		cout << ptr->getNodeOrderID();//Der jetztige Knoten

		if (ptr->getRight() != nullptr) { //Der rechte Nachfolger existiert
			if (ptr->getRight()->getRed() == false) { //Der rechte Nachfolger ist schwarz
				nodeQueue.push(ptr->getRight());
				niveauQueue.push(anfangs_niveau + 1);
			}
			else {//Der rechte Nachfolger ist rot
				cout << ", " << ptr->getRight()->getNodeOrderID();
				// Wenn der rote Nachfolger keinen linken Nachfolger hat
				if (ptr->getRight()->getLeft() != nullptr) {
					nodeQueue.push(ptr->getRight()->getLeft());
					niveauQueue.push(anfangs_niveau + 1);
				}
				// Wenn der rote Nachfolger keinen rechten Nachfolger hat
				if (ptr->getRight()->getRight() != nullptr) {
					nodeQueue.push(ptr->getRight()->getRight());
					niveauQueue.push(anfangs_niveau + 1);
				}
			}
		}//Der rechte Nachfolger existiert nicht

		cout << ")";//Neue Ausgabe dran

		niveauQueue.pop();
		nodeQueue.pop();
	}
}

void Tree::printLevelOrder(int parameter) {

	queue<TreeNode*> nodeQueue;
	queue<int> niveauQueue;
	int anfangs_niveau = 0;
	nodeQueue.push(anker);
	niveauQueue.push(0);
	while (nodeQueue.empty() == false) {
		TreeNode* ptr = nodeQueue.front();
		if (niveauQueue.front() == 0 || niveauQueue.front() > anfangs_niveau) {
			if (niveauQueue.front() > parameter) {
				return;
			}
			if (niveauQueue.front() == parameter) {//Die Knoten zum Niveau parameter
				cout << endl << "Niv. " << niveauQueue.front() << ": ";
			}
			if (niveauQueue.front() > anfangs_niveau) {
				anfangs_niveau++;
			}
		}
		if (niveauQueue.front() == parameter) {//Die Knoten zum Niveau parameter
			cout << "(";
		}
		if (ptr->getLeft() != nullptr)
		{
			if (ptr->getLeft()->getRed() == false) {
				nodeQueue.push(ptr->getLeft());
				niveauQueue.push(anfangs_niveau + 1);

			}
			else {
				if (niveauQueue.front() == parameter) {//Die Knoten zum Niveau parameter
					cout << ptr->getLeft()->getNodeOrderID() << ", ";
				}
				if (ptr->getLeft()->getLeft() != nullptr) {
					nodeQueue.push(ptr->getLeft()->getLeft());
					niveauQueue.push(anfangs_niveau + 1);
				}
				if (ptr->getLeft()->getRight() != nullptr) {
					nodeQueue.push(ptr->getLeft()->getRight());
					niveauQueue.push(anfangs_niveau + 1);
				}
			}
		}
		if (niveauQueue.front() == parameter) {//Die Knoten zum Niveau parameter
			cout << ptr->getNodeOrderID();
		}
		if (ptr->getRight() != nullptr) {
			if (ptr->getRight()->getRed() == false) {
				nodeQueue.push(ptr->getRight());
				niveauQueue.push(anfangs_niveau + 1);
			}
			else {
				if (niveauQueue.front() == parameter) {//Die Knoten zum Niveau parameter
					cout << ", " << ptr->getRight()->getNodeOrderID();
				}
				if (ptr->getRight()->getLeft() != nullptr) {
					nodeQueue.push(ptr->getRight()->getLeft());
					niveauQueue.push(anfangs_niveau + 1);
				}
				if (ptr->getRight()->getRight() != nullptr) {
					nodeQueue.push(ptr->getRight()->getRight());
					niveauQueue.push(anfangs_niveau + 1);
				}
			}
		}
		if (niveauQueue.front() == parameter) {//Die Knoten zum Niveau parameter
			cout << ")";
		}
		niveauQueue.pop();
		nodeQueue.pop();
	}
}

void Tree::printAll(void) {
	TreeNode* k = anker;
	printPreorder(k);
}


void Tree::printPreorder(TreeNode* k) {
	// Ausgabe in Preorder
	if (k != nullptr) {
		cout << k->getNodeChronologicalID() << "\t| " << k->getName() << "\t| " << k->getAge() << "\t| " << k->getIncome() << "\t| " << k->getPostCode() << "\t |  " << k->getNodeOrderID() << "\t |  " << k->getRed() << endl;
		printInorder(k->getLeft());
		printInorder(k->getRight());
	}
}
void Tree::printInorder(TreeNode* k) {
	// Ausgabe in Preorder
	if (k != nullptr) {
		printInorder(k->getLeft());
		cout << k->getNodeChronologicalID() << "\t| " << k->getName() << "\t| " << k->getAge() << "\t| " << k->getIncome() << "\t| " << k->getPostCode() << "\t |  " << k->getNodeOrderID() << "\t |  " << k->getRed() << endl;
		printInorder(k->getRight());
	}
}
void Tree::printInorder(TreeNode* k, string Name, bool& yn) {
	// Ausgabe in Inorder
	if (k != nullptr) {
		if (k->getName() == Name) {
			cout << "ID: " << k->getNodeChronologicalID() << " , " << "Name: " << k->getName() << " , " << "Age: " << k->getAge() << " , " << "Income: " << k->getIncome() << " , " << "PostCode: " << k->getPostCode() << " , " << "OrderID: " << k->getNodeOrderID() << "Red: " << k->getRed() << endl;
			yn = true;
			return;
		}
		printInorder(k->getLeft(), Name, yn);
		printInorder(k->getRight(), Name, yn);
	}
}
void Tree::printPreorder(TreeNode* k, string Name, bool& yn) {
	// Ausgabe in Preorder
	if (k != nullptr) {
		if (k->getName() == Name) {
			cout << "ID: " << k->getNodeChronologicalID() << " , " << "Name: " << k->getName() << " , " << "Age: " << k->getAge() << " , " << "Income: " << k->getIncome() << " , " << "PostCode: " << k->getPostCode() << " , " << "OrderID: " << k->getNodeOrderID() << "Red: " << k->getRed() << endl;
			yn = true;
		}
		printInorder(k->getLeft(), Name, yn);
		printInorder(k->getRight(), Name, yn);
	}
}