all:
	make main
main.o: main.c person.h elevator.h
	gcc -c main.c
elevator.o: elevator.c person.h elevator.h
	gcc -c elevator.c
person.o: person.c person.h
	gcc -c person.c
main: person.o elevator.o main.o person.h elevator.h
	gcc -g -o main main.o elevator.o person.o -lncurses 
run:
	./main
debug: main
	gdb main
clean:
	rm -f main *.o