//
// Created by Monssif Errami on 03/07/2023.
//

#ifndef JEU_ZZ11_MAPGENERATOR_H
#define JEU_ZZ11_MAPGENERATOR_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define GRID_SIZE 12
#define CELL_SIZE 45
#define SCREEN_WIDTH (GRID_SIZE * CELL_SIZE)
#define SCREEN_HEIGHT (GRID_SIZE * CELL_SIZE)
#define NUM_OBSTACLES 20
#define NUM_SAVIORS 2
#define NUM_ANIMALS 5

#define FRAME_COUNT 120
#define MOVEMENT_SPEED 20
#define SPEED 90000
#define NUM_DIRECTIONS 100
// Structure pour représenter les coordonnées des obstacles
typedef struct {
    int x;
    int y;
} Obstacle;

// Structure pour représenter les sauveurs
typedef struct {
    int x;
    int y;
} Savior;

// Tableau de sauveurs
Savior saviors[NUM_SAVIORS];

//Structure pour représenter les animaux blessés
typedef struct {
    int x;
    int y;
} Animal;


typedef struct {
    SDL_Rect rect;
    int* movementArray;
    int arraySize;
    int currentIndex;
} Subject;


typedef enum {
   UP, DOWN, LEFT, RIGHT
}DIRECTION;


#endif //JEU_ZZ11_MAPGENERATOR_H
