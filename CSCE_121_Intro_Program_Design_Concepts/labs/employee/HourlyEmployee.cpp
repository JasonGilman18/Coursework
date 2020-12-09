#include "HourlyEmployee.h"

using namespace std;

HourlyEmployee::HourlyEmployee() : Employee()
{
	hourly_wage = 0;
	hours_worked = 0;
}

HourlyEmployee::HourlyEmployee(string s,double d) : Employee(s)
{
	hourly_wage = d;
	hours_worked = 0;
}

HourlyEmployee::HourlyEmployee(string s,double d,double d2) : Employee(s)
{
	hourly_wage = d;
	hours_worked = d2;
}

void HourlyEmployee::set_hours_worked(double d)
{
	hours_worked = d;
}

double HourlyEmployee::get_hours_worked()
{
	return hours_worked;
}

double HourlyEmployee::weekly_pay()
{
	if(hours_worked>40)
	{
		double overtime = (hours_worked-40)*1.5;
		return (hourly_wage*40) + (hourly_wage*overtime);
	}
	else
		return hourly_wage*hours_worked;
}

string HourlyEmployee::to_str()
{
	stringstream temp;
	temp << "Employee's Name: ";
	temp << get_name();
	temp << "\n";
	temp << "Weekly Pay: ";
	temp << weekly_pay();
	temp << "\n";
	temp << "Hours Worked: ";
	temp << get_hours_worked();
	temp <<"\n";
	temp << "Hourly Wage: ";
	temp << hourly_wage;
	return temp.str();
}