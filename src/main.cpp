#include <iostream>
#include "vm.h"

int main(int argc, char *argv[]) {
	if (argc > 1) {
		VirtualMachine vm = VirtualMachine();

		vm.load_rom(argv[1]);
		vm.cycle();

		for (;;) {
			vm.cycle();
		}
	}
}