#include "Parametry_Konfiguracyjne.h"

Parametry_Konfiguracyjne::Parametry_Konfiguracyjne()
{
	chambersCapasity = 1;
	chambersAmount = 1;
	customersAmount = 1;
	speciesAmount= 1;
	palletsCapacity= 1;
	marketPrices = new double[speciesAmount][12];
	customerPrices = new double **[customersAmount];
	for (int i = 0; i < customersAmount; i++)
	{
		customerPrices[i] = new double *[speciesAmount];
		for (int j = 0; j < speciesAmount; j++)
		{
			customerPrices[i][j] = new double[12];
		}
	}
	customerOrders = new int **[customersAmount];
	for (int i = 0; i < customersAmount; i++)
	{
		customerOrders[i] = new int *[speciesAmount];
		for (int j = 0; j < speciesAmount; j++)
		{
			customerOrders[i][j] = new int[12];
		}
	}
}


Parametry_Konfiguracyjne::~Parametry_Konfiguracyjne()
{
	delete[] marketPrices;
	for (int i = 0; i < customersAmount; i++)
	{
		for (int j = 0; j < speciesAmount; j++)
		{
			delete[] customerPrices[i][j];
		}
		delete[] customerPrices[i];
	}
	delete[] customerPrices;
	for (int i = 0; i < customersAmount; i++)
	{
		for (int j = 0; j < speciesAmount; j++)
		{
			delete[] customerOrders[i][j];
		}
		delete[] customerOrders[i];
	}
	delete[] customerOrders;
	cout << "PAPA" << endl;
}

Parametry_Konfiguracyjne::Parametry_Konfiguracyjne(string filename)
{
	chambersCapasity = 1;
	chambersAmount = 1;
	customersAmount = 1;
	speciesAmount = 1;
	palletsCapacity = 1;
	marketPrices = new double[speciesAmount][12];
	customerPrices = new double **[customersAmount];
	for (int i = 0; i < customersAmount; i++)
	{
		customerPrices[i] = new double *[speciesAmount];
		for (int j = 0; j < speciesAmount; j++)
		{
			customerPrices[i][j] = new double[12];
		}
	}
	customerOrders = new int **[customersAmount];
	for (int i = 0; i < customersAmount; i++)
	{
		customerOrders[i] = new int *[speciesAmount];
		for (int j = 0; j < speciesAmount; j++)
		{
			customerOrders[i][j] = new int[12];
		}
	}
	cout << "ELO :D" << endl;
}
