all: prog limpa

prog: linear input render aresta object geometry main
	g++ main.o Render.o Linear.o Input.o Aresta.o Object.o Geometry.o -o prog -lSDL2 -lSDL2_image

input: 
	g++ Input.cpp -c -Wall -g

main: 
	g++ main.cpp -c -Wall -g

linear: 
	g++ Linear.cpp -c -Wall -g

render: 
	g++ Render.cpp -c -Wall -g

geometry: 
	g++ Geometry.cpp -c -Wall -g

aresta: 
	g++ Aresta.cpp -c -Wall -g

object: 
	g++ Object.cpp -c -Wall -g

limpa: 
	rm *.o

