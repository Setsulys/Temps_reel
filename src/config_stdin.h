

/* Il faut appeler cette fonction avant de lancer le jeu en mode texte. 
 * NB: il ne faut appeler cette fonction qu'une seule fois.
 * */
void init_stdin();


/* Si `init_stdin()` a ete appelee, il faut appeler `restaure_stdin()`
 * juste avant la fin du programme, pour restaurer les parametres
 * d'orine du terminal. */
void restaure_stdin();

