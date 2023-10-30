//
// Created by Monssif Errami on 03/07/2023.
//

#include "mapGenerator.h"

void end_sdl(char ok, // fin normale : ok = 0 ; anormale ok = 1
             char const* msg, // message à afficher
             SDL_Window* window, // fenêtre à fermer
             SDL_Renderer* renderer) { // renderer à fermer
    char msg_formated[255];
    int l;

    if (!ok) { // Affichage de ce qui ne va pas
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");

        SDL_Log(msg_formated, SDL_GetError());
    }

    if (renderer != NULL) { // Destruction si nécessaire du renderer
        SDL_DestroyRenderer(renderer); // Attention : on suppose que les NULL sont maintenus !!
        renderer = NULL;
    }
    if (window != NULL) { // Destruction si nécessaire de la fenêtre
        SDL_DestroyWindow(window); // Attention : on suppose que les NULL sont maintenus !!
        window= NULL;
    }

    SDL_Quit();

    if (!ok) { // On quitte si cela ne va pas
        exit(EXIT_FAILURE);
    }
}

SDL_Texture* load_texture_from_image(char * file_image_name, SDL_Window *window, SDL_Renderer *renderer ){
    SDL_Surface *my_image = NULL; // Variable de passage
    SDL_Texture* my_texture = NULL; // La texture

    my_image = IMG_Load(file_image_name); // Chargement de l'image dans la surface
    // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL,
    // uniquement possible si l'image est au format bmp */
    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image); // la SDL_Surface ne sert que comme élément transitoire
    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
}

SDL_Texture** createMovingSpriteTextures(SDL_Renderer* renderer, const char* spritePath, int numFrames) {
    // Load the sprite image
    SDL_Surface* spriteSurface = IMG_Load(spritePath);
    if (!spriteSurface) {
        printf("Failed to load sprite image: %s\n", IMG_GetError());
        return NULL;
    }

    // Calculate the width of each frame
    int frameWidth = spriteSurface->w / numFrames;

    // Create an array to store the textures for each frame
    SDL_Texture** frameTextures = malloc(sizeof(SDL_Texture*) * numFrames);
    if (!frameTextures) {
        printf("Failed to allocate memory for frame textures\n");
        SDL_FreeSurface(spriteSurface);
        return NULL;
    }

    // Split the sprite image into individual frames and create a texture for each frame
    for (int i = 0; i < numFrames; i++) {
        // Create a new surface for the frame
        SDL_Surface* frameSurface = SDL_CreateRGBSurface(0, frameWidth, spriteSurface->h, spriteSurface->format->BitsPerPixel, spriteSurface->format->Rmask, spriteSurface->format->Gmask, spriteSurface->format->Bmask, spriteSurface->format->Amask);
        if (!frameSurface) {
            printf("Failed to create frame surface: %s\n", SDL_GetError());
            SDL_FreeSurface(spriteSurface);
            for (int j = 0; j < i; j++) {
                SDL_DestroyTexture(frameTextures[j]);
            }
            free(frameTextures);
            return NULL;
        }

        // Copy the pixels from the sprite surface to the frame surface
        SDL_Rect srcRect = { i * frameWidth, 0, frameWidth, spriteSurface->h };
        SDL_BlitSurface(spriteSurface, &srcRect, frameSurface, NULL);

        // Create a texture from the frame surface
        frameTextures[i] = SDL_CreateTextureFromSurface(renderer, frameSurface);
        if (!frameTextures[i]) {
            printf("Failed to create texture from frame surface: %s\n", SDL_GetError());
            SDL_FreeSurface(spriteSurface);
            SDL_FreeSurface(frameSurface);
            for (int j = 0; j < i; j++) {
                SDL_DestroyTexture(frameTextures[j]);
            }
            free(frameTextures);
            return NULL;
        }

        // Free the frame surface as it is no longer needed
        SDL_FreeSurface(frameSurface);
    }

    // Free the sprite surface as it is no longer needed
    SDL_FreeSurface(spriteSurface);

    return frameTextures;
}



SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}




//Generer les arbres aléatoirement
void generateObstacles(char grid[GRID_SIZE][GRID_SIZE], Obstacle obstacles[NUM_OBSTACLES], SDL_Renderer* renderer, SDL_Texture* obstacleTexture) {


    for (int i = 0; i < NUM_OBSTACLES; i++) {
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;
        obstacles[i].x = x;
        obstacles[i].y = y;
        grid[x][y] = 'A'; // 'A' représente un obstacle (arbre) dans la grille

        SDL_Rect obstacleRect = { y * 50, x * 50, 50, 50 };
        SDL_RenderCopy(renderer, obstacleTexture, NULL, &obstacleRect);
    }
}


void printGrid(char grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}



//Generer les sauveurs
void generateSaviors(char grid[GRID_SIZE][GRID_SIZE], Savior saviors[NUM_SAVIORS]/*, SDL_Renderer* renderer, SDL_Texture* animalTexture*/) {


    for (int i = 0; i < NUM_SAVIORS; i++) {
        int x, y;
        do {
            x = rand() % GRID_SIZE;
            y = rand() % GRID_SIZE;
        } while (grid[x][y] != '0' || grid[x][y] == 'A');

        saviors[i].x = x;
        saviors[i].y = y;
        grid[x][y] = 'S'; // 'S' représente un sauveur dans la grille

//        SDL_Rect saviorRect = { y * CELL_SIZE, x * CELL_SIZE, CELL_SIZE, CELL_SIZE };
//        SDL_RenderCopy(renderer, saviorTexture, NULL, &saviorRect);
    }
}

bool isPathExists(char grid[GRID_SIZE][GRID_SIZE], int startX, int startY, int targetX, int targetY, bool visited[GRID_SIZE][GRID_SIZE]) {
    // Vérifier si les positions sont valides et si elles sont déjà visitées
    if (startX < 0 || startX >= GRID_SIZE || startY < 0 || startY >= GRID_SIZE || visited[startX][startY]) {
        return false;
    }

    // Marquer la case comme visitée
    visited[startX][startY] = true;

    // Vérifier si la case cible a été atteinte
    if (startX == targetX && startY == targetY) {
        return true;
    }

    // Vérifier la connectivité avec les cases adjacentes
    if (grid[startX][startY] != 'A') {
        if (isPathExists(grid, startX - 1, startY, targetX, targetY, visited)) return true; // Case en haut
        if (isPathExists(grid, startX + 1, startY, targetX, targetY, visited)) return true; // Case en bas
        if (isPathExists(grid, startX, startY - 1, targetX, targetY, visited)) return true; // Case à gauche
        if (isPathExists(grid, startX, startY + 1, targetX, targetY, visited)) return true; // Case à droite
    }

    return false;
}


void generateAnimals(char grid[GRID_SIZE][GRID_SIZE], Animal animals[NUM_ANIMALS]/*, SDL_Renderer* renderer, SDL_Texture* animalTexture*/) {
    srand(time(NULL));

    for (int i = 0; i < NUM_ANIMALS; i++) {
        int x, y;
        bool pathExists;

        do {
            x = rand() % GRID_SIZE;
            y = rand() % GRID_SIZE;

            // Vérifier si un chemin existe entre l'animal et au moins un sauveur
            bool visited[GRID_SIZE][GRID_SIZE] = { false };
            pathExists = false;

            for (int j = 0; j < NUM_SAVIORS; j++) {
                if (isPathExists(grid, x, y, saviors[j].x, saviors[j].y, visited)) {
                    pathExists = true;
                    break;
                }
            }

        } while (grid[x][y] != '0' || grid[x][y] == 'A' || !pathExists);

        animals[i].x = x;
        animals[i].y = y;
        grid[x][y] = 'W'; // 'W' représente un animal blessé dans la grille

//        SDL_Rect animalRect = { y * CELL_SIZE, x * CELL_SIZE, CELL_SIZE, CELL_SIZE };
//        SDL_RenderCopy(renderer, animalTexture, NULL, &animalRect);
    }
}



void drawMap(SDL_Renderer* renderer, SDL_Texture* backgroundTexture, SDL_Texture* obstacleTexture, SDL_Texture*** saviorTexture, SDL_Texture*** animalTextures,TTF_Font* font, char grid[GRID_SIZE][GRID_SIZE], Obstacle obstacles[], Savior *savior, Animal animals[], int anim,int time) {
    // Clear the screen

    int frameIndex = SDL_GetTicks() / 100 % 4;


    // Display the background
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    // Display the obstacles
    for (int i = 0; i < NUM_OBSTACLES; i++) {
        SDL_Rect obstacleRect = { obstacles[i].y * CELL_SIZE, obstacles[i].x * CELL_SIZE, CELL_SIZE, CELL_SIZE };
        SDL_RenderCopy(renderer, obstacleTexture, NULL, &obstacleRect);
        // Subject rectangle
    }

    //Display the saviors



    for (int i = 0 ; i < NUM_SAVIORS ; i++){
        int frameIndex = SDL_GetTicks() / 100 % 4;
        SDL_Rect saviorRect = { saviors[i].x * CELL_SIZE /*+ f(saviors[i].x,saviors[i].x+1,time)*/, saviors[i].y *CELL_SIZE /*+f(saviors[i].y,saviors[i].y+1,time)*/, CELL_SIZE, CELL_SIZE };
        SDL_RenderCopy(renderer, saviorTexture[i][frameIndex], NULL, &saviorRect);
    }



    // Display the saviors

    // Display the animals
    for (int i = 0; i < anim; i++) {
        int frameIndex = SDL_GetTicks() / 100 % 4;
        SDL_Rect animalRect = { animals[i].x * CELL_SIZE, animals[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE };
        SDL_RenderCopy(renderer, animalTextures[i][frameIndex], NULL, &animalRect);
    }

    //display score

    SDL_Color textColor = { 255, 255, 255, 255 };
    char scoreText[32];

    snprintf(scoreText, sizeof(scoreText), "Score: %d", NUM_ANIMALS - anim);
    SDL_Texture* scoreTexture = renderText(scoreText, font, textColor, renderer);


    int textureWidth, textureHeight;
    SDL_QueryTexture(scoreTexture, NULL, NULL, &textureWidth, &textureHeight);
    SDL_Rect scoreRect = { 10,   10, textureWidth, textureHeight };
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);


    SDL_DestroyTexture(scoreTexture);
    SDL_DestroyTexture(scoreTexture);

    // Update the display
    SDL_RenderPresent(renderer);

}

void drawMapEnd(SDL_Renderer* renderer, SDL_Texture* backgroundTexture, SDL_Texture* obstacleTexture, SDL_Texture*** saviorTexture, SDL_Texture*** animalTextures,TTF_Font* font, char grid[GRID_SIZE][GRID_SIZE], Obstacle obstacles[], Savior *savior, Animal animals[], int anim,SDL_Texture* gameOverTexture) {
    // Clear the screen

    int frameIndex = SDL_GetTicks() / 100 % 4;


    // Display the background
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    // Display the obstacles
    for (int i = 0; i < NUM_OBSTACLES; i++) {
        SDL_Rect obstacleRect = { obstacles[i].y * CELL_SIZE, obstacles[i].x * CELL_SIZE, CELL_SIZE, CELL_SIZE };
        SDL_RenderCopy(renderer, obstacleTexture, NULL, &obstacleRect);
        // Subject rectangle
    }

    //Display the saviors



    for (int i = 0 ; i < NUM_SAVIORS ; i++){
        int frameIndex = SDL_GetTicks() / 100 % 4;
        SDL_Rect saviorRect = { saviors[i].x * CELL_SIZE , saviors[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE };
        SDL_RenderCopy(renderer, saviorTexture[i][frameIndex], NULL, &saviorRect);

    }



    // Display the saviors

    // Display the animals
    for (int i = 0; i < anim; i++) {
        int frameIndex = SDL_GetTicks() / 100 % 4;
        SDL_Rect animalRect = { animals[i].x * CELL_SIZE, animals[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE };
        SDL_RenderCopy(renderer, animalTextures[i][frameIndex], NULL, &animalRect);
    }

    //display score

    SDL_Color textColor = { 255, 255, 255, 255 };
    char scoreText[32];

    snprintf(scoreText, sizeof(scoreText), "Score: %d", NUM_ANIMALS - anim);
    SDL_Texture* scoreTexture = renderText(scoreText, font, textColor, renderer);


    int textureWidth, textureHeight;
    SDL_QueryTexture(scoreTexture, NULL, NULL, &textureWidth, &textureHeight);
    SDL_Rect scoreRect = { 10,   10, textureWidth, textureHeight };
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);

    // Render the start button
    SDL_Rect buttonRect = { SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 100, 300, 200 };
    SDL_RenderCopy(renderer, gameOverTexture, NULL, &buttonRect);


    SDL_DestroyTexture(scoreTexture);
    SDL_DestroyTexture(scoreTexture);

    // Update the display
    SDL_RenderPresent(renderer);

}


SDL_Texture* createBackgroundTexture(SDL_Renderer* renderer, const char* spriteImagePath) {
    SDL_Surface* spriteSurface = IMG_Load(spriteImagePath);
    if (!spriteSurface) {
        printf("Failed to load sprite image: %s\n", IMG_GetError());
        return NULL;
    }

    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, spriteSurface);
    if (!backgroundTexture) {
        printf("Failed to create background texture: %s\n", SDL_GetError());
        SDL_FreeSurface(spriteSurface);
        return NULL;
    }

    SDL_FreeSurface(spriteSurface);
    return backgroundTexture;
}

void drawStartScreen(SDL_Renderer* renderer, SDL_Texture* startButtonTexture) {
    static int backgroundOffset = 0; // Offset for moving background
    SDL_Texture* backgroundTexture =  createBackgroundTexture(renderer,"b_sprite.jpg");

    // Clear the screen
    SDL_RenderClear(renderer);

    // Render the moving background
    SDL_Rect backgroundRect1 = { -backgroundOffset, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_Rect backgroundRect2 = { -backgroundOffset + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundRect1);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundRect2);

    // Update the background offset
    backgroundOffset = (backgroundOffset + 1) % SCREEN_WIDTH;

    // Render the start button
    SDL_Rect buttonRect = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 100 };
    SDL_RenderCopy(renderer, startButtonTexture, NULL, &buttonRect);

    // Update the display
    SDL_RenderPresent(renderer);
}

