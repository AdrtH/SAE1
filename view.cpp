#include <iostream>
#include "types.hpp"
#include "view.hpp"

using namespace std;


void print_square(Plateau Plateau, int x, int y){
    if(Plateau[x][y].couleur){
        if (Plateau[x][y].type == pion){
            cout << "p";
        }
        if (Plateau[x][y].type == fou){
            cout << "b";
        }
        if (Plateau[x][y].type == cavalier){
            cout << "n";
        }
        if (Plateau[x][y].type == tour){
            cout << "r";
        }
        if (Plateau[x][y].type == reine){
            cout << "q";
        }
        if (Plateau[x][y].type == roi){
            cout << "k";
        }
    }
    else{
        if (Plateau[x][y].type == pion){
            cout << "P";
        }
        if (Plateau[x][y].type == fou){
            cout << "B";
        }
        if (Plateau[x][y].type == cavalier){
            cout << "N";
        }
        if (Plateau[x][y].type == tour){
            cout << "R";
        }
        if (Plateau[x][y].type == reine){
            cout << "Q";
        }
        if (Plateau[x][y].type == roi){
            cout << "K";
        }
        if (Plateau[x][y].type == rien){
            cout << "-";
        }
    }
}

void print_board(Plateau plateau){
    cout << "  a b c d e f g h  " << endl;
    for(int i = taille-1; i > -1; i--){
        cout << i+1 << " ";
        for (int j = 0; j<taille;j++){
            print_square(plateau, i, j);
            cout << " ";
        }
        cout << i+1 << endl;
    }
    cout << "  a b c d e f g h  " << endl;
}
