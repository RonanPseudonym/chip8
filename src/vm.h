#include <iostream>

#include "read.h"
#include "stack.h"
#include "instruction.h"

class VirtualMachine {
	private:
		unsigned short opcode;

		unsigned char memory[4096];
		unsigned char V[16];

		Stack stack;

		unsigned short I;
		unsigned short PC;

		unsigned int SP;

		unsigned int sound_timer;
		unsigned int display_timer;

	public:
		bool gfx[64 * 32];
		bool draw_flag;

		VirtualMachine() {
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
			Instruction instr = Instruction(opcode);

			// switch (opcode) {
			// 	case 0x00E0: // CLS
			// 		std::fill_n(gfx, 64 * 32, false);
			// 		PC += 2;
			// 		draw_flag = true;
			// 		return;
			// 	// case 0x00EE: // RET || TODO: check if this is correct
			// 	// 	pc = stack.get_top();
			// 	// 	pc += 2;
			// 		// break;
			// }

			// switch(opcode & 0xF000) { // first digit: has to be > 0, other digits: impossible to be more than 0
			// 	case 0x1000: // GOTO

			// 		PC += 2;
			// 		return;

			// 	// case 0x2000: // CALL

			// 	// 	PC += 2;
			// 	// 	return;
					
			// 	// case 0x3000: // SKIP if Vx == kk

			// 	// 	PC += 2;
			// 	// 	return;

			// 	// case 0x4000: // SKIP if Vx != kk

			// 	// 	PC += 2;
			// 	// 	return;

			// 	// case 0x5000: // SKIP if Vx == Vy

			// 	// 	PC += 2;
			// 	// 	return;

			// 	case 0x6000: // Vx = kk

			// 		PC += 2;
			// 		return;

			// 	case 0x7000: // Vx += kk

			// 		PC += 2;
			// 		return;

			// 	case 0xA000: // SET INDEX REGISTER

			// 		PC += 2;
			// 		return;

			// 	case 0xD000: // DRAW

			// 		PC += 2;
			// 		return;

			// }
		}

		void cycle() {
			draw_flag = false;

			current();
			interpret();

			if (display_timer > 0)
				display_timer --;

			if (sound_timer > 0)
				sound_timer --;
		}
};