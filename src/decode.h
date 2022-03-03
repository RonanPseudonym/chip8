#include <map>

enum IType {
    CLS
};

std::map<std::string, IType> encodings {
    {"00e0", IType::CLS},
};