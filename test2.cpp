#include <iostream>
#include "types.hpp"
#include "board.hpp"
#include "view.hpp"
#include "mask.hpp"
#include "game.hpp"
#include "historique.hpp"

using namespace std;

int main(void)
{
    gameTab jeuTab;
    startTab(jeuTab.plateau);
    print_board(jeuTab.plateau);

    Masque masque = empty_mask();

    jeuTab.col_joue = 1;
    jeuTab.typeJ[0] = humain;
    jeuTab.typeJ[1] = ordi;

    one_run(&jeuTab);
    one_run(&jeuTab);
    one_run(&jeuTab);

    backtrack_historique(&jeuTab);

    print_board(jeuTab.plateau, masque);

    return 0;
}