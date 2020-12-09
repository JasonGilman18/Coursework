/*
 * TemperatureData.cpp
 *
 *  Created on: Jul 16, 2018
 *      Author: student
 */

#include "TemperatureData.h"
using namespace std;

TemperatureData::TemperatureData() //initialize everything
{
	id = "";
	year = 0;
	month = 0;
	temperature = 0.0;
}

TemperatureData::TemperatureData(std::string id2, int year2, int month2, double temperature2) //initialize everything
{
	id = id2;
	year = year2;
	month = month2;
	temperature = temperature2;
}

TemperatureData::~TemperatureData() {} // You should not need to implement this

bool TemperatureData::operator<(const TemperatureData& b) 
{
	if((this->id).compare(b.id) == 0)
	{
		if(this->year == b.year)
		{
			if(this->month == b.month)
			{
				return this->temperature < b.temperature;
			}
			else
				return this->month < b.month;
		}
		else
			return this->year < b.year;
	}
	else
		return (this->id).compare(b.id) < 0;
}

