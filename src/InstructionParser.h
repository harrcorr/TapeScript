#include "Cpu.h"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

bool isInstruction(CPU* cpu, std::string instruction);
bool isMemAddress(std::string argument);
bool isRegister(std::string argument);
std::string replaceStr(std::string s,std::string toReplace="\"");

bool loadDataToRegister(CPU* cpu,std::string registerName,std::string source);
void printDatatoSTDout(std::string toPrint);
int executeInstruction(CPU enums,CPU* cpu,std::vector<std::string> instruction);

