#include "FruitLib.h"


//Sprawdza czy z klawiatury wpisano liczbê czy nie
bool is_number(const string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it))
		++it;
	return !s.empty() && it == s.end();
}

//Wypisujê wczytane wartoœci z plików na ekran
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
//Inicjuje osobnika z pierwszego pokolenia
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
//Wylicza funkcjê celu, kary i pomocnicze wartoœci
void countParameters(Specimen *spec, const Problem_Data *dane)
{
	//zerowanie funkcji celu, kary i liczby mutaji
	spec->profit = 0;
	spec->punishment = 0;
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
		chambersInUse += ceil(double(spec->warehouseState[i][0] + spec->bought[i][0]) / (2 * dane->chambersCapasity));
	}
	if (chambersInUse <= dane->chambersAmount)
		spec->profit -= chambersInUse * dane->chambersKeepCosts[0];
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
			chambersInUse += ceil(double(spec->warehouseState[i][j] + spec->bought[i][j]) / (2 * dane->chambersCapasity));
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


//Operatory krzy¿owania
void cross1(Specimen * child1, Specimen * child2, list<Specimen>::iterator * parent1, list<Specimen>::iterator * parent2, minstd_rand0 *generator)
{
	//zerowanie funkcji celu, kary i liczby mutaji
	child1->profit = child2->profit = 0;
	child1->punishment= child2->punishment = 0;
	child1->mutationAmount = child2->mutationAmount = 0;
	//krzy¿owanie
	for (int j = 0; j < 12; j++)//miesi¹ce
	{
		for (int i = 0; i < child1->speciesAmount; i++)//gatunki
		{
			for (int k = 0; k < child1->customersAmount; k++)//odbiorcy
			{
				switch ((*generator)() % 2)
				{
				case 0://geny od pierwszego rodzica
					{
						child1->genome[k][i][j] = parent1->_Ptr->_Myval.genome[k][i][j];
						child2->genome[k][i][j] = parent2->_Ptr->_Myval.genome[k][i][j];
						break;
					}
				case 1://geny od drugiego rodzica
					{
						child1->genome[k][i][j] = parent2->_Ptr->_Myval.genome[k][i][j];
						child2->genome[k][i][j] = parent1->_Ptr->_Myval.genome[k][i][j];
						break;
					}
				default:
					break;
				}
			}
		}
	}
}
void cross2(Specimen * child1, Specimen * child2, list<Specimen>::iterator * parent1, list<Specimen>::iterator * parent2, minstd_rand0 *generator)
{

}
//Operatory mutacji
void mutate(Specimen * spec, Configuration_Parameters *conf, minstd_rand0 *generator)
{
	spec->mutationAmount = 0;
	for (int j = 0; j < 12; j++)//miesi¹ce
	{
		for (int i = 0; i < spec->speciesAmount; i++)//gatunki
		{
			for (int k = 0; k < spec->customersAmount; k++)//odbiorcy
			{			
				if ((*generator)() < generator->max() *conf->mutationFactor)
				{
					spec->genome[k][i][j] = (*generator)() % (j + 2); //mutacja
					spec->mutationAmount ++;  //zwiêkszenie liczby mutacji
				}

				
			}
		}
	}
}