#include <unistd.h>
#include <cstring>
#include <map>
#include "debug.h"

std::map<std::string, bool> flags {
    {"sys_addr_cmd", false},
    {"original_shift", false},
    {"modern_offset_jump", false},
    {"original_store_and_load", false}
};

void parse_cli(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        std::string arg = std::string(argv[i]);
        if (arg == "--help") {
            info("Usage: " + std::string(argv[0]) + " [ROM]" );
            br();
            // print out all valid flags
            info("Valid flags:");
            for (auto it = flags.begin(); it != flags.end(); it++) {
                info("  --" + it->first);
            }

            exit(0);
        } else if (arg.substr(0, 2) == "--") {
            // get all characters in arg ignoring the first two
            std::string arg_sub = arg.substr(2);

            // find arg_sub in flags
            auto it = flags.find(arg_sub);
            if (it != flags.end()) {
                // set flag to true
                flags[arg_sub] = true;
                ok("Flag " + arg + " recognized");
            } else {
                warning("Unknown flag '" + arg_sub + "', ignoring for now");
            }
        }
    }
}