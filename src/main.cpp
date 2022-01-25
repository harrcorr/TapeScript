
#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include "./InstructionParser.h"
std::vector<std::string> readFile(std::string file){
	std::ifstream in;
	in.open(file);
	std::string str;
	std::vector<std::string> instructions;
    while (std::getline(in, str))
    {
    	if(str.size() > 0){ instructions.push_back(str); };
    }
	return instructions;
}
std::vector<std::string> tokenize(std::string ins,std::string del = " "){
  	int start = 0;
	std::vector<std::string> tokens;
    int end = ins.find(del);
    while (end != -1) {
		tokens.push_back(ins.substr(start, end - start));
        start = end + del.size();
        end = ins.find(del, start);
    }
	tokens.push_back(ins.substr(start, end - start));
	return tokens;
}
void render(CPU* cpu){
	std::cout << "registers: \n";
	for(std::pair<std::string,int> reg : cpu->registers){
		std::cout << reg.first << " : " << reg.second << "\n";
	}
	std::cout << "Tape: \n";
	for(int i = 0; i < 100; i++){
		if(i < 0){
			std::cout << " ";
		}else{
			if(i%10 == 0){
				std::cout << "\n";
			}else{
				std::cout << ",";
			}
			if(i != cpu->registers["StackPointer"]){
			std::cout << cpu->tape[i];
			}else{
			std::cout << "_" << cpu->tape[i] << "_";

			}
		}

	}
	// print the text buffer from the cpu after rendering all other information
	std::cout << "\n\n";
	std::cout << "----------- OUTPUT -----------\n";
	for(int i = 0; i < cpu->textBuffer.size();i++){
		std::cout << cpu->textBuffer[i];
	}
	std::cout << "------------------------------\n";
}
void indexLables(CPU* cpu,std::vector<std::vector<std::string> > instructions){
	for(int i = 0; i < instructions.size(); i++){
		if(instructions[i][0] == ":"){	
			cpu->labelCache.insert(std::pair<std::string,int>(instructions[i][1],i-1));
		}
		
	}

}
bool awaitInput = false;
bool clockSpeed = 2;
int main(int argc, char** argv){
	CPU cpu;
	std::vector<std::string> ins = readFile(argv[1]);
	// iterate over all instructions and tokenize them
	// (break them down into command and argument)
	std::vector<std::vector<std::string> > tokenizedInstructions;
	for(int i = 0; i < ins.size(); i++){
		std::vector<std::string> tokenized = tokenize(ins[i]);
		tokenizedInstructions.push_back(tokenized);
		// also test if the instruction contains a label as these need to be stored seperately so they can be
		// accessed at any time
		indexLables(&cpu,tokenizedInstructions);
	}
	std::string in;
	while(cpu.registers["InstructionPointer"] != tokenizedInstructions.size()){
		// if some code doesnt work on your system you may need to change these two instructions
		// sleep(clockSpeed)
		// and
		// system("clear")
		// to your systems equivalent
		// (this application was written for ArchLinux 5.16.2) 
		// ahem obligatory i use arch btw ahem
		system("clear");			
		executeInstruction(cpu,&cpu,tokenizedInstructions[cpu.registers["InstructionPointer"]]);
		render(&cpu);
		if(awaitInput){
		std::cin >> in;
		}else{
			sleep(clockSpeed);
		}
	}
	return 0;
}
