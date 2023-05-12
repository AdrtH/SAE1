#ifndef MASK_HPP


#define MASK_HPP

Masque empty_mask();
void clear_mask(Masque*);
couleurMasque get_mask(Masque, int, int);
void set_mask(Masque*, int, int, couleurMasque);
void print_board(Plateau, Masque);
void print_square_color(Plateau, int, int, int, int, Masque);
void highlight_possible_moves_pawn(Plateau, int, int, Masque*);
void highlight_possible_moves(Plateau, int, int, Masque*);
void highlight_possible_moves_king(Plateau, int, int, Masque*);
void highlight_possible_moves_rook(Plateau, int, int, Masque*);
void highlight_possible_moves_bishop(Plateau, int, int, Masque*);
void highlight_possible_moves_knight(Plateau, int, int, Masque*);
void highlight_possible_moves_queen(Plateau, int, int, Masque*);

void highlight_movable_pieces(Plateau, bool, Masque*);
void highlight_attacked_pieces(Plateau, bool, Masque*);
void highlight_take_pieces(Plateau, int, int, Masque*);
void mask_choices(Plateau, bool);
  
#endif // MASK_HPP



