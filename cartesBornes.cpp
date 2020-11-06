#include "cartesBornes.h"
#include "Cartes.h"
#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;

cartesBornes::cartesBornes(string nom, int bornes) :Cartes(nom), bornes(bornes)
{

}

void cartesBornes::afficher()
{
    cout << " ------------------------- " << endl;
    cout << " |                       |" << endl;
    cout << " |C'est une carte borne  |" << endl;
    printf(" |%-23d|\n", this->bornes); //11
    cout << " |                       |" << endl;
    cout << " ------------------------- " << endl;
}
