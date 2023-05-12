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


  print_board(jeuTab.plateau, masque);
  
  move_pieceTab(jeuTab.plateau, 4, 1, 4, 3); // simuler pion e4
  clear_mask(&masque);
  highlight_possible_moves(jeuTab.plateau, 4,0, &masque);
  print_board(jeuTab.plateau, masque);


  emptyTableau(jeuTab.plateau);
  set_squareTab(jeuTab.plateau, 4, 4, Piece{tour, blanc});
  clear_mask(&masque);
  highlight_possible_moves(jeuTab.plateau, 4, 4, &masque);
  print_board(jeuTab.plateau, masque);

  set_squareTab(jeuTab.plateau, 6, 4, Piece{pion, noir});
  set_squareTab(jeuTab.plateau, 4, 1, Piece{pion, blanc});
  clear_mask(&masque);
  highlight_possible_moves(jeuTab.plateau, 4, 4, &masque);
  print_board(jeuTab.plateau, masque);

  emptyTableau(jeuTab.plateau);
  set_squareTab(jeuTab.plateau, 4, 4, Piece{fou, blanc});
  clear_mask(&masque);
  highlight_possible_moves(jeuTab.plateau, 4, 4, &masque);
  print_board(jeuTab.plateau, masque);

  set_squareTab(jeuTab.plateau, 6, 6, Piece{pion, noir});
  set_squareTab(jeuTab.plateau, 2, 2, Piece{pion, blanc});
  clear_mask(&masque);
  highlight_possible_moves(jeuTab.plateau, 4, 4, &masque);
  print_board(jeuTab.plateau, masque);


  
  emptyTableau(jeuTab.plateau);
  set_squareTab(jeuTab.plateau, 4, 4, Piece{cavalier, blanc});
  clear_mask(&masque);
  highlight_possible_moves(jeuTab.plateau, 4, 4, &masque);
  print_board(jeuTab.plateau, masque);

  set_squareTab(jeuTab.plateau, 5, 6, Piece{pion, noir});
  set_squareTab(jeuTab.plateau, 2, 3, Piece{pion, blanc});
  clear_mask(&masque);
  highlight_possible_moves(jeuTab.plateau, 4, 4, &masque);
  print_board(jeuTab.plateau, masque);


  
  emptyTableau(jeuTab.plateau);
  startTab(jeuTab.plateau);
  move_pieceTab(jeuTab.plateau, 4, 1, 4, 3); // simuler pion e4
  clear_mask(&masque);
  highlight_movable_pieces(jeuTab.plateau, blanc, &masque);
  print_board(jeuTab.plateau, masque);

  move_pieceTab(jeuTab.plateau, 3,0, 5,2); // simuler dame g4
  clear_mask(&masque);
  highlight_possible_moves(jeuTab.plateau, 5,2, &masque);
  // cout << "mouvement dame" << endl;
  print_board(jeuTab.plateau, masque);
  
  clear_mask(&masque);
  // print_board(jeuTab.plateau, masque);
  highlight_attacked_pieces(jeuTab.plateau, blanc, &masque);
  print_board(jeuTab.plateau, masque);


  clear_mask(&masque);
  highlight_take_pieces(jeuTab.plateau, 5,6, &masque);
  print_board(jeuTab.plateau, masque);
  /* printChaine(jeuChaine.plateau);
  printTab(jeuTab.plateau); */
  return 0;
};
