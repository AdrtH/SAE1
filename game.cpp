#include <iostream>
#include "types.hpp"
#include "board.hpp"
#include "view.hpp"
#include "mask.hpp"
#include "board.hpp"

using namespace std;

bool test_run(Plateau p, Coup coup, bool couleur){
    Piece piece = get_squareTab(p, coup.xDepart, coup.yDepart);
    if ((piece.type == rien) || (piece.couleur != couleur)){
        return false;
    }
    Masque m = empty_mask();
    Masque m1 = empty_mask();
    highlight_movable_pieces(p, couleur, &m);
    if(get_mask(m, coup.xDepart,coup.yDepart) != cyan) 
        return false;
    highlight_possible_moves(p, coup.xDepart, coup.yDepart, &m);
    if(get_mask(m, coup.xArrive, coup.yArrive) != bleu)
        return false;
    return true;
}

Coup choose_mouvement_human(Plateau p, bool couleur){
    Coup c;
    char char1, char2;
    cout << "Coordonnées du point de départ";
    cin >> char1, c.yDepart;
    c.xDepart = int(char1) - 97;
    c.yDepart--;
    cout << "Coordonnées du point d'arrivée";
    cin >> char2, c.yArrive;
    c.yDepart = int(char2) - 97;
    c.yArrive--;
    if (test_run(p, c, couleur)){
        return c;
    }
    else{
        choose_mouvement_human(p, couleur);
    }
}