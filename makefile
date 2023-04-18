machineLangSim: driver.o
	g++ -o machineLangSim driver.o 
driver.o: driver.cpp 
	g++ -c driver.cpp 
clean:
	rm *.o machineLangSim
