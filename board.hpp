
#ifndef BOARD_HPP

#define BOARD_HPP

// FONCTIONS SUR TABLEAU
void emptyTableau(Plateau);
Piece get_squareTab(Plateau, int, int);
void set_squareTab(Plateau, int, int, Piece);
void startTab(Plateau);
void move_pieceTab(Plateau, int, int, int, int);
void printTab(Plateau);
Coup move_pieceTab(gameTab*, int, int, int, int);
gameTab startGame();
void copy_board(Plateau, Plateau);
void empiler(Pile*, Coup);
Coup depiler(Pile*);

// FONCTIONS SUR CHAINE
void emptyChaine(Liste*);
Piece get_squareChaine(Liste*, int, int);
void set_squareChaine(Liste*, int, int, Plateau);
Liste* startChaine();
void move_pieceChaine(Liste **, int, int, int, int);
void printChaine(Liste*);


#endif //BOARD_HPP
