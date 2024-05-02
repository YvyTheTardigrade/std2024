all: main

list.o : ../../lib/list/list.h ../../lib/list/list.c
	gcc -c ../../lib/list/list.c -o list.o -Wall -Wextra

queue.o : ../../lib/queue/queue.h ../../lib/queue/queue.c
	gcc -c ../../lib/queue/queue.c -o queue.o -Wall -Wextra

stack.o : ../../lib/stack/stack.h ../../lib/stack/stack.c
	gcc -c ../../lib/stack/stack.c -o stack.o -Wall -Wextra

tree.o : ./../../lib/tree/tree.c ./../../lib/tree/tree.h  ./../../lib/queue/queue.h  ./../../lib/stack/stack.h ./../../lib/list/list.h
	gcc  -c ./../../lib/tree/tree.c -o tree.o -Wall -Wextra

main.o : main.c ./../../lib/list/list.h ./../../lib/tree/tree.h 
	gcc -c main.c -o main.o -Wall -Wextra

main : list.o queue.o stack.o tree.o main.o
	gcc list.o tree.o main.o queue.o stack.o -o main.exe -Wall -Wextra
	
clean:
	rm *.o


