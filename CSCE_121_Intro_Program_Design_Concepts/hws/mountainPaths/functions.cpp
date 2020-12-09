#include<vector>
#include<cmath>
#include<iostream>
#include "functions.h"

using namespace std;

int colorPath(const vector<vector<int>>& heightMap, vector<vector<int>>& r, vector<vector<int>>& g, vector<vector<int>>& b, int color_r, int color_g,
	int color_b, int start_row) 
{
	int dist = 0;
	int currRow = start_row;
	int currOp = (heightMap.at(start_row)).at(0);
	int op1 = 0;
	int op2 = 0;
	int op3 = 0;
	
	for(int i=0;i<(heightMap.at(start_row)).size()-1;++i)
	{
		//cout << "COL: " << i << endl;
		
		if(currRow == 0)
		{
			op2 = (heightMap.at(currRow)).at(i+1); //across one
			op3 = (heightMap.at(currRow+1)).at(i+1); //across one,down one
			
			if(abs(currOp-op2) <= abs(currOp-op3))
			{
				(r.at(currRow)).at(i+1) = color_r;
				(g.at(currRow)).at(i+1) = color_g;
				(b.at(currRow)).at(i+1) = color_b;
				dist += abs(currOp-op2);
				currOp = (heightMap.at(currRow)).at(i+1);
			}
			else if(abs(currOp-op2) > abs(currOp-op3))
			{
				(r.at(currRow+1)).at(i+1) = color_r;
				(g.at(currRow+1)).at(i+1) = color_g;
				(b.at(currRow+1)).at(i+1) = color_b;
				dist += abs(currOp-op3);
				currOp = (heightMap.at(currRow+1)).at(i+1);
				currRow += 1;
			}
		}
		else if(currRow == heightMap.size()-1)
		{
			op1 = (heightMap.at(currRow-1)).at(i+1); //across one,up one
			op2 = (heightMap.at(currRow)).at(i+1); //across one
			
			if(abs(currOp-op1) < abs(currOp-op2))
			{
				(r.at(currRow-1)).at(i+1) = color_r;
				(g.at(currRow-1)).at(i+1) = color_g;
				(b.at(currRow-1)).at(i+1) = color_b;
				dist += abs(currOp-op1);
				currOp = (heightMap.at(currRow-1)).at(i+1);
				currRow -= 1;
			}
			else if(abs(currOp-op1) >= abs(currOp-op2))
			{
				(r.at(currRow)).at(i+1) = color_r;
				(g.at(currRow)).at(i+1) = color_g;
				(b.at(currRow)).at(i+1) = color_b;
				dist += abs(currOp-op2);
				currOp = (heightMap.at(currRow)).at(i+1);
			}
		}
		else
		{
			op1 = (heightMap.at(currRow-1)).at(i+1);
			op2 = (heightMap.at(currRow)).at(i+1);
			op3 = (heightMap.at(currRow+1)).at(i+1);
			
			if(abs(currOp-op1) < abs(currOp-op2) && abs(currOp-op1) < abs(currOp-op3))
			{
                (r.at(currRow-1)).at(i+1) = color_r;
				(g.at(currRow-1)).at(i+1) = color_g;
				(b.at(currRow-1)).at(i+1) = color_b;
				dist += abs(currOp-op1);
				currOp = (heightMap.at(currRow-1)).at(i+1);
				currRow -= 1;
			}
			else if(abs(currOp-op2) <= abs(currOp-op1) && abs(currOp-op2) <= abs(currOp-op3))
			{
				(r.at(currRow)).at(i+1) = color_r;
				(g.at(currRow)).at(i+1) = color_g;
				(b.at(currRow)).at(i+1) = color_b;
				dist += abs(currOp-op2);
				currOp = (heightMap.at(currRow)).at(i+1);
			}
			else if(abs(currOp-op3) < abs(currOp-op1) && abs(currOp-op3) < abs(currOp-op2))
			{
				(r.at(currRow+1)).at(i+1) = color_r;
				(g.at(currRow+1)).at(i+1) = color_g;
				(b.at(currRow+1)).at(i+1) = color_b;
				dist += abs(currOp-op3);
				currOp = (heightMap.at(currRow+1)).at(i+1);
				currRow += 1;
			}
		}	
	}
	
	(r.at(currRow)).at(heightMap.at(currRow).size()-1) = color_r;
	(g.at(currRow)).at(heightMap.at(currRow).size()-1) = color_g;
	(b.at(currRow)).at(heightMap.at(currRow).size()-1) = color_b;
	
	return dist;
	
}
