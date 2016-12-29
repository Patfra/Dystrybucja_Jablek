#pragma once
#include "Problem_Data.h"
class Configuration_Parameters
{
public:

	double mutationFactor;
	int populationAmount;
	int breedAmount;
	bool iterationON;
	int iteration;
	int margin;
	int marginRange;


	Configuration_Parameters();
	~Configuration_Parameters();
	Configuration_Parameters( string filename );
};

