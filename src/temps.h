/* ========================================================================== */
/*          Annexe 1: Gestion du temps                                        */
/* ========================================================================== */

#ifndef __TEMPS__
#define __TEMPS__

    #include <sys/select.h>
    #include <time.h>

    /* Le pas de temps le plus naturel pour un programme est le tick.
    * Le temps entre deux ticks est defini par le systeme d'exploitation
    * mais celui-ci fournit egalement les possibilites pour le traduire
    * en duree classique (voir ci-dessous).
    * On mesurera le temps en nombre de "tick" depuis le lancement du 
    * programme.  Ce nombre peut etre tres grand, on utilisera donc un 
    * `long unsigned` pour le stocker. */


    /* NB: Certaines variables/fonctions ci-dessous sont entierement definies (pas
    * seulement declarees).  C'est pour permettre cela qu'on utilise le mot-clef
    * `static` ci-dessous; vous pouvez utiliser ces fonctions normalement sans le
    * prendre en compte.
    * (La definition precise du mot clef `static` est bien plus complexe que cela
    * et on la laisse a des cours ulterieurs.) */


    /* La fonction ` maintenant () ` renvoie le nombre de "tick" du
    * processeur depuis le lancement du programme . */
    long unsigned maintenant();


    /* La variable globale `une_seconde` vaut le nombre de "tick"
    * correspondant a une seconde.  Par exemple, si la condition
    * `maintenant()>=une_seconde` est vraie, cela signifie qu'au 
    * moins une seconde s'est ecoulee depuis le lancement du 
    * programme.  Similairement `maintenant()+une_seconde` 
    * represente le moment une seconde dans l'avenir. */
    static const long unsigned une_seconde = CLOCKS_PER_SEC;


    /* La variable globale `une_milliseconde` vaut le nombre de "tick" 
    * correspondant a une milliseconde, c'est-a-dire un millieme 
    * de seconde. */
    static const long unsigned une_milliseconde = une_seconde/1000;


    /* La fonction `millisleep(i)` fait en sorte que le programme 
    * attende i millisecondes avant de continuer a s'executer. */
    void millisleep(unsigned long i);

#endif