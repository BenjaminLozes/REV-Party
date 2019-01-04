all: test-lab

test-lab: csvReading.o command.o launcher.c
	gcc -Wall -o test-lab csvReading.o command.o launcher.c

csvReading.o: csvReading.c
	gcc -c -Wall -o csvReading.o csvReading.c

command.o: command.c
	gcc -c -Wall -o command.o command.c

clean :
	rm csvReading.o command.o test-lab
