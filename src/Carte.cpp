#include "Carte.h"
#include "Fourmie.h"

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

    vecteur2D.at(dimensionL/2).at(dimensionC/2) = new Fourmilliere(1, 10, 1, dimensionL/2, dimensionC/2);

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
    this->affiche();
}

void Carte::affiche(){
    for(int i=0; i<vecteur2D.size();i++){
        std::cout << "|";
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
        std::cout << "|";
        std::cout << std::endl;
    }
}

void Carte::resetActions(){

    for(int i=0; i<vecteur2D.size();i++){
        for(int j=0; j<vecteur2D[i].size(); j++){
            int o_type = vecteur2D[i][j]->type();  //0 = rien, 1=obstacle, 2=nourriture, 3=fourmieAllier, 4=fourmieEnnemie, 5=fourmiliereAllier, 6=fourmiliereEnnemis (ALLIER OU ENNEMIS PAS ENCORE DEFINIS)
            switch(o_type)
            {

                case 3: //Fourmie
                    {
                    Fourmie* fourmie =  dynamic_cast<Fourmie*>(this->vecteur2D[i][j]);
                    fourmie->active = true;
                    break;
                    }

            }
        }
    }
}

void Carte::update(){

    std::cout << "\nUPDATE CARTE... \n ";

    for(int i=0; i<vecteur2D.size();i++){
        for(int j=0; j<vecteur2D[i].size(); j++){
            int o_type = vecteur2D[i][j]->type();  //0 = rien, 1=obstacle, 2=nourriture, 3=fourmieAllier, 4=fourmieEnnemie, 5=fourmiliereAllier, 6=fourmiliereEnnemis (ALLIER OU ENNEMIS PAS ENCORE DEFINIS)
            //std::cout << "Check X : "<< i <<" ,Y : "<< j <<" case : "<< o_type <<"\n ";
            switch(o_type)
            {

                case 3: //Fourmie
                    {
                        Fourmie* fourmie =  dynamic_cast<Fourmie*>(this->vecteur2D[i][j]);
                        if(fourmie->active == true) //Evite les fourmis d'agir 2 fois dans le tour
                        {
                            std::cout << " UPDATE FOURMIE... \n ";
                            fourmie->observeEtDecide(this);
                            fourmie->active = false;
                            break;
                        }
                        break;
                    }

                case 5: //Fourmilliere
                    {
                        std::cout << " UPDATE FOURMILLIERE... \n ";
                        Fourmilliere* fourmilliere = dynamic_cast<Fourmilliere*>(this->vecteur2D[i][j]);
                        fourmilliere->checkFourmies(this);
                        break;
                    }
            }
        }
    }
}
