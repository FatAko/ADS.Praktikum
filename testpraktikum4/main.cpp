#include <iostream>
#include <string>
#include <vector>
#include "sort.h"
using namespace std;

int main() {
	vector<int> arr;
	arr.push_back(39);
	arr.push_back(47);
	arr.push_back(15);
	arr.push_back(35);
	arr.push_back(83);
	arr.push_back(17);
	arr.push_back(12);
	arr.push_back(78);
	cout << "unsortiert:" << endl;
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr.at(i) << ", ";
	}
	cout << endl;

	int n = 8;
	vector<int> hibbard;
	for (int h = 1; h < n; h = 2 * h + 1)
		hibbard.push_back(h);

	for (int i = 0; i < hibbard.size(); i++)
	{
		cout << hibbard.at(i) << ", ";
	}
	cout << endl;

	//ShellSort(arr,arr.size());
	//QuickSort(arr, 0,7);
	MergeSort(arr, 0, 7);
	cout << "sortiert:" << endl;
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr.at(i) << ", ";
	}
	cout << endl;

	system("PAUSE");
	return 0;
}