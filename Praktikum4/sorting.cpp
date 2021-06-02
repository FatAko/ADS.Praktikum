#include "sorting.h"


namespace sorting {

	//************
	// QuickSort *
	//************      
	void QuickSort(vector<int> &arr, int left, int right) {
		
		int nachlinks = right; // Laufindex, der vom rechten Ende nach links laeuft
		int nachrechts = left; // Laufindex, der vom linken Ende nach rechts laeuft
		if (nachrechts < nachlinks)
		{ // Pivotelement bestimmen
			// int pivot = feld[(nachrechts + nachlinks)/2];
			int pivot = arr.at(right);

			while (nachrechts <= nachlinks)
			{    // Links erstes Element suchen, das
				// groesser oder gleich dem Pivotelement ist
				while ((nachrechts < right) && (arr.at(nachrechts) < pivot))
					nachrechts++;

				// Rechts erstes Element suchen, das
				// kleiner oder gleich dem Pivotelement ist
				while ((nachlinks > left) && (arr.at(nachlinks) > pivot))
					nachlinks--;

				// Wenn nicht aneinander vorbei gelaufen, Inhalte vertauschen
				if (nachrechts <= nachlinks)
				{
					int temp = arr.at(nachrechts);
					arr.at(nachrechts) = arr.at(nachlinks);
					arr.at(nachlinks) = temp;
					nachrechts++;
					nachlinks--;
				}
			} // end while

			// Linken Teil sortieren
			if (nachlinks > left) QuickSort(arr, left, nachlinks);

			// Rechten Teil sortieren
			if (nachrechts < right) QuickSort(arr, nachrechts, right);

		} // end if

	}

	//************
	// MergeSort *
	//************

	//***************************
	// implement mergesort here *
	//***************************


	void Merge(vector<int> &a, vector<int> &b, int low, int pivot, int high) {

		std::vector<int> leftArray(pivot - low + 1);
		std::vector<int> rightArray(high - pivot);

		// fill in left array
		for (int i = 0; i < leftArray.size(); ++i)
			leftArray.at(i) = a.at(low + i);

		// fill in right array
		for (int i = 0; i < rightArray.size(); ++i)
			rightArray.at(i) = a.at(pivot + 1 + i);

		/* Merge the temp arrays */

		// initial indexes of first and second subarrays
		int leftIndex = 0, rightIndex = 0;

		// the index we will start at when adding the subarrays back into the main array
		int currentIndex = low;

		// compare each index of the subarrays adding the lowest value to the currentIndex
		while (leftIndex < leftArray.size() && rightIndex < rightArray.size()) {
			if (leftArray[leftIndex] <= rightArray[rightIndex]) {
				a.at(currentIndex) = leftArray.at(leftIndex);
				leftIndex++;
			}
			else {
				a.at(currentIndex) = rightArray.at(rightIndex);
				rightIndex++;
			}
			currentIndex++;
		}

		// copy remaining elements of leftArray[] if any
		while (leftIndex < leftArray.size()) a.at(currentIndex++) = leftArray.at(leftIndex++);

		// copy remaining elements of rightArray[] if any
		while (rightIndex < rightArray.size()) a.at(currentIndex++) = rightArray.at(rightIndex++);
	}

	void MergeSort(vector<int> &a, vector<int> &b, int low, int high) {
		// base case
		if (low < high) {
			// find the middle point
			int middle = (low + high) / 2;

			MergeSort(a,b, low, middle); // sort first half
			MergeSort(a,b, middle + 1, high);  // sort second half

			// merge the sorted halves
			Merge(a,b, low, middle, high);
		}
	}



	//************
	// Heapsort  *
	//************

	void HeapSort(vector<int> &a, int n) {

		// build heapSort (rearrange array)
		for (int i = n / 2 - 1; i >= 0; i--) {
			percDown(a, n, i);
		}

		// one by one extract an element from heapSort
		for (int i = n - 1; i >= 0; i--) {
			// move current root to end
			int temp = a.at(0);
			a.at(0) = a.at(i);
			a.at(i) = temp;

			// call max heapify on the reduced heapSort
			percDown(a, i, 0);
		}

	}

	void percDown(std::vector<int>& a, int n, int i) {
		int max = i; // initialize max as root
		int left = 2 * i + 1;
		int right = 2 * i + 2;

		// if left child is larger than root
		if (left < n && a.at(left) > a.at(max))
			max = left;

		// if right child is larger than max
		if (right < n && a.at(right) > a.at(max))
			max = right;

		// if max is not root
		if (max != i) {
			// swap
			int temp = a.at(i);
			a.at(i) = a.at(max);
			a.at(max) = temp;

			// recursively heapify the affected sub-tree
			percDown(a, n, max);
		}
	}



	//************
	// Shellsort *
	//************
	void ShellSort(vector<int> &a, int n)
	{
		vector<int> hibbard;
		for (int h = 1; h < n; h = 2 * h + 1)
			hibbard.push_back(h);

		for (int x = hibbard.size() - 1; x >= 0; x--)
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


  void randomizeVector(vector<int> &array, int n) {
    array.resize(n);

    for(unsigned int i=0;i<array.size();i++)
      array[i]=rand() % 1000000;
  }


}





