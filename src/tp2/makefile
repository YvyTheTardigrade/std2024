all: main

list.o : ../../lib/list/list.h ../../lib/list/list.c
	gcc -c ../../lib/list/list.c -o list.o -Wall -Wextra

queue.o : ../../lib/queue/queue.h ../../lib/queue/queue.c
	gcc -c ../../lib/queue/queue.c -o queue.o -Wall -Wextra

stack.o : ../../lib/stack/stack.h ../../lib/stack/stack.c
	gcc -c ../../lib/stack/stack.c -o stack.o -Wall -Wextra

main.o : main.c ../../lib/list/list.h ../../lib/queue/queue.h ../../lib/stack/stack.h
	gcc -c main.c -o main.o -Wall -Wextra

main : list.o queue.o stack.o main.o
	gcc list.o queue.o stack.o main.o -o main.exe -Wall -Wextra
	
clean:
	rm *.o


