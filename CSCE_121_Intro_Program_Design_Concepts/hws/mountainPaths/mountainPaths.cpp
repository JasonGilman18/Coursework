#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <climits>
#include "functions.h"
using namespace std;

int main()
{
	//Part 1
	//user input and validating
	int rows = 0;
	int cols = 0;
	string fileName = "";
	
	cout << "Enter the number of rows in the map: ";
	cin >> rows;
	if(cin.fail() || rows<0)
	{
		cout << "Error: input need to be a positive integer";
		exit(1);
	}
			
	cout << "Enter the number of columns in the map: ";
	cin >> cols;
	if(cin.fail() || cols<0)
	{
		cout << "Error: input needs to be a positive integer";
		exit(1);
	}
			
	ifstream mapData;
	cout << "Enter the name of the file containing the map data: ";
	cin >> fileName;
	if(cin.fail())
	{
		cout << "Error: input should be a string";
		exit(1);
	}
	mapData.open(fileName);
	if(!mapData)
	{
		cout << "Error: Unable to open the file" << endl;
		exit(1);
	}
	
	//reading in data and finding min/max
	int count = 0;
	int temp = 0;
	int numVals = rows*cols;
	double min = (double)INT_MAX;
	double max = (double)INT_MIN;
	vector <vector<int>> data;
	vector <int> rowTemp;
	while(mapData >> temp)
	{
		if(mapData.fail())
		{
			cout << "Error: filestream should be integers";
			exit(1);
		}
		if(count==cols-1)
		{
			count = 0;
			rowTemp.push_back(temp);
			numVals -= 1;
			data.push_back(rowTemp);
			rowTemp.clear();
		}
		else
		{
			rowTemp.push_back(temp);
			numVals -= 1;
			count += 1;
		}
		if(temp<min)
			min = (double)temp;
		else if(temp>max)
			max = (double)temp;
	}
	cout << numVals << endl;
	if(numVals!=0)
	{
		cout << "Error: the amount of data does not match the number of rows and cols";
		exit(1);
	}
	
	//filling RGB vectors
	int shade = 0;
	rowTemp.clear();
	vector <vector<int>> rValues;
	vector <vector<int>> gValues;
	vector <vector<int>> bValues;
	for(int r=0;r<data.size();++r)
	{
		for(int c=0;c<data.at(r).size();++c)
		{
			shade = round((((data.at(r)).at(c) - min)/(max - min))*255);
			rowTemp.push_back(shade);
		}
		rValues.push_back(rowTemp);
		gValues.push_back(rowTemp);
		bValues.push_back(rowTemp);
		rowTemp.clear();
	}
	
	//Part 2
	//vector <vector<int>> data
	//vector <vector<int>> rValues
	//vector <vector<int>> gValues
	//vector <vector<int>> bValues
	
	int shortestPath = colorPath(data,rValues,gValues,bValues,252,25,63,0);
	int shortestRow = 0;
	int newPath = 0;
	for(int i=0;i<data.size();++i)
	{
		newPath = colorPath(data,rValues,gValues,bValues,252,25,63,i);
		if(newPath<shortestPath)
		{
			shortestPath = newPath;
			shortestRow = i;
		}
	}
	colorPath(data,rValues,gValues,bValues,31,253,13,shortestRow);
	
	//outputting to file
	string outputName = fileName.append(".ppm");
	ofstream output (outputName);
	output << "P3" << endl;
	output << cols << " " << rows << endl;
	output << "255" << endl;
	
	for(int r=0;r<data.size();++r)
	{
		for(int c=0;c<data.at(r).size();c++)
		{
			output << (rValues.at(r)).at(c) << " " << (gValues.at(r)).at(c) << " " << (bValues.at(r)).at(c) << " ";
		}
		output << endl;
	}
	
	mapData.close();
	output.close();
	
	return 0;
}