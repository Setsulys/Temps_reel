#include"niveau.h"

Niveau* malloc_Niveau (Coordonnees tailles){
    Niveau* tmp;
    unsigned int i;
    tmp = (Niveau*) malloc(sizeof(Niveau));
    if (NULL != tmp){
        tmp->taille.x = tailles.x;
        tmp->taille.y = tailles.y;

        tmp->objets = (Objet**) malloc(sizeof(Objet*) * tailles.x);
        for (i = 0; i < tailles.x ; i ++){
            tmp->objets[i] = (Objet*) malloc(sizeof(Objet) * tailles.y);
        }
        if (NULL != tmp->objets){
            for (i = 0; i < tailles.x; i ++){
                if (NULL != tmp->objets[i]){
                    tmp->objets[i]->type = VIDE;
                    tmp->objets[i]->donnee_suppl = NULL;
                }
            }
        }
        
        tmp->allure_perso = 250; /* en ms */
        tmp->depl_perso_autorise = true;

    }
    return tmp;

}

void free_Niveau(Niveau* niveau){/*Fonction qui bug */
    unsigned int i;
    if (NULL != niveau){
        for(i = 0; i < niveau->taille.y-1; i ++){
            printf("2\n");
            printf("%d\n", niveau->objets[i]->type);
            free(niveau->objets[i]);
            niveau->objets[i] = NULL;
        }
        printf("3\n");
        free(niveau->objets);
        niveau->objets = NULL;
        free(niveau);
        niveau = NULL;
    }
}

Niveau* niveau0(){
    unsigned int i,j;
    Coordonnees tailles;
    Niveau* niveau_zero;

    tailles.x = 10;
    tailles.y = 5;

    niveau_zero = malloc_Niveau(tailles);

    for (i = 0; i < tailles.x; i ++){
        for (j = 0; j < tailles.y; j ++){
            if ((i < 7 && j == 1) || (i == 8 && j > 0) ){
                niveau_zero->objets[i][j].type = MUR; 
            }
        }
    }
    niveau_zero->objets[0][0].type = LANCEUR;
    niveau_zero->objets[5][3].type = LANCEUR;

    niveau_zero->objets[0][tailles.y - 1].type = PERSONNAGE;
    niveau_zero->coo_perso.x = 0;
    niveau_zero->coo_perso.y = 4;
    
    niveau_zero->objets[tailles.x - 1][tailles.y - 1].type = DESTINATION;

    return niveau_zero;
}

void affiche_projectile(Niveau *niveau, unsigned int i, unsigned int j){
    Deplacement* depl;

    depl = (Deplacement*) niveau->objets[i][j].donnee_suppl;
    niveau->objets[i][j].donnee_suppl = depl;

    switch(depl->direction){
        case BAS:
            printf("v ");
            break;
        case HAUT:
            printf("^ ");
            break;
        case GAUCHE:
            printf("< ");
            break;
        case DROITE:
            printf("> ");
            break;
    }
}

void affiche_Niveau(Niveau * niveau){
    unsigned int i, j;
    assert(NULL != niveau);

    printf("\n");
    for (j = 0; j < niveau->taille.y; j ++){
        printf("\t\t\t\t");
        for (i = 0; i < niveau->taille.x; i ++){
            switch(niveau->objets[i][j].type){
                case VIDE:
                    printf(". ");
                    break;
                case LANCEUR:
                    printf("0 ");
                    break;
                case PERSONNAGE:
                    printf("P ");
                    break;
                case MUR:
                    printf("# ");
                    break;
                case DESTINATION:
                    printf("D ");
                    break;
                case PROJECTILE:
                    affiche_projectile(niveau, i, j);
                    break;
            }
        }
        printf("\n");
    }
    printf("\n");

}
