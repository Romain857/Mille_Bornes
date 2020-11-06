#include "cartesAttaque.h"
#include "Cartes.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <stdio.h>




using namespace std;



cartesAttaque::cartesAttaque(string nom, string attaque) :Cartes(nom), attaque(attaque)
{

}

void cartesAttaque::afficher()
{

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);


    cout << " ------------------------- " << endl;
    cout << " |                       |" << endl;
    cout << " |C'est une carte borne  |" << endl;
    printf(" |%-23s|\n", this->attaque.c_str()); //11
    cout << " |                       |" << endl;
    cout << " ------------------------- " << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
