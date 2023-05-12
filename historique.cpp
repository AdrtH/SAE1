#include <iostream>
#include "types.hpp"
#include "board.hpp"
#include "historique.hpp"
#include "view.hpp"


using namespace std;

void MAJ_historique(Pile *p, Coup c)
{
  empiler(p, c);
}

void play_historique(Pile p)
{
  gameTab g = startGame(humain, humain);
  print_board(g.plateau);
  char buffer;
  for(int i=0; i<p.sommet; ++i){
    move_pieceTab(&g, p.coup[i].xDepart, p.coup[i].yDepart, p.coup[i].xArrive, p.coup[i].yArrive);
    print_board(g.plateau);
    cout << "Appuyez sur entrée pour passer au coup suivant" << endl;
    getchar();
  }
}
