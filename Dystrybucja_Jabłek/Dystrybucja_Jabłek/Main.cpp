#ifndef FRUIT
#include "FruitLib.h"
#define FRUIT
#endif

int main()
{
	// Generator liczb pseudolosowych
	minstd_rand0 generator;
	generator.seed(0);	
	// Zmienne
	bool stop = false , repeat = false;
	string confFile, dataFile;
	Problem_Data * data;
	Configuration_Parameters * conf;
	//==============================================================================
	//Poprawne wczytanie numeru pliku konfiguracyjnego
	do {
		cout << "Podaj numer pliku konfiguracyjnego (1 - " << CONF_END << " ):   ";
		cin >> confFile;
		repeat = (!is_number(confFile) || (1 > stoi(confFile) || CONF_END < stoi(confFile)));
		if(repeat)
			cout << "Zle dane!!" << endl;
	} while (repeat);
	repeat = false;
	confFile = "Conf_" + confFile + ".csv";
	//==============================================================================
	//Poprawne wczytanie numeru pliku z danymi
	do {
		cout << "Podaj numer pliku z danymi (1 - " << DATA_END << " ):   ";
		cin >> dataFile;
		repeat = (!is_number(dataFile) || (1 > stoi(dataFile) || DATA_END < stoi(dataFile)));
		if (repeat)
			cout << "Zle dane!!" << endl;
	} while (repeat);
	repeat = false;
	dataFile = "Problem_" + dataFile + ".csv";
	conf = new Configuration_Parameters(confFile);
	data = new Problem_Data(dataFile);
	//writeParameters(data, conf);
	//Generacja Pokolenia
	list<Specimen> generation;
	list<Specimen>::iterator it;
	Specimen *nSpecimen;
	nSpecimen = new Specimen(data);
	//tworzenie pierwszego osobnika
	initSpecimen(nSpecimen, &generator);
	countParameters(nSpecimen, data);	
	generation.push_back(*nSpecimen);
	for(int i = 1; i < conf->populationAmount; i++)
	{
		//tworzenie nowego osobnika
		initSpecimen(nSpecimen, &generator);
		countParameters(nSpecimen, data);
		it = generation.begin();
		while (it != generation.end() && it->profit > nSpecimen->profit)
		{
			it++;
		}
		if(it == generation.end())
			generation.push_back(*nSpecimen);
		else

			generation.insert(it, *nSpecimen);
	}
	it = generation.begin();
	while (it != generation.end())
	{
		cout << it->profit << endl;	
		it++;
	}
	cout << endl;
	int iteracje = 0;
	list<Specimen>::iterator it1;
	list<Specimen>::iterator it2;
	while (iteracje < 1)
	{
		it1 = generation.begin();
		it2 = generation.begin();
		// Iteracje, mutacje, krzy¿owanie, funkcja celu, zapis danych do pliku
		for (int parent1 = 0; parent1 < conf->breedAmount; parent1++)
		{
			it1++;
			it2 = it1;
			it1--;
			for (int parent2 = parent1 + 1; parent2 < conf->breedAmount; parent2++)
			{
				cross1(nSpecimen, &it1, &it2, &generator);
				mutate(nSpecimen, conf, &generator);
				countParameters(nSpecimen, data);
				cout << nSpecimen->profit <<" "<< nSpecimen->punishment << endl;
				it2 ++ ;
			}
			it1++;
		}
		cout << endl;
		iteracje++;
	} 

	it = generation.begin();
	while (it != generation.end())
	{
		cout << it->profit << endl;
		it++;
	}

	do 
	{
		// Iteracje, mutacje, krzy¿owanie, funkcja celu, zapis danych do pliku
	} while (!_getch());
	delete nSpecimen;
	delete conf;
	delete data;
	generation.clear();

	return 0;
}