
all: main.o affichage.o fir.o iir.o integration.o lecture.o mesure.o fichiers.o
	gcc -g main.o affichage.o fir.o iir.o integration.o lecture.o mesure.o fichiers.o -o a.out

#Compilatin des fichiers un à un
main.o: main.c
	gcc -g -c -Wall main.c
	#gcc -c compile et assemble mais le link pas,
	#-g paremètre autoriser le mode débug

affichage.o: affichage.c
	gcc -g -c -Wall affichage.c

fir.o: fir.c
	gcc -g -c -Wall fir.c

iir.o: iir.c
	gcc -g -c -Wall iir.c

integration.o: integration.c
	gcc -g -c -Wall integration.c

lecture.o: lecture.c
	gcc -g -c -Wall lecture.c

mesure.o: mesure.c
	gcc -g -c -Wall mesure.c

fichiers.o: fichiers.c
	gcc -g -c -Wall fichiers.c


# clean house
clean:
	rm -f main.o affichage.o fir.o iir.o integration.o lecture.o mesure.o fichiers.o a.out

# run le programme avec la commande ./a.out
run: a.out
	 ./a.out

# Compiler le programme avec valgrind et les information de débug (trouvé sur internet)
debug: a.out
	valgrind a.out

# Lancer avec les erreurs de valgrind
valgrind: a.out
	valgrind a.out

# Pour savoir les erreurs de leak
valgrind_leakcheck: a.out
	valgrind --leak-check=full a.out

# Pour savoir les erreurs de leak
valgrind_extreme: a.out
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes a.out