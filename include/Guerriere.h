#ifndef GUERRIERE_H
#define GUERRIERE_H

#include "Fourmie.h"

class Guerriere : public Fourmie
{
    public:
        Guerriere();
        Guerriere(int team, int baseNourritureMax, int baseNourritureActuel, int baseSanteMax, int baseSanteActuel, int baseResistance, int posX, int posY);
        virtual ~Guerriere();
        void observeEtDecide(Carte* C);
        //void recupererNourriture(Ressource target);
        //void lacherNourriture(int posX, int posY);
        //void lacherPheromone(int type);
        //void attaque(Fourmie target);
        void afficheStats();

    protected:
        int tempsMortVieilliesse;
        int force;
        int nourritePortee;
        int degatsAttaque;

    private:
};

#endif // GUERRIERE_H
