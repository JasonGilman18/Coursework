#ifndef MANAGER_H
#define MANAGER_H
#include "SalariedEmployee.h"
#include <string>
#include <sstream>

class Manager:public SalariedEmployee
{
	public:
		Manager();
		Manager(std::string,double,double);
		double weekly_pay();
		virtual std::string to_str();
		
	private:
		double weekly_bonus;
};

#endif
