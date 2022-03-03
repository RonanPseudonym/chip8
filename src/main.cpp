#include <iostream>
#include "gfx.h"

int main(int argc, char *argv[]) {
	ok("Started program");

	if (argc > 1) {
		VirtualMachine vm = VirtualMachine();

		br();
		ok("Created virtal machine");

		GFXWindow win = GFXWindow(argv[1]);
		ok("Created virtual display");

		br();
		vm.load_rom(argv[1]);

		ok("ROM loaded");

		br();
		ok("Setup complete");
		br();

		bool first_cycle = true;

		for (;;) {
			vm.cycle();

			if (first_cycle) {
				ok("Initial cycle completed");
				first_cycle = false;
			}

			if (!win.update(&vm) || err_flag) {
				br();
				warning("Leaving game loop");
				break;
			}
		}

		ok("Exited loop");

		// for (;;) {
		// 	win.update();
		// }
	} else {
		error("No ROM specified, try using command-line arguments to specify");
	}

	ok("Program ended");
}