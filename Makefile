all: test-lab

test-lab:
	gcc -g -Wall utils_sd.c uninominal.c alternatif.c csvanalyse.c squelette.c utils_scrutin.c launcher.c -o scrutin

csv : csvTest