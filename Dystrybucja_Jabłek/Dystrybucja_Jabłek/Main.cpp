#ifndef PROBLEM_DATA
#include "Problem_Data.h"
#define PROBLEM_DATA
#endif
#ifndef CONF_PARAM
#include "Configuration_Parameters.h"
#define CONF_PARAM
#endif
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

int main()
{
	bool stop = false , repeat = false;
	int test;
	string confFile, dataFile;
	Problem_Data * data;
	Configuration_Parameters * conf;
	//==============================================================================
	//Poprawne wczytanie numeru pliku konfiguracyjnego
	do {
		cout << "Podaj numer pliku konfiguracyjnego (1 -" << CONF_END << " ):   ";
		cin >> confFile;
		repeat = (!is_number(confFile) || (1 > stoi(confFile) || CONF_END < stoi(confFile)));
		if(repeat)
			cout << "Zle dane!!" << endl;
	} while (repeat);
	repeat = false;
	confFile = "Conf_" + confFile + ".csv";
	cout << confFile << endl;
	//==============================================================================
	//Poprawne wczytanie numeru pliku z danymi
	do {
		cout << "Podaj numer pliku z danymi (1 -" << DATA_END << " ):   ";
		cin >> dataFile;
		repeat = (!is_number(dataFile) || (1 > stoi(dataFile) || DATA_END < stoi(dataFile)));
		if (repeat)
			cout << "Zle dane!!" << endl;
	} while (repeat);
	repeat = false;
	dataFile = "Problem_" + dataFile + ".csv";
	cout << dataFile << endl;
	conf = new Configuration_Parameters(confFile);
	cout << conf->mutationFactor << endl;	
	cout << conf->populationAmount << endl;
	cout << conf->breedAmount << endl;
	cout << conf->iterationON << endl;
	cout << conf->iteration << endl;
	cout << conf->margin << endl;
	cout << conf->marginRange << endl;
	data = new Problem_Data(dataFile);


	delete conf;
	do {

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