#include <stdio.h>
#include <stdlib.h>

struct retour {
    int N;
    int K;
    char** tab;
};
typedef struct  retour retour;



retour extraction(FILE *entree)
{
    if (entree == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        retour  vip = {-1,-1,NULL};
        return vip;
    }

    // Lecture du premier ensemble (taille)
    char taille[100];  
    if (fgets(taille, sizeof(taille), entree) == NULL) {
        printf("Erreur de lecture du fichier.\n");
        retour  vip = {-1,-1,NULL};
        return vip;
    }
    
    int N = atoi(taille);
    // printf("La taille de l'ensemble de base est : %s qui est %d \n", taille, N);
    

    // Lecture du nombre de sous-ensembles
    char nbSE[100];  
    if (fgets(nbSE, sizeof(nbSE), entree) == NULL) {
        printf("Erreur de lecture du nombre de sous-ensembles.\n");
        retour  vip = {-1,-1,NULL};
        return vip;
    }
    int K = atoi(nbSE);
    // printf("Le nombre de sous-ensembles est : %s qui est %d", nbSE,K);    

   char **matrice = (char**) malloc(sizeof(char*) * K);
    for (int i = 0; i < K; i++) {
        matrice[i] = (char*) malloc(sizeof(char) * N);
    }
    
    int i,j;
    char a;
    // teste avec boucle for
    for(i = 0; i < K; i++)
    {
        for(j = 0; j < N ; j++)
        {
            a = fgetc(entree);
            matrice[i][j] = a;
            // printf(" * %c ", a);
               
        
        }
        fgetc(entree);
        // matrice[i][] = fgets(taille, sizeof(taille), entree);
        // printf("La taille de l'ensemble de base est : %s qui est %d \n", taille, N);
    }


    // aficche mat dim 2
    // printf("\n\n******************************\n\n");
    // for(i = 0; i < K; i++)
    // {
    //     for(j = 0; j < N ; j++)
    //     {
    //         printf(" - %c - ",matrice[i][j]);
    //     }
    //     printf("\n");
        
    // }

    retour val = {N,K,matrice};


    // Fermeture du fichier
    fclose(entree);

    return val;
}


void affichage(char ** m, int K, int N)
{
    int i,j;
    for(i = 0; i < K; i++)
    {
        for(j = 0; j < N ; j++)
        {
            printf(" - %c - ",m[i][j]);
        }
        printf("\n");
        
    }
}


int main()
{
    FILE *fichier = fopen("fichier.txt", "r");  
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }


    retour v = extraction(fichier);

    affichage(v.tab,v.K, v.N);

    return 0;
}
