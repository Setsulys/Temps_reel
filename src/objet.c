#include"objet.h"


void traite_projectile(Niveau* niveau, Evenement e, Tas *tas){
    Deplacement* depl;
    depl = (Deplacement*) niveau->objets[e.coo_obj.x][e.coo_obj.y].donnee_suppl;
    switch(depl->direction){/*avancement des projectile avec verification que le projectile ne rencontre pas un mur ou les bords du niveau*/
        case HAUT:/*gestion du projectile haut*/
            if (e.coo_obj.y >= 1 && (niveau->objets[e.coo_obj.x][e.coo_obj.y - 1].type == VIDE 
                    || niveau->objets[e.coo_obj.x][e.coo_obj.y - 1].type == PERSONNAGE)){

                /* creation du nouveau projectile */
                niveau->objets[e.coo_obj.x][e.coo_obj.y - 1].type = PROJECTILE;
                /* recopiage de ses caracteristiques */
                niveau->objets[e.coo_obj.x][e.coo_obj.y - 1].donnee_suppl = depl;
                /* supression de l'encien objet */
                niveau->objets[e.coo_obj.x][e.coo_obj.y].type = VIDE;
                gestion_ev(tas,e,'H');
            }
            else /*if(niveau->objets[e.coo_obj.x][e.coo_obj.y + 1].type == MUR)*/{
                niveau->objets[e.coo_obj.x][e.coo_obj.y].type = VIDE;
            }
            break;
        case BAS:/*gestion du projectile bas*/
            if (e.coo_obj.y < niveau->taille.y && (niveau->objets[e.coo_obj.x][e.coo_obj.y + 1].type == VIDE
                    || niveau->objets[e.coo_obj.x][e.coo_obj.y + 1].type == PERSONNAGE)){
                
                /* creation du nouveau projectile */
                niveau->objets[e.coo_obj.x][e.coo_obj.y + 1].type = PROJECTILE;
                /* recopiage de ses caracteristiques */
                niveau->objets[e.coo_obj.x][e.coo_obj.y + 1].donnee_suppl = depl;
                /* supression de l'encien objet */
                niveau->objets[e.coo_obj.x][e.coo_obj.y].type = VIDE;
                gestion_ev(tas,e,'B');
            }
            else/* if(niveau->objets[e.coo_obj.x][e.coo_obj.y - 1].type == MUR)*/{
                niveau->objets[e.coo_obj.x][e.coo_obj.y].type = VIDE;
            }
            break;
        case DROITE:/*gestion du projectile droit*/
            if ((e.coo_obj.x < niveau->taille.x - 1) && (niveau->objets[e.coo_obj.x + 1][e.coo_obj.y].type == VIDE
                    || niveau->objets[e.coo_obj.x + 1][e.coo_obj.y].type == PERSONNAGE)){

                /* creation du nouveau projectile */
                niveau->objets[e.coo_obj.x + 1][e.coo_obj.y].type = PROJECTILE;
                /* recopiage de ses caracteristiques */
                niveau->objets[e.coo_obj.x + 1][e.coo_obj.y].donnee_suppl = depl;
                /* supression de l'encien objet */
                niveau->objets[e.coo_obj.x][e.coo_obj.y].type = VIDE;
                gestion_ev(tas,e,'D');
            }
            else/* if(niveau->objets[e.coo_obj.x + 1][e.coo_obj.y].type == MUR)*/{
                niveau->objets[e.coo_obj.x][e.coo_obj.y].type = VIDE;
            }
            break;
        case GAUCHE:/*gestion du projectile gauche*/
            if (e.coo_obj.x >= 1 && (niveau->objets[e.coo_obj.x - 1][e.coo_obj.y].type == VIDE
                    || niveau->objets[e.coo_obj.x - 1][e.coo_obj.y].type == PERSONNAGE)){

                /* creation du nouveau projectile */
                niveau->objets[e.coo_obj.x - 1][e.coo_obj.y].type = PROJECTILE;
                /* recopiage de ses caracteristiques */
                niveau->objets[e.coo_obj.x - 1][e.coo_obj.y].donnee_suppl = depl;
                /* supression de l'encien objet */
                niveau->objets[e.coo_obj.x][e.coo_obj.y].type = VIDE;
                gestion_ev(tas,e,'G');
            }
            else /*if(niveau->objets[e.coo_obj.x - 1][e.coo_obj.y].type == MUR)*/{
                niveau->objets[e.coo_obj.x][e.coo_obj.y].type = VIDE;
            }
            break;
        default:
            printf("HAUT\n");
            millisleep(1000);
            break;
    }

}

void gestion_donnee_suppl(Objet* obj, Direction dir) {
    /*caster donnee_suppl dans le format voulus et ajout des données demandé?*/
    Deplacement* depl;
    Generation* gen;
    switch (obj->type) {
        case PROJECTILE:
            depl = (Deplacement*) malloc(sizeof(Deplacement));
            if (NULL != depl){
                depl->direction = dir;
                depl->allure = 300;
                obj->donnee_suppl = depl;
            }
            break;
        case LANCEUR:
            gen = (Generation*) malloc(sizeof(Generation));
            if (NULL != gen){
                gen->intervalle = 1000;
                gen->allure_proj = 300;
                
                obj->donnee_suppl = gen;
            }
            break;
        default:
            obj->donnee_suppl = NULL;
            break;

    }
}

void traite_lanceur(Niveau* niveau, Evenement e, Tas* tas){
    /*Attribution des données supplémentaires aux projectiles*/
    Direction dir;
    Evenement new_ev;
    int verif = 0 ;
    if (e.coo_obj.x >= 1 && (niveau->objets[e.coo_obj.x - 1][e.coo_obj.y].type == VIDE
            || niveau->objets[e.coo_obj.x - 1][e.coo_obj.y].type == PERSONNAGE)){  /*gestion du projectile gauche*/

        niveau->objets[e.coo_obj.x - 1][e.coo_obj.y].type = PROJECTILE;
        dir = GAUCHE;
        gestion_donnee_suppl(&(niveau->objets[e.coo_obj.x - 1][e.coo_obj.y]), dir);
        /* ajout du projectile engendrer par le lanceur */
        new_ev.coo_obj.x = e.coo_obj.x - 1;
        new_ev.coo_obj.y = e.coo_obj.y;
        new_ev.moment = e.moment + 300;
        ajoute_evenement(tas, new_ev);
        verif = 1;
    }
    if ((e.coo_obj.x < niveau->taille.x - 1) && (niveau->objets[e.coo_obj.x + 1][e.coo_obj.y].type == VIDE
            || niveau->objets[e.coo_obj.x + 1][e.coo_obj.y].type == PERSONNAGE)){   /*gestion du projectile droit*/

        niveau->objets[e.coo_obj.x + 1][e.coo_obj.y].type = PROJECTILE;
        dir = DROITE;
        gestion_donnee_suppl(&(niveau->objets[e.coo_obj.x + 1][e.coo_obj.y]), dir);
        /* ajout du projectile engendrer par le lanceur */
        new_ev.coo_obj.x = e.coo_obj.x + 1;
        new_ev.coo_obj.y = e.coo_obj.y;
        new_ev.moment = e.moment + 300;
        ajoute_evenement(tas, new_ev);
        verif = 1;
    }
    if (e.coo_obj.y > 0 && (niveau->objets[e.coo_obj.x][e.coo_obj.y - 1].type == VIDE
            || niveau->objets[e.coo_obj.x][e.coo_obj.y - 1].type == PERSONNAGE)){  /*gestion du projectile haut*/

        niveau->objets[e.coo_obj.x][e.coo_obj.y - 1].type = PROJECTILE;
        dir = HAUT;
        gestion_donnee_suppl(&(niveau->objets[e.coo_obj.x][e.coo_obj.y - 1]), dir);
        /* ajout du projectile engendrer par le lanceur */
        new_ev.coo_obj.x = e.coo_obj.x;
        new_ev.coo_obj.y = e.coo_obj.y - 1;
        new_ev.moment = e.moment + 300;
        ajoute_evenement(tas, new_ev);
        verif = 1;
    }
    if (e.coo_obj.y < niveau->taille.y - 1 && (niveau->objets[e.coo_obj.x][e.coo_obj.y + 1].type == VIDE 
            || niveau->objets[e.coo_obj.x][e.coo_obj.y + 1].type == PERSONNAGE)){   /*gestion du projectile bas*/

        niveau->objets[e.coo_obj.x][e.coo_obj.y + 1].type = PROJECTILE;
        dir = BAS;
        gestion_donnee_suppl(&(niveau->objets[e.coo_obj.x][e.coo_obj.y + 1]), dir);
        /* ajout du projectile engendrer par le lanceur */
        new_ev.coo_obj.x = e.coo_obj.x;
        new_ev.coo_obj.y = e.coo_obj.y + 1;
        new_ev.moment = e.moment + 300;
        ajoute_evenement(tas, new_ev);
        verif = 1;
    }
    if(1 == verif){ /*s'il passe dans un des boucles il faut cree le prochaine lanceur */
        /* ajout du prochain lanceur */
        e.moment += 1000;
        ajoute_evenement(tas, e); 
    }
    
}

int traite_personnage(Niveau* niveau, clock_t *intervalle){
    unsigned perso_x, perso_y;
    int touche = 0;
    if (niveau->depl_perso_autorise != true){ /* test si le deplacement est autorise pour le personnage */
        return 0;
    }
    touche = capte_touche();
    if (touche == 0){
        return 0;
    }
    
    perso_x = niveau->coo_perso.x;
    perso_y = niveau->coo_perso.y;
    switch(touche){
        case 'z':
            if (perso_y > 0 && (niveau->objets[perso_x][perso_y - 1].type != MUR && niveau->objets[perso_x][perso_y - 1].type != LANCEUR)){
                if (niveau->objets[perso_x][perso_y - 1].type == DESTINATION){
                    return 10; /* le personnage arrive a destination */
                }
                else{
                    /* creation du nouveau personnage */
                    niveau->objets[perso_x][perso_y - 1].type = PERSONNAGE; 
                    /* supression de l'encien objet */
                    niveau->objets[perso_x][perso_y].type = VIDE;   
                    /* mise a jour du niveau */
                    niveau->depl_perso_autorise = false;
                    niveau->coo_perso.y --;
                    *intervalle = maintenant() / une_milliseconde;
                    return 0;
                }
            }
            break;
        case 'q':
            if (perso_x > 0 && (niveau->objets[perso_x - 1][perso_y].type != MUR && niveau->objets[perso_x - 1][perso_y].type != LANCEUR)){
                if (niveau->objets[perso_x - 1][perso_y].type == DESTINATION){
                    return 10; /* le personnage arrive a destination */
                }
                else{
                    /* creation du nouveau personnage */
                    niveau->objets[perso_x - 1][perso_y].type = PERSONNAGE;
                    /* supression de l'encien objet */
                    niveau->objets[perso_x][perso_y].type = VIDE;
                    niveau->depl_perso_autorise = false;
                    /* mise a jour du niveau */
                    niveau->coo_perso.x --;
                    *intervalle = maintenant() / une_milliseconde;
                    return 0;
                }
            }
            break;
        case 's':
            if (perso_y < niveau->taille.y - 1 && (niveau->objets[perso_x][perso_y + 1].type != MUR && niveau->objets[perso_x][perso_y + 1].type != LANCEUR)){
                if (niveau->objets[perso_x][perso_y + 1].type == DESTINATION){
                    return 10; /* le personnage arrive a destination */
                }
                else{
                    /* creation du nouveau personnage */
                    niveau->objets[perso_x][perso_y + 1].type = PERSONNAGE;
                    /* supression de l'encien objet */
                    niveau->objets[perso_x][perso_y].type = VIDE;
                    /* mise a jour du niveau */
                    niveau->depl_perso_autorise = false;
                    niveau->coo_perso.y ++;
                    *intervalle = maintenant() / une_milliseconde;  
                    return 0; 
                }

            }
            break;
        case 'd':
            if (perso_x < niveau->taille.x - 1 && (niveau->objets[perso_x + 1][perso_y].type != MUR && niveau->objets[perso_x + 1][perso_y].type != LANCEUR)){
                if (niveau->objets[perso_x + 1][perso_y].type == DESTINATION){
                    return 10; /* le personnage arrive a destination */
                }
                else{
                    /* creation du nouveau personnage */
                    niveau->objets[perso_x + 1][perso_y].type = PERSONNAGE;
                    /* supression de l'encien objet */
                    niveau->objets[perso_x][perso_y].type = VIDE;
                    /* mise a jour du niveau */
                    niveau->depl_perso_autorise = false;
                    niveau->coo_perso.x ++;
                    *intervalle = maintenant() / une_milliseconde;
                    return 0;
                }
            }
            break;
        default:
                return 0;
            break;
    }
    return 0;
}

