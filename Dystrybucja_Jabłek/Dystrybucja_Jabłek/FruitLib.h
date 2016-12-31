#pragma once
#include "Specimen.h"
#include <list>
#include <random>
#include <math.h>

#define CONF_END 10
#define DATA_END 4
#define PUNISHMENT 900 //300 kilo po 3 z³

//Sprawdza czy z klawiatury wpisano liczbê czy nie
bool is_number(const string& s);

//Wypisujê wczytane wartoœci z plików na ekran
void writeParameters(Problem_Data * data, Configuration_Parameters * conf);

//Inicjuje osobnika z pierwszego pokolenia
void initSpecimen(Specimen *nspec, minstd_rand0 *generator);

//Wylicza funkcjê celu, kary i pomocnicze wartoœci
void countParameters(Specimen *spec, const Problem_Data *dane);
//Operatory krzy¿owania
void cross1(Specimen * child1, Specimen * child2, list<Specimen>::iterator * parent1, list<Specimen>::iterator * parent2, minstd_rand0 *generator);
void cross2(Specimen * child1, Specimen * child2, list<Specimen>::iterator * parent1, list<Specimen>::iterator * parent2, minstd_rand0 *generator);
//Operatory mutacji
void mutate(Specimen * spec, Configuration_Parameters *conf, minstd_rand0 *generator);
