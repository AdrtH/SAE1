Pour compiler le programme:
lancer cmake dans un dossier build,
lancer make main un executable "main" sera créer, c'est le jeu d'echecs.

Précision: quand des coordonnées sont demandées, toujours les saisir dans la forme lettre nombre
par exemple: e4
la lettre doit être en minuscule

La seule fonctionnalitée non implementée est l'arrêt à 50 coups.
Nous avons implementée comme améliorations le pat et le roque.
Nous avons aussi pris l'initiative de pouvoir sauvegarder dans un fichier un historique d'une partie, qui peut être charger par la suite. Pour sauvegarder une partie, il faut que celle-ci soit finie, quelque soit la maniere.

Le jeu est fonctionnel, il manque seulement des règles comme la promotion de pion, la prise en passant, la règles des 50 coups, et la règle des positions repetées pour en faire un jeu d'echecs complet.
