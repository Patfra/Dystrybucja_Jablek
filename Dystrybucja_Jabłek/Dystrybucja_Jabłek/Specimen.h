#pragma once
#include "Configuration_Parameters.h"
class Specimen
{
public:
	int *** genome;
	int customersAmount;
	int speciesAmount;
	long long int profit;
	long long int punishment;
	int mutationAmount;
	int ** bought;
	int ** warehouseState;
	Specimen(Problem_Data *data);
	Specimen(const Specimen & nspec);
	Specimen();
	~Specimen();
};

