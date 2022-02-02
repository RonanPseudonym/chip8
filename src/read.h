#include <fstream>

class RomLoader {
	private:
		char rom[4096];
		int rom_length; 

		std::string name;
		std::string file_contents;

	public:
		RomLoader(std::string _name) {
			name = _name;
		}

		void load() {
			std::ifstream infile (name, std::ios::in | std::ios::out | std::ios::binary);

			int c = 0;
			char input;

			while (!infile.eof())
		    {
		    	char input = infile.get();

		        rom[c] = input;
		        c++;
		    }

		    rom_length = c + 1;
		}

		void load_to_memory(unsigned char (&memory)[4096], int offset) {
			for (int i = 0; i < rom_length; i++) {
				memory[i + offset] = rom[i];
			}
		}
};