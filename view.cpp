#include <iostream>
#include "types.hpp"
#include "view.hpp"


using namespace std;


void set_background(int color)
{
  cout << "\x1b[48;5;"+to_string(color)+"m";
}

void set_foreground(int color)
{
  cout << "\x1b[38;5;"+to_string(color)+"m";
}

void print_square_color(Plateau Plateau, int x, int y, int colorBG1, int colorBG2)
{
  if(Plateau[x][y].type != rien)
  if(Plateau[x][y].couleur) set_foreground(0);
  else set_foreground(7);
  if ((x+y)%2) set_background(colorBG1);
  else set_background(colorBG2);
  print_square(Plateau, x, y);
  cout << ' ';
  cout << "\x1b[0m";
}

void print_square(Plateau Plateau, int x, int y){
  if (Plateau[x][y].type == pion){
    cout << "♟︎";
  }
  if (Plateau[x][y].type == fou){
    cout << "♝";
  }
  if (Plateau[x][y].type == cavalier){
    cout << "♞";
  }
  if (Plateau[x][y].type == tour){
    cout << "♜";
  }
  if (Plateau[x][y].type == reine){
    cout << "♛";
  }
  if (Plateau[x][y].type == roi){
    cout << "♚";
  }
  if (Plateau[x][y].type == rien){
    cout << ' ';
  }
}

void print_board(Plateau plateau){
    cout << "  a b c d e f g h  " << endl;
    for(int i = taille-1; i > -1; i--){
        cout << i+1 << " ";
        for (int j = 0; j<taille;j++){
	  print_square_color(plateau, i, j, 215, 94);
        }
        cout << i+1 << endl;
    }
    cout << "  a b c d e f g h  " << endl;
}
