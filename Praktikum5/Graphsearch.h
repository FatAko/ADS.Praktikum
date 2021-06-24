#pragma once
#include "EdgeWeightedDigraph.h"
#include "EdgeWeightedGraph.h"
#include <iostream>
#include <queue>

namespace Graphsearch {

	/**
		* Fuehrt eine rekursive Tiefensuche im Graphen G,
		* ab dem Knoten v aus und markiert alle besuchten
		* Knoten in marked.
		* Alle besuchten Knoten werden ausgegeben.
		*
		* \param[in]	 G			Graph
		* \param[in]	 v			Startknoten
		* \param[in/out] marked		Bereits besuchte Knoten
		* \param[in/out] edgeTo		Vektor mit dem Nachfolgeknoten zu jedem Knoten
		*/
	void DFS_recursive(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo) {
		//Markiere aktuellen Knoten als besucht
		marked[v] = true;
		//Nachbarbarknoten des zu betrachtenden Knoten
		std::vector<Edge> nachbarn = G.getAdj(v);
		//Betrachte nacheinander die Nachbarn
		for (int i = 0; i < nachbarn.size(); i++)
		{
			//Wenn Nachbarknoten nicht markiert
			if (!marked[nachbarn[i].other(v)])
			{
				//Kante in edgeTo vektor abspeichern -> Reihenfolge Travesierung (edgeTo speichert letzten Knoten auf Pfad zu diesem Knoten)
				edgeTo[nachbarn[i].other(v)] = v;
				//Rekursiver Aufruf für den neuen Knoten
				DFS_recursive(G, nachbarn[i].other(v), marked, edgeTo);
			}
		}
	}

	/**
		* Fuehrt eine rekursive Tiefensuche im Graphen g, ab dem Knoten v aus.
		* Alle besuchten Knoten werden ausgegeben.
		* Starterfunktion zu DFS_recursive(EdgeWeigtedGraph, int, std::vector<bool>, std::vector<int>)
		*
		* \param[in]  G			Graph
		* \param[out] marked	Bereits besuchte Knoten
		* \param[out] edgeTo	Vektor mit dem Nachfolgeknoten zu jedem Knoten
		* \param[in]  v			Startknoten
		* \return	  true		Graph ist zusammenhaengend
		*			  false		Graph ist nicht zusammenhaengend
		*/

	bool DFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo) {

		marked.resize(G.getV(), false); //(G.getV(),false)
		edgeTo.resize(G.getV(), -1);
		//Alle Knoten als nicht besucht markieren und alle edgeTo Elemente auf -1
		for (int i = 0; i < G.getV(); i++)
		{
			marked[i] = false;
			edgeTo[i] = -1;
		}
		//Rekursive Tiefensuche mit Startknoten v
		DFS_recursive(G, v, marked, edgeTo);
		//Knotenliste durchlaufen -> falls ein Knoten als nicht besucht Markiert -> Graph nicht zusammenhängend
		for (int i = 0; i < G.getV(); i++)
		{
			if (!marked[i]) {
				return false;
			}
		}
		//Alle Knoten sind als besucht Markiert, also ist der Graph zusammenhängend
		return true;
	}

	/**
		* Fuehrt eine iterative Breitensuche im Graphen g, ab dem Knoten v aus.
		* Alle besuchten Knoten werden ausgegeben.
		*
		* \param[in]  G			Graph
		* \param[in]  v			Startknoten
		* \param[out] marked	Gibt an welche Knoten besucht wurden bei der Suche
		* \param[out] edgeTo	Gibt den Nachfolgerknoten eines Knoten an
		* \return	  true		Graph ist zusammenhaengend
		*			  false		Graph ist nicht zusammenhaengend
		*/
	bool BFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo) {
		marked.resize(G.getV(), false);
		edgeTo.resize(G.getV(), -1);
		//Alle Knoten als nicht besucht markieren und alle edgeTo Elemente auf -1
		for (int m = 0; m < G.getV(); m++)
		{
			marked[m] = false;
			edgeTo[m] = -1;
		}
		std::queue<int> q;
		//Startknoten in die Queue
		q.push(v);
		while (!q.empty())
		{
			//Das erste Element der Queue betrachten und dann entfernen
			int v = q.front();
			q.pop();
			if (marked[v]) //Falls Knoten als besucht markiert, überspringen
			{
				continue;
			}
			else //noch nicht besuchter Knoten
			{
				marked[v] = true;
				//Alle Nachbarn des betrachteten Knoten in die Queue, sofern sie noch nicht als besucht markiert wurden
				std::vector<Edge>neighbors = G.getAdj(v); 
				for (int i = 0; i < neighbors.size(); i++)
				{
					//Falls noch nicht markiert - > in die Queue
					if (!marked[neighbors[i].other(v)])
					{
						edgeTo[neighbors[i].other(v)] = v;
						q.push(neighbors[i].other(v));
					}

				}
			}
		}
		//Knotenliste durchlaufen -> falls ein Knoten als nicht besucht Markiert -> Graph nicht zusammenhängend
		for (int i = 0; i < G.getV(); i++) {
			if (!marked[i]) {
				return false;
			}
		}
		//Alle Knoten sind als besucht Markiert, also ist der Graph zusammenhängend
		return true;
	}
}
