#include "Fourmilliere.h"

Fourmilliere::Fourmilliere()
{
    //ctor
}

Fourmilliere::~Fourmilliere()
{
    //dtor
}

void Fourmilliere::checkFourmies(Carte* C)
{
    std::vector<int> fourmiesSortie;

    for(int i = 0; i < this.vecteurFourmie.size(); i++){
        //Verifier si une fourmie porte a manger et le recuperer
        if(this->vecteurFourmie.at(i).nourriturePortee > 0){
            this->reserveNourriture += this->vecteurFourmie.at(i).nourriturePortee;
            this->vecteurFourmie.at(i).nourriturePortee = 0;
        }
        //Verifier la faim d'une fourmie et la nourir
        while(this.vecteurFourmie.at(i).nourritureMax - this.vecteurFourmie.at(i).nourritureActuel > 0 && this.reserveNourriture > 0){
            this.vecteurFourmie.at(i).nourritureActuel += 1;
            this.reserveNourriture -= 1;
        }
        //Verifier si la fourmie peut sortir et la faire sortir
        if(this.vecteurFourmie.at(i).nourritureActuel == this.vecteurFourmie.at(i).nourritureMax) {
            int elementHaut = C->vecteur2D[this->positionX][this->positionY]->type();
            int elementBas = C->vecteur2D[this->positionX][this->positionY]->type();
            int elementGauche = C->vecteur2D[this->positionX][this->positionY]->type();
            int elementDroite = C->vecteur2D[this->positionX][this->positionY]->type();

            if(elementHaut==0 || elementBas==0 || elementGauche==0 || elementDroite==0 ) //Alentours vides
                {
                    if(elementHaut==0) {
                        C.vecteur2D.at(this.positionX-1).at(this.positionY) = this.vecteurFourmie.at(i);
                        this.vecteurFourmie.erase(i);
                        fourmiesSortie.push_back(i);    //Enregistre les fourmies sorties pour pas chambouler le FOR.
                    } else if(elementBas==0) {
                        C.vecteur2D.at(this.positionX+1).at(this.positionY) = this.vecteurFourmie.at(i);
                        this.vecteurFourmie.erase(i);   //RISQUE DE CHAMBOULER LE FOR !
                        fourmiesSortie.push_back(i);    //Enregistre les fourmies sorties pour pas chambouler le FOR.
                    } else if(elementGauche==0) {
                        C.vecteur2D.at(this.positionX).at(this.positionY-1) = this.vecteurFourmie.at(i);
                        this.vecteurFourmie.erase(i);   //RISQUE DE CHAMBOULER LE FOR !
                        fourmiesSortie.push_back(i);    //Enregistre les fourmies sorties pour pas chambouler le FOR.
                    } else if(elementDroite==0) {
                        C.vecteur2D.at(this.positionX-1).at(this.positionY+1) = this.vecteurFourmie.at(i);
                        this.vecteurFourmie.erase(i);   //RISQUE DE CHAMBOULER LE FOR !
                        fourmiesSortie.push_back(i);    //Enregistre les fourmies sorties pour pas chambouler le FOR.
                    }
                }
        }
    }

    if(!fourmiesSortie.empty()) //Verifie si des fourmies sont sorties durant la boucle FOR et les retires du vecteur
    {
        for(int i = 0; i < fourmiesSortie.size(); i++){
            this.vecteurFourmie.erase(fourmiesSortie.at(i));
        }
    }

}

int Fourmilliere::type(){
    return 5;
}
