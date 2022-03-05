#include <iostream>
#include <map>

#include "read.h"
#include "stack.h"

class VirtualMachine {
	private:
		unsigned short opcode;

		unsigned char memory[4096];
		unsigned char V[16];

		Stack stack;

		unsigned short I;

		unsigned int SP;
		unsigned short PC;

	public:
		bool gfx[32][64];
		bool draw_flag;

		unsigned int sound_timer;
		unsigned int display_timer;

		std::map<std::string, bool> announcements {
			{"original_shift", false},
			{"modern_offset_jump", false},
			{"original_store_and_load", false}
		};

		void announce(std::string ann) {
			if (announcements[ann]) {
				return;
			}

			announcements[ann] = true;
			info(ann + " is set to " + (flags[ann] ? "true" : "false") + ", corresponding instruction was just used");
		}

		VirtualMachine() {
			srand(time(0));
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

		void interpret(char keyout) {
			Instruction instr = Instruction(opcode);

			if (flags["slow_mode"])
				info("Executing instruction " + instr.opcode);

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

				case IType::RET: // Also autocompleted (kinda)
					PC = stack.pop();

					break;
					

				case IType::JP_ADDR:
					PC = instr.addr;

					break;

				case IType::CALL_ADDR: // Autocompleted, might not work
					stack.push(PC + 2); // Especially don't trust the +2
					PC = instr.addr;

					break;

				case IType::SE_VX_BYTE:
					if (V[instr.x] == instr.byte) {
						PC += 2;
					}

					PC += 2;
					break;

				case IType::SNE_VX_BYTE:
					if (V[instr.x] != instr.byte) {
						PC += 2;
					}

					PC += 2;
					break;

				case IType::SE_VX_VY:
					if (V[instr.x] == V[instr.y]) {
						PC += 2;
					}

					PC += 2;
					break;

				case IType::LD_VX_BYTE:
					V[instr.x] = instr.byte;

					PC += 2;
					break;

				case IType::ADD_VX_BYTE: { // These might have overflow issues
					unsigned short sum = V[instr.x] + instr.byte;

					if (sum > 255) V[0xF] = 1;
					else V[0xF] = 0;

					V[instr.x] = sum; // Pretty sure this works?

					PC += 2;
					break;
				}

				case IType::LD_VX_VY:
					V[instr.x] = V[instr.y];

					PC += 2;
					break;

				case IType::OR_VX_VY:
					V[instr.x] |= V[instr.y];

					PC += 2;
					break;

				case IType::AND_VX_VY:
					V[instr.x] &= V[instr.y];

					PC += 2;
					break;

				case IType::XOR_VX_VY:
					V[instr.x] ^= V[instr.y];

					PC += 2;
					break;

				case IType::ADD_VX_VY: {
					unsigned short sum = V[instr.x] + V[instr.y];

					if (sum > 255) V[0xF] = 1;
					else V[0xF] = 0;

					V[instr.x] = sum; // Pretty sure this works?

					PC += 2;
					break;
				}

				case IType::SUB_VX_VY: {
					if (V[instr.x] > V[instr.y]) V[0xF] = 1;
					else V[0xF] = 0;

					V[instr.x] -= V[instr.y];

					PC += 2;
					break;
				}

				case IType::SHR_VX: {
					if (flags["original_shift"]) {
						V[instr.x] = V[instr.y];
					}

					// Don't trust this

					bool x_last_bit = V[instr.x] & 0x1;
					V[0xF] = x_last_bit ? 1 : 0;

					V[instr.x] /= 2;

					PC += 2;

					announce("original_shift");
					break;
				}

				case IType::SUBN_VX_VY: {
					if (V[instr.x] > V[instr.y]) V[0xF] = 1;
					else V[0xF] = 0;

					V[instr.y] -= V[instr.x];

					PC += 2;
					break;
				}

				case IType::SHL_VX: {
					if (flags["original_shift"]) {
						V[instr.x] = V[instr.y];
					}

					bool x_last_bit = V[instr.x] & 0x1;
					V[0xF] = x_last_bit ? 1 : 0;

					V[instr.x] *= 2;

					PC += 2;

					announce("original_shift");
					break;
				}

				case IType::SNE_VX_VY: {
					if (V[instr.x] != V[instr.y]) PC += 2;

					PC += 2;
					break;
				}

				case IType::LD_I_ADDR:
					I = instr.addr;

					PC += 2;
					break;

				case IType::JP_V0_ADDR:
					if (flags["modern_offset_jump"]) {
						PC = instr.addr + V[instr.hex_loc_of(instr.addr_str[1])] + 2; // +2?
					} else {
						PC = instr.addr + V[0] + 2; // +2?
					}

					announce("modern_offset_jump");
					break;

				case IType::RND_VX_BYTE:
					V[instr.x] = (rand() % 256) & instr.byte; // I think rand() is % 256 but I'm not sure

					PC += 2;
					break;

				case IType::DRAW_X_Y_NIBL: { // This is a spooky one
					unsigned char x = V[instr.x] % 64;
					unsigned char y = V[instr.y] % 32;
					unsigned char height = instr.nibble;

					// print out x y and height
					// std::cout << "x: " << +x << " y: " << +y << " height: " << +height << std::endl;

					V[0xF] = 0;

					for (int yp = 0; yp < height; yp ++) {
						unsigned char row = memory[I + yp];

						// Turn row into an array of bools
						bool row_bools[8];
						for (int i = 0; i < 8; i ++) {
							row_bools[i] = (row & (1 << (7-i))) != 0;
						}

						// bool row_bools_2[8];

						// // Reverse row_bools
						// for (int i = 0; i < 8; i ++) {
						// 	row_bools_2[7-i] = row_bools[i];
						// }

						// Print out row_bools
						// for (int i = 0; i < 8; i ++) {
						// 	std::cout << row_bools_2[i] << " ";
						// }

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

				case SKP_VX:
					if (V[instr.x] == keyout) PC += 2;

					PC += 2;
					break;

				case SKNP_VX:
					if (V[instr.x] != keyout) PC += 2;

					PC += 2;
					break;

				case LD_VX_DT:
					V[instr.x] = display_timer;

					PC += 2;
					break;

				// case LD_VX_K:
				// 	// Key stuff

				// 	PC += 2;
				// 	break;

				case LD_DT_VX:
					display_timer = V[instr.x];

					PC += 2;
					break;

				case LD_ST_VX:
					sound_timer = V[instr.x];

					PC += 2;
					break;

				case ADD_I_VX:
					I += V[instr.x];

					PC += 2;
					break;

				// case LD_F_VX:
				// 	// Icky font stuff

				// 	PC += 2;
				// 	break;

				// case LD_B_VX:
				// 	// Lmao what

				// 	PC += 2;
				// 	break;

				case LD_I_VX:
					if (flags["original_store_and_load"]) {
						for (int i = 0; i < instr.x; i ++) {
							memory[I] = V[i];
							I ++;
						}

						I += instr.x + 1;
					} else {
						for (int i = 0; i < instr.x; i ++) {
							memory[I + i] = V[i];
						}
					}

					PC += 2;

					announce("original_store_and_load");
					break;

				case LD_VX_I:
					if (flags["original_store_and_load"]) {
						for (int i = 0; i < instr.x; i ++) {
							V[i] = memory[I];
							I ++;
						}

						I += instr.x + 1;
					} else {
						for (int i = 0; i < instr.x; i ++) {
							V[i] = memory[I + i];
						}
					}

					PC += 2;

					announce("original_store_and_load");
					break;

				default:
					warning("Instruction "+std::to_string(instr.type)+" ["+instr.opcode+"] not implemented");

					PC += 2;
					break;
			}
		}

		void cycle(char keyout) {
			draw_flag = false;

			current();
			interpret(keyout);

			if (display_timer > 0)
				display_timer --;

			if (sound_timer > 0)
				sound_timer --;
		}
};