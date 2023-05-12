#include <iostream>
#include "types.hpp"
#include "board.hpp"
#include "view.hpp"
#include "mask.hpp"
#include "game.hpp"

using namespace std;

int main(void)
{
    gameTab jeuTab;
    startTab(jeuTab.plateau);
    print_board(jeuTab.plateau);

    Masque masque = empty_mask();

    jeuTab.col_joue = 0;
    jeuTab.typeJ[0] = humain;

    move_pieceTab(jeuTab.plateau, 4, 1, 4, 3); // simuler pion e4
    print_board(jeuTab.plateau, masque);

    clear_mask(&masque);

    one_run(&jeuTab);

    print_board(jeuTab.plateau, masque);

    return 0;
}