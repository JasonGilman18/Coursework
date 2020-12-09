//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//                              DynArrayStack                               //
//                            DynArrayStack.cpp                             //
//                                                                          //
// Written By :                         Environment : Mac OS X 10.13.3      //
// Date ......: 2018/04/01              Compiler ...: Homebrew GCC 6.3.0_1  //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                                 Includes                                 //
//////////////////////////////////////////////////////////////////////////////
#include "DynArrayStack.h"

//////////////////////////////////////////////////////////////////////////////
//                     Public Interface Implementation                      //
//////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
*                       DynArrayStack::DynArrayStack()                       *
*                                                                            *
*                                                                            *
* Written By :                          Environment : Mac OS X 10.13.3       *
* Date ......:  2018/04/01              Compiler ...: Homebrew GCC 6.3.0_1   *
*****************************************************************************/
DynArrayStack::DynArrayStack() : capacity{init_size}, top{0}, v{nullptr}
{
    v = new char[init_size];
}

DynArrayStack::DynArrayStack(char c)
{	
	v = new char[init_size];
	capacity = init_size;
	v[0] = c;
	top = 1;
}

/*****************************************************************************
*                      DynArrayStack::~DynArrayStack()                       *
*                                                                            *
* Written By :                          Environment : Mac OS X 10.13.3       *
* Date ......:  2018/04/01              Compiler ...: Homebrew GCC 6.3.0_1   *
*****************************************************************************/
DynArrayStack::~DynArrayStack()
{
    delete v;
}

/*****************************************************************************
*                      void DynArrayStack::push(char c)                      *
*                                                                            *
* Written By :                          Environment : Mac OS X 10.13.3       *
* Date ......:  2018/04/01              Compiler ...: Homebrew GCC 6.3.0_1   *
*****************************************************************************/
void DynArrayStack::push(char c)
{
    if (top == capacity) //throw Overflow();
	{
		char temp[capacity*2];
		for(int i=0;i<capacity;++i)
		{
			temp[i] = v[i];
		}
		delete v;
		v = temp;
		capacity *= 2;
	}
    v[top] = c;
    top += 1;
}

/*****************************************************************************
*                         char DynArrayStack::pop()                          *
*                                                                            *
* Written By :                          Environment : Mac OS X 10.13.3       *
* Date ......:  2018/04/01              Compiler ...: Homebrew GCC 6.3.0_1   *
*****************************************************************************/
char DynArrayStack::pop()
{
    if (top <= 0) throw Underflow();
	else if(top == .5*capacity)
	{
		char temp[(int)(.5*capacity)];
		capacity *= .5;
		for(int i=0;i<capacity;++i)
		{
			temp[i] = v[i];
		}
		delete v;
		v = temp;
	}
    top -= 1;
    return v[top];
}

//////////////////////////////////////////////////////////////////////////////
//                      Private Method Implementations                      //
//////////////////////////////////////////////////////////////////////////////

