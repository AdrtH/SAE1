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
  Coup coup[MAXHISTORIQUE];
  int  sommet;
};

struct gameChaine{
  Liste* plateau;
  int    tour;
  Piece  capturees[32];
  Pile   historique;
};

enum typeJoueur{
  ordi,
  humain,
};

struct gameTab{
  Plateau      plateau;
  bool         col_joue;
  int          tour;
  Piece        capturees[32];
  Pile         historique;
  std::string  enPassant;
  int          nbCoups; // à incrementer apres jeu de noirs
  int          nbDemiCoups; // incrementer à chaque jeu et reset quand capture
  typeJoueur   typeJ[2];
};


enum couleurMasque{
  noCol   = 0,
  rouge   = 9,
  vert    = 10,
  orange  = 202,
  bleu    = 12,
  violet  = 89,
  cyan    = 14,
  gris    = 8
};

struct Masque{
  couleurMasque masque[taille][taille];
};


#endif //TYPES_HPP
