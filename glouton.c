#include <stdio.h>
#include <stdlib.h>



//ddljdndjn

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

int nbElementDansSS(char * tab, int taille)
{
    int i;
    int cpt = 0;
    for(i = 0; i < taille; i++)
    {
        if(tab[i]== '1')
        {
            cpt++;
        }
    }
    return cpt;
}


char ** enleverElementDansTab(char ** tab, int lgn, int K)
{
    int i;
    tab[lgn] = NULL;

    for(i = lgn; i < K-1; i++)
    {
        tab[i] = tab[i+1];
    }
     tab[K-1] = NULL;
    return tab;

}


int estComplet(char ** sousEnsemble,int col, int lgn)
{
    int i,j;
   
    for(i = 0; i < col; i++)
    {
        int p = 0;
        for(j = 0; j< lgn; j++)
        {
            if (sousEnsemble[j][i] == '1') p=1;
        }

        if(p != 1) return 0;
    }
    return 1;
}


char ** recopieTableau(char ** tab, int N, int K) 
{
    int i,j;
    char **copie = (char**)  malloc(sizeof(char*)*K);
    for(i = 0; i < K; i++)
    {
        copie[i] = (char*) malloc(sizeof(char)* N);
    }

    for(i = 0; i < K ; i++)
    {
       copie[i] = tab[i];
        
    }

    return copie;

}


void recette(char ** tb,int N, int K)
{

    int i,j;
    char ** tableau = recopieTableau(tb,N,K);
    int Kcopie = K; // nombre de sous ensemble 

    char ** sousEnsemble = (char**)  malloc(sizeof(char*)*K); //k ss max 
    for(i = 0; i < K; i++)
    {
        sousEnsemble[i] = (char*) malloc(sizeof(char)* N);
    }

    int SScol = N; // nombre de colonne dans tab glouton (taille)
    int SSlgn = 0; // nombre de ligne dans tab glouton
    int cpt;
    int maxElement = 0;
    int ligneMax = -1;

    while (!estComplet(sousEnsemble,SScol,SSlgn) && SSlgn < K)
    {
        for(i = 0; i < Kcopie; i++)
        {
            cpt = nbElementDansSS(tableau[i],N);
            
            if(cpt > maxElement)
            {
                maxElement = cpt;
                ligneMax = i;
            }
        }

        if(ligneMax == -1) {
            // Aucun sous-ensemble supplémentaire ne couvre de nouveaux éléments
            break;  
        }

        // copie des elements dans le tableu ss 
        for(j = 0; j < N; j++) {
            sousEnsemble[SSlgn][j] = tableau[ligneMax][j];
        }
        SSlgn++;

        // retirer l'ensemble du tab
        enleverElementDansTab(tableau,ligneMax,Kcopie);
        Kcopie--;

        // reinitialisation pour effectuer de nouv teste dans ;a boucle while 
        maxElement = 0;
        ligneMax = -1;
    }

    if (!estComplet(sousEnsemble, N, SSlgn))
    {
        printf("Aucune combinaison ne couvre tous les éléments.\n");
    }
    else
    {
        printf("La combinaison glouton est valide pour :\n");
        affichage(sousEnsemble, SSlgn, N);
    }


    // liberation memoire 
    for (i = 0; i < Kcopie; i++) {
        free(tableau[i]);
    }
    free(tableau);
    free(sousEnsemble);

}

int main()
{
    FILE *fichier = fopen("fichier2.txt", "r");  
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }


    retour v = extraction(fichier);
    int N = v.N ; // nombre element
    int K = v.K; // nombre de ss
    recette(v.tab,N,K);



    return 0;

}
