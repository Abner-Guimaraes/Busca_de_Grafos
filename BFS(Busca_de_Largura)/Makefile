all: T2BFS

T2DFS: main.o T2BFS.o
	gcc -o T2DFS main.o T2DFS.o

main.o: main.c T2BFS.h
	gcc -o main.o main.c -c -W -Wall -ansi -pedantic

T2DFS.o: T2BFS.c T2BFS.h
	gcc -o T2BFS.o T2BFS.c -c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o *~
