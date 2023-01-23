#include"tas.h"

Tas* malloc_Tas(unsigned capacite_initiale){
    Tas* tmp;
    Evenement* even = NULL;

    tmp = (Tas*) malloc(sizeof(Tas));
    if(NULL!= tmp){
        even = (Evenement*) malloc(sizeof(Evenement) * capacite_initiale);
        if (NULL != even){
            tmp->valeurs = even;
        }
        tmp->taille = 0;
        tmp->capacite = capacite_initiale;
    }
    return tmp;
}

void free_Tas(Tas* tas){
    if (NULL != tas){
        free(tas->valeurs);
        tas->valeurs = NULL;
        free(tas);
        tas = NULL;
    }
}

void trier_tas_croissant(Tas *tas){
    int i;
    Evenement a;
    for(i = 0;(unsigned long) i < tas->taille - 1; i ++){
        if(tas->valeurs[i].moment > tas->valeurs[i + 1].moment){
            a = tas->valeurs[i];
            tas->valeurs[i] = tas->valeurs[i + 1];
            tas->valeurs[i + 1] = a;
        }

    }
}

void affiche_tas_ev(Tas tas){
    unsigned int i;
    printf("[");
    for (i = 0; i < tas.capacite; i ++){
        printf("%ld,", tas.valeurs[i].moment);
    }
    printf("]\n");
}

Tas* construit_Tas(Niveau* niveau){
    Tas* tmp;
    int iter;
    unsigned int i,j;
    
    tmp = malloc_Tas(TAILLE_MAX);

    if (NULL != tmp){
        iter = 0;
        for(i = 0; i < niveau->taille.x; i++){
            for(j = 0; j < niveau->taille.y; j++){
                if(LANCEUR == niveau->objets[i][j].type ){ /* ajout des lanceur de depart dans le tas */
                    tmp->valeurs[iter].moment = 1000;
                    tmp->valeurs[iter].coo_obj.x = i;
                    tmp->valeurs[iter].coo_obj.y = j;
                    iter ++;
                    tmp->taille ++;
                }
            }
        }
    }

    return tmp;
}

void affiche_Tas(Tas tas){
    unsigned int i;
    printf("tas.taille = %d\n\n", tas.taille);
    for (i = 0; i < tas.taille; i ++){
        
        printf("tas.valeur[i].moment = %ld\n", tas.valeurs[i].moment);
        printf("tas.valeurs.coo_obj = (%d,%d)\n",tas.valeurs[i].coo_obj.x, tas.valeurs[i].coo_obj.y);
        printf("_________________________________________\n");
    }
}

