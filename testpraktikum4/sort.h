#pragma once
#include <vector>
using namespace std;

void ShellSort(vector<int>& a,int n);
void QuickSort(vector<int>& a, int p, int r);
int Partition(vector<int>& a, int p, int r);
void Merge(std::vector<int>& arr, int start, int middle, int end);
void MergeSort(std::vector<int>& arr, int start, int end);
