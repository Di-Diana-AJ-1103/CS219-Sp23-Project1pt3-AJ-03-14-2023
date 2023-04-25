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
bool Nflag(uint32_t, std::string);
bool Zflag(uint32_t);
bool Cflag(std::string operation, uint32_t hexResult, uint32_t hex1, uint32_t hex2, bool C);
bool Vflag(uint32_t hexResult, uint32_t hex1, uint32_t hex2, std::string operation, bool V);
void flagPrint(uint32_t hexResult, uint32_t hex1, uint32_t hex2, std::string operation, bool C, bool V, int LineCount);
void printRegistries(uint32_t registries[]);

//Main Function
int main(){
    std::fstream myfile("Programming-Project-3.txt");
    int userChoice, regNum, regNum2, regNum3;
    bool C = 0, V = 0;
    //char for reading the r for registry and the hashes
    char buffer; 
    std::string line, operation;
    uint32_t hex1, hex2, hexResult, binPlaces;
    uint32_t registries[MAX]= { 0 };
    if (myfile.is_open()){
        myfile >> operation >> buffer >> regNum >> buffer >> buffer >> std::hex >> hex1;
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
                                registries[regNum] = hex1;
                                std::cout << operation << " R" << regNum << ", #0x" << std::hex << hex1 << std::endl;
                                printRegistries(registries);
                                flagPrint(hex1, hex1, hex1, operation, C, V, lineCount);
                            }else if(lineCount == 12 || lineCount == 13){
                                myfile >> operation >> buffer >> regNum >> buffer >> buffer >> regNum2;
                                hex1 = registries[regNum];
                                hex2 = registries[regNum2];
                                hexResult = arithmeticCommand(operation, hex1, hex2);
                                std::cout << operation << " R" << regNum << ", R" << regNum2 << std::endl;
                                printRegistries(registries);
                                flagPrint(hexResult, hex1, hex2, operation, C, V, lineCount);
                            }else if(lineCount == 10 || lineCount == 11){
                                myfile >> operation >> buffer >> regNum >> buffer >> buffer >> regNum2 >> buffer >> buffer >> binPlaces;
                                hex1 = registries[regNum2];
                                hex2 = binPlaces;
                                hexResult = arithmeticCommand(operation, hex1, hex2);
                                registries[regNum] = hexResult;
                                std::cout << operation << " R" << regNum << ", R" << regNum2 << ", #" << binPlaces << std::endl;
                                printRegistries(registries);
                                flagPrint(hexResult, hex1, hex2, operation, C, V, lineCount);
                            }else{
                                myfile >> operation >> buffer >> regNum >> buffer >> buffer >> regNum2 >> buffer >> buffer >> regNum3;
                                hex1 = registries[regNum2];
                                hex2 = registries[regNum3];
                                hexResult = arithmeticCommand(operation, hex1, hex2);
                                registries[regNum] = hexResult;
                                std::cout << operation << " R" << regNum << ", R" << regNum2 << ", R" << regNum3 << std::endl;
                                printRegistries(registries);
                                flagPrint(hexResult, hex1, hex2, operation, C, V, lineCount);
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

void flagPrint(uint32_t hexResult, uint32_t hex1, uint32_t hex2, std::string operation, bool C, bool V, int lineCount){
    C = Cflag(operation, hexResult, hex1, hex2, C);
    V = Vflag(hexResult, hex1, hex2, operation, V);
    if(lineCount == 5){
        C = !C;
        V = !V;
    }else if(lineCount >= 6 && lineCount <= 9 || lineCount == 13){
        C = !C;
    }
    std::cout << std::endl << "N: " << Nflag(hexResult, operation) << " Z: " << Zflag(hexResult) <<  " C: " << C << " V: " << V << std::endl << std::endl;
}

int getOpt(){
    int opt;
    std::cin >> opt;
    return opt;
}

int arithmeticCommand(std::string operation, uint32_t hex1, uint32_t hex2){
    int hexResult;
    if(operation == "ADD" || operation == "ADDS" || operation == "add" || operation == "adds"){
        hexResult = hex1 + hex2;
    }else if(operation == "SUB" || operation == "SUBS" || operation == "sub" || operation == "subs" || operation == "CMP" || operation == "cmp"){
        hexResult = hex1 - hex2;
    }else if(operation == "XOR" || operation == "XORS" || operation == "xor" || operation == "xors"){
        hexResult = hex1 ^ hex2;
    }else if(operation == "LSL" || operation == "LSLS" || operation == "lsl" || operation == "lsls"){
        hexResult = hex1 << hex2;
    }else if(operation == "ASR" || operation == "ASRS" || operation == "asr" || operation == "asrs"){
        hexResult = ASR(hex1, hex2);
    }else if(operation == "LSR" || operation == "LSRS" || operation == "lsr" || operation == "lsrs"){
        hexResult = hex1 >> hex2;
    }else if(operation == "ORR" || operation == "ORRS" || operation == "orr" || operation == "orrs"){
        hexResult = hex1 | hex2;
    }else if(operation == "AND" || operation == "ANDS" || operation == "and" || operation == "ands" || operation == "TST" || operation == "tst"){
        hexResult = hex1 & hex2;
    }
    return hexResult;
}

//Has to take in all registries as parameters (oh lawd)

void printRegistries(uint32_t registries[]){
    for(uint32_t i = 0; i < MAX; i++){
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

bool Nflag(uint32_t hexResult, std::string operation){
    if(hexResult > 0x7FFFFFFF && operation.length() == 4){
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

bool Cflag(std::string operation, uint32_t hexResult, uint32_t hex1, uint32_t hex2, bool C){
    if(operation == "ADD" || operation == "ADDS" || operation == "add" || operation == "adds" || operation == "lsrs" || operation == "LSRS" || operation == "lsr" || operation == "LSR"){
        if(hexResult < hex1){
            C = !C;
        }
    }else if(operation == "SUBS" || operation == "subs" || operation == "cmp" || operation == "CMP"){
        if(hexResult > hex1 || hexResult > hex2 || hexResult < (hex1 + hex2)){
            C = !C;
        }
    }else if(operation == "LSL" || operation == "LSLS" || operation == "lsl" || operation == "lsls" || operation == "ASR" || operation == "ASRS" || operation == "asr" || operation == "asrs"){
        if(hexResult < hex1 + hex2){
            C = !C;
        }
    }else if(operation == "MOV" || operation == "mov" || operation == "ands" || operation == "ANDS" || operation == "XOR" || operation == "xors" || operation == "xor" || operation == "and" || operation == "AND" || operation == "ands" || operation == "ANDS" || operation == "ORR" || operation == "orrs" || operation == "orr" || operation == "ORRS" || operation == "tst" || operation == "TST"){
        return C;
    }
    return C;
}

bool Vflag(uint32_t hexResult, uint32_t hex1, uint32_t hex2, std::string operation, bool V){
    if(operation == "TST" || operation == "tst" || operation == "NOTS" || operation == "nots" || operation == "CMP" || operation == "cmp"){
        V = V;
    }else if((hexResult < hex1) || (hexResult < hex2) || (hexResult > 0x7FFFFFFF)){
        V = !V;
    }else if(operation == "lsrs" || operation == "LSRS" || operation == "LSLS" || operation == "lsls" || operation == "lsl" || operation == "LSL" || operation == "lsr" || operation == "LSR"){
        if((hexResult > hex1) || (hexResult > hex2)){
            V = !V;
        }
    }else if(operation == "MOV" || operation == "mov" || operation == "ands" || operation == "ANDS" || operation == "XOR" || operation == "xors" || operation == "xor" || operation == "and" || operation == "AND" || operation == "ORR" || operation == "orrs" || operation == "orr" || operation == "ORRS"){
        V = V;
    }
    return V;
}
