#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <cstdint>

typedef struct
{
    uint16_t opcode;
    uint16_t mask;
} InstructionSet;

class Chip8
{
    bool run;
    int8_t* memory;
    InstructionSet instructionSet[35];

public:
    Chip8();
    ~Chip8();
    void Run();
    bool Init();
    void Pause();
    void Restart();
    void Execute();
};

#endif // CHIP8_HPP
