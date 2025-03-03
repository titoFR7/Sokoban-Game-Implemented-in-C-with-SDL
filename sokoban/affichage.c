#include "affichage.h"
#include "jeu.h"
#include <stdio.h>
#include <SDL2/SDL.h>

//acceuil SDL
int acueille(SDL_Renderer * renderer){

    // Création des surfaces     
    SDL_Surface* sol = SDL_LoadBMP("textures/tex_all_light.bmp");
    SDL_Surface* playButton = SDL_LoadBMP("textures/play.bmp");
    SDL_Surface* quitButton = SDL_LoadBMP("textures/quitter.bmp");
    SDL_Surface* logoSurf = SDL_LoadBMP("textures/logo.bmp");

    //création des textures
    SDL_Texture* playButtonTex = SDL_CreateTextureFromSurface(renderer, playButton);
    SDL_Texture* solTex = SDL_CreateTextureFromSurface(renderer, sol);
    SDL_Texture* quitButtonTex = SDL_CreateTextureFromSurface(renderer, quitButton);
    SDL_Texture* logo = SDL_CreateTextureFromSurface(renderer, logoSurf);
    //effacement des surface (deja dans texture)
    SDL_FreeSurface(sol);
    SDL_FreeSurface(playButton);
    SDL_FreeSurface(quitButton);
    SDL_FreeSurface(logoSurf);

    //remplir le fond de la fenetre
    for(int x = 0; x < HAUTEUR / PIXEL; x++){
        for(int y = 0; y < LARGEUR / PIXEL; y++){
            SDL_Rect dest = {y * PIXEL, x * PIXEL, PIXEL, PIXEL};
            SDL_RenderCopy(renderer, solTex, NULL, &dest);
        }
    }

    //placer les boutons
    SDL_Rect destButtonPlay = {560,550,168,88};
    SDL_RenderCopy(renderer, playButtonTex, NULL, &destButtonPlay);

    SDL_Rect destLogo = {340,218,600,300};
    SDL_RenderCopy(renderer, logo, NULL, &destLogo);

    SDL_Rect destButtonQuit = {20,20,168,88};
    SDL_RenderCopy(renderer, quitButtonTex, NULL, &destButtonQuit);

    //mettre a jour
    SDL_RenderPresent(renderer);


    //boucle principal 
    SDL_Event event;
    int choix = -1;
    while(choix == -1){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                    choix = 0;
            }else if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    choix = 0;
                }
            }else if(event.type == SDL_MOUSEBUTTONDOWN){
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonPlay)){                
                    choix = 4;

                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonQuit)){
                    choix = 0;
                }
            }
        }
    }

   
    //libération des textures
    SDL_DestroyTexture(solTex);
    SDL_DestroyTexture(playButtonTex);
    SDL_DestroyTexture(quitButtonTex);
    SDL_DestroyTexture(logo);
    return choix;
   
}

//fonction pour selectionner le niveau
int selectLevel(SDL_Renderer * renderer,int * currentLevel){
    
    SDL_Surface * fondSurf = SDL_LoadBMP("textures/tex_all_light.bmp");
    SDL_Texture * fond = SDL_CreateTextureFromSurface(renderer,fondSurf);

    SDL_FreeSurface(fondSurf);

    for(int x = 0; x < HAUTEUR / PIXEL; x++){
        for(int y = 0; y < LARGEUR / PIXEL; y++){
            SDL_Rect dest = {y * PIXEL, x * PIXEL, PIXEL, PIXEL};
            SDL_RenderCopy(renderer, fond, NULL, &dest);
        }
    }

    SDL_Surface * level1Surf = SDL_LoadBMP("textures/levels/level1.bmp");
    SDL_Surface * level2Surf = SDL_LoadBMP("textures/levels/level2.bmp");
    SDL_Surface * level3Surf = SDL_LoadBMP("textures/levels/level3.bmp");
    SDL_Surface * level4Surf = SDL_LoadBMP("textures/levels/level4.bmp");
    SDL_Surface * level5Surf = SDL_LoadBMP("textures/levels/level5.bmp");
    SDL_Surface * level6Surf = SDL_LoadBMP("textures/levels/level6.bmp");
    SDL_Surface * level7Surf = SDL_LoadBMP("textures/levels/level7.bmp");
    SDL_Surface * level8Surf = SDL_LoadBMP("textures/levels/level8.bmp");
    SDL_Surface * level9Surf = SDL_LoadBMP("textures/levels/level9.bmp");
    SDL_Surface * level10Surf = SDL_LoadBMP("textures/levels/level10.bmp");
    SDL_Surface * level11Surf = SDL_LoadBMP("textures/levels/level11.bmp");
    SDL_Surface * level12Surf = SDL_LoadBMP("textures/levels/level12.bmp");
    SDL_Surface * level13Surf = SDL_LoadBMP("textures/levels/level13.bmp");
    SDL_Surface * level14Surf = SDL_LoadBMP("textures/levels/level14.bmp");
    SDL_Surface * level15Surf = SDL_LoadBMP("textures/levels/level15.bmp");
    SDL_Surface * level16Surf = SDL_LoadBMP("textures/levels/level16.bmp");
    SDL_Surface * level17Surf = SDL_LoadBMP("textures/levels/level17.bmp");
    SDL_Surface * level18Surf = SDL_LoadBMP("textures/levels/level18.bmp");
    SDL_Surface * level19Surf = SDL_LoadBMP("textures/levels/level19.bmp");
    SDL_Surface * level20Surf = SDL_LoadBMP("textures/levels/level20.bmp");
    SDL_Surface * backSurf = SDL_LoadBMP("textures/back-fleche.bmp");

    SDL_Texture * level1 = SDL_CreateTextureFromSurface(renderer,level1Surf);
    SDL_Texture * level2 = SDL_CreateTextureFromSurface(renderer,level2Surf);
    SDL_Texture * level3 = SDL_CreateTextureFromSurface(renderer,level3Surf);
    SDL_Texture * level4 = SDL_CreateTextureFromSurface(renderer,level4Surf);
    SDL_Texture * level5 = SDL_CreateTextureFromSurface(renderer,level5Surf);
    SDL_Texture * level6 = SDL_CreateTextureFromSurface(renderer,level6Surf);
    SDL_Texture * level7 = SDL_CreateTextureFromSurface(renderer,level7Surf);
    SDL_Texture * level8 = SDL_CreateTextureFromSurface(renderer,level8Surf);
    SDL_Texture * level9 = SDL_CreateTextureFromSurface(renderer,level9Surf);
    SDL_Texture * level10 = SDL_CreateTextureFromSurface(renderer,level10Surf);
    SDL_Texture * level11 = SDL_CreateTextureFromSurface(renderer,level11Surf);
    SDL_Texture * level12 = SDL_CreateTextureFromSurface(renderer,level12Surf);
    SDL_Texture * level13 = SDL_CreateTextureFromSurface(renderer,level13Surf);
    SDL_Texture * level14 = SDL_CreateTextureFromSurface(renderer,level14Surf);
    SDL_Texture * level15 = SDL_CreateTextureFromSurface(renderer,level15Surf);
    SDL_Texture * level16 = SDL_CreateTextureFromSurface(renderer,level16Surf);
    SDL_Texture * level17 = SDL_CreateTextureFromSurface(renderer,level17Surf);
    SDL_Texture * level18 = SDL_CreateTextureFromSurface(renderer,level18Surf);
    SDL_Texture * level19 = SDL_CreateTextureFromSurface(renderer,level19Surf);
    SDL_Texture * level20 = SDL_CreateTextureFromSurface(renderer,level20Surf);
    SDL_Texture * back = SDL_CreateTextureFromSurface(renderer,backSurf);

    SDL_FreeSurface(level1Surf);
    SDL_FreeSurface(level2Surf);
    SDL_FreeSurface(level3Surf);
    SDL_FreeSurface(level4Surf);
    SDL_FreeSurface(level5Surf);
    SDL_FreeSurface(level6Surf);
    SDL_FreeSurface(level7Surf);
    SDL_FreeSurface(level8Surf);
    SDL_FreeSurface(level9Surf);
    SDL_FreeSurface(level10Surf);
    SDL_FreeSurface(level11Surf);
    SDL_FreeSurface(level12Surf);
    SDL_FreeSurface(level13Surf);
    SDL_FreeSurface(level14Surf);
    SDL_FreeSurface(level15Surf);
    SDL_FreeSurface(level16Surf);
    SDL_FreeSurface(level17Surf);
    SDL_FreeSurface(level18Surf);
    SDL_FreeSurface(level19Surf);
    SDL_FreeSurface(level20Surf);
    SDL_FreeSurface(backSurf);

    //veriable pour positionner les boutons plus facilement
    int distanceBord = 180;
    int espace = 205;
    int espaceHaut = 80;

    //ligne 1

    SDL_Rect destButtonLevel1 = {distanceBord,espaceHaut,96,96};
    SDL_RenderCopy(renderer, level1, NULL, &destButtonLevel1);

    SDL_Rect destButtonLevel2 = {distanceBord+espace,espaceHaut,96,96};
    SDL_RenderCopy(renderer, level2, NULL, &destButtonLevel2);

    SDL_Rect destButtonLevel3 = {distanceBord+ 2*espace,espaceHaut,96,96};
    SDL_RenderCopy(renderer, level3, NULL, &destButtonLevel3);

    SDL_Rect destButtonLevel4 = {distanceBord+ 3*espace,espaceHaut,96,96};
    SDL_RenderCopy(renderer, level4, NULL, &destButtonLevel4);

    SDL_Rect destButtonLevel5 = {distanceBord+ 4*espace,espaceHaut,96,96};
    SDL_RenderCopy(renderer, level5, NULL, &destButtonLevel5);

    //ligne 2

    SDL_Rect destButtonLevel6 = {distanceBord,3*espaceHaut,96,96};
    SDL_RenderCopy(renderer, level6, NULL, &destButtonLevel6);

    SDL_Rect destButtonLevel7 = {distanceBord+espace,3*espaceHaut,96,96};
    SDL_RenderCopy(renderer, level7, NULL, &destButtonLevel7);

    SDL_Rect destButtonLevel8 = {distanceBord+ 2*espace,3*espaceHaut,96,96};
    SDL_RenderCopy(renderer, level8, NULL, &destButtonLevel8);

    SDL_Rect destButtonLevel9 = {distanceBord+ 3*espace,3*espaceHaut,96,96};
    SDL_RenderCopy(renderer, level9, NULL, &destButtonLevel9);

    SDL_Rect destButtonLevel10 = {distanceBord+ 4*espace,3*espaceHaut,96,96};
    SDL_RenderCopy(renderer, level10, NULL, &destButtonLevel10);

    //ligne 3

    SDL_Rect destButtonLevel11 = {distanceBord,5*espaceHaut,96,96};
    SDL_RenderCopy(renderer, level11, NULL, &destButtonLevel11);

    SDL_Rect destButtonLevel12 = {distanceBord+espace,5*espaceHaut,96,96};
    SDL_RenderCopy(renderer, level12, NULL, &destButtonLevel12);

    SDL_Rect destButtonLevel13 = {distanceBord+ 2*espace,5*espaceHaut,96,96};
    SDL_RenderCopy(renderer, level13, NULL, &destButtonLevel13);

    SDL_Rect destButtonLevel14 = {distanceBord+ 3*espace,5*espaceHaut,96,96};
    SDL_RenderCopy(renderer, level14, NULL, &destButtonLevel14);

    SDL_Rect destButtonLevel15 = {distanceBord+ 4*espace,5*espaceHaut,96,96};
    SDL_RenderCopy(renderer, level15, NULL, &destButtonLevel15);

    //ligne 4

    SDL_Rect destButtonLevel16 = {distanceBord,7*espaceHaut,96,96};
    SDL_RenderCopy(renderer, level16, NULL, &destButtonLevel16);

    SDL_Rect destButtonLevel17 = {distanceBord+espace,7*espaceHaut,96,96};
    SDL_RenderCopy(renderer, level17, NULL, &destButtonLevel17);

    SDL_Rect destButtonLevel18 = {distanceBord+ 2*espace,7*espaceHaut,96,96};
    SDL_RenderCopy(renderer, level18, NULL, &destButtonLevel18);

    SDL_Rect destButtonLevel19 = {distanceBord+ 3*espace,7*espaceHaut,96,96};
    SDL_RenderCopy(renderer, level19, NULL, &destButtonLevel19);

    SDL_Rect destButtonLevel20 = {distanceBord+ 4*espace,7*espaceHaut,96,96};
    SDL_RenderCopy(renderer, level20, NULL, &destButtonLevel20);

    SDL_Rect destButtonBack = {50,50,50,50};
    SDL_RenderCopy(renderer, back, NULL, &destButtonBack);

    //mettre a jour
    SDL_RenderPresent(renderer);

    //boucle principal 
    SDL_Event event;
    int choix = -1;
    while(choix == -1){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                    choix = 3;
            }else if(event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    choix = 3;
                }
            }else if(event.type == SDL_MOUSEBUTTONDOWN){
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonLevel1)){
                    *currentLevel = 1;                
                    choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonLevel2)){
                    *currentLevel = 2; 
                    choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonLevel3)){
                    *currentLevel = 3; 
                    choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonLevel4)){
                    *currentLevel = 4; 
                    choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonLevel5)){
                    *currentLevel = 5; 
                    choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonLevel6)){
                    *currentLevel = 6; 
                    choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonLevel7)){
                    *currentLevel = 7; 
                    choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonLevel8)){
                    *currentLevel = 8; 
                    choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonLevel9)){
                    *currentLevel = 9; 
                    choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonLevel10)){
                    *currentLevel = 10; 
                    choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonLevel11)){
                    *currentLevel = 11; 
                    choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonLevel12)){
                    *currentLevel = 12; 
                    choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonLevel13)){
                    *currentLevel = 13; 
                    choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonLevel14)){
                    *currentLevel = 14; 
                    choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonLevel15)){
                    *currentLevel = 15; 
                    choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonLevel16)){
                    *currentLevel = 16; 
                    choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonLevel17)){
                    *currentLevel = 17; 
                    choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonLevel18)){
                    *currentLevel = 18; 
                    choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonLevel19)){
                    *currentLevel = 19; 
                    choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonLevel20)){
                    *currentLevel = 20; 
                    choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonBack)){
                    choix = 3;
                }
            }
        }
    }

    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(level1);
    SDL_DestroyTexture(level2);
    SDL_DestroyTexture(level3);
    SDL_DestroyTexture(level4);
    SDL_DestroyTexture(level5);
    SDL_DestroyTexture(level6);
    SDL_DestroyTexture(level7);
    SDL_DestroyTexture(level8);
    SDL_DestroyTexture(level9);
    SDL_DestroyTexture(level10);
    SDL_DestroyTexture(level11);
    SDL_DestroyTexture(level12);
    SDL_DestroyTexture(level13);
    SDL_DestroyTexture(level14);
    SDL_DestroyTexture(level15);
    SDL_DestroyTexture(level16);
    SDL_DestroyTexture(level17);
    SDL_DestroyTexture(level18);
    SDL_DestroyTexture(level19);
    SDL_DestroyTexture(level20);

    return choix;

}


//fonction affichage de la defaite 
int playerLooseSDL(SDL_Renderer * renderer,int * currentLevel,int nbDep,unsigned int temps){

    //chargement des surfaces
    SDL_Surface* backgroundSurf = SDL_LoadBMP("textures/tex_all_dark.bmp");
    SDL_Surface* looseSurf = SDL_LoadBMP("textures/defaite.bmp");
    SDL_Surface* homeSurf = SDL_LoadBMP("textures/home.bmp");
    SDL_Surface* replaySurf = SDL_LoadBMP("textures/back.bmp");
    
    //chargement des textures
    SDL_Texture* background = SDL_CreateTextureFromSurface(renderer,backgroundSurf);
    SDL_Texture* loose = SDL_CreateTextureFromSurface(renderer,looseSurf);
    SDL_Texture* home = SDL_CreateTextureFromSurface(renderer,homeSurf);
    SDL_Texture* replay = SDL_CreateTextureFromSurface(renderer,replaySurf);

    //libération des surfaces
    SDL_FreeSurface(homeSurf);
    SDL_FreeSurface(replaySurf);
    SDL_FreeSurface(backgroundSurf);
    SDL_FreeSurface(looseSurf);

    //remplir le fond de la fenetre
    for(int x = 0; x < HAUTEUR / PIXEL; x++){
    for(int y = 0; y < LARGEUR / PIXEL; y++){
        SDL_Rect dest = {y * PIXEL, x * PIXEL, PIXEL, PIXEL};
        SDL_RenderCopy(renderer, background, NULL, &dest);
        }
    }

    //calcul du score
    int score = temps-nbDep;

    //affichage du score
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("textures/minecraft.ttf", 24);
    SDL_Color color = {255, 255, 255, 255};
    char scoreStr[15]; 
    sprintf(scoreStr, "%d", score);
    SDL_Surface *surface = TTF_RenderText_Solid(font, scoreStr, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect dstrect = {590, 335, 100, 50}; 
    
  
    //affichage des textures/boutons
    SDL_Rect destLoose = {340,168,600,400};
    SDL_RenderCopy(renderer, loose, NULL, &destLoose);
    SDL_Rect destHome = {687,440,60,60};
    SDL_RenderCopy(renderer, home, NULL, &destHome);
    SDL_Rect destReplay = {536,440,60,60};
    SDL_RenderCopy(renderer, replay, NULL, &destReplay);
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    SDL_RenderPresent(renderer);
    //0 Quit | 2 play | 3 acueille
    //boucle principal 
    SDL_Event event;
    int choix = -2;
    while(choix == -2){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                choix = 0;
            }else if(event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    choix = 4;
                }
            }else if(event.type == SDL_MOUSEBUTTONDOWN){
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destHome)){                
                    *currentLevel = 1;
                    choix = 4;
                }else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destReplay)){
                   choix = 2;
                } 
                
            }
        }
    }

    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(loose);
    SDL_DestroyTexture(home);
    SDL_DestroyTexture(replay);
    
    return choix;
}

//affiche la victoire
int playerWin(SDL_Renderer * renderer,int * currentLevel,int nbDep,unsigned int temps){

    //chargement des surfaces
    SDL_Surface* backgroundSurf = SDL_LoadBMP("textures/tex_all_dark.bmp");
    SDL_Surface* victorySurf = SDL_LoadBMP("textures/victory.bmp");
    SDL_Surface* homeSurf = SDL_LoadBMP("textures/home.bmp");
    SDL_Surface* nextSurf = SDL_LoadBMP("textures/next.bmp");
    SDL_Surface* replaySurf = SDL_LoadBMP("textures/back.bmp");

    //chargement des textures
    SDL_Texture* background = SDL_CreateTextureFromSurface(renderer,backgroundSurf);
    SDL_Texture* victory = SDL_CreateTextureFromSurface(renderer,victorySurf);
    SDL_Texture* home = SDL_CreateTextureFromSurface(renderer,homeSurf);
    SDL_Texture* next = SDL_CreateTextureFromSurface(renderer,nextSurf);
    SDL_Texture* replay = SDL_CreateTextureFromSurface(renderer,replaySurf);

    SDL_FreeSurface(homeSurf);
    SDL_FreeSurface(nextSurf);
    SDL_FreeSurface(replaySurf);
    SDL_FreeSurface(backgroundSurf);
    SDL_FreeSurface(victorySurf);


    for(int x = 0; x < HAUTEUR / PIXEL; x++){
    for(int y = 0; y < LARGEUR / PIXEL; y++){
        SDL_Rect dest = {y * PIXEL, x * PIXEL, PIXEL, PIXEL};
        SDL_RenderCopy(renderer, background, NULL, &dest);
        }
    }

    int score = temps/nbDep;

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("textures/minecraft.ttf", 24);
    SDL_Color color = {255, 255, 255, 255};
    char scoreStr[15]; 
    sprintf(scoreStr, "%d", score);
    
    SDL_Surface *surface = TTF_RenderText_Solid(font, scoreStr, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect dstrect = {590, 335, 100, 50}; 
    
    SDL_Rect destVictory = {340,168,600,400};
    SDL_RenderCopy(renderer, victory, NULL, &destVictory);
    SDL_Rect destHome = {611,440,60,60};
    SDL_RenderCopy(renderer, home, NULL, &destHome);
    SDL_Rect destReplay = {456,440,60,60};
    SDL_RenderCopy(renderer, replay, NULL, &destReplay);
    SDL_Rect destNext = {777,440,60,60};
    SDL_RenderCopy(renderer, next, NULL, &destNext);
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_RenderPresent(renderer);

    //0 Quit | 2 play | 4 select level
    //boucle principal 
    SDL_Event event;
    int choix = -2;
    while(choix == -2){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                    choix = 4;
            }else if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    choix = 4;
                }
            }else if(event.type == SDL_MOUSEBUTTONDOWN){
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destHome)){                
                    *currentLevel = 1;
                    choix = 4;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destReplay)){
                   choix = 2;
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destNext)){
                  *currentLevel +=1;
                   choix = 2;
                }
            }
        }
    }
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(victory);
    SDL_DestroyTexture(home);
    SDL_DestroyTexture(next);
    SDL_DestroyTexture(replay);
    
    return choix;
}

//detection de la defaite
int playerLoose(Map * map){
    int choix1 = 0;
    // Si toutes les caisses sont bien placées, pas de défaite
    if(nombreCaisseGood(map) == map->nbCaisses){
        return 0;
    }
    // Vérification des caisses bloquées
    for(int i = 0; i < map->lignes; i++){
        for(int j = 0; j < map->colonnes; j++){
            if(map->map[i][j] == 'C'){
                // Vérification si la caisse est sur une position gagnante
                int flag = 0;
                for(int k = 0; k < map->nbCaisses; k++){
                    Coord current = map->WinCaissePos[k];
                    if(current.x == i && current.y == j){
                        flag = 1;
                        break;
                    }
                }
                // Si la caisse n'est pas sur une position gagnante
                if(flag == 0){
                    // Vérification des murs autour de la caisse
                    if(i+1 < map->lignes && j+1 < map->colonnes && 
                        i-1 >= 0 && j-1 >= 0){  // Vérification des limites
                        
                        // Vérification des coins bloqués
                        if((map->map[i+1][j] == '#' && map->map[i][j+1] == '#') ||
                            (map->map[i-1][j] == '#' && map->map[i][j-1] == '#') ||
                            (map->map[i+1][j] == '#' && map->map[i][j-1] == '#') ||
                            (map->map[i-1][j] == '#' && map->map[i][j+1] == '#'))
                        {
                            choix1 = 1;
                            break;  // On peut sortir dès qu'on trouve une caisse bloquée
                        }
                    }
                }
            }
        }
        if(choix1 == 1)break;  // Sort de la boucle externe si une caisse est bloquée
    }
    return choix1;
}