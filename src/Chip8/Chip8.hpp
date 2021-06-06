#ifndef CHIP8_HPP
#define CHIP8_HPP

class Chip8;

#include <wx/sound.h>

#include <chrono>
#include <string>
#include <thread>

#define WIDTH  (64)
#define HEIGHT (32)
#define SCREEN_SIZE (WIDTH*HEIGHT*3)
#define VF (V[15])
#define OPCODE_NBR (34)
#define CHIP8_MEMORY_SIZE (4096)

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

struct Chip8State
{
    uint8_t delay;
    uint8_t sound;
    uint16_t PC;
    uint16_t I;
    int8_t  SP;
    uint16_t stack[16];
    uint8_t  V[16];
};

struct Instruction
{
    uint16_t opcode;
    uint16_t mask;
};

class Chip8
{
    uint8_t memory[CHIP8_MEMORY_SIZE];
    uint8_t delay;
    uint8_t sound;
    uint16_t PC;
    uint16_t I;
    int8_t  SP;
    uint16_t stack[16];
    uint8_t  V[16];

    Instruction instructions[OPCODE_NBR];
    std::thread executionThread;
    bool run;
    bool isRunning;

    unsigned char beep[76] = {0x52, 0x49, 0x46, 0x46, // RIFF
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

    void Interpreter();

    void ClearMemory();
    void ClearScreen();
    void Draw(const uint8_t x, const uint8_t y, const uint8_t n);
    void GenerateInstructionSet();
    int8_t GetInstruction(const uint16_t opcode) const;
    uint16_t GetNextWord();
    void LoadFont();
    void WaitKey(const uint8_t x);

    uint32_t clockInterval;

public:
    wxSound audio;
    uint8_t screen[SCREEN_SIZE]; // direct RGB data for performances
    bool keys[16];
    int8_t lastKey;

    bool romOpened;
    std::string romPath;

    Chip8() = delete;
    Chip8(Chip8&) = delete;
    Chip8(Chip8&&) = delete;
    explicit Chip8(size_t frequency); // frequency in instruction per second

    void CloseROM();
    bool OpenROM(const std::string& path);
    void Run(const bool loop = true);
    void Stop(const bool wait = true);
    void Reset();
    void SetEmulationSpeed(size_t frequency);
    bool IsRunning() const;
    Chip8State GetState() const;
    const uint8_t* GetMemory() const;
};

#endif // CHIP8_HPP
