#ifndef __FICHIER__
#define __FICHIER__

/* ======== include ======================================= */
    #include<string.h>
    #include<stdlib.h>
    #include"niveau.h"
    #include"structure.h"
    #include"tas.h"
    #include"evenement.h"
    #include"graphique.h"
    #include"config_stdin.h"

    /* compte le nombre lignes d'un ficher */
    int compte_lignes(FILE* fichier);

    /* compte le nombre de caracteres d'un fichier sur la premier ligne */
    int compte_caractere_lignes(FILE* fichier);

    /* creer le niveau du fichier passer en agrument */
    Niveau* read_Niveau_file(char *nom_fichier);

    /* gere les arguments du main */
    void gestion_argument(int argc, const char *argv[]);

    /* affiche d'un message d'explication pour l'execution du programme */
    void message_explication();

    /* lance le jeux en ascii */
    void game_ascii(Niveau *niveau);

    /* lance le jeu en graphique */
    void game_graphique(Niveau* niveau);

    /* verification des arguments du main entrer par l'utilisateur */
    void verif_arguments(int argc, const char *argv[]);



#endif
