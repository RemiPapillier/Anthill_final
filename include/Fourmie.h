#ifndef FOURMIE_H
#define FOURMIE_H

#include "Box.h"
#include "Carte.h"
#include "Fourmilliere.h"

class Fourmilliere;

class Carte;

class Fourmie: public Box
{
    public:
        Fourmie();
        virtual ~Fourmie();
        void deplacement(Carte* C, int X, int Y);
        void deplacementAleatoireEtRecolte(Carte* C, int elementHaut, int elementBas, int elementGauche, int elementDroite);
        void retourFourmilliere(Carte* C, int elementHaut, int elementBas, int elementGauche, int elementDroite);
        void mangerPortee();
        virtual void encaisseAttaque(int dmgRecut);
        void recolter(Carte* C, int X, int Y);
        virtual void mourir();
        void entrerFourmilliere(Carte* C, int X, int Y);
        int type();

 //   protected:
        int equipe;
        Fourmilliere* fourmilliereMaison;
        int objectifActuel;   //0=Attente, 1=Cherche Nourriture, 2=Retour � la fourmili�re, 3=Faim, 4=Combat
        int age;
        int nourritureMax;
        int nourritureActuel;
        int santeMax;
        int santeActuel;
        int resistance;
        int vitesseDeplacement;
        int force;
        int nourriturePortee;

    private:
};

#endif // FOURMIE_H
