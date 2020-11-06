#include "jeu.h"
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

#include "listeJoueurs.h"



void jeu::deroulementJeu(listeJoueurs* Joueurs, Deck* deck, int i) {
    int tour;
    int choix;
    int defausse;

    for (tour = 1; tour <= i + 1; tour++) {
        if (tour == i + 1) {
            tour = 1;
        }
        system("cls");
        Joueurs->getJoueurs()[tour - 1]->afficherEtat();
        cout << "Voici la main du joueur " << tour << endl;
        Joueurs->getJoueurs()[tour - 1]->afficherMain();
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
            this->jouerCartes(tour, choix, i, deck, Joueurs);
            Joueurs->getJoueurs()[tour - 1]->choisir(tour, choix, deck);
        }
        else {
            cout << "Quelle carte voulez vous defaussez ?" << endl;
            cin >> choix;
            Joueurs->getJoueurs()[tour - 1]->choisir(tour, choix, deck);
        }

    }
}

void jeu::jouerCartes(int tour, int choix, int i, Deck* deck, listeJoueurs* Joueurs) {
    //récupération toute variable

    //récup Etat conduite
    int creve = Joueurs->getJoueurs()[tour - 1]->getCreve();
    int accident = Joueurs->getJoueurs()[tour - 1]->getAccident();
    int feuRouge = Joueurs->getJoueurs()[tour - 1]->getFeuRouge();
    int essence = Joueurs->getJoueurs()[tour - 1]->getEssence();
    int limitation = Joueurs->getJoueurs()[tour - 1]->getLimitation();

    //récup Bottes
    int antiCreve = Joueurs->getJoueurs()[tour - 1]->getAntiCreve();
    int antiAcci = Joueurs->getJoueurs()[tour - 1]->getAntiAcci();
    int antiEssen = Joueurs->getJoueurs()[tour - 1]->getAntiEssen();
    int antiFeu = Joueurs->getJoueurs()[tour - 1]->getAntiFeu();

    int stade = Joueurs->getJoueurs()[tour - 1]->getStade();



    string nomCarte = Joueurs->getJoueurs()[tour - 1]->getMainJoueur()[choix - 1]->getNom();



    if (nomCarte == "Bornes") {
        if (creve == 1 || accident == 1 || feuRouge == 1 || essence == 1) {
            cout << "Vous ne pouvez pas utilisez cette carte! Utilisez une carte Parade ou defaussez vous ou attaquez un adversaire" << endl;
            this->choixCarte(tour, choix, i, deck, Joueurs);

        }
        else {
            int bornes = Joueurs->getJoueurs()[tour - 1]->getMainJoueur()[choix - 1]->getBornes();
            if (limitation == 1) {
                if (bornes <= 50) {
                    Joueurs->getJoueurs()[tour - 1]->setStade(stade + bornes);


                }
                else {
                    cout << "vous ne pouvez pas jouez cette carte vous etes limite a 50. Choississez une autre Cartes" << endl;

                    this->choixCarte(tour, choix, i, deck, Joueurs);

                }

            }
            if (bornes + stade > 1000) {
                cout << "vous ne pouvez pas jouer cette carte elle vous emmene plus loin que 1000" << endl;
                this->choixCarte(tour, choix, i, deck, Joueurs);
            }
            else {
                Joueurs->getJoueurs()[tour - 1]->setStade(stade + bornes);

            }

        }
    }

    if (nomCarte == "Bottes") {
        string Bottes = Joueurs->getJoueurs()[tour - 1]->getMainJoueur()[choix - 1]->getBottes();
        if (Bottes == "Camion Citerne") {

            Joueurs->getJoueurs()[tour - 1]->setAntiEssen(1);
            Joueurs->getJoueurs()[tour - 1]->setEssence(0);
            cout << "Vous etes maintenant insensible aux pannes d'essence !" << endl;
        }
        if (Bottes == "Prioritaire") {

            Joueurs->getJoueurs()[tour - 1]->setAntiFeu(1);
            Joueurs->getJoueurs()[tour - 1]->setFeuRouge(0);
            Joueurs->getJoueurs()[tour - 1]->setLimitation(0);
            cout << "Vous etes maintenant insensible aux feu rouges !" << endl;
        }
        if (Bottes == "Increvable") {
            Joueurs->getJoueurs()[tour - 1]->setCreve(0);
            Joueurs->getJoueurs()[tour - 1]->setAntiCreve(1);
            cout << "Vous etes maintenant insensible aux crevaisons !" << endl;
        }
        if (Bottes == "As du volant") {
            Joueurs->getJoueurs()[tour - 1]->setAccident(0);
            Joueurs->getJoueurs()[tour - 1]->setAntiAcci(1);
            cout << "Vous etes maintenant insensible aux accidents!" << endl;
        }
    }

    if (nomCarte == "Attaque") {


        string Attaque = Joueurs->getJoueurs()[tour - 1]->getMainJoueur()[choix - 1]->getAttaque();
        int cible;

        if (Attaque == "Crevaison") {



            cout << " Quelle joueur veux tu goumer ?" << endl;
            cin >> cible;
            while (cible <= 0 || cible >= i + 1) {
                cout << "Choisi un joueur valide " << endl;
                cin >> cible;
            }
            int checkAttaque = Joueurs->getJoueurs()[cible - 1]->getCreve();
            int checkBotte = Joueurs->getJoueurs()[cible - 1]->getAntiCreve();

            if (checkBotte == 1)
            {
                cout << "vous ne pouvez pas l'attaquer il à utiliser car il a la botte qui le contre" << endl;
                this->choixCarte(tour, choix, i, deck, Joueurs);
            }

            if (checkAttaque == 1)
            {
                cout << "vous ne pouvez pas l'attaquer car il à déja cette attaque sur lui" << endl;
                this->choixCarte(tour, choix, i, deck, Joueurs);
            }
            else

                Joueurs->getJoueurs()[cible - 1]->setFeuRouge(1);
            cout << "Le joueur " << cible << " ne peux plus avancer" << endl;
        }
        if (Attaque == "Feu rouge") {




            cout << " Quelle joueur veux tu goumer ?" << endl;
            cin >> cible;
            while (cible <= 0 || cible >= i + 1) {
                cout << "Choisi un joueur valide " << endl;
                cin >> cible;
            }

            int checkBotte = Joueurs->getJoueurs()[cible - 1]->getAntiFeu();
            int checkAttaque = Joueurs->getJoueurs()[cible - 1]->getFeuRouge();

            if (checkBotte == 1)
            {
                cout << "vous ne pouvez pas l'attaquer il à utiliser car il a la botte qui le contre" << endl;
                this->choixCarte(tour, choix, i, deck, Joueurs);
            }
            if (checkAttaque == 1)
            {
                cout << "vous ne pouvez pas l'attaquer car il à déja cette attaque sur lui" << endl;
                this->choixCarte(tour, choix, i, deck, Joueurs);
            }
            else
                Joueurs->getJoueurs()[cible - 1]->setFeuRouge(1);
            cout << "Le joueur " << cible << " ne peux plus avancer" << endl;
        }
        if (Attaque == "Panne d'essence") {




            cout << " Quelle joueur veux tu goumer ?" << endl;
            cin >> cible;
            while (cible <= 0 || cible >= i + 1) {
                cout << "Choisi un joueur valide " << endl;
                cin >> cible;
            }

            int checkBotte = Joueurs->getJoueurs()[cible - 1]->getAntiEssen();
            int checkAttaque = Joueurs->getJoueurs()[cible - 1]->getEssence();

            if (checkBotte == 1)
            {
                cout << "vous ne pouvez pas l'attaquer il à utiliser car il a la botte qui le contre" << endl;
                this->choixCarte(tour, choix, i, deck, Joueurs);
            }
            if (checkAttaque == 1)
            {
                cout << "vous ne pouvez pas l'attaquer car il à déja cette attaque sur lui" << endl;
                this->choixCarte(tour, choix, i, deck, Joueurs);
            }
            else
                Joueurs->getJoueurs()[cible - 1]->setEssence(1);
            cout << "Le joueur " << cible << " ne peux plus avancer" << endl;
        }

        if (Attaque == "Accident") {

            cout << " Quelle joueur veux tu goumer ?" << endl;
            cin >> cible;
            while (cible <= 0 || cible >= i + 1) {
                cout << "Choisi un joueur valide " << endl;
                cin >> cible;
            }

            int checkBotte = Joueurs->getJoueurs()[cible - 1]->getAntiAcci();
            int checkAttaque = Joueurs->getJoueurs()[cible - 1]->getAccident();

            if (checkBotte == 1)
            {
                cout << "vous ne pouvez pas l'attaquer il à utiliser car il a la botte qui le contre" << endl;
                this->choixCarte(tour, choix, i, deck, Joueurs);
            }
            if (checkAttaque == 1)
            {
                cout << "vous ne pouvez pas l'attaquer car il à déja cette attaque sur lui" << endl;
                this->choixCarte(tour, choix, i, deck, Joueurs);
            }
            else
                Joueurs->getJoueurs()[cible - 1]->setAccident(1);
            cout << "Le joueur " << cible << " ne peux plus avancer" << endl;
        }

        if (Attaque == "Limitation 50") {

            cout << " Quelle joueur veux tu goumer ?" << endl;
            cin >> cible;
            while (cible <= 0 || cible >= i + 1) {
                cout << "Choisi un joueur valide " << endl;
                cin >> cible;
            }

            int checkBotte = Joueurs->getJoueurs()[cible - 1]->getAntiFeu();
            int checkAttaque = Joueurs->getJoueurs()[cible - 1]->getLimitation();

            if (checkBotte == 1)
            {
                cout << "vous ne pouvez pas l'attaquer il à utiliser car il a la botte qui le contre" << endl;
                this->choixCarte(tour, choix, i, deck, Joueurs);
            }
            if (checkAttaque == 1)
            {
                cout << "vous ne pouvez pas l'attaquer car il à déja cette attaque sur lui" << endl;
                this->choixCarte(tour, choix, i, deck, Joueurs);
            }
            else
                Joueurs->getJoueurs()[cible - 1]->setLimitation(1);
            cout << "Le joueur " << cible << " ne peux plus avancer" << endl;
        }
    }

    if (nomCarte == "Parade") {

        string Parade = Joueurs->getJoueurs()[tour - 1]->getMainJoueur()[choix - 1]->getParade();
        if (Parade == "Feu vert") {

            int peutParer = Joueurs->getJoueurs()[tour - 1]->getFeuRouge();
            if (peutParer == 1)
            {

                cout << " vous pouvez de nouveau avancer" << endl;
                Joueurs->getJoueurs()[tour - 1]->setFeuRouge(0);
            }
            else
            {
                cout << " vous n'avez pas de raison d'utiliser cette carte " << endl;
                this->choixCarte(tour, choix, i, deck, Joueurs);
            }

        }

        if (Parade == "Fin de limitation") {
            int peutParer = Joueurs->getJoueurs()[tour - 1]->getLimitation();
            if (peutParer == 1)
            {

                cout << " vous pouvez de nouveau avancer" << endl;
                Joueurs->getJoueurs()[tour - 1]->setLimitation(0);
            }
            else
            {
                cout << " vous n'avez pas de raison d'utiliser cette carte " << endl;
                this->choixCarte(tour, choix, i, deck, Joueurs);
            }

        }

        if (Parade == "Essence") {
            int peutParer = Joueurs->getJoueurs()[tour - 1]->getEssence();
            if (peutParer == 1)
            {

                cout << " vous pouvez de nouveau avancer" << endl;
                Joueurs->getJoueurs()[tour - 1]->setEssence(0);
            }
            else
            {
                cout << " vous n'avez pas de raison d'utiliser cette carte " << endl;
                this->choixCarte(tour, choix, i, deck, Joueurs);
            }

        }

        if (Parade == "Roue de secours") {
            int peutParer = Joueurs->getJoueurs()[tour - 1]->getCreve();
            if (peutParer == 1)
            {

                cout << " vous pouvez de nouveau avancer" << endl;
                Joueurs->getJoueurs()[tour - 1]->setCreve(0);
            }
            else
            {
                cout << " vous n'avez pas de raison d'utiliser cette carte " << endl;
                this->choixCarte(tour, choix, i, deck, Joueurs);
            }

        }

        if (Parade == "Reparation") {
            int peutParer = Joueurs->getJoueurs()[tour - 1]->getAccident();
            if (peutParer == 1)
            {

                cout << " vous pouvez de nouveau avancer" << endl;
                Joueurs->getJoueurs()[tour - 1]->setAccident(0);
            }
            else
            {
                cout << " vous n'avez pas de raison d'utiliser cette carte " << endl;
                this->choixCarte(tour, choix, i, deck, Joueurs);
            }

        }

    }

    int s = Joueurs->getJoueurs()[tour - 1]->getStade();
    cout << "Vous en etes maintenant a " << s << " bornes" << endl;
    if (s == 1000)
    {
        cout << "Bravo Vous avez gagne le joueur " << endl;

    }

}

void jeu::choixCarte(int tour, int choix, int i, Deck* deck, listeJoueurs* Joueurs) {
    int defausse;
    system("pause");
    cout << "Vous pouvez choisir une autre carte Jouable ou vous defaussez 2 pour la defausse 1 pour jouer une autre carte" << endl;
    cin >> defausse;
    while (defausse >= 3 || defausse <= 0) {
        cout << " faites un choix valide entre 1 ou 2 (1 pour jouer une carte 2 pour la defausse)" << endl;
        cin >> defausse;
    }
    if (defausse == 1) {
        cout << "Choississez une carte que vous pourrez jouez!" << endl;
        Joueurs->getJoueurs()[tour - 1]->afficherMain();
        cin >> choix;
        while (choix >= 8 || choix <= 0) {
            cout << " faites un choix valide entre 1 et 7" << endl;
            cin >> choix;
        }
        this->jouerCartes(tour, choix, i, deck, Joueurs);
    }
    else {
        Joueurs->getJoueurs()[tour - 1]->afficherMain();
        cout << "Quelle carte voulez vous defaussez ?" << endl;
        cin >> choix;
        Joueurs->getJoueurs()[tour - 1]->choisir(tour, choix, deck);
    }
}


void jeu::afficherMenu() {



    int choix;
    bool gameOn = true;
    while (gameOn != false) {


        cout << endl << " 1 - Commencer une nouvelle partie" << endl;
        cout << " 2 - Regles " << endl;
        cout << " 3 - A propos " << endl;
        cout << " 4 - Quittez ce magnifique jeu" << endl;
        cout << endl << "Que voulez-vous : ";

        cin >> choix;

        switch (choix)
        {
        case 1:
            cout << "La partie va bientot commencer " << endl;
            gameOn = false;
            system("pause");
            system("cls");
            break;
        case 2:
            cout << endl << "Le but du jeu, il faut arrive le plus rapidement posssible en evitant et en faisant des coups-fourrés a vous adversaire pour arriver a 1000 Bornes, pas plus pas moins !" << endl;
            cout << endl << "Le mille Bornes est un jeu qui se joue de 2 a 4 joueurs dans le sens des aiguilles d'une montre " << endl;
            cout << "Une carte vous est automatiquement distribué à chaque tour pour en avoir  toujours 7 dans votre main" << endl;
            cout << "Vous devez imperativement avoir une carte Feu vert pour démarer sinon, la défausse est la seule solution !" << endl;
            cout << endl << "Il existe type de cartes : " << endl;
            cout << endl << " - Les cartes Attaques permettent de stopper ou retarder un joueur dans sa course " << endl;
            cout << "   -- Limite de vitesse / Feu rouge / Crevaison / Panne dessence / Accident" << endl;
            cout << endl << " - Les cartes Bornes vous permettent d'avancer de 25 a 200 bornes " << endl;
            cout << "   -- 25 / 50 / 75 / 100 / 200 " << endl;
            cout << endl << " - Les carte Bottes  permettent de vous immunisé contre une attaque bien précise" << endl;
            cout << "   -- Increvable / Citerne d'essence / As du volant / Vehicule Prioriataire" << endl;
            cout << endl << " - Les cartes parades vont vous servir à contrer les attaques de vos adversaires" << endl;
            cout << "   -- Fin de limite de vitesse / Feu vert / Essence / Roue de secours / Reparation" << endl;
            cout << endl << "Que le meilleur gagne" << endl;
            break;
        case 3:
            cout << endl << "Fait par Mathys Vende, Romain Martineau et Pierre Vallade" << endl;

            break;
        case 4:
            cout << "Fin du jeu";
            exit(EXIT_FAILURE);
            break;
        default:
            cout << "Veuillez choisir une option valide";
            cout << "Recomencez";
            cin >> choix;
            break;
        }

    }

}
