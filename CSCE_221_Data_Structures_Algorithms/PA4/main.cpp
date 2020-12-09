#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

//the sorts functions come before the main function.
//inside the main function the names of the input and output files can be changed.

void bubbleSort(int n, vector<int> &v)
{
	int comparisons = 0;
	int moves = 0;
	int temp;
	for(int i=0;i<n-1;i++)
		for(int m=0;m<n-1;m++)
		{
			if(v.at(m)>v.at(m+1)) //swap places if greater
			{
				temp = v.at(m+1);
				v.at(m+1) = v.at(m);
				moves++;
				v.at(m) = temp;
				moves++;
			}
			comparisons++;
		}
	cout << "BUBBLE SORT, COMPARISONS: " << comparisons << " MOVES: " << moves << endl;
}

void insertionSort(int n, vector<int> &v)
{
	int comparisons = 0;
	int moves = 0;
	int num;
	int sortedSpot;
	int temp;
	for(int i=1;i<n;i++)
	{
		num = v.at(i); //number to be inserted
		sortedSpot = i-1;
		while(sortedSpot >= 0 && num < v.at(sortedSpot)) //find the sorted location of the inserted number
		{
			v.at(sortedSpot+1) = v.at(sortedSpot);
			sortedSpot--;
			comparisons++;
		}
		if(sortedSpot < 0)
			v.at(0) = num;
		else 
			v.at(sortedSpot+1) = num; //should be 1 place greater becuase the loop decrements every iteration
		
		moves++;
	}
	cout << "INSERTION SORT, COMPARISONS: " << comparisons << " MOVES: " << moves << endl;
}

int pivot(vector<int> &v, int f, int l, int &moves, int &comparisons) //will return the position of where the partition is.
{

	int pivotElement = v.at(f);//first elemnt
	int temp;
	int tempf = f+1;
	int templ = l;
	
	while(tempf < templ)
	{
		comparisons++;
		while(v.at(tempf) < pivotElement && tempf <= l)
		{
			tempf++;
			comparisons++;
			comparisons++;
		}
		while(pivotElement < v.at(templ))
		{
			templ--;
			comparisons++;
		}	
		if(tempf < templ)
		{
			comparisons++;
			temp = v.at(tempf);
			v.at(tempf) = v.at(templ);
			v.at(templ) = temp;
			moves++;
			moves++;
		}
	}
	
	v.at(f) = v.at(templ);
	v.at(templ) = pivotElement;
	moves++;
	moves++;
	return templ;
}

void quickSort(vector<int> &v, int f, int l, int &moves, int &comparisons)
{
	//partition element will be the first element. now to sort array around this.
	//first half of e, values less than pivot.
	//second half, values greater than pivot.
	
	int pivotPlace;
	if(f < l)
	{
		pivotPlace = pivot(v,f,l,moves,comparisons);
		quickSort(v,f,pivotPlace-1,moves,comparisons);
		quickSort(v,pivotPlace+1,l,moves,comparisons);
	}
	cout << "QUICK SORT, COMPARISONS: " << comparisons << " MOVES: " << moves << endl;
}
	
void selectionSort(int n, vector<int> &v)
{
	int comparisons = 0;
	int moves = 0;
	int smallest;
	int temp;
	for(int i=0;i<n-1;i++)
	{
		int smallestIndex = i;
		for(int e=i+1;e<n;e++) //e is the index of the element to to compare to the smallest;finding smalles element
		{
			if(v.at(smallestIndex) > v.at(e))
				smallestIndex = e;
			comparisons++;
		}
		temp = v.at(smallestIndex);
		v.at(smallestIndex) = v.at(i);
		moves++;
		v.at(i) = temp;
		moves++;
	}
	cout << "SELECTION SORT, COMPARISONS: " << comparisons << " MOVES: " << moves << endl;
}

void merge(vector<int> &v, int f, int m, int l, int &moves, int &comparisons) //helper function to merge the vecs into one sorted vec
{
	vector<int> tempVec(l-f+1,0);
	int tempf = f;
	int tempm = m+1;
	int temp = 0;
	while(tempf <= m && tempm <= l)
	{
		comparisons++;
		comparisons++;
		if(v.at(tempf) <= v.at(tempm))
		{
			comparisons++;
			tempVec.at(temp++) = v.at(tempf++);
			moves++;
		}
		else
		{
			tempVec.at(temp++) = v.at(tempm++);
			moves++;
		}
	}
	while(tempf <= m)
	{
		comparisons++;
		tempVec.at(temp++) = v.at(tempf++);
		moves++;
	}
	while(tempm <= l)
	{
		comparisons++;
		tempVec.at(temp++) = v.at(tempm++);
		moves++;
	}
	for(temp = 0,tempf=f;tempf<=l;tempf++,temp++)
		v.at(tempf) = tempVec.at(temp);
}
	
void mergeSort(vector<int> &v, int f, int l, int &moves, int &comparisons)
{
	int m;
	if(f<l)
	{
		m = (f+l)/2;//find middle
		mergeSort(v,f,m,moves,comparisons);//first half of array, from first to mid
		mergeSort(v,m+1,l,moves,comparisons);//second hald of array, from mid to last
		merge(v,f,m,l,moves,comparisons);
	}
	cout << "MERGE SORT, COMPARISONS: " << comparisons << " MOVES: " << moves << endl;
}

int main()
{
	//names of the input and output files!!!
	string inputFileName = "100.txt";
	string outputFileName = "output.txt";
	
	ifstream inputFile;
	ofstream outputFile;
	
	inputFile.open(inputFileName);
	
	vector<int> arr;
	string line;
	int num;
	int moves = 0;
	int comparisons = 0;
	if(inputFile.is_open()) //read nums from file into arr
	{
		int sort;
		inputFile >> sort;
		int n;
		inputFile >> n;
		
		for(int i=0;i<n;i++)
		{
			inputFile >> num;
			arr.push_back(num);
		}
		//vector<int> sorted;
		switch(sort)
		{
			case 1 :selectionSort(n,arr);
					break;
		
			case 2 :insertionSort(n,arr);
					break;
				 
			case 3 :bubbleSort(n,arr);
					break;
		
			case 4 :mergeSort(arr,0,n-1,moves,comparisons);
					break;
				 
			case 5 :quickSort(arr,0,n-1,moves,comparisons);
					break;
				 
		}
		
		outputFile.open(outputFileName);
		
		for(int i=0;i<n;i++)
			outputFile << arr.at(i) << endl;
		
		outputFile.close();
		inputFile.close();
	}
	return 0;
}