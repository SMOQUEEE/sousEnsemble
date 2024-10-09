#include <stdio.h>
#include <stdlib.h>

void extraction(FILE *entree)
{
    if (entree == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    // Lecture du premier ensemble (taille)
    char taille[100];  
    if (fgets(taille, sizeof(taille), entree) == NULL) {
        printf("Erreur de lecture du fichier.\n");
        return;
    }
    
    int N = atoi(taille);
    // printf("La taille de l'ensemble de base est : %s qui est %d \n", taille, N);
    

    // Lecture du nombre de sous-ensembles
    char nbSE[100];  
    if (fgets(nbSE, sizeof(nbSE), entree) == NULL) {
        printf("Erreur de lecture du nombre de sous-ensembles.\n");
        return;
    }
    int K = atoi(nbSE);
    // printf("Le nombre de sous-ensembles est : %s qui est %d", nbSE,K);    

    char matrice[K][N];
    int i,j;
    char a;
    // teste avec boucle for
    for(i = 0; i < K; i++)
    {
        for(j = 0; j < N ; j++)
        {
            a = fgetc(entree);
            matrice[i][j] = a;
            printf(" * %c ", a);
               
        
        }
        fgetc(entree);
        // matrice[i][] = fgets(taille, sizeof(taille), entree);
        // printf("La taille de l'ensemble de base est : %s qui est %d \n", taille, N);
    }


    // aficche mat dim 2
    printf("\n\n******************************\n\n");
    for(i = 0; i < K; i++)
    {
        for(j = 0; j < N ; j++)
        {
            printf(" - %c - ",matrice[i][j]);
        }
        printf("\n");
        
    }

    // Fermeture du fichier
    fclose(entree);
}


int main()
{
    FILE *fichier = fopen("fichier.txt", "r");  
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    extraction(fichier);  

    return 0;
}
