#include "Box.h"

Box::Box()
{
    //ctor
}

Box::~Box()
{
    //dtor
}

Box::Box(int x, int y)
{
    positionX = x;
    positionY = y;
}

int Box::type(){
    return 0;
}
