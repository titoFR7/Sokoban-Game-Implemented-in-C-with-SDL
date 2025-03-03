#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "affichage.h"

//Structure pour gérer des coordonées

typedef struct Coord{
    int x;
    int y;    
}Coord;

//structure pour gérer la map
typedef struct structMap{
    char ** map; //matrice
    int colonnes; 
    int lignes;
    Coord * player;
    Coord * WinCaissePos; // liste de struct Coord
    int nbCaisses;
}Map;

//Crée la map a partir d'un fichier .txt
Map * initMap(int niveau);

//Affiche la map dans la console
void afficheMap(char **map, int lignes, int colonnes);
void libereEspaceDeLaMap(Map *m);

//Déplacement
int deplaceJoueur(int direction,Map * map);

//Vérifie si un déplaement est valide
int deplacementValide(Coord * coord,Map * map);

//condition de victoire + gestion de I 
int nombreCaisseGood(Map * map);

//Regarde si le player n'est pas dans une configuration perdante
int playerLoose(Map * map);

//lancer partie 
int playGameSDL(SDL_Renderer * renderer,int * currentLevel);

//lance la résolution
int playGameSDLSolution(SDL_Renderer * renderer,int * currentLevel);




