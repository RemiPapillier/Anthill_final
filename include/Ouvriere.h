#ifndef OUVRIERE_H
#define OUVRIERE_H

#include "Fourmie.h"
#include "Guerriere.h"
#include "Carte.h"

class Ouvriere: public Fourmie
{
    public:
        Ouvriere();
        Ouvriere(int team, Fourmilliere* fourmilliereMaison,int posX, int posY, bool active);
        virtual ~Ouvriere();
        void observeEtDecide(Carte* C);
        Guerriere evoluer();
        void afficheStats();

    protected:
        int tempsAvantGuerriere;

    private:
};

#endif // OUVRIERE_H
