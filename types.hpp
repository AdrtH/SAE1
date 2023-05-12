#ifndef TYPES_HPP

#define TYPES_HPP

#include <string>

typedef FLAG unsigned char;

const int  taille        = 8;
const bool blanc	 = false;
const bool noir	         = true;
const int  MAXHISTORIQUE = 512;
const int  MAXCAPTURE    = 32; 

enum typePiece{
	       pion,
	       fou,
	       cavalier,
	       tour,
	       reine,
	       roi,
	       rien
};

enum typeJoueur {
  ordi,
  humain
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

FLAG GRD_ROQUE_BLANC  = 1;    // 0000 0001
FLAG GRD_ROQUE_NOIR   = 1<<1; // 0000 0010
FLAG PTT_ROQUE_BLANC  = 1<<2; // 0000 0100
FLAG PPR_ROQUE_NOIR   = 1<<3; // 0000 1000
FLAG PRISE_EN_PASSANT = 1<<4;    // 0000 0001
FLAG CAPTURE          = 1<<5; // 0000 0010

struct Coup{
  int  xDepart, yDepart;
  int  xArrive, yArrive;
  FLAG etat; // bool prise en passant, capture et roque
};

struct Pile{
  Coup coup[MAXHISTORIQUE]; // trouvé une solution pour revert un coup avec une prise
  int  sommet;
};

struct PilePiece{
  Piece p[MAXCAPTURE];
  int   sommet;
};

struct gameChaine{
  Liste* plateau;
  int    tour;
  Piece  capturees[32];
  Pile   historique;
};

struct gameTab{
  Plateau      plateau;
  bool         col_joue;
  PilePiece    capturees;
  Pile         historique;
  int          nbCoups;     // incrementer apres jeu de noirs
  int          nbDemiCoups; // incrementer à chaque jeu et reset quand capture
  typeJoueur   typeJ[2];
  FLAG         roqueDispo;
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
