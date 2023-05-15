#include <iostream>
#include <random>
#include "types.hpp"
#include "board.hpp"
#include "view.hpp"
#include "mask.hpp"
#include "board.hpp"
#include "historique.hpp"
#include "game.hpp"
using namespace std;

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

bool test_run(gameTab *g, Coup coup, bool couleur){
    Piece piece = get_squareTab(g->plateau, coup.xDepart, coup.yDepart);
    if ((piece.type == rien) || (piece.couleur != couleur)){
        return false;
    }
    Masque m = empty_mask();
    Masque m1 = empty_mask();
    highlight_movable_pieces(g, couleur, &m);
    if(get_mask(m, coup.xDepart,coup.yDepart) != cyan) 
        return false;
    highlight_possible_moves(g, coup.xDepart, coup.yDepart, &m);
    if(get_mask(m, coup.xArrive, coup.yArrive) != bleu)
        return false;
    return true;
}

Coup choose_mouvement_human(gameTab* g, bool couleur){
    Coup c;
    char char1, char2;
    cout << "Coordonnées du point de départ : ";
    cin >> char1 >> c.yDepart;
    c.xDepart = int(char1) - 97;
    c.yDepart--;
    cout << "Coordonnées du point d'arrivée : ";
    cin >> char2 >> c.yArrive;
    c.xArrive = int(char2) - 97;
    c.yArrive--;
    if (!test_run(g, c, couleur)){
        return choose_mouvement_human(g, couleur);
    }
    return c;
}

void one_run_human(gameTab* G){
    Coup coup;
    mask_choices(G, G->col_joue);
    coup = choose_mouvement_human(G, G->col_joue);
    Piece piece = get_squareTab(G->plateau, coup.xDepart, coup.yDepart);
    move_pieceTab(G, coup.xDepart, coup.yDepart, coup.xArrive, coup.yArrive);
}

void one_run(gameTab* G){
    if (G->typeJ[G->col_joue] == humain){
        one_run_human(G);
        print_board(G->plateau);
    }
    else{
        one_run_computer(G);
        print_board(G->plateau);
    }
} 

Coup choose_mouvement_computer(gameTab *g) // avec l'architecture du code, on n'a pas besoin de fonction tel que "choose movement king in check computer" car le masque empeche deja à l'ordinateur de jouer un coup illégal.
{
  Coup ret;
  Masque m = empty_mask();
  highlight_movable_pieces(g, g->col_joue, &m);
  int count=0;
  int coords[64][2] = {{0}};
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      if(get_mask(m, j,i) == cyan) {
	coords[count][0] = j;
	coords[count][1] = i;
	++count;
      }
    }
  }
  int choix = alea(0,count-1);
  ret.xDepart = coords[choix][0];
  ret.yDepart = coords[choix][1];
  clear_mask(&m);
  highlight_possible_moves(g, ret.xDepart, ret.yDepart, &m);
  count = 0;
  for(int i=0; i<taille; ++i){
    for(int j=0; j<taille; ++j){
      if(get_mask(m, j,i) == bleu) {
	coords[count][0] = j;
	coords[count][1] = i;
	++count;
      }
    }
  }
  choix = alea(0,count-1);
  count = 0;
  ret.xArrive = coords[choix][0];
  ret.yArrive = coords[choix][1];
  // TODO: prendre en compte prise en passant/roque dans etat de coup
  return ret;
}

void one_run_computer(gameTab *g)
{
  Coup coup = choose_mouvement_computer(g);
  move_pieceTab(g, coup.xDepart, coup.yDepart, coup.xArrive, coup.yArrive);
  
}
