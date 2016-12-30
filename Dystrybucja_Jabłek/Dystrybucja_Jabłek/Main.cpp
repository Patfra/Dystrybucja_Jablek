#ifndef SPECIMEN
#include "Specimen.h"
#define SPECIMEN
#endif
#include <list>
#include <random>
#include <math.h>
#define CONF_END 10
#define DATA_END 4
#define PUNISHMENT 900 //300 kilo po 3 z³
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
				cout << data->customerOrders[k][i][j] << " ";
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
				//cout << nspec->genome[k][i][j] << "";
			}
		}
	}
	//cout << endl;
}
void countParameters(Specimen *spec, const Problem_Data *dane)
{
	//zerowanie tablic
	for (int j = 0; j < 12; j++)//miesi¹ce
	{
		for (int i = 0; i < spec->speciesAmount; i++)//gatunki
		{
			spec->bought[i][j] = 0;
			spec->warehouseState[i][j] = 0;
		}
	}
	//zlicznie kupionych  i sprzedanych jab³ek w ka¿dym z miesiêcy i zyski (funkcjê celu)
	for (int j = 0; j < 12; j++)//miesi¹ce
	{
		for (int i = 0; i < spec->speciesAmount; i++)//gatunki
		{
			for (int k = 0; k < spec->customersAmount; k++)//odbiorcy
			{
				if (spec->genome[k][i][j] > 0)
				{
					if (spec->genome[k][i][j] > 1)
						spec->profit += dane->customerOrders[k][i][j] * (dane->customerPrices[k][i][j] - dane->marketPrices[i][j + 1 - spec->genome[k][i][j]]);
					else
						spec->profit += dane->customerOrders[k][i][j] * dane->customerPrices[k][i][j];
					spec->warehouseState[i][j] -= dane->customerOrders[k][i][j];
					switch (spec->genome[k][i][j])
					{
					case 1:
					{
						spec->bought[i][0] += dane->customerOrders[k][i][j];
						break;
					}
					case 2:
					{
						spec->bought[i][1] += dane->customerOrders[k][i][j];
						break;
					}
					case 3:
					{
						spec->bought[i][2] += dane->customerOrders[k][i][j];
						break;
					}
					case 4:
					{
						spec->bought[i][3] += dane->customerOrders[k][i][j];
						break;
					}
					case 5:
					{
						spec->bought[i][4] += dane->customerOrders[k][i][j];
						break;
					}
					case 6:
					{
						spec->bought[i][5] += dane->customerOrders[k][i][j];
						break;
					}
					case 7:
					{
						spec->bought[i][6] += dane->customerOrders[k][i][j];
						break;
					}
					case 8:
					{
						spec->bought[i][7] += dane->customerOrders[k][i][j];
						break;
					}
					case 9:
					{
						spec->bought[i][8] += dane->customerOrders[k][i][j];
						break;
					}
					case 10:
					{
						spec->bought[i][9] += dane->customerOrders[k][i][j];
						break;
					}
					case 11:
					{
						spec->bought[i][10] += dane->customerOrders[k][i][j];
						break;
					}
					case 12:
					{
						spec->bought[i][11] += dane->customerOrders[k][i][j];
						break;
					}
					default:
						break;
					}
				}
							
			}
		}
	}
	//Ustalenie stanu przechowalni
	for (int i = 0; i < spec->speciesAmount; i++)//gatunki
	{
		spec->warehouseState[i][0] += spec->bought[i][0];
	}
	for (int j = 1; j < 12; j++)//miesi¹ce
	{
		for (int i = 0; i < spec->speciesAmount; i++)//gatunki
		{
			spec->warehouseState[i][j] += spec->warehouseState[i][j - 1] + spec->bought[i][j];
		}
	}
	//wylicznie kosztów i funkcji kary
	int chambersInUse = 0;
	for (int i = 0; i < spec->speciesAmount; i++)//gatunki
	{		
		chambersInUse+=  ceil(double(spec->warehouseState[i][0] + spec->bought[i][0])/ (2 * dane->chambersCapasity));
	}
	if (chambersInUse <= dane->chambersAmount)
		spec->profit - chambersInUse * dane->chambersKeepCosts[0];
	else
	{
		spec->profit -= dane->chambersAmount * dane->chambersKeepCosts[0];
		spec->punishment += (chambersInUse - dane->chambersAmount) * PUNISHMENT * dane->chambersCapasity;
	}
	for (int j = 1; j < 12; j++)//miesi¹ce
	{
		chambersInUse = 0;
		for (int i = 0; i < spec->speciesAmount; i++)//gatunki
		{
			chambersInUse += ceil(double(spec->warehouseState[i][j] + spec->bought[i][j]) / (2*dane->chambersCapasity));
		}
		if (chambersInUse <= dane->chambersAmount)
			spec->profit -= chambersInUse * dane->chambersKeepCosts[j];
		else
		{
			spec->profit -= dane->chambersAmount * dane->chambersKeepCosts[j];
			spec->punishment += (chambersInUse - dane->chambersAmount) * PUNISHMENT * dane->chambersCapasity;
		}
	}
	spec->profit -= spec->punishment;
	//for (int j = 0; j < 12; j++)//miesi¹ce
	//{
	//	for (int i = 0; i < spec->speciesAmount; i++)//gatunki
	//	{
	//		cout << spec->bought[i][j] << " ";
	//	}
	//	cout << "   ";
	//	for (int i = 0; i < spec->speciesAmount; i++)//gatunki
	//	{
	//		cout << spec->warehouseState[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << spec->profit<< endl;
	//cout << spec->punishment;
	//cout << endl;

}
int main()
{
	// Generator liczb pseudolosowych
	minstd_rand0 generator;
	generator.seed(0);	
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
		while (it->profit > nSpecimen->profit && it != generation.end())
			it++;
		generation.insert(it, *nSpecimen);
	}
	it = generation.begin();
	while (it != generation.end())
	{
		cout << it->profit << endl;
		it++;
	}
	delete nSpecimen;
	delete conf;
	delete data;
	generation.clear();
	do {
		// Iteracje, mutacje, krzy¿owanie, funkcja celu, zapis danych do pliku
	} while ( !_getch() );

	return 0;
}