test-subseq: test-subseq.o maxSeq.o
	gcc -o test-subseq -pedantic -std=gnu99 -Wall -Werror maxSeq.o test-subseq.o 

maxSeq: maxSeq.o
	gcc -o maxSeq -pedantic -std=gnu99 -Wall -Werror maxSeq.o 

maxSeq.o: maxSeq.c
	gcc -c -pedantic -std=gnu99 -Wall -Werror maxSeq.c 

test-subseq.o: test-subseq.c
	gcc -c -pedantic -std=gnu99 -Wall -Werror test-subseq.c 
