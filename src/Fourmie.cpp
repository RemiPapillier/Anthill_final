#include "Fourmie.h"

Fourmie::Fourmie()
{
    //ctor
}

Fourmie::~Fourmie()
{
    //dtor
}

int Fourmie::type(){
    return 3;
}

void Fourmie::observeEtDecide(Carte* C) {
//virtual
}

void Fourmie::encaisseAttaque(int dmgRecut) {
  if (dmgRecut-resistance > 0) {
    santeActuel = santeActuel - (dmgRecut - resistance);
    if (santeActuel <= 0){
      mourir();
    }
  }
}

void Fourmie::deplacement(Carte* C, int X, int Y) {
    int ancienFourmieX = this->positionX;
    int ancienFourmieY = this->positionY;

    Box* caseCible = C->vecteur2D.at(X).at(Y);
    caseCible->positionX = ancienFourmieX;
    caseCible->positionY = ancienFourmieY;

    //MAJ DE LA FOURMIE
    this->positionX = X;
    this->positionY = Y;

    //MAJ DE LA POSITION DANS LE VECTEUR2D (Echange entre l'objet dans la cible et la fourmie en position actuelle)
    C->vecteur2D.at(X).at(Y) = this;
    C->vecteur2D.at(ancienFourmieX).at(ancienFourmieY) = caseCible;
}

void Fourmie::mourir() {
  //a definir
  //Lacher les ressources sur place.
}

void Fourmie::mangerPortee() {
    while(this->nourritureMax - this->nourritureActuel > 0 && this->nourriturePortee > 0){
        this->nourritureActuel += 1; //Integrer les stats de poids et nutritions plus tard
        this->nourriturePortee -= 1;
    }
}

void Fourmie::recolter(Carte* C, int X, int Y){
//    Nourriture* cible = C->vecteur2D.at(X).at(Y); //utile quand la nouriture aura des stats.
    this->nourriturePortee += 1;
    C->vecteur2D.at(X).at(Y) = new Box(X,Y);
}

void Fourmie::deplacementAleatoireEtRecolte(Carte* C, int elementHaut, int elementBas, int elementGauche, int elementDroite){
    if(elementHaut==2 || elementBas==2 || elementGauche==2 || elementDroite==2 ) //NOURRITURE A PROXIMITE
    {
        if(elementHaut==2) {
            recolter(C, this->positionX-1, this->positionY);
        } else if(elementBas==2) {
            recolter(C, this->positionX+1, this->positionY);
        } else if(elementGauche==2) {
            recolter(C, this->positionX, this->positionY-1);
        } else if(elementDroite==2) {
            recolter(C, this->positionX, this->positionY+1);
        }
    } else {

            int randDirection = rand() % 4; //random entre 0 et 3 //DEPLACEMENT ALEATOIRE
            bool deplacementFait = false;

            while(!deplacementFait) {

                switch(randDirection)
                {
                    case 0:
                        //HAUT
                        if(elementHaut==0){
                            deplacement(C, this->positionX-1, this->positionY);
                            deplacementFait = true;
                            break;
                        }
                    case 1:
                        //BAS
                        if(elementBas==0){
                            deplacement(C, this->positionX+1, this->positionY);
                            deplacementFait = true;
                            break;
                        }
                    case 2:
                        //GAUCHE
                        if(elementGauche==0){
                            deplacement(C, this->positionX, this->positionY-1);
                            deplacementFait = true;
                            break;
                        }
                    case 3:
                        //DROITE
                        if(elementBas==0){
                            deplacement(C, this->positionX, this->positionY+1);
                            deplacementFait = true;
                            break;
                        }
                    randDirection = rand() % 4;
                }//end Switch
            } //end while
        } //end else
}

void Fourmie::retourFourmilliere(Carte* C, int elementHaut, int elementBas, int elementGauche, int elementDroite){
//TROUVER UN MOYEN D'EVITER QUE LA FOURMIE SE BLOQUE...Idealement impl�menter Dijkstra
 if(elementHaut==5 || elementBas==5 || elementGauche==5 || elementDroite==5 ) //FOURMILLIERE A PROXIMITE
    {
        if(elementHaut==5) {
            entrerFourmilliere(C, this->positionX-1, this->positionY);
        } else if(elementBas==5) {
            entrerFourmilliere(C, this->positionX+1, this->positionY);
        } else if(elementGauche==5) {
            entrerFourmilliere(C, this->positionX, this->positionY-1);
        } else if(elementDroite==5) {
            entrerFourmilliere(C, this->positionX, this->positionY+1);
        }
    } else {
    int randDirection = rand() % 4; //random entre 0 et 3 //DEPLACEMENT ALEATOIRE
    bool deplacementFait = false;

        while(!deplacementFait) {

            switch(randDirection)
            {
                case 0:
                    //HAUT
                    if( elementHaut==0 && ( abs(this->positionX -1 -this->fourmilliereMaison->positionX) < abs( this->positionX - this->fourmilliereMaison->positionX ) ) )
                    {
                        deplacement(C, this->positionX-1, this->positionY);
                        deplacementFait = true;
                        break;
                    }
                case 1:
                    //BAS
                    if(elementBas==0 && (abs(this->positionX+1 -this->fourmilliereMaison->positionX) < abs(this->positionX -this->fourmilliereMaison->positionX))){
                        deplacement(C, this->positionX+1, this->positionY);
                        deplacementFait = true;
                        break;
                    }
                case 2:
                    //GAUCHE
                    if(elementGauche==0 && (abs(this->positionY-1 -this->fourmilliereMaison->positionY) < abs(this->positionY-this->fourmilliereMaison->positionY))){
                        deplacement(C, this->positionX, this->positionY-1);
                        deplacementFait = true;
                        break;
                    }
                case 3:
                    //DROITE
                    if(elementBas==0 && (abs(this->positionY+1 -this->fourmilliereMaison->positionY) < abs(this->positionY -this->fourmilliereMaison->positionY))){
                        deplacement(C, this->positionX, this->positionY+1);
                        deplacementFait = true;
                        break;
                    }
                randDirection = rand() % 4;
            }//end Switch
        } //end while
    } //end else
}

void Fourmie::entrerFourmilliere(Carte* C, int X, int Y){
    //Ajout de la fourmie dans la fourmilliere
    Fourmilliere* fourmilliereCible = (Fourmilliere*)C->vecteur2D.at(X).at(Y);
    fourmilliereCible->vecteurFourmie.push_back(this);
    //MAJ la carte (Retirer la fourmie de là où elle étais)
    C->vecteur2D.at(this->positionX).at(this->positionY) = new Box(this->positionX,this->positionY);
    this->positionX = X;
    this->positionY = Y;
}
