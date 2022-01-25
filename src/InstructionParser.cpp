#include "./InstructionParser.h"
bool isInstruction(CPU* cpu, std::string instruction){
	// test if instruction is in CPU instruction map 
	try{
		cpu->instructionMap.at(instruction);
		return true;
	}catch(std::out_of_range){
		return false;
	}
}
// determine datatype of args
bool isMemAdress(std::string argument){
	return (argument.find("0x") == std::string::npos) ? false : true;	
}
bool isRegister(std::string argument){
	// test is argument is surrounded by quotes if it is its likely a register so return true
	if(argument.length() != 0){
	if(argument.c_str()[0] == '"' && argument.c_str()[argument.length()-1] == '"' ) { return true; }
	}
	return false;
}
// --------------------------------------- 

std::string replaceStr(std::string s,std::string toReplace){
 	size_t pos = 0;
	std::string replace = "\0";
    while ((pos = s.find(toReplace, pos)) != std::string::npos) {
         s.replace(pos, toReplace.length(), replace);
         pos += replace.length();
    }
    return s;
}
// this function does what is says on the tin and stops me repeating the same error checking over and over
// for all register operations
bool loadDataToRegister(CPU* cpu,std::string registerName,std::string source){
	if(isRegister(source)){
		std::cout << "stripped register string " << replaceStr(source) << "\n";
		cpu->registers[registerName] = cpu->registers[replaceStr(source)];		
	}else{
		cpu->registers[registerName] = std::stoi(source);
	}
	return true;
}
// using a function for this allows greater syntatic sugar if its wanted
void printDatatoSTDout(CPU* cpu, std::string toPrint){
	cpu->textBuffer.push_back(toPrint + "\n");

}
int executeInstruction(CPU enums,CPU* cpu,std::vector<std::string> instruction){
	
	// sorting args and command into seperate objects for ease of access
	std::string command = instruction[0];
	std::vector<std::string> args;
	std::cout << "Executing : ";
	std::cout << command << " ";
	for(int i = 1; i < instruction.size(); i++){
		std::cout << instruction[i] << " ";
		// print the command and arguments for the end user
		args.push_back(instruction[i]);
	}
	std::cout << "\n";

	// confirm that the instruction about to be executed is a valid command
	// if not halt
	// if it is continue on
	if(isInstruction(cpu, command)){
		// this is the primary switch statement for parsing instructions
		// for implementation details please refer to README.MD
		switch( cpu->instructionMap.at(command) ){
			case enums.LOADA:
				loadDataToRegister(cpu,"A",args[0]);
				break;
			case enums.LOADB:
				loadDataToRegister(cpu,"B",args[0]);
				break;
			case enums.LOADC:
				loadDataToRegister(cpu,"C",args[0]);
				break;
			case enums.PRINT:
				if(isMemAdress(args[0])){
					std::string address = replaceStr(args[0],"0x");
					printDatatoSTDout(cpu,std::to_string(cpu->tape[std::stoi(address)]));
				
				}else if(isRegister(args[0])){

					std::string address = replaceStr(args[0]);
					printDatatoSTDout(cpu,std::to_string(cpu->registers[address]));
				
				}else{
					printDatatoSTDout(cpu,args[0]);
				}
				break;
			case enums.STORE:
				cpu->tape[cpu->registers["StackPointer"]] = cpu->registers[args[0]];
				break;
			case enums.SHIFTLEFT:
				if(cpu->registers["StackPointer"]-1 >= 0){
					cpu->registers["StackPointer"]-=1;					
				}
				break;
			case enums.SHIFTRIGHT:
				cpu->registers["StackPointer"]=cpu->registers["StackPointer"]+1;
				break;
			case enums.SET:
				cpu->registers[args[0]] = cpu->registers[args[1]];
				break;
			case enums.SUB:
				cpu->registers["MathOp"] = cpu->registers[args[0]] - cpu->registers[args[1]];
				break;
			case enums.ADD:
				cpu->registers["MathOp"] = cpu->registers[args[0]] + cpu->registers[args[1]];
				break;
			case enums.JMP:
				cpu->registers["InstructionPointer"] = cpu->labelCache[args[0]];
				break;
			case enums.IF:
				if(cpu->registers[args[0]] == cpu->registers[args[1]]){
					std::vector<std::string> newCommand;
					for(int i = 2; i < args.size(); i++){
						newCommand.push_back(args[i]);
					}
					std::cout << "executing new instruction";
					executeInstruction(enums,cpu,newCommand);
				}
				break;
			

			defualt:
				// if some strange error occurs where the instruction passes the is instruction test but doesnt have an implementation then exit
				std::cout << "Critical Error.... terminating\n";
				return -1;
	
		}
		cpu->registers["InstructionPointer"]++;
	}else{
		// since it would be wasteful to load the : ( label ) charachter as an instruction we just ignore it in error checking
		if(command != ":"){
		std::cout << "instruction " << command << " does not exist!\n";
		return -1;
		}else{
			// if it is actually valid but without an instruction implementation store continue
			// else halt with implementation as above
			cpu->registers["InstructionPointer"]++;
		}
	}

	return 1;
}
