#include "Problem_Data.h"

Problem_Data::Problem_Data()
{
	chambersCapasity = 1;
	chambersAmount = 1;
	customersAmount = 1;
	speciesAmount= 1;
	palletsCapacity= 1;
	marketPrices = new double[speciesAmount][12];
	customerPrices = new double **[customersAmount];
	for (int i = 0; i < customersAmount; i++)
	{
		customerPrices[i] = new double *[speciesAmount];
		for (int j = 0; j < speciesAmount; j++)
		{
			customerPrices[i][j] = new double[12];
		}
	}
	customerOrders = new int **[customersAmount];
	for (int i = 0; i < customersAmount; i++)
	{
		customerOrders[i] = new int *[speciesAmount];
		for (int j = 0; j < speciesAmount; j++)
		{
			customerOrders[i][j] = new int[12];
		}
	}
}


Problem_Data::~Problem_Data()
{
	delete[] marketPrices;
	for (int i = 0; i < customersAmount; i++)
	{
		for (int j = 0; j < speciesAmount; j++)
		{
			delete[] customerPrices[i][j];
		}
		delete[] customerPrices[i];
	}
	delete[] customerPrices;
	for (int i = 0; i < customersAmount; i++)
	{
		for (int j = 0; j < speciesAmount; j++)
		{
			delete[] customerOrders[i][j];
		}
		delete[] customerOrders[i];
	}
	delete[] customerOrders;
	cout << "Destruktor obiektu Problem_Data" << endl;
}

Problem_Data::Problem_Data(string filename)
{
	chambersCapasity = 1;
	chambersAmount = 1;
	customersAmount = 1;
	speciesAmount = 1;
	palletsCapacity = 1;
	marketPrices = new double[speciesAmount][12];
	customerPrices = new double **[customersAmount];
	for (int i = 0; i < customersAmount; i++)
	{
		customerPrices[i] = new double *[speciesAmount];
		for (int j = 0; j < speciesAmount; j++)
		{
			customerPrices[i][j] = new double[12];
		}
	}
	customerOrders = new int **[customersAmount];
	for (int i = 0; i < customersAmount; i++)
	{
		customerOrders[i] = new int *[speciesAmount];
		for (int j = 0; j < speciesAmount; j++)
		{
			customerOrders[i][j] = new int[12];
		}
	}
	cout << "ELO :D" << endl;


	ifstream File((filename).c_str(), fstream::in);   //wczytywanie pliku
	if (!File)
	{
		File.close();
		cerr << "Blad podczas wczytywanie pliku " << filename << endl;
		chambersCapasity = 1;
		chambersAmount = 1;
		customersAmount = 1;
		speciesAmount = 1;
		palletsCapacity = 1;
		marketPrices = new double[speciesAmount][12];
		customerPrices = new double **[customersAmount];
		for (int i = 0; i < customersAmount; i++)
		{
			customerPrices[i] = new double *[speciesAmount];
			for (int j = 0; j < speciesAmount; j++)
			{
				customerPrices[i][j] = new double[12];
			}
		}
		customerOrders = new int **[customersAmount];
		for (int i = 0; i < customersAmount; i++)
		{
			customerOrders[i] = new int *[speciesAmount];
			for (int j = 0; j < speciesAmount; j++)
			{
				customerOrders[i][j] = new int[12];
			}
		}
	}
	string line;
	string dane[7];
	//Ignoruje pierwszy wiersz
	File >> line;

	//Wczytujê i interpretujê drugi wiersz
	File >> line;
	cout << line << endl;
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

	/////////////////////////
	chambersCapasity = 1;
	chambersAmount = 1;
	customersAmount = 1;
	speciesAmount = 1;
	palletsCapacity = 1;
	marketPrices = new double[speciesAmount][12];
	customerPrices = new double **[customersAmount];
	for (int i = 0; i < customersAmount; i++)
	{
		customerPrices[i] = new double *[speciesAmount];
		for (int j = 0; j < speciesAmount; j++)
		{
			customerPrices[i][j] = new double[12];
		}
	}
	customerOrders = new int **[customersAmount];
	for (int i = 0; i < customersAmount; i++)
	{
		customerOrders[i] = new int *[speciesAmount];
		for (int j = 0; j < speciesAmount; j++)
		{
			customerOrders[i][j] = new int[12];
		}
	}
}
