/*
jeu.h
-------------------

Par Mohameth El Bachir NDIAYE

Rôle, contient les prototypes de jeu.c

Création: Samedi 05/08/2017 à 23 H 26 MN

Dernière Modification: Dimanche 06/08/2017 à 22 H 26 MN
*/

#ifndef DEF_CONSTANTES
#define	DEF_CONSTANTES

void jouer(SDL_Surface *ecran);
void deplacerJoueur(int carte[][NOMBRE_BLOCS_HAUTEUR], SDL_Rect *pos, int direction); //Pos correspond à la position du joeur
void deplacerCaisse(int *premiereCase, int *secondeCase);

#endif
