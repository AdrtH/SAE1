#ifndef TYPES_HPP

#define TYPES_HPP

#include <string>

const int  taille        = 8;
const bool blanc	 = false;
const bool noir	         = true;
const int  MAXHISTORIQUE = 100;

enum typePiece{
	       pion,
	       fou,
	       cavalier,
	       tour,
	       reine,
	       roi,
	       rien
};

struct Piece{
  typePiece	type;
  bool		couleur;
};

typedef Piece Plateau[taille][taille];

struct Liste{
  int    x,y;
  Piece  piece;
  Liste* suiv;
};

struct Coup{
  int xDepart, yDepart;
  int xArrive, yArrive;
};

struct Pile{
  Coup        coup[MAXHISTORIQUE];
  int         sommet;
};

struct gameChaine{
  Liste* plateau;
  int    tour;
  Piece  capturees[32];
  Pile   historique;
};

struct gameTab{
  Plateau      plateau;
  int          tour;
  Piece        capturees[32];
  Pile         historique;
  std::string  enPassant;
  int          nbCoups; // à incrementer apres jeu de noirs
  int          nbDemiCoups; // incrementer à chaque jeu et reset quand capture
};

typedef unsigned char typeMasque;

const typeMasque ACCESSIBLE =   0b1;
const typeMasque ACTUELLE   =  0b10;
const typeMasque ATTAQUEE   = 0b100;

struct Masque{
  typeMasque masque[taille][taille];
};


#endif //TYPES_HPP
