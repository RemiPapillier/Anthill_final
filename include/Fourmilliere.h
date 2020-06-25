#ifndef FOURMILLIERE_H
#define FOURMILLIERE_H

#include "Box.h"
#include <vector>

#include "Carte.h"
#include "Fourmie.h"

class Fourmie;

class Carte;

class Fourmilliere: public Box
{
    public:
        Fourmilliere();
        virtual ~Fourmilliere();
        int type();
        void checkFourmies(Carte* C);

//    protected:
        int equipe;
        int reserveNourriture;
        std::vector<Fourmie*> vecteurFourmie;

    private:
};

#endif // FOURMILLIERE_H
