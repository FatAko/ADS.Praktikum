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
	// Füge eine Kante mit minimalen Kosten hinzu, die von einem Baumknoten zu einem Nicht-Baumknoten verläuft und deren Ziel w dem Startknoten s am nächsten ist.
	std::vector<DirectedEdge> edges = G[v]; // adjazente Knoten zum Knoten v
	for (DirectedEdge e : edges) {
		
		int w = e.to(); 
		
		if (distToVect[w] > distToVect[v] + e.weight()) { //ist Weg kürzer?
			
			distToVect[w] = distToVect[v] + e.weight(); //überschribe mit neuem kurzerem Weg
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
	//Alle entfernungen auf "unendlich" setzen
	distToVect.resize(G.getV());
	for (int v = 0; v < G.getV(); v++) {
		distToVect[v] = DBL_MAX;
	}
	distToVect[s] = 0.0; //startknoten zu sich selbst
	pq.push(s, 0.0); //erste Entfernung eintragen
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
	std::vector<DirectedEdge> weg;
	//Falls kein Weg existiert -> return leeren Vektor
	if (!hasPathTo(v))
	{
		return weg;
	}
	//Startknoten bestimmen
	int st = edgeTo.begin()->first; 
	int s = edgeTo.at(st).from();

	std::vector<DirectedEdge> rückwaerts;
	while (v != s)
	{
		rückwaerts.push_back(edgeTo.at(v));
		v = edgeTo.at(v).from();
	}
	weg.resize(rückwaerts.size());
	//Weg von Hinten nach vorne
	for (int i = 0; i < rückwaerts.size(); i++)
	{
		weg[i] = rückwaerts[rückwaerts.size() - i - 1];
	}
	return weg;
}
