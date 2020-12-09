#include "SalariedEmployee.h"

using namespace std;

SalariedEmployee::SalariedEmployee() : Employee()
{
	annual_salary = 0.0;
}

SalariedEmployee::SalariedEmployee(string s, double d) : Employee(s)
{
	annual_salary = d;
}

double SalariedEmployee::weekly_pay()
{
	return annual_salary/52;
}

string SalariedEmployee::to_str()
{
	stringstream temp;
	temp << "Employee's Name: ";
	temp << get_name();
	temp << "\n";
	temp << "Weekly Pay: ";
	temp << weekly_pay();
	temp << "\n";
	temp << "Annual Salary: ";
	temp << annual_salary;
	return temp.str();
}