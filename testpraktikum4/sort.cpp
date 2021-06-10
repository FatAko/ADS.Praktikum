#include "sort.h"
#include <vector>
#include <iostream>
using namespace std;

void Merge(std::vector<int>& arr, int start, int middle, int end) {

	std::vector<int> leftArray(middle - start + 1);
	std::vector<int> rightArray(end - middle);

	// fill in left array
	for (int i = 0; i < leftArray.size(); ++i)
		leftArray[i] = arr[start + i];

	// fill in right array
	for (int i = 0; i < rightArray.size(); ++i)
		rightArray[i] = arr[middle + 1 + i];

	/* Merge the temp arrays */

	// initial indexes of first and second subarrays
	int leftIndex = 0, rightIndex = 0;

	// the index we will start at when adding the subarrays back into the main array
	int currentIndex = start;

	// compare each index of the subarrays adding the lowest value to the currentIndex
	while (leftIndex < leftArray.size() && rightIndex < rightArray.size()) {
		if (leftArray[leftIndex] <= rightArray[rightIndex]) {
			arr[currentIndex] = leftArray[leftIndex];
			leftIndex++;
		}
		else {
			arr[currentIndex] = rightArray[rightIndex];
			rightIndex++;
		}
		currentIndex++;
	}

	// copy remaining elements of leftArray[] if any
	while (leftIndex < leftArray.size()) arr[currentIndex++] = leftArray[leftIndex++];

	// copy remaining elements of rightArray[] if any
	while (rightIndex < rightArray.size()) arr[currentIndex++] = rightArray[rightIndex++];
}

void MergeSort(std::vector<int>& arr, int start, int end) {
	// base case
	if (start < end) {
		// find the middle point
		int middle = (start + end) / 2;

		MergeSort(arr, start, middle); // sort first half
		MergeSort(arr, middle + 1, end);  // sort second half

		// merge the sorted halves
		Merge(arr, start, middle, end);
	}
}
/*
void QuickSort(vector<int>& a, int links, int rechts)
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
		if (nachlinks > links) QuickSort(a, links, nachlinks);

		// Rechten Teil sortieren
		if (nachrechts < rechts) QuickSort(a, nachrechts, rechts);

	} // end if
}
*/

void QuickSort(vector<int>& a, int p, int r) {

	if (p < r) {
		int pivot = Partition(a, p, r);
		QuickSort(a, p, pivot - 1);
		QuickSort(a, pivot + 1, r);
	}
}

int Partition(vector<int>& a, int p, int r) {

	int pivot = a[r];
	int i = p - 1;

	for (int j = p; j <= r - 1; j++) {
		if (a[j] <= pivot) {
			i++;
			swap(a[i], a[j]);
			for (int i = 0; i < a.size(); i++)
			{
				cout << a.at(i) << ", ";
			}
			cout << endl;
		}
	}
	swap(a[i + 1], a[r]);
	return i + 1;
}

void ShellSort(vector<int>& a, int n)
{
	vector<int> hibbard;
	for (int h = 1; h < n; h = 2 * h + 1)
		hibbard.push_back(h);

	for (int x = hibbard.size() - 1; x >= 0; x--)
	{
		int gap = hibbard.at(x);
		cout << "abstand: " << gap << endl;
		for (int i = gap; i < n; i++)
		{
			int temp = a.at(i);
			int j = i;
			for (; j >= gap && a.at(j - gap) > temp; j -= gap)
			{
				a.at(j) = a.at(j - gap);
			}
			a.at(j) = temp;

			for (int i = 0; i < a.size(); i++)
			{
				cout << a.at(i) << ", ";
			}
			cout << endl;

		}
	}

}
