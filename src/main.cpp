#include <iostream>
#include "gfx.h"

int main(int argc, char *argv[]) {
	if (argc > 1) {
		VirtualMachine vm = VirtualMachine();
		GFXWindow win = GFXWindow();

		vm.load_rom(argv[1]);

		for (;;) {
			vm.cycle();
			if (!win.update(&vm)) {
				break;
			}
		}

		// for (;;) {
		// 	win.update();
		// }
	}
}