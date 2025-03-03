//                  ,----..           ,--.     ,----..                                         ,--.
//   .--.--.       /   /   \      ,--/  /|    /   /   \       ,---,.     ,---,               ,--.'|
//  /  /    '.    /   .     :  ,---,': / '   /   .     :    ,'  .'  \   '  .' \          ,--,:  : |
// |  :  /`. /   .   /   ;.  \ :   : '/ /   .   /   ;.  \ ,---.' .' |  /  ;    '.     ,`--.'`|  ' :
// ;  |  |--`   .   ;   /  ` ; |   '   ,   .   ;   /  ` ; |   |  |: | :  :       \    |   :  :  | |
// |  :  ;_     ;   |  ; \ ; | '   |  /    ;   |  ; \ ; | :   :  :  / :  |   /\   \   :   |   \ | :
//  \  \    `.  |   :  | ; | ' |   ;  ;    |   :  | ; | ' :   |    ;  |  :  ' ;.   :  |   : '  '; |
//   `----.   \ .   |  ' ' ' : :   '   \   .   |  ' ' ' : |   :     \ |  |  ;/  \   \ '   ' ;.    ;
//   __ \  \  | '   ;  \; /  | |   |    '  '   ;  \; /  | |   |   . | '  :  | \  \ ,' |   | | \   |
//  /  /`--'  /  \   \  ',  /  '   : |.  \  \   \  ',  /  '   :  '; | |  |  '  '--'   '   : |  ; .'
// '--'.     /    ;   :    /   |   | '_\.'   ;   :    /   |   |  | ;  |  :  :         |   | '`--'
//   `--'---'      \   \ .'    '   : |        \   \ .'    |   :   /   |  | ,'         '   : |
//                  `---`      ;   |,'         `---`      |   | ,'    `--''           ;   |.'
//                             '---'      

#include <stdio.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "jeu.h"
#include "affichage.h"

int main(){

    //initialisation SDL
    if (0 != SDL_Init(SDL_INIT_TIMER |SDL_INIT_EVENTS|SDL_INIT_VIDEO|SDL_INIT_GAMECONTROLLER)){
        printf("Erreur d'init SDL");
        return EXIT_FAILURE;    
    }

    //initialisation de la fenetre
    SDL_Window * window = SDL_CreateWindow("SOKOBAN - MOTA - TRECHOT",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,LARGEUR,HAUTEUR,SDL_WINDOW_SHOWN);
    if(window == NULL){
        printf("Erreur de création de la window");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }
    //initialisation du renderer
    SDL_Renderer * renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(window == NULL){
        printf("Erreur de création du renderer");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }
 
    // Boucle principale
    int currentLevel = 1;
    int running = 1;
    int choix = 3; // 0 Quit | 2 play | 3 accueil | 4 selectLevel
   

    while(running){
        if(choix == 0){
            running = 0;
        }else if(choix == 2){
            choix = playGameSDL(renderer, &currentLevel);
            SDL_RenderClear(renderer);
        }else if(choix == 3){ 
            choix = acueille(renderer);
            SDL_RenderClear(renderer);
        }else if(choix == 4){ 
            choix = selectLevel(renderer,&currentLevel);
            SDL_RenderClear(renderer);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
     
}
    
