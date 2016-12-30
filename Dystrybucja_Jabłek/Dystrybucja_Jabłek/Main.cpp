#ifndef SPECIMEN
#include "Specimen.h"
#define SPECIMEN
#endif
#include <list>
#include <random>
#define CONF_END 10
#define DATA_END 4
//Sprawdza czy z klawiatury wpisano liczbê czy nie
bool is_number(const string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) 
		++it;
	return !s.empty() && it == s.end();
}

void writeParameters(Problem_Data * data, Configuration_Parameters * conf)
{
	cout << conf->mutationFactor << " ";
	cout << conf->populationAmount << " ";
	cout << conf->breedAmount << " ";
	cout << conf->iterationON << " ";
	cout << conf->iteration << " ";
	cout << conf->margin << " ";
	cout << conf->marginRange << endl;

	cout << data->chambersCapasity << " ";
	cout << data->chambersAmount << " ";
	cout << data->customersAmount << " ";
	cout << data->speciesAmount << endl;
	for (int i = 0; i < data->speciesAmount; i++)
	{
		for (int j = 0; j < 12; j++)
			cout << data->marketPrices[i][j] << " ";
		cout << endl;
	}
	for (int k = 0; k < data->customersAmount; k++)
	{
		for (int i = 0; i < data->speciesAmount; i++)
		{
			for (int j = 0; j < 12; j++)
				cout << data->customerPrices[k][i][j] << " ";
			cout << endl;
		}
	}
	for (int k = 0; k < data->customersAmount; k++)
	{
		for (int i = 0; i < data->speciesAmount; i++)
		{
			for (int j = 0; j < 12; j++)
				cout << data->customerPrices[k][i][j] << " ";
			cout << endl;
		}
	}
	for (int j = 0; j < 12; j++)
		cout << data->chambersKeepCosts[j] << " ";
	cout << endl;
}
void initSpecimen(Specimen *nspec, minstd_rand0 *generator)
{
	for (int j = 0; j < 12; j++)//miesi¹ce
	{		
		for (int i = 0; i < nspec->speciesAmount; i++)//gatunki
		{
			for (int k = 0; k < nspec->customersAmount; k++)//odbiorcy
			{
				nspec->genome[k][i][j] = (*generator)() % (j + 2);
				cout << nspec->genome[k][i][j] << "";
			}
		}
	}
	cout << endl;
}

int main()
{
	// Generator liczb pseudolosowych
	minstd_rand0 generator;
	generator.seed(0);
	cout << generator();
	// Zmienne
	bool stop = false , repeat = false;
	int test;
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
	writeParameters(data, conf);
	//Generacja Pokolenia
	list<Specimen> generation;
	Specimen *nSpecimen;
	nSpecimen = new Specimen(data);
	for(int i = 0; i < conf->populationAmount; i++)
	{
		//tworze nowego osobnika
		initSpecimen(nSpecimen, &generator);
		generation.push_back(*nSpecimen);
	}

	delete conf;
	delete data;
	do {
		// Iteracje, mutacje, krzy¿owanie, funkcja celu, zapis danych do pliku
	} while ( !_getch() );

	return 0;
}










//data = new Problem_Data(dataFile);

//// to na razie jest wstêp
//while (true)
//{
//	cout << "Podaj liczbe :" << endl;
//	cin >> test;
//	if (test > 1000)
//		break;
//	else
//		cout << "Liczba za ma³a" << endl;
//	data = new Problem_Data;
//	delete data;
//	data = new Problem_Data(confFile);
//	delete data;
//	
//}