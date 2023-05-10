#include <iostream>
#include "types.hpp"
#include "board.hpp"
#include "view.hpp"
#include "mask.hpp"
#include "board.hpp"

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
  Piece piece = get_squareTab(p, x, y);
  switch (piece.type) {
  case rien:
    break;
  case roi:
    highlight_possible_moves_king(p,x,y,m);
    break;
  case reine:
    highlight_possible_moves_queen(p,x,y,m);
    break;
  case tour:
    highlight_possible_moves_rook(p,x,y,m);
    break;
  case fou:
      highlight_possible_moves_bishop(p,x,y,m);
    break;
  case cavalier:
    highlight_possible_moves_knight(p,x,y,m);
    break;
    /* case pion:
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
      if(piece_actu.couleur != piece.couleur) set_mask(m, x,i, bleu);
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
  Piece piece_actu;

<<<<<<< HEAD
  if(piece.couleur){

    piece_actu = get_squareTab(p, x, y-1);
    if (piece_actu.type == rien){
      set_mask(m, x, y-1, bleu);

      if(y == 6){
        piece_actu = get_squareTab(p, x, y-2);
        if (piece_actu.type == rien){
          set_mask(m, x, y-2, bleu);
        }
      }      
    }

    piece_actu = get_squareTab(p, x-1, y-1);
    if((piece_actu.type != rien) && (!piece_actu.couleur)){
      set_mask(m, x-1, y-1, bleu);
    }
    piece_actu = get_squareTab(p, x+1, y-1);
    if((piece_actu.type != rien) && (!piece_actu.couleur)){
      set_mask(m, x+1, y-1, bleu);
    }
  }
  else{
    piece_actu = get_squareTab(p, x, y+1);
    if (piece_actu.type == rien){
      set_mask(m, x, y+1, bleu);

      if(y == 1){
        piece_actu = get_squareTab(p, x, y+2);
        if (piece_actu.type == rien){
          set_mask(m, x, y+2, bleu);
        }
      }      
    }

    piece_actu = get_squareTab(p, x-1, y+1);
    if((piece_actu.type != rien) && (piece_actu.couleur)){
      set_mask(m, x-1, y+1, bleu);
    }

    piece_actu = get_squareTab(p, x+1, y+1);
    if((piece_actu.type != rien)&& (piece_actu.couleur)){
      set_mask(m, x+1, y+1, bleu);
    }
  }

}

void mask_choices_menu(Plateau p, bool couleur, Masque *m){
  cout << "Menu : " << endl;
  cout << "1 : Afficher les pièces déplaçables" << endl;
  cout << "2 : Afficher les pièces attaquables" << endl;
  cout << "3 : Afficher les pièces dangereuses à une pièce" << endl;
  int choix;
  cin >> choix;
  if (choix == 1){
    highlight_movable_pieces(p, couleur, m);
  }
  if (choix == 2){
    highlight_attacked_pieces(p, couleur, m);
  }
  if (choix == 3){
    cout << "Entrez les coordonnées de la pièce :" << endl;
    int x, y;
    cin << x << y;
    highlight_take_pieces(p, x, y m);
  }
  else {
    cout << "Le chiffre est invalide." << endl;
    mask_choices_menu(p, couleur, m);
  }

}

void mask_choices(Plateau p, bool couleur, Masque *m){
  char a;
  cout << "Voulez vous afficher des informations sur le jeu ? (O/N)";
  cin >> a;
  while(a == 'O'){
    mask_choices(p, couleur, m);
    cout << "Voulez vous afficher une autre information ? (O/N)";
    cin >> a;
=======
  for(int i = 1; x+i < taille && y+i < taille; i++){
    PieceActu = get_squareTab(p, x+i, y+i);
    if (PieceActu.type != rien){
      if (PieceActu.couleur != piece.couleur) set_mask(m, x+i, y+i, bleu);
      break;
    }
    set_mask(m, x+i, y+i, bleu);
  }
  for(int i = 1; x+i <taille && y-i >-1; i++){
    PieceActu = get_squareTab(p, x+i, y-i);
    if (PieceActu.type != rien){
      if (PieceActu.couleur != piece.couleur) set_mask(m, x+i, y-i, bleu);
      break;
    }
    set_mask(m, x+i, y-i, bleu);
  }
  for(int i = 1; y+i < taille && x-i > -1; i++){
    PieceActu = get_squareTab(p, x-i, y+i);
    if (PieceActu.type != rien){
      if (PieceActu.couleur != piece.couleur) set_mask(m, x-i, y+i, bleu);
      break;
    }
    set_mask(m, x-i, y+i, bleu);
  }
  for(int i = 1; y-i>-1 && x-i>-1; i++){
    PieceActu = get_squareTab(p, x-i, y-i);
    if (PieceActu.type != rien){
      if (PieceActu.couleur != piece.couleur) set_mask(m, x-i, y-i, bleu);
      break;
    }
    set_mask(m, x-i, y-i, bleu);
  }
}

void highlight_possible_moves_knight(Plateau p, int x, int y, Masque* m)
{
  set_mask(m, x, y, rouge);
  Piece piece = get_squareTab(p, x, y);
  Piece piece_actu;

  piece_actu = get_squareTab(p, x+2, y+1);
  if(piece_actu.type == rien) set_mask(m, x+2, y+1, bleu);
  else {
    if (piece_actu.couleur != piece.couleur) set_mask(m, x+2, y+1, bleu);
  }

  piece_actu = get_squareTab(p, x+1, y+2);
  if(piece_actu.type == rien) set_mask(m, x+1, y+2, bleu);
  else {
    if (piece_actu.couleur != piece.couleur) set_mask(m, x+1, y+2, bleu);
  }

  piece_actu = get_squareTab(p, x-2, y-1);
  if(piece_actu.type == rien) set_mask(m, x-2, y-1, bleu);
  else {
    if (piece_actu.couleur != piece.couleur) set_mask(m, x-2, y-1, bleu);
  }

  piece_actu = get_squareTab(p, x-1, y-2);
  if(piece_actu.type == rien) set_mask(m, x-1, y-2, bleu);
  else {
    if (piece_actu.couleur != piece.couleur) set_mask(m, x-1, y-2, bleu);
  }
  
  piece_actu = get_squareTab(p, x-2, y+1);
  if(piece_actu.type == rien) set_mask(m, x-2, y+1, bleu);
  else {
    if (piece_actu.couleur != piece.couleur) set_mask(m, x-2, y+1, bleu);
  }

  piece_actu = get_squareTab(p, x-1, y+2);
  if(piece_actu.type == rien) set_mask(m, x-1, y+2, bleu);
  else {
    if (piece_actu.couleur != piece.couleur) set_mask(m, x-1, y+2, bleu);
  }

  piece_actu = get_squareTab(p, x+2, y-1);
  if(piece_actu.type == rien) set_mask(m, x+2, y-1, bleu);
  else {
    if (piece_actu.couleur != piece.couleur) set_mask(m, x+2, y-1, bleu);
  }

  piece_actu = get_squareTab(p, x+1, y-2);
  if(piece_actu.type == rien) set_mask(m, x+1, y-2, bleu);
  else {
    if (piece_actu.couleur != piece.couleur) set_mask(m, x+1, y-2, bleu);
  }
}


void highlight_possible_moves_queen(Plateau p, int x, int y, Masque *m)
{
  Piece piece = get_squareTab(p, x,y);
  if(piece.type != reine) {
    cout << "ARza" << endl;
    exit(1);
  }
  highlight_possible_moves_bishop(p,x,y,m);
  highlight_possible_moves_rook(p,x,y,m);
}


bool isMovable(Masque m)
{
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      if(get_mask(m, j,i) == bleu) return true;
    }
  }
  return false;
}

void highlight_movable_pieces(Plateau p, bool col, Masque *m)
{
  Piece piece;
  Masque mtemp = empty_mask();
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      clear_mask(&mtemp);
      piece = get_squareTab(p, j,i);
      if(piece.couleur != col) continue;
      highlight_possible_moves(p, j, i, &mtemp);
      if(isMovable(mtemp)) set_mask(m, j, i, cyan);
    }
  }
}

void highlight_attacked_pieces(Plateau p, bool col, Masque *m)
{
  Masque mtemp = empty_mask();
  Piece piece;
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      piece = get_squareTab(p, j,i);
      if((piece.type    == rien)
      || (piece.couleur != col)) continue;
      highlight_possible_moves(p, j, i, &mtemp);
      print_board(p, mtemp);
    }
  }
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      piece = get_squareTab(p, j,i);
      if(piece.type    != rien
      && piece.couleur != col){
	if(get_mask(mtemp, j,i) == bleu)
	  set_mask(m, j,i, rouge);
	else set_mask(m, j,i, vert);
      }
    }
  }
}


void highlight_take_pieces(Plateau p, int x, int y, Masque* m)
{
  Piece piece_attaque = get_squareTab(p, x,y);
  Masque mtemp = empty_mask();
  Piece piece;
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      piece = get_squareTab(p, j,i);
      if((piece.type    == rien)
      || (piece.couleur == piece_attaque.couleur)) continue;
      highlight_possible_moves(p, j, i, &mtemp);
      if(get_mask(mtemp, x,y) == bleu)
	set_mask(m, j,i, gris);
      clear_mask(&mtemp);
    }
>>>>>>> AdrtH/SAE1/main
  }
}

