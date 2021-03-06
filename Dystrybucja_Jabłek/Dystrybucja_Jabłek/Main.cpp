#include "FruitLib.h"

using namespace std;
int main(int argc, char* args[])
{
	
	// Generator liczb pseudolosowych
	minstd_rand0 generator;
	generator.seed(100);	
	// Zmienne
	bool stop = false , repeat = false;
	string confFile, dataFile, OutFile, SolutionFile;
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
	OutFile = dataFile;
	SolutionFile = dataFile;
	dataFile = "Problem_" + dataFile + ".csv";
	conf = new Configuration_Parameters(confFile);
	data = new Problem_Data(dataFile);
	//Pliki wyj�ciowe                                 trza tu poprawi� by by�y daty
	OutFile = "Out_" + OutFile + ".csv";
	SolutionFile = "Solution_" + SolutionFile + ".csv";
	ofstream Out((OutFile).c_str(), fstream::out);
	ofstream Solution((SolutionFile).c_str(), fstream::out);

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
	list<Specimen> breed; //potomstwo
	Specimen *child1 = new Specimen(data) , *child2 = new Specimen(data); //wska�niki na nowyh potomk�w
	int weakest = conf->breedAmount*(conf->breedAmount - 1);
	int theSame; // liczba osobnikow o takiej samej wartosci funkcji celu
	while (iteracje < conf->iteration)
	{
		it1 = generation.begin();
		it2 = generation.begin();
		//mutacje, krzy�owanie, funkcja celu
		for (int parent1 = 0; parent1 < conf->breedAmount; parent1++)
		{
			it1++;
			it2 = it1;
			it1--;
			for (int parent2 = parent1 + 1; parent2 < conf->breedAmount; parent2++)
			{
				cross1(child1, child2, &it1, &it2, &generator);
				mutate(child1, conf, &generator);
				mutate(child2, conf, &generator);
				countParameters(child1, data);
				countParameters(child2, data);
				//cout << child1->profit <<" "<< child1->punishment << endl;
				//cout << child2->profit << " " << child2->punishment << endl;
				breed.push_back(*child1);
				breed.push_back(*child2);
				it2 ++ ;
			}
			it1++;
		}		
		//Do��czanie nowych osobnik�w do populacji + sortowanie i eliminacja najs�abszych
		theSame = 0;
		while (!breed.empty())
		{
			nSpecimen = &(breed.back());
			it = generation.begin();
			while (it != generation.end() && it->profit > nSpecimen->profit)
			{
				it++;
			}
			if (it == generation.end())
				generation.push_back(*nSpecimen);
			else
			{
				if (it->profit != nSpecimen->profit)
					generation.insert(it, *nSpecimen);
				else
					theSame++;
			}
			breed.pop_back();
		}
		//Eliminacja najs�abszych
		for (int i = 0; i < weakest - theSame; i++)
			generation.pop_back();
		// Iteracje i zapis do pliku
		iteracje++;		
		Out << iteracje << ",";
		generation.front().write2stream(&Out, ',');
		generation.back().write2stream(&Out, ',');
		Out << endl;
		cout.precision(0);
		cout << (iteracje)* 100 / conf->iteration << "\%" << endl;
	} 
	//Ostatnie pokolenie
	it = generation.begin();
	while (it != generation.end())
	{
		cout << it->profit  << endl;
		it++;
	}
	//Najlepszy osobnik
	for (int i = 0; i < generation.front().customersAmount; i++)
	{		
		for (int j = 0; j < generation.front().speciesAmount; j++)
		{			
			for (int k = 0; k < 12; k++)
			{
				cout << generation.front().genome[i][j][k] << " ";
				Solution << generation.front().genome[i][j][k] << ";";
			}
			cout << endl;
			Solution << endl;
		}
		 cout << endl;
		 Solution << endl;
	}


	do 
	{
	} while (!_getch());
	Out.close();
	Solution.close();
	delete child1;
	delete child2;
	delete conf;
	delete data;
	generation.clear();

	breed.clear();

	return 0;
}