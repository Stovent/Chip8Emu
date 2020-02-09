#ifndef CHIP8_HPP
#define CHIP8_HPP

class Chip8;

#include <string>

#include <wx/sound.h>

#include "../Chip8Emu.hpp"

#define WIDTH  (64)
#define HEIGHT (32)
#define VF (V[15])
#define OPCODE_NBR (34)

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
    ORVxVy,
    ANDVxVy,
    XORVxVy,
    ADDVxVy,
    SUBVxVy,
    SHRVxVy,
    SUBNVxVy,
    SHLVxVy,
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

typedef struct
{
    uint16_t opcode;
    uint16_t mask;
} Instruction;

class Chip8
{
    uint8_t memory[4096];
    uint8_t delay;
    uint8_t sound;
    int8_t  SP;
    uint16_t PC;
    uint16_t I;
    uint16_t stack[16];
    uint8_t  V[16];

    std::chrono::steady_clock::time_point timePoint;
    Instruction instructions[OPCODE_NBR];

    wxSound audio;
    unsigned char beep[76] {0x52, 0x49, 0x46, 0x46, // RIFF
                0x3C, 0, 0, 0, // file size
                0x57, 0x41, 0x56, 0x45, // WAVE
                0x66, 0x6D, 0x74, 0x20,// fmt
                0x10, 0, 0, 0, // bloc size
                1, 0, // PCM
                1, 0, // Mono
                0x44, 0xAC, 0, 0, // 44100 Hz
                0x44, 0xAC, 0, 0,
                1, 0,
                8, 0,
                0x64, 0x61, 0x74, 0x61, // data
                0x20, 0, 0, 0, // data size
                128, 0, 128, 0, 128, 0, 128, 0, 128, 0, 128, 0, 128, 0, 128, 0, 128, 0, 128, 0, 128, 0, 128, 0, 128, 0, 128, 0, 128, 0, 128, 0
    };

    void (Chip8::*Execute)() = nullptr;
    void Interpreter();

    void ClearMemory();
    void ClearScreen();
    void Draw(const uint8_t x, const uint8_t y, const uint8_t n);
    void GenerateInstructionSet();
    int8_t GetInstruction(const uint16_t opcode) const;
    uint16_t GetNextWord();
    void Reset();
    void LoadFont();
    void WaitKey(const uint8_t x);

    uint32_t clockInterval;

public:
    uint8_t screen[WIDTH*HEIGHT*3]; // direct RGB data for performances
    bool keys[16];
    int8_t lastKey;

    bool run;
    bool romOpened;
    std::string romPath;

    Chip8(uint32_t frequency); // frequency in instruction per second

    void CloseROM();
    bool OpenROM(const std::string& path);
    void Run();
};

#endif // CHIP8_HPP
