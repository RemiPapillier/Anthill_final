#ifndef CARTE_H
#define CARTE_H

#include <iostream>
#include <vector>
#include <Box.h>
#include <typeinfo>
#include <stdlib.h>
#include <Obstacle.h>
#include <Nourriture.h>
#include <time.h>

class Carte
{
    public:
        Carte();
        Carte(int col, int line, int obs, int f, float phe);
        virtual ~Carte();
        void initialisation();
        void update();
        std::vector<std::vector<Box*>> vecteur2D;


    protected:
        int dimensionC;
        int dimensionL;
        int obstacles;
        int food;
        float pheromone;

    private:

};

#endif // CARTE_H
