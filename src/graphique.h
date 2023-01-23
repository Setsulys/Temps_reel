#ifndef __GRAPHIQUE__
#define __GRAPHIQUE__

    #include<stdio.h>
    #include<MLV/MLV_all.h>

    #include"tas.h"
    #include"evenement.h"
 

    #define WIDTH 1500
    #define HEIGHT 800
    #define CENTERX 250
    #define CENTERY 100

    /*affiche le score en cours de partie*/
    void affichetemps(clock_t debut);

    /* affiche les projectile en MLV */
    void affiche_projectileMLV(Niveau *niveau, unsigned int i, unsigned int j,const MLV_Image*Proj_D,const MLV_Image*Proj_G,const MLV_Image*Proj_H,const MLV_Image*Proj_B);

    /* affiche les sprites*/
    void dessinemlv(Niveau*niveau, const MLV_Image*Vide,const MLV_Image*Mur,const MLV_Image*Arrive,const MLV_Image*Token,const MLV_Image*Lanceur, const MLV_Image*Proj_D, const MLV_Image*Proj_G, const MLV_Image*Proj_H, const MLV_Image*Proj_B);

    /*affichage du nom des createur avec un copyright*/
    void afficheNom();

    /*affichage en debut de partie des regles du jeu*/
    void afficheRegles();

    /*initialisation graphique*/
    void game_graphique(Niveau *niveau);

    /*affiche le role des sprites en debut de partie*/
    void affichesprites(int *x, int *y);

    /*traite les déplacements du personnage*/
    int traite_personnageMLV(Niveau* niveau, clock_t *intervalle);

    /*affiche un ecran de victoire avec une musique de victoire*/
    void affichevictoireMLV(clock_t fin);

    /*affiche un ecran de defaite avec une musique de defaite*/
    void affichedefaiteMLV(clock_t fin);

#endif