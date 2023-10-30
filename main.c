#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <SDL2/SDL_ttf.h>


#include "mapGenerator.h"
#include "mapGenerator.c"
#include "Simulation.c"



int main(int argc, char* argv[]) {

    srand(time(NULL));
    Animal animals[NUM_ANIMALS];

    // Initialization of SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Forêt", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    IMG_Init(IMG_INIT_PNG);

    // Subject rectangle



    // Load the background image
    SDL_Texture* backgroundTexture = load_texture_from_image("backround.png", window, renderer);

    // Load the obstacle image
    SDL_Texture* obstacleTexture = load_texture_from_image("tree.png", window, renderer);

    // Load the savior image
//    SDL_Texture* saviorTexture = load_texture_from_image("savior.bmp", window, renderer);

    SDL_Texture***  saviorTexture = (SDL_Texture***)malloc(2 * sizeof (SDL_Texture**));
    saviorTexture[0] = createMovingSpriteTextures(renderer, "saviorUP.png", 4);
    saviorTexture[1] = createMovingSpriteTextures(renderer, "saviorUP.png", 4);
    SDL_Texture** saviorTextureUP = createMovingSpriteTextures(renderer, "saviorUP.png", 4);
    SDL_Texture** saviorTextureDOWN = createMovingSpriteTextures(renderer, "saviorDOWN.png", 4);
    SDL_Texture** saviorTextureLEFT = createMovingSpriteTextures(renderer, "saviorLEFT.png", 4);
    SDL_Texture** saviorTextureRIGHT = createMovingSpriteTextures(renderer,"saviorRIGHT.png", 4);

    //animal textures
    SDL_Texture*** animalTextures= (SDL_Texture***)malloc(5 * sizeof (SDL_Texture**));
    animalTextures[0] = createMovingSpriteTextures(renderer,"fox1.png", 6);
    animalTextures[1] = createMovingSpriteTextures(renderer,"fox2.png", 14);
    animalTextures[2] = createMovingSpriteTextures(renderer,"fox3.png", 11);
    animalTextures[3] = createMovingSpriteTextures(renderer,"fox2.png", 14);
    animalTextures[4] = createMovingSpriteTextures(renderer,"fox3.png", 11);


    // Load the start button image
    SDL_Texture* startButtonTexture = load_texture_from_image("start.png", window, renderer);
    SDL_Texture* gameOverTexture = load_texture_from_image("Game_Over.png", window, renderer);

    // Grid to represent the window with obstacles
    char grid[GRID_SIZE][GRID_SIZE];

    // Initialization of the grid with empty spaces
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = '0';
        }
    }

    // Random generation of obstacles
    Obstacle obstacles[NUM_OBSTACLES];
    generateObstacles(grid, obstacles, renderer, obstacleTexture);
    generateSaviors(grid, saviors/*, renderer, saviorTexture*/);
    generateAnimals(grid, animals/*, renderer, saviorTexture*/);

    //load font

    if (TTF_Init() < 0)
    {
        // Handle initialization error
        SDL_Log("Failed to initialize SDL_ttf: %s", TTF_GetError());
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("font.ttf", 24);

    if (!font)
    {
        // Handle font loading error
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return 1;
    }

    // Display the grid with obstacles
    printGrid(grid);

    // Show the start screen

    bool endscreen = false;
    bool startScreen = true;
    bool running = true;
    int time = 0;
    int time2 = 1;
    int anim = NUM_ANIMALS;
    // Main game loop
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (startScreen) {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if (mouseX >= SCREEN_WIDTH / 2 - 100 && mouseX <= SCREEN_WIDTH / 2 + 100 &&
                        mouseY >= SCREEN_HEIGHT / 2 - 50 && mouseY <= SCREEN_HEIGHT / 2 + 50) {
                        startScreen = false;
                    }
                }
            }
        }

        if (startScreen) {
            // Draw the start screen
            drawStartScreen(renderer, startButtonTexture);
        }
        else {
            if (!time){                                   //premier affichage
                trouver_emplacement_sauveurs(grid,GRID_SIZE, saviors);
                anim = trouver_emplacement_animal(grid,GRID_SIZE,animals);


                drawMap(renderer, backgroundTexture, obstacleTexture, saviorTexture, animalTextures,font, grid, obstacles,
                        saviors, animals,anim,0);


            }else if(time > SPEED ){                        //boucle de jeu

                trouver_emplacement_sauveurs(grid,GRID_SIZE, saviors);
                anim = trouver_emplacement_animal(grid,GRID_SIZE,animals);

                Savior sauveur1 = saviors[0];
                Savior sauveur2 = saviors[1];

                // Générer les situations actuelles des sauveurs
                SituationActuelle situation_sauveur1 = generer_situation_actuelle(sauveur1, grid, 12);
                SituationActuelle situation_sauveur2 = generer_situation_actuelle(sauveur2, grid, 12);


                char* action1 = action_final(situation_sauveur1, regles, nombre_regles);
                printf("%s\n",action1);
                char* action2 = action_final(situation_sauveur2, regles, nombre_regles);
                printf("%s\n",action2);

                if (strcmp(action1, "A") == 0) {
                    saviorTexture[0] = saviorTextureUP;
                } else if (strcmp(action1, "R") == 0) {
                    saviorTexture[0] = saviorTextureDOWN;
                } else if (strcmp(action1, "G") == 0) {
                    saviorTexture[0] = saviorTextureLEFT;
                } else if (strcmp(action1, "D") == 0) {
                    saviorTexture[0] = saviorTextureRIGHT;
                }

                if (strcmp(action2, "A") == 0) {
                    saviorTexture[1] = saviorTextureUP;
                } else if (strcmp(action2, "R") == 0) {
                    saviorTexture[1] = saviorTextureDOWN;
                } else if (strcmp(action2, "G") == 0) {
                    saviorTexture[1] = saviorTextureLEFT;
                } else if (strcmp(action2, "D") == 0) {
                    saviorTexture[1] = saviorTextureRIGHT;
                }

                if(time2 == 3){
                    executer_action(action1,grid,&saviors[0]);
                    executer_action(action2,grid,&saviors[1]);
                    time2 = 1;
                }
                time2++;
                printGrid(grid);

                drawMap(renderer, backgroundTexture, obstacleTexture, saviorTexture, animalTextures,font, grid, obstacles,
                        saviors, animals,anim,time2);

                time = 0;
                if (anim == 0){
                    drawMapEnd(renderer, backgroundTexture, obstacleTexture, saviorTexture, animalTextures,font, grid, obstacles,
                               saviors, animals,anim,gameOverTexture);
                }
            }
            time++;
        }

    }

    // Free resources
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(obstacleTexture);
    for (int j = 0; j < 2; j++){
        for (int i = 0; i < 4; i++) {
            SDL_DestroyTexture(saviorTexture[j][i]);
        }
    }

    for (int j = 0; j < 4; j++){
        for (int i = 0; i < 4; i++) {
            SDL_DestroyTexture(animalTextures[j][i]);
        }
    }
    SDL_DestroyTexture(startButtonTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;

}




