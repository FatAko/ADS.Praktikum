#include "sorting.h"


namespace sorting {

	//************
	// QuickSort *
	//************
	void QuickSort(vector<int>& a, int p, int r) {

		if (p < r) {
			int pivot = Partition(a, p, r);
			QuickSort(a, p, pivot - 1);//sortiere linke Seite
			QuickSort(a, pivot + 1, r);//sortiere rechte Seite
		}
	}
	int Partition(vector<int>& a, int p, int r) {

		int pivot = a[r];
		int i = p - 1;
		//Aufteilung des Arrays: kleinere Elemente als Pivot nach links und größere nach rechts
		//i immer aufschieben, wenn Element gefunden wurde, das kleiner als pivot ist
		for (int j = p; j <= r - 1; j++) {
			if (a[j] <= pivot) {
				i++;
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
		int temp = a[i+1];
		a[i+1] = a[r];
		a[r] = temp;
		//pos des pivot Elements 
		return i + 1;
	}
	//************
	// MergeSort *
	//************
	/*
	*  Der rekursive MergeSort-Algorithmus teilt das zu sortierende Array in 2 gleich große Teilarrays auf und
	*  sortiert diese rekursiv wieder mit dem MergeSort-Algorithmus.
	*/
	void MergeSort(vector<int>& a, vector<int>& b, int left, int right) {
		int middle = 0;
		if (left < right) {
			middle = (right + left) / 2; //Mitte bestimmen
			MergeSort(a, b, left, middle); //rechtes Teilarray
			MergeSort(a, b, middle + 1, right); //linkes Teilarray
			Merge(a, b, left, middle + 1, right); // Nach dem Mischen ist das Teilarray A[middle..right] sortiert.
		}
	}
	void Merge(vector<int>& a, vector<int>& b, int leftPos, int rightPos, int rightEnd) {
		int leftEnd = rightPos - 1;
		int tmpPos = leftPos; // Schreibindex für b
		int n = rightEnd - leftPos + 1; // Anzahl Elemente

		while (leftPos <= leftEnd && rightPos <= rightEnd) {

			//Vergleiche Elemente RT und LT: falls Wert von rechts übernommen wird, erhöhe rightpos. Das gleiche auf der anderen Seite
			// Das zu betrachtende Element ist links kleiner
			if (a[leftPos] <= a[rightPos]) {
				b[tmpPos] = a[leftPos];
				tmpPos++; //Schreibindex bei jeder Einfügeoperation um eine Stelle weiter
				leftPos++;
			}
			else { // Das zu betrachtende Element ist rechts kleiner
				b[tmpPos] = a[rightPos];
				tmpPos++;
				rightPos++;
			}
		}
		//Falls rechte TF fertig, übernehme den Rest der linken TF
		while (leftPos <= leftEnd) {
			b[tmpPos] = a[leftPos];
			tmpPos++; //Schreibindex bei jeder Einfügeoperation um eine Stelle weiter
			leftPos++;
		}
		//Falls linke TF fertig, übernehme den Rest der rechten TF
		while (rightPos <= rightEnd) {
			b[tmpPos] = a[rightPos];
			tmpPos++;
			rightPos++;
		}

		//Kopiere gemischtes sortiertes Array B in A zurück
		int i = 0;
		while (i < n) {
			a[rightEnd] = b[rightEnd];
			rightEnd--;
			i++;
		}
	}
	//************
	// Heapsort  *
	//************
	void HeapSort(vector<int>& a, int n) {
		//Aufbau des Arrays als Binbaum in Levelorder (MaxHeap)
		for (int i = (n / 2)-1; i >= 0; i--) {
			percDown(a, n, i); //Botton Up aufräumen gemäß MaxHeap
		}
		//Bei jedem Durchlauf ein element weniger betrachten. Das größte Element jeweils nach hinten schieben
		for (int i = n - 1; i > 0; i--) {
			// Größtes Element im betrachteten "Fenster" wird mit letztem getauscht
			int temp = a[0];
			a[0] = a[i];
			a[i] = temp;
			percDown(a, i, 0); // MaxHeap aufbauen, da Struktur durch Tausch zerstört
		}
	}
	void percDown(vector<int>& a, int n, int i) {
		int leftChild = 2 * i + 1, rightChild = 2 * i + 2, wurzel = i, temp = 0;
		//Betrachte linken Nachfolger: falls größer, dann neue Wurzel (vom Teilbaum)
		if (leftChild < n) {
			if (a[leftChild] > a[wurzel])
				wurzel = leftChild;
		}
		//Betrachte rechten Nachfolger: falls größer, dann neue Wurzel (vom Teilbaum)
		if (rightChild < n) {
			if (a[rightChild] > a[wurzel])
				wurzel = rightChild;
		}
		//Wenn neues größtes Element gefunden: mit Wurzel tauschen. Danach MaxHeap Struktur wiederherstellen
		if (wurzel != i) {
			temp = a[i];
			a[i] = a[wurzel];
			a[wurzel] = temp;
			percDown(a, n, wurzel);
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

		//Abstand aus Vektor auslesen: nächst kleinere hibbard Element
		for (int x = hibbard.size() - 1; x >= 0; x--) {
			int gap = hibbard.at(x); //Abstand festlegen

			//Das zu vergleichende Element: InsertionSort im Abstand H
			for (int i = gap; i < n; i++) {
				int temp = a.at(i);
				int j = i;

				//falls Element kleiner, richtige Pos einfügen / Vergleich der Elemente gemäß Abstand
				//Elemente werden solange vertauscht, bis der richtige Platz gefunden wurde
				for (; j >= gap && a.at(j - gap) > temp; j -= gap)
					a.at(j) = a.at(j - gap);

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





