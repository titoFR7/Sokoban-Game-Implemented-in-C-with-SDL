#include <SDL2/SDL.h>

//taille de la fenetre
#define HAUTEUR 736
#define LARGEUR 1280
#define PIXEL 32


//Acueille SDL
int acueille(SDL_Renderer * renderer);
//Selection level SDL
int selectLevel(SDL_Renderer * renderer,int * currentLevel);
//afffichage loose
int playerLooseSDL(SDL_Renderer * renderer,int * currentLevel,int nbDep,unsigned int temps);
//affichage Win
int playerWin(SDL_Renderer * renderer,int * currentLevel,int nbDep,unsigned int temps);


