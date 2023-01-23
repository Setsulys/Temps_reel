CC = gcc
CFLAGS = -Wall -ansi -Wextra
LDFLAGS = -lMLV
EXEC = tempsreels
OBJ = ./src/main.o ./src/niveau.o ./src/objet.o ./src/tas.o ./src/evenement.o ./src/temps.o ./src/config_stdin.o ./src/graphique.o ./src/annexe.o


tempsreels: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	
main.o: main.c tas.h evenement.h config_stdin.h graphique.h fichier.h
	$(CC) -c $< $(CFLAGS) $(LDFLAGS)
	
niveau.o: niveau.c niveau.h structure.h
	$(CC) -c $< $(CFLAGS) $(LDFLAGS)

objet.o: objet.c objet.h tas.h structure.h evenement.h
	$(CC) -c $< $(CFLAGS) $(LDFLAGS)

tas.o: tas.c tas.h objet.h temps.h
	$(CC) -c $< $(CFLAGS) $(LDFLAGS)

evenement.o: evenement.c evenement.h tas.h
	$(CC) -c $< $(CFLAGS) $(LDFLAGS)

graphique.o: graphique.c graphique.h niveau.h temps.h
	$(CC) -c $< $(CFLAGS) $(LDFLAGS)

annexe.o : fichier.c fichier.h niveau.h
	$(CC) -c $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -f *./src/ $(OBJ)
	rm -f tempsreels