#ifndef NOURRITURE_H
#define NOURRITURE_H

#include "Box.h"

class Nourriture: public Box
{
    public:
        Nourriture();
        Nourriture(int posX, int posY);
        virtual ~Nourriture();
        int type();

/*    protected:
        int nutrition;
        int poid;
        int rarete;
*/
    private:
};

#endif // NOURRITURE_H
