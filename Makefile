app.out: main.o
	gcc -o app.out main.o

main.o:
	gcc -c main.c