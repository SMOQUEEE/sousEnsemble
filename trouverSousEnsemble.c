#include <stdio.h>
#include <stdlib.h>
#include <limits.h>



struct retour {
    int N;
    int K;
    char** tab;
};
typedef struct  retour retour;



void unionDesEnsembles(char *resultat, char *ensemble, int N) {
    // On additionnne un ensemble existant à un entre ensemble contenant N éléments
    for (int i = 0; i < N; i++)
    {
        if (ensemble[i] == '1') 
        {
            resultat[i] = '1';  
        }
    }
}

// Fonction qui vérifie si une chaîne est "1111111"
int estEnsembleComplet(char *ensemble,int N) {
    for (int i = 0; i < N; i++) 
    {
        if (ensemble[i] != '1') 
        {
            return 0; 
        }
    }
    return 1;  
}

// Fonction qui effectue l'union de plusieurs ensembles et vérifie si le résultat est "1111111"
int compterEtVerifierCombination(const char *combinaison, char** ensembles, int *indices, int N, int K) {
    // On initialise une chaine de caractère contenant que des 0"; 
    char * ensembleCombine = (char*) malloc(sizeof(char)*(N+1));
    int i;
    for(i = 0; i < N+1; i++)
    {
        ensembleCombine[i] = '0';
    }
     ensembleCombine[N] = '\0'; 


    int count = 0;  

    // On parcourt les ensembles et nous les combinons
    for (int j = 0; j < K; j++) {
        if (combinaison[j] == '1') {
            unionDesEnsembles(ensembleCombine, ensembles[j], N);
            indices[count++] = j; // On incremente le nombre d'opération et l'ajoutant dans la liste
        }
    }

    // Vérifie si l'ensemble combiné est complet
    if (estEnsembleComplet(ensembleCombine,N)) {
        return count;  
    }
    
    return INT_MAX;  // Retourne INT_MAX si la combinaison n'est pas complète
}

void trouverCombinationMinimale(char ** ensembles, int N, int K) {
    int minCombination = INT_MAX;  
    int meilleuresIndices[K];  
    int indicesCourants[K];  

    // Parcours toutes les combinaisons possibles (1 << K) reprèsente 2 puissance k
    for (int i = 0; i < (1 << K); i++) {
        char combinaison[K + 1];  
        int temp = i;
    

        for (int j = 0; j < K; j++) {
            if(temp%2 == 0) 
            {
                combinaison[j] = '1';
            }
            else combinaison[j] = '0';
            temp /= 2;  
        }
        combinaison[K] = '\0'; 


        // On vérifie si la combinaison est complète : Si elle donne que de "11111..."

        int count = compterEtVerifierCombination(combinaison, ensembles, indicesCourants,N,K);
        
        // Si la combinaison est plus courte que la meilleure, on la stocke et on met à jour les indices de la meilleure combinaison.
        if (count < minCombination) {
            minCombination = count;
            for (int j = 0; j < count; j++) {
                meilleuresIndices[j] = indicesCourants[j]; 
            }
        }
    }

    // On vérifie s'il existe une combinaison complète et nous l'affichons
    if (minCombination < INT_MAX) {
        printf("La combinaison minimale qui nous donne un ensemble complet est : ");
        for (int i = 0; i < minCombination; i++) {
            printf("%d ", meilleuresIndices[i]);  
        }
        printf("\n");
    } 
    // Si il en existe aucune on affiche ce message:
    else {
        printf("Aucune combinaison ne nous donne un ensemble complet.\n");
    }
}




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
        
        }
        fgetc(entree);
    }


   

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




int main() {
    // Définir les 6 sous-ensembles sous forme binaire
    // char ensembles[K][N+1] = {
    //     "1001001",  // Ensemble 0
    //     "1001000",  // Ensemble 1
    //     "0000001",  // Ensemble 2
    //     "1110010",  // Ensemble 3
    //     "0110111",  // Ensemble 4
    //     "0000111"   // Ensemble 5
    // };
    
    FILE *fichier = fopen("fichier.txt", "r");  
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }


    retour v = extraction(fichier);


    // affichage(v.tab,v.K, v.N);
    int N = v.N ;
    int K = v.K;
    char **ensembles = (char**) malloc(sizeof(char*) * K);
    for (int i = 0; i < K; i++) {
        ensembles[i] = (char*) malloc(sizeof(char) * N);
        ensembles[i] = v.tab[i];
    }
    // char ensembles[K][N + 1] = v.tab;
    affichage(ensembles,K,N);

    // Trouver et afficher la combinaison minimale qui donne exactement "1111111"
    trouverCombinationMinimale(ensembles,N, K);

    return 0;
}
