#pragma once
#include"listeJoueurs.h"
#include "joueur.h"
#include "Deck.h"
#include <vector>


class jeu
{
public:
	void deroulementJeu(listeJoueurs*, Deck*, int);

	void jouerCartes(int, int, int, Deck*, listeJoueurs*);

	void choixCarte(int, int, int, Deck*, listeJoueurs*);

	void afficherMenu();

};

