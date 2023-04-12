// Ce fichier permet de donner un exemple pratique en C de nos représentations.

// REPRESENTATION DES PIECES

// structures par struct "unique"

struct Pion {
  bool couleur;
  bool a_bougé;
};
struct Roi{
  bool couleur;
  bool a_bougé;
};
struct Reine{
  bool couleur;
};
etc..

// Representation par struct globale

enum typeDePiece{
     pion,
     fou,
     cavalier, etc..
};

struct Piece{
  bool        couleur;
  typeDePiece type;
};

// Representation par enumeration
enum pieces{
     pionBlanc,
     pionNoir,
     fouBlanc,...

}

// REPRESENTATION DU PLATEAU

Piece plateau[8][8];

// OU

struct plateau{
  Piece plateau[8][8];
  Piece prises;
  bool blanc_echec;
  bool noir_echec;
};

