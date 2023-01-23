
#ifndef __STRUCTURES__
#define __STRUCTURES__

/* ======== include ======================================= */
    #include<stdbool.h> /* Definis le type `bool` */
  

/* ======== #DEFINE ======================================= */
    #define TAILLE_MAX 50


/* ========================================================================== */
/*          Partie 1: Niveau                                                  */
/* ========================================================================== */



/* ======== Definition du type `Objet` ====================================== */
    typedef enum {
      VIDE = 0,          LANCEUR,           MUR,
      PROJECTILE,        PERSONNAGE,        DESTINATION,
    } TypeObjet;

    typedef struct {
      TypeObjet type;     /* Type de l'objet */
      void* donnee_suppl; /* Donnee supplementaire: son type depend de 
                          * `type` ci-dessus:
                          * - Deplacement*  si  type == PROJECTILE
                          * - Generation* si type == LANCEUR
                          * - donnee\_suppl vaut NULL pour les 
                          *   autres types. */
    } Objet;


/* ======== Definition du type `Deplacement` ================================ */
    typedef enum { 
      HAUT,              
      GAUCHE, 
      BAS,               
      DROITE
    } Direction;

    typedef struct {
      Direction direction; /* Direction du deplacement */
      unsigned long allure; /* Allure du deplacement */
    } Deplacement;


/* ======== Definition du type `Generation` ================================= */
    typedef struct {
      unsigned long intervalle; /* Intervalle entre deux envois
                                * de projectiles */
      unsigned long allure_proj; /* Allure des projectiles envoyes */
    } Generation;


/* ======== Definition du type `Niveau` ===================================== */

    typedef struct {
      unsigned x;
      unsigned y;
    } Coordonnees;

    typedef struct {
      Coordonnees taille; /* Taille du niveau */
      Objet** objets; /* Tableau bi-directionnel de largeur taille.x, 
                      * de hauteur taille.y, et dont chaque case 
                      * contient un Objet */
      Coordonnees coo_perso; /* Position actuelle du personnage. */
      unsigned long allure_perso; /* Allure du personnage */
      bool depl_perso_autorise; /* Vaut `true` si  le temps ecoule
                                * depuis le dernier deplacement du
                                * personnage est superieur a son
                                * allure. */
    } Niveau;


/* ======== Definition du type `Tas` ======================================= */

    typedef struct {
        unsigned long moment; /* Moment auquel evenement doit avoir lieu en
                                * nombre de "tick" du processeur
                                * Voir Gestion du temps */
        Coordonnees coo_obj; /* Objet affecte */
    }Evenement;

    typedef struct {
        unsigned taille;    /* Nombre d'Evenements contenus dans le tas */
        unsigned capacite;  /* Nombre de cases allouees pour les `valeurs` (i.e. taille maximale) */
        Evenement *valeurs; /* Tableau d'Evenements de taille `capacite` et dont les `taille` premieres cases sont utilisees. */
    }Tas;


#endif