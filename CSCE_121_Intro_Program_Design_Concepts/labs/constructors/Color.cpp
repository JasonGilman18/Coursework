//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//                        CLASS CONSTRUCTORS LAB                            //
//                               COLOR.CPP                                  //
//                                                                          //
//  Date ...: 18/MAR/2017                                                   //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                                 Includes                                 //
//////////////////////////////////////////////////////////////////////////////
#include "Color.h"
using namespace std;

//////////////////////////////////////////////////////////////////////////////
//                     Color Class Member Definitions                       //
//////////////////////////////////////////////////////////////////////////////
std::string Color::to_str()
{
    std::stringstream ss;
    ss << '(' << R << ',' << G << ',' << B << ')';
    return ss.str();
}

Color::Color()
{
	R = 255;
	B = 255;
	G = 255;
}

Color::Color(int r,int g,int b)
{
	if(r>=0 && r<=255)
		R = r;
	else
		throw Color_error{};
	if(g>=0 && g<=255)
		G = g;
	else
		throw Color_error{};
	if(b>=0 && b<=255)
		B = b;
	else
		throw Color_error{};
}

void Color::set_R(int r)
{
    if (!is_valid_val(r))
        throw Color_error{};
    R = r;
}
void Color::set_G(int g)
{
    if (!is_valid_val(g))
        throw Color_error{};
    G = g;
}
void Color::set_B(int b)
{
    if (!is_valid_val(b))
        throw Color_error{};
    B = b;
}
bool Color::is_valid_val(int v)
{
    if (v < 0 || v > 255)
        return false;
    else
        return true;
}