#include <iomanip>
#include <string>
#include <sstream>

#include "decode.h"
#include "read.h"

class Instruction {
    public:
        IType type;
        std::string opcode;

        unsigned short addr;
        unsigned char x;
        unsigned char y;
        unsigned char byte;
        unsigned char nibble;

        Instruction(unsigned short opcode_num) {
            opcode = opcode_to_str(opcode_num);
            clear();


            auto iter = encodings.begin();
            while (iter != encodings.end()) {
                if (identify(iter -> first)) {
                    type = iter -> second;
                    return;
                }
                ++iter;
            }

            error("Unknown instruction 0x" + opcode);
        }

    private:
        char hex_digits[16] = {
            '0', '1', '2', '3',
            '4', '5', '6', '7', 
            '8', '9', 'a', 'b', 
            'c', 'd', 'e', 'f'};

        std::string opcode_to_str(unsigned short opcode) {
            std::stringstream ss;
            ss << std::hex << std::setfill('0') << std::setw(4) << opcode;
            return ss.str();
        }

        void clear() {
            addr = 0;
            x = 0;
            y = 0;
            byte = 0;
            nibble = 0;
        }

        int hex_loc_of(char c) {
            for (int i = 0; i < 16; i++) {
                if (hex_digits[i] == c) {
                    return i;
                }
            }
            return -1;
        }

        bool identify(std::string check) {
            char kk[2]  = {'0', '0'};
            char nnn[4] = {'0', '0', '0', '0'};

            int kk_c = 0;
            int nnn_c = 1;

            for (int i = 0; i < 4; i ++) {
                switch (check[i]) {
                    case 'n': // ADDR NNN
                        nnn[nnn_c] = opcode[i];
                        nnn_c ++;

                        break;

                    case 'z': // NIBBLE
                        nibble = hex_loc_of(opcode[i]);
                        break;

                    case 'x': // X-POS
                        x = hex_loc_of(opcode[i]);
                        break;

                    case 'y': // Y-POS
                        y = hex_loc_of(opcode[i]);
                        break;

                    case 'k': // BYTE KK
                        kk[kk_c] = opcode[i];
                        kk_c ++;

                        break;

                    default:
                        if (check[i] != opcode[i]) {
                            clear();
                            return false;
                        }
                        break;
                }
            }

            addr = (
                hex_loc_of(nnn[0]) << 12) | 
                (hex_loc_of(nnn[1]) << 8) | 
                (hex_loc_of(nnn[2]) << 4) |
                hex_loc_of(nnn[3]);

            byte = (
                hex_loc_of(kk[0]) << 4) |
                hex_loc_of(kk[1]);

            return true;
        }
};