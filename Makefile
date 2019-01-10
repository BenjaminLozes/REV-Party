all: test-lab

liste:
	gcc -g -Wall elementliste.c liste.c squelette.c mainfile.c -o testsListe

test-lab:
	gcc -g -Wall utils_sd.c uninominal.c alternatif.c csvanalyse.c squelette.c utils_scrutin.c launcher.c -o scrutin


cleanTests:
	rm testsListe