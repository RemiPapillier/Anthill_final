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
    //AJOUTER LA DETECTION ET L'ATTAQUE D'ENNEMIS

    //0 = rien, 1=obstacle, 2=nourriture, 3=fourmieAllier, 4=fourmieEnnemie, 5=fourmili�reAllier, 6=fourmili�reEnnemis (ALLIER OU ENNEMIS PAS ENCORE DEFINIS)
    int elementHaut = C->vecteur2D[this->positionX][this->positionY]->type();
    int elementBas = C->vecteur2D[this->positionX][this->positionY]->type();
    int elementGauche = C->vecteur2D[this->positionX][this->positionY]->type();
    int elementDroite = C->vecteur2D[this->positionX][this->positionY]->type();

    //DECIDE SELON SON ETAT
    if(this->nourritureActuel < nourritureMax * 20 / 100)   //20% de la nourriture max
    {
        this->objectifActuel=3;
    } else if(this->nourritePortee >= this->force) {
        this->objectifActuel=2;
    } else {
        this->objectifActuel=1;
    }

    //OBSERVATION
    if(objectifActuel==1)    //CHERCHE A MANGER
    {
        deplacementAleatoireEtRecolte(C ,elementHaut, elementBas, elementGauche, elementDroite);
    } else if(objectifActuel==3) //FAIM
    {
        if(nourritePortee>0)
        {//Mange ce quelle porte
            mangerPortee();
        } else
        {//rentre a la fourmilliere
            retourFourmilliere(C ,elementHaut, elementBas, elementGauche, elementDroite);
        }

    } else if(objectifActuel==2) //RETOUR A LA FOURMILLIERE
    {
      retourFourmilliere(C ,elementHaut, elementBas, elementGauche, elementDroite);
    }


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

