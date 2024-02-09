all: test main

pugi: pugixml.cpp
	g++ -c pugixml.cpp
main: pugi main.cpp graph.cpp haversine.cpp
	g++ main.cpp graph.cpp haversine.cpp shortestpath.cpp weightFunctionAdd.cpp weightFunctionMin.cpp weightFunctionCompose.cpp weightFunction.cpp pugixml.o -o main -lSDL2 -g
test: functionTest.cpp weightFunction.cpp weightFunctionMin.cpp
	g++ functionTest.cpp weightFunction.cpp weightFunctionMin.cpp -o test -g
clean:
	rm -f main
	rm -f test
	rm -f pugixml.o