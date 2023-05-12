#include <iostream>
#include <random>
#include "mask.hpp"
#include "historique.hpp"


int alea(int n1, int n2)
{
  if(n1 > n2) {
    cout << "ERREUR: intervale d'aleatoire invalide" << endl;
    exit(1);
  }
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<> dist(n1, n2);

  int ret = dist(rng);
  return ret;
  
}


void one_run_human(gameTab *g)
{
  mask_choices(g->plateau, g->col);
}

Coup choose_mouvement_human();
Coup choose_mouvement_computer(gameTab *g)
{
  Coup ret;
  Masque m = empty_mask();
  highlight_movable_pieces(g->plateau, g->col, &m);
  int count=0;
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      if(get_mask(m, j,i) == cyan) ++count;
    }
  }
  int choix = alea(0,count);
  count = 0;
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      if(get_mask(m, j,i) == cyan) ++count;
      if(count == choix){
	ret.xDepart = j;
	ret.yDepart = i;
      }
    }
  }
  clear_mask(&m);
  highlight_possible_moves(g->plateau, j,i, &m);
  choix = 0;
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      if(get_mask(m, j,i) == cyan) ++count;
    }
  }
  count = 0;
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      if(get_mask(m, j,i) == cyan) ++count;
    }
  }
  choix = alea(0,count);
  count = 0;
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      if(get_mask(m, j,i) == cyan) ++count;
      if(choix == count){
	ret.xArrive = j;
	ret.yArrive = i;
      }
    }
  }
  return ret;
}

void one_run_computer(gameTab *g)
{
  Coup coup = choose_mouvement_computer(g);
  coup = move_pieceTab(g, coup.xDepart, coup.yDepart, coup.xArrive, coup.yArrive);
  
}


void one_run(gameTab* g)
{
  

}
