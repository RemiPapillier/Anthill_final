#ifndef BOX_H
#define BOX_H

#include <iostream>

class Box
{
    public:
        Box();
        Box(int x,int y);
        virtual ~Box();
        virtual int type();
        int positionX;
        int positionY;

    protected:

    private:
};

#endif // BOX_H
