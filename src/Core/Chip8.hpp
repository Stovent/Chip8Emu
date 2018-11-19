#ifndef CHIP8_HPP
#define CHIP8_HPP

class Chip8;

#include <cstdint>

#include "../GUI/GamePanel.hpp"

typedef struct
{
    uint16_t opcode;
    uint16_t mask;
} InstructionSet;

class Chip8
{
    bool run;
    int8_t* memory;
    GamePanel* gamePanel;
    InstructionSet instructionSet[35];

public:
    Chip8(GamePanel* gp);
    ~Chip8();
    void Run();
    bool Init();
    void Pause();
    void Restart();
    void Execute();
    void LoadFont();
    bool LoadROM(const char* file);
};

#endif // CHIP8_HPP
