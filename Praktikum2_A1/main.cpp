/*************************************************
* ADS Praktikum 2.1
* main.cpp
* 
*************************************************/
#define CATCH_CONFIG_RUNNER

#include <iostream>
#include <string>
#include "Ring.h"
#include "catch.h"

using namespace std;


int main()
{
	int result = Catch::Session().run();
	int eingabe = 0;
	string beschreibung = "", daten = "";
	Ring backupRing;
	RingNode* node;
	cout << "========================================" << endl;
	cout << "SuperBackUp - Organizer" << endl;
	cout << "========================================" << endl;
	cout << "1) Backup anlegen" << endl;
	cout << "2) Backup suchen" << endl;
	cout << "3) Alle Backups suchen" << endl;
	cout << endl;
	while (true)
	{
		cout << "?> ";
		cin >> eingabe;
		switch (eingabe)
		{
		case 1:
			cout << "+Neuen Datensatz anlegen" << endl;
			cout << "Beschreibung ?> ";
			cin.ignore();
			getline(cin, beschreibung);
			cout << "Daten ?> ";
			getline(cin, daten);
			backupRing.addNewNode(beschreibung,daten);
			cout << "+Ihr Datensatz wurde hinzugefuegt." << endl;
			cout << endl;
			break;
		case 2:
			cout << "+Nach welchen Daten soll gesucht werden?" << endl;
			cout << "?> ";
			cin.ignore();
			getline(cin, daten);
			if (backupRing.search(daten))
			{
				node = backupRing.getNode(daten);
				cout << "+Gefunden in Backup: Alter = " << node->getAge() << ", Beschreibung: " << node->getDescription() << ", Daten: " << node->getData() << endl;
				cout << endl;
				break;
			}
			else
			{
				cout << "+Datensatz konnte nicht gefunden werden." << endl;
				cout << endl;
				break;
			}
		case 3:
			cout << endl;
			backupRing.print();
			cout << endl;
			break;
		default:
			break;
		}
	}

	system("Pause");
	return 0;
}
