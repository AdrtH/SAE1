#ifndef TYPES_HPP

#define TYPES_HPP

const int  taille        = 8;
const bool blanc	 = false;
const bool noir	         = true;
const int  MAXHISTORIQUE = 100;


using Plateau = Piece[taille][taille];


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

struct Liste{
  int    x,y;
  Piece  piece;
  Liste* suiv;
};

struct Pile{
  string coup[MAXHISTORIQUE];
  int    sommet;
};

struct gameChaine{
  Liste* plateau;
  int    tour;
  Piece  capturees[32];
  Pile   historique;
};

struct gameTab{
  Plateau
 plateau;
  int   tour;
  Piece capturees[32];
  Pile  historique;
};


#endif //TYPES_HPP
