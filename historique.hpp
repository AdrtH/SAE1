#ifndef HISTORIQUE_HPP

using namespace std;

#define HISTORIQUE_HPP

void MAJ_historique(Pile*, Coup);
void play_historique(Pile);


void save_historique(Pile, char*);
Pile load_historique(char*, bool*);

#endif // HISTORIQUE_HPP
