#include <iostream>

// #include "read.h"
#include "stack.h"
#include "instruction.h"

class VirtualMachine {
	private:
		unsigned short opcode;

		unsigned char memory[4096];
		unsigned char V[16];

		Stack stack;

		unsigned short I;

		unsigned int SP;
		unsigned short PC;

		unsigned int sound_timer;
		unsigned int display_timer;

	public:
		bool gfx[32][64];
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

		// void advance() {
		// 	PC += 2;
		// }

		void interpret() {
			Instruction instr = Instruction(opcode);

			switch (instr.type) {
				case IType::CLS:
					// Fill gfx with 0s
					for (int i = 0; i < 32; i++) {
						for (int j = 0; j < 64; j++) {
							gfx[i][j] = false;
						}
					}

					PC += 2;
					break;

				case IType::JUMP_ADDR:
					PC = instr.addr;

					break;

				case IType::LD_VX_BYTE:
					V[instr.x] = instr.byte;

					PC += 2;
					break;

				case IType::ADD_VX_BYTE:
					V[instr.x] += instr.byte;

					PC += 2;
					break;

				case IType::LD_I_ADDR:
					I = instr.addr;

					PC += 2;
					break;

				case IType::DRAW_X_Y_NIBL:
					unsigned char x = V[instr.x] % 64;
					unsigned char y = V[instr.y] % 32;
					unsigned char height = instr.nibble;

					V[0xF] = 0;

					for (int yp = 0; yp < height; yp ++) {
						unsigned char row = memory[I + yp];

						// Turn row into an array of bools
						bool row_bools[8];
						for (int i = 0; i < 8; i ++) {
							row_bools[i] = (row & (1 << i)) != 0;
						}

						for (int xp = 0; xp < 8; xp ++) {
							bool bit = row_bools[xp];

							if (bit && gfx[y + yp][x + xp] == true) { // if both are on
								gfx[y + yp][x + xp] = false;
								V[0xF] = 1;
							} else if (bit) {
								gfx[y + yp][x + xp] = true;
							}

							if (x + xp >= 64 || y + yp >= 32) {
								warning("X or Y is out of bounds, skipping rest of sprite line");
								break;
							}
						}
					}

					draw_flag = true;

					PC += 2;
					break;
			}
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