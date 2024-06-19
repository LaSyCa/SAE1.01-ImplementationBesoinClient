/**
 * 
 * \author Juline Guyomard
 * 
 * \version 1.0
 * 
 * \date  26 novembre 2021
 * 
 * \brief Programme pour jouer au sudoku.
 * 
 * Ce programme contient plusieurs fonctions et procédures dans le but de jouer au sudoku dans la console.
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*****************************************************
 *           DECLARATION DES CONSTANTES              *
*****************************************************/

/**
 * \def TAILLE
 * 
 * \brief constante pour la taille d'un tableau.
*/
#define TAILLE 9

/**
 * 
 * \typedef tGrille 
 * 
 * \brief type tableau a 2 dimensions de TAILLE entiers
 * 
 * Le type tGrille sert à 
*/
typedef int tGrille[TAILLE][TAILLE] ;

/**
 * \def N
 * 
 * \brief constante pour changer la taille du sudoku, avoir une grille de 3x3 ou 2x2...
*/
const int N = 3;

/*****************************************************
 *       DECLARATIONS DES FONCTIONS/PROCEDURES       *
*****************************************************/

void chargerGrille(tGrille g);

void afficherGrille(tGrille grille1);

void saisir(int *valeur);

bool termine(tGrille grille1);

bool possible(tGrille grille1, int numLigne, int numColonne, int valeur);

/*****************************************************
 *              PROGRAMME PRINCIPAL                  *
*****************************************************/

/**
 * 
 * \fn int main()
 * 
 * \brief Entrée du programme
 *  
 * \return EXIT_SUCCESS Arrêt du programme.
*/
int main(){ 
    tGrille grille1; /** \var grille1 : la grille de jeu du sudoku. */
    int numLigne; /** \var numLigne : entier, correspond au numéro de ligne. */
    int numColonne; /** \var numColonne : entier, correspond au numéro de colonne. */
    int valeur ; /** \var valeur : la valeur à insérer dans la grille. */
    chargerGrille(grille1);
    while (termine(grille1) == false){
        afficherGrille(grille1);
        printf("Indices de la case ? : \n");
        saisir(&numLigne);
        saisir(&numColonne);
        if (grille1[numLigne-1][numColonne-1] !=0){
            printf("IMPOSSIBLE, la case n'est pas libre.\n");
        }
        else{
            printf("Valeur à insérer ?:\n");
            saisir(&valeur);

            if (possible(grille1, numLigne, numColonne, valeur)){
                grille1[numLigne-1][numColonne-1] = valeur;
            }
        }  
    }
    afficherGrille(grille1);
    printf("Grille pleine, fin de partie\n");
    
    return EXIT_SUCCESS ; 
}

/*****************************************************
 *      DEFINITION DES FONCTIONS ET PROCEDURES       *
*****************************************************/
/**
 * 
 * \fn bool termine(tGrille grille1)
 * 
 * \brief Fonction qui indique si la grille est fini.
 * 
 * \param grille1 : la grille de jeu du sudoku
 * 
 * \return true si la grille est complète, fini et false sinon.
 * 
 * Consiste à vérifier que la grille n'est pas pleine avant de continuer à jouer.
*/
bool termine(tGrille grille1){
    int ligne; /** \var ligne : entier, correspond au numéro de ligne. */
    int colonne;  /** \var colonne : entier, correspond au numéro de colonne. */
    int compt;  /** \var compt : initialiser a zéro, il compte le nombre de 0. */
    bool res;
    res = false;
    compt = 0;
    for (ligne = 0 ; ligne < TAILLE; ligne++){
        for (colonne = 0 ; colonne < TAILLE; colonne++){
            if (grille1[ligne][colonne] == 0)
            {
                compt++;
            }
            
        }
    }

    if (compt == 0)
    {
        res = true;
    }
    
    return res;
}
/**
 * 
 * \fn void chargerGrille(tGrille g)
 * 
 * \brief Procédure qui permet de charger la grille d'un sudoku.
 * 
 * \param g : la grille de jeu du sudoku
 * 
 * Consiste à charger en mémoire la grille du sudoku  existante à partir d'un fichier dont le nom est lue au clavier.
*/
void chargerGrille(tGrille g){
    char nomFichier[30];
    FILE * f;
    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
    if (f==NULL){
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    } else {
        fread(g, sizeof(int), TAILLE*TAILLE, f);
    }
    fclose(f);
}
/**
 * 
 * \fn void afficherGrille(tGrille g)
 * 
 * \brief Procédure qui permet d'afficher la grille d'un sudoku.
 * 
 * \param grille1 : la grille de jeu du sudoku
 * 
 * Consiste à afficher à l'écran de la grille et de son contenu au début et à chaque étape du jeu.
*/
void afficherGrille(tGrille grille1){
    int i; 
    int j;
    printf("    1  2  3   4  5  6   7  8  9\n");
    printf("  +---------+---------+---------+\n");
    for (i = 0; i < TAILLE; i++){


        printf("%d |", i+1);
        
        for (j = 0; j < TAILLE; j++){
            if (grille1[i][j]==0){
                printf(" . ");
            }
            else{
                printf(" %d ", grille1[i][j]);
            }

            if ( (j+1) % 3 == 0){
                printf("|");
            }
            
            
        }

        printf("\n");
        if ( (i+1) % 3 == 0){
            printf("  +---------+---------+---------+\n");
        }
        
    }

    
}
/**
 * 
 * \fn void saisir(int *valeur)
 * 
 * \brief Procédure qui permet de saisir un numéro de ligne, de colonne et une valeur à insérer dans la grille d'un sudoku.
 * 
 * \param valeur : la valeur lue, entier compris entre 1 et n²
 * 
 * Consiste à lire au clavier une valeur, la sasie se répète tant que la valeur n'est pas valide. La valeur doit être un entier, et compris entre 1 et n².
*/
void saisir(int *valeur) {
    char chaine[49]; 
    int val; 
    bool correct = false;
    do
    {
        scanf("%s", chaine);
        if (sscanf(chaine, "%d", &val) != 0){
            *valeur = val;
            if(val > 0 && val < TAILLE+1){
                *valeur = val;
                correct = true;
            }
            else{
                printf("La valeur doit etre comprise en 1 et %d borne incluse.\n", TAILLE);
            }
        }
        else {
            printf("Vous devez saisir un entier.\n");
        }

    } while (correct != true); 
}


/**
 * 
 * \fn possible(tGrille grille1, int numLigne, int numColonne, int valeur)
 * 
 * \brief Fonction qui indique si la valeur peut-être ajouté dans une case de la grille.
 * 
 * \param grille1 : la grille de jeu du sudoku
 * \param numLigne : entier, correspond au numéro de ligne de la case visé
 * \param numColonne : entier, correspond au numéro de colonne de la case visé
 * \param valeur : la valeur à insérer dans la grille
 * 
 * \return true si la valeur peut-être ajouté et false sinon.
 * 
 * Consiste à vérifier que la valeur n’est pas déjà présente sur la même ligne, sur la même colonne et dans le même bloc que la case.
*/
bool possible(tGrille grille1, int numLigne, int numColonne, int valeur){
    bool res;
    res = true;
    int i,j;
    for(i=0;i<TAILLE;i++){
        if(valeur == grille1[numLigne-1][i]){
            printf("Il y a déjà la valeur dans la ligne\n");
            res = false;
        }
    }
    
    for(j=0;j<TAILLE;j++){
        if (valeur==grille1[j][numColonne-1]){
            printf("Il y a déjà la valeur dans la colonne\n");
            res = false;
        }
    }
    
    while (numLigne%3!=0){
        numLigne ++;
    }
    while (numColonne%3!=0){
        numColonne ++;
    }

    for (i = numLigne-1; i > numLigne-4 ; i--){
        for (j = numColonne-1; j > numColonne-4 ; j--){
            if (grille1[i][j] == valeur){
                printf("La valeur est déja présente dans la case.\n");
                res = false;
            }
        }
    }
    return res;
}
