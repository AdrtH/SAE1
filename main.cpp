#include <iostream>
#include "types.hpp"
#include "board.hpp"
#include "view.hpp"
#include "mask.hpp"
#include "historique.hpp"
#include "game.hpp"

using namespace std;

void capitalize(char* c)
{
  if(*c > 90) *c = (*c)-32;
}


void play()
{
  char input;
  do{
    cout << "Entrez H si le joueur 1 (blanc) est humain et O si le joueur 1 est un ordinateur : ";
    cin  >> input;
    capitalize(&input);
  }while(input != 'O' && input != 'H');
  typeJoueur j1 = (input == 'H')? humain: ordi;
  do{
    cout << "Entrez H si le joueur 2 (blanc) est humain et O si le joueur 2 est un ordinateur : ";
    cin  >> input;
    capitalize(&input);
  }while(input != 'O' && input != 'H');
  typeJoueur j2 = (input == 'H')? humain: ordi;
  gameTab jeu = startGame(j1,j2);
  while(!isCheckMate(jeu.plateau, blanc) && !isCheckMate(jeu.plateau, noir)
	&& !isPat(jeu.plateau, jeu.col_joue)){
    one_run(&jeu);
  }
  cout << !isCheckMate(jeu.plateau, blanc) << endl;
  cout << !isCheckMate(jeu.plateau, noir)  << endl;
  cout << !isPat(jeu.plateau, blanc)       << endl;
  cout << !isPat(jeu.plateau, noir)        << endl;  
  if(isCheckMate(jeu.plateau, noir)){
    cout << "Le joueur blanc a gagné" << endl;
  } else if(isCheckMate(jeu.plateau, blanc)){
    cout << "Le joueur noir a gagné" << endl;
  } else {
    cout << "Egalité!" << endl;
  }
  cout << "Voulez-vous enregistrer cette partie ? (O/N) ";
  cin  >> input;
  capitalize(&input);
  if(input == 'O'){
    char *str;
    string input = "";
    while(input.length() > 63 || input == ""){
      cout << "Entrez le nom de la sauvegarde (63 char max): ";
      cin  >> input;
    }
    str = new char[input.length()+1];
    for(int i=0; i<input.length(); ++i){
      str[i] = input[i];
    }
    str[input.length()] = '\0';
    save_historique(jeu.historique, str);
  }
}

void load()
{
  char *str;
  string input = "";
  while(input.length() > 63 || input == ""){
    cout << "Entrez le nom de la sauvegarde (63 char max): ";
    cin  >> input;
  }
  str = new char[input.length()+1];
  for(int i=0; i<input.length(); ++i){
      str[i] = input[i];
    }
  str[input.length()] = '\0';
  bool res;
  Pile h = load_historique(str, &res);
  if(!res) return;
  play_historique(h);
}

int main(void)
{
  char input;
  while(true){
    cout << "---------- ECHECS ----------" << endl;
    cout << "| Que voulez-vous faire ?  |" << endl
	 << "|                          |" << endl;
    cout << "| Jouer une partie   (J)   |" << endl;
    cout << "| Charger une partie (C)   |" << endl;
    cout << "|                          |" << endl;
    cout << "| Sortir         (Autre)   |" << endl;
    cout << "----------------------------" << endl;
    cin  >> input;
    capitalize(&input);
    switch(input){
    case 'J':
      play();
      break;
    case 'C':
      load();
      break;
    default:
      return 0;
    }
  }
  return 0;
};
