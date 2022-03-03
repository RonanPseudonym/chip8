#include <fstream>
#include "debug.h"

class RomLoader {
	private:
		char rom[4096];
		int rom_length; 

		std::string name;
		std::string file_contents;

	public:
		RomLoader(std::string _name) {
			name = _name;

			ok("RomLoader instantiated");

			if (name.substr(name.find_last_of(".") + 1) != "ch8") {
				warning("File extension is not .ch8");
			};
		}

		void load() {
			std::ifstream infile (name, std::ios::in | std::ios::out | std::ios::binary);

			if (!infile) {
				error("Could not open file " + name);
				return;
			}

			ok("File readable");

			int c = 0;
			char input;

			while (!infile.eof())
		    {
		    	char input = infile.get();

		        rom[c] = input;
		        c++;
		    }

			ok("File loaded into memory");

		    rom_length = c + 1;
			ok("ROM size calculated");
		}

		void load_to_memory(unsigned char (&memory)[4096], int offset) {
			for (int i = 0; i < rom_length; i++) {
				memory[i + offset] = rom[i];
			}
		}
};