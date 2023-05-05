#include <iostream>
#include "types.hpp"
#include "board.hpp"
#include "view.hpp"
#include "mask.hpp"

using namespace std;

int main(void)
{
  gameTab jeuTab;
  startTab(jeuTab.plateau);
  print_board(jeuTab.plateau);

  Masque masque = empty_mask();
  
  move_pieceTab(jeuTab.plateau, 4, 1, 4, 3); // simuler pion e4
  highlight_possible_moves_pawn(jeuTab.plateau, 4, 3, &masque);
  
  /* printChaine(jeuChaine.plateau);
  printTab(jeuTab.plateau); */
  print_board(jeuTab.plateau, masque);
  return 0;
};
