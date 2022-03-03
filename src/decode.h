#include <map>

enum IType {
    _SYS_ADDR, // Depritacted

    CLS,
    RET,

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
    SHR_VX_VY,
    SUBN_VX_VY,
    SHL_VX_VY,
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

    // ===== SUPER CHIP-8

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
    {"1nnn", IType::JP_ADDR},
    {"annn", IType::LD_I_ADDR},
    {"6xkk", IType::LD_VX_BYTE},
    {"7xkk", IType::ADD_VX_BYTE},
    {"dxyz", IType::DRAW_X_Y_NIBL},
};