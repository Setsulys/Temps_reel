#include"annexe.h"

int compte_lignes(FILE* fichier){
    int nb_lignes = 0, c;
    while((c = fgetc(fichier)) != EOF){
        if(c == '\n'){
            nb_lignes += 1;
        }
    }
    nb_lignes += 1;
    return nb_lignes;
}

int compte_caractere_lignes(FILE* fichier){
    int compteur = 0;
    while(fgetc(fichier) != '\n'){
        compteur ++;
    }
    return compteur;
}

Niveau* read_Niveau_file(char *nom_fichier){
    FILE *fichier;
    Coordonnees tailles;
    Niveau* tmp;
    unsigned int i = 0, j = 0, nblignes = 0, nbcolonnes = 0;
    char c;
    
    fichier = fopen(nom_fichier, "r+");

    if (NULL != fichier){

        nblignes = compte_lignes(fichier);
        rewind(fichier);

        nbcolonnes = compte_caractere_lignes(fichier);
        rewind(fichier);

        tailles.x = nbcolonnes;
        tailles.y = nblignes;

        tmp = malloc_Niveau(tailles);
        while((c = fgetc(fichier)) != EOF){
            switch (c){
                case '0':
                    tmp->objets[i][j].type = LANCEUR;
                    i ++;
                    break;
                case '.':
                    tmp->objets[i][j].type = VIDE;
                    i ++;
                    break;
                case '#':
                    tmp->objets[i][j].type = MUR;
                    i ++;
                    break;
                case 'D':
                    tmp->objets[i][j].type = DESTINATION;
                    i ++;
                    break;
                case 'P':
                    tmp->objets[i][j].type = PERSONNAGE;
                    tmp->coo_perso.x = i;
                    tmp->coo_perso.y = j;
                    i ++;
                    break;
                case '\n':
                    j ++;
                    i = 0;
                    break;
                default:
                    i = 0;
                    break;
            }
        }
        fclose(fichier);
        return tmp;
    }
    return NULL;
    
}

void gestion_argument(int argc, const char *argv[]){
    if (argc < 2){
        printf("Vous n'avez pas saisie assez d'arguments\n");
        message_explication();
    }
    else{
        if (argv[1][0] == '-' && argv[1][1] == '-'){
            verif_arguments(argc, argv);
        }
        else{
            printf("Vous avez mal saisie les d'arguments\n");
            message_explication();
        }
    }
    
}

void message_explication(){
    printf("Pour executer vous possedez deux choix\n\n");
    printf("Usage 1: tempsreels --test=<int>\nLance le programme avec un niveau exemple compris entre [0,6] difficultés croissante en mode MLV si possible.\n\n");
    printf("Usage 2: tempsreels --test=<int> -a\nLance le programme avec un niveau exemple compris entre [0,6] difficultés croissante en mode Ascii dans le terminal.\n\n");
    printf("Usage 3: tempsereels --fichier=<fichier>\nLance le programme en lisant le niveau depuis le fichier donné en mode MLV si possible.\n\n");
    printf("Usage 4: tempsereels --fichier=<fichier> -a\nLance le programme en lisant le niveau depuis le fichier donné en mode Ascii dans le terminal.\n\n");
    printf("Usage 5: tempsereels --usage \nDonne des explications de sur la maniere d'utiliser le jeu\n\n");
}

void verif_arguments(int argc, const char *argv[]){
    char exemple[6] = "test=";
    char fichier[9] = "fichier=";
    char usage[6] = "usage";
    char chemin[150] = "./niveau_joueur/";
    char lettre;
    int len_exemple, len_fichier, len_usage, len_niveau;
    int i;

    len_exemple = strlen(exemple);
    len_fichier = strlen(fichier);
    len_usage = strlen(usage);
    len_niveau = strlen(argv[1]);

    Niveau *niveau;

    switch(argv[1][2]){
        case 't':
            for(i = 0; i < len_exemple; i ++){
                if (argv[1][i + 2] != exemple[i]){
                    printf("Vous avez mal saisie les d'arguments\n");
                    message_explication();
                    break;
                }
            }
            char lance[21] = "./src/niveau/niveau";
            
            if (argv[1][7] > '7' || argv[1][7] < '0' || len_niveau > 9){
                printf("Vous avez mal saisie les d'arguments\nSeuls les niveau compris entre 0 et 6 inclus sont present pour exemple\n\n");
                message_explication();
                break;
            }
            
            lance[19] = argv[1][7];
            niveau = read_Niveau_file(lance);
            if(argc > 2 && argv[2][0] == '-' && argv[2][1] == 'a'){
                game_ascii(niveau);
            }
            else{
                if(niveau->taille.x <= 12 && niveau->taille.y <=10)
                    game_graphique(niveau);
                else{
                    printf("Votre niveau est trop grand pour etre joué en mode graphique\n");
                    printf("Vous allez devoir jouer en mode ascii \n");
                    game_ascii(niveau);
                }
            }
            /*free_Niveau(niveau);*/
            break;
        case 'f':
            if (len_niveau <= 10){
                printf("Vous avez mal saisie les d'arguments\n");
                message_explication();
                break;
            }
            for(i = 0; i < len_fichier; i ++){
                if (argv[1][i + 2] != fichier[i]){
                    printf("Vous avez mal saisie les d'arguments\n");
                    message_explication();
                    break;
                }
            }
            for (i = 10; i < len_niveau ; i ++){
                lettre = argv[1][i];
                chemin[6 + i] = lettre;
            }

            niveau = read_Niveau_file(chemin);
            if (NULL == niveau){
                printf("Vous avez mal saisie le nom du fichier contenant le niveau");
                message_explication();
                break;
            }

            if(argc > 2 && argv[2][0] =='-' && argv[2][1] == 'a'){
                game_ascii(niveau);
            }
            else{
                if(niveau->taille.x <= 12 && niveau->taille.y <=10)
                    game_graphique(niveau);
                else{
                    printf("Votre niveau est trop grand pour etre joué en mode graphique\n");
                    printf("Vous allez devoir jouer en mode ascii \n");
                    game_ascii(niveau);
                }
            }
            /*free_Niveau(niveau);*/
            break;
        case 'u':
            for(i = 0; i < len_usage; i ++){
                if (argv[1][i + 2] != usage[i]){
                    printf("Vous avez mal saisie les d'arguments\n");
                    message_explication();
                    break;
                }
            }
            message_explication();
            break;
        default:
            message_explication();
            break;
    }
}

void game_ascii(Niveau *niveau){
    init_stdin();
    Tas* tas;

    Evenement min;
    clock_t intervalle;

    tas = construit_Tas(niveau);

    intervalle = 0;

    affiche_Niveau(niveau);

    while(verif_partie(*niveau) == 1){
        millisleep(25);
        if (traite_personnage(niveau, &intervalle) == 10){
            affiche_victoire();
            break;
        }
        depl_autorise(niveau, intervalle);
        if (un_evenement_est_pret(tas)){
            min = ote_minimum(tas);
            traite_evenement(min, tas, niveau);
            if (evenement_en_cour(min, *tas) != 1){
                system("clear");
                affiche_Niveau(niveau);
            }
        }
    }
    free_Tas(tas);
    restaure_stdin();
}

void game_graphique(Niveau *niveau){

    Tas* tas;
    Evenement min;
    clock_t intervalle,debut,fin;

    tas = construit_Tas(niveau);
    intervalle = 0;
    int x = 0, y = 0, defaite = 1;



    MLV_create_window("tempsreels","Jeu graphique",WIDTH, HEIGHT);
/*----------Initialisation des musiques----------*/   
    MLV_init_audio();
    MLV_Music* music = MLV_load_music("src/sounds/Astralchain.mp3");
    MLV_Music* megalo = MLV_load_music("src/sounds/Megalovania.mp3");
/*----------Initialisation des sprites----------*/
	MLV_Image *Vide = MLV_load_image("src/IMGS/vide.png");
	MLV_Image *Mur = MLV_load_image("src/IMGS/mur.png");
	MLV_Image *Arrive = MLV_load_image("src/IMGS/arrive.png");
	MLV_Image *Token = MLV_load_image("src/IMGS/token.png");
	MLV_Image *Lanceur = MLV_load_image("src/IMGS/lanceur.png");

	MLV_Image *Proj_D = MLV_load_image("src/IMGS/droite.png");
	MLV_Image *Proj_G = MLV_load_image("src/IMGS/gauche.png");
	MLV_Image *Proj_H = MLV_load_image("src/IMGS/haut.png");
	MLV_Image *Proj_B = MLV_load_image("src/IMGS/bas.png");
/*----------resize des sprites----------*/
	MLV_resize_image_with_proportions(Mur, (WIDTH / 10) - 5, (HEIGHT / 10) - 5);
    MLV_resize_image_with_proportions(Vide, (WIDTH / 10) - 5, (HEIGHT / 10) - 5);
	MLV_resize_image_with_proportions(Arrive, (WIDTH / 10) - 5, (HEIGHT / 10) - 5);
	MLV_resize_image_with_proportions(Token, (WIDTH / 10) - 5, (HEIGHT / 10) - 5);
	MLV_resize_image_with_proportions(Lanceur, (WIDTH / 10) - 5, (HEIGHT / 10) - 5);

	MLV_resize_image_with_proportions(Proj_D, (WIDTH / 10) - 5, (HEIGHT / 10) - 5);
	MLV_resize_image_with_proportions(Proj_G, (WIDTH / 10) - 5, (HEIGHT / 10) - 5);
	MLV_resize_image_with_proportions(Proj_H, (WIDTH / 10) - 5, (HEIGHT / 10) - 5);
	MLV_resize_image_with_proportions(Proj_B, (WIDTH / 10) - 5, (HEIGHT / 10) - 5);
/*------------------presentation du jeu et des sprites----------*/
    afficheRegles();
    affichesprites(&x, &y);
    MLV_clear_window(MLV_rgba(20,20,20,255));
	afficheNom();
    debut = maintenant()/une_milliseconde;
    affichetemps(debut);
	dessinemlv(niveau, Vide, Mur, Arrive, Token, Lanceur, Proj_D, Proj_G, Proj_H, Proj_B);
	MLV_actualise_window();
/*-----------------Enclanchement de la musique (easter egg)------------------*/
    if((x <= (WIDTH/20) * 17) && y <= ((HEIGHT/50)*49)){
        MLV_play_music(music, 1.0, -1);
    }
    else{
        MLV_play_music(megalo, 1.0, -1);
    }
/*---------------------Boucle principale--------------------*/
    while(verif_partie(*niveau) == 1){
        MLV_wait_milliseconds(25);
        if (traite_personnageMLV(niveau, &intervalle) == 10){
            fin = maintenant() / une_milliseconde - debut;
            affichevictoireMLV(fin);
            defaite =0;
            break;
        }
        depl_autorise(niveau, intervalle);
        if (un_evenement_est_pret(tas)){
            min = ote_minimum(tas);
            traite_evenement(min, tas, niveau);
            if (evenement_en_cour(min, *tas) != 1){
                MLV_clear_window(MLV_rgba(20,20,20,255));
                afficheNom();
                affichetemps(debut);
	            dessinemlv(niveau, Vide, Mur, Arrive, Token, Lanceur, Proj_D, Proj_G, Proj_H, Proj_B);
	            MLV_actualise_window();
            } 
        }
    }
    if(defaite == 1 ){
        fin = maintenant()/ une_milliseconde - debut;
        affichedefaiteMLV(fin);
    }
/*------------------free----------*/
    free_Tas(tas);

	MLV_free_image(Vide);
  	MLV_free_image(Mur);
	MLV_free_image(Arrive);
	MLV_free_image(Token);
	MLV_free_image(Lanceur);
	MLV_free_image(Proj_D);
	MLV_free_image(Proj_G);
	MLV_free_image(Proj_H);
	MLV_free_image(Proj_B);

    MLV_free_music(music);
    MLV_free_audio();
}

