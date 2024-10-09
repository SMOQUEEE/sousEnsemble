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
    // char ensembleCombine[N + 1] = "0000000"; 
    char * ensembleCombine = (char*) malloc(sizeof(char)*(N+1));
    
    int i;
    for(i = 0; i < N+1; i++)
    {
        ensembleCombine[i] = '0';
    }
     ensembleCombine[N] = '\0'; 


    int count = 0;  

    // On parcourt les ensembles
    for (int j = 0; j < K; j++) {
        // Vérifie si le j-ième caractère de la combinaison est '1'
        if (combinaison[j] == '1') {
            unionDesEnsembles(ensembleCombine, ensembles[j], N);
            indices[count++] = j; 
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

    // Parcours toutes les combinaisons possibles
    for (int i = 0; i < (1 << K); i++) {
        char combinaison[K + 1];  // Taille K + 1 pour le caractère nul
        int temp = i;

        // Générer la combinaison de manière simple
        for (int j = 0; j < K; j++) {
            combinaison[j] = (temp % 2 == 1) ? '1' : '0';  // Prendre le bit de poids faible
            temp /= 2;  // Décale temp vers la droite pour le prochain bit
        }
        combinaison[K] = '\0';  // Terminer la chaîne

        // Vérifier la combinaison
        int count = compterEtVerifierCombination(combinaison, ensembles, indicesCourants,N,K);

        // Mise à jour de la meilleure combinaison
        if (count < minCombination) {
            minCombination = count;
            for (int j = 0; j < count; j++) {
                meilleuresIndices[j] = indicesCourants[j]; 
            }
        }
    }

    // Afficher la meilleure combinaison
    if (minCombination < INT_MAX) {
        printf("La combinaison minimale qui donne 1111111 est : ");
        for (int i = 0; i < minCombination; i++) {
            printf("%d ", meilleuresIndices[i]);  
        }
        printf("\n");
    } else {
        printf("Aucune combinaison ne donne 1111111.\n");
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
