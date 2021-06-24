#include <assert.h>
#include "DijkstraSP.h"

/**
 * Füge eine Kante mit minimalen Kosten hinzu, die von einem
 * Baumknoten zu einem Nicht-Baumknoten verläuft und deren
 * Ziel w dem Startknoten s am nächsten ist.
 *
 * \param[in]  G		Kantengewichteter-Digraph
 * \param[in]  v		Zielknoten
 */
void DijkstraSP::relax(EdgeWeightedDigraph G, int v)
{
	// untersuche alle adjazenten Knoten zu v und überprüfe deren Wegekosten 
	// Digraph : gerichteter Graph
	 // Füge eine Kante mit minimalen Kosten hinzu, die von einem Baumknoten zu einem Nicht-Baumknoten verläuft und deren Ziel w dem Startknoten s am nächsten ist.
	std::vector<DirectedEdge> edges = G[v]; // adjazente Knoten zum Knoten v
	// foreach loop
	for (DirectedEdge e : edges) {
		//v -> w
		//w ist der Zielknoten des adjazenten Knotens zum Knoten v
		int w = e.to(); // e.top();	
		//std::map<int, DirectedEdge> edgeTo;			// nächste Kante, die die geringsten nächsten Kosten zu s hat
		//std::vector<double> distToVect;				// Gewichte der Pfade von s	
		//distTo[v], das die Länge des kürzesten bekannten Pfad von s nach v ist.
		if (distToVect[w] > distToVect[v] + e.weight()) {
			//Ein kürzeren Weg ist gefunden
			//Eine Kante v -> w wird relaxiert, wenn der kürzeste Weg von s nach w über die Kante von v nach w verläuft.
			distToVect[w] = distToVect[v] + e.weight();
			edgeTo[w] = e;
			if (pq.contains(w)) pq.change(w, distToVect[w]);
			else pq.push(w, distToVect[w]);
		}
	}
}

/**
 * Fuert den Dijkstra Algorithmus von s, im Graph G aus.
 *
 * \param[in]  G		Kantengewichteter-Digraph
 * \param[in]  s		Startknoten
 */
DijkstraSP::DijkstraSP(EdgeWeightedDigraph G, int s)
{
	// distToVect[v] : Abstände vom Startvertex zu v
	// V : Anzahl Knoten von G 
	distToVect.resize(G.getV());
	for (int v = 0; v < G.getV(); v++) {
		//Wofür steht die Konstante DBL_MAX ?
		//Initialisierung 
		distToVect[v] = DBL_MAX;
	}
	//die Länge des kürzesten bekannten Pfad von s nach s ist 0.0
	distToVect[s] = 0.0;
	// pq für den Dijkstra Algorithmus
	// red : on pq
	// black : on SPT 
	pq.push(s, 0.0);
	while (!pq.empty()) {
		// Füge immer eine Kante mit minimalen Pfadkosten zu s hinzu
		int min_node = pq.top().value;
		pq.pop();
		// Füge immer eine Kante mit minimalen Pfadkosten zu s der PQ hinzu
		relax(G, min_node);
	}
}

/**
 * Gibt die Distanz von s zum Knoten v zurueck
 *
 * \param[in]  v		Zielknoten
 * \return Summe der Gewichte auf dem Pfad zu v
 */
double DijkstraSP::distTo(int v) const
{
	return distToVect.at(v);
}

/**
 * Gibt zurueck ob es einen Pfad zu v von s aus gibt
 *
 * \param[in]  v		Zielknoten
 * \return true, wenn es einen Pfad von s nach v gibt, sonst false
 */
bool DijkstraSP::hasPathTo(int v) const
{
	if (distTo(v) != DBL_MAX) {
		return true;
	}
	return false;
}

/**
 * Gibt den Pfad von s nach v als Vektor zurueck
 *
 * \param[in]  v		Zielknoten
 * \return Vektor mit allen Kanten des Pfades von s nach v
 */
std::vector<DirectedEdge> DijkstraSP::pathTo(int v) 
{
	std::vector<DirectedEdge>path;
	//path.push_back(edgeTo[0]);
	for (const auto& item : edgeTo)
	{
		//cout << item.first << " -> " << item.second.from() << ", " << item.second.to() << std::endl;
		path.push_back(item.second);
	}
	//Vektor durchlaufen
	std::vector<DirectedEdge>pathValues;
	for (int j = path.size() - 1; j >= 0; --j) {
		if (path.at(j).to() == v) {
			pathValues.push_back(path.at(j));
			v = path.at(j).from();
		}
	}
	reverse(pathValues.begin(), pathValues.end());
	return pathValues;
}
