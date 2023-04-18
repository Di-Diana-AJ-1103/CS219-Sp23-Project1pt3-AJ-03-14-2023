// --------------------------------------
// AUTHOR: AJ Di Diana
// Class: CS219
// Program: Machine Language Simulator
// Part1: 02-22-2023
// Part2: 03-31-2023
// Part3: 04-22-2023
// --------------------------------------
//Libraries and headers
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#define MAX 8

//Prototype functions
void mainMenu();
int getOpt();
int arithmeticCommand(std::string, uint32_t, uint32_t);
int ASR(uint32_t, uint32_t);
bool Nflag(uint32_t);
bool Zflag(uint32_t);
bool Cflag();
bool Vflag(uint32_t hexResult, uint32_t hex1, uint32_t hex2);
void flagPrint(uint32_t hexResult, uint32_t hex1, uint32_t hex2, std::string operation);

//Main Function
int main(){
    std::fstream myfile ("Programming-Project-3.txt");
    int userChoice, regNum;
    //char for reading the r for registry and the hashes
    char buffer; 
    std::string line, operation;
    uint32_t hex1, hex2, hexResult, binPlaces;
    int registries[MAX];

    if (myfile.is_open()){
        myfile >> operation >> std::hex >> hex1 >> std::hex >> hex2;
        myfile.close();
    }else{
        std::cout << "Unable to open file" << std::endl;
    }
        do{
        mainMenu();
        userChoice = getOpt();
        switch(userChoice){
            case 1:
                myfile.open ("Programming-Project-3.txt");
                if (myfile.is_open()){
                    while (myfile.good()){
                        for(int lineCount = 1; lineCount <= 13; lineCount++){
                            //needs to be fixed
                            if(lineCount == 1 || lineCount == 2 || lineCount == 5 || lineCount == 9){
                                myfile >> operation >> buffer >> regNum >> buffer >> buffer >> std::hex >> hex1;
                                hexResult = ~hex1;
                                std::cout << operation << " 0x" << std::hex << hex1 << ": 0x" << std::hex << hexResult << std::endl;
                            }else if(lineCount >= 9 && lineCount <= 20){
                                myfile >> operation >> std::hex >> hex1 >> binPlaces;
                                hexResult = arithmeticCommand(operation, hex1, binPlaces);
                                std::cout << operation << " 0x" << std::hex << hex1 << " " << binPlaces << ": 0x" << std::hex << hexResult << std::endl;
                                flagPrint(hexResult, hex1, hex2, operation);
                            }else{
                                myfile >> operation >> std::hex >> hex1 >> std::hex >> hex2;
                                hexResult = arithmeticCommand(operation, hex1, hex2);
                                std::cout << operation << " 0x" << std::hex << hex1 << " 0x" << std::hex << hex2 << ": 0x" << std::hex << hexResult << std::endl;
                                flagPrint(hexResult, hex1, hex2, operation);
                            }
                        }
                    }
                    myfile.close();
                }else{
                    std::cout << "Unable to open file" << std::endl;
                }
                break;
            case 2:
                myfile.open ("Programming-Project-3.txt");
                if (myfile.is_open()){
                    while (!myfile.eof()){
                        getline(myfile, line);
                        std::cout << "" << line << std::endl;
                    }
                    myfile.close();
                }else{
                    std::cout << "Unable to open file" << std::endl;
                }
                break;
            case 0:
                std::cout << "Exiting simulation..." << std::endl;
                break;
            default:
                std::cout << "Invalid Input." << std::endl;
        }
    }while(userChoice != 0);
    return 0;
}

//Displays main menu
void mainMenu(){
    std::cout << std::endl << "Welcome to the Machine Language Simulator! Please choose a command (Number)." << std::endl <<
                 "  1 -> Perform Operations" << std::endl <<
                 "  2 -> Display File Contents" << std::endl <<
                 "  0 -> Exit Sim" << std::endl;       
}

void flagPrint(uint32_t hexResult, uint32_t hex1, uint32_t hex2, std::string operation){
    if(operation.length() == 4){
        std::cout << "N: " << Nflag(hexResult) << " Z: " << Zflag(hexResult) << " V: " << Vflag(hexResult, hex1, hex2) << std::endl;
    }else{
        std::cout << "N: 0 " << " Z: 0" << " C: 0" << " V: 0" << std::endl;
    }
}

int getOpt(){
    int opt;
    std::cin >> opt;
    return opt;
}

int arithmeticCommand(std::string operation, uint32_t hex1, uint32_t hex2){
    int hexResult;
    if(operation == "ADD" || "ADDS" || "add" || "adds"){
        hexResult = hex1 + hex2;
    }else if(operation == "SUB" || "SUBS" || "sub" || "subs"){
        hexResult = hex1 - hex2;
    }else if(operation == "XOR" || "XORS" || "xor" || "xors"){
        hexResult = hex1 ^ hex2;
    }else if(operation == "LSL" || "LSLS" || "lsl" || "lsls"){
        hexResult = hex1 << hex2;
    }else if(operation == "ASR" || "ASRS" || "asr" || "asrs"){
        hexResult = ASR(hex1, hex2);
    }else if(operation == "LSR" || "LSRS" || "lsr" || "lsrs"){
        hexResult = hex1 >> hex2;
    }else if(operation == "ORR" || "ORRS" || "orr" || "orrs"){
        hexResult = hex1 | hex2;
    }else if(operation == "AND" || "ANDS" || "and" || "ands"){
        hexResult = hex1 & hex2;
    }
    return hexResult;
}

//Has to take in all registries as parameters (oh lawd)
void moveRegister(std::string operation, int registries[] ,int regNum, uint32_t hex1){
    registries[regNum] = hex1;
}

void printRegisters(int registries[]){
    for(int i = 0; i < MAX; i++){
        std::cout << "R" << i << ":0x" << registries[i] << " ";
    }
}

int ASR(uint32_t hex1, uint32_t  hex2){
    int hexResult;
    if(hex1 == 0xffffffff || hex2 == 0xffffffff){ //edge case
        hexResult = hex1 >> hex2 | ~(~0x0U >> hex2);
    }else{
        hexResult = hex1 >> hex2;
    }
    return hexResult;
}

bool Nflag(uint32_t hexResult){
    if(hexResult > 0x7FFFFFFF){
        return true;
    }
    return false;
}

bool Zflag(uint32_t hexResult){
    if(hexResult == 0){
        return true;
    }
    return false;
}

bool Cflag(){

}

bool Vflag(uint32_t hexResult, uint32_t hex1, uint32_t hex2){
    if((hexResult < hex1) || (hexResult < hex2)){
        return true;
    }else{
        return false;
    }
}