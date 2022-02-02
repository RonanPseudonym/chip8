#include <iostream>

#include "read.h"
#include "stack.h"
#include "gfx.h"

class VirtualMachine {
	private:
		unsigned short opcode;

		unsigned char memory[4096];
		unsigned char V[16];

		Stack stack;
		GFXWindow window;

		unsigned short I;
		unsigned short PC;

		unsigned int SP;

		unsigned int sound_timer;
		unsigned int display_timer;

		bool gfx[64 * 32];

	public:
		VirtualMachine() {
			stack = Stack();
		}

		void load_fontset(unsigned char font[80])
		{
			for (int i = 0; i < 80; i ++) {
				memory[i] = font[i];
			}
		}

		void load_rom(std::string name) {
			RomLoader rom_loader = RomLoader(name);
			rom_loader.load();
			rom_loader.load_to_memory(memory, 512);

			PC = 512;
		}

		void current() {
			unsigned char c0 = memory[PC];
			unsigned char c1 = memory[PC + 1];

			unsigned short c0s = memory[PC + 1];

			opcode = c0 << 8 | c1;
		}

		void advance() {
			PC += 2;
		}

		void interpret() {
			switch(opcode) {
				// case 0x00E0: // CLS
				// 	std::fill_n(gfx, 64 * 32, false);
				// 	break;

				// case 0x00EE: // RET
				// 	std::fill_n(gfx, 64 * 32, false);
				// 	break;
			}
		}

		void cycle() {
			current();
			interpret();

			if (display_timer > 0)
				display_timer --;

			if (sound_timer > 0)
				sound_timer --;
		}
};