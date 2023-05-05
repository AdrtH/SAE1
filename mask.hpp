#ifndef MASK_HPP


#define MASK_HPP

Masque empty_mask();
void clear_mask(Masque*);
couleurMasque get_mask(Masque, int, int);
void set_mask(Masque*, int, int, couleurMasque);
void print_board(Plateau, Masque);
void print_square_color(Plateau, int, int, int, int, Masque);

#endif // MASK_HPP



