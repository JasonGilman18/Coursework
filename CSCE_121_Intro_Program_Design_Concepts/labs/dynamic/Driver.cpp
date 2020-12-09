#include <iostream>
#include <stdexcept>
#include "DynArrayStack.h"

using namespace std;

int main()
try {
    //DynArrayStack das{};
	
	/*
	overflow error
	das.push('k');
	das.push('j');
	das.push('h');
	das.push('m');
	*/
	
	/*
	underflow
	das.pop();
	*/
	
	//DynArrayStack das('k');
	
	DynArrayStack das{};
	das.pop();
	
	
    return 0;
}
catch(runtime_error& e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch(DynArrayStack::Overflow& e) 
{
    //cerr << e << '\n';
    return 2;
}
catch(DynArrayStack::Underflow& e)
{
	//cerr << e << '\n';
	return 3;
}