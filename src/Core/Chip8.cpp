#include "Chip8.hpp"

#include <cstring>

Chip8::Chip8()
{
    run = true;
    memory = new int8_t[4096];
    Init();
}

Chip8::~Chip8()
{
    delete[] memory;
}

void Chip8::Run()
{
    while (true)
        if(run)
            Execute();
}

bool Chip8::Init()
{
    if(memory == nullptr)
        return false;
    memset(memory, 0, 4096);
    return true;
}

void Chip8::Pause()
{
    run = false;
}

void Chip8::Restart()
{
    run = false;
    Init();
    run = true;
}

void Chip8::Execute()
{

}
