#include <iostream>
#include "types.hpp"
#include "view.hpp"
#include "mask.hpp"

using namespace std;

Masque empty_mask()
{
  Masque ret;
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille;++j){
      ret.masque[i][j] = noCol;
    }
  }
  return ret;
}

void clear_mask(Masque *m)
{
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille;++j){
      m->masque[i][j] = noCol;
    }
  }
}


couleurMasque get_mask(Masque m, int x, int y)
{
  return m.masque[y][x];
}

void set_mask(Masque *m, int x, int y, couleurMasque val)
{
  m->masque[y][x] = val;
}

void print_board(Plateau plateau, Masque masque)
{
  cout << "  a b c d e f g h  " << endl;
  for(int i = taille-1; i > -1; i--){
    cout << i+1 << " ";
    for (int j = 0; j<taille;j++){
      print_square_color(plateau, j, i, 215, 94, masque);
    }
    cout << i+1 << endl;
  }
  cout << "  a b c d e f g h  " << endl;
}

void print_square_color(Plateau Plateau, int x, int y,
			int colorBG1, int colorBG2,  Masque m)
{
  couleurMasque couleurMasque = get_mask(m, x, y);
  if(couleurMasque != noCol) set_background(couleurMasque);
  else if((x+y)%2) set_background(colorBG1);
  else set_background(colorBG2);
  if(Plateau[y][x].type != rien)
    if(Plateau[y][x].couleur) set_foreground(0);
    else set_foreground(15);
  print_square(Plateau, x, y);
  cout << ' ';
  cout << "\x1b[0m";
}

void highlight_possible_moves(Plateau p, int x, int y, masque *m)
{
  get_squareTab(p, x, y);
}

void highlight_possible_moves_bishop(Plateau p, int x, int y, Masque *m){
  set_mask(m, x, y, rouge);
  Piece piece = get_squareTab(p, x, y);
  Piece PieceActu;

  for(int i = 0; i < taille; i++){
    PieceActu = get_squareTab(p, x+i, y+i);
    if (PieceActu.typePiece != rien){
      if (PieceActu.couleur != piece.couleur){
        set_mask(m, x+i, y+i, bleu);
      }
      break;
    }
    else{
      set_mask(m, x+i, y+i, bleu);
    }
  }

    for(int i = 0; i < taille; i++){
    PieceActu = get_squareTab(p, x+i, y-i);
    if (PieceActu.typePiece != rien){
      if (PieceActu.couleur != piece.couleur){
        set_mask(m, x+i, y-i, bleu);
      }
      break;
    }
    else{
      set_mask(m, x+i, y-i, bleu);
    }
  }

    for(int i = 0; i < taille; i++){
    PieceActu = get_squareTab(p, x-i, y+i);
    if (PieceActu.typePiece != rien){
      if (PieceActu.couleur != piece.couleur){
        set_mask(m, x-i, y+i, bleu);
      }
      break;
    }
    else{
      set_mask(m, x-i, y+i, bleu);
    }
  }

    for(int i = 0; i < taille; i++){
    PieceActu = get_squareTab(p, x-i, y-i);
    if (PieceActu.typePiece != rien){
      if (PieceActu.couleur != piece.couleur){
        set_mask(m, x-i, y-i, bleu);
      }
      break;
    }
    else{
      set_mask(m, x-i, y-i, bleu);
    }
  }
}

void highlight_possible_moves_queen(Plateau p, int x, int y, Masque *m){
  highlight_possible_moves_rook(p, x, y, m);
  highlight_possible_moves_bishop(p, x, y, m);
}

