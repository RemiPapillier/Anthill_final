#include <iostream>
#include <windows.h>
#include <climits>
#include <stdio.h>
#include <Carte.h>

using namespace std;

int get_columns_prompt(){
  _CONSOLE_SCREEN_BUFFER_INFO csbi;
  int columns;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  columns= csbi.srWindow.Right - csbi.srWindow.Left +1 -2; //-2 a cause des | sur les cotes
  return columns-1;
}

int get_rows_prompt(){
  _CONSOLE_SCREEN_BUFFER_INFO csbi;
  int rows;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  rows= csbi.srWindow.Bottom - csbi.srWindow.Top +1;
  return rows;
}

char user_input_custom(char answer){
  cout << "Would you like to configure a custom environment (Y/N)? ";
  cin >> answer;
  while(!((answer == 'y') || (answer == 'Y') || (answer == 'n') || (answer == 'N'))){
    cout << "Please, you must enter Y or N: ";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    cin >> answer;
  }
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  cout << endl;
  return answer;
}

int user_input_col(int map_columns, int columns){
  cout << "=> How many columns contain your map (min: 1 / max: " << columns << ")? ";
  cin >> map_columns;
  while(!cin.good() || map_columns > columns || map_columns < 1){
    if(!cin.good()){
      cout << "Please, enter an integer: ";
    }
    else if(map_columns > columns){
      cout << "For a good visualization, enter a number lower than " << columns << ": ";
    }
    else if(map_columns < 1){
      cout << "Please, enter at least 1 column: ";
    }
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    cin >> map_columns;
  }
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  cout << endl;
  return map_columns;
}

int user_input_rows(int map_rows, int rows){
  cout << "=> How many rows contain your map (min: 1 / max: " << rows << ")? ";
  cin >> map_rows;
  while(!cin.good() || map_rows > rows || map_rows < 1){
    if(!cin.good()){
      cout << "Please, enter an integer: ";
    }
    else if(map_rows > rows){
      cout << "For a good visualization, enter a number lower than " << rows << ": ";
    }
    else if(map_rows < 1){
      cout << "Please, enter at least 1 row: ";
    }
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    cin >> map_rows;
  }
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  cout << endl;
  return map_rows;
}

int user_input_obstacles(int obstacles, int map_columns, int map_rows){
  cout << "=> How many obstacles contain your map (min: 0 / max: " << map_columns*map_rows << " / recommended: " << map_columns*map_rows/5 << ")? ";
  cin >> obstacles;
  while(!cin.good() || obstacles > map_rows*map_columns || obstacles < 0){
    if(!cin.good()){
      cout << "Please, enter an integer: ";
    }
    else if(obstacles > map_rows*map_columns){
      cout << "There are too many obstacles, enter a number lower than " << map_columns*map_rows << ": ";
    }
    else if(obstacles < 0){
      cout << "Please, you can't enter a negative number: ";
    }
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    cin >> obstacles;
  }
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  cout << endl;
  return obstacles;
}

int user_input_food(int food, int obstacles, int map_columns, int map_rows){
  cout << "=> How much food contain your map (min: 0 / max: " << map_columns*map_rows-obstacles << " / recommended: " << (map_columns*map_rows-obstacles)/6 << ")? ";
  cin >> food;
  while(!cin.good() || food > map_rows*map_columns-obstacles || food < 0){
    if(!cin.good()){
      cout << "Please, enter an integer: ";
    }
    else if(food > map_rows*map_columns-obstacles){
      cout << "There is too much food, enter a number lower than " << map_columns*map_rows-obstacles << ": ";
    }
    else if(food < 0){
      cout << "Please, you can't enter a negative number: ";
    }
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    cin >> food;
  }
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  cout << endl;
  return food;
}

float user_input_evap(float evaporation){
  cout << "=> What is the pheromone evaporation rate (min: 0 / max: 1)? ";
  cin >> evaporation;
  while(!cin.good() || evaporation > 1 || evaporation < 0){
    if(!cin.good()){
      cout << "Please, enter a float: ";
    }
    else if(evaporation > 1){
      cout << "Please, enter a number lower than 1: ";
    }
    else if(evaporation < 0){
      cout << "Please, you can't enter a negative number: ";
    }
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    cin >> evaporation;
  }
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  cout << endl;
  return evaporation;
}

int main() {

  int columns = get_columns_prompt();
  int rows = get_rows_prompt();

  char answer;
  int map_columns, map_rows, obstacles, food;
  float evaporation;

  cout << "\n --- Welcome to the Anthill simulation ---\n\n";
  answer = user_input_custom(answer);

  if(answer == 'Y' || answer == 'y'){
    map_columns = user_input_col(map_columns, columns);
    map_rows = user_input_rows(map_rows, rows);
    obstacles = user_input_obstacles(obstacles, map_columns, map_rows);
    food = user_input_food(food, obstacles, map_columns, map_rows);
    evaporation = user_input_evap(evaporation);
  }
  else{
    map_columns = get_columns_prompt();
    map_rows = get_rows_prompt();
    obstacles = (map_columns * map_rows) / 5;
    food = (map_columns * map_rows) / 10;
    evaporation = 0.95;
  }

  Carte* m_carte = new Carte(map_columns, map_rows, obstacles, food, evaporation);
  m_carte->initialisation();

  int cycle = 0;

  char continuer;
    cout << "\n Press any key to continue or q to stop : ";
    cin >> continuer;
    cout << "\n";

  while(continuer != 'q' && continuer != 'Q') {
    m_carte->resetActions(); //Remet les fourmis en active ce qui leur permet d'agir une fois.
    m_carte->update();  //MAJ les cases de la carte et lance les routines des fourmis et des fourmillieres.
    cout << " --- Cycle : " << cycle << " --- \n";
    m_carte->affiche();
    cin.clear();
    cout << "\n Press any key to continue or q to stop : ";
    cin >> continuer;
    cout << "\n";
    cycle++;
  }
  cout << "\n --- FIN DU PROGRAMME ---\n\n";
  cin.clear();

  return 0;
}
