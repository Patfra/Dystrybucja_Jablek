#include "Problem_Data.h"

Problem_Data::Problem_Data()
{
	chambersCapasity = 1;
	chambersAmount = 1;
	customersAmount = 1;
	speciesAmount= 1;
	marketPrices = new int *[speciesAmount];
	for (int j = 0; j < speciesAmount; j++)
	{
		marketPrices[j] = new int[12];
	}
	customerPrices = new int **[customersAmount];
	for (int i = 0; i < customersAmount; i++)
	{
		customerPrices[i] = new int *[speciesAmount];
		for (int j = 0; j < speciesAmount; j++)
		{
			customerPrices[i][j] = new int[12];
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
	for (int i = 0; i < speciesAmount; i++)
	{		
		delete[] marketPrices[i];
	}
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
	ifstream File((filename).c_str(), fstream::in);   //wczytywanie pliku
	if (!File)
	{
		File.close();
		cerr << "Blad podczas wczytywanie pliku " << filename << endl;
		chambersCapasity = 1;
		chambersAmount = 1;
		customersAmount = 1;
		speciesAmount = 1;
		marketPrices = new int *[speciesAmount];
		for (int j = 0; j < speciesAmount; j++)
		{
			marketPrices[j] = new int[12];
		}
		customerPrices = new int **[customersAmount];
		for (int i = 0; i < customersAmount; i++)
		{
			customerPrices[i] = new int *[speciesAmount];
			for (int j = 0; j < speciesAmount; j++)
			{
				customerPrices[i][j] = new int[12];
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
	else {
		string line;
		string dane[4];
		//Ignoruje pierwszy wiersz
		getline(File, line);
		//cout << line << endl;
		//Wczytujê i interpretujê drugi wiersz
		getline(File, line);
		//cout << line << endl;
		int dane_it = 0;
		string::const_iterator it = line.begin();
		while (line.end() != it && dane_it != 4)
		{
			if ((*it) != ';')
				dane[dane_it] = dane[dane_it] + (*it);
			else
			{
				dane_it++;
			}
			++it;
		}

		///////////////////////////
		chambersCapasity = stoi(dane[0]);
		chambersAmount = stoi(dane[1]);
		customersAmount = stoi(dane[2]);
		speciesAmount = stoi(dane[3]);
		marketPrices = new int *[speciesAmount];
		for (int j = 0; j < speciesAmount; j++)
		{
			marketPrices[j] = new int[12];
		}
		customerPrices = new int **[customersAmount];
		for (int i = 0; i < customersAmount; i++)
		{
			customerPrices[i] = new int *[speciesAmount];
			for (int j = 0; j < speciesAmount; j++)
			{
				customerPrices[i][j] = new int[12];
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
		//Ignoruje trzeci wiersz
		getline(File, line);
		//cout << line << endl;
		//Wczytujê ceny runkowe
		string tmp;
		for (int i = 0; i < speciesAmount; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				getline(File, tmp, ';');
				//cout << tmp << " ";
				marketPrices[i][j] = stoi(tmp);
			}
			//cout << endl;
			//ignorujê pozosta³e znaki w lini je¿eli jakieœ s¹
			if (File.peek() != '\n')
				getline(File, line);
		}
		//ignorujê wiersz oddzielaj¹cy
		getline(File, line);
		//cout << line << endl;
		//Wczytujê ceny odbiorców
		for (int k = 0; k < customersAmount; k++)
		{
			for (int i = 0; i < speciesAmount; i++)
			{
				for (int j = 0; j < 12; j++)
				{
					getline(File, tmp, ';');
					//cout << tmp << " ";
					customerPrices[k][i][j] = stoi(tmp);
				}
				//cout << endl;
				//ignorujê pozosta³e znaki w lini je¿eli jakieœ s¹
				if (File.peek() != '\n')
					getline(File, line);					
			}
		}
		//ignorujê wiersz oddzielaj¹cy
		getline(File, line);
		//cout << line << endl;
		//Wczytujê zamówienia odbiorców
		for (int k = 0; k < customersAmount; k++)
		{
			for (int i = 0; i < speciesAmount; i++)
			{
				for (int j = 0; j < 12; j++)
				{
					getline(File, tmp, ';');
					//cout << tmp << " ";
					customerPrices[k][i][j] = stoi(tmp);
				}
				//cout << endl;
				//ignorujê pozosta³e znaki w lini je¿eli jakieœ s¹
				if (File.peek() != '\n')
					getline(File, line);
			}
		}
		//ignorujê wiersz oddzielaj¹cy
		getline(File, line);
		//cout << line << endl;
		//Wczytujê koszty utrzymania
		for (int j = 0; j < 12; j++)
		{
			getline(File, tmp, ';');
			//cout << tmp << " ";
			chambersKeepCosts[j] = stoi(tmp);
		}
		//cout << endl;
		File.close();
	}
}
