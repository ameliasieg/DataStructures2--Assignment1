all: proj1.x

proj1.x: mydriver.o
	g++ -std=c++11 mydriver.o -o proj1.x

mydriver.o: mydriver.cpp
	g++ -std=c++11 -c mydriver.cpp

clean:
	rm *.o *.x