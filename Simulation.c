//
// Created by Monssif Errami on 06/07/2023.
//
//trouver l'emplacement des sauveurs


#define IT_MAX 50
#include "mapGenerator.h"


typedef struct {
    char * case_haut;
    char * case_gauche;
    char * case_droite;
    char * case_bas;
    char *  sauveur_proche;
    char * animal_proche;
} SituationActuelle;

void transformChartoInt(int *directions ,char* actions1 , char* actions2){


    if (strcmp(actions1,"A") ==0){
        directions[0] = 0;
    } else if (strcmp(actions1,"R") ==0) {
        directions[0] = 1;
    } else if (strcmp(actions1,"G") ==0) {
        directions[0] = 2;
    } else if (strcmp(actions1,"D") ==0) {
        directions[0] = 3;
    }

    if (strcmp(actions2,"A") ==0){
        directions[1] = 0;
    } else if (strcmp(actions2,"R") ==0) {
        directions[1] = 1;
    } else if (strcmp(actions2,"G") ==0) {
        directions[1] = 2;
    } else if (strcmp(actions2,"D") ==0) {
        directions[1] = 3;
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


Regle regles[] = {
        {"0", "-1", "-1", "-1", "S", "N", "A", 1},
        {"-1", "-1", "-1", "-1", "-1", "N", "A", 1},
        {"-1", "-1", "-1", "-1", "-1", "S", "R", 1},
        {"-1", "-1", "-1", "-1", "-1", "E", "D", 1},
        {"-1", "-1", "-1", "-1", "-1", "O", "G", 1},
        {"1", "0", "-1", "-1", "-1", "N", "G", 1},
        {"1", "-1", "0", "-1", "-1", "N", "D", 1},
        {"1", "-1", "-1", "0", "-1", "N", "R", 1},
        {"-1", "0", "-1", "1", "-1", "S", "G", 1},
        {"-1", "-1", "0", "1", "-1", "S", "D", 1},
        {"0", "-1", "-1", "1", "-1", "S", "A", 1},
        {"-1", "-1", "1", "0", "-1", "E", "R", 1},
        {"-1", "0", "1", "-1", "-1", "E", "G", 1},
        {"0", "-1", "1", "-1", "-1", "E", "A", 1},
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

int nombre_regles = sizeof(regles) / sizeof(Regle);
