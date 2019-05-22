main: main.o listy.o tree.o
	gcc -o main main.o tree.o listy.o
listy.o: listy.c listy.h tree.h primary.h
	gcc -Wall -Wextra -std=c11 -O2 -c listy.c
tree.o: tree.c listy.h tree.h primary.h
	gcc -Wall -Wextra -std=c11 -O2 -c tree.c
main.o: main.c listy.h primary.h tree.h
	gcc -Wall -Wextra -std=c11 -O2 -c main.c

clean:
	rm main.o
	rm tree.o
	rm listy.o
	rm main
