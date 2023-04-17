machineLangSim: driver.o
	g++ -o machineLangSim main.o 
driver.o: driver.cpp 
	g++ -c driver.cpp 
clean:
	rm *.o machineLangSim
