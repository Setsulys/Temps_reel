#include"graphique.h"


void affichetemps(clock_t debut){
    MLV_draw_text((WIDTH / 20) * 18, (HEIGHT / 6), "timer : %d", MLV_COLOR_RED, (maintenant() / une_milliseconde)- debut);
}

void affiche_projectileMLV(Niveau *niveau, unsigned int i, unsigned int j, const MLV_Image *Proj_D, const MLV_Image *Proj_G, const MLV_Image  *Proj_H, const MLV_Image *Proj_B){
    Deplacement* depl;

    depl = (Deplacement*) niveau->objets[i][j].donnee_suppl;
    niveau->objets[i][j].donnee_suppl = depl;

    switch(depl->direction){
        case BAS:
            MLV_draw_image(Proj_B, ((WIDTH/19)*i)  + 15 + CENTERX, (HEIGHT/10)*j + 12);
            break;
        case HAUT:
            MLV_draw_image(Proj_H, ((WIDTH/19)*i)  + 15 + CENTERX, (HEIGHT/10)*j + 12);
            break;
        case GAUCHE:
            MLV_draw_image(Proj_G, ((WIDTH/19)*i) + 15 + CENTERX, (HEIGHT/10)*j + 12);
            break;
        case DROITE:
            MLV_draw_image(Proj_D, ((WIDTH/19)*i)  + 15 + CENTERX, (HEIGHT/10)*j + 12);
            break;
    }
}

void dessinemlv(Niveau*niveau, const MLV_Image *Vide, const MLV_Image *Mur, const MLV_Image *Arrive, const MLV_Image *Token, const MLV_Image *Lanceur, const MLV_Image *Proj_D, const MLV_Image *Proj_G, const MLV_Image *Proj_H, const MLV_Image *Proj_B){
	unsigned int i =  0, j =  0;

	for (j = 0; j < niveau->taille.y; j ++){
        for (i = 0; i < niveau->taille.x; i ++){
            switch(niveau->objets[i][j].type){
            	case VIDE:
                    MLV_draw_image(Vide, ((WIDTH / 19) * i) + 15 + CENTERX , (HEIGHT / 10) * j + 12);
                    break;
                case LANCEUR:
                    MLV_draw_image(Lanceur, ((WIDTH / 19) * i) + 15 + CENTERX, (HEIGHT / 10) * j + 12);
                    break;
                case PERSONNAGE:
                    MLV_draw_image(Token, ((WIDTH / 19) * i)  + 15 + CENTERX, (HEIGHT / 10) * j + 12);
                    break;
                case MUR:
                    MLV_draw_image(Mur, i * (WIDTH / 19)+ 15 + CENTERX, (HEIGHT / 10) * j + 12);
                    break;
                case DESTINATION:
                    MLV_draw_image(Arrive, i * (WIDTH / 19) + 15 + CENTERX, (HEIGHT / 10) * j + 12);
                    break;
                case PROJECTILE:
                    affiche_projectileMLV(niveau, i, j, Proj_D, Proj_G, Proj_H, Proj_B);
                    break;
            }
        }
    }
}

void afficheNom(){
    MLV_draw_text((WIDTH/20)*17, (HEIGHT/50)*49, "© Haelling Lucas | LY Steven ", MLV_COLOR_GREEN);
}

void afficheRegles(){
    int x, y;
    MLV_Keyboard_button touche;

    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_Image  *titre = MLV_load_image("src/IMGS/titre.png");
    MLV_resize_image_with_proportions(titre,WIDTH/2,HEIGHT/2);
    MLV_draw_image(titre, ((WIDTH / 20) * 5), 0);
    MLV_draw_text(WIDTH / 4, (HEIGHT / 16) * 7, "tempreels est un jeu ou le but du joueur sera d'atteindre l'arrivée ", MLV_COLOR_GOLDENROD);
    MLV_draw_text(WIDTH / 4, (HEIGHT / 16) * 8, "il devra pour cela, il devra passer dans une zone remplis de pieges ", MLV_COLOR_GOLDENROD);
    MLV_draw_text(WIDTH / 4, (HEIGHT / 16) * 9, "il devra alors se déplacer et eviter les projectiles qui lui sont envoyé ", MLV_COLOR_GOLDENROD);
    MLV_draw_text(WIDTH / 4, (HEIGHT / 16) * 11, "Cliquer sur la fenetre pour faire disparaitre ce message ou appuyer sur une touche du clavier", MLV_COLOR_GOLDENROD);
    afficheNom();
    MLV_actualise_window();
    MLV_wait_keyboard_or_mouse(&touche, NULL, NULL, &x, &y);
    MLV_free_image(titre);
}

void affichevictoireMLV(clock_t fin){
    int x,y;
    MLV_Keyboard_button touche;
    MLV_Music* victory = MLV_load_music("src/sounds/victoire.mp3");
    MLV_Image* victoire = MLV_load_image("src/IMGS/victoire.png");

    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_resize_image_with_proportions(victoire, WIDTH / 2, HEIGHT / 2);
    MLV_draw_text((WIDTH / 20) * 9, (HEIGHT / 6) * 5, "temps de completion : %d", MLV_COLOR_RED, fin);
    MLV_draw_text((WIDTH / 20) * 17, (HEIGHT / 12) * 49, "© Haelling Lucas | LY Steven ", MLV_COLOR_GREEN);
    MLV_draw_image(victoire,WIDTH / 24 * 7, HEIGHT / 24 * 7);
    MLV_play_music(victory, 1.0, 1);
    MLV_actualise_window();
    MLV_wait_seconds(5);
    MLV_draw_text((WIDTH / 20) * 8, (HEIGHT / 6), "appuyez sur une touche ou cliquez sur l'ecran pour finir", MLV_COLOR_RED);
    MLV_actualise_window();
    MLV_wait_keyboard_or_mouse_or_seconds(&touche, NULL, NULL, &x, &y, 13);
}

void affichedefaiteMLV(clock_t fin){
    MLV_Keyboard_button touche;
    int x,y;

    MLV_Music* defaite = MLV_load_music("src/sounds/defaite.mp3");
    MLV_Image* mort = MLV_load_image("src/IMGS/mort.png");
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_resize_image_with_proportions(mort,WIDTH/2, HEIGHT/2);
    MLV_draw_text((WIDTH / 20) * 9, (HEIGHT / 6) * 5, "temps de survie : %d", MLV_COLOR_RED, fin);
    MLV_draw_text((WIDTH / 20) * 17, (HEIGHT / 12) * 49, "© Haelling Lucas | LY Steven ", MLV_COLOR_GREEN);
    MLV_draw_image(mort,WIDTH / 24 * 7, HEIGHT / 24 * 7);
    MLV_play_music(defaite, 1.0, 1);
    MLV_actualise_window();
    MLV_wait_seconds(5);
    MLV_draw_text((WIDTH / 20) * 8, (HEIGHT / 6), "appuyez sur une touche ou cliquez sur l'ecran pour finir", MLV_COLOR_RED);
    MLV_actualise_window();
    MLV_wait_keyboard_or_mouse_or_seconds(&touche, NULL, NULL, &x, &y, 11);
}

void affichesprites(int *x, int *y){
    MLV_Keyboard_button touche;

    /*--------------initialisation des images--------------*/
    MLV_Image  * lanceur = MLV_load_image("src/IMGS/lanceur.png");
    MLV_Image  * token = MLV_load_image("src/IMGS/token.png");
    MLV_Image  * arrive = MLV_load_image("src/IMGS/arrive.png");
    MLV_Image  * mur = MLV_load_image("src/IMGS/mur.png");

    /*------------redimension des images----------------*/    
    MLV_resize_image_with_proportions(lanceur,WIDTH / 5,HEIGHT / 5);
    MLV_resize_image_with_proportions(token, WIDTH / 5, HEIGHT / 5);
    MLV_resize_image_with_proportions(arrive, WIDTH / 5, HEIGHT/5);
    MLV_resize_image_with_proportions(mur, WIDTH / 5, HEIGHT / 5);

    /*------------affichage des images----------------*/
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_draw_image(lanceur, (WIDTH / 16) *1 + 12, (HEIGHT / 16) * 4);
    MLV_draw_image(token, (WIDTH / 16) * 5 + 12, (HEIGHT / 16) * 4);
    MLV_draw_image(arrive, (WIDTH / 16) * 9 + 12, (HEIGHT / 16) * 4);
    MLV_draw_image(mur, (WIDTH / 16) * 13 + 12, (HEIGHT / 16) * 4);

    /*------------affichage du texte----------------*/
    MLV_draw_text((WIDTH / 16) * 7, (HEIGHT / 16) * 2, "Présentation des objets", MLV_COLOR_STEEL_BLUE);
    MLV_draw_text((WIDTH / 16) * 1 + 100, (HEIGHT / 16) * 8, "Un Lanceur", MLV_COLOR_RED);
    MLV_draw_text((WIDTH / 16) * 1, (HEIGHT / 16) * 10, "Le lanceur vous lancera des projectiles letaux", MLV_COLOR_RED);
    MLV_draw_text((WIDTH / 16) * 1, (HEIGHT / 16) * 11, "à intervalles régulier en direction", MLV_COLOR_RED);
    MLV_draw_text((WIDTH / 16) * 1, (HEIGHT / 16) * 12, "des quatres points cardinaux", MLV_COLOR_RED);

    MLV_draw_text((WIDTH / 16) * 5 + 100, (HEIGHT / 16) * 8, "Vous", MLV_COLOR_STEEL_BLUE);
    MLV_draw_text((WIDTH / 16) * 5, (HEIGHT / 16) * 10, "Vous controlerez ce mage pour tenter de", MLV_COLOR_STEEL_BLUE);
    MLV_draw_text((WIDTH / 16) * 5, (HEIGHT / 16) * 11, "possiblement sortir de ce donjon", MLV_COLOR_STEEL_BLUE);
    MLV_draw_text((WIDTH / 16) * 5, (HEIGHT / 16) * 12, "La tache ne sera pas toujours", MLV_COLOR_STEEL_BLUE);
    MLV_draw_text((WIDTH / 16) * 5, (HEIGHT / 16) * 13, "aussi facile", MLV_COLOR_STEEL_BLUE);

    MLV_draw_text((WIDTH / 16) * 9 + 100, (HEIGHT / 16) * 8, "La Destination", MLV_COLOR_GOLDENROD);
    MLV_draw_text((WIDTH / 16) * 9, (HEIGHT / 16) * 10, "Ceci est l'endroit au quel vous devez vous", MLV_COLOR_GOLDENROD);
    MLV_draw_text((WIDTH / 16) * 9, (HEIGHT / 16) * 11, "diriger pour sortir de ce donjon ou", MLV_COLOR_GOLDENROD);

    MLV_draw_text((WIDTH / 16) * 13 + 100, (HEIGHT / 16) * 8, "Les Murs", MLV_COLOR_ROSY_BROWN);
    MLV_draw_text((WIDTH / 16) * 13, (HEIGHT / 16) * 10, "il vous sera impossible de passer ", MLV_COLOR_ROSY_BROWN);
    MLV_draw_text((WIDTH / 16) * 13, (HEIGHT / 16) * 11, "à travers ce mur, vous devrez", MLV_COLOR_ROSY_BROWN);
    MLV_draw_text((WIDTH / 16) * 13, (HEIGHT / 16) * 12, "les contourner", MLV_COLOR_ROSY_BROWN);

    MLV_draw_text(WIDTH/16*5, (HEIGHT/16)*14, "Cliquer sur la fenetre pour faire disparaitre ce message ou appuyer sur une touche du clavier", MLV_COLOR_GOLDENROD);
    afficheNom();
    MLV_actualise_window();
    MLV_wait_keyboard_or_mouse(&touche, NULL, NULL,x, y);
    MLV_free_image(lanceur);   
    MLV_free_image(token); 
    MLV_free_image(mur); 
    MLV_free_image(arrive); 
}

int traite_personnageMLV(Niveau* niveau, clock_t *intervalle){
    unsigned perso_x, perso_y;
    MLV_Button_state state;
    MLV_Keyboard_button touche = 0;
    if (niveau->depl_perso_autorise != true){ /* test si le deplacement est autorise pour le personnage */
        return 0;
    }
    MLV_get_event(&touche, NULL, NULL, NULL, NULL, NULL, NULL, NULL,&state);
    perso_x = niveau->coo_perso.x;
    perso_y = niveau->coo_perso.y;
    if(state == MLV_PRESSED){
        switch(touche){
    /*-------------------------Deplacement vers le haut--------------------------*/            
            case MLV_KEYBOARD_z:
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
                case MLV_KEYBOARD_UP:
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
                        *intervalle = maintenant() / 10000;
                        return 0;
                    }
                }
                break;
    /*-------------------------Deplacement vers la gauche--------------------------*/                    
            case MLV_KEYBOARD_q:
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
                        *intervalle = maintenant() / 10000;
                        return 0;
                    }
                }
                break;
            case MLV_KEYBOARD_LEFT:
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
                        *intervalle = maintenant() / 10000;
                        return 0;
                    }
                }
                break;
    /*-------------------------Deplacement vers la droite--------------------------*/                    
            case MLV_KEYBOARD_s:
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
                        *intervalle = maintenant() / 10000;  
                        return 0; 
                    }

                }
                break;
            case MLV_KEYBOARD_DOWN:
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
                        *intervalle = maintenant() / 10000;  
                        return 0; 
                    }

                }
                break;
    /*-------------------------Deplacement vers le bas--------------------------*/                    
            case MLV_KEYBOARD_d:
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
                        *intervalle = maintenant() / 10000;
                        return 0;
                    }
                }
                break;
            case MLV_KEYBOARD_RIGHT:
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
                        *intervalle = maintenant() / 10000;
                        return 0;
                    }
                }
                break;
    /*-------------------------autres touches pas de deplacement--------------------------*/                
            default:
                    return 0;
                break;
        }
    }
    return 0;
}




