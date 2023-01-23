#ifndef __EVENEMENT__
#define __EVENEMENT__


/* ======== include ======================================= */
    #include<stdbool.h>

    #include"tas.h"

    #define ALLURE_PROJECTILE 1000

/* ======== fonctions` ======================================= */

    /* renvoie true si un evenement est pret sinon false */
    bool un_evenement_est_pret(Tas* tas);

    /* supprime et renvoie le minimum dans le tas */
    Evenement ote_minimum(Tas* tas);

    /* ajoute un evenement au tas */
    void ajoute_evenement(Tas* tas, Evenement n);

    /* traitre un evenement */
    Deplacement traite_evenement(Evenement e, Tas* tas, Niveau* niveau);

    /* renvoie 1 si un evenement dans le tas doit s'executer en meme temps que l'evenement e passée en parametre */
    int evenement_en_cour(Evenement e, Tas tas);

    /* déplace un projectille selon sa direction */
    void gestion_ev(Tas* tas, Evenement e, char directionc);

    /* renvoie 1 si une touche 's', 'q', 's' ou 'd' est presser 0 sinon */
    int capte_touche();

    /* verifie si le personnage peut se deplacer */
    void depl_autorise(Niveau *niveau, clock_t depl);

    /* verifie l'etat de la partie */
    int verif_partie(Niveau niveau);

    /* affiche le messag de victoire */
    void affiche_victoire();




#endif