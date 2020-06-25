#include "Nourriture.h"

Nourriture::Nourriture()
{
    //ctor
}

Nourriture::~Nourriture()
{
    //dtor
}

Nourriture::Nourriture(int posX, int posY) {
  positionX = posX;
  positionX = posY;
}

int Nourriture::type(){
    return 2;
}
