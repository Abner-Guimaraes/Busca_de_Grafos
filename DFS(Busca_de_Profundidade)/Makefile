all: T2DFS

T2DFS: main.o T2DFS.o
	gcc -o T2DFS main.o T2DFS.o

main.o: main.c T2DFS.h
	gcc -o main.o main.c -c -W -Wall -ansi -pedantic

T2DFS.o: T2DFS.c T2DFS.h
	gcc -o T2DFS.o T2DFS.c -c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o *~
