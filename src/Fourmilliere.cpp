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
        this->vecteurFourmie.push_back(new Ouvriere(equipe, this, posX, posY, true));
    }
}

Fourmilliere::~Fourmilliere()
{
    //dtor
}

void Fourmilliere::checkFourmies(Carte* C)
{
    std::cout << "=== Pendant ce temps dans la Fourmilliere === \n ";
    std::cout << "  Reserve de nourriture : "<< this->reserveNourriture<<"\n ";
    std::vector<int> fourmiesSortie;

    bool hautOK = true; //Evite que deux fourmis sortent du m�me cot�s.
    bool basOK = true;
    bool gaucheOK = true;
    bool droiteOK = true;
    if(this->vecteurFourmie.empty()){
        std::cout << "  Il n'y a aucune fourmis a l'interieur. \n ";
    } else {
        std::cout << this->vecteurFourmie.size() << " : fourmis dans la fourmilliere. \n";
        for(int i = 0; i < this->vecteurFourmie.size(); i++){
                std::cout << " - Fourmie : " << i <<" -\n ";
            if(this->vecteurFourmie.at(i)->active == false) {
                std::cout << "   Viens tout juste de rentrer.\n ";
                this->vecteurFourmie.at(i)->active = true;
            } else {
            //Verifier si une fourmie porte a manger et le recuperer
            if(this->vecteurFourmie.at(i)->nourriturePortee > 0){
                std::cout << "   Nourriture recupere : " << this->vecteurFourmie.at(i)->nourriturePortee <<"\n ";
                this->reserveNourriture += this->vecteurFourmie.at(i)->nourriturePortee;
                this->vecteurFourmie.at(i)->nourriturePortee = 0;
                std::cout << "  Reserve de nourriture passe a : "<< this->reserveNourriture<<"\n ";
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
                            std::cout << "vers le Nord. \n";
                            this->vecteurFourmie.at(i)->positionX = this->positionX-1;
                            C->vecteur2D.at(this->positionX-1).at(this->positionY) = this->vecteurFourmie.at(i);
                            //this.vecteurFourmie.erase(i);
                            fourmiesSortie.push_back(i);    //Enregistre les fourmies sorties pour pas chambouler le FOR.
                            this->vecteurFourmie.at(i)->active = false;
                            hautOK = false;
                        } else if(elementBas==0 && basOK == true) {
                            std::cout << "vers le Sud. \n";
                            this->vecteurFourmie.at(i)->positionX = this->positionX+1;
                            C->vecteur2D.at(this->positionX+1).at(this->positionY) = this->vecteurFourmie.at(i);
                            //this.vecteurFourmie.erase(i);
                            fourmiesSortie.push_back(i);    //Enregistre les fourmies sorties pour pas chambouler le FOR.
                            this->vecteurFourmie.at(i)->active = false;
                            basOK = false;
                        } else if(elementGauche==0 && gaucheOK == true) {
                            std::cout << "vers l'Ouest. \n";
                            this->vecteurFourmie.at(i)->positionY = this->positionY-1;
                            this->vecteurFourmie.at(i)->active = false;
                            C->vecteur2D.at(this->positionX).at(this->positionY-1) = this->vecteurFourmie.at(i);
                           //this.vecteurFourmie.erase(i);
                            fourmiesSortie.push_back(i);    //Enregistre les fourmies sorties pour pas chambouler le FOR.
                            this->vecteurFourmie.at(i)->active = false;
                            gaucheOK = false;
                        } else if(elementDroite==0 && droiteOK == true) {
                            std::cout << "vers le l'Est. \n";
                            this->vecteurFourmie.at(i)->positionY = this->positionY+1;
                            C->vecteur2D.at(this->positionX).at(this->positionY+1) = this->vecteurFourmie.at(i);
                           //this.vecteurFourmie.erase(i);
                            fourmiesSortie.push_back(i);    //Enregistre les fourmies sorties pour pas chambouler le FOR.
                            this->vecteurFourmie.at(i)->active = false;
                            droiteOK = false;
                        }
                    }
                }
            }

        }

        if(!fourmiesSortie.empty()) //Verifie si des fourmies sont sorties durant la boucle FOR et les retires du vecteur
        {
            for(int i = 0; i < fourmiesSortie.size(); i++){
                this->vecteurFourmie.erase(vecteurFourmie.begin()+fourmiesSortie.at(i)-1-i); //Efface la fourmie du vecteur de la fourmilliere. Le -i sert � suivre l'evolution du vecteur qui retrecis a chaque suppression.
            }
        }
    }


std::cout << "=== FIN - Retour a l'exterieur === \n ";
}

int Fourmilliere::type(){
    return 5;
}
