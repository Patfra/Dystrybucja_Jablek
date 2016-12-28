#pragma once
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;
class Parametry_Konfiguracyjne
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

	Parametry_Konfiguracyjne();
	~Parametry_Konfiguracyjne();
	Parametry_Konfiguracyjne( string filename );

};

