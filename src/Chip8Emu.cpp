#include "Chip8Emu.hpp"

Chip8Emu::Chip8Emu() : wxApp(), chip8(700)
{
}

bool Chip8Emu::OnInit()
{
    new MainFrame(this);
    return true;
}

int Chip8Emu::OnExit()
{
    chip8.Stop(false);
    return 1;
}
