/*
constantes.h
-------------------

Par Mohameth El Bachir NDIAYE

Rôle, définit les constantes pour tout le programme (taille fenetre,...)

Création: Samedi 05/08/2017 à 23 H 26 MN

Dernière Modification: Samedi 05/08/2017 à 23 H 28 MN
*/

#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

	#define TAILLE_BLOC 			34
	#define NOMBRE_BLOCS_LARGEUR 	12
	#define NOMBRE_BLOCS_HAUTEUR 	12
	#define	LARGEUR_FENETRE 		NOMBRE_BLOCS_LARGEUR * TAILLE_BLOC
	#define HAUTEUR_FENETRE 		NOMBRE_BLOCS_HAUTEUR * TAILLE_BLOC

	enum {HAUT, BAS, GAUCHE, DROITE};
	enum {VIDE, MUR, CAISSE, OBJECTIF, MARIO, CAISSE_OK};

#endif
