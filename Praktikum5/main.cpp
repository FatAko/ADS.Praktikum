#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include <iostream>
#include "EdgeWeightedGraph.h"
#include "PrimMST.h"
#include "Graphsearch.h"
#include "KruskalMST.h"
#include "DijkstraSP.h"
#include <string>

using namespace std;

int main() {
	// Starte Unit-Tests
	Catch::Session().run();
	
	string eingabe = "";
	bool dOderG = false; //Digraph falls 1
	int graphNr = 0;
	int startKnoten = -1;
	int zielKnoten = -1;
	double laenge = 0.0;

	EdgeWeightedGraph* graph = nullptr;
	EdgeWeightedDigraph* digraph = nullptr;
	vector<bool>marked;
	vector<int>edgeTo;
	bool zusammenhaengend = false;


	while (true)
	{
		cout << "Praktikum 5: Graphenalgorithmen:" << endl;
		cout << "1) Graph einlesen" << endl;
		cout << "2) Tiefensuche" << endl;
		cout << "3) Breitensuche" << endl;
		cout << "4) MST nach Prim" << endl;
		cout << "5) MST nach Kruskal" << endl;
		cout << "6) Kuerzeste Wege nach Dijkstra" << endl;
		cout << "7) Ausgabe der Adjazenzliste" << endl;
		cout << "8) Programm beenden" << endl;
		cout << "Weiter mit beliebiger Eingabe ..." << endl;
		cout << "?>";

		cin >> eingabe;
		if (eingabe == "1") {
			cout << "Graph oder Digraph? (G = 0/D = 1)" << endl;
			cout << "?>";
			cin >> dOderG;
			cout << "Welcher Graph soll eingelesen werden? (1,2,3)" << endl;
			cout << "?>";
			cin >> graphNr;
			if (graphNr == 1) {
				if (dOderG) {
					digraph = new EdgeWeightedDigraph("graph1.txt");
				} else graph = new EdgeWeightedGraph("graph1.txt");
			}
			else if (graphNr == 2) {
				if (dOderG) {
					digraph = new EdgeWeightedDigraph("graph2.txt");
				} else graph = new EdgeWeightedGraph("graph2.txt");
			}
			else if (graphNr == 3) {
				if (dOderG) {
					digraph = new EdgeWeightedDigraph("graph3.txt");
				} else graph = new EdgeWeightedGraph("graph3.txt");
			}
			else {
				cout << "Ungueltige Eingabe" << endl;
				cout << "?>";
				continue;
			}
		}else if (eingabe == "2") {
			if (graph != nullptr) {
			
				while (true)
				{
					cout << "Gib einen Startknoten zwischen 0 und " << graph->getV() - 1 << " an." << endl;
					cout << "?>";
					cin >> startKnoten;
					if (startKnoten >= 0 && startKnoten < graph->getV())
						break;
				}
				cout << "Tiefensuche (Depth-First-Search (DFS)) - Startknoten: " << startKnoten << endl;
				cout << "Besuchsreihenfolge:" << endl;
				zusammenhaengend = Graphsearch::DFS(*graph, startKnoten, marked, edgeTo);
				if (zusammenhaengend)
					cout << endl << "Graph ist zusammenhaengend" << endl;
				else
					cout << endl << "Graph ist nicht zusammenhaengend" << endl;
			}
			else
				cout << "Keinen Graphen geladen" << endl;
			cout << "?>";
			continue;

		}else if (eingabe == "3") {
			if (graph != nullptr) {

				while (true)
				{
					cout << "Gib einen Startknoten zwischen 0 und " << graph->getV() - 1 << " an." << endl;
					cout << "?>";
					cin >> startKnoten;
					if (startKnoten >= 0 && startKnoten < graph->getV())
						break;
				}
				cout << "Breitensuche (Breadth-First-Search (DFS)) - Startknoten: " << startKnoten << endl;
				cout << "Besuchsreihenfolge:" << endl;
				zusammenhaengend = Graphsearch::BFS(*graph, startKnoten, marked, edgeTo);
				if (zusammenhaengend)
					cout << endl << "Graph ist zusammenhaengend" << endl;
				else
					cout << endl << "Graph ist nicht zusammenhaengend" << endl;
			}
			else
				cout << "Keinen Graphen geladen" << endl;
			cout << "?>";
			continue;

		}else if (eingabe == "4") {
			if (graph != nullptr) {
				while (true)
				{
					cout << "Gib einen Startknoten zwischen 0 und " << graph->getV() - 1 << " an." << endl;
					cout << "?>";
					cin >> startKnoten;
					if (startKnoten >= 0 && startKnoten < graph->getV())
						break;
				}
				PrimMST prim(*graph, startKnoten);
				cout << "Minimaler Spannbaum (MST) nach Prim: " << endl;
				cout << "Gewicht: " << prim.weight() << endl;
				cout << "Adjazenzliste: " << endl;
				/*for (int i = 0; i < graph->getV(); i++) {
					vector<Edge>adj = graph->getAdj(i);
					cout << i;
					for (int kante = 0; kante < adj.size(); kante++) {
						cout << " -> " << adj[kante].other(i) << " [" << adj[kante].weight() << "]";
					}
					cout << endl;
				}*/
				for (int i2 = 0, zeile = 0; i2 < prim.edges().size(); i2++) {

					for (int i = 0; i < prim.edges().size(); i++) {

						if (prim.edges()[i].either() == i2) {
							cout << i2;
							zeile++;
							break;
						}
					}
					for (int i = 0; i < prim.edges().size(); i++) {

						if (prim.edges()[i].either() == i2)
							cout << " -> " << prim.edges()[i].other(i2) << "[" << prim.edges()[i].weight() << "] ";
					}
					if (zeile != 0) {
						cout << endl;
					}
					zeile = 0;
				}
				cout << endl;
			}
			else
				cout << "Keinen Graph geladen" << endl;
			cout << "?>";
			continue;

		}else if (eingabe == "5") {
			if (graph != nullptr) {
				KruskalMST kruskal(*graph);
				cout << "Minimaler Spannbaum (MST) nach kruskal: " << endl;
				cout << "Gewicht: " << kruskal.weight() << endl;
				cout << "Adjazenzliste: " << endl;
				/*for (int i = 0; i < graph->getV(); i++) {
					vector<Edge>adj = graph->getAdj(i);
					cout << i;
					for (int j = 0; j < adj.size(); j++) {
						cout << " -> " << adj[j].other(i) << " [" << adj[j].weight() << "]";
					}
					cout << endl;
				}*/
				for (int i2 = 0, zeile = 0; i2 < kruskal.edges().size(); i2++) {
					for (int i = 0; i < kruskal.edges().size(); i++) {
						if (kruskal.edges()[i].either() == i2) {
							cout << i2;
							zeile++;
							break;
						}
					}
					for (int i = 0; i < kruskal.edges().size(); i++) {
						if (kruskal.edges()[i].either() == i2)
							cout << " -> " << kruskal.edges()[i].other(i2) << "[" << kruskal.edges()[i].weight() << "] ";
					}
					if (zeile != 0) {
						cout << endl;
					}
					zeile = 0;
				}
				cout << endl;
			}
			else
				cout << "Keinen Graph geladen" << endl;
			cout << "?>";
			continue;

		}else if (eingabe == "6") {

			if (digraph != nullptr) {

				while (true)
				{
					cout << "Gib einen Startknoten zwischen 0 und " << digraph->getV() - 1 << " an." << endl;
					cout << "?>";
					cin >> startKnoten;

					cout << "Gib einen Zielknoten zwischen 0 und " << digraph->getV() - 1 << " an." << endl;
					cout << "?>";
					cin >> zielKnoten;
					if ((startKnoten >= 0 && startKnoten < digraph->getV()) && (zielKnoten >= 0 && zielKnoten < digraph->getV()))
						break;
				}
				DijkstraSP dijkstra(*digraph, startKnoten);
				if (dijkstra.hasPathTo(zielKnoten)) {
					vector<DirectedEdge> path = dijkstra.pathTo(zielKnoten);
					cout << "Gewichtete Kanten des Graphen" << endl;
				
					vector<DirectedEdge> adj;
					for (int i = 0; i < digraph->getV(); i++) {
						adj = digraph->getAdj(i);
						cout << i;
						for (int j = 0; j < adj.size(); j++) {
							cout << " -> " << adj[j].to() << " [" << adj[j].weight() << "]";
						}
						cout << endl;
					}
					cout << "Kuerzester Weg(Dijkstra):" << endl;
					cout << "Start:  " << startKnoten << endl;
					cout << "Ziel:   " << zielKnoten << endl;
					if (path.size() > 0)
					{
						cout << "Pfad:   " << path[0].from();
						for (int i = 0; i < path.size(); i++) {
							cout << " [" << path[i].weight() << "]" << " -> " << path[i].to();
							laenge += path[i].weight();
						}
					}
					else
					{
						cout << "Pfad:   " << startKnoten << " -> " << zielKnoten << endl;
					}
					cout << endl << "Kosten: " << laenge << endl;

				}
				else {
					cout << "Kein Pfad vorhanden!" << endl;
					continue;
				}
			}
			else
				cout << "Keinen Graph geladen" << endl;
			continue;

		}else if (eingabe == "7") {
			
			if (graph != nullptr)
			{
				cout << "Ausgabe Graph" << endl;
				vector<Edge> adj;

				for (int i = 0; i < graph->getV(); i++) {
					adj = graph->getAdj(i);
					cout << i;
					for (int j = 0; j < adj.size(); j++) {
						cout << " -> " << adj[j].other(i) << " [" << adj[j].weight() << "]";
					}
					cout << endl;
				}
			}
			else cout << "Keinen Grapen geladen" << endl;
			if (digraph != nullptr)
			{
				cout << "Ausgabe Digraph" << endl;
				vector<DirectedEdge> adj;

				for (int i = 0; i < digraph->getV(); i++) {
					adj = digraph->getAdj(i);
					cout << i;
					for (int j = 0; j < adj.size(); j++) {
						cout << " -> " << adj[j].to() << " [" << adj[j].weight() << "]";
					}
					cout << endl;
				}
			}
			else cout << "Keinen Grapen geladen" << endl;
			
		}else if (eingabe == "8") {
			break;
		}else{
			cout << "?>";
			continue;
		}
		cout << "?>";
	}


	system("PAUSE");
	return 0;
}
