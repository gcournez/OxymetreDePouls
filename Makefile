

# -g option enables debugging mode 
# -c flag generates object code for separate files


all: main.o affichage.o fir.o iir.o integration.o lecture.o mesure.o fichiers.o
	gcc -g main.o affichage.o fir.o iir.o integration.o lecture.o mesure.o fichiers.o -o a.out

# create/compile the individual files >>separately<<
main.o: main.c
	gcc -g3 -c -Wall main.c -lcunit

affichage.o: affichage.c
	gcc -g3 -c -Wall affichage.c -lcunit

fir.o: fir.c
	gcc -g3 -c -Wall fir.c -lcunit

iir.o: iir.c
	gcc -g3 -c -Wall iir.c -lcunit

integration.o: integration.c
	gcc -g3 -c -Wall integration.c -lcunit

lecture.o: lecture.c
	gcc -g3 -c -Wall lecture.c -lcunit

mesure.o: mesure.c
	gcc -g3 -c -Wall mesure.c -lcunit

fichiers.o: fichiers.c
	gcc -g3 -c -Wall fichiers.c -lcunit


# clean house
clean:
	rm -f main.o affichage.o fir.o iir.o integration.o lecture.o mesure.o fichiers.o a.out

# run the program
run: a.out
	 ./a.out

# compile program with debugging information
debug: a.out
	valgrind a.out

# run program with valgrind for errors
valgrind: a.out
	valgrind a.out

# run program with valgrind for leak checks
valgrind_leakcheck: a.out
	valgrind --leak-check=full a.out

# run program with valgrind for leak checks (extreme)
valgrind_extreme: a.out
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes a.out