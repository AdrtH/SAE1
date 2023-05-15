#include <iostream>
#include "types.hpp"
#include "board.hpp"
#include "view.hpp"
#include "mask.hpp"
#include "board.hpp"
#include "historique.hpp"

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

bool simulate_Coup(Plateau p, int xDep, int yDep, int xArr, int yArr)
{
  gameTab gdup = startGame(humain, humain);
  copy_board(p, gdup.plateau);
  move_pieceTab(gdup.plateau, xDep, yDep, xArr, yArr);
  bool col = get_squareTab(p, xDep, yDep).couleur;
  return isCheck(&gdup, col);
}

void highlight_possible_moves(gameTab *g, int x, int y, Masque *m)
{
  Piece piece = get_squareTab(g->plateau, x, y);
  switch (piece.type) {
  case rien:
    break;
  case roi:
    highlight_possible_moves_king(g,x,y,m);
    break;
  case reine:
    highlight_possible_moves_queen(g->plateau,x,y,m);
    break;
  case tour:
    highlight_possible_moves_rook(g->plateau,x,y,m);
    break;
  case fou:
      highlight_possible_moves_bishop(g->plateau,x,y,m);
    break;
  case cavalier:
    highlight_possible_moves_knight(g->plateau,x,y,m);
    break;
  case pion:
    highlight_possible_moves_pawn(g->plateau,x,y,m);
    break;
  default:
    break;
  }
  for(int i=0; i<taille; ++i){ // situation de clouage et d'auto echecs
    for(int j=0; j<taille; ++j){
      if(get_mask(*m,j,i) == bleu)
	if(simulate_Coup(g->plateau, x,y,j,i))
	   set_mask(m, j,i, noCol);
    }
  }
  return;
}

void highlight_possible_moves_safe(gameTab* g, int x, int y, Masque *m) // même fonction qu'au dessus, mais qui est utilisée pour eviter une boucle d'appel (isCheck -> attacked pieces -> possibleMove -> isCheck)
{								       // tout en utilisant le même comportement que Lichess au niveau des clouages.                                                              
  Piece piece = get_squareTab(g->plateau, x, y);
  switch (piece.type) {
  case rien:
    break;
  case roi:
    highlight_possible_moves_king(g->plateau,x,y,m);
    break;
  case reine:
    highlight_possible_moves_queen(g->plateau,x,y,m);
    break;
  case tour:
    highlight_possible_moves_rook(g->plateau,x,y,m);
    break;
  case fou:
      highlight_possible_moves_bishop(g->plateau,x,y,m);
    break;
  case cavalier:
    highlight_possible_moves_knight(g->plateau,x,y,m);
    break;
  case pion:
    highlight_possible_moves_pawn(g->plateau,x,y,m);
    break;
  default:
    break;
  }
  return;
}

void highlight_possible_moves_pawn(Plateau p, int x, int y, Masque *m){
  set_mask(m, x, y, rouge);
  Piece piece = get_squareTab(p, x, y);
  Piece piece_actu;

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

void highlight_possible_moves_king(gameTab *g, int x, int y, Masque *m) // Inclus le roque
{
  Masque mtemp = empty_mask();
  Piece ptemp;
  for(int i=0;i<taille;++i){
    for(int j=0; j<taille; ++j){
      ptemp = get_squareTab(g->plateau, j,i);
      if(ptemp.type != rien && ptemp.couleur != g->col_joue) highlight_possible_moves_safe(g, j,i,&mtemp);
    }
  }
  cout << "test" << endl;
  print_board(g->plateau, mtemp);
  if(g->roqueDispo & (GRD_ROQUE_BLANC<<(g->col_joue))){ // on si le joueur peut encore grd_roque
    Piece p1 = get_squareTab(g->plateau, x-1,y);
    Piece p2 = get_squareTab(g->plateau, x-2,y);
    Piece p3 = get_squareTab(g->plateau, x-3,y);
    if(get_mask(mtemp, x-1, y) != bleu // on verifie que les cases de déplacements du roi ne soit pas attaquables
    && get_mask(mtemp, x-2,y) != bleu
    && p1.type == rien && p2.type == rien && p3.type == rien){ // on verifie que les cases soit libres
      set_mask(m, x-2, y, bleu);
    }
  }
  cout << (g->roqueDispo & (PTT_ROQUE_BLANC << (g->col_joue)))<< endl;
  if(g->roqueDispo & (PTT_ROQUE_BLANC<<(g->col_joue))){ // on si le joueur peut encore grd_roque
    Piece p1 = get_squareTab(g->plateau, x+1,y);
    Piece p2 = get_squareTab(g->plateau, x+2,y);
    cout << "teste" << endl;
    cout << (get_mask(mtemp, x+1, y) != bleu) << endl;
    cout << (get_mask(mtemp, x+2, y) != bleu) << endl;
    cout << (p1.type)<< endl;
    cout <<(p2.type) << endl;
    if(get_mask(mtemp, x+1, y) != bleu
    && get_mask(mtemp, x+2, y) != bleu// on verifie que les cases de déplacements du roi ne soit pas attaquables
    && p1.type == rien && p2.type == rien){ // on verifie que les cases soit libres
      cout << "gros roque" << endl;
      set_mask(m, x+2, y, bleu);
    }
  }
  highlight_possible_moves_king(g->plateau, x,y,m);
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
  Piece PieceActu;
  
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
    for(int i = 1; x+i < taille && y+i < taille; i++){
    PieceActu = get_squareTab(p, x+i, y+i);
    if (PieceActu.type != rien){
      if (PieceActu.couleur != piece.couleur) set_mask(m, x+i, y+i, bleu);
      break;
    }
    set_mask(m, x+i, y+i, bleu);
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
    return;
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

void highlight_movable_pieces(gameTab* g, bool col, Masque *m)
{
  // Pour résumer, on regarde chaque piece de color, on regarde son masque de mouvement, s'il est non vide, on la marque comme bougeable.
  Piece piece;
  Masque mtemp = empty_mask();
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      clear_mask(&mtemp);
      piece = get_squareTab(g->plateau, j,i);
      if(piece.couleur != col) continue;
      highlight_possible_moves(g, j, i, &mtemp);

      if(isMovable(mtemp)) set_mask(m, j, i, cyan);
    }
  }
}


void highlight_attacked_pieces(gameTab* g, bool col, Masque *m)
{
  // Pour résumer, on regarde les mouvements des pieces de la couleur opposé, on marque toutes les pieces se trouvant sur une case bleue sont attaquées.
  Masque mtemp = empty_mask();
  Piece piece;
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      piece = get_squareTab(g->plateau, j,i);
      if((piece.type    == rien)
      || (piece.couleur != col)) continue;
      highlight_possible_moves(g, j, i, &mtemp);
    }
  }
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      piece = get_squareTab(g->plateau, j,i);
      if(piece.type    != rien
      && piece.couleur != col){
	if(get_mask(mtemp, j,i) == bleu)
	  set_mask(m, j,i, rouge);
	else set_mask(m, j,i, vert);
      }
    }
  }
}

void highlight_attacked_pieces_safe(gameTab *g, bool col, Masque *m) // même fonction qu'au dessus, mais qui est utilisée pour eviter une boucle d'appel (isCheck -> attacked pieces -> possibleMove -> isCheck)
{				                                    // tout en utilisant le même comportement que Lichess au niveau des clouages.
  Masque mtemp = empty_mask();
  Piece piece;
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      piece = get_squareTab(g->plateau, j,i);
      if((piece.type    == rien)
      || (piece.couleur != col)) continue;
      highlight_possible_moves_safe(g, j, i, &mtemp);
    }
  }
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      piece = get_squareTab(g->plateau, j,i);
      if(piece.type    != rien
      && piece.couleur != col){
	if(get_mask(mtemp, j,i) == bleu)
	  set_mask(m, j,i, rouge);
	else set_mask(m, j,i, vert);
      }
    }
  }
}

  
void highlight_take_pieces(gameTab* g, int x, int y, Masque* m)
{
  Piece  piece_attaque = get_squareTab(g->plateau, x,y);
  Masque mtemp         = empty_mask();
  Piece  piece;
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      piece = get_squareTab(g->plateau, j,i);
      if((piece.type    == rien)
      || (piece.couleur == piece_attaque.couleur)) continue;
      highlight_possible_moves(g, j, i, &mtemp);
      if(get_mask(mtemp, x,y) == bleu)
	set_mask(m, j,i, gris);
      clear_mask(&mtemp);
    }
  }
}


void mask_choices_menu(gameTab* g, bool couleur, Masque *m){
  cout << "Menu : " << endl;
  cout << "1 : Afficher les pièces déplaçables" << endl;
  cout << "2 : Afficher les pièces attaquables" << endl;
  cout << "3 : Afficher les pièces dangereuses à une pièce" << endl;
  cout << "4 : Afficher les deplacements d'une pièce" << endl;
  int choix;
  char c1;
  int x,y;
  cin >> choix;
  switch (choix){
    case 1:
      highlight_movable_pieces(g, couleur, m);
      print_board(g->plateau, *m);
      clear_mask(m);
      break;
    case 2:
      highlight_attacked_pieces(g, couleur, m);
      print_board(g->plateau, *m);
      clear_mask(m);
      break;
    case 3:
      cout << "Entrez les coordonnées de la pièce : " << endl;
      cin >> c1 >> y;
      x = int(c1) - 97;
      y--;
      highlight_take_pieces(g, x, y, m);
      print_board(g->plateau, *m);
      clear_mask(m);
      break;
    case 4:
      cout << "Entrez les coordonnées de la pièce : " << endl;
      cin >> c1 >> y;
      x = int(c1) - 97;
      y--;
      highlight_possible_moves(g, x,y,m);
      print_board(g->plateau, *m);
      clear_mask(m);
      break;
    default:
      cout << "Le chiffre est invalide." << endl;
      mask_choices_menu(g, couleur, m);
      break;
  }
}

void mask_choices(gameTab* g, bool couleur){
  Masque m = empty_mask();

  char a;
  cout << "Voulez vous afficher des informations sur le jeu ? (O/N) ";
  cin >> a;
  while(a == 'O'){
    mask_choices_menu(g, couleur, &m);
    cout << "Voulez vous afficher une autre information ? (O/N) ";
    cin >> a;
  }
  cout << "Voulez vous annuler des coups ? (O/N) ";
  cin  >> a;
  if(a == 'O'){
    backtrack_historique(g);
  }
}

bool isCheck(gameTab *g, bool color) // techniquement la fonction "king in check", mais elle a été implémentée avant qu'elle soit demandée, d'où le nom différent.
{
  Masque m = empty_mask();
  highlight_attacked_pieces_safe(g, !color, &m);
  Piece p;
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      p = get_squareTab(g->plateau, j,i);
      if(p.type == roi && p.couleur == color){
	if(get_mask(m, j,i) == rouge) return true; // on cherche si le roi de color est attaqué
	else return false;
      }
    }
  }
  // unreachable, mais par précaution
  return false;
}

bool isPat(gameTab *g, bool col)
{
  Masque m = empty_mask();
  Piece p;
  for(int k=0; k<taille; ++k){
    for(int l=0; l<taille; ++l){
      p = get_squareTab(g->plateau, l,k);
      if(p.type == rien || p.couleur != col) continue;
      highlight_possible_moves(g, k,l, &m);
    }
  }
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      if(get_mask(m, j,i) == bleu) return false;
    }
  }
  return true; // le joueur color n'a pas de mouvement disponible
}

bool isCheckMate(gameTab* g, bool col)
{
  // une situation d'echec et mat et un pat couplé à un echec
  return isPat(g, col) && isCheck(g, col);
}

