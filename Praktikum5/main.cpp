#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include <iostream>
#include "EdgeWeightedGraph.h"
#include "PrimMST.h"
#include "Graphsearch.h"
#include "KruskalMST.h"
#include "DijkstraSP.h"

using namespace std;

void adjazenzliste(EdgeWeightedDigraph* digraph);
void adjazenzliste(EdgeWeightedGraph* graph);

int main() {
	// Starte Unit-Tests
	Catch::Session().run();

	int graph = -1, dia = -1;
	bool diag = false;
	int auswahl = -1;
	EdgeWeightedGraph* g = nullptr;
	EdgeWeightedDigraph* d = nullptr;

	cout << "Praktikum 5: Graphenalgorithem" << endl
		<< "1) Graph einlesen" << endl
		<< "2) Tiefensuche " << endl
		<< "3) Breitensuche" << endl
		<< "4) MST nach Prim" << endl
		<< "5) MST nach Kruskal" << endl
		<< "6) Kuerzeste Wege nach Dijkstra" << endl
		<< "7) Ausgabe der Adjazenzliste" << endl
		<< "8) Programm beenden" << endl
		<< "Weiter mit beliebiger Eingabe" << endl
		<< "?>";
	while (true) {
		cin >> auswahl;
		switch (auswahl) {
		case 1:
			cout << "Als Diagraph(0) oder Graph(1) ? " << endl
				<< "?>";
			cin >> dia;
			switch (dia) {
			case 0:
				dia = true;
				break;
			case 1:
				dia = false;
				break;
			default:
				cout << "Falscher Wert" << endl;
				break;
			}
			cout << "Welcher Graph soll eingelesen werden (1,2 oder 3) ? " << endl
				<< "?>";
			cin >> graph;

			switch (graph) {
			case 1:
				if (dia)
					d = new EdgeWeightedDigraph("graph1.txt");
				else
					g = new EdgeWeightedGraph("graph1.txt");
				break;
			case 2:
				if (dia)
					d = new EdgeWeightedDigraph("graph2.txt");
				else
					g = new EdgeWeightedGraph("graph2.txt");
				break;
			case 3:
				if (dia)
					d = new EdgeWeightedDigraph("graph3.txt");
				else
					g = new EdgeWeightedGraph("graph3.txt");
				break;
			default:
				graph = -1;
				cout << "Gib eine Zahl zwischen 1 und 3 ein!" << endl;
				break;
			}
			break;


		case 2:
			if (g != nullptr) {
				int startKnoten = -1;
				do {
					cout << "Gib eine Zahl zwischen 0 und " << g->getV() - 1 << " an." << endl <<
						"?>";
					cin >> startKnoten;
				} while (startKnoten<0 || startKnoten>g->getV());
				vector<bool>marked;
				vector<int>edgeTo;
				bool verbunden = false;
				cout << "Tiefensuche (Depth-First-Search (DFS)) - Startknoten: " << startKnoten << endl
					<< "Besuchsreihenfolge: ";
				verbunden = Graphsearch::DFS(*g, startKnoten, marked, edgeTo);

				if (verbunden)
					cout << endl << "Graph ist zusammenhaengend" << endl;
				else
					cout << endl << "Graph ist nicht zusammenhaengend" << endl;
			}
			else
				cout << "Keinen Graph geladen" << endl;
			system("PAUSE");
			cout << endl << endl << endl;
			break;
		case 3:
			if (g != nullptr) {
				int startKnoten = -1;
				do {
					cout << "Gib eine Startknoten zwischen 0 und " << g->getV() - 1 << " an." << endl
						<< "?>";
					cin >> startKnoten;
				} while (startKnoten<0 || startKnoten>g->getV());
				vector<bool>marked;
				vector<int>edgeTo;
				bool verbunden = false;
				cout << "Breitensuche (Breadth-First-Search (BFS)) - Startknoten: " << startKnoten << endl
					<< "Besuchsreihenfolge: ";
				verbunden = Graphsearch::BFS(*g, startKnoten, marked, edgeTo);

				if (verbunden)
					cout << endl << "Graph ist zusammenhaengend" << endl;
				else
					cout << endl << "Graph ist nicht zusammenhaengend" << endl;
			}
			else
				cout << "Keinen Graph geladen" << endl;
			system("PAUSE");
			cout << endl << endl << endl;
			break;
		case 4:
			if (g != nullptr) {
				int startKnoten = -1;
				do {
					cout << "Gib einen Startknoten zwischen 0 und " << g->getV() - 1 << " an." << endl
						<< "?>";
					cin >> startKnoten;
				} while (startKnoten<0 || startKnoten>g->getV());
				PrimMST prim(*g, startKnoten);
				cout << "Minimaler Spannbaum (MST) nach Prim: " << endl
					<< "Gewicht: " << prim.weight() << endl
					<< "Adjazenzliste: " << endl;

				for (int knoten = 0; knoten < g->getV(); knoten++) {
					vector<Edge>adj = g->getAdj(knoten);
					cout << knoten;
					for (int kante = 0; kante < adj.size(); kante++) {
						cout << " -> " << adj[kante].other(knoten) << " [" << adj[kante].weight() << "]";
					}
					cout << endl;
				}
			}
			else
				cout << "Keinen Graph geladen" << endl;
			system("PAUSE");
			cout << endl << endl << endl;
			break;
		case 5:
			if (g != nullptr) {
				KruskalMST kruskal(*g);
				cout << "Minimaler Spannbaum (MST) nach Kruskal: " << endl
					<< "Gewicht: " << kruskal.weight() << endl
					<< "Adjazenzliste: " << endl;
				for (int knoten = 0; knoten < g->getV(); knoten++) {
					vector<Edge>adj = g->getAdj(knoten);
					cout << knoten;
					for (int kante = 0; kante < adj.size(); kante++) {
						cout << " -> " << adj[kante].other(knoten) << " [" << adj[kante].weight() << "]";
					}
					cout << endl;
				}
			}
			else
				cout << "Keinen Graph geladen" << endl;
			system("PAUSE");
			cout << endl << endl << endl;
			break;
		case 6:
			if (d != nullptr) {
				int startKnoten = -1, zielKnoten = -1;
				do {
					cout << "Gib einen Startknoten zwischen 0 und " << d->getV() - 1 << " an." << endl
						<< "?>";
					cin >> startKnoten;
					cout << "Gib einen Zielknoten zwischen 0 und " << d->getV() - 1 << " an." << endl
						<< "?>";
					cin >> zielKnoten;

				} while ((startKnoten<0 || startKnoten>d->getV() && (zielKnoten<0 || zielKnoten>d->getV())));
				DijkstraSP dijkstra(*d, startKnoten);
				if (!dijkstra.hasPathTo(zielKnoten)) {
					cout << endl << "ACHTUNG!" << endl << "Zwischen diesen Knoten existert kein Weg!" << endl;
					break;

				}
				vector<DirectedEdge> path = dijkstra.pathTo(zielKnoten);
				double kosten = 0.0;
				cout << "Gewichtete Kanten des Graphen" << endl;
				adjazenzliste(d);
				// Weg anzeigen und Kosten ermitteln
				cout << "Kuerzester Weg(Dijkstra):" << endl
					<< "Start:  " << startKnoten << endl
					<< "Ziel:   " << zielKnoten << endl
					<< "Pfad:    " << path[0].from();
				for (int kante = 0; kante < path.size(); kante++) {
					cout << " [" << path[kante].weight() << "]" << " -> " << path[kante].to();
					kosten += path[kante].weight();
				}
				cout << endl << "Kosten: " << kosten << endl;
			}

			else
				cout << "Keinen Graph geladen" << endl;
			system("PAUSE");
			cout << endl << endl << endl;
			break;
		case 7:
			if (d != nullptr)
				cout << "Diagraph ist geladen(1)" << endl;
			else
				cout << "Diagraph ist nicht geladen" << endl;
			if (g != nullptr)
				cout << "Graph ist geladen(0)" << endl;
			else
				cout << "Graph ist nicht geladen" << endl;
			cout << "Ihre Auswahl: ?>";
			cin >> auswahl;
			switch (auswahl) {
			case 0:
				adjazenzliste(g);
				break;
			case 1:
				adjazenzliste(d);
				break;
			}
			break;
		case 8:
			return 0;
		}
	}

	system("PAUSE");
	return 0;
}

void adjazenzliste(EdgeWeightedDigraph* digraph) {

	if (!digraph)
		cout << "Bitte zuerst einen Graphen laden!";
	else {
		vector<DirectedEdge> adj;

		for (int knoten = 0; knoten < digraph->getV(); knoten++) {
			adj = digraph->getAdj(knoten);
			cout << knoten;
			for (int kante = 0; kante < adj.size(); kante++) {
				cout << " -> " << adj[kante].to() << " [" << adj[kante].weight() << "]";
			}
			cout << endl;
		}
	}


}
void adjazenzliste(EdgeWeightedGraph* graph) {
	if (!graph)
		cout << "Bitte zuerst einen Graphen laden!";
	else {
		vector<Edge> adj;

		for (int knoten = 0; knoten < graph->getV(); knoten++) {
			adj = graph->getAdj(knoten);
			cout << knoten;
			for (int kante = 0; kante < adj.size(); kante++) {
				cout << " -> " << adj[kante].other(knoten) << " [" << adj[kante].weight() << "]";
			}
			cout << endl;
		}
	}
	cout << endl;
	system("pause");
	cout << endl << endl;
}
