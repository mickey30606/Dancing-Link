all:DL.o run.o
	g++ -g -o run DL.o run.o
DL.o:DL.cpp DL.h
	g++ -g -c DL.cpp DL.h
run.o:run.cpp DL.h
	g++ -g -c run.cpp DL.h
clean:
	rm *.o run *.gch
