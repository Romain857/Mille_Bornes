#include "carteParade.h"
#include "Cartes.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <stdio.h>

using namespace std;


carteParade::carteParade(string nom, string parade) :Cartes(nom), parade(parade)
{

}
void carteParade::afficher()
{

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << " ------------------------- " << endl;
    cout << " |                       |" << endl;
    cout << " |C'est une carte borne  |" << endl;
    printf(" |%-23s|\n", this->parade.c_str()); //11
    cout << " |                       |" << endl;
    cout << " ------------------------- " << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

