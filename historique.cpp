#include <iostream>
#include <fstream>
#include "types.hpp"
#include "board.hpp"
#include "historique.hpp"
#include "view.hpp"


using namespace std;

void MAJ_historique(Pile *p, Coup c)
{
  empiler(p, c);
}

void play_historique(Pile p)
{
  gameTab g = startGame(humain, humain);
  print_board(g.plateau);
  char buffer;
  for(int i=0; i<p.sommet; ++i){
    move_pieceTab(&g, p.coup[i].xDepart, p.coup[i].yDepart, p.coup[i].xArrive, p.coup[i].yArrive);
    print_board(g.plateau);
    if(i<p.sommet-1)cout << "Appuyez sur entrée pour passer au coup suivant" << endl;
    else cout << "Appuyez sur entrée pour sortir" << endl;
    getchar();
  }
}

// Petit bonus: on rajoute une fonctionnalitée, on peut sauvegarder une partie jouée, et la recharger (pour utiliser play_historique après)
// On utilise un genre de format csv pour ca, chaque ligne va enregistrer un coup
void save_historique(Pile p, char* filepath)
{
  ifstream test(filepath); // on test si le fichier existe
  char answer;
  if (test){ // le fichier existe t il ?
    cout << "Le nom spécifié existe, voulez vous l'écraser (O)? Annuler (Autre)? ";
    cin  >> answer;
    if(answer == 'o' || answer == 'O'){
      int res = remove(filepath);
      if(!res) cout << "Le fichier a été supprimé avec succes." << endl;
      else {
	cout << "Erreur lors de la suppression du fichier, annulation de l'opération" << endl;
	test.close();
	return;
      }
    } else {
      test.close();
      return;
    }
  } 
  ofstream file(filepath);
  if (file){
    file << p.sommet << endl; // la premiere ligne désigne le sommet
    Coup c;
    for(int i=0; i<p.sommet; ++i){
      c = p.coup[i];
      file << c.xDepart << ' ' << c.yDepart << ' '
	   << c.xArrive << ' ' << c.yArrive << ' '
	   << (int)c.etat << endl;
    }
    cout << "Fichier créer avec succes." << endl;
  } else {
    cout << "Erreur lors de la création du fichier, abandon" << endl;
    file.close();
    return;
  }
  file.close();
}

Pile load_historique(char* filepath, bool* res)
{
  Pile ret;
  ifstream file(filepath);
  if(!filepath){
    cout << "Erreur lors de l'ouverture du fichier" << endl;
    *res = false;
    file.close();
    return ret;
  }
  file >> ret.sommet;
  if(ret.sommet < 0 || ret.sommet > MAXHISTORIQUE){
    cout << "Erreur, le format du fichier ne convient pas" << endl;
    *res = false;
    file.close();
    return ret;
  }
  int i=0;
  int etat;
  while(!file.eof() && i<ret.sommet){
      file >> ret.coup[i].xDepart >> ret.coup[i].yDepart
           >> ret.coup[i].xArrive >> ret.coup[i].yArrive
           >> etat;
      ret.coup[i].etat = (unsigned char)etat;
      ++i;
  }
  if(i<ret.sommet){
    cout << "Erreur le fichier est invalide" << endl;
    *res = false;
  } else *res = true;
  file.close();
  return ret;
}
