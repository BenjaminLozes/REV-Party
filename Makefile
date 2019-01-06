all: test-lab

csv : csvTest

csvTest: squelette.o csvanalyse.c
	gcc -g -Wall -o csvTest squelette.o csvanalyse.c

test-lab: squelette.o csvanalyse.o command.o launcher.c
	gcc -g -Wall -o test-lab squelette.o csvanalyse.o command.o launcher.c

squelette.o: squelette.c
	gcc -c -Wall -o squelette.o squelette.c

csvanalyse.o: csvanalyse.c
	gcc -c -Wall -o csvanalyse.o csvanalyse.c

command.o: command.c
	gcc -c -Wall -o command.o command.c

clean :
	rm squelette.o csvanalyse.o command.o test-lab
