#include "types.hpp"
#include "historique.hpp"
#include "mask.hpp"
#include <iostream>

using namespace std;

void emptyChaine(Liste* tete)
{
  if(tete->suiv)
    emptyChaine(tete->suiv);
  delete tete->suiv;
  tete->suiv = NULL;
}

void emptyTableau(Plateau plateau)
{
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      plateau[i][j] = Piece{rien, 0};
    }
  }
}

Piece get_squareChaine(Liste* tete, int x, int y)
{
  if(tete->x == x && tete->y == y)
    return tete->piece;
  if(tete->suiv)
    return get_squareChaine(tete->suiv, x, y);
  return Piece{rien, 0};
}

Piece get_squareTab(Plateau plateau, int x, int y)
{
  return plateau[y][x];
}

void set_squareChaine(Liste* tete, int x, int y, Piece piece)
{
  Liste* ptr = tete;
  while(ptr){
    if(ptr->x==x && ptr->y==y){
      ptr->piece = piece;
      return;
    }
    ptr = ptr->suiv;
  }
  ptr->suiv = new Liste;
  ptr->x = x;
  ptr->y = y;
  ptr->piece = piece;
  ptr->suiv = NULL;
}

void set_squareTab(Plateau plateau, int x, int y, Piece piece)
{
  plateau[y][x] = piece;
}

Liste* startChaine()
{
  Liste* ret = NULL;
  Liste* ptr = NULL;
  // initialiser les pions
  for(int i=0; i<taille;++i){
    if(!ptr){
      ptr = new Liste;
      ret = ptr;
    }
    else {
      ptr->suiv = new Liste;
      ptr = ptr->suiv;
    }
    ptr->x = i;
    ptr->y = 1;
    ptr->piece = Piece{pion, blanc};
    ptr->suiv = new Liste;
    ptr = ptr->suiv;
    ptr->x = i;
    ptr->y = 6;
    ptr->piece = Piece{pion, noir};
  }
  // initialiser les tours
  for(int i = 0; i<=7; i+=7){
    ptr->suiv = new Liste;
    ptr = ptr->suiv;
    ptr->x = i;
    ptr->y = 0;
    ptr->piece = Piece{tour, blanc};
    ptr->suiv = new Liste;
    ptr = ptr->suiv;
    ptr->x = i;
    ptr->y = 7;
    ptr->piece = Piece{tour, noir};
  }
  // initialiser les cavaliers
  for(int i = 1; i<=6; i+=5){
    ptr->suiv = new Liste;
    ptr = ptr->suiv;
    ptr->x = i;
    ptr->y = 0;
    ptr->piece = Piece{cavalier, blanc};
    ptr->suiv = new Liste;
    ptr = ptr->suiv;
    ptr->x = i;
    ptr->y = 7;
    ptr->piece = Piece{cavalier, noir};
  }
  // initialiser les fous
  for(int i = 2; i<=5; i+=3){
    ptr->suiv = new Liste;
    ptr = ptr->suiv;
    ptr->x = i;
    ptr->y = 0;
    ptr->piece = Piece{fou, blanc};
    ptr->suiv = new Liste;
    ptr = ptr->suiv;
    ptr->x = i;
    ptr->y = 7;
    ptr->piece = Piece{fou, noir};
 }
  // initialiser les reines
  ptr->suiv = new Liste;
  ptr = ptr->suiv;
  ptr->x = 3;
  ptr->y = 0;
  ptr->piece = Piece{reine, blanc};
  ptr->suiv = new Liste;
  ptr = ptr->suiv;
  ptr->x = 3;
  ptr->y = 7;
  ptr->piece = Piece{reine, noir};
  // initialiser les rois
  ptr->suiv = new Liste;
  ptr = ptr->suiv;
  ptr->x = 4;
  ptr->y = 0;
  ptr->piece = Piece{roi, blanc};
  ptr->suiv = new Liste;
  ptr = ptr->suiv;
  ptr->x = 4;
  ptr->y = 7;
  ptr->piece = Piece{roi, noir};
  ptr->suiv = NULL;
  return ret;
}

void startTab(Plateau plateau)
{
  for(int i = 0; i<taille; ++i){
    for(int j = 0; j<taille; ++j){
      plateau[i][j] = {rien,0};
    }
  }
  for(int i = 0; i<taille; ++i){
    plateau[1][i] = Piece{pion, blanc};
    plateau[6][i] = Piece{pion, noir};
  }
  for(int i = 0; i<=7; i+=7){
    plateau[0][i] = Piece{tour, blanc};
    plateau[7][i] = Piece{tour, noir};
  }
  for(int i = 1; i<=6; i+=5){
    plateau[0][i] = Piece{cavalier, blanc};
    plateau[7][i] = Piece{cavalier, noir};
  }
  for(int i = 2; i<=5; i+=3){
    plateau[0][i] = Piece{fou, blanc};
    plateau[7][i] = Piece{fou, noir};
  }
  plateau[0][3] = Piece{reine, blanc};
  plateau[7][3] = Piece{reine, noir};
  plateau[0][4] = Piece{roi,   blanc};
  plateau[7][4] = Piece{roi,   noir};
}


void emptyPile(Pile *p)
{
  p->sommet = 0;
}


void emptyPile(PilePiece *p)
{
  p->sommet = 0;
}


gameTab startGame(typeJoueur j1, typeJoueur j2)
{
  gameTab ret;
  startTab(ret.plateau);
  ret.col_joue = blanc;
  ret.nbCoups = 0;
  ret.nbDemiCoups = 0;
  ret.typeJ[0] = j1;
  ret.typeJ[1] = j2;
  ret.roqueDispo = GRD_ROQUE_BLANC | GRD_ROQUE_NOIR
                 | PTT_ROQUE_BLANC | PTT_ROQUE_NOIR;
  emptyPile(&(ret.capturees));
  emptyPile(&(ret.historique));
  return ret;
}

void move_pieceChaine(Liste **tete, int xDepart, int yDepart, int xArrive, int yArrive)
{
  Liste* ptr  = *tete;
  Liste* prec = NULL;
  while(ptr){
    if(ptr->x==xArrive && ptr->y==yArrive){
      Liste* ancien = ptr;
      ptr = ptr->suiv;
      delete ancien;
      if(prec) prec->suiv = ptr;
      else *tete = ptr;
    }
    if(ptr->x==xDepart && ptr->y==yDepart){
      ptr->x = xArrive;
      ptr->y = yArrive;
    }
    prec = ptr;
    ptr = ptr->suiv;
  }
}

void move_pieceTab(Plateau plateau, int xDepart, int yDepart, int xArrive, int yArrive)
{
  Piece piece = plateau[yDepart][xDepart];
  plateau[yDepart][xDepart] = Piece{rien, 0};
  plateau[yArrive][xArrive] = piece;
}

void empiler(PilePiece *p, Piece piece)
{
  if(p->sommet >= MAXCAPTURE) return;
  p->p[p->sommet++] = piece;
}

void empiler(Pile *p, Coup c)
{
  if(p->sommet >= MAXHISTORIQUE) return;
  p->coup[(p->sommet)++] = c;
}


Coup depiler(Pile *p)
{
  if(p->sommet == 0) {
    cout << "Erreur, underflow de l'historique" << endl;
    exit(1);
  }
  return p->coup[--(p->sommet)];
}

Piece depiler(PilePiece *p){
  if(p->sommet == 0) {
    cout << "Erreur, underflow des pieces capturees" << endl;
    exit(1);
  }
  return p->p[--(p->sommet)];
}

Coup move_pieceTab(gameTab* g, int xDepart, int yDepart, int xArrive, int yArrive)
{
  Coup c = {xDepart, yDepart, xArrive, yArrive, 0};
  if(isCheck(g, g->col_joue)){
    g->roqueDispo &= (~(GRD_ROQUE_BLANC<<(g->col_joue))); // on enleve les roques si le roi a bougé
    g->roqueDispo &= (~(PTT_ROQUE_BLANC<<(g->col_joue)));
  }
  Piece piece = g->plateau[yDepart][xDepart];
  if(piece.type == roi && xDepart-xArrive == 2 ){ // grand roque
    c.etat |= GRD_ROQUE_BLANC<<(g->col_joue);
    move_pieceTab(g->plateau, 0,yDepart, xDepart-1, yDepart);
  }
  if(piece.type == roi && xDepart-xArrive == -2 ){ // petit roque
    c.etat |= PTT_ROQUE_BLANC<<(g->col_joue);
    move_pieceTab(g->plateau, 7,yDepart, xDepart+1, yDepart);    
  }
  g->plateau[yDepart][xDepart] = Piece{rien, 0};
  ++(g->nbDemiCoups);
  Piece p = get_squareTab(g->plateau, xArrive, yArrive);
  // TODO: s'occuper de la prise en passant
  // TODO: s'occuper du roque
  if(p.type != rien || p.couleur != 0){ // si on prend une piece
    empiler(&(g->capturees), p);
    g->nbDemiCoups = 0; // s'il y a capture on reset les demis coups
    c.etat |= CAPTURE;
  }
  if(piece.type == roi){
    g->roqueDispo &= (~(GRD_ROQUE_BLANC<<(g->col_joue))); // on enleve les roques si le roi a bougé
    g->roqueDispo &= (~(PTT_ROQUE_BLANC<<(g->col_joue)));
  }
  if(piece.type == tour){ // on enleve le roque spécifique si une tour est deplacée
    if(xDepart == 0) g->roqueDispo &= (~(GRD_ROQUE_BLANC<<(g->col_joue)));
    else if(xDepart == 8) g->roqueDispo &= (~(PTT_ROQUE_BLANC<<(g->col_joue)));
  }
  if(piece.type == pion) g->nbDemiCoups = 0; // s'il y a deplacement de pion on reset les demis coups
  if(g->col_joue) ++(g->nbCoups); // si c'est les noirs qui ont joué, le nombre de coups augmente
  g->plateau[yArrive][xArrive] = piece;
  g->col_joue = !(g->col_joue);
  MAJ_historique(&(g->historique), c);
  return c; // pour éventuellement l'ajouter à l'historique
}


void copy_board(Plateau p, Plateau ret)
{
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille;++j){
      ret[i][j] = p[i][j];
    }
  }
}


void printChaine(Liste* tete)
{
  Liste* ptr = tete;
  while(ptr){
    cout << '('
	 << ptr->x << ','
	 << ptr->y << ','
	 << ptr->piece.type << ','
         << ptr->piece.couleur << ')';
    if(ptr->suiv) cout << "->";
    else          cout << endl;
    ptr = ptr->suiv;
  }
}

void printTab(Plateau plateau)
{
  for(int i = taille-1; i>=0; --i){
    for(int j = 0; j<taille; ++j){
      cout << '(' << plateau[i][j].type << ',' << plateau[i][j].couleur << ')';
    }
    cout << endl;
  }
}

