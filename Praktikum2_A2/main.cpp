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

int main()
{
    int result = Catch::Session().run();

    Tree* baum = new Tree();
    string name = "", eingabe = "";
    int alter = 0, plz = 0, orderID = 0;
    double einkommen = 0.0;

    cout << "====================================" << endl;
    cout << "ADS-Praktikum 2.2" << endl;
    cout << "====================================" << endl;
    cout << "1) Datensatz einfuegen, manuell" << endl;
    cout << "2) Datensatz einfuegen, CSV Import" << endl;
    cout << "3) Datensatz loeoschen" << endl;
    cout << "4) Datensatz suchen" << endl;
    cout << "5) Gesamte Datenstruktur anzeigen" << endl;
    cout << "6) Beenden" << endl;
    cout << "?>" << endl;
    cout << endl;

    while (true)
    {
        vector<TreeNode> liste;
        cout << "?> ";
        cin >> eingabe;
        if (eingabe == "1")
        {
            cout << "+ Bitte geben Sie den Datensatz ein" << endl;
            cout << "Name ?> "; cin >> name;
            cout << "Alter ?> "; cin >> alter;
            cout << "Einkommen ?> "; cin >> einkommen;
            cout << "PLZ ?> "; cin >> plz;
            baum->addNode(name, alter, einkommen, plz);
            cout << "+ Ihr Datensatz wurde eingefuegt" << endl; cout << endl;
        }
        else if (eingabe == "2")
        {
            mainscreen_addTreeCSV(baum);
            cout << endl;
        }
        else if (eingabe == "3")
        {
            cout << "+ Bitte geben Sie den zu loeschenden Datensatz an" << endl;
            cout << "?> "; cin >> orderID;
            baum->deleteNode(orderID);
            cout << "+ Datensatz wurde geloescht." << endl; cout << endl;
        }
        else if (eingabe == "4")
        {
            cout << "+ Bitte geben Sie den zu suchenden Datensatz an" << endl;
            cout << "Name ?> ";
            cin >> name;
            liste = baum->getNodes(name);
            printNodeList(liste);
            cout << endl; cout << endl;
        }
        else if (eingabe == "5")
        {
            cout << "ID | Name | Age | Income | PostCode | OrderID" << endl;
            cout << "---+------------+-------+-----------+-------+-------" << endl;
            baum->printAll();
            cout << endl; cout << endl;
        }
        else if (eingabe == "6")
            break;
    }
    system("PAUSE");
    return 0;
}

