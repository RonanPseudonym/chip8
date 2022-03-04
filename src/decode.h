#include <map>
#include "cli.h"

enum IType {
    CLS,
    RET,

    SYS_ADDR, // Depritacted

    JP_ADDR,
    CALL_ADDR,

    SE_VX_BYTE,
    SNE_VX_BYTE,

    SE_VX_VY,
    LD_VX_BYTE,
    ADD_VX_BYTE,

    LD_VX_VY,
    OR_VX_VY,
    AND_VX_VY,
    XOR_VX_VY,
    ADD_VX_VY,
    SUB_VX_VY,
    SHR_VX,
    SUBN_VX_VY,
    SHL_VX,
    SNE_VX_VY,

    LD_I_ADDR,
    JP_V0_ADDR,
    RND_VX_BYTE,
    DRAW_X_Y_NIBL,

    SKP_VX,
    SKNP_VX,

    LD_VX_DT,
    LD_VX_K,
    LD_DT_VX,
    LD_ST_VX,

    ADD_I_VX,

    LD_F_VX,
    LD_B_VX,
    LD_I_VX,
    LD_VX_I,

    // ===== SUPER CHIP-8 =====

    SCD_NIBL,
    SCR,
    SCL,
    EXIT,
    LOW,
    HIGH,
    DRW_VX_VY_0,
    LD_HF_VX,
    LD_R_VX,
    LD_VX_R
};

std::map<std::string, IType> encodings {
    {"00e0", IType::CLS},
    {"00ee", IType::RET},

    // Sys addr    

    {"1nnn", IType::JP_ADDR},
    {"2nnn", IType::CALL_ADDR},

    {"3xkk", IType::SE_VX_BYTE},
    {"4xkk", IType::SNE_VX_BYTE},

    {"5xy0", IType::SE_VX_VY},

    {"6xkk", IType::LD_VX_BYTE},
    {"7xkk", IType::ADD_VX_BYTE},

    {"8xy0", IType::LD_VX_VY},
    {"8xy1", IType::OR_VX_VY},
    {"8xy2", IType::AND_VX_VY},
    {"8xy3", IType::XOR_VX_VY},
    {"8xy4", IType::ADD_VX_VY},
    {"8xy5", IType::SUB_VX_VY},
    {"8xy6", IType::SHR_VX},
    {"8xy7", IType::SUBN_VX_VY},
    {"8xyE", IType::SHL_VX},
    {"9xy0", IType::SNE_VX_VY},

    {"annn", IType::LD_I_ADDR},
    {"bnnn", IType::JP_V0_ADDR},
    {"cxkk", IType::RND_VX_BYTE},
    {"dxyz", IType::DRAW_X_Y_NIBL},

    {"ex9e", IType::SKP_VX},
    {"exa1", IType::SKNP_VX},

    {"fx07", IType::LD_VX_DT},
    {"fx0a", IType::LD_VX_K},
    {"fx15", IType::LD_DT_VX},
    {"fx18", IType::LD_ST_VX},

    {"fx1e", IType::ADD_I_VX},
    {"fx29", IType::LD_F_VX},
    {"fx33", IType::LD_B_VX},
    {"fx55", IType::LD_I_VX},
    {"fx65", IType::LD_VX_I},

    // ===== Super CHIP-8 ======

    {"00cz", IType::SCD_NIBL},
    {"00fb", IType::SCR},
    {"00fc", IType::SCL},
    {"00fd", IType::EXIT},
    {"00fe", IType::LOW},
    {"00ff", IType::HIGH},
    {"dxy0", IType::DRW_VX_VY_0},
    {"fx30", IType::LD_HF_VX},
    {"fx75", IType::LD_R_VX},
    {"fx85", IType::LD_VX_R},
};

void add_conditional_flags() {
    if (flags["sys_addr_cmd"]) {
        encodings["0nnn"] = IType::SYS_ADDR;
    }
}