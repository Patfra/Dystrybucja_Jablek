#pragma once
#include "Specimen.h"
#include <list>
#include <random>
#include <math.h>

#define CONF_END 10
#define DATA_END 4
#define PUNISHMENT 900 //300 kilo po 3 z�

//Sprawdza czy z klawiatury wpisano liczb� czy nie
bool is_number(const string& s);

//Wypisuj� wczytane warto�ci z plik�w na ekran
void writeParameters(Problem_Data * data, Configuration_Parameters * conf);

//Inicjuje osobnika z pierwszego pokolenia
void initSpecimen(Specimen *nspec, minstd_rand0 *generator);

//Wylicza funkcj� celu, kary i pomocnicze warto�ci
void countParameters(Specimen *spec, const Problem_Data *dane);
//Operatory krzy�owania
void cross1(Specimen * nspec, list<Specimen>::iterator * parent1, list<Specimen>::iterator * parent2, minstd_rand0 *generator);
void cross2(Specimen * nspec, list<Specimen>::iterator * parent1, list<Specimen>::iterator * parent2, minstd_rand0 *generator);
//Operatory mutacji
void mutate(Specimen * spec, Configuration_Parameters *conf, minstd_rand0 *generator);
