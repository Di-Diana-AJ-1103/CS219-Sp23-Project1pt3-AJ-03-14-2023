# Project 1, part 3: Machine Language Simulator
## Author: AJ Di Diana

## Program
The chosen language is c++ for this project; it includes the makefile to create the executable "machineLangSim" along with the main.cpp for the main driver code, and the Programming-Project-3.txt for the use of reading ARM UAL code instructions. This program will perform a series of bitwise operations depending on the operation listed before the selected 2 hexadecimals (or integers for shifting) and it will print them to the terminal as well as the hexadecimal result after said bitwise operation. This program also outputs NZCV flags after each operation. In the menu there is also an option to print out the file contents to the terminal or to exit the program. 

TLDR: Performs an assortment of bitwise operations, shows set flags, shows results in registers, able to print out file contents, able to give the user an option to exit program.

## File List
1.  main.cpp -> The main driver code, the motherboard of this coding project.
2.  makefile -> The makefile that compiles all the files into one executable (in this case: machineLangSim).
    - This will be used to create objects like the main.o object as well, an object containing all of the main driver code in one little neat package.
3.  Programming-Project-3.txt -> A sample containing the desired operation and the hexadecimals to perform said operation.
4.  README.md -> The file you are currently reading -- it contains all of the information you need to know about how the program operates (roughly).

## Components
1.	The machine language simulator uses an interactable menu to perform bitwise operations with hexadecimals.
2.	Reads in assembly instructions and performs them accordingly and store them into their assigned registry.
3.	Able to store hexadecimals in "registers" and display them (0-7).
4.  Displays whether or not NZCV flags are set.
5.  Has the hexadecimals and operations in question read from an external .txt file. 

## Execution
To nagivate to the folder holding this project, make sure to  type "cd AJ-Di-Diana-Programming-Project1-Part2"
    - Use the "ls" command to look for the directories you need to help navigate further.
To run the file, type "make" then "./machineLangSim" in the command line.
If the executable "machineLangSim" and "main.o" object are already present, skip to typing in "./machineLangSim"


