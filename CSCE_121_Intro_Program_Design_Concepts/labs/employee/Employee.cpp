#include "Employee.h"

using namespace std;

Employee::Employee()
{
	name = "";
}

Employee::Employee(string s)
{
	name = s;
}

void Employee::set_name(string s)
{
	name = s;
}

string Employee::get_name()
{
	return name;
}

ostream& operator<<(ostream& os, Employee* e)
{
	os << e->to_str() << endl;
	return os;
}