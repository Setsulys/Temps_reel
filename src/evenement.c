#include"evenement.h"

bool un_evenement_est_pret(Tas* tas){
    if (maintenant() >= tas->valeurs->moment){
        return true;
    }
    return false;
}

Evenement ote_minimum(Tas* tas){
    Evenement min;
    Evenement dernier = tas->valeurs[tas->taille - 1];
    assert(NULL != tas);
    
    /* Extraction du min */
    min = tas->valeurs[0];
    
    /* On échange le dernier élément et le premier */
    if (tas->taille > 1){
        tas->valeurs[0] = dernier;
        tas->valeurs[tas->taille - 1] = min;
        tas->taille --;
    }
    trier_tas_croissant(tas);  
    return min;
}

void ajoute_evenement(Tas* tas, Evenement n){
    assert(NULL != tas);
    /*agrandissement de la taille du tas*/
    tas->taille ++;

    /* gestion de la capacite maximale du tableau dynamique valeurs */
    if (tas->capacite <= tas->taille){
        tas->capacite *= 2;
        tas->valeurs = (Evenement*) realloc(tas->valeurs, sizeof(Evenement) * tas->capacite);
    }
    /* ajout de l'evenement au tas */
    tas->valeurs[tas->taille - 1] = n;
    trier_tas_croissant(tas);
}

void donnees_supl_projectile(Evenement e, Niveau *niveau){
    Deplacement* depl;
    if (niveau->taille.x > e.coo_obj.x + 1 && niveau->objets[e.coo_obj.x + 1][e.coo_obj.y].type == PROJECTILE){
        /* verification des données de projectile*//*coordonnées de lanceur renvoye une segfault */
        depl = (Deplacement*) niveau->objets[e.coo_obj.x + 1][e.coo_obj.y].donnee_suppl;
        niveau->objets[e.coo_obj.x + 1][e.coo_obj.y].donnee_suppl = depl;
    }
    if (niveau->taille.x > e.coo_obj.x - 1 && niveau->objets[e.coo_obj.x - 1][e.coo_obj.y].type == PROJECTILE){
        /* verification des données de projectile*//*coordonnées de lanceur renvoye une segfault */
        depl = (Deplacement*) niveau->objets[e.coo_obj.x - 1][e.coo_obj.y].donnee_suppl;
        niveau->objets[e.coo_obj.x - 1][e.coo_obj.y].donnee_suppl = depl;
    }
    if (niveau->taille.y > e.coo_obj.y + 1 && niveau->objets[e.coo_obj.x][e.coo_obj.y + 1].type == PROJECTILE){
        /* verification des données de projectile*//*coordonnées de lanceur renvoye une segfault */
        depl = (Deplacement*) niveau->objets[e.coo_obj.x][e.coo_obj.y + 1].donnee_suppl;
        niveau->objets[e.coo_obj.x][e.coo_obj.y + 1].donnee_suppl = depl;
    }
    if (niveau->taille.y > e.coo_obj.y - 1 && niveau->objets[e.coo_obj.x][e.coo_obj.y - 1].type == PROJECTILE){
        /* verification des données de projectile*//*coordonnées de lanceur renvoye une segfault */
        depl = (Deplacement*) niveau->objets[e.coo_obj.x][e.coo_obj.y - 1].donnee_suppl;
        niveau->objets[e.coo_obj.x][e.coo_obj.y - 1].donnee_suppl = depl;
    }
}

Deplacement traite_evenement(Evenement e, Tas* tas, Niveau* niveau){
    Objet obj;
    Deplacement* depl;
    obj = niveau->objets[e.coo_obj.x][e.coo_obj.y];
    switch(obj.type){
        case LANCEUR:
            traite_lanceur(niveau, e, tas);
            donnees_supl_projectile(e, niveau);
            break;
        case PROJECTILE:
            depl = (Deplacement*) niveau->objets[e.coo_obj.x][e.coo_obj.y].donnee_suppl;/* verification des données de projectile*//*coordonnées de lanceur renvoye une segfault */
            traite_projectile(niveau, e, tas);
            depl = (Deplacement*) niveau->objets[e.coo_obj.x][e.coo_obj.y].donnee_suppl;
            break;
        default:
            break;
    }
    return *depl;
}

int evenement_en_cour(Evenement e, Tas tas){
    if (e.moment == tas.valeurs[0].moment){
        return 1;
    }
    return 0;
}

void gestion_ev(Tas* tas, Evenement e, char directionc){
    Evenement tmp;

    tmp.coo_obj = e.coo_obj;
    tmp.moment = e.moment;
    switch (directionc){
        case 'H':
            tmp.coo_obj.y --;
            break;
        case 'B': 
            tmp.coo_obj.y ++;
            break;
        case 'G':
            tmp.coo_obj.x --;
            break;
        case 'D':
            tmp.coo_obj.x ++;
            break;
    }
    tmp.moment += 300;

    ajoute_evenement(tas, tmp);

}

int capte_touche(){
    int touche = 0;

    touche = getchar();
    touche = tolower(touche);

    if (touche == 'z' || touche == 'q' || touche == 's' || touche == 'd'){
        return touche;
    }
    return 0;
}

void depl_autorise(Niveau *niveau, clock_t depl){
    if (depl == 0){
        return;
    }
    if(((maintenant() / 1000) - depl) >= niveau->allure_perso){
        niveau->depl_perso_autorise = true;
    }
}

int verif_partie(Niveau niveau){
    if (niveau.objets[niveau.coo_perso.x][niveau.coo_perso.y].type != PERSONNAGE){
        printf("Vous avez perdu\nvous etes nul\nréessayez!\n\n");
        return -1;  /*partie perdu */
    }
    if (niveau.objets[niveau.coo_perso.x][niveau.coo_perso.y].type != DESTINATION)
        return 1;
    return 0;
}

void affiche_victoire(){
    printf("Bravo Vous etes arrivé·e à destination!!! \n");
    printf("Vous avez reussi ce Niveau!!!!!\n");
    printf("Vous etes trop fort!!\n\n");
}