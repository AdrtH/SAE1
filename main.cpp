#include <iostream>
#include "types.hpp"
#include "board.hpp"
#include "view.hpp"

using namespace std;

int main(void)
{
  gameTab jeuTab;
  startTab(jeuTab.plateau);
  print_board(jeuTab.plateau);
  gameChaine jeuChaine;
  jeuChaine.plateau = startChaine();

  move_pieceChaine(&jeuChaine.plateau, 4, 1, 4, 3); // simuler pion e4
  move_pieceTab(jeuTab.plateau, 4, 1, 4, 3);
  
  /* printChaine(jeuChaine.plateau);
  printTab(jeuTab.plateau); */
  print_board(jeuTab.plateau);
  return 0;
};
