FLAGS := -lSDL2 -lSDL2main -std=c++11
CC    := g++

a.out : src/main.cpp src/gfx.h src/read.h src/stack.h src/vm.h src/instruction.h src/decode.h src/debug.h
	$(CC) $(FLAGS) src/main.cpp