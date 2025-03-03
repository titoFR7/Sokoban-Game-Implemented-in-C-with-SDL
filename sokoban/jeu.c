#include "jeu.h"
#include "affichage.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

//Libère l'espace de la map.
void libereEspaceDeLaMap(Map *m){
    if(m == NULL || m->map == NULL){
        return;
    }
    for(int i = 0; i < m->lignes; i++){
        if(m->map[i] != NULL){
            free(m->map[i]);
        }
    }
    free(m->WinCaissePos);
    free(m->map);
    free(m->player);
    free(m);  
}

// Crée le tableau pour stocker la map.
char ** creeMap(int lignes, int colonnes){
    char ** map = malloc(lignes*sizeof(char*));
    int i;
    for(i = 0 ; i < lignes ; i++){
    map[i] = malloc(colonnes*sizeof(char));
    }
    return map;
}

//Initialise la map en fonction du niveau choisi
Map * initMap(int niveau){

    // Transforme parametre niveau (int) en char (mapX.txt) pour choisir le fichier correspondant au niveau
    char nomMap[20];
    sprintf(nomMap, "maps/map%d.txt", niveau);
    
    //Ouvre le fichier contenant le niveau
    FILE * fd = fopen(nomMap,"r");
    if(fd == NULL){
        perror("Erreur ouverture");
    }

    //Compte les lignes et colonnes du fichier pour définir la taille de la matrice, puis détermine le nombre de caisses
    char current = '\0';
    int lignes = 1,colonnes = 0,MaxColonnes = 0,nbCaisse = 0;
    while((current = fgetc(fd)) != EOF){
        if(current == 'I'){
            nbCaisse +=1;
        }
        if(current == '\n'){
            lignes +=1;
            if(colonnes > MaxColonnes){
                MaxColonnes = colonnes;
                colonnes = 0;
            }else{
                colonnes = 0;
            }
        }
        if(current != '\n'){
         colonnes +=1;   
        }    
    }
    //on revient au debut du fichier
    fseek(fd,0,SEEK_SET);
   
    //Crée le tableau (map)
    char ** tab = creeMap(lignes,MaxColonnes);

    //tableau avec les position ou doivent etre les caisse
    Coord * tabCoord = malloc(nbCaisse*sizeof(Coord));
    Coord * coordJoueur = malloc(sizeof(Coord));

    //Copie la map (depuis le fichier txt) dans la matrice. Il ne faut pas revenir à la ligne avant d'avoir atteint la largeur de la map (MaxColonnes)
    int i = 0, j = 0,count = 0;
    while((current = fgetc(fd)) != EOF){
        if(current == '\n'){
            continue; 
        }
        if(current == 'P'){
            coordJoueur->x = i;
            coordJoueur->y = j; 
        }
        if(current == 'I'){
            tabCoord[count].x = i;
            tabCoord[count].y = j;
            count +=1; 
        }
        tab[i][j] = current;
        j++;
        if(j >= MaxColonnes){
            i++;
            j = 0; 
        }
        if(i >= lignes){
            break;
        }
    } 

    //reglage d'un bug isolé
    if(niveau == 19 || niveau == 20){
        lignes -=1;
    }

    //Crée la structure Map et l'initialise
    Map * newMap = malloc(sizeof(Map));
    newMap->map = tab;
    newMap->colonnes = MaxColonnes;
    newMap->lignes = lignes;
    newMap->player = coordJoueur;
    
    newMap->WinCaissePos = tabCoord;
    newMap->nbCaisses = nbCaisse;

    fclose(fd);  
    return newMap;
}

//Verifie si le joueur souhaite faire un déplacement valide (vide = 1, caisse = 2, mur = 0) 
int deplacementValide(Coord * coord,Map * map){

    char next_pose = map->map[coord->x][coord->y];

    if(next_pose == ' ' || next_pose == 'I'){
        return 1;                
    }else if(next_pose == '#'){
        return 0;             
    }else if(next_pose == 'C'){
        return 2;             
    }
    return 3;    
}

//Deplace le joueur en fonction de la direction choisie
int deplaceJoueur(int direction,Map * map){

    //Reherche la positon future 
    Coord * next_coord = malloc(sizeof(Coord));
    Coord * current_coord = malloc(sizeof(Coord));
    current_coord->x = map->player->x;
    current_coord->y = map->player->y;
    Coord * next_coord_caisse = malloc(sizeof(Coord)); //Cas où le joueur pousse une caisse.
    int choix=0;

    //q = 2 || d = 3 || s = 1 || z = 0

    //calcul futures coordonnées en fonction de la direction
    if(direction == 0){            //y
        next_coord->x = (map->player->x -1);
        next_coord->y = (map->player->y);
        next_coord_caisse->x = (map->player->x -2);
        next_coord_caisse->y = (map->player->y);
   }else if(direction == 1){         //-y
        next_coord->x = (map->player->x +1);
        next_coord->y = (map->player->y);
        next_coord_caisse->x = (map->player->x +2);
        next_coord_caisse->y = (map->player->y);
   }else if(direction == 2){        //-x
        next_coord->x = (map->player->x);
        next_coord->y = (map->player->y-1);
        next_coord_caisse->x = (map->player->x);
        next_coord_caisse->y = (map->player->y-2);
   }else if(direction == 3){           //x
        next_coord->x = (map->player->x);
        next_coord->y = (map->player->y+1);
        next_coord_caisse->x = (map->player->x);
        next_coord_caisse->y = (map->player->y+2);
   }

    // On vérifie dans quelle situation nous sommes (déplacement autorisé ou non)
    int situation = deplacementValide(next_coord,map);
    
    //on applique les changements si le déplacement est valide
    if(situation == 1){
        map->map[current_coord->x][current_coord->y] = ' ';
        map->map[next_coord->x][next_coord->y] = 'P';
        map->player->x = next_coord->x;
        map->player->y = next_coord->y;     
        choix = 1;
    }else if(situation == 0){
        choix = 0;

    }else if(situation == 2){
        //On vérifie si la caisse peut être déplacée (si la case suivante est vide)
        if(deplacementValide(next_coord_caisse,map) == 1){
        map->map[current_coord->x][current_coord->y] = ' ';
        map->map[next_coord->x][next_coord->y] = 'P';
        map->map[next_coord_caisse->x][next_coord_caisse->y] = 'C';
        map->player->x = next_coord->x;
        map->player->y = next_coord->y;
        if(playerLoose(map) == 1){
            choix = 2;
        }else if(nombreCaisseGood(map) == map->nbCaisses){
            choix = 3;             
        }else{
            choix = 1; 
          }
        }
    }
    free(current_coord);
    free(next_coord);
    free(next_coord_caisse);
    return choix;
}

//Calcul le nombre de caisses bien placées avec les donnees de la map
int nombreCaisseGood(Map * map){
    Coord current;
    int nbcaisseGOOD = 0;
    for(int i = 0;i<(map->nbCaisses);i++){
        current = map->WinCaissePos[i];
        if(map->map[current.x][current.y] == ' '){
            map->map[current.x][current.y] = 'I';
        }
        if(map->map[current.x][current.y] == 'C'){
            nbcaisseGOOD +=1;
        }
    }
    return nbcaisseGOOD;  
}

//Lance le jeuc avec SDL et renvoie le choix de l'utilisateur (0 Quit | 2 play | 3 acueille | 4 selectLevel)
int playGameSDL(SDL_Renderer * renderer,int * currentLevel){
    
    //initialisation des variables
    int choix = 4;
    int nbDep = 0;
    int continuer = 1;
    int currentNbDep = 0;
    int depTextureChoice = -1;
    unsigned int time = SDL_GetTicks();
    unsigned int tempsPasser = 0;
    char nbDepStr[20];
    char timeText[20];
    SDL_Event event;


    TTF_Init();
    TTF_Font *font = TTF_OpenFont("textures/minecraft.ttf", 24);
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *timeSurface = NULL;
    SDL_Texture *timeTexture = NULL;
    //position du texte (timer)
    SDL_Rect timeRect = {590, 20, 100, 50};
    //position nbdep
    SDL_Rect dstrect = {1200, 20, 50, 50}; 

    //initialisation des surfaces 
    SDL_Surface* mur = SDL_LoadBMP("textures/tex_all_dark.bmp");
    SDL_Surface* box = SDL_LoadBMP("textures/box.bmp");
    SDL_Surface* playerFace = SDL_LoadBMP("textures/player_face.bmp");
    SDL_Surface* playerBack = SDL_LoadBMP("textures/player_back.bmp");
    SDL_Surface* playerLeft = SDL_LoadBMP("textures/player_left.bmp");
    SDL_Surface* playerRight = SDL_LoadBMP("textures/player_right.bmp");
    SDL_Surface* goal = SDL_LoadBMP("textures/goal.bmp");
    SDL_Surface* sol = SDL_LoadBMP("textures/tex_all_light.bmp");
    SDL_Surface* backSurf = SDL_LoadBMP("textures/back-fleche.bmp");
    SDL_Surface* replaySurf = SDL_LoadBMP("textures/back.bmp");
    SDL_Surface* lampeSurf = SDL_LoadBMP("textures/lampe.bmp");
 
    //initialisation des textures
    SDL_Texture* back = SDL_CreateTextureFromSurface(renderer, backSurf);
    SDL_Texture* replay = SDL_CreateTextureFromSurface(renderer, replaySurf);
    SDL_Texture* lampe = SDL_CreateTextureFromSurface(renderer, lampeSurf);
    SDL_Texture* murTex = SDL_CreateTextureFromSurface(renderer, mur);
    SDL_Texture* boxTex = SDL_CreateTextureFromSurface(renderer, box);
    SDL_Texture* playerTexFace = SDL_CreateTextureFromSurface(renderer, playerFace);
    SDL_Texture* playerTexBack = SDL_CreateTextureFromSurface(renderer, playerBack);
    SDL_Texture* playerTexLeft = SDL_CreateTextureFromSurface(renderer, playerLeft);
    SDL_Texture* playerTexRight = SDL_CreateTextureFromSurface(renderer, playerRight);
    SDL_Texture* goalTex = SDL_CreateTextureFromSurface(renderer, goal);
    SDL_Texture* solTex = SDL_CreateTextureFromSurface(renderer, sol);

    //libération des surfaces
    SDL_FreeSurface(mur);
    SDL_FreeSurface(box);
    SDL_FreeSurface(playerFace);
    SDL_FreeSurface(goal);
    SDL_FreeSurface(sol);
    SDL_FreeSurface(playerBack);
    SDL_FreeSurface(playerLeft);
    SDL_FreeSurface(playerRight);
    SDL_FreeSurface(backSurf);
    SDL_FreeSurface(replaySurf);
    SDL_FreeSurface(lampeSurf);
   
    //Initialisation de la map et du joueur
    Map* map = initMap(*currentLevel);
    
    int mapLargeur = map->colonnes * PIXEL;
    int mapHauteur = map->lignes * PIXEL;
    int decalageX = (LARGEUR - mapLargeur) / 2;
    int decalageY = (HAUTEUR - mapHauteur) / 2;

    currentNbDep = nbDep;

    //initialisation des rectangles pour les boutons
    SDL_Rect destReplay = {100,20,50,50};
    SDL_Rect destBack = {20,20,50,50};
    SDL_Rect destLampe = {1220,670,50,50};

    //Recupere les touche appuyer par l'utilisateur
    int VarTemp;
    while(continuer == 1){   
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    continuer = -1;                    
                    break;
                case SDL_KEYDOWN:
                 //q = 2 || d = 3 || s = 1 || z = 0    
                    switch(event.key.keysym.sym){
                        case SDLK_UP:
                        case SDLK_z:
                            VarTemp = deplaceJoueur(0,map);
                            if(VarTemp == 1){
                                currentNbDep +=1;
                                depTextureChoice = 0;
                            }else if(VarTemp == 2){
                                continuer = 0;
                                choix = playerLooseSDL(renderer,currentLevel,currentNbDep,tempsPasser);
                            }else if(VarTemp == 3){
                                continuer = 0;
                                choix = playerWin(renderer,currentLevel,currentNbDep,tempsPasser); 
                            }
                            break;
                        case SDLK_LEFT:
                        case SDLK_q:
                            VarTemp = deplaceJoueur(2,map);
                            if(VarTemp == 1){
                                currentNbDep +=1;
                                depTextureChoice = 1;
                            }else if(VarTemp == 2){
                                continuer = 0;
                                choix = playerLooseSDL(renderer,currentLevel,currentNbDep,tempsPasser);
                            }else if(VarTemp == 3){
                                continuer = 0;
                                choix = playerWin(renderer,currentLevel,currentNbDep,tempsPasser); 
                            }
                            break;
                        case SDLK_RIGHT:
                        case SDLK_d:


                            VarTemp = deplaceJoueur(3,map);
                            if(VarTemp == 1){
                                currentNbDep +=1;
                                depTextureChoice = 2;
                            }else if(VarTemp == 2){
                                continuer = 0;
                                choix = playerLooseSDL(renderer,currentLevel,currentNbDep,tempsPasser);
                            }else if(VarTemp == 3){
                                continuer = 0;
                                choix = playerWin(renderer,currentLevel,currentNbDep,tempsPasser); 
                            }
                            break;
                        case SDLK_DOWN:
                        case SDLK_s:
                            VarTemp = deplaceJoueur(1,map);
                            if(VarTemp == 1){
                                currentNbDep +=1;
                                depTextureChoice = -1;
                            }else if(VarTemp == 2){
                                continuer = 0;
                                choix = playerLooseSDL(renderer,currentLevel,currentNbDep,tempsPasser);
                            }else if(VarTemp == 3){
                                continuer = 0;
                                choix = playerWin(renderer,currentLevel,currentNbDep,tempsPasser); 
                            }
                            break;
                        //Si le joueur appuie sur la touche échap alors on quitte la boucle et on affiche l'écran selectLevel et on réinitialise le niveau a 1
                        case SDLK_ESCAPE:
                            continuer = -1;  
                            choix = 4;
                            *currentLevel = 1;                   
                            break;
                    }       
                    break;
                    //Si le joueur clique sur un bouton alors on quitte la boucle et on affiche l'écran correspondant
                    case SDL_MOUSEBUTTONDOWN:{
                        int mouseX = event.button.x;
                        int mouseY = event.button.y;
                        if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destBack)){
                            *currentLevel = 1;
                            choix = 4;
                            continuer = 0;
                            break;
                        } else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destReplay)){
                            choix = 2;
                            continuer = 0;
                            break;
                        }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destLampe)){
                            playGameSDLSolution(renderer,currentLevel);
                            choix = 2;
                            continuer = 0;
                            break;
                    }
                break;
            }
        }
        }
       

        // Remplir tout l'écran avec la texture du sol
        for(int x = 0; x < HAUTEUR / PIXEL; x++){
            for(int y = 0; y < LARGEUR / PIXEL; y++){
                SDL_Rect dest = {y * PIXEL, x * PIXEL, PIXEL, PIXEL};
                SDL_RenderCopy(renderer, solTex, NULL, &dest);
            }
        }

        // Dessiner la map
        for(int x = 0; x < map->lignes; x++){
            for(int y = 0; y < map->colonnes; y++){
                //afficher la map au milieu de l'écran
                SDL_Rect dest = {decalageX + y * PIXEL, decalageY + x * PIXEL, PIXEL, PIXEL};
                SDL_RenderCopy(renderer, solTex, NULL, &dest);
                switch(map->map[x][y]){
                    case '#':
                        SDL_RenderCopy(renderer, murTex, NULL, &dest);
                        break;
                    case 'P':
                        //-1 spawn et bas | 0 haut | 1 gauche | 2 droite 
                        if(depTextureChoice == -1){
                          SDL_RenderCopy(renderer, playerTexFace, NULL, &dest);  
                        }else if(depTextureChoice == 0){
                            SDL_RenderCopy(renderer, playerTexBack, NULL, &dest); 
                        }else if(depTextureChoice == 1){
                            SDL_RenderCopy(renderer, playerTexLeft, NULL, &dest); 
                        }else if(depTextureChoice == 2){
                            SDL_RenderCopy(renderer, playerTexRight, NULL, &dest); 
                        }          
                        break;
                    case 'C':
                        SDL_RenderCopy(renderer, boxTex, NULL, &dest);
                        break;
                    case 'I':
                        SDL_RenderCopy(renderer,goalTex, NULL, &dest);
                        break;
                }
            }
        }

        //pour affichage des I 
        nombreCaisseGood(map);

        //snprintf pour eviter le dépassement
        snprintf(nbDepStr, sizeof(nbDepStr), "%d", currentNbDep); 
        SDL_Surface *surfaceDep = TTF_RenderText_Solid(font, nbDepStr, color);
        SDL_Texture *textureDep = SDL_CreateTextureFromSurface(renderer, surfaceDep);
        SDL_FreeSurface(surfaceDep);
        SDL_RenderCopy(renderer, textureDep, NULL, &dstrect);
        SDL_DestroyTexture(textureDep);

        //timer 
        tempsPasser = SDL_GetTicks() - time;
        int seconds = tempsPasser / 1000;
        int minutes = seconds / 60;
        seconds = seconds % 60;
    
        //affichage du temps
        snprintf(timeText, sizeof(timeText), "%02d:%02d", minutes, seconds);
        timeSurface = TTF_RenderText_Solid(font, timeText, color);
        timeTexture = SDL_CreateTextureFromSurface(renderer, timeSurface);

        //libération de la surface
        SDL_FreeSurface(timeSurface);

        //affiche le texte 
        SDL_RenderCopy(renderer, timeTexture, NULL, &timeRect);
        
        //Affichage des boutons
        SDL_RenderCopy(renderer, replay, NULL, &destReplay);
        SDL_RenderCopy(renderer, back, NULL, &destBack);
        SDL_RenderCopy(renderer, lampe, NULL, &destLampe);

        SDL_RenderPresent(renderer);
        //Rafraichissement de l'écran delay
        SDL_Delay(10);
        //effacer l'écran pour le mettre à jour
        
        SDL_RenderClear(renderer);
    }

    //libération de la mémoire a la fin du jeux
    SDL_DestroyTexture(timeTexture);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyTexture(murTex);
    SDL_DestroyTexture(solTex);
    SDL_DestroyTexture(playerTexFace);
    SDL_DestroyTexture(boxTex);
    SDL_DestroyTexture(playerTexBack);
    SDL_DestroyTexture(playerTexLeft);
    SDL_DestroyTexture(playerTexRight);
    SDL_DestroyTexture(back);
    SDL_DestroyTexture(replay);
    SDL_DestroyTexture(lampe);
    SDL_DestroyTexture(goalTex);

    libereEspaceDeLaMap(map);
   
    return choix;
}


//fonction qui sert a montrer la solution du niveau
int playGameSDLSolution(SDL_Renderer *renderer, int *currentLevel) {
    
    int continuer = 1;
    int depTextureChoice = -1;
    int delayCustom = 150;
    int pauseFlag = 1;
    char buffer = '\0';
    int flag = 0;
   
    //initialisation des surfaces + initialisation des textures
    SDL_Surface *mur = SDL_LoadBMP("textures/tex_all_dark.bmp");
    SDL_Surface *box = SDL_LoadBMP("textures/box.bmp");
    SDL_Surface *playerFace = SDL_LoadBMP("textures/player_face.bmp");
    SDL_Surface *playerBack = SDL_LoadBMP("textures/player_back.bmp");
    SDL_Surface *playerLeft = SDL_LoadBMP("textures/player_left.bmp");
    SDL_Surface *playerRight = SDL_LoadBMP("textures/player_right.bmp");
    SDL_Surface *goal = SDL_LoadBMP("textures/goal.bmp");
    SDL_Surface *sol = SDL_LoadBMP("textures/tex_all_light.bmp");
    SDL_Surface *backSurf = SDL_LoadBMP("textures/back-fleche.bmp");
    SDL_Surface *pauseSurf = SDL_LoadBMP("textures/pause.bmp");
    SDL_Surface *plusSurf = SDL_LoadBMP("textures/plus.bmp");
    SDL_Surface *moinsSurf = SDL_LoadBMP("textures/moins.bmp");

    SDL_Texture *pause = SDL_CreateTextureFromSurface(renderer, pauseSurf);
    SDL_Texture *plus = SDL_CreateTextureFromSurface(renderer, plusSurf);
    SDL_Texture *moins = SDL_CreateTextureFromSurface(renderer, moinsSurf);
    SDL_Texture *murTex = SDL_CreateTextureFromSurface(renderer, mur);
    SDL_Texture *boxTex = SDL_CreateTextureFromSurface(renderer, box);
    SDL_Texture *playerTexFace = SDL_CreateTextureFromSurface(renderer, playerFace);
    SDL_Texture *playerTexBack = SDL_CreateTextureFromSurface(renderer, playerBack);
    SDL_Texture *playerTexLeft = SDL_CreateTextureFromSurface(renderer, playerLeft);
    SDL_Texture *playerTexRight = SDL_CreateTextureFromSurface(renderer, playerRight);
    SDL_Texture *goalTex = SDL_CreateTextureFromSurface(renderer, goal);
    SDL_Texture *solTex = SDL_CreateTextureFromSurface(renderer, sol);
    SDL_Texture *back = SDL_CreateTextureFromSurface(renderer, backSurf);

    SDL_FreeSurface(mur);
    SDL_FreeSurface(box);
    SDL_FreeSurface(playerFace);
    SDL_FreeSurface(playerBack);
    SDL_FreeSurface(playerLeft);
    SDL_FreeSurface(playerRight);
    SDL_FreeSurface(goal);
    SDL_FreeSurface(sol);
    SDL_FreeSurface(backSurf);
    SDL_FreeSurface(pauseSurf);
    SDL_FreeSurface(plusSurf);
    SDL_FreeSurface(moinsSurf);

    //initialisation de la map et du joueur
    Map *map = initMap(*currentLevel);

    int mapLargeur = map->colonnes * PIXEL;
    int mapHauteur = map->lignes * PIXEL;
    int decalageX = (LARGEUR - mapLargeur) / 2;
    int decalageY = (HAUTEUR - mapHauteur) / 2;
  
    //Ouvre le fichier contenant les déplacements de la solution 
    FILE *fd = fopen("maps/solve.txt", "r");
    if(fd == NULL){
        perror("Erreur ouverture fichier");
        libereEspaceDeLaMap(map);
       
        return -1;
    }

    //parcourir le fichier pour trouver la solution du niveau actuel
   
    while((buffer = fgetc(fd)) != EOF){
        if(buffer == '0'){
            flag+=1;
        }
        if(flag == *currentLevel){

            break;
        }
    }

    //boucle principale
    while(continuer == 1){
        //condition de pause
        if(pauseFlag == 1){
        //affichage du fond de la map
        for(int x = 0; x < HAUTEUR / PIXEL; x++){
            for(int y = 0; y < LARGEUR / PIXEL; y++){
                SDL_Rect dest = {y * PIXEL, x * PIXEL, PIXEL, PIXEL};
                SDL_RenderCopy(renderer, solTex, NULL, &dest);
            }
        }

        //affichage de la map
        for(int x = 0; x < map->lignes; x++){
            for(int y = 0; y < map->colonnes; y++){
                SDL_Rect dest = {decalageX + y * PIXEL, decalageY + x * PIXEL, PIXEL, PIXEL};
                SDL_RenderCopy(renderer, solTex, NULL, &dest);

                switch(map->map[x][y]){
                    case '#':
                        SDL_RenderCopy(renderer, murTex, NULL, &dest);
                        break;
                    case 'P':
                        // -1 spawn et bas | 0 haut | 1 gauche | 2 droite 
                        if(depTextureChoice == -1){
                            SDL_RenderCopy(renderer, playerTexFace, NULL, &dest);
                        }else if(depTextureChoice == 0){
                            SDL_RenderCopy(renderer, playerTexBack, NULL, &dest);
                        }else if(depTextureChoice == 1){
                            SDL_RenderCopy(renderer, playerTexLeft, NULL, &dest);
                        }else if(depTextureChoice == 2){
                            SDL_RenderCopy(renderer, playerTexRight, NULL, &dest);
                        }
                        break;
                    case 'C':
                        SDL_RenderCopy(renderer, boxTex, NULL, &dest);
                        break;
                    case 'I':
                        SDL_RenderCopy(renderer, goalTex, NULL, &dest);
                        break;
                }
            }
        }

        //Recupere les solutions dans "solve.txt" et les execute
        buffer = fgetc(fd);
       
        if(buffer == '0'){
            break;
        }
        if(buffer == 'z'){
            deplaceJoueur(0,map);
        }else if(buffer == 's'){
            deplaceJoueur(1,  map);
        }else if(buffer == 'q'){
            deplaceJoueur(2, map);
        }else if(buffer == 'd'){
            deplaceJoueur(3, map);
        }else if(buffer == '0'){
            continuer = 0;
            break;
        }
        //verifier si le joueur a gagné + actualiser l'affichage des goals
        for(int i = 0; i < (map->nbCaisses); i++){
            Coord current;
            current = map->WinCaissePos[i];
            if(map->map[current.x][current.y] == ' '){
                map->map[current.x][current.y] = 'I';
            }
        }
        }
        //affichage des boutons
        SDL_Rect destButtonBack = {20, 20, 50, 50};
        SDL_RenderCopy(renderer, back, NULL, &destButtonBack);

        SDL_Rect destButtonPause = {100, 20, 50, 50};
        SDL_RenderCopy(renderer, pause, NULL, &destButtonPause);

        SDL_Rect destButtonPlus = {1100, 20, 50, 50};
        SDL_RenderCopy(renderer, plus, NULL, &destButtonPlus);

        SDL_Rect destButtonMoins = {1200, 20, 50, 50};
        SDL_RenderCopy(renderer, moins, NULL, &destButtonMoins);
        
        SDL_RenderPresent(renderer);
        SDL_Delay(delayCustom);

        // Gestion des évenements
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) {
                continuer = 0;
                break;
            }else if(event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    continuer = 0;
                    break;
                }
            }else if(event.type == SDL_MOUSEBUTTONDOWN){
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                //Si le joueur clique sur le bouton back alors on quitte la boucle et on affiche le niveau actuel
                if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonBack)){
                    fclose(fd);
                    SDL_DestroyTexture(murTex);
                    SDL_DestroyTexture(solTex);
                    SDL_DestroyTexture(playerTexFace);
                    SDL_DestroyTexture(boxTex);
                    SDL_DestroyTexture(playerTexBack);
                    SDL_DestroyTexture(playerTexLeft);
                    SDL_DestroyTexture(playerTexRight);
                    SDL_DestroyTexture(goalTex);
                    SDL_DestroyTexture(back);
                    libereEspaceDeLaMap(map);
                    SDL_DestroyTexture(plus);
                    SDL_DestroyTexture(moins);
                    
                    return 2;
                //Si le joueur clique sur le bouton pause alors on met en pause le jeu
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonPause)){
                    if(pauseFlag == 1){
                        pauseFlag = 0;
                    }else if (pauseFlag == 0){
                        pauseFlag = 1;
                    }
                //Si le joueur clique sur le moins plus alors on diminue la vitesse de la solution en augmentant le delay
                }else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonMoins)){
                    if(delayCustom <= 10000){
                        delayCustom += 100;
                    }
                //Si le joueur clique sur le bouton plus alors on augmente la vitesse de la solution en diminuant le delay
                }else if(SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &destButtonPlus)){
                    if(delayCustom > 100){
                        delayCustom -= 100;
                    }
                }
            }       
        } 
    }

    //fermeture du fichier et libération de la mémoire
    fclose(fd);
    SDL_DestroyTexture(murTex);
    SDL_DestroyTexture(solTex);
    SDL_DestroyTexture(playerTexFace);
    SDL_DestroyTexture(boxTex);
    SDL_DestroyTexture(playerTexBack);
    SDL_DestroyTexture(playerTexLeft);
    SDL_DestroyTexture(playerTexRight);
    SDL_DestroyTexture(goalTex);
    SDL_DestroyTexture(back);
    SDL_DestroyTexture(plus);
    SDL_DestroyTexture(moins);

    libereEspaceDeLaMap(map);
    
    return 2;
}


