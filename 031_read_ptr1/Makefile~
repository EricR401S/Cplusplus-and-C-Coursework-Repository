
test-power: test-power.o power.o
	gcc -o test-power -pedantic -std=gnu99 -Wall -Werror power.o test-power.o 

power: power.o
	gcc -o power -pedantic -std=gnu99 -Wall -Werror power.o 


test-power.o: test-power.c
	gcc -c -pedantic -std=gnu99 -Wall -Werror test-power.c 


power.o: power.c
	gcc -c -pedantic -std=gnu99 -Wall -Werror power.c 
