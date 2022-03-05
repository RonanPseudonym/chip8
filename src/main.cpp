#include <iostream>
#include "gfx.h"

int main(int argc, char *argv[]) {
	parse_cli(argc, argv);

	br();
	
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

		add_conditional_flags();
		ok("Configured instruction set from command-line flags");
		br();

		ok("Setup complete");
		br();

		bool first_cycle = true;

		for (;;) {
			if (flags["slow_mode"]) {
				vm.cycle(win.keyout);
			} else {
				for (int i = 0; i < 10; i ++) { // 10 cycles per frame
					vm.cycle(win.keyout);
				}
			}

			if (first_cycle) {
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
