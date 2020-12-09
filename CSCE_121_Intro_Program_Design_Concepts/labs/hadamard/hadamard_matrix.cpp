//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//                           LW: Hadamard matrix                            //
//                           hadamard_matrix.cpp                            //
//                                                                          //
// Written By :                         Environment :                       //
// Date ......:                         Compiler ...:                       //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                                #includes                                 //
//////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <limits>
#include "hadamard_matrix.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
//                           function definitions                           //
//////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
*                    vector<vector<bool>> hadamard(int n)                    *
*                                                                            *
*       Description ....:                                                    *
*                                                                            *
*                                                                            *
* Written By :                          Environment :                        *
* Date ......:                          Compiler ...:                        *
*****************************************************************************/
vector<vector<bool>> hadamard(int n)
{
    vector<vector<bool>> v; //(1, vector<bool>(1));
    //v.at(0).at(0) = 1;
    // continue implementation.
	
	for(int i=0;i<n;++i)
	{
		vector<bool> a;
		v.push_back(a);
	}
	for(int r=0;r<n;++r)
	{
		for(int c=0;c<n;++c)
		{
			(v.at(r)).push_back(1);	
		}
	}
	
	for(int i=1;i<n;i+=i)
	{
		for(int r=0;r<i;++r)
		{
			for(int c=0;c<i;++c)
			{
				(v.at(i+r)).at(c) = (v.at(r)).at(c);
				(v.at(r)).at(i+c) = (v.at(r)).at(c);
				(v.at(i+r)).at(i+c) = !(v.at(r)).at(c);
			}
		}
	}
	
    return v;
}
/*****************************************************************************
*                 void print (vector <vector<bool>> const&v)                 *
*                                                                            *
*       Description ....:                                                    *
*                                                                            *
*                                                                            *
* Written By :                          Environment :                        *
* Date ......:                          Compiler ...:                        *
*****************************************************************************/
void print (vector <vector<bool>> const&v)
{
	int rows = v.size();
	int cols = (v.at(0)).size();
	for(int r=0;r<rows;++r)
	{
		for(int c=0;c<cols;++c)
		{
			cout << (v.at(r)).at(c);
		}
		if(!(rows-r == 1))
			cout << endl;
	}
}

/*****************************************************************************
*                          int str_to_int(std::string)                       *
*                                                                            *
*       Description ....:                                                    *
*                                                                            *
*                                                                            *
* Written By :                          Environment :                        *
* Date ......:                          Compiler ...:                        *
*****************************************************************************/

int str_to_int(std::string s)
{
    stringstream ss {s}; int val;
    ss >> val;
    if (ss.fail()) {
        ss.ignore(numeric_limits<streamsize>::max(), '\n');
        ss.clear();
        throw runtime_error("Value provided not an integer");
    }

    return val;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////