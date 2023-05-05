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


  for(int i=0; i<taille; ++i){
    set_mask(&masque, 1,i, rouge);
    set_mask(&masque, 2,i, vert);
    set_mask(&masque, 3,i, orange);
    set_mask(&masque, 4,i, bleu);
    set_mask(&masque, 5,i, violet);
    set_mask(&masque, 6,i, cyan);
    set_mask(&masque, 7,i, gris);
  }

  print_board(jeuTab.plateau, masque);
  
  move_pieceTab(jeuTab.plateau, 4, 1, 4, 3); // simuler pion e4
  highlight_possible_moves(jeuTab.plateau, 4,0, &masque);
  print_board(jeuTab.plateau, masque);


  emptyTableau(jeuTab.plateau);
  set_squareTab(jeuTab.plateau, 4, 4, Piece{tour, blanc});
  highlight_possible_moves(jeuTab.plateau, 4, 4, &masque);

  print_board(jeuTab.plateau, masque);
  
  
  
  /* printChaine(jeuChaine.plateau);
  printTab(jeuTab.plateau); *\
  return 0;
};
