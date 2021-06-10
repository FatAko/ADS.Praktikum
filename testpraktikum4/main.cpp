#include <iostream>
#include <string>
#include <vector>
#include "sort.h"
using namespace std;

int main() {
	vector<int> arr;
	arr.push_back(9);
	arr.push_back(26);
	arr.push_back(11);
	arr.push_back(20);
	arr.push_back(18);
	arr.push_back(5);
	arr.push_back(15);
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
	/*
	for (int i = 0; i < hibbard.size(); i++)
	{
		cout << hibbard.at(i) << ", ";
	}
	cout << endl;
	*/
	//ShellSort(arr,arr.size());
	QuickSort(arr, 0,arr.size()-1);
	//MergeSort(arr, 0, 7);
	cout << "sortiert:" << endl;
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr.at(i) << ", ";
	}
	cout << endl;

	system("PAUSE");
	return 0;
}