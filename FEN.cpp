void write_FEN(Piece Plateau[taille][taille], string fichier){
  ofstream fic(fichier);
  if (fic){
    for(int i = taille-1; i > -1; i--){
      for(int j = 0; j < taille; j++){

        if (Plateau[i][j].type == rien){
          int compteur = 1;
          while ((j < 7) && (Plateau[i][j+1].type == rien)){
            compteur++;
            j++;
          }
          fic << compteur;
        }

        else if (Plateau[i][j].type != rien){
            if(Plateau[i][j].couleur){
                if (Plateau[i][j].type == pion){
                    fic << "p";
                }
                if (Plateau[i][j].type == fou){
                    fic << "b";
                }
                if (Plateau[i][j].type == cavalier){
                    fic << "n";
                }
                if (Plateau[i][j].type == tour){
                    fic << "r";
                }
                if (Plateau[i][j].type == reine){
                    fic << "q";
                }
                if (Plateau[i][j].type == roi){
                    fic << "k";
                }
            }
            else{
                if (Plateau[i][j].type == pion){
                    fic << "P";
                }
                if (Plateau[i][j].type == fou){
                    fic << "B";
                }
                if (Plateau[i][j].type == cavalier){
                    fic << "N";
                }
                if (Plateau[i][j].type == tour){
                    fic << "R";
                }
                if (Plateau[i][j].type == reine){
                    fic << "Q";
                }
                if (Plateau[i][j].type == roi){
                    fic << "K";
                }
            }
        }
      }
      if (i != 0)
      fic << "/";
    }
  }
  else{
    cout << "Erreur" << endl;
  }
    fic.close();
}

void read_FEN(Piece Plateau[taille][taille], string fichier){
    ifstream fic(fichier);
    if (fic){
        int i = 7;
        int j = 0;
        char a;
        while(!fic.eof()){
            fic >> a;
                if (((int)a-48 < 9) && ((int)a-48 > -1)){
                    for (int k = 0; k < int(a)-48; k++){
                        Plateau[i][j].type = rien;
                        Plateau[i][j].couleur = false;
                    }
                }

                if ((int)a == 47)
                    i--;

                if (((int)a > 64) && ((int)a < 91)){
                    Plateau[i][j].couleur = false;
                    if (a == 'R'){
                        Plateau[i][j].type = tour;
                    }
                    if (a =='N'){
                        Plateau[i][j].type = cavalier;
                    }
                    if (a == 'B'){
                        Plateau[i][j].type = fou;
                    }
                    if (a == 'Q'){
                        Plateau[i][j].type = reine;
                    }
                    if (a == 'K'){
                        Plateau[i][j].type = roi;
                    }
                    if (a == 'P'){
                        Plateau[i][j].type = pion;
                    }
                }

                if (((int)a > 96) && ((int)a < 123)){
                    Plateau[i][j].couleur = true;
                    if (a == 'r'){
                        Plateau[i][j].type = tour;
                    }
                    if (a == 'n'){
                        Plateau[i][j].type = cavalier;
                    }
                    if (a == 'b'){
                        Plateau[i][j].type = fou;
                    }
                    if (a == 'q'){
                        Plateau[i][j].type = reine;
                    }
                    if (a == 'k'){
                        Plateau[i][j].type = roi;
                    }
                    if (a == 'p'){
                        Plateau[i][j].type = pion;
                    }
                }
                j++;
                if (j == 8)
                    j = 0;
            }
            cout << "coucou" << endl;

    }
    else{
        cout << "Erreur";
    }
    fic.close();
}