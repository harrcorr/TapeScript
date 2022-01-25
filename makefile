CC=g++

all: build/InstructionParser.o build/main.o
	${CC} -o build/TapeScript build/InstructionParser.o build/main.o
build/InstructionParser.o: src/InstructionParser.cpp src/InstructionParser.h
	${CC} -c src/InstructionParser.cpp -o build/InstructionParser.o
build/main.o: src/Cpu.h src/main.cpp
	${CC} -c src/main.cpp -o build/main.o	


/build/main.o: 

