#ifndef CHIP8_HPP
#define CHIP8_HPP

class Chip8;

#include <cstdint>

#include <wx/sound.h>

#include "../GUI/GamePanel.hpp"
#include "../Chip8Emu.hpp"

#define VF V[15]

typedef struct
{
    uint16_t opcode;
    uint16_t mask;
} Instruction;

class Chip8
{
    GamePanel* gamePanel;
    Instruction instructions[35];
    unsigned char beep[46] {0x52, 0x49, 0x46, 0x46, // RIFF
                38, 0, 0, 0, // file size
                0x57, 0x41, 0x56, 0x45, // WAVE
                0x66, 0x6D, 0x74, 0x20,// fmt
                16, 0, 0, 0, // bloc size
                1, 0, // PCM
                1, 0, // Mono
                0x44, 0xAC, 0, 0, // 44100 Hz
                0x44, 0xAC, 0, 0,
                1, 0,
                8, 0,
                0x64, 0x61, 0x74, 0x61, // data
                2, 0, 0, 0, // data size
                255, 0
    };

    wxSound audio;

public:
    uint8_t* memory;
    uint16_t stack[16];
    uint8_t V[16];
    uint16_t I;
    uint16_t PC;
    uint16_t SP;
    uint8_t sound;
    uint8_t delay;
    bool keys[16];

    wxLongLong last;

    bool stop;

    Chip8(GamePanel* gp);
    ~Chip8();
    void Run();
    bool Init();
    void Pause(bool val = false);
    void Execute();

    void ExportMemory();

    void LoadFont();
    bool OpenROM(const char* file);
    void Reset();
    void CloseROM();

    uint16_t GetNextOpcode();
    int8_t GetInstruction(uint16_t opcode) const;
};

enum InstructionSet
{
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
