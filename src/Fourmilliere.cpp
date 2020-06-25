#include "Fourmilliere.h"
#include "Ouvriere.h"

Fourmilliere::Fourmilliere()
{
    //ctor
}

Fourmilliere::Fourmilliere(int equipe, int nourritureDeBase, int nombreDeFourmis, int posX, int posY)
{
    this->equipe = equipe;
    this->reserveNourriture = nourritureDeBase;
    this->positionX = posX;
    this->positionY = posY;
    for(int i = 0; i < nombreDeFourmis; i++){
        this->vecteurFourmie.push_back(new Ouvriere(equipe, this, posX, posY));
    }
}

Fourmilliere::~Fourmilliere()
{
    //dtor
}

void Fourmilliere::checkFourmies(Carte* C)
{
    std::cout << " Pendant ce temps dans la Fourmilliere... \n ";
    std::vector<int> fourmiesSortie;

    bool hautOK = true; //Evite que deux fourmis sortent du même cotés.
    bool basOK = true;
    bool gaucheOK = true;
    bool droiteOK = true;
    std::cout << this->vecteurFourmie.size() << " : fourmis dans la fourmilliere. \n";
    for(int i = 0; i < this->vecteurFourmie.size(); i++){
            std::cout << " - Fourmie : " << i <<" -\n ";
        //Verifier si une fourmie porte a manger et le recuperer
        if(this->vecteurFourmie.at(i)->nourriturePortee > 0){
            std::cout << "   Nourriture recupere : " << this->vecteurFourmie.at(i)->nourriturePortee <<"\n ";
            this->reserveNourriture += this->vecteurFourmie.at(i)->nourriturePortee;
            this->vecteurFourmie.at(i)->nourriturePortee = 0;
        }
        //Verifier la faim d'une fourmie et la nourir
        while(this->vecteurFourmie.at(i)->nourritureMax - this->vecteurFourmie.at(i)->nourritureActuel > 0 && this->reserveNourriture > 0){
            std::cout << "   Se nourris. \n ";
            this->vecteurFourmie.at(i)->nourritureActuel += 1;
            this->reserveNourriture -= 1;
        }
        //Verifier si la fourmie peut sortir et la faire sortir
        if(this->vecteurFourmie.at(i)->nourritureActuel == this->vecteurFourmie.at(i)->nourritureMax) {
            //0 = rien, 1=obstacle, 2=nourriture, 3=fourmieAllier, 4=fourmieEnnemie, 5=fourmiliereAllier, 6=fourmiliereEnnemis (ALLIER OU ENNEMIS PAS ENCORE DEFINIS)
            int elementHaut = C->vecteur2D[this->positionX-1][this->positionY]->type();
            int elementBas = C->vecteur2D[this->positionX+1][this->positionY]->type();
            int elementGauche = C->vecteur2D[this->positionX][this->positionY-1]->type();
            int elementDroite = C->vecteur2D[this->positionX][this->positionY+1]->type();

            if( (elementHaut==0 && hautOK )|| (elementBas==0 && basOK ) || (elementGauche==0 && gaucheOK) || (elementDroite==0 && droiteOK) ) //Alentours vides
                std::cout << "   Fourmie " << i <<" sort de la fourmilliere ";
                {
                    if(elementHaut==0 && hautOK == true) {
                        std::cout << "depuis le Haut. \n";
                        this->vecteurFourmie.at(i)->positionX = this->positionX-1;
                        C->vecteur2D.at(this->positionX-1).at(this->positionY) = this->vecteurFourmie.at(i);
                        //this.vecteurFourmie.erase(i);
                        fourmiesSortie.push_back(i);    //Enregistre les fourmies sorties pour pas chambouler le FOR.
                        hautOK = false;
                    } else if(elementBas==0 && basOK == true) {
                        std::cout << "depuis le Bas. \n";
                        this->vecteurFourmie.at(i)->positionX = this->positionX+1;
                        C->vecteur2D.at(this->positionX+1).at(this->positionY) = this->vecteurFourmie.at(i);
                        //this.vecteurFourmie.erase(i);
                        fourmiesSortie.push_back(i);    //Enregistre les fourmies sorties pour pas chambouler le FOR.
                        basOK = false;
                    } else if(elementGauche==0 && gaucheOK == true) {
                        std::cout << "depuis la Gauche. \n";
                        this->vecteurFourmie.at(i)->positionY = this->positionY-1;
                        C->vecteur2D.at(this->positionX).at(this->positionY-1) = this->vecteurFourmie.at(i);
                       //this.vecteurFourmie.erase(i);
                        fourmiesSortie.push_back(i);    //Enregistre les fourmies sorties pour pas chambouler le FOR.
                        gaucheOK = false;
                    } else if(elementDroite==0 && droiteOK == true) {
                        std::cout << "depuis la Droite. \n";
                        this->vecteurFourmie.at(i)->positionY = this->positionY+1;
                        C->vecteur2D.at(this->positionX).at(this->positionY+1) = this->vecteurFourmie.at(i);
                       //this.vecteurFourmie.erase(i);
                        fourmiesSortie.push_back(i);    //Enregistre les fourmies sorties pour pas chambouler le FOR.
                        droiteOK = false;
                    }
                }
        }
    }

    if(!fourmiesSortie.empty()) //Verifie si des fourmies sont sorties durant la boucle FOR et les retires du vecteur
    {
        for(int i = 0; i < fourmiesSortie.size(); i++){
            this->vecteurFourmie.erase(vecteurFourmie.begin()+fourmiesSortie.at(i)-1-i); //Efface la fourmie du vecteur de la fourmilliere. Le -i sert à suivre l'evolution du vecteur qui retrecis a chaque suppression.
        }
    }

std::cout << "-FIN- Retour a l'exterieur... \n ";
}

int Fourmilliere::type(){
    return 5;
}
