#ifndef HOURLYEMPLOYEE_H
#define HOURLYEMPLOYEE_H
#include "Employee.h"
#include <string>
#include <sstream>

class HourlyEmployee:public Employee
{
	public:
		HourlyEmployee();
		HourlyEmployee(std::string,double);
		HourlyEmployee(std::string s,double d,double d2);
		void set_hours_worked(double);
		double get_hours_worked();
		double weekly_pay();
		virtual std::string to_str();
	
	private:
		double hourly_wage;
		double hours_worked;
	
};

#endif