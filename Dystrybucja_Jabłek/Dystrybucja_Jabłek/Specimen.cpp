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
	bought = new int *[speciesAmount];
	for (int i = 0; i < speciesAmount; i++)
	{
		bought[i] = new int[12];
	}
	warehouseState = new int *[speciesAmount];
	for (int i = 0; i < speciesAmount; i++)
	{
		warehouseState[i] = new int[12];
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
	bought = new int *[speciesAmount];
	for (int i = 0; i < speciesAmount; i++)
	{
		bought[i] = new int [12];
	}
	warehouseState = new int *[speciesAmount];
	for (int i = 0; i < speciesAmount; i++)
	{
		warehouseState[i] = new int[12];
	}
}
Specimen::Specimen(const Specimen & nspec)
{
	profit = nspec.profit;
	punishment = nspec.punishment;
	mutationAmount = nspec.mutationAmount;
	customersAmount = nspec.customersAmount;
	speciesAmount = nspec.speciesAmount;
	genome = new int **[customersAmount];
	for (int i = 0; i < customersAmount; i++)
	{
		genome[i] = new int *[speciesAmount];
		for (int j = 0; j < speciesAmount; j++)
		{
			genome[i][j] = new int[12];
			for (int k= 0; k < 12; k++)
			{
				genome[i][j][k] = nspec.genome[i][j][k];
			}
		}
	}
	bought = new int *[speciesAmount];
	for (int i = 0; i < speciesAmount; i++)
	{
		bought[i] = new int[12];
		for (int k = 0; k < 12; k++)
		{
			bought[i][k] = nspec.bought[i][k];
		}
	}
	warehouseState = new int *[speciesAmount];
	for (int i = 0; i < speciesAmount; i++)
	{
		warehouseState[i] = new int[12];
		for (int k = 0; k < 12; k++)
		{
			warehouseState[i][k] = nspec.warehouseState[i][k];
		}


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
