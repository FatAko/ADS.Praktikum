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
            "importieren(j / n) ? >";
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
    cout << "====================================" << endl;
    cout << "ADS-Praktikum 2.2" << endl;
    cout << "====================================" << endl;
    int eingabe = 0, alter = 0, plz = 0, orderID = 0;
    string name = "";
    double einkommen = 0.0;
    cout << "1) Datensatz einfuegen, manuell" << endl;
    cout << "2) Datensatz einfuegen, CSV Import" << endl;
    cout << "3) Datensatz loeoschen" << endl;
    cout << "4) Datensatz suchen" << endl;
    cout << "5) Gesamte Datenstruktur anzeigen" << endl;
    cout << "6) Beenden" << endl;
    cout << "?>" << endl;
    cout << endl;
    Tree* baum = new Tree();
    while (true)
    {
        vector<TreeNode> liste;
        cout << "?> ";
        cin >> eingabe;
        switch (eingabe)
        {
        case 1:
            cout << "+ Bitte geben Sie den Datensatz ein" << endl;
            cout << "Name ?> ";
            cin >> name;
            cout << "Alter ?> ";
            cin >> alter;
            cout << "Einkommen ?> ";
            cin >> einkommen;
            cout << "PLZ ?> ";
            cin >> plz;
            baum->addNode(name, alter, einkommen, plz);
            cout << "+ Ihr Datensatz wurde eingefuegt" << endl;
            cout << endl;
            break;
        case 2:
            mainscreen_addTreeCSV(baum);
            break;
        case 3:
            cout << "+ Bitte geben Sie den zu loeschenden Datensatz an" << endl;
            cout << "?> ";
            cin >> orderID;
            baum->deleteNode(orderID);
            cout << "+ Datensatz wurde geloescht." << endl;
            break;
        case 4:
            cout << "+ Bitte geben Sie den zu suchenden Datensatz an" << endl;
            cout << "Name ?> ";
            cin >> name;
            liste = baum->getNodes(name);
            printNodeList(liste);
            cout << endl;
            cout << endl;
            cout << endl;
            //testtttt
            break;
        case 5:
            baum->printAll();
            cout << endl;
            cout << endl;
            break;
        case 6:
            break;
        default:
            break;
        }
    }
    
    system("PAUSE");

    return 0;
}

