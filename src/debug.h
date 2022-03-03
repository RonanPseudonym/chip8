#include <iostream>
#include <ctime>

bool err_flag;

void pretty_print(std::string type, std::string color, std::string text) {
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);

    std::cout << 
        // "\e[0;61m" << now -> tm_hour << ":" << now -> tm_min << ":" << now -> tm_sec << 
        "\033[" << color << "m[" << type << "]\033[0m " << text << std::endl;
}

void ok(std::string message) {
    pretty_print("OK", "32;1", message);
}

void warning(std::string message) {
    pretty_print("WARNING", "33;1", message);
}

void br() {
    std::cout << std::endl;
}

void error(std::string message) {
    br();
    pretty_print("ERR", "31;1", message);
    err_flag = true;
}