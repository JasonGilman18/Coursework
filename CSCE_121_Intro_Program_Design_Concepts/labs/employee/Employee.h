#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>
#include <iostream>

class Employee
{
	public:
		Employee();
		Employee(std::string);
		void set_name(std::string);
		std::string get_name();
		virtual std::string to_str() = 0;
		
	private:
		std::string name;
};
std::ostream& operator<<(std::ostream& os, Employee* e);
#endif