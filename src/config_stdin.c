#include <stdio.h>
#include <termios.h>
#include <fcntl.h>

#include "config_stdin.h"


/* Emplacement stockant les paramètres d'origine du terminal */
struct termios old_tio;


void init_stdin()
{
  /* Reparametrisation de STDIN */
  fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK); /* Rend l'appel à `read`
                                                        sur le descripteur 0 
                                                        (STDIN dans la plupart 
                                                        des cas) non-bloquant */
  setbuf(stdin, NULL); /* Supprime le buffer du flux stdin */

  /* Reparametrisation du terminal*/
  struct termios new_tio;
  tcgetattr(0,&old_tio); /* Récupère les parametres actuels du terminal */
  new_tio=old_tio; /* Copie les anciens parametres dans les nouveaux*/
  new_tio.c_lflag &=(~ICANON & ~ECHO); /* Desactive les mode 'canonique' et 
                                          'echo' */
  new_tio.c_cc[VMIN] = 1; /* Taille du buffer avant transmission à STDIN */
  new_tio.c_cc[VTIME] = 0; /* Temps d'attente (en ds) avant de transmettre 
                              une input à STDIN. */
  tcsetattr(0, TCSANOW, &new_tio); /* Applique les paramètres */
}


void restaure_stdin()
{

  /* Applique au terminal ses paramètres d'origine */
  tcsetattr(0,TCSANOW,&old_tio);
}

