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
  Piece plateau[taille][taille];
  int   tour;
  Piece capturees[32];
  Pile  historique;
};
