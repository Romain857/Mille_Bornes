#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <stdio.h>
#include "joueur.h"
#include "Deck.h"
//#include "mainJoueur.h"
#include "listeJoueurs.h"
#include "jeu.h"


using namespace std;

int main() {



	cout << endl << "Bienvenue dans le jeu Mille-Bornes" << endl;
	jeu* jeux = new jeu;
	jeux->afficherMenu();

	int i;
	cout << "Combien de joueurs etes-vous ? ";
	cin >> i;

	srand(time(NULL));
	Deck* deck = new Deck;
	deck->chargerDeck();
	deck->melange();
	//deck->afficherdeck();
	system("pause");

	listeJoueurs* Joueurs = new listeJoueurs;
	Joueurs->distribution(deck, i);



	jeux->deroulementJeu(Joueurs, deck, i);

	return 0;


	//cout << "Les joueurs present dans la game" << endl;





	//random_shuffle(Joueurs.begin(), Joueurs.end());

/*	Joueurs[0]->afficher();
	Joueurs[1]->afficher();
	Joueurs[2]->afficher();
	Joueurs[3]->afficher();
	*/




	/*for (tour = 1; tour <= i + 1; tour++) {
		if (tour == i + 1) {
			tour = 1;
		}
		cout << "Voici la main du joueur " << tour << endl;
		mesMains[tour]->afficher();
		cout << "Voulez vous vous defaussez ou jouer une carte ? 1 = jouer une carte 2 = defausse" << endl;
		cin >> defausse;
		while (defausse >= 3 || defausse <= 0) {
			cout << " faites un choix valide entre 1 ou 2 (1 pour jouer une carte 2 pour la defausse)" << endl;
			cin >> defausse;
		}
		if (defausse == 1) {
			cout << "Choisissez une carte a jouer" << endl;
			cin >> choix;
			while (choix >= 8 || choix <= 0) {
				cout << " faites un choix valide entre 1 et 7" << endl;
				cin >> choix;
			}
			listeJoueurs->getJoueurs()[tour - 1];//->jouerCartes(tour, choix, mesMains[tour], deck);
			mesMains[tour]->choisir(tour, choix, deck);
		}
		else {
			cout << "Quelle carte voulez vous defaussez ?" << endl;
			cin >> choix;
			mesMains[tour]->choisir(tour, choix, deck);
		}

	}*/

	/*
	string nom[4];

	 cout << "Quel est le nom du premier joueur ?" << endl;
	 cin >> nom[0];
	 cout << endl << "Quel est le nom du second joueur ?" << endl;
	 cin >> nom[1];
	 cout << "Quel est le nom du premier joueur ?" << endl;
	 cin >> nom[2];
	 cout << endl << "Quel est le nom du second joueur ?" << endl;
	 cin >> nom[3];
	 system("cls");
	 */

}
