/*
editeur.c
-------------------

Par Mohameth El Bachir NDIAYE

Rôle, contient les niveaux du jeu

Création: Samedi 05/08/2017 à 23 H 26 MN

Dernière Modification: Samedi 05/08/2017 à 23 H 29 MN
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "editeur.h"
#include "fichiers.h"

void editeur(SDL_Surface *ecran)
{
	SDL_Surface *mur = NULL, *caisse = NULL, *objectif = NULL, *mario = NULL;
	SDL_Rect position;
	SDL_Event event;

	int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
	int objetActuel = MUR, i = 0, j = 0;
	int carte[NOMBRE_BLOCS_LARGEUR][NOMBRE_BLOCS_HAUTEUR] = {0};

	//Chargement des sprites (décors, personnages...)
	mur = IMG_Load("mur.jpg");
	caisse = IMG_Load("caisse.jpg");
	objectif = IMG_Load("objectif.png");
	mario = IMG_Load("mario_bas.gif");

	//Chargement du niveau
	if (!chargerNiveau(carte))
	{
		exit(EXIT_FAILURE); //On arrête le jeu si le fichier de niveau n'existe pas
	}

	while(continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:{
				continuer = 0;
			break;}
	
			case SDL_MOUSEBUTTONDOWN:{
				if (event.button.button == SDL_BUTTON_LEFT) //Click gauche pour placer un objet
				{
					carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
					//On divise pour savoir à quelle case on se trouve (la division envoie une valeur entiere donc case = 2 ou 5 ou...)
					clicGaucheEnCours = 1; //On retient qu'un bouton est enfoncé
				}
				else if (event.button.button == SDL_BUTTON_RIGHT) //Click droit pour effacer l'objet
				{
					carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = VIDE;
					//On divise pour savoir à quelle case on se trouve (la division envoie une valeur entiere donc case = 2 ou 5 ou...)
					clicDroitEnCours = 1;
				}
			break;}
	
			case SDL_MOUSEBUTTONUP:{
				if (event.button.button == SDL_BUTTON_LEFT) //Si le click gauche est relaché on remet clicGaucheEnCours à 0;
				{
					clicGaucheEnCours = 0;
				}
				else if (event.button.button == SDL_BUTTON_RIGHT) //Si le click droit est relaché on remet clicDroitEnCours à 0;
				{
					clicDroitEnCours = 0;
				}
			break;}
	
			case SDL_MOUSEMOTION:{
				if (clicGaucheEnCours) //Si le clic gauche est maintenu, on remplit
				{
					carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = objetActuel;
				}
				else if (clicDroitEnCours) //Si le clic droit est maintenu, on vide
				{
					carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = VIDE;
				}
			break;}
	
			case SDL_KEYDOWN:{
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:{
						continuer = 0;
					break;}
	
					case SDLK_s:{
						sauvegarderNiveau(carte);
					break;}
	
					case SDLK_c:{
						chargerNiveau(carte);
					break;}
	
					case SDLK_KP1:{
						objetActuel = MUR;
					break;}
	
					case SDLK_KP2:{
						objetActuel = CAISSE;
					break;}
	
					case SDLK_KP3:{
						objetActuel = OBJECTIF;
					break;}
	
					case SDLK_KP4:{
						objetActuel = MARIO;
					break;}
				}
			break;}
		}
	
		// Effacement de l'écran
		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
	
		// Placement des objets à l'écran
		for (i = 0 ; i < NOMBRE_BLOCS_LARGEUR ; i++)
		{
		    for (j = 0 ; j < NOMBRE_BLOCS_HAUTEUR ; j++)
		    {
		        position.x = i * TAILLE_BLOC;
		        position.y = j * TAILLE_BLOC;
	
		        switch(carte[i][j])
		        {
		            case MUR:{
		                SDL_BlitSurface(mur, NULL, ecran, &position);
		            break;}
		            case CAISSE:{
		                SDL_BlitSurface(caisse, NULL, ecran, &position);
		            break;}
		            case OBJECTIF:{
		                SDL_BlitSurface(objectif, NULL, ecran, &position);
		            break;}
		            case MARIO:{
		                SDL_BlitSurface(mario, NULL, ecran, &position);
		            break;}
		        }
		    }
		}
	
		// Mise à jour de l'écran
		SDL_Flip(ecran);
	}
	
	SDL_FreeSurface(mur);
	SDL_FreeSurface(caisse);
	SDL_FreeSurface(objectif);
	SDL_FreeSurface(mario);
}