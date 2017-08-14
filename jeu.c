/*
jeu.c
-------------------

Par Mohameth El Bachir NDIAYE

Rôle, contient le jeu

Création: Samedi 05/08/2017 à 23 H 26 MN

Dernière Modification: Vendredi 12/08/2017 à 01 H 05 MN
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "jeu.h"

void jouer(SDL_Surface *ecran)
{
	SDL_Surface *mario[4] = {NULL};
	SDL_Surface *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL;
	SDL_Rect position, positionJoueur;
	SDL_Event event;

	int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
	int carte[NOMBRE_BLOCS_LARGEUR][NOMBRE_BLOCS_HAUTEUR] = {0};

	//Chargement des sprites (décors, personnages...)
	mur = IMG_Load("mur.jpg");
	caisse = IMG_Load("caisse.jpg");
	caisseOK = IMG_Load("caisse_ok.jpg");
	objectif = IMG_Load("objectif.png");
	mario[HAUT] = IMG_Load("mario_haut.gif");
	mario[BAS] = IMG_Load("mario_bas.gif");
	mario[GAUCHE] = IMG_Load("mario_gauche.gif");
	mario[DROITE] = IMG_Load("mario_droite.gif");

	marioActuel = mario[BAS]; //Mario sera dirigé vers le bas au départ (L'image qui regarde vers nous)

	//Chargement du niveau
	if (!chargerNiveau(carte))
	{
		exit(EXIT_FAILURE); //On arrête le jeu si le fichier de niveau n'existe pas
	}

	//Recherche de la position au depart de Mario
	for (i = 0; i < NOMBRE_BLOCS_LARGEUR; i++)
	{
		for (j = 0; j < NOMBRE_BLOCS_LARGEUR; j++)
		{
			if (carte[i][j] == MARIO)
			{
				positionJoueur.x = i;
				positionJoueur.y = j;
				carte[i][j] = VIDE;
			}
		}
	}

	SDL_EnableKeyRepeat(100, 100);

	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:{
				continuer = 0;
				break;}

			case SDL_KEYDOWN:{
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:{
						continuer = 0;
					break;}

					case SDLK_UP:{
						marioActuel = mario[HAUT];
						deplacerJoueur(carte, &positionJoueur, HAUT);
					break;}

					case SDLK_DOWN:{
						marioActuel = mario[BAS];
						deplacerJoueur(carte, &positionJoueur, BAS);
					break;}

					case SDLK_LEFT:{
						marioActuel = mario[GAUCHE];
						deplacerJoueur(carte, &positionJoueur, GAUCHE);
					break;}

					case SDLK_RIGHT:{
						marioActuel = mario[DROITE];
						deplacerJoueur(carte, &positionJoueur, DROITE);
					break;}
				}
			break;}
		}	

		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); //Effacement de l'ecran

		//Placement des objets à l'ecran
		objectifsRestants = 0;

		for (i = 0; i < NOMBRE_BLOCS_LARGEUR; i++)
		{
			for (j = 0; j < NOMBRE_BLOCS_HAUTEUR; j++)
			{
				position.x = TAILLE_BLOC * i;
				position.y = TAILLE_BLOC * j;

				switch (carte[i][j])
				{
					case MUR:{
						SDL_BlitSurface(mur, NULL, ecran, &position);
					break;}

					case CAISSE:{
						SDL_BlitSurface(caisse, NULL, ecran, &position);
					break;}

					case CAISSE_OK:{
						SDL_BlitSurface(caisseOK, NULL, ecran, &position);
					break;}

					case OBJECTIF:{
						SDL_BlitSurface(objectif, NULL, ecran, &position);
						objectifsRestants = 1; //Tant qu'il y'a au moins un objectif, objectifsRestants vaut 1 (Pour le test de victoire)|Booleen
					break;}
				}
			}
		}

		//Si on a trouvé aucun objectif sur la carte c'est qu'on a gagné
		if (!objectifsRestants)
		{
			continuer = 0;
		}

		position.x = positionJoueur.x * TAILLE_BLOC;
		position.y = positionJoueur.y * TAILLE_BLOC;
		SDL_BlitSurface(marioActuel, NULL, ecran, &position);

		SDL_Flip(ecran);
	}


	//On desactive la repetition des touches (remise à 0)
	SDL_EnableKeyRepeat(0, 0);

	//On décharge les surfaces
	SDL_FreeSurface(mur);
	SDL_FreeSurface(caisse);
	SDL_FreeSurface(caisseOK);
	SDL_FreeSurface(objectif);
	
	for (i = 0; i < 4; i++)
	{
		SDL_FreeSurface(mario[i]);
	}
}

void deplacerJoueur(int carte[][NOMBRE_BLOCS_HAUTEUR], SDL_Rect *pos, int direction) //Pos correspond à la position du joeur
{
	switch(direction)
	{
		case HAUT:{ //On fait des test pour verifier qu'on est pas au bord de la carte ou s'il n'y a pas un mur ou 2caisses au dessus avant de se déplacer
			if (pos->y - 1 < 0)
			{
				break;
			}

			if (carte[pos->x][pos->y - 1] == MUR)
			{
				break;
			}
			
			if ((carte[pos->x][pos->y - 1] == CAISSE || carte[pos->x][pos->y - 1] == CAISSE_OK) && (pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR || carte[pos->x][pos->y - 2] == CAISSE || carte[pos->x][pos->y - 2] == CAISSE_OK))
			{
				break;
			}

			//Si tous ces tests sont passés, on peut déplacer le joueur
			//Mais on vérifie d'abord s'il y'a une caisse à déplacer
			deplacerCaisse(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);
			pos->y--; //Deplacement du jouer vers le haut
		break;}

		case BAS:{
			if (pos->y + 1 >= NOMBRE_BLOCS_HAUTEUR)
			{
				break;
			}

			if (carte[pos->x][pos->y + 1] == MUR) 
			{
				break;
			}

			if ((carte[pos->x][pos->y + 1] == CAISSE || carte[pos->x][pos->y + 1] == CAISSE_OK) && (pos->y + 2 >= NOMBRE_BLOCS_HAUTEUR || carte[pos->x][pos->y + 2] == MUR || carte[pos->x][pos->y + 2] == CAISSE || carte[pos->x][pos->y + 2] == CAISSE_OK))
			{
				break;
			}

			deplacerCaisse(&carte[pos->x][pos->y + 1], &carte[pos->x][pos->y + 2]);
			pos->y++; //Deplacement du jouer vers le bas
		break;}

		case GAUCHE:{
			if (pos->x - 1 < 0)
			{
				break;
			}

			if (carte[pos->x - 1][pos->y] == MUR)
			{
				break;
			}
			
			if ((carte[pos->x - 1][pos->y] == CAISSE || carte[pos->x - 1][pos->y] == CAISSE_OK) && (pos->x - 2 < 0 || carte[pos->x - 2][pos->y] == MUR || carte[pos->x- 2][pos->y ] == CAISSE || carte[pos->x - 2][pos->y] == CAISSE_OK))
			{
				break;
			}

			deplacerCaisse(&carte[pos->x - 1][pos->y], &carte[pos->x - 2][pos->y]);
			pos->x--; //Deplacement du jouer vers la gauche
		break;}

		case DROITE:{
			if (pos->x + 1 >= NOMBRE_BLOCS_LARGEUR)
			{
				break;
			}

			if (carte[pos->x + 1][pos->y] == MUR)
			{
				break;
			}
			
			if ((carte[pos->x + 1][pos->y] == CAISSE || carte[pos->x + 1][pos->y] == CAISSE_OK) && (pos->x + 2 >= NOMBRE_BLOCS_LARGEUR || carte[pos->x + 2][pos->y] == MUR || carte[pos->x + 2][pos->y] == CAISSE || carte[pos->x + 2][pos->y] == CAISSE_OK))
			{
				break;
			}

			deplacerCaisse(&carte[pos->x + 1][pos->y], &carte[pos->x + 2][pos->y]);
			pos->x++; //Deplacement du jouer vers la droite
		break;}

	}
}

void deplacerCaisse(int *premiereCase, int *secondeCase)
{
	if (*premiereCase == CAISSE || *premiereCase == CAISSE_OK)
	{
		if (*secondeCase == OBJECTIF)
		{
			*secondeCase = CAISSE_OK;
		}
		else
		{
			*secondeCase = CAISSE;
		}

		if (*premiereCase == CAISSE_OK)
		{
			*premiereCase = OBJECTIF;
		}
		else
		{
			*premiereCase = VIDE;
		}
	}
}
