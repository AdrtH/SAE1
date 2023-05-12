#include <iostream>
#include <random>
#include "types.hpp"
#include "board.hpp"
#include "view.hpp"
#include "mask.hpp"
#include "board.hpp"
#include "game.hpp"
#include "historique.hpp"
using namespace std;

void MAJ_historique(Pile *p, Coup c){
    empiler(p,c);
}

void backtrack_historique(gameTab *g){
    Coup c;
    int a;
    cout << "Entrer '0' pour voir le coup précédent " << endl;
    cin >> a;
    while ((a == 0) && (g->historique.sommet > 1)){
        c = depiler(&(g->historique));
        move_pieceTab(g, c.xArrive, c.yArrive, c.xDepart, c.yDepart);
        print_board(g->plateau);
        cout << "Entrer '0' pour voir le coup précédent " << endl;
        cin >> a;
    } 
    c = depiler(&(g->historique));
    move_pieceTab(g, c.xArrive, c.yArrive, c.xDepart, c.yDepart);
    print_board(g->plateau);
}