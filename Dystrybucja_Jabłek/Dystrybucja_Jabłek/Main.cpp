#ifndef PARAMETRY_KONFIGURACYJNE
#include "Parametry_Konfiguracyjne.h"
#define PARAMETRY_KONFIGURACYJNE
#endif

int main()
{
	// to na razie jest wstêp
	bool stop = false;
	int a;
	string file = "Conf_1";
	Parametry_Konfiguracyjne * conf;
	while (true)
	{
		cout << "Podaj liczbe :" << endl;
		cin >> a;
		if (a > 1000)
			break;
		else
			cout << "Liczba za ma³a" << endl;
		conf = new Parametry_Konfiguracyjne;
		delete conf;
		conf = new Parametry_Konfiguracyjne(file);
		delete conf;
		
	}
	do {

	} while ( !_getch() );
	return 0;
}