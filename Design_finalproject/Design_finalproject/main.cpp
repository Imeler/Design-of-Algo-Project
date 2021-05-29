// Created By Sauvens Fleurnord
// Prof Cardei M.
// Design and Analysis of Algorithm (COT4400)
//FInal Project 

#include<iostream> // open the proper libraries 
#include <vector> 
#include <stdlib.h> 
#include <chrono>
#include <time.h>
#include <ctime>
#include <random>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdint.h> // portable: uint64_t   MSVC: __int64 
using namespace std;
using namespace std::chrono;

const int m = 5;
const int n_end = 200000;   // end of array size
const int n_start = 10000;  // start of array size
const int increment = 10000;  // increment array by

//create a vector and fill it up with random numbers
void random(vector<vector<int> >& vec, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			vec[i][j] = rand() % 32767 + 1;
		}
	}
}

//implementing the insertion sort algorithm
void insertionSort(vector<int> arr, int n, int i) {
	int key = 0;
	int j = 0;
	for (int i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
	std::cout << "The order statistic of the insertion sort algorithm for vector size " << n << " is:" << arr[i - 1] << std::endl;

}

//Implementing the heap sort algorithm
int parent(int i) {
	return floor(i / 2);
}
int left(int i) {
	return (2 * i) + 1;
}
int right(int i) {
	return (2 * i) + 2;
}

void max_heapify(vector<int> &arr, int n, int i) {
	int l = left(i);
	int r = right(i);
	int largest = 0;
	int temp = 0;
	if (l < n && arr[l] > arr[i]) {
		largest = l;
	}
	else {
		largest = i;
	}
	if (r < n && arr[r] > arr[largest]) {
		largest = r;
	}
	if (largest != i) {
		temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;
		max_heapify(arr, n, largest);
	}
}

void build_max_heap(vector<int> &arr, int n) {
	for (int i = floor(n / 2) - 1; i >= 0; i--) {
		max_heapify(arr, n, i);
	}
}

void heapsort(vector<int> arr, int n, int i) {
	int temp = 0;
	build_max_heap(arr, n);

	for (int i = n - 1; i >= 0; i--) {
		temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;

		max_heapify(arr, i, 0);
	}
	std::cout << "The order statistic of the heap sort algorithm for vector size " << n << " is:" << arr[i - 1] << std::endl;
}

// Implementing the randomized-select algorithm
int partition(vector<int> &arr, int p, int r) {
	int x = arr[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; j++) {

		if (arr[j] <= x) {
			i++;
			int temp = arr[j];
			arr[j] = arr[i];
			arr[i] = temp;

		}
	}
	int temp = arr[r];
	arr[r] = arr[i + 1];
	arr[i + 1] = temp;

	return i + 1;
}
int randomized_partition(vector<int>& arr, int p, int r) {
	int i = (rand() % (r + 1 - p)) + p;
	// std::cout << i;
	int temp = arr[r];
	arr[r] = arr[i];
	arr[i] = temp;

	return partition(arr, p, r);
}
int randomized_select(vector<int> arr, int p, int r, int i)
{
	if (p == r) {
		return arr[p];
	}
	int q = randomized_partition(arr, p, r - 1);
	int k = q - p + 1;
	if (i == k) {
		return arr[q];
	}
	else if (i < k) {
		return randomized_select(arr, p, q - 1, i);
	}
	else
		return randomized_select(arr, q + 1, r, i - k);

}

//that's the main function. The mai source of the program
int main() {
	//counter that keeps track of time
	int s = 0;
	//keep track of total time in m from 1-5
	long long tot_time1 = 0.0;
	long long tot_time2 = 0.0;
	long long tot_time3 = 0.0;
	//averag times for each algorithm
	vector<long long> t_ALG1(20);
	vector<long long> t_ALG2(20);
	vector<long long> t_ALG3(20);
	//time
	time_t current_time;
	// Create a vectors containing m elements of size n 
	vector<vector<int> > vec(m, vector<int>(n_end));
	//fill it up with random numbers
	random(vec, m, n_end);


	for (int i = n_start; i <= n_end; i += increment) {
		//i-th order statistic
		int order = floor((2 * i) / 3);
		//vector B to be passed on to sorting alg
		vector<int> B(i);
		//5 rows
		for (int j = 0; j < m; j++) {

			//columns
			for (int k = 0; k < i; k++) {
				B[k] = vec[j][k];
			}
			//----------------------------------------insertion sort------------------------------------

			//start time
			auto start = std::chrono::high_resolution_clock::now();
			//long start = time(&current_time);
			insertionSort(B, i, order);
			//end time
			auto elapsed = std::chrono::high_resolution_clock::now() - start;

			long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
			tot_time1 += microseconds;

			//----------------------------------------Heap sort----------------------------------------

			//start time
			auto start2 = std::chrono::high_resolution_clock::now();
			//long start = time(&current_time);
			heapsort(B, i, order);
			//end time
			auto elapsed2 = std::chrono::high_resolution_clock::now() - start2;

			long long microseconds2 = std::chrono::duration_cast<std::chrono::microseconds>(elapsed2).count();
			tot_time2 += microseconds2;
			//----------------------------------------Randomize_Select------------------------------------

		   //start time
			auto start3 = std::chrono::high_resolution_clock::now();
			//long start = time(&current_time);
			randomized_select(B, 0, i, order);
			//end time
			auto elapsed3 = std::chrono::high_resolution_clock::now() - start3;

			long long microseconds3 = std::chrono::duration_cast<std::chrono::microseconds>(elapsed3).count();
			tot_time3 += microseconds3;
		}
		//save time for each array size
		t_ALG1[s] += tot_time1 / m;
		t_ALG2[s] += tot_time2 / m;
		t_ALG3[s] += tot_time3 / m;
		//print times
		std::cout << "\n Time for insertion sort algorithm with : " << i << " numbers: " << t_ALG1[s] << std::endl;
		std::cout << "\n Time for heap sort algorithm with : " << i << " numbers: " << t_ALG2[s] << std::endl;
		std::cout << "\n Time for randomized select algorithm with : " << i << " numbers: " << t_ALG3[s] << "\n\n";
		//increment counter for  t_ALG variables
		s++;
		//set tot_time back to 0
		tot_time1 = 0;
		tot_time2 = 0;
		tot_time3 = 0;

	}

	// Show the final times
	std::cout << "Times for the first algorithm " << std::endl;
	for (int i = 0; i < 20; i++) {
		std::cout << t_ALG1[i] << ", ";
	}
	std::cout << "\n";
	std::cout << "Times for the second algorithm" << std::endl;
	for (int i = 0; i < 20; i++) {
		std::cout << t_ALG2[i] << ", ";
	}
	std::cout << "\n";
	std::cout << "Times for the third algorithm" << std::endl;
	for (int i = 0; i < 20; i++) {
		std::cout << t_ALG3[i] << ", ";
	}
	return 0;
}