all: test-lab

test-lab: elementliste.o liste.o squelette.o mainfile.c
	gcc -Wall -o test-lab elementliste.o liste.o squelette.o mainfile.c

squelette.o: squelette.c
	gcc -c -Wall -o squelette.o squelette.c

elementliste.o: elementliste.c
	gcc-c -Wall -o elementliste.o elementliste.c

liste.o: liste.c
	gcc -c -Wall -o liste.o liste.c

clean :
	rm liste.o elementliste.o squelette.o test-lab
