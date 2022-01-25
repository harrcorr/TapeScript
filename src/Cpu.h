#pragma once
#include <map>
#include <string>
#include <vector>
struct CPU{
	// the buffsize for the tape is 1k 
	int tape[1000];
	// this is the format for cpu instructions
	// you add the command as an enum 
	// and then add the enum to the map with a string representation 
	// this allows the instruction parser to register ids without using random intreger ids
	std::vector<std::string> textBuffer;
	enum instructions 
	{
		LOADA,
		LOADB,
		LOADC,
		PRINT,
		STORE,
		SHIFTLEFT,
		SHIFTRIGHT,
		SET,
		ADD,
		SUB,
		JMP,
		IF,

	};
	// instruction implementations are in ./InstructionParser.cpp
	// instruction usage is in README.MD
	const std::map<std::string,instructions> instructionMap = { 
		{"LOADA",LOADA},
		{"LOADB",LOADB},
		{"LOADC",LOADC},
		{"PRINT",PRINT},
		{"STORE",STORE},
		{"SHIFTLEFT",SHIFTLEFT},
		{"SHIFTRIGHT",SHIFTRIGHT},
		{"SET",SET},
		{"SUB",SUB},
		{"ADD",ADD},
		{"JMP",JMP},
		{"IF",IF},
	};
	std::map<std::string,int> registers = {{"A",0},{"B",0},{"C",0},{"InstructionPointer",0},{"StackPointer",0},{"MathOp",0} };
	std::map<std::string,int> labelCache;
};
