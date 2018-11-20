#ifndef CHIP8_HPP
#define CHIP8_HPP

class Chip8;

#include <cstdint>

#include "../GUI/GamePanel.hpp"

typedef struct
{
    uint16_t opcode;
    uint16_t mask;
} Instruction;

class Chip8
{
    bool run;
    GamePanel* gamePanel;
    Instruction instructions[35];

public:
    int8_t* memory;
    uint16_t stack[16];
    uint8_t V[16];
    uint16_t I;
    uint16_t PC;
    uint16_t SP;
    uint8_t sound;
    uint8_t timer;

    Chip8(GamePanel* gp);
    ~Chip8();
    void Run();
    bool Init();
    void Pause(bool val = false);
    void Restart(bool runAgain = true);
    void Execute();

    void LoadFont();
    bool LoadROM(const char* file);
    void CloseROM();

    uint16_t GetNextOpcode();
    int8_t GetInstruction(uint16_t opcode) const;
};

enum InstructionSet
{
    SYS,
    CLS,
    RET,
    JPaddr,
    CALL,
    SEVxByte,
    SNEVxByte,
    SEVxVy,
    LDVxByte,
    ADDVxByte,
    LDVxVy,
    OR,
    AND,
    XOR,
    ADDVxVy,
    SUB,
    SHR,
    SUBN,
    SHL,
    SNEVxVy,
    LDIaddr,
    JPV0addr,
    RND,
    DRW,
    SKP,
    SKNP,
    LDVxDT,
    LDVxK,
    LDDTVx,
    LDSTVx,
    ADDIVx,
    LDFVx,
    LDBVx,
    LDIVx,
    LDVxI
};

#endif // CHIP8_HPP
