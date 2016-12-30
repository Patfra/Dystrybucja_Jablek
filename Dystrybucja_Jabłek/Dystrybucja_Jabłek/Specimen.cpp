#include "Specimen.h"



Specimen::Specimen(Problem_Data * data)
{
	profit = 0;
	punishment = 0;
	mutationAmount = 0;
	customersAmount = data->customersAmount;
	speciesAmount = data->speciesAmount;
	genome = new int **[customersAmount];
	for (int i = 0; i < customersAmount; i++)
	{
		genome[i] = new int *[speciesAmount];
		for (int j = 0; j < speciesAmount; j++)
		{
			genome[i][j] = new int[12];
		}
	}
	bought = new int *[customersAmount];
	for (int i = 0; i < customersAmount; i++)
	{
		bought[i] = new int[speciesAmount];
	}
	warehouseState = new int *[customersAmount];
	for (int i = 0; i < customersAmount; i++)
	{
		warehouseState[i] = new int[speciesAmount];
	}

}

Specimen::Specimen()
{
	profit = 0;
	punishment = 0;
	mutationAmount = 0;
	customersAmount = 1;
	speciesAmount = 1;	
	genome = new int **[customersAmount];
	for (int i = 0; i < customersAmount; i++)
	{
		genome[i] = new int *[speciesAmount];
		for (int j = 0; j < speciesAmount; j++)
		{
			genome[i][j] = new int[12];
		}
	}
	bought = new int *[customersAmount];
	for (int i = 0; i < customersAmount; i++)
	{
		bought[i] = new int [speciesAmount];
	}
	warehouseState = new int *[customersAmount];
	for (int i = 0; i < customersAmount; i++)
	{
		warehouseState[i] = new int[speciesAmount];
	}
}


Specimen::~Specimen()
{
	for (int i = 0; i < customersAmount; i++)
	{
		for (int j = 0; j < speciesAmount; j++)
		{
			delete[] genome[i][j];
		}
		delete[] genome[i];
	}
	delete[] genome;
	for (int i = 0; i < speciesAmount; i++)
	{
		delete[] bought[i];
	}
	delete[] bought;
	for (int i = 0; i < speciesAmount; i++)
	{
		delete[] warehouseState[i];
	}
	delete[] warehouseState;
}
