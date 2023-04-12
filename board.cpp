#include <iostream>
#include "type.hpp"

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
  return plateau[x][y];
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

void startTab(Piece plateau)
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
    //prec = ptr;
    ptr = ptr->suiv;
  }
}

void move_pieceTab(Piece plateau, int xDepart, int yDepart, int xArrive, int yArrive)
{
  Piece piece = plateau[yDepart][xDepart];
  plateau[yDepart][xDepart] = Piece{rien, 0};
  plateau[yArrive][xArrive] = piece;
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


void printTab(Piece plateau)
{
  for(int i = taille-1; i>=0; --i){
    for(int j = 0; j<taille; ++j){
      cout << '(' << plateau[i][j].type << ',' << plateau[i][j].couleur << ')';
    }
    cout << endl;
  }
}
