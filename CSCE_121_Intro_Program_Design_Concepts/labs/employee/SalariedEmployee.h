#ifndef SALARIEDEMPLOYEE_H
#define SALARIEDEMPLOYEE_H
#include "Employee.h"
#include <string>
#include <sstream>

class SalariedEmployee:public Employee
{
	public:
		SalariedEmployee();
		SalariedEmployee(std::string,double annual_salary);
		virtual double weekly_pay();
		virtual std::string to_str();
		
	protected:
		double annual_salary;
};

#endif