#ifndef __NIVEAUX__
#define __NIVEAUX__

/* ======== include ======================================= */
    #include<stdio.h>
    #include<stdlib.h>
    #include<assert.h>

    #include"structure.h"
    

/* ======== fonctions` ======================================= */

    /* alloue l'espace necessaire pour un niveau */
    Niveau* malloc_Niveau (Coordonnees tailles);

    /* desalloue l'espace necessaire d'un niveau */
    void free_Niveau(Niveau* niveau);

    /* creation d'un niveau 0 */
    Niveau* niveau0();

    /*affiche un projectille dans le niveau selon sa position*/
    void affiche_projectile(Niveau *niveau, unsigned int i, unsigned int j);

    /* affiche un niveau dans le terminal */
    void affiche_Niveau(Niveau * niveau);

#endif 