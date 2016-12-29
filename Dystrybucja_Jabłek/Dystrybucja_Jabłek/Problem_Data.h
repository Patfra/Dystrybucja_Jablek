#pragma once
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;
class Problem_Data
{
public:

	int chambersCapasity;
	int chambersAmount;
	int customersAmount;
	int speciesAmount;
	int palletsCapacity;
	double chambersKeepCosts[12];
	double (* marketPrices)[12];
	double *** customerPrices;
	int *** customerOrders;

	Problem_Data();
	~Problem_Data();
	Problem_Data( string filename );


};

