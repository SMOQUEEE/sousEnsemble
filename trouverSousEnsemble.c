#include <stdio.h>
#include <limits.h>

#define N 7  // Taille des ensembles (7 bits)
#define K 6  // Nombre de sous-ensembles

void unionDesEnsembles(char *resultat, char *ensemble) {
    for (int i = 0; i < N; i++)
    {
        if (ensemble[i] == '1') 
        {
            resultat[i] = '1';  
        }
    }
}

// Fonction qui vérifie si une chaîne est "1111111"
int estEnsembleComplet(char *ensemble) {
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
int compterEtVerifierCombination(const char *combinaison, char ensembles[K][N + 1], int *indices) {
    char ensembleCombine[N + 1] = "0000000"; 
    ensembleCombine[N] = '\0';  

    int count = 0;  

    // On parcourt les ensembles
    for (int j = 0; j < K; j++) {
        // Vérifie si le j-ième caractère de la combinaison est '1'
        if (combinaison[j] == '1') {
            unionDesEnsembles(ensembleCombine, ensembles[j]);
            indices[count++] = j; 
        }
    }

    // Vérifie si l'ensemble combiné est complet
    if (estEnsembleComplet(ensembleCombine)) {
        return count;  
    }
    
    return INT_MAX;  // Retourne INT_MAX si la combinaison n'est pas complète
}

void trouverCombinationMinimale(char ensembles[K][N + 1]) {
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
        int count = compterEtVerifierCombination(combinaison, ensembles, indicesCourants);

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


int main() {
    // Définir les 6 sous-ensembles sous forme binaire
    char ensembles[K][N+1] = {
        "1001001",  // Ensemble 0
        "1001000",  // Ensemble 1
        "0000001",  // Ensemble 2
        "1110010",  // Ensemble 3
        "0110111",  // Ensemble 4
        "0000111"   // Ensemble 5
    };

    // Trouver et afficher la combinaison minimale qui donne exactement "1111111"
    trouverCombinationMinimale(ensembles);

    return 0;
}
