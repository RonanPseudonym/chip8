main.o : src/main.cpp src/vm.h src/read.h src/stack.h src/gfx.h
	g++ -o main.o src/main.cpp