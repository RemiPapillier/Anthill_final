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
            int o_type = vecteur2D[i][j]->type();
            if(o_type==0){
                std::cout << " ";
            }
            else if(o_type==1){
                std::cout << "O";
            }
            else if(o_type==2){
                std::cout << "N";
            }
            else if(o_type==3){
                std::cout << "F";
            }
            else if(o_type==4){
                std::cout << " ";
            }
            else if(o_type==5){
                std::cout << "-";
            }
        }
        std::cout << std::endl;
    }
}

void Carte::update(){

}
