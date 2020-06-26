#include "Guerriere.h"
#include <iostream>

Guerriere::Guerriere()
{
    //ctor
}

Guerriere::Guerriere(int team, int baseNourritureMax, int baseNourritureActuel, int baseSanteMax, int baseSanteActuel, int baseResistance, int posX, int posY) {
  equipe = team;
  objectifActuel = 0;
  age = 0;
  nourritureMax = rand() % 6+baseNourritureMax; //random entre base +- 5
  nourritureActuel = baseNourritureActuel;
  santeMax = rand() % 6+baseSanteMax; //random entre base +- 5
  santeActuel = baseSanteActuel;
  resistance = rand() % 3+baseResistance; //random entre base +- 2
  vitesseDeplacement = 3;
  tempsMortVieilliesse = 20;
  force = 8;
  degatsAttaque = rand() % 3+3; //random entre 3 et 5

//  positionX = posX;
//  positionX = posY;
}

Guerriere::~Guerriere()
{
    //dtor
}

void Guerriere::observeEtDecide(Carte* C) {
    //A ajouter, decisions de combat.

    //0 = rien, 1=obstacle, 2=nourriture, 3=fourmieAllier, 4=fourmieEnnemie, 5=fourmili�reAllier, 6=fourmili�reEnnemis (ALLIER OU ENNEMIS PAS ENCORE DEFINIS)
    int elementHaut = C->vecteur2D[this->positionX-1][this->positionY]->type();
    int elementBas = C->vecteur2D[this->positionX+1][this->positionY]->type();
    int elementGauche = C->vecteur2D[this->positionX][this->positionY-1]->type();
    int elementDroite = C->vecteur2D[this->positionX][this->positionY+1]->type();
/*
    std::cout << " Haut : "<< elementHaut <<"\n ";
    std::cout << " Bas : "<< elementBas <<"\n ";
    std::cout << " Gauche : "<< elementGauche <<"\n ";
    std::cout << " Droite : "<< elementDroite <<"\n ";
    */
    std::cout << " Ancienne Position X : "<< this->positionX << " , Y : " << this->positionY <<"\n ";
    std::cout << " La guerriere observe et decide";
    //DECIDE SELON SON ETAT
    if(this->nourritureActuel < nourritureMax * 20 / 100)   //20% de la nourriture max
    {
        std::cout << " qu'elle a faim et doit manger. \n ";
        this->objectifActuel=3;
    } else if(this->nourriturePortee >= this->force) {
        std::cout << " qu'elle porte assez de nourriture. \n ";
        this->objectifActuel=2;
    } else {
        std::cout << " qu'elle doit chercher de la nourriture. \n ";
        this->objectifActuel=1;
    }

    //OBSERVATION
    if(objectifActuel==1)    //CHERCHE A MANGER
    {
        std::cout << "  Elle s'aventure donc et ";
        deplacementAleatoireEtRecolte(C ,elementHaut, elementBas, elementGauche, elementDroite);
    } else if(objectifActuel==3) //FAIM
    {
        if(nourriturePortee>0)
        {//Mange ce quelle porte
            std::cout << "  Elle mange ce qu'elle a sur son dos. \n ";
            mangerPortee();
        } else
        {//rentre a la fourmilliere
            std::cout << "  Elle retourne se nourrir chez elle ";
            retourFourmilliere(C ,elementHaut, elementBas, elementGauche, elementDroite);
        }

    } else if(objectifActuel==2) //RETOUR A LA FOURMILLIERE
    {
        std::cout << "  Elle se dirige vers chez elle ";
      retourFourmilliere(C ,elementHaut, elementBas, elementGauche, elementDroite);
    }
std::cout << "    Nouvelle Position X : "<< this->positionX << " , Y : " << this->positionY <<"\n ";
std::cout << " La guerriere a fini pour ce cycle.\n";
}


void Guerriere::afficheStats() {
  std::cout << "Stats Guerriere\n" ;
  std::cout << "Equipe : "<< equipe << "\n" ;
  std::cout << "Objectif Actuel : "<< objectifActuel << "\n" ;
  std::cout << "Age : "<< age << "\n" ;
  std::cout << "Nourriture Actuel/Max : "<< nourritureActuel << " / " << nourritureMax <<"\n" ;
  std::cout << "Sante Actuel/Max : "<< santeActuel << " / " << santeMax <<"\n" ;
  std::cout << "Resistance : "<< resistance << "\n" ;
  std::cout << "Degats attaque : "<< degatsAttaque << "\n" ;
}

