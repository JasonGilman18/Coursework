#include "sorts.h"
using namespace std;

vector<int> bubbleSort(int n, vector<int> v)
{
	int comparisons = 0;
	int moves = 0;
	int temp;
	for(int i=0;i<n-1;i++)
		for(int m=0;m<n-1;m++)
		{
			if(v.at(m)>v.at(m+1))
			{
				temp = v.at(m+1);
				v.at(m+1) = v.at(m);
				v.at(m) = temp;
				moves++;
			}
			comparisons++;
		}
}

void insertionSort(int n, vector<int> v)
{
	
}

void quickSort(int n, vector<int> v)
{

}
	
void selectionSort(int n, vector<int> v)
{
	
}
	
void mergeSort(int n, vector<int> v)
{
	
}