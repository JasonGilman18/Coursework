#include "Manager.h"

using namespace std;

Manager::Manager() : SalariedEmployee()
{
	weekly_bonus = 0.0;
}

Manager::Manager(string s, double d, double d2) : SalariedEmployee(s,d)
{
	weekly_bonus = d2;
}

double Manager::weekly_pay()
{
	return SalariedEmployee::weekly_pay() + weekly_bonus;
}

string Manager::to_str()
{
	stringstream temp;
	temp << "Employee's Name: ";
	temp << get_name();
	temp << "\n";
	temp << "Weekly Pay: ";
	temp << weekly_pay();
	temp << "\n";
	temp << "Weekly Bonus: ";
	temp << weekly_bonus;
	temp << "\n";
	temp << "Annual Salary: ";
	temp << annual_salary;
	return temp.str();
}