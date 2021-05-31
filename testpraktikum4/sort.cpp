#include "sort.h"
#include <vector>
#include <iostream>
using namespace std;


void QuickSort(vector<int>&a, int links, int rechts)
{
    int nachlinks = rechts; // Laufindex, der vom rechten Ende nach links laeuft
    int nachrechts = links; // Laufindex, der vom linken Ende nach rechts laeuft
    if (nachrechts < nachlinks)
    { // Pivotelement bestimmen
        // int pivot = feld[(nachrechts + nachlinks)/2];
        int pivot = a.at(links);

        while (nachrechts <= nachlinks)
        {    // Links erstes Element suchen, das
            // groesser oder gleich dem Pivotelement ist
            while ((nachrechts < rechts) && (a.at(nachrechts) < pivot))
                nachrechts++;

            // Rechts erstes Element suchen, das
            // kleiner oder gleich dem Pivotelement ist
            while ((nachlinks > links) && (a.at(nachlinks) > pivot))
                nachlinks--;

            // Wenn nicht aneinander vorbei gelaufen, Inhalte vertauschen
            if (nachrechts <= nachlinks)
            {
                int temp = a.at(nachrechts);
                a.at(nachrechts) = a.at(nachlinks);
                a.at(nachlinks) = temp;
                nachrechts++;
                nachlinks--;
            }
        } // end while

        // Linken Teil sortieren
        if (nachlinks > links) QuickSort(a,links, nachlinks);

        // Rechten Teil sortieren
        if (nachrechts < rechts) QuickSort(a,nachrechts, rechts);

    } // end if
}

void ShellSort(vector<int>& a, int n)
{
	vector<int> hibbard;
	for (int h = 1; h < n; h = 2 * h + 1)
		hibbard.push_back(h);

	for (int x = hibbard.size()-1; x >= 0; x--)
	{
		int gap = hibbard.at(x);
		for (int i = gap; i < n; i++)
		{
			int temp = a.at(i);
			int j = i;
			for (; j >= gap && a.at(j - gap) > temp; j -= gap)
			{
				a.at(j) = a.at(j - gap);
			}
			a.at(j) = temp;
		}
	}
}