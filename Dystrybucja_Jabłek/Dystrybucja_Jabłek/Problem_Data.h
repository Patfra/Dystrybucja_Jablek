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
	int chambersKeepCosts[12];
	int ** marketPrices;
	int *** customerPrices;
	int *** customerOrders;

	Problem_Data();
	~Problem_Data();
	Problem_Data( string filename );


};

