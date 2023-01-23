#ifndef __OBJET__
#define __OBJET__

/* ======== include ======================================= */
    #include<stdlib.h>    
    #include<ctype.h>
    #include<MLV/MLV_all.h>
    #include"structure.h"
    #include"tas.h"
    #include"evenement.h"


/* ======== fonctions` ======================================= */

    /* traite un evenement réalisée sur un projectile */
    void traite_projectile(Niveau* niveau, Evenement e, Tas *tas);

    /* gestion du champs données supl dans la structure objet */
    void gestion_donnee_suppl(Objet* obj, Direction dir);

    /* gestion de données supl pour les projectile cree par les lanceurs */
    void donnees_supl_projectile(Evenement e, Niveau *niveau);

    /* traitre un evenement rséalisée sur un lanceur */
    void traite_lanceur(Niveau* niveau, Evenement e, Tas* tas);

    /* traite le deplacement d'un personnage en ascii */
    int traite_personnage(Niveau *niveau, clock_t *intervalle);


 
    
#endif 