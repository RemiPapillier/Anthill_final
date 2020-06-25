#include "Obstacle.h"

Obstacle::Obstacle()
{
    //ctor
}

Obstacle::~Obstacle()
{
    //dtor
}

Obstacle::Obstacle(int posX, int posY) {
  positionX = posX;
  positionX = posY;
}

int Obstacle::type(){
    return 1;
}
