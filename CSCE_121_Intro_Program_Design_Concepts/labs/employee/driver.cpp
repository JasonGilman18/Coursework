#include "Employee.h"

#include "HourlyEmployee.h"
#include "SalariedEmployee.h"
#include "Manager.h"
#include <string>
#include <vector>

using namespace std;

int main()
{
	vector<Employee*> v;
	HourlyEmployee* h = new HourlyEmployee("Aramis",25,45);
	SalariedEmployee* s = new SalariedEmployee("Porthos",100000);
	Manager* m = new Manager("Athos",120000,500);
	v.push_back(h);
	v.push_back(s);
	v.push_back(m);
	
	for(int i=0;i<v.size();++i)
		cout << v.at(i) << endl;
}