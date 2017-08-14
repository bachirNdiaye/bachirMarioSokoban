/*
main.c
-------------------

Par Mohameth El Bachir NDIAYE

Rôle, menu du jeu. Permet de choisir entre l'éditeur et le jeu lui-même.

Création: Samedi 05/08/2017 à 23 H 26 MN

Dernière Modification: Dimanche 06/08/2017 à 21 H 41 MN
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "jeu.h"
#include "editeur.h"

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *menu = NULL;
    SDL_Rect positionMenu;
    SDL_Event event;

    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("caisse.jpg"), NULL); //L'incône doit être chargé avant SDL_SetVideoMode()

    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    SDL_WM_SetCaption("Mario Sokoban by Bachir", NULL);

    menu = IMG_Load("menu_accueil.jpg");
    positionMenu.x = 0;
    positionMenu.y = 0;

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:{
                continuer = 0;
            break;}

            case SDL_KEYDOWN:{
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:{ //Veut arreter le jeu
                        continuer = 0;
                    break;}

                    case SDLK_KP1:{ // Demande à jouer
                        jouer(ecran);
                    break;}

                    case SDLK_KP2:{ //Demande à editer le niveau
                        editeur(ecran);
                    break;}
                }
            break;}
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(menu);
    SDL_Quit();

    return EXIT_SUCCESS;
}
