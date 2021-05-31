#define CATCH_CONFIG_RUNNER
#include "catch.h"

#include <iostream>
#include <omp.h>

#include "sorting.h"
#include "hashtable.h"

using namespace std;

//benchmark functions
void benchmark_quicksort();


int main(int argc, char** argv) {

  Catch::Session().run();
  
  std::cout << "\nPress Enter to run measurement" << std::endl;
  std::cin.get();

  benchmark_quicksort();
  //***************************
  // run all benchmarks *
  //***************************

  return 0;
}




//executes benchmark for quicksort
void benchmark_quicksort() {

  //file stream
  ofstream quicksort_measurement;
  quicksort_measurement.open("quicksort.txt", ios::out | ios::app);

  //benchmark parameters / variables
  double dtime;
  int n_start = 1000;
  int n_step = 1000;
  int n_end = 1000000;

  vector<int> V;

  //actual benchmark loop
  for (int n = n_start; n<=n_end; n += n_step) {
	
	//"progress bar"
    std::cout << "Running Quicksort with n: " << n << std::endl;

	//generate n random integers
	sorting::randomizeVector(V, n);

	//start measurement
    dtime = omp_get_wtime();
    
	//execzute sorting algorithm
    sorting::QuickSort(V,0,V.size()-1);

	//stop time
    dtime = omp_get_wtime() - dtime;

	//write to file
    quicksort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
  }

  //close file handle
  quicksort_measurement.close();
}

