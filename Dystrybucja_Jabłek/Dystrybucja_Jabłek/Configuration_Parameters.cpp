#include "Configuration_Parameters.h"


Configuration_Parameters::Configuration_Parameters()
{
	mutationFactor = 0;
	populationAmount = 0;
	breedAmount = 0;
	iterationON = 0;
	iteration = 0;
	margin = 0;
	marginRange = 0;
}

Configuration_Parameters::Configuration_Parameters(string filename)
{
	ifstream File((filename).c_str(), fstream::in);   //wczytywanie pliku
	if (!File)
	{
		File.close();
		cerr << "Blad podczas wczytywanie pliku " << filename << endl;
		mutationFactor = 0;
		populationAmount = 0;
		breedAmount = 0;
		iterationON = 0;
		iteration = 0;
		margin = 0;
		marginRange = 0;
	}
	string line;
	string dane[7];
	//Ignoruje pierwszy wiersz
	File >> line;
	
	//Wczytujê i interpretujê drugi wiersz
	File >> line;
	int dane_it = 0;
	string::const_iterator it = line.begin();
	while (line.end() != it)
	{
		if ((*it) != ';')
			dane[dane_it] = dane[dane_it] + (*it);
		else
		{			
			dane_it++;
		}
		++it;
	}	
	while (File.good())
	{
		File >> line;
	}
	File.close();


	mutationFactor = stod(dane[0]);
	populationAmount = stoi(dane[1]);
	breedAmount = stoi(dane[2]);
	iterationON = stoi(dane[3]);
	iteration = stoi(dane[4]);
	margin = stoi(dane[5]);
	marginRange = stoi(dane[6]);
}

Configuration_Parameters::~Configuration_Parameters()
{
	cout << "Destruktor obiektu Configuration_Parameters" << endl;
}
