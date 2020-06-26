#include "Ouvriere.h"

Ouvriere::Ouvriere()
{
    //ctor
}

Ouvriere::Ouvriere(int team, Fourmilliere* fourmilliereM, int posX, int posY, bool activite) : Fourmie() {
  equipe = team;
  objectifActuel = 0;   //0=Attente, 1=Cherche Nourriture, 2=Retour � la fourmili�re, 3=Faim, 4=Combat
  age = 0;
  nourritureMax = rand() % 6+10; //random entre 10 et 15
  nourritureActuel = nourritureMax;
  santeMax = rand() % 6+15; //random entre 15 et 20
  santeActuel = santeMax;
  resistance = rand() % 3+2; //random entre 2 et 4
  vitesseDeplacement = 2;

  tempsAvantGuerriere = 20;
  nourriturePortee = 0;
  force = 2;

  fourmilliereMaison=fourmilliereM;

  positionX = posX;
  positionY = posY;
  active = activite;
}

Ouvriere::~Ouvriere()
{
    //dtor
}

Guerriere Ouvriere::evoluer() {
  //call la cr�ation de la guerri�re et passer les stats en arguments
  return Guerriere(equipe, nourritureMax, nourritureActuel, santeMax, santeActuel, resistance, positionX, positionY);
}

void Ouvriere::observeEtDecide(Carte* C) {
    //0 = rien, 1=obstacle, 2=nourriture, 3=fourmieAllier, 4=fourmieEnnemie, 5=fourmili�reAllier, 6=fourmili�reEnnemis (ALLIER OU ENNEMIS PAS ENCORE DEFINIS)
    int elementHaut = C->vecteur2D[this->positionX-1][this->positionY]->type();
    int elementBas = C->vecteur2D[this->positionX+1][this->positionY]->type();
    int elementGauche = C->vecteur2D[this->positionX][this->positionY-1]->type();
    int elementDroite = C->vecteur2D[this->positionX][this->positionY+1]->type();

    std::cout << " Haut : "<< elementHaut <<"\n ";
    std::cout << " Bas : "<< elementBas <<"\n ";
    std::cout << " Gauche : "<< elementGauche <<"\n ";
    std::cout << " Droite : "<< elementDroite <<"\n ";
    std::cout << " Ancienne Position x : "<< this->positionX << " , Position Y : " << this->positionY <<"\n ";

    std::cout << " L'ouvriere observe et decide";
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
std::cout << "    Nouvelle Position x : "<< this->positionX << " , Position Y : " << this->positionY <<"\n ";
std::cout << " L'ouvriere a fini pour ce cycle.\n";
}

void Ouvriere::afficheStats() {
  std::cout << "Stats Ouvriere\n" ;
  std::cout << "Equipe : "<< equipe << "\n" ;
  std::cout << "Objectif Actuel : "<< objectifActuel << "\n" ;
  std::cout << "Age : "<< age << "\n" ;
  std::cout << "Nnourriture Actuel/Max : "<< nourritureActuel << " / " << nourritureMax <<"\n" ;
  std::cout << "Sante Actuel/Max : "<< santeActuel << " / " << santeMax <<"\n" ;
  std::cout << "Resistance : "<< resistance << "\n" ;
}
