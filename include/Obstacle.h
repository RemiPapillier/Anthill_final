#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Box.h"

class Obstacle: public Box
{
    public:
        Obstacle();
        Obstacle(int posX, int posY);
        virtual ~Obstacle();
        int type();

    protected:

    private:
};

#endif // OBSTACLE_H
