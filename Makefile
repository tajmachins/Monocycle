all: main

main: main.o Character.o
	g++ main.o Character.o -o main

%.o : %.cpp
	g++ -c $< -o $@

clean : 
	rm -f $*.o
	rm -f main
