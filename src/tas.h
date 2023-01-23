#ifndef __TAS__
#define __TAS__

/* ======== include ======================================= */
    #include <assert.h>
    #include"niveau.h"
    #include"temps.h"
    #include"objet.h"

    
/* ======== fonctions` ======================================= */

    /* alloue l'espace necessaire pour un tas */
    Tas* malloc_Tas(unsigned capacite_initiale);

    /* desalloue l'espace necessaire d'un tas */
    void free_Tas(Tas* tas);

    /* trie le tas dans l'ordre croissant par rapport au moment de l'evenement */
    void trier_tas_croissant(Tas *tas);

    /* affiche le tas tableau tas */
    void affiche_tas_ev(Tas tas);

    /*Construit le tas depuis le niveau donné en argument*/
    Tas* construit_Tas(Niveau* niveau);

    /*affiche le tas actuelle dans le terminal*/
    void affiche_Tas(Tas tas);

#endif 