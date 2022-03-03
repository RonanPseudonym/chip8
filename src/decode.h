#include <map>

enum IType {
    CLS,
    JUMP_ADDR,
    LD_VX_BYTE,
    ADD_VX_BYTE,
    LD_I_ADDR,
    DRAW_X_Y_NIBL
};

std::map<std::string, IType> encodings {
    {"00e0", IType::CLS},
    {"1nnn", IType::JUMP_ADDR},
    {"annn", IType::LD_I_ADDR},
    {"6xkk", IType::LD_VX_BYTE},
    {"7xkk", IType::ADD_VX_BYTE},
    {"dxyz", IType::DRAW_X_Y_NIBL},
};