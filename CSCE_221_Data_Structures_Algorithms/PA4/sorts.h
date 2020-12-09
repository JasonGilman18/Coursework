#ifndef SORTS_H
#define SORTS_H
#include <vector>

class sorts
{
	public:
		
		std::vector<int> sorts::bubbleSort(int n, std::vector<int>); //bubble sort with n elements
		
		void sorts::insertionSort(int n, std::vector<int>); //insertion sort with n elements
		
		void sorts::quickSort(int n, std::vector<int>); // n elements to sort
		
		void sorts::selectionSort(int n, std::vector<int>); // n elements to sort
		
		void sorts::mergeSort(int n, std::vector<int>); // n elements to sort
};

#endif 