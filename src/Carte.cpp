#include "Carte.h"

Carte::Carte()
{
    //ctor
}

Carte::~Carte()
{
    //dtor
}

Carte::Carte(int col, int line, int obs, int f, float phe){
    for (int i=0; i<line; i++){
        std::vector<Box*>temp;
        for (int j=0; j<col; j++){
            temp.push_back(new Box(j,i));
        }
        vecteur2D.push_back(temp);
    }
    dimensionC = col;
    dimensionL = line;
    obstacles = obs;
    food = f;
    pheromone = phe;
}

void Carte::initialisation(){
    srand ( time(NULL) );

    vecteur2D.at(dimensionL/2).at(dimensionC/2) = new Fourmilliere();

    int compteur=0;
    while(compteur<obstacles){
        int x = rand() % dimensionC;
        int y = rand() % dimensionL;
        if(vecteur2D.at(y).at(x)->type() == 0){
            vecteur2D.at(y).at(x) = new Obstacle();
            compteur++;
        }
    }
    compteur = 0;
    while(compteur<food){
        int x = rand() % dimensionC;
        int y = rand() % dimensionL;
        if(vecteur2D.at(y).at(x)->type() == 0){
            vecteur2D.at(y).at(x) = new Nourriture();
            compteur++;
        }
    }
    for(int i=0; i<vecteur2D.size();i++){
        for(int j=0; j<vecteur2D[i].size(); j++){
            int o_type = vecteur2D[i][j]->type();  //0 = rien, 1=obstacle, 2=nourriture, 3=fourmieAllier, 4=fourmieEnnemie, 5=fourmiliereAllier, 6=fourmiliereEnnemis (ALLIER OU ENNEMIS PAS ENCORE DEFINIS)
            switch(o_type)
            {
                case 0://rien
                    {
                     std::cout << " ";
                     break;
                    }

                case 1://Obstacle
                    {
                    std::cout << "O";
                    break;
                    }

                case 2://Nourriture
                    {
                    std::cout << "N";
                    break;
                    }

                case 3://Fourmie
                    {
                    std::cout << "F";
                    break;
                    }

                case 5://Fourmilliere
                    {
                    std::cout << "@";
                    break;
                    }
            }
        }
        std::cout << std::endl;
    }
}

void Carte::update(){

}
