/*
fichiers.h
-------------------

Par Mohameth El Bachir NDIAYE

Rôle, ...

Création: Samedi 05/08/2017 à 23 H 26 MN

Dernière Modification: Samedi 05/08/2017 à 23 H 29 MN
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "fichiers.h"

int chargerNiveau(int niveau[][NOMBRE_BLOCS_HAUTEUR])
{
	FILE* fichier = NULL;
	char ligneFichier[NOMBRE_BLOCS_HAUTEUR * NOMBRE_BLOCS_LARGEUR + 1] = {0};
	int i = 0, j = 0;

	fichier = fopen("niveaux.lvl", "r");

	if (fichier == NULL)
	{
		return 0;
	}

	fgets(ligneFichier, NOMBRE_BLOCS_HAUTEUR * NOMBRE_BLOCS_LARGEUR + 1, fichier);
	//fgets(chaine, taille_a_lire, fichier);

	for (i = 0; i < NOMBRE_BLOCS_LARGEUR; i++)
	{
		for (j = 0; j < NOMBRE_BLOCS_HAUTEUR; j++)
		{
			switch (ligneFichier[(i * NOMBRE_BLOCS_LARGEUR) + j])
			{
				case '0':{
					niveau[j][i] = 0;
				break;}

				case '1':{
					niveau[j][i] = 1;
				break;}

				case '2':{
					niveau[j][i] = 2;
				break;}

				case '3':{
					niveau[j][i] = 3;
				break;}

				case '4':{
					niveau[j][i] = 4;
				break;}
			}
		}
	}

	fclose(fichier);
	return 1; //Pour indiquer que tout c'est bien passé
}

int sauvegarderNiveau(int niveau[][NOMBRE_BLOCS_HAUTEUR])
{
	FILE* fichier;
	int i = 0, j = 0;

	fopen("niveaux.lvl", "w");
	if (fichier == NULL)
	{
		return 0;
	}

	for (i = 0; i < NOMBRE_BLOCS_LARGEUR; i++)
	{
		for (j = 0; j < NOMBRE_BLOCS_HAUTEUR; j++)
		{
			fprintf(fichier, "%d", niveau[j][i]);
		}
	}

	fclose(fichier);
	return 1; //Pour indiquer que tout c'est bien passé
}