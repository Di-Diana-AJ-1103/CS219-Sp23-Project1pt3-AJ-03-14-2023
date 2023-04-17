machineLangSim: main.o
	g++ -o machineLangSim main.o 
main.o: main.cpp 
	g++ -c main.cpp 
clean:
	rm *.o machineLangSim
