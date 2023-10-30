#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>



#define GRID_SIZE 12
#define CELL_SIZE 45
#define SCREEN_WIDTH (GRID_SIZE * CELL_SIZE)
#define SCREEN_HEIGHT (GRID_SIZE * CELL_SIZE)
#define NUM_OBSTACLES 20
#define NUM_SAVIORS 2
#define NUM_ANIMALS 15
#define IT_MAX 10

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


//Generer les arbres aléatoirement 
 void generateObstacles(char grid[GRID_SIZE][GRID_SIZE], Obstacle obstacles[NUM_OBSTACLES]) {
  

    for (int i = 0; i < NUM_OBSTACLES; i++) {
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;
        obstacles[i].x = x;
        obstacles[i].y = y;
        grid[x][y] = 'A'; // 'A' représente un obstacle (arbre) dans la grille

    }
}

//Dessiner la grille 
void printGrid(char grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}

//Generer les sauveurs 
void generateSaviors(char grid[GRID_SIZE][GRID_SIZE], Savior saviors[NUM_SAVIORS]) {
    

    for (int i = 0; i < NUM_SAVIORS; i++) {
        int x, y;
        do {
            x = rand() % GRID_SIZE;
            y = rand() % GRID_SIZE;
        } while (grid[x][y] != '0' || grid[x][y] == 'A');

        saviors[i].x = x;
        saviors[i].y = y;
        grid[x][y] = 'S'; // 'S' représente un sauveur dans la grille
    }
}

bool isPathExists(char grid[GRID_SIZE][GRID_SIZE], int startX, int startY, int targetX
, int targetY, bool visited[GRID_SIZE][GRID_SIZE]) {
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
        if (isPathExists(grid, startX - 1, startY, targetX, targetY, visited)) return true;  // Case en haut
        if (isPathExists(grid, startX + 1, startY, targetX, targetY, visited)) return true;  // Case en bas
        if (isPathExists(grid, startX, startY - 1, targetX, targetY, visited)) return true;  // Case à gauche
        if (isPathExists(grid, startX, startY + 1, targetX, targetY, visited)) return true;  // Case à droite
    }

    return false;
}

void generateAnimals(char grid[GRID_SIZE][GRID_SIZE], Animal animals[NUM_ANIMALS]) {
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
    }
}

//trouver l'emplacement des sauveurs
void trouver_emplacement_sauveurs(char matrice[][12], int taille, Savior* sauveurs) {
    int sauveurs_trouves = 0;
    while ((sauveurs_trouves<2))
    {
        for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            if (matrice[i][j] == 'S') {
                sauveurs[sauveurs_trouves].x= j;
                sauveurs[sauveurs_trouves].y = i;
                sauveurs_trouves++;}
                
            }
        }
    }
   
}
//trouver l'emplacement des sauveurs
int trouver_emplacement_animal(char matrice[][12], int taille, Animal* animals ) {

    int anim_trouv = 0;
        for (int i = 0; i < taille; i++) {
            for (int j = 0; j < taille; j++) {
                if (matrice[i][j] == 'W') {
                    animals[anim_trouv].x= j;   
                    animals[anim_trouv].y = i;
                    anim_trouv++;
                }
                
            }
        }
        return anim_trouv;
    
   
}

// //Fonction trouver le sauveur le plus proche
char* sauveur_proche(Savior sauveur, char matrice[][12], int N ){

      char* C;
      int dis_min=99;
      int x=0, y=0;
      for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                  if (matrice[i][j]=='S' )
                  {
                        if (sauveur.x!=j || sauveur.y!=i){
                              int dis=abs(sauveur.x-j)+abs(sauveur.y-i);//distance Hamilto
                              if(dis<dis_min){
                                    x=j;
                                    y=i;
                                    dis_min=dis;
                              }
                        }
                  }
            }
      }//on a trouvé le sauveur le plus proche 
      if (x-sauveur.x>=0){//le sauveur est dans l'est
            if(y-sauveur.y>=0) {   
                  //sauveur dans le SUD
                  if(x-sauveur.x  > y-sauveur.y){
                        C="E";
                  }else{C="S";}


            }else{
                  //Sauveur dans le nord
                  if(x-sauveur.x>sauveur.y-y){
                        C="E";
                  }else{C="N";}


            }
      }else{if(y-sauveur.y>=0) {   
                  //sauveur dans le SUD
                  if(sauveur.x-x > y-sauveur.y){
                        C="O";
                  }else{C="S";}


            }else{
                  //Sauveur dans le nord
                  if(x-sauveur.x > sauveur.y-y){
                        C="O";
                  }else{C="N";}


            }

      }
      return C ;

}

// //Fonction trouver l'animal le plus proche
char* animal_proche(Savior sauveur , char matrice[][12], int N ){
      char* C="a";
      int dis_min=99;
      int x=0, y=0;
      for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                  if (matrice[i][j]=='W')
                  {
                        int dis=abs(sauveur.x-j)+abs(sauveur.y-i);//distance Hamilto
                        if(dis<dis_min){
                              x=j;
                              y=i;
                              dis_min=dis;
                  }}
            }
      }//on a trouvé l'animal le plus proche

      if (x-sauveur.x>0){//l'animal est dans l'est
            if(y-sauveur.y>0) { 
                  //ANIMAL dans le SUD
                  C="SE";

            }else{
                  //ANIMAL dans le nord
                  if(sauveur.y-y>0){
                        C="NE";
                  }else{C="E";}


            }
      }else{ 
            //L'animal dans l'ouest
            if(x<sauveur.x){
                  if(y-sauveur.y>0){   
                  //animal dans le SUD
                  C="SO";

            }else{
                  //Sauveur dans le nord
                  if(sauveur.y-y>0){
                        C="NO";
                  }else{C="O";}


            }
            }
            else{  
                  if(y-sauveur.y>0){   
                        //animal dans le SUD
                        C="S";

            }else{
                  //Sauveur dans le nord
                  if(sauveur.y-y>0){
                        C="N";}
}


      }}
      return C ;


}


char* get_case_haut(Savior sauveur, char matrice[][GRID_SIZE], int N) {
    char* C;
    int x = sauveur.x;
    int y = sauveur.y - 1;
    
    
    
    if (matrice[y][x] == 'W') {
         C="0";
    }
    else if (matrice[y][x] == 'A') {
        C="1";
    }
    else if (y == -1) {
        C="1";
    }
    else {
        C="0";
    }
    
    return C;
    
}

char* get_case_gauche(Savior sauveur, char matrice[][GRID_SIZE], int N) {
    char* C;
    int x = sauveur.x - 1;
    int y = sauveur.y;
    
    if (matrice[y][x] == 'W') {
         C="0";
    }
    else if (matrice[y][x] == 'A') {
        C="1";
    }
    else if (x == -1) {
         C="1";
    }
    else {
        C="0";
    }
    
    return C;
}

char* get_case_droite(Savior sauveur, char matrice[][GRID_SIZE], int N) {
      char* C;
    int x = sauveur.x + 1;
    int y = sauveur.y;
    
    
    if (matrice[y][x] == 'W') {
         C="0";
    }
    else if (matrice[y][x] == 'A') {
        C="1";
    }
    else if (x > N-1) {
        C="1";
    }
    else {
        C="0";
    }
    
    return C;
    
    
}

char* get_case_bas(Savior sauveur, char matrice[][GRID_SIZE], int N) {
     char* C;
    int x = sauveur.x;
    int y = sauveur.y + 1;
    
    
  if (matrice[y][x] == 'W') {
         C="0";
    }
    else if (matrice[y][x] == 'A') {
        C="1";
    }
    else if (y > N-1) {
         C="1";
    }
    
    else {
        C="0";
    }
    
    return C;
   
}


    typedef struct {
    char * case_haut;
    char * case_gauche;
    char * case_droite;
    char * case_bas;
    char *  sauveur_proche;
    char * animal_proche;
} SituationActuelle;

SituationActuelle generer_situation_actuelle(Savior sauveur, char matrice[][12], int N) {
    SituationActuelle situation;

    // Récupérer les informations des cases adjacentes
    situation.case_haut = get_case_haut(sauveur, matrice, N);
    situation.case_gauche = get_case_gauche(sauveur, matrice, N);
    situation.case_droite = get_case_droite(sauveur, matrice, N);
    situation.case_bas = get_case_bas(sauveur, matrice, N);

    // Récupérer les informations sur les positions proches des animaux et sauveurs
    char* animaux_proches = animal_proche(sauveur, matrice, N);
    char* sauveurs_proches = sauveur_proche(sauveur, matrice, N);

    // Copier les directions dans la situation actuelle
    situation.sauveur_proche = strdup(sauveurs_proches);
    situation.animal_proche = strdup(animaux_proches);
    return situation;
}

typedef struct {
    char * case_haut;
    char * case_gauche;
    char * case_droite;
    char * case_bas;
    char* sauveur_proche;
    char* animal_proche;
    char * action;
    int priorite;
} Regle;

bool correspond_a_la_situation(SituationActuelle observation, Regle regle) {
    if ((regle.case_haut == observation.case_haut ||  strcmp(regle.case_haut, "-1") == 0) &&
        (regle.case_gauche == observation.case_gauche || strcmp(regle.case_gauche, "-1") == 0) &&
        (regle.case_droite == observation.case_droite ||  strcmp(regle.case_droite, "-1") == 0) &&
        (regle.case_bas == observation.case_bas ||  strcmp(regle.case_bas, "-1") == 0) &&
        ( (strcmp(regle.sauveur_proche, observation.sauveur_proche) == 0) || (strcmp(regle.sauveur_proche, "-1") == 0)  )  &&
        ((strcmp(regle.animal_proche , observation.animal_proche) == 0)||((strcmp(regle.animal_proche, "N") == 0 && (strcmp(observation.animal_proche, "NE") == 0 || strcmp(observation.animal_proche, "NO") == 0 )) ||
         (strcmp(regle.animal_proche, "S") == 0 && (strcmp(observation.animal_proche, "SE") == 0 || strcmp(observation.animal_proche, "SO") == 0))  )))  {
        return true;
    }else {
    return false;
    }
}

Regle* filtrer_regles(SituationActuelle situation, Regle* regles, int taille_regles, int* taille_filtre) {
    Regle* regles_filtrees = malloc(taille_regles * sizeof(Regle)); // Allouer un tableau pour stocker les règles filtrées
    int taille = 0; // Taille du tableau des règles filtrées
    
    for (int i = 0; i < taille_regles; i++) {
        if (correspond_a_la_situation(situation, regles[i])) {
            regles_filtrees[taille++] = regles[i]; // Ajouter la règle filtrée au tableau
        }
    }
    
    // Réallouer la mémoire pour correspondre à la taille réelle des règles filtrées
    regles_filtrees = realloc(regles_filtrees, taille * sizeof(Regle));
    
    *taille_filtre = taille; // Mettre à jour la taille du tableau des règles filtrées
    
    return regles_filtrees;
}

double* calculer_probabilites(Regle* regles_filtrees, int nb_regles_filtrees, int puissance) {
    double* probabilites = malloc(nb_regles_filtrees * sizeof(double));
 
    // Calculer la somme des puissances des priorités
    double somme_puissances = 0.0;
    for (int i = 0; i < nb_regles_filtrees; i++) {
       somme_puissances += pow(regles_filtrees[i].priorite, puissance);
    }
 
    // Calculer les probabilités pour chaque règle
   for (int i = 0; i < nb_regles_filtrees; i++) {
   double puissance_priorite = pow(regles_filtrees[i].priorite, puissance);
   probabilites[i] = puissance_priorite / somme_puissances;
 }
 
 return probabilites;
}

char * choisir_action(double* probabilites,Regle* regles_filtrees, int taille_probabilites) {
 // Générer un nombre aléatoire entre 0 et 1
 double random = (double)rand() / RAND_MAX;
 
 // Trouver l'action correspondante à la probabilité générée aléatoirement
   double cumulatif = 0.0;
   for (int i = 0; i < taille_probabilites; i++) {
      cumulatif += probabilites[i];
      if (random <= cumulatif) {
    return regles_filtrees[i].action;
    }
 }
 
 // Si aucune action n'a été choisie, retourner un caractère nul
 return "N";
}

int action_possible(char* action, SituationActuelle situation) {
 // Vérifier si l'action est possible en fonction de la situation
 if (strcmp(action, "A") == 0) {
     if (strcmp(situation.case_haut, "1") == 0) {
    return 0; // Action impossible
   }
   } else if (strcmp(action, "R") == 0) {
      if (strcmp(situation.case_bas, "1") == 0) {
     return 0; // Action impossible
   }
    } else if (strcmp(action, "G") == 0) {
        if (strcmp(situation.case_gauche, "1") == 0) {
        return 0; // Action impossible
    }
   } else if (strcmp(action, "D") == 0) {
       if (strcmp(situation.case_droite, "1") == 0) {
      return 0; // Action impossible
    }
    } else if (strcmp(action, "N") == 0) {
    return 0; // Action impossible
    }
 
 return 1; // Action possible
}

char* action_final(SituationActuelle situation , Regle* regles, int taille_regles){

      int taille_filtre=0;
      Regle* regle_filtree = filtrer_regles(situation,regles,taille_regles,&taille_filtre);

      double* probabilites = calculer_probabilites(regle_filtree,taille_filtre,2);
      int possible=0;
      char * action="N";

    while (possible != 1)
    {
     action = choisir_action(probabilites,regle_filtree,taille_filtre);
     possible=action_possible(action,situation);
    }

 return action;
 
}

void executer_action(char* action, char matrice[][12], Savior* situation) {
    int x = situation->x;
    int y = situation->y;

   if (strcmp(action, "A") == 0) {
       matrice[y - 1][x] = 'S';
       matrice[y][x] = '0';
       situation->x = x; // Mettez ici la nouvelle valeur de x après le déplacement
       situation->y = y - 1; // Mettez ici la nouvelle valeur de y après le déplacement
      } else if (strcmp(action, "R") == 0) {
                  matrice[y + 1][x] = 'S';
                  matrice[y][x] = '0';
                  situation->x = x; // Mettez ici la nouvelle valeur de x après le déplacement
                 situation->y = y + 1; // Mettez ici la nouvelle valeur de y après le déplacement
            } else if (strcmp(action, "G") == 0) {
                 matrice[y][x - 1] = 'S';
                 matrice[y][x] = '0';
                 situation->x = x - 1; // Mettez ici la nouvelle valeur de x après le déplacement
                 situation->y = y; // Mettez ici la nouvelle valeur de y après le déplacement
               } else if (strcmp(action, "D") == 0) {
                        matrice[y][x + 1] = 'S';
                        matrice[y][x] = '0';
                       situation->x = x + 1; // Mettez ici la nouvelle valeur de x après le déplacement
                       situation->y = y; // Mettez ici la nouvelle valeur de y après le déplacement
 }
}
void melangerTableau(int* tableau, int taille) {
    srand(time(NULL));
    
    for (int i = taille - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        
        int temp = tableau[i];
        tableau[i] = tableau[j];
        tableau[j] = temp;
    }
}

double score(Regle* regles,int nombre_regles){
    double scr=0;

    int iteration =0 ;

    Savior sauveurs[NUM_SAVIORS];
    Animal animals[NUM_ANIMALS];
    Obstacle obstacles[NUM_OBSTACLES];

    for (int i = 0; i < GRID_SIZE; i++)
    {
        // Grille pour représenter la fenêtre avec les obstacles
        char grid[GRID_SIZE][GRID_SIZE];
        // Initialisation de la grille avec des espaces vides
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                grid[i][j] = '0';
            }
        }
    // Génération aléatoire des obstacles
   
    generateObstacles(grid, obstacles);
    generateSaviors(grid, saviors);
    generateAnimals(grid, animals);
     int anim=0;
    while (iteration<IT_MAX )
        {
            //trouver l'emplacement des sauveurs
            trouver_emplacement_sauveurs(grid,GRID_SIZE, sauveurs);
         
            //trouver l'eplacement des animals
             anim =trouver_emplacement_animal(grid,GRID_SIZE,animals);
  
            //Récupérer les positions des sauveurs 
            Savior sauveur1 = sauveurs[0];
            Savior sauveur2 = sauveurs[1];
                
            // Générer les situations actuelles des sauveurs
            SituationActuelle situation_sauveur1 = generer_situation_actuelle(sauveur1, grid, 12);
            SituationActuelle situation_sauveur2 = generer_situation_actuelle(sauveur2, grid, 12);

            // Appel à la fonction action_final
            char* action1 = action_final(situation_sauveur1, regles, nombre_regles);
            
            char* action2 = action_final(situation_sauveur2, regles, nombre_regles);
            
            executer_action(action1,grid,&sauveurs[0]);
            executer_action(action2,grid,&sauveurs[1]);

            iteration++;
                }
    scr+=anim;
    }
    return (scr/5);
}

Regle* modifi_Regle(Regle* regles, int i, int j,char* nouvelleValeur,int nomb) {
    // Calculer le nombre total de règles
    // int nomb = sizeof(regles) / sizeof(Regle);

    // Allouer un nouveau tableau de règles avec la même taille que l'original
    Regle* nouveauRegles = malloc(nomb * sizeof(Regle));

    // Copier les règles de l'original vers le nouveau tableau
    memcpy(nouveauRegles, regles, nomb * sizeof(Regle));

    // Modifier la valeur de la règle (i, j) dans le nouveau tableau
    if(j == 0){       
        nouveauRegles[i].case_haut = nouvelleValeur;
    } else if (j ==1){
        nouveauRegles[i].case_gauche = nouvelleValeur;
    }else if(j == 2){
        nouveauRegles[i].case_droite = nouvelleValeur;
    }else if( j ==3 ){
        nouveauRegles[i].case_haut = nouvelleValeur;
    }else if ( j ==4 ){
         nouveauRegles[i].sauveur_proche = nouvelleValeur;
    }else if(j==5) {
         nouveauRegles[i].animal_proche = nouvelleValeur;
    }else{
        nouveauRegles[i].action = nouvelleValeur;
    }
    // Retourner le nouveau tableau de règles modifié
    return nouveauRegles;
}

Regle* modify_Regle(Regle* regles, int i, int j,int nouvelleValeur,int nomb) {

    // Allouer un nouveau tableau de règles avec la même taille que l'original
    Regle* nouveauRegles = malloc(nomb * sizeof(Regle));

    // Copier les règles de l'original vers le nouveau tableau
    memcpy(nouveauRegles, regles, nomb * sizeof(Regle));

    // Modifier la valeur de la règle (i, j) dans le nouveau tableau
    if ( j ==7 ){
         nouveauRegles[i].priorite = nouvelleValeur;
    }

    // Retourner le nouveau tableau de règles modifié
    return nouveauRegles;
}

void copierRegles(Regle regles[], const Regle nouv_regles[], int taille) {
    memcpy(regles, nouv_regles, taille * sizeof(Regle));
}



int main() {

 Regle regles[] = {
 {"0", "-1", "-1", "-1", "S", "N", "A", 1},
 {"-1", "-1", "-1", "-1", "-1", "N", "A", 1},
 {"-1", "-1", "-1", "-1", "-1", "S", "R", 1},
 {"-1", "-1", "-1", "-1", "-1", "E", "D", 1},
 {"-1", "-1", "-1", "-1", "-1", "O", "G", 1},
 {"1", "0", "-1", "-1", "-1", "N", "G", 2},
 {"1", "-1", "0", "-1", "-1", "N", "D", 3},
 {"1", "-1", "-1", "0", "-1", "N", "R", 2},
 {"-1", "0", "-1", "1", "-1", "S", "G", 1},
 {"-1", "-1", "0", "1", "-1", "S", "D", 3},
 {"0", "-1", "-1", "1", "-1", "S", "A", 1},
 {"-1", "-1", "1", "0", "-1", "E", "R", 2},
 {"-1", "0", "1", "-1", "-1", "E", "G", 1},
 {"0", "-1", "1", "-1", "-1", "E", "A", 2},
 {"0", "1", "-1", "-1", "-1", "O", "A", 1},
 {"-1", "1", "-1", "0", "-1", "O", "R", 1},
 {"-1", "-1", "-1", "0", "-1", "S", "R", 1},
 {"-1", "-1", "0", "-1", "-1", "E", "D", 1},
 {"-1", "0", "-1", "-1", "-1", "O", "G", 1},
 {"0", "-1", "-1", "-1", "-1", "N", "A", 1},
 {"-1", "-1", "-1", "0", "N", "S", "R", 4},
 {"-1", "0", "-1", "-1", "E", "O", "G", 4},
 {"-1", "-1", "0", "-1", "O", "E", "D", 4},
 {"1", "-1", "0", "-1", "S", "NE", "D", 3},
 {"1", "-1", "0", "-1", "O", "NE", "D", 3},
 {"0", "-1", "1", "-1", "S", "NE", "A", 3},
 {"0", "-1", "1", "-1", "O", "NE", "A", 3},
 {"0", "-1", "0", "-1", "S", "NE", "A", 2},
 {"0", "-1", "0", "-1", "O", "NE", "D", 2},
 {"-1", "-1", "0", "1", "N", "SE", "D", 3},
 {"-1", "-1", "0", "1", "O", "SE", "D", 3},
 {"-1", "-1", "1", "0", "N", "SE", "R", 3},
 {"-1", "-1", "1", "0", "O", "SE", "R", 3},
 {"-1", "-1", "0", "0", "N", "SE", "R", 2},
 {"-1", "-1", "0", "0", "O", "SE", "D", 2},
 {"0", "-1", "-1", "-1", "S", "NO", "A", 3},
 {"-1", "0", "-1", "-1", "E", "NO", "G", 3},
 {"1", "0", "-1", "-1", "S", "NO", "G", 3},
 {"0", "1", "-1", "-1", "E", "NO", "A", 3},
 {"1", "0", "-1", "-1", "S", "NO", "G", 2},
 {"0", "1", "-1", "-1", "E", "NO", "A", 2},
 {"-1", "0", "-1", "-1", "E", "SO", "G", 3},
 {"-1", "1", "-1", "0", "N", "SO", "R", 3},
 {"-1", "0", "-1", "1", "N", "SO", "G", 3},
 {"-1", "1", "-1", "0", "E", "SO", "R", 3},
 {"-1", "0", "-1", "-1", "E", "SO", "G", 2},
 {"-1", "-1", "0", "-1", "O", "E", "D", 2}
 };

    srand(time(NULL));

    char* cases[]={"0","1","-1"};
    char* sauveur[]={"N","S","E","O"};
    char* direct_animal[]={"NE","SE","E","O","SO","NO","S","N"};
    char* action[]={"A","R","G","D"};
    int  prio[]={1,2,3,4};
 
    int nombre_regles = sizeof(regles) / sizeof(Regle);
    int tableau_ind[282];
    int ligne,colonne;
    
    for(int i=0;i<282;i++){
        tableau_ind[i]=i;    
    }

    melangerTableau(tableau_ind,282);


    for (int k=0;k<15;k++){

        ligne=tableau_ind[k]/8;
        printf("ligne est %d\n",ligne);
        colonne=tableau_ind[k]%8;
        printf("colonne est %d\n",colonne);
       
        
        if ((colonne==0) || (colonne==1) ||(colonne==2) ||(colonne==3)){

              double score_pred=score (regles, nombre_regles);
              double score_1=0;

            for (int i = 0; i < 3; i++)
            {
                Regle* nouv_reg = modifi_Regle(regles,ligne, colonne,cases[i],nombre_regles);

                score_1= score (nouv_reg , nombre_regles);
                printf("le score est %f\n",score_1);

                if (score_1< score_pred)
                {
                    printf("le score pre est  %f  le score de i est %f",score_pred,score_1);
                   copierRegles(regles,nouv_reg,nombre_regles);
                   printf("%d\n",1);
                   score_pred = score_1 ;
                }
                
            }
            
        }else if (colonne==4){
             double score_pred=NUM_ANIMALS;
             double score_2=0;
           
            for (int i = 0; i < 4; i++)
            {
                Regle* nouv_reg=modifi_Regle(regles,ligne, colonne,sauveur[i],nombre_regles);

                score_2=score(nouv_reg,nombre_regles);

                if (score_2<score_pred)
                {
                    copierRegles(regles,nouv_reg,nombre_regles);
                    printf("%d\n",2);
                     score_pred = score_2 ;
                }
                
            }
            
        }else if (colonne==5){
               double score_pred=NUM_ANIMALS;
               double score_3=0;
               

            for (int i = 0; i < 8; i++)
            {
                Regle* nouv_reg=modifi_Regle(regles,ligne, colonne,direct_animal[i],nombre_regles);

                score_3=score(nouv_reg,nombre_regles);

                if (score_3<score_pred)
                {
                    copierRegles(regles,nouv_reg,nombre_regles);
                   printf("%d\n",3);
                    score_pred = score_3 ;
                }
                
            }

        }else if(colonne==6){
               double score_pred=NUM_ANIMALS;
               double score_4=0;

            for (int i = 0; i < 3; i++)
            {
                Regle* nouv_reg=modifi_Regle(regles,ligne, colonne,action[i],nombre_regles);

                score_4=score(nouv_reg,nombre_regles);

                if (score_4<score_pred)
                {
                   copierRegles(regles,nouv_reg,nombre_regles);
                  printf("%d\n",4);
                   score_pred = score_4 ;
                }
                
            }
        }else{
              double score_pred=NUM_ANIMALS;
              double score_5=0;

            for (int i = 0; i < 4; i++)
            {
                Regle* nouv_reg=modify_Regle(regles,ligne, colonne,prio[i],nombre_regles);

                score_5=score(nouv_reg,nombre_regles);

                if (score_5<score_pred)
                {
                   copierRegles(regles,nouv_reg,nombre_regles);
                   printf("%d\n",5);
                    score_pred = score_5 ;
                }
                
            }

        }
            
}
    Regle regles_finales[nombre_regles];
    copierRegles(regles_finales, regles, nombre_regles);
    // Affichage des règles générées
    for (int i = 0; i < nombre_regles; i++) {
      
    printf("{%s, %s, %s, %s, %s , %s , %s , %d}\n", regles_finales[i].case_haut ,regles_finales[i].case_gauche ,regles_finales[i].case_droite ,regles_finales[i].case_bas,
    regles_finales[i].sauveur_proche,regles_finales[i].animal_proche, regles_finales[i].action,regles_finales[i].priorite);
     
  }
}








       
     
       