#ifndef BOARD_HPP

#define BOARD_HPP

// FONCTIONS SUR TABLEAU
void emptyTableau(Piece);
Piece get_squareTab(Piece, int, int);
void set_squareTab(Piece, int, int, Piece);
void startTab(Piece);
void move_pieceTab(Piece, int, int, int, int);
void printTab(Piece);

// FONCTIONS SUR CHAINE
void emptyChaine(Liste*);
Piece get_squareChaine(Liste*, int, int);
void set_squareChaine(Liste*, int, int, Piece);
Liste* startChaine();
void move_pieceChaine(Liste **, int, int, int, int);
void printChaine(Liste*);
