/*************************************************
 * ADS Praktikum 2.2
 * main.cpp
 *
 *************************************************/
#define CATCH_CONFIG_RUNNER
#include "Tree.h"
#include "catch.h"
#include <iostream>

using namespace std;

///////////////////////////////////////
// Hilfsmethoden fürs Menü hier:



/***************************
 ** Vorgegebene  Funktion **
 ***************************
   "mainscreen_addTreeCSV"

Importiert CSV Datei in bestehenden Baum.
Bei Aufruf in der main() Methode, muss der Pointer auf den Anker des Baums, als Parameter übergeben werden.
Es wird die im gleichen Verzeichnis liegende Datei "ExportZielanalyse.csv" geladen.
****************************/
void mainscreen_addTreeCSV(Tree*& ref)
{
	char j;
	cout << "+ Moechten Sie die Daten aus der Datei ExportZielanalyse.csv "
		"importieren(j / n) ?> ";
	cin >> j;
	if (j == 'j')
	{
		ifstream csvread;
		csvread.open("ExportZielanalyse.csv", ios::in);
		if (!csvread.is_open())
			cerr << "Fehler beim Lesen!" << endl;
		else
		{
			string name, age, postcode, income;

			while (!csvread.eof())
			{
				getline(csvread, name, ';');
				getline(csvread, age, ';');
				getline(csvread, income, ';');
				getline(csvread, postcode, '\n');
				ref->addNode(name, stoi(age), stod(income), stoi(postcode));
			}
			csvread.close();
		}
		cout << "+ Daten wurden dem Baum hinzugefuegt." << endl;
	}
}
//
///////////////////////////////////////
int main()
{

	int result = Catch::Session().run();

	///////////////////////////////////////
	// Ihr Code hier:
	string Name;
	int Age;
	double Income;
	int PostCode;
	int Auswahl;
	char jn;
	int niveau;
	int OrderID;
	cout << "1) Datensatz einfuegen, manuell" << endl;
	cout << "2) Datensatz einfuegen, CSV Import" << endl;
	cout << "3) Suchen" << endl;
	cout << "4) Ausgabe in Preorder" << endl;
	cout << "5) Ausgabe in Levelorder" << endl;
	cout << "6) Ausgabe in Levelorder (mit Niveauauswahl)" << endl;
	Tree* baum = new Tree();
	bool weiter = true;
	while (weiter) {
		cout << "?> " <<endl;
		cin >> Auswahl;
		if (Auswahl == 1) {
			cout << "+ Bitte geben Sie die den Datensatz ein" << endl;
			cout << "Name ?> ";
			cin >> Name;
			cout << "Alter ?> ";
			cin >> Age;
			cout << "Einkommen ?> ";
			cin >> Income;
			cout << "PLZ ?> ";
			cin >> PostCode;
			baum->addNode(Name, Age, Income, PostCode);//Name Age Income PostCode
			cout << "+ Ihr Datensatz wurde eingefuegt" << endl;
		}
		else if (Auswahl == 2) {
			mainscreen_addTreeCSV(baum);
		}
		else if (Auswahl == 3) {
			cout << "+ Bitte geben Sie den zu suchenden Datensatz an" << endl;
			cout << "Name ?> ";
			cin >> Name;
			cout << "+ Fundstellen: " << endl;
			baum->searchNode(Name);
		}
		else if (Auswahl == 4) {
			cout << "ID      | Name  | Age   | Income|PostCode| OrderID| Red" << endl;
			cout << "--------+-------+-------+-------+--------+--------+-----" << endl;
			baum->printAll();
			cout << endl;
		}
		else if (Auswahl == 5) {
			cout << "Ausgabe in Levelorder als binarer Suchbaum:" << endl;
			cout << "ID      | Name  | Age   | Income|PostCode| OrderID| Red" << endl;
			cout << "--------+-------+-------+-------+--------+--------+-----" << endl;
		
			cout << endl << endl;
			cout << "Ausgabe in Levelorder als 234 - Baum:";
			baum->printLevelOrder();
			cout << endl << endl;
		}
		else {
			cout << "+ Bitte geben Sie die Niveauauswahl an:" << endl;
			cin >> niveau;
			baum->printLevelOrder(niveau);
			cout << endl << endl;
		}
	}

	//
	///////////////////////////////////////
	system("PAUSE");

	return 0;
}
