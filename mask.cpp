#include <iostream>
#include "types.hpp"
#include "board.hpp"
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
  if(x>-1 && x<taille && y>-1 && y<taille)m->masque[y][x] = val;
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

void highlight_possible_moves(Plateau p, int x, int y, Masque *m)
{
  clear_mask(m);
  Piece piece = get_squareTab(p, x, y);
  cout << piece.type << endl;
  switch (piece.type) {
  case roi:
    highlight_possible_moves_king(p,x,y,m);
    break;
    /* case reine:
    higlight_possible_moves_queen();
    break; */
  case tour:
    highlight_possible_moves_rook(p,x,y,m);
    break;
    /* case fou:
    higlight_possible_moves_bishop();
    break;
  case cavalier:
    highlight_possible_moves_knight();
    break;
  case pion:
    highlight_possible_moves_pawn();
    break; */
  default:
    break;
  }
  return;
}

void highlight_possible_moves_king(Plateau p, int x, int y, Masque *m)
{
  Piece piece = get_squareTab(p, x, y);
  for(int i=y-1; i<y+2; ++i){
    for(int j=x-1; j<x+2;++j){
      Piece piece_actu = get_squareTab(p,j,i);
      if(i==y && j==x) set_mask(m, j,i, rouge);
      else if(piece_actu.couleur != piece.couleur || piece_actu.type == rien)
	set_mask(m, j,i, bleu);
    }
  }
}

void highlight_possible_moves_rook(Plateau p, int x, int y, Masque *m)
{
  set_mask(m,x,y, rouge);
  Piece piece = get_squareTab(p,x,y);
  Piece piece_actu;
  for(int i=x+1; i<taille; ++i){
    piece_actu = get_squareTab(p, i, y);
    if(piece_actu.type != rien){
      if(piece_actu.couleur != piece.couleur) set_mask(m, i,y, bleu);
      break;
    }
    set_mask(m, i,y, bleu);
  }
  for(int i=x-1; i>-1; --i){
    piece_actu = get_squareTab(p, i, y);
    if(piece_actu.type != rien){
      if(piece_actu.couleur != piece.couleur) set_mask(m, i,y, bleu);
      break;
    }
    set_mask(m, i,y, bleu);      
  }
  for(int i=y+1; i<taille; ++i){
    piece_actu = get_squareTab(p, x, i);
    if(piece_actu.type != rien){
      if(piece_actu.couleur != piece.couleur) set_mask(m, i,x, bleu);
      break;
    }
    set_mask(m, x,i, bleu);      
  }
  for(int i=y-1; i>-1; --i){
    piece_actu = get_squareTab(p, x, i);
    if(piece_actu.type != rien){
      if(piece_actu.couleur != piece.couleur) set_mask(m, x,i, bleu);
      break;
    }
    set_mask(m, x,i, bleu);      
  }
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

