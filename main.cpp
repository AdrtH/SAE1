#include <iostream>
#include "type.hpp"
#include "board.hpp"

int main(void)
{
  cout << rien << endl;
  gameTab jeuTab;
  startTab(jeuTab.plateau);
  gameChaine jeuChaine;
  jeuChaine.plateau = startChaine();

  move_pieceChaine(&jeuChaine.plateau, 4, 1, 4, 3); // simuler pion e4
  move_pieceTab(jeuTab.plateau, 4, 1, 4, 3);
  
  printChaine(jeuChaine.plateau);
  printTab(jeuTab.plateau);
  return 0;
};
