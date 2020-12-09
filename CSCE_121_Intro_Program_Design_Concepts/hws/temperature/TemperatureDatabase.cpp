#include "TemperatureDatabase.h"

#include <fstream>
using namespace std;

// Default constructor/destructor. Modify them if you need to.
TemperatureDatabase::TemperatureDatabase() {}
TemperatureDatabase::~TemperatureDatabase() {}

void TemperatureDatabase::loadData(const string& filename) 
{
	// Implement this function for part 1
	ifstream file;
	file.open(filename);
	string line;
	string id;
	int year;
	int month;
	double temperature;
	bool goodDat = true;
	if(file.is_open())
	{
		file >> id;
		if(file.fail())
		{
			cout << "Error: Other invalid input" << endl;
			goodDat = false;
		}
		
		file >> year;
		if(file.fail())
		{
			cout << "Error: Other invalid input" << endl;
			goodDat = false;
		}
		else if(!(year>=1800 && year<=2018))
		{
			cout << "Error: Invalid year " << year << endl;
			goodDat = false;
		}
		
		file >> month;
		if(file.fail())
		{
			cout << "Error: Other invalid input" << endl;
			goodDat = false;
		}
		else if(!(month>=1 && month<=12))
		{
			cout << "Error: Invalid month " << month << endl;
			goodDat = false;
		}
		
		file >> temperature;
		if(file.fail())
		{
			cout << "Error: Other invalid input" << endl;
			goodDat = false;
		}
		else if(!(temperature>=-50 && temperature<=50))
		{
			cout << "Error: Invalid temperature " << temperature << endl;
			goodDat = false;
		}
		
		if(goodDat)
			records.insert(id,year,month,temperature);
		
		goodDat = true;
		while(getline(file,line))
		{
			file >> id;
			if(file.fail())
			{
				cout << "Error: Other invalid input" << endl;
				goodDat = false;
			}
			
			file >> year;
			if(file.fail())
			{
				cout << "Error: Other invalid input" << endl;
				goodDat = false;
			}
			else if(!(year>=1800 && year<=2018))
			{
				cout << "Error: Invalid year " << year << endl;
				goodDat = false;
			}
			
			file >> month;
			if(file.fail())
			{
				cout << "Error: Other invalid input" << endl;
				goodDat = false;
			}
			else if(!(month>=1 && month<=12))
			{
				cout << "Error: Invalid month " << month << endl;
				goodDat = false;
			}
			
			file >> temperature;
			if(file.fail())
			{
				cout << "Error: Other invalid input" << endl;
				goodDat = false;
			}
			else if(!(temperature>=-50 && temperature<=50))
			{
				cout << "Error: Invalid temperature " << temperature << endl;
				goodDat = false;
			}
			
			if(goodDat)
				records.insert(id,year,month,temperature);
			
			goodDat = true;
			id = "";
			year = 0;
			month = 0;
			temperature = 0;
		}
	}
	else
	{
		cout << "Error: Unable to open " << filename << endl;
	}
	file.close();
	
}

void TemperatureDatabase::performQuery(const string& filename) 
{
	// Implement this function for part 2
	//  Leave it blank for part 1
	
	ifstream file;
	file.open(filename);
	ofstream outFile;
	outFile.open("result.dat");
	string line;
	string id;
	string type;
	int year1;
	int year2;
	double avg;
	int mode;
	bool goodDat = true;
	
	if(file.is_open())
	{
		while(getline(file,line))
		{
			istringstream iss(line);
			
			iss >> id;
			if(id.length() != 6)
			{
				cout << "Error: Other invalid query" << endl;
				goodDat = false;
			}
			
			if(goodDat)
			{
				iss >> type;
				if(type != "AVG" && type != "MODE")
				{
					cout << "Error: Unsupported query " << type << endl;
					goodDat = false;
				}
			}
			
			if(goodDat)
			{
				iss >> year1;
				/*
				if(year1<1800 || year1>2018)
				{
					cout << "Error: Invalid range " << year1 << "-" << year2 << endl;
					goodDat = false;
				}
				*/
			}	
			
			if(goodDat)
			{
				iss >> year2;
				if(year2 == 0)
				{
					cout << "Error: Other invalid query" << endl;
					goodDat = false;
				}
				else if(year1<1800 || year1>2018)
				{
					cout << "Error: Invalid range " << year1 << "-" << year2 << endl;
					goodDat = false;
				}
				else if(year2<1800 || year2>2018)
				{
					cout << "Error: Invalid range " << year1 << "-" << year2 << endl;
					goodDat = false;
				}
				else if(year1>year2)
				{
					cout << "Error: Invalid range " << year1 << "-" << year2 << endl;
					goodDat = false;
				}
			}
			
			if(goodDat)
			{
				if(type == "AVG")
				{
					avg = records.calculateAverage(id,year1,year2);
					outFile << id << " " << year1 << " " << year2 << " " << type << " ";
					if(avg == -99.99)
						outFile << "unknown" << endl;
					else
						outFile << avg << endl;
				}
				else if(type == "MODE")
				{
					mode = records.calculateMode(id,year1,year2);
					outFile << id << " " << year1 << " " << year2 << " " << type << " ";
					if(mode == -99)
						outFile << "unknown" << endl;
					else
						outFile << mode << endl;
				}
			}
			
			goodDat = true;
			id = "";
			type = "";
			year1 = 0;
			year2 = 0;
		}
	}
	else
	{
		cout << "Error: Unable to open " << filename << endl;
	}
	file.close();
	outFile.close();
	
}
