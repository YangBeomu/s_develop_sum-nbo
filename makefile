#Makefile
all: sum-nbo

sum-nbo:
	g++ -o sum-nbo main.cpp

#main.o: main.cpp
	#g++ -c -o main.o main.cpp

clean:
	rm -f sum-nbo
	#rm -f *.o

